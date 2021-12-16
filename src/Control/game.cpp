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
    menus_[MenuType::GAME_OVER] = new GameOver();
    menus_[MenuType::YOU_WIN] = new YouWin();
    menus_[MenuType::TEXT_WINDOW] = new TextWindow();
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
    Input::setMouseHorizontalSensitivity(10.0f);
    //glfwSetKeyCallback(window_, KeyCallback);
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Set pointer to game object, so that callbacks can access it
    glfwSetWindowUserPointer(window_, (void *) this);
}

void Game::SetupResources(void) {
    std::string filename;

    // Create geometry of the objects
    resman_.CreateQuad("FlatSurface");
    resman_.CreateParticle("Particle");

    // Load/Create terrain
    resman_.CreateTerrain("Terrain", glm::vec3(2.5f, 1.0f, 2.5f));

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
    filename = std::string(MESH_DIRECTORY) + std::string("/hovertank") + std::string("/hovertank_Gun_Stand.mesh");
    resman_.LoadResource(ResourceType::Mesh, HOVERTANK_GUN_STAND, filename.c_str());
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
    filename = std::string(MESH_DIRECTORY) + std::string("") + std::string("/enemy.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Alien", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("") + std::string("/rubber_bullet.mesh");
    resman_.LoadResource(ResourceType::Mesh, "RubberBullet", filename.c_str());
    filename = std::string(MESH_DIRECTORY) + std::string("") + std::string("/spike_ball.mesh");
    resman_.LoadResource(ResourceType::Mesh, "SpikeBall", filename.c_str());

    // Load shaders
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/simple_texture");
    resman_.LoadResource(ResourceType::Material, "Simple", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/instancing");
    resman_.LoadResource(ResourceType::Material, "Instanced", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/lit");
    resman_.LoadResource(ResourceType::Material, "Lighting", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/geyser_particle");
    resman_.LoadResource(ResourceType::Material, "GeyserParticles", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/artifact_particle");
    resman_.LoadResource(ResourceType::Material, "ArtifactParticles", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/terrain");
    resman_.LoadResource(ResourceType::Material, "TerrainMaterial", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/screen_space_effect");
    resman_.LoadResource(ResourceType::Material, "ScreenSpaceEffect", filename.c_str());

    // Load texture
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/uv6.png");
    resman_.LoadResource(ResourceType::Texture, "uv6", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/environment") + std::string("/rocky.png");
    resman_.LoadResource(ResourceType::Texture, "RockyTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/environment") + std::string("/snow.png");
    resman_.LoadResource(ResourceType::Texture, "SnowTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/environment") + std::string("/dirt.png");
    resman_.LoadResource(ResourceType::Texture, "DirtTexture", filename.c_str());
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
    resman_.LoadResource(ResourceType::Texture, "CrateTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("") + std::string("/parachute.png");
    resman_.LoadResource(ResourceType::Texture, "ParachuteTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("") + std::string("/water_particle.png");
    resman_.LoadResource(ResourceType::Texture, "GeyserParticleTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("") + std::string("/sparkle_particle.png");
    resman_.LoadResource(ResourceType::Texture, "ArtifactParticleTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/projectiles") + std::string("/energy_blast.png");
    resman_.LoadResource(ResourceType::Texture, "EnergyBlastTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/projectiles") + std::string("/rubber.png");
    resman_.LoadResource(ResourceType::Texture, "RubberTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/projectiles") + std::string("/electric.png");
    resman_.LoadResource(ResourceType::Texture, "ElectricTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/chaser_enemy.png");
    resman_.LoadResource(ResourceType::Texture, "ChaserEnemyTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/shooter_enemy.png");
    resman_.LoadResource(ResourceType::Texture, "ShooterEnemyTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/scanning.png");
    resman_.LoadResource(ResourceType::Texture, "ScanningTexture", filename.c_str());

    // Setup drawing to texture
    scene_.SetupDrawToTexture();
}

void SetupHovertank();
void SetupArtifacts();
void SetupEnemies();
void SetupHazards();

void Game::SetupScene(void) {
    // Set background color for the scene
    scene_.SetBackgroundColor(viewport_background_color_g);

    // Create Terrain Instance
    Terrain* terrain = CreateInstance<Terrain>("Terrain Object", "Terrain", "TerrainMaterial", "uv6");
    terrain->Translate(glm::vec3(-625.f, 0.0F, -625.0F));
    terrain->SetTextures("SnowTexture", "RockyTexture", "RockyTexture", "DirtTexture");
    terrain->Init();
    terrain_ = terrain;

    // Creates tank instance with all its children
    SetupHovertank();

    // Creates the instanced environmental objects
    EnvironmentObject* rocks1 = CreateInstance<EnvironmentObject>("Rocks 1", "Rock1", "Instanced", "RockyTexture");
    rocks1->InitPositions(1337, 250);
    rocks1->SetInstanceGroupID(0);
    rocks1->SetColliderRadius(1.5f);
    rocks1->Init();
    EnvironmentObject* rocks2 = CreateInstance<EnvironmentObject>("Rocks 2", "Rock2", "Instanced", "RockyTexture");
    rocks2->InitPositions(65156, 250);
    rocks2->SetInstanceGroupID(1);
    rocks2->SetColliderRadius(1.0f);
    rocks2->Init();
    EnvironmentObject* rocks3 = CreateInstance<EnvironmentObject>("Rocks 3", "Rock3", "Instanced", "RockyTexture");
    rocks3->InitPositions(351351, 250);
    rocks3->SetInstanceGroupID(2);
    rocks3->SetColliderRadius(2.0f);
    rocks3->Init();
    EnvironmentObject* rocks4 = CreateInstance<EnvironmentObject>("Plant", "Plant", "Instanced", "PlantTexture");
    rocks4->InitPositions(7516331, 250);
    rocks4->SetInstanceGroupID(3);
    rocks4->SetColliderRadius(1.0f);
    rocks4->Init();

    // Creates the artifacts, hazards, and enemies
    SetupArtifacts();
    SetupHazards();
    SetupEnemies();
}

void Game::DrawScene(std::string effect) {
    // Draw the scene to a texture
    scene_.DrawToTexture(camera_);
    // Process the texture with a screen-space effect and display the texture
    scene_.DisplayTexture(resman_.GetResource(effect)->GetResource());
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
            case State::PAUSED:   SetState(State::RUNNING); break;
            case State::RUNNING:  SetState(State::PAUSED); break;
            case State::UPGRADES: SetState(State::PAUSED); break;
            default: break;
            }
        }
        // Press 'U' key to open/close the upgrades screen
        if (Input::getKeyDown(INPUT_KEY_U)) {
            switch (state_) {
            case State::PAUSED:   SetState(State::UPGRADES); break;
            case State::RUNNING:  SetState(State::UPGRADES); break;
            case State::UPGRADES: SetState(State::RUNNING); break;
            }
        }

        // toggle freeroam if 'F' key clicked
        // developer feature - should probably be removed before submission
        if (Input::getKeyDown(INPUT_KEY_F1)) {
            freeroam_ = !freeroam_;
        }

        // render main menu when game is stopped
        if (state_ == State::STOPPED) {
            menus_[MenuType::MAIN]->Render();
        }
        // render pause menu and frozen game state in the background when paused
        else if (state_ == State::PAUSED) {
            DrawScene("ScreenSpaceEffect");
            menus_[MenuType::PAUSE]->Render();
        }
        // render upgrades screen and frozen game state in the background
        else if (state_ == State::UPGRADES) {
            DrawScene("ScreenSpaceEffect");
            menus_[MenuType::UPGRADES]->Render();
        }
        else if (state_ == State::GAME_OVER) {
            menus_[MenuType::GAME_OVER]->Render();
        }
        else if (state_ == State::YOU_WIN) {
            menus_[MenuType::YOU_WIN]->Render();
        }
        // update and render game when running
        else if (state_ == State::RUNNING) {
            // handle camera movement
            if (freeroam_) {
                camera_->UpdateCameraFreeroam();
            } else {
                camera_->UpdateCameraToTarget((HoverTank*)scene_.GetNode(HOVERTANK_BASE));
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

            // only update if the text window isn't showing
            if(((TextWindow*) menus_[MenuType::TEXT_WINDOW])->GetState() == TextState::NOTHING) {
                player_->Update(); // player has it's own update method
                scene_.Update();
            }
            DrawScene("ScreenSpaceEffect");
            
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

void Game::SetPlayer(Player* player) {
    player_ = player;
}

void Game::SetState(State state) {
    if (state == State::RUNNING) {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    }  else {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
    }

    state_ = state;
}

std::vector<Projectile*> *Game::GetReferenceToEnemyProjectiles() {
    return &enemy_projectiles_;
}

std::vector<Projectile*> Game::GetEnemyProjectiles() {
    return enemy_projectiles_;
}

std::vector<Enemy*>& Game::GetEnemies() {
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

void SetupHovertank() {
    // create hovertank hierarchy
    // to convert blender coordinates to opengl coordinates: (x, y, z) -> (x, z, -y)
    // if scaling: multiply all translation values by the scale factor
    // if a new model is loaded, will probably need to update these translations
    std::string hovertankMaterial = "Lighting";
    std::string hovertankTexture = "HovertankTexture";
    HoverTank* hovertank_base = Game::GetInstance().CreateInstance<HoverTank>(HOVERTANK_BASE, HOVERTANK_BASE, hovertankMaterial, hovertankTexture);
    hovertank_base->SetPosition(glm::vec3(-216.0f, -41.0f, -181.0f));
    Game::GetInstance().SetPlayer(new Player(100.f, 100.f, hovertank_base));

    HoverTankTurret* hovertank_turret = Game::GetInstance().CreateInstance<HoverTankTurret>(HOVERTANK_TURRET, HOVERTANK_TURRET, hovertankMaterial, hovertankTexture);
    hovertank_turret->Translate(glm::vec3(0.f, 1.055f, -0.9f));
    hovertank_turret->SetParent(hovertank_base);
    hovertank_turret->SetForward(hovertank_base->GetForward());
    hovertank_base->SetTurret(hovertank_turret);

    // create hovertank tracks
    std::string trackLocations[] = { "Rear", "Rear", "Front", "Front" };
    std::vector<HoverTankTrack*> hovertank_tracks;
    for (int i = 0; i < 4; ++i) {
        hovertank_tracks.push_back(Game::GetInstance().CreateInstance<HoverTankTrack>("HovertankTrack" + trackLocations[i], "HovertankTrack" + trackLocations[i], hovertankMaterial, hovertankTexture));
        hovertank_tracks.at(i)->SetParent(hovertank_base);
        float dx = -1.4f + 2.8f * ((i + 1) % 2); // left tracks (i=0,2) should translate (x) by 1.4, right (i=1,3) by -1.4
        float dy = -0.3f; // all tracks should translate (y) by -.3
        float dz = -1.5f +3.0f * (floor(i / 2)); // back tracks (i=0,1) should translate (z) by -1, front (i=2,3) by 3
        hovertank_tracks.at(i)->Translate(glm::vec3(dx, dy, dz));
    }
    
    // Create Hovertank scanner
    Scanner* hovertank_scanner = Game::GetInstance().CreateInstance<Scanner>("Scanner", HOVERTANK_SCANNER, hovertankMaterial, hovertankTexture);
    hovertank_scanner->Translate(glm::vec3(0.0f, 0.345, 1.0375f));
    hovertank_scanner->SetParent(hovertank_turret);
    hovertank_base->SetScanner(hovertank_scanner);

    // Create Hovertank gun stand
    SceneNode* hovertank_gun_stand = Game::GetInstance().CreateInstance<SceneNode>("Machine Gun Stand", HOVERTANK_GUN_STAND, hovertankMaterial, hovertankTexture);
    hovertank_gun_stand->SetParent(hovertank_turret);
    hovertank_gun_stand->SetActive(false);

    // Create Hovertank guns
    MachineGun* hovertank_small_gun = Game::GetInstance().CreateInstance<MachineGun>("Machine Gun", HOVERTANK_MACHINE_GUN, hovertankMaterial, hovertankTexture);
    hovertank_small_gun->Translate(glm::vec3(0.325f, 0.895f, -0.35f));
    hovertank_small_gun->SetParent(hovertank_gun_stand);
    hovertank_small_gun->SetActive(false);
    hovertank_base->SetMachineGun(hovertank_small_gun);

    EnergyCannon* hovertank_big_gun = Game::GetInstance().CreateInstance<EnergyCannon>("Energy Cannon", HOVERTANK_MACHINE_GUN, hovertankMaterial, hovertankTexture);
    hovertank_big_gun->Translate(glm::vec3(-0.325f, 0.9f, -0.35f));
    hovertank_big_gun->Scale(glm::vec3(1.5f, 1.5f, 1.0f));
    hovertank_big_gun->Rotate(glm::angleAxis(glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    hovertank_big_gun->SetParent(hovertank_gun_stand);
    hovertank_big_gun->SetActive(false);
    hovertank_base->SetEnergyCannon(hovertank_big_gun);

    EnergyEmitter* energy_blast = Game::GetInstance().CreateInstance<EnergyEmitter>("EnergyBlast", "Cube", hovertankMaterial, "uv6");
	energy_blast->Scale(glm::vec3(0.01));
	energy_blast->SetParent(hovertank_gun_stand);
	energy_blast->SetActive(false);
    hovertank_base->SetEnergyEmitter(energy_blast);
}

Artifact* CreateArtifact(glm::vec2 pos, std::string name, float points) {
    static int artifactID = 0;
    Artifact* artifact = Game::GetInstance().CreateInstance<Artifact>("Artifact" + std::to_string(artifactID), "Cube", "Simple", "uv6");
    artifact->SetPosition(glm::vec3(pos.x, Game::GetInstance().GetTerrain()->GetHeightAt(pos.x, pos.y), pos.y));
    artifact->Setup(name, points, artifactID++);
    Game::GetInstance().GetArtifacts().push_back(artifact);
    return artifact;
}

void SetupArtifacts() {
    // easy artifacts
    Artifact* artifact = CreateArtifact(glm::vec2(-245.0f, -132.0f), "Artifact1", 1500);
    artifact = CreateArtifact(glm::vec2(-172.0f, -130.0f), "Artifact2", 2500);
    artifact = CreateArtifact(glm::vec2(-163.0f, -40.0f), "Artifact3", 3500);
    artifact = CreateArtifact(glm::vec2(-228.0f, 25.0f), "Artifact4", 4500);
    artifact = CreateArtifact(glm::vec2(-360.0f, 4.0f), "Artifact5", 5500);
    artifact = CreateArtifact(glm::vec2(-308.0f, 100.0f), "Artifact6", 6500);
    artifact = CreateArtifact(glm::vec2(-245.0f, 180.0f), "Artifact7", 7500);
    artifact = CreateArtifact(glm::vec2(52.0f, 82.0f), "Artifact8", 8750);
    artifact = CreateArtifact(glm::vec2(-14.0f, 120.0f), "Artifact9", 9750);
    artifact = CreateArtifact(glm::vec2(-137.0f, 67.0f), "Artifact10", 10000);
    artifact = CreateArtifact(glm::vec2(-143.0f, 277.0f), "Artifact11", 10000);

    // hard artifacts
    artifact = CreateArtifact(glm::vec2(99.0f, 248.0f), "Artifact12", 10000);
    artifact = CreateArtifact(glm::vec2(253.0f, 50.0f), "Artifact13", 10000);
    artifact = CreateArtifact(glm::vec2(460.0f, 62.0f), "Artifact14", 10000);
    artifact = CreateArtifact(glm::vec2(320.0f, -76.0f), "Artifact15", 10000);
    artifact = CreateArtifact(glm::vec2(204.0f, -7.0f), "Artifact16", 10000);
    artifact = CreateArtifact(glm::vec2(234.0f, -263.0f), "Artifact17", 10000);
}

template <typename T>
Enemy* CreateEnemies(glm::vec2 pos, std::string texture) {
    static int enemyID = 0;
    T* enemy = Game::GetInstance().CreateInstance<T>("Enemy" + std::to_string(enemyID++), "Alien", "Lighting", texture);
    enemy->SetPosition(glm::vec3(pos.x, Game::GetInstance().GetTerrain()->GetHeightAt(pos.x, pos.y) + 1.0f, pos.y));
    Game::GetInstance().GetEnemies().push_back(enemy);
    return enemy;
}

void SetupEnemies() {
    // Shooter enemies
    Enemy* enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-235.0f, 52.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-335.0f, 294.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-366.0f, 287.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-413.0f, 230.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-197.0f, 484.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(193.0f, 538.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(270.0f, 78.0f),   "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(234.0f, 31.0f),   "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(478.0f, 80.0f),   "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(477.0f, 61.0f),   "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(468.0f, 41.0f),   "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(301.0f, -76.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(313.0f, -90.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(313.0f, -59.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(338.0f, -52.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(192.0f, -2.0f),   "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(209.0f, 7.0f),    "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(230.0f, -14.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(182.0f, -12.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(232.0f, -258.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-240.0f, 264.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-314.0f, 78.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-206.0f, -41.0f), "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-16.0f, 84.0f),   "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-124.0f, 26.0f),  "ShooterEnemyTexture");
    enemy = CreateEnemies<ShooterEnemy>(glm::vec2(-127.0f, 77.0f),  "ShooterEnemyTexture");

    // Chaser enemies
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(-249.0f, 192.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(-470.0f, 393.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(-403.0f, 486.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(3.0f, 536.0f),    "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(341.0f, 548.0f),  "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(382.0f, 467.0f),  "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(299.0f, 430.0f),  "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(197.0f, 408.0f),  "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(112.0f, 248.0f),  "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(86.0f, 250.0f),   "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(75.0f, 261.0f),   "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(275.0f, 34.0f),   "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(222.0f, 57.0f),   "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(447.0f, 65.0f),   "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(451.0f, 84.0f),   "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(246.0f, -255.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(245.0f, -276.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(234.0f, -284.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(216.0f, -273.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(212.0f, -249.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(-360.0f, 20.0f),  "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(-233.0f, 186.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(-164.0f, 278.0f), "ChaserEnemyTexture");
    enemy = CreateEnemies<ChaserEnemy>(glm::vec2(-146.0f, 57.0f),  "ChaserEnemyTexture");
}

template <typename T>
Hazard* CreateHazard(glm::vec2 pos, std::string texture) {
    static int hazardID = 0;
    T* hazard = Game::GetInstance().CreateInstance<T>("Hazard" + std::to_string(hazardID++), "Pool", "Lighting", texture);
    hazard->SetPosition(glm::vec3(pos.x, Game::GetInstance().GetTerrain()->GetHeightAt(pos.x, pos.y) - 3.0f, pos.y));
    hazard->SetScale(glm::vec3(15.0f));
    return hazard;
}

void SetupHazards() {
    // mud pools
    Hazard* hazard = CreateHazard<MudPool>(glm::vec2(-200.0f, -128.0f), "MudTexture");
    hazard = CreateHazard<MudPool>(glm::vec2(-302.0f, -26.0f), "MudTexture");
    hazard = CreateHazard<MudPool>(glm::vec2(-260.0f, 169.0f), "MudTexture");
    hazard = CreateHazard<MudPool>(glm::vec2(142.0f, 186.0f), "MudTexture");
    hazard = CreateHazard<MudPool>(glm::vec2(248.0f, 71.0f), "MudTexture");
    hazard = CreateHazard<MudPool>(glm::vec2(440.0f, 44.0f), "MudTexture");
    hazard = CreateHazard<MudPool>(glm::vec2(333.0f, -33.0f), "MudTexture");
    hazard = CreateHazard<MudPool>(glm::vec2(260.0f, -239.0f), "MudTexture");

    // acid pools
    hazard = CreateHazard<AcidPool>(glm::vec2(-235.0f, 1.5f), "AcidTexture");
    hazard = CreateHazard<AcidPool>(glm::vec2(-160.0f, 231.0f), "AcidTexture");
    hazard = CreateHazard<AcidPool>(glm::vec2(-2.5f, 117.0f), "AcidTexture");
    hazard = CreateHazard<AcidPool>(glm::vec2(91.0f, 227.0f), "AcidTexture");
    hazard = CreateHazard<AcidPool>(glm::vec2(364.0f, 76.0f), "AcidTexture");
    hazard = CreateHazard<AcidPool>(glm::vec2(240.0f, -219.0f), "AcidTexture");
    hazard = CreateHazard<AcidPool>(glm::vec2(337.0f, -75.0f), "AcidTexture");

    // geysers
    hazard = CreateHazard<Geyser>(glm::vec2(-275.0f, 67.0f), "GeyserTexture");
    hazard = CreateHazard<Geyser>(glm::vec2(-191.0f, 108.0f), "GeyserTexture");
    hazard = CreateHazard<Geyser>(glm::vec2(2.0f, 69.0f), "GeyserTexture");
    hazard = CreateHazard<Geyser>(glm::vec2(247.0f, 125.0f), "GeyserTexture");
    hazard = CreateHazard<Geyser>(glm::vec2(218.0f, -70.0f), "GeyserTexture");
}


} // namespace game
