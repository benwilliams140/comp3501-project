#include "Control/game.h"

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Main window settings
const std::string window_title_g = "Demo";
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

    // Load shaders
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/simple_texture");
    resman_.LoadResource(ResourceType::Material, "Simple", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/lit");
    resman_.LoadResource(ResourceType::Material, "Lighting", filename.c_str());

    // Load texture
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/rocky.png");
    resman_.LoadResource(ResourceType::Texture, "RockyTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/uv6.png");
    resman_.LoadResource(ResourceType::Texture, "uv6", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/track_texture.png");
    resman_.LoadResource(ResourceType::Texture, "TrackTexture", filename.c_str());
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
    HoverTank* hovertank_base = CreateInstance<HoverTank>(HOVERTANK_BASE, HOVERTANK_BASE, hovertankMaterial, "uv6");
    player_ = new Player(100.f, 100.f, hovertank_base);
    player_->AddMoney(100000); // for demo purposes
    HoverTankTurret* hovertank_turret = CreateInstance<HoverTankTurret>(HOVERTANK_TURRET, HOVERTANK_TURRET, hovertankMaterial, "uv6");
    hovertank_turret->Translate(glm::vec3(0.f, 1.055f, -0.4f));
    hovertank_turret->SetParent(hovertank_base);
    hovertank_turret->SetForward(hovertank_base->GetForward());
    hovertank_base->SetTurret(hovertank_turret);

    // create hovertank tracks
    std::string trackLocations[] = { "Rear", "Rear", "Front", "Front" };
    std::vector<HoverTankTrack*> hovertank_tracks;
    for (int i = 0; i < 4; ++i) {
        hovertank_tracks.push_back(CreateInstance<HoverTankTrack>("HovertankTrack" + trackLocations[i], "HovertankTrack" + trackLocations[i], hovertankMaterial, "TrackTexture"));
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

    // Initialize certain scene nodes
    terrain_->Init();
}

void Game::MainLoop(void){
    // Loop while the user did not close the window
    while (!glfwWindowShouldClose(window_)){
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
            Time::Update();

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

bool Game::GetFreeroam() const {
    return freeroam_;
}

std::vector<Artifact*>& Game::GetArtifacts() {
    return artifacts_;
}

} // namespace game
