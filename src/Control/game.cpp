#include "Control/game.h"

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Main window settings
const std::string window_title_g = "Game";
const unsigned int window_width_g = 1280;
const unsigned int window_height_g = 720;
const bool window_full_screen_g = false;

// Viewport and camera settings
glm::vec3 camera_position_g(0.5, 0.5, 10.0);
glm::vec3 camera_look_at_g(0.0, 0.0, 0.0);
glm::vec3 camera_up_g(0.0, 1.0, 0.0);
const glm::vec3 viewport_background_color_g(0.1, 0.1, 0.1);

// Materials 
const std::string material_directory_g = MATERIAL_DIRECTORY;

Game::Game(void){
    // do nothing
}

void Game::Init(void){
    // Run all initialization steps
    InitWindow();
    InitView();
    InitEventHandlers();
    InitMenus(); // must be called after the GLFWwindow is initialized

    // Set variables
    state_ = State::STOPPED;
    freeroam_ = false;
}
       
void Game::InitWindow(void){
    // Initialize the window management library (GLFW)
    if (!glfwInit()){
        throw(GameException(std::string("Could not initialize the GLFW library")));
    }

    // not sure if we want the window to be resizable (we could make resolution a setting?)
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a window and its OpenGL context
    if (window_full_screen_g){
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), glfwGetPrimaryMonitor(), NULL);
    } else {
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), NULL, NULL);
    }
    if (!window_){
        glfwTerminate();
        throw(GameException(std::string("Could not create window")));
    }

    // Make the window's context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        throw(GameException(std::string("Could not initialize the GLEW library: ")+std::string((const char *) glewGetErrorString(err))));
    }
}

void Game::InitMenus() {
    // initialize ImGUI instance
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsClassic();

    // create menus
    menus_[MenuType::MAIN] = new MainMenu();
    menus_[MenuType::PAUSE] = new PauseMenu();
    menus_[MenuType::HUD] = new HUD();
    menus_[MenuType::UPGRADES] = new Upgrades();
}

void Game::InitView(void){
    // Set up z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Set viewport
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);

    // Enable primiteve restart
    glPrimitiveRestartIndex(-1);
    glEnable(GL_PRIMITIVE_RESTART);

    // Set up camera
    camera_ = new Camera(camera_position_g, camera_look_at_g, camera_up_g, width, height);
}

void Game::InitEventHandlers(void){
    // Set event callbacks
    Input::setup(window_);
    //glfwSetKeyCallback(window_, KeyCallback);
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Set pointer to game object, so that callbacks can access it
    glfwSetWindowUserPointer(window_, (void *) this);
}

void Game::SetupResources(void) {
    std::string filename;

    // Create geometry of the objects
    resman_.CreateQuad("FlatSurface");

    // Load/Create terrain
    resman_.CreateTerrain("Terrain", glm::vec3(2.5f, 1.0f, 2.5f));
    //filename = std::string(TEXTURE_DIRECTORY) + std::string("/terrain_height_map.png");
    //resman_.LoadResource(ResourceType::Terrain, "Terrain", filename.c_str(), glm::vec3(5.0f, 1.0f, 5.0f));

    // Load geometry
    filename = std::string(MESH_DIRECTORY) + std::string("/cube.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Cube", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/sphere.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Sphere", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Chassis.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_BASE, filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Turret.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_TURRET, filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Track_Rear.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_TRACK_REAR, filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Track_Front.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_TRACK_FRONT, filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Scanner.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_SCANNER, filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Scanner_Cone.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_SCANNER_CONE, filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Machine_Gun.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_MACHINE_GUN, filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/environment") + std::string("/pool.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Pool", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/environment") + std::string("/rock1.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Rock1", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/environment") + std::string("/rock2.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Rock2", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/environment") + std::string("/rock3.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Rock3", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("/environment") + std::string("/plant.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Plant", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("") + std::string("/parachute.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Parachute", filename.c_str());

    // Load shaders
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/simple_texture");
    resman_.LoadResource(ResourceType::Material, "Simple", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/instancing");
    resman_.LoadResource(ResourceType::Material, "Instanced", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/lit");
    resman_.LoadResource(ResourceType::Material, "Lighting", filename.c_str());

    // Load texture
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/rocky.png");
    resman_.LoadResource(ResourceType::Texture, "RockyTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/uv6.png");
    resman_.LoadResource(ResourceType::Texture, "uv6", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/hovertank_texture.png");
    resman_.LoadResource(ResourceType::Texture, "HovertankTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/environment") + std::string("/mud.png");
    resman_.LoadResource(ResourceType::Texture, "MudTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/environment") + std::string("/acid.png");
    resman_.LoadResource(ResourceType::Texture, "AcidTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/environment") + std::string("/geyser.png");
    resman_.LoadResource(ResourceType::Texture, "GeyserTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/environment") + std::string("/alien_plant.png");
    resman_.LoadResource(ResourceType::Texture, "PlantTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("") + std::string("/crate.png");
    resman_.LoadResource(ResourceType::Texture, "Crate", filename.c_str());
}

void Game::SetupScene(void) {
    // Set background color for the scene
    scene_.SetBackgroundColor(viewport_background_color_g);

    // Create Terrain Instance
    Terrain* terrain = CreateInstance<Terrain>("Terrain Object", "Terrain", "Lighting", "uv6");
    terrain->Translate(glm::vec3(-625.f, 0.0F, -625.0F));
    terrain_ = terrain;

    // create hovertank hierarchy
    // to convert blender coordinates to opengl coordinates: (x, y, z) -> (x, z, -y)
    // if scaling: multiply all translation values by the scale factor
    // if a new model is loaded, will probably need to update these translations
    std::string hovertankMaterial = "Simple";
    HoverTank* hovertank_base = CreateInstance<HoverTank>(HOVERTANK_BASE, HOVERTANK_BASE, hovertankMaterial, "HovertankTexture");
    player_ = new Player(100.f, 100.f, hovertank_base);
    player_->AddMoney(100000); // for demo purposes
  
    HoverTankTurret* hovertank_turret = CreateInstance<HoverTankTurret>(HOVERTANK_TURRET, HOVERTANK_TURRET, hovertankMaterial, "HovertankTexture");
    hovertank_turret->Translate(glm::vec3(0.f, 1.055f, -0.4f));
    hovertank_turret->SetParent(hovertank_base);
    hovertank_turret->SetForward(hovertank_base->GetForward());
    hovertank_base->SetTurret(hovertank_turret);

    // create hovertank tracks
    std::string trackLocations[] = { "Rear", "Rear", "Front", "Front" };
    std::vector<HoverTankTrack*> hovertank_tracks;
    for (int i = 0; i < 4; ++i) {
        hovertank_tracks.push_back(CreateInstance<HoverTankTrack>("HovertankTrack" + trackLocations[i], "HovertankTrack" + trackLocations[i], hovertankMaterial, "HovertankTexture"));
        hovertank_tracks.at(i)->SetParent(hovertank_base);
        float dx = -1.4f + 2.8f * ((i + 1) % 2); // left tracks (i=0,2) should translate (x) by 1.4, right (i=1,3) by -1.4
        float dy = -0.3f; // all tracks should translate (y) by -.3
        float dz = -1.0f + 3.0f * (floor(i / 2)); // back tracks (i=0,1) should translate (z) by -1, front (i=2,3) by 3
        hovertank_tracks.at(i)->Translate(glm::vec3(dx, dy, dz));
    }
    
    // Create Hovertank scanner
    Scanner* hovertank_scanner = CreateInstance<Scanner>("Scanner", HOVERTANK_SCANNER, hovertankMaterial, "uv6");
    hovertank_scanner->Translate(glm::vec3(0.0f, 0.345, 1.0375f));
    hovertank_scanner->SetParent(hovertank_turret);
    hovertank_base->SetScanner(hovertank_scanner);

    // Create Artifacts
    Artifact* artifact1 = CreateInstance<Artifact>("Artifact 1", "Cube", "Simple", "uv6");
    artifact1->SetPosition(glm::vec3(5.0f, -11.0f, 25.0f));
    artifacts_.push_back(artifact1);

    EnvironmentObject* rocks1 = CreateInstance<EnvironmentObject>("Rocks 1", "Rock1", "Instanced", "RockyTexture");
    rocks1->InitPositions(1337, 250);
    rocks1->SetInstanceGroupID(0);
    rocks1->SetColliderRadius(1.5f);
    EnvironmentObject* rocks2 = CreateInstance<EnvironmentObject>("Rocks 2", "Rock2", "Instanced", "RockyTexture");
    rocks2->InitPositions(65156, 250);
    rocks2->SetInstanceGroupID(1);
    rocks2->SetColliderRadius(1.0f);
    EnvironmentObject* rocks3 = CreateInstance<EnvironmentObject>("Rocks 3", "Rock3", "Instanced", "RockyTexture");
    rocks3->InitPositions(351351, 250);
    rocks3->SetInstanceGroupID(2);
    rocks3->SetColliderRadius(2.0f);
    EnvironmentObject* rocks4 = CreateInstance<EnvironmentObject>("Plant", "Plant", "Instanced", "PlantTexture");
    rocks4->InitPositions(7516331, 250);
    rocks4->SetInstanceGroupID(3);
    rocks4->SetColliderRadius(1.0f);

    // should be using the CalculateTerrainHeightAt function to place the hazards (and make a function for it?)
    // should also calculate collision box based on scale
    // this is all temporary
    AcidPool* acidPool = CreateInstance<AcidPool>("AcidPool1", "Pool", "Simple", "AcidTexture");
    acidPool->SetPosition(glm::vec3(5.0f, -14.0f, 40.0f));
    acidPool->Scale(glm::vec3(15));

    MudPool* mudPool = CreateInstance<MudPool>("MudPool1", "Pool", "Simple", "MudTexture");
    mudPool->SetPosition(glm::vec3(45.0f, -9.0f, 40.0f));
    mudPool->Scale(glm::vec3(15));

    Geyser* geyser = CreateInstance<Geyser>("Geyser1", "Pool", "Simple", "GeyserTexture");
    geyser->SetPosition(glm::vec3(-35.0f, -20.0f, 40.0f));
    geyser->Scale(glm::vec3(15));
    
    ShooterEnemy* enemy = CreateInstance<ShooterEnemy>("Enemy1", "Cube", "Simple", "uv6");
    enemy->SetPosition(glm::vec3(10.0f, -5.0f, 25.0f));
    enemies_.push_back(enemy);

    ChaserEnemy* enemyChase = CreateInstance<ChaserEnemy>("Enemy2", "Cube", "Simple", "uv6");
    enemyChase->SetPosition(glm::vec3(15.0f, -5.0f, 25.0f));
    enemies_.push_back(enemyChase);

    // Create Care Package
    CarePackage* package = CreateInstance<CarePackage>("Package", "Cube", "Simple", "Crate");
    package->SetPosition(glm::vec3(-30.0f, 35.0f, 75.0f));

    // Initialize certain scene nodes
    terrain_->Init();
    rocks1->Init();
    rocks2->Init();
    rocks3->Init();
    rocks4->Init();
}

void Game::MainLoop(void){
    // Loop while the user did not close the window
    while (!glfwWindowShouldClose(window_)){
        Time::Update(); // time should update every frame

        // Clear background
        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Press 'Escape' key to pause/unpause game
        if (Input::getKeyDown(INPUT_KEY_ESCAPE)) {
            switch (state_) {
            case State::PAUSED: state_ = State::RUNNING; break;
            case State::RUNNING: state_ = State::PAUSED; break;
            case State::UPGRADES: state_ = State::PAUSED; break; // switch to pause menu
            default: break;
            }
        }
        // Press 'U' key to open/close the upgrades screen
        if (Input::getKeyDown(INPUT_KEY_U)) {
            switch (state_) {
            case State::PAUSED: state_ = State::UPGRADES; break; // switch to upgrades screen
            case State::RUNNING: state_ = State::UPGRADES; break;
            case State::UPGRADES: state_ = State::RUNNING; break;
            }
        }

        // toggle freeroam if 'F' key clicked
        // developer feature - should probably be removed before submission
        if (Input::getKeyDown(INPUT_KEY_F)) {
            freeroam_ = !freeroam_;
        }

        // render main menu when game is stopped
        if (state_ == State::STOPPED) {
            menus_[MenuType::MAIN]->Render();
        }
        // render pause menu and frozen game state in the background when paused
        else if (state_ == State::PAUSED) {
            scene_.Draw(camera_);
            menus_[MenuType::PAUSE]->Render();
        }
        // render upgrades screen and frozen game state in the background
        else if (state_ == State::UPGRADES) {
            scene_.Draw(camera_);
            menus_[MenuType::UPGRADES]->Render();
        }
        // update and render game when running
        else if (state_ == State::RUNNING) {
            // handle camera movement
            if (freeroam_) {
                camera_->UpdateCameraFreeroam();
            } else {
                camera_->UpdateCameraToTarget((HoverTank*)scene_.GetNode(HOVERTANK_BASE));
            }

            // for tooltip testing
            if (Input::getKeyDown(INPUT_KEY_T)) {
                ((HUD*)menus_[MenuType::HUD])->ActivateTooltip("Test", 1.0f);
            }
            
            // removes dead projectiles
            std::vector<Projectile*> projectilesToRemove = player_->GetTank()->GetTurret()->RemoveDeadProjectiles();
            for (auto it = projectilesToRemove.begin(); it != projectilesToRemove.end(); ++it) {
                scene_.RemoveNode((*it)->GetName());
            }
     
            //remove dead enemy projectiles
            std::vector<Projectile*> enemyprojecttilesToRemove = RemoveDeadEnemyProjectiles();
            for (auto it = enemyprojecttilesToRemove.begin(); it != enemyprojecttilesToRemove.end(); ++it) {
                scene_.RemoveNode((*it)->GetName());
            }

            player_->Update(); // player has it's own update method
            scene_.Update();
            scene_.Draw(camera_);
            

            
            
            // render the HUD overtop of the game and handle its input
            menus_[MenuType::HUD]->Render();
            menus_[MenuType::HUD]->HandleInput();
        }

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);
        Input::update();

        // Update other events like input handling
        glfwPollEvents();
    }
}

void Game::ResizeCallback(GLFWwindow* window, int width, int height){
    // Set up viewport and camera projection based on new window size
    glViewport(0, 0, width, height);
    void* ptr = glfwGetWindowUserPointer(window);
    Game *game = (Game *) ptr;
    game->camera_->SetProjection(width, height);
}

Game::~Game(){
    
    glfwTerminate();
}

Resource* Game::GetResource(std::string res) {
    Resource* resource = resman_.GetResource(res);
    if (!resource) {
        throw(GameException(std::string("Could not find resource \"") + res + std::string("\"")));
    }
}

void Game::RemoveInstance(SceneNode* entity) {
    scene_.RemoveNode(entity);
}

std::vector<Projectile*> Game::RemoveDeadEnemyProjectiles() {
    std::vector<Projectile*> projectilesToRemove;

    //goes through entire list of enemy projectiles, if it's dead get rid of it
    for (int i = enemy_projectiles_.size() - 1; i >= 0; i--) {
        if (!enemy_projectiles_[i]->IsAlive()) {
            projectilesToRemove.push_back(enemy_projectiles_[i]);
            enemy_projectiles_.erase(enemy_projectiles_.begin() + i);
        }
    }

    return projectilesToRemove;
}

void Game::AddEnemyProjectile(Projectile * proj) {
    enemy_projectiles_.push_back(proj);
}

Camera* Game::GetCamera() {
    return camera_;
}

GLFWwindow* Game::GetWindow()
{
    return window_;
}

Terrain* Game::GetTerrain() {
    return terrain_;
}

Player* Game::GetPlayer() {
    return player_;
}

void Game::SetState(State state) {
    state_ = state;
}

std::vector<Projectile*> *Game::GetReferenceToEnemyProjectiles() {
    return &enemy_projectiles_;
}

std::vector<Projectile*> Game::GetEnemyProjectiles() {
    return enemy_projectiles_;
}

std::vector<Enemy*> Game::GetEnemies() {
    return enemies_;
}

bool Game::GetFreeroam() const {
    return freeroam_;
}

std::vector<Artifact*>& Game::GetArtifacts() {
    return artifacts_;
}

std::vector<CarePackage*>& Game::GetCarePackages() {
    return carePackages_;
}

Menu* Game::GetMenu(MenuType menu)
{
    return menus_[menu];
}

void Game::AddCarePackage(CarePackage* package) {
    carePackages_.push_back(package);
}

void Game::RemoveCarePackage(CarePackage* package) {
    auto itr = std::find(carePackages_.begin(), carePackages_.end(), package);
    if((*itr) == package) carePackages_.erase(itr);
}

} // namespace game
