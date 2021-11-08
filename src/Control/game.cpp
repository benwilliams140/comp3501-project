#include "Control/game.h"

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Main window settings
const std::string window_title_g = "Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const bool window_full_screen_g = false;



// Viewport and camera settings
glm::vec3 camera_position_g(0.5, 0.5, 10.0);
glm::vec3 camera_look_at_g(0.0, 0.0, 0.0);
glm::vec3 camera_up_g(0.0, 1.0, 0.0);
const glm::vec3 viewport_background_color_g(0.1, 0.1, 0.1);


// Materials 
const std::string material_directory_g = MATERIAL_DIRECTORY;

// Forward function declarations
void UpdateCameraMovement(Camera*);

Game::Game(void){
    // do nothing
}

void Game::Init(void){
    // Run all initialization steps
    InitWindow();
    InitView();
    InitEventHandlers();
    InitMenus();

    // Set variables
    state_ = State::STOPPED;
    freeroam_ = false;
}
       
void Game::InitWindow(void){
    // Initialize the window management library (GLFW)
    if (!glfwInit()){
        throw(GameException(std::string("Could not initialize the GLFW library")));
    }

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
    //resman_.CreateTorus("SimpleTorusMesh", 0.8, 0.35, 30, 30);
    //resman_.CreateSeamlessTorus("SeamlessTorusMesh", 0.8, 0.35, 80, 80);
    //resman_.CreateCylinder("SimpleCylinderMesh", 2.0, 0.4, 30, 30);

    // Load terrain
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/terrain_height_map.png");
    resman_.LoadResource(ResourceType::Terrain, "Terrain", filename.c_str(), glm::vec3(5.0f, 1.0f, 5.0f));

    // Load geometry
    filename = std::string(MESH_DIRECTORY) + std::string("/cube.mesh");
    resman_.LoadResource(ResourceType::Mesh, "Cube", filename.c_str());

    // Load shaders
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/textured_material");
    resman_.LoadResource(ResourceType::Material, "TextureShader", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/corona");
    resman_.LoadResource(ResourceType::Material, "Procedural", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/simple_texture");
    resman_.LoadResource(ResourceType::Material, "Simple", filename.c_str());
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/lit");
    resman_.LoadResource(ResourceType::Material, "Lighting", filename.c_str());

    // Load texture
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/rocky.png");
    resman_.LoadResource(ResourceType::Texture, "RockyTexture", filename.c_str());
    filename = std::string(TEXTURE_DIRECTORY) + std::string("/uv6.png");
    resman_.LoadResource(ResourceType::Texture, "uv6", filename.c_str());
}

void Game::SetupScene(void) {
    // Set background color for the scene
    scene_.SetBackgroundColor(viewport_background_color_g);

    // Create an object for showing the texture
    // instance contains identifier, geometry, shader, and texture
    //game::SceneNode *mytorus = CreateInstance("MyTorus1", "SimpleTorusMesh", "TextureShader", "RockyTexture");
    //game::SceneNode *mytorus = CreateInstance("MyTorus1", "SimpleTorusMesh", "Procedural", "RockyTexture");
    //game::SceneNode *mytorus = CreateInstance("MyTorus1", "SeamlessTorusMesh", "Lighting", "RockyTexture");

    SceneNode* terrain = CreateInstance<Terrain>("Terrain Object", "Terrain", "Simple", "uv6");
    terrain->Translate(glm::vec3(-50.f));
    terrain_ = (Terrain*)terrain;

    SceneNode* hovertank_base = CreateInstance<HoverTank>("Hovertank Base", "Cube", "Simple", "RockyTexture");
    hovertank_base->Translate(glm::vec3(0.f, 0.f, -0.f));
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
            default: break;
            }
        }

        // toggle freeroam if 'F' key clicked
        // developer feature - should probably be removed before submission
        if (Input::getKeyDown(INPUT_KEY_F)) {
            freeroam_ = !freeroam_;
        }

        // render main menu when game is stopped
        if (state_ == State::STOPPED) {
            menus_[MenuType::MAIN]->Render(window_);
        }
        // render pause menu and frozen game state in the background when paused
        else if (state_ == State::PAUSED) {
            scene_.Draw(camera_);
            menus_[MenuType::PAUSE]->Render(window_);
        }
        // update and render game when running
        else if (state_ == State::RUNNING) {
            // handle camera/tank movement
            if (freeroam_) {
                UpdateCameraMovement(camera_);
            }
            else {
                UpdateCameraPos();
            }

            // Update the scene
            static double last_time = 0;
            double current_time = glfwGetTime();
            if ((current_time - last_time) > 0.01) {
                // Animate the scene
                //scene_.Update();

                last_time = current_time;
            }
            scene_.Update();
            scene_.Draw(camera_);
        }

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);

        Input::update();

        // Update other events like input handling
        glfwPollEvents();
    }
}

void Game::UpdateCameraPos() {
    HoverTank* tank = (HoverTank*)scene_.GetNode("Hovertank Base");
    camera_->SetPosition(tank->GetPosition() - tank->GetForward() * 15.f + tank->GetUp() * 5.f);
    camera_->SetView(camera_->GetPosition(), tank->GetPosition(), tank->GetUp());
}

void UpdateCameraMovement(Camera* camera) {
    float rot_factor(glm::pi<float>() / 180);
    float trans_factor = 1.0;
    
    // Translate forward/backward
    if (Input::getKey(INPUT_KEY_W)){
        camera->Translate(camera->GetForward()*trans_factor);
    }
    if (Input::getKey(INPUT_KEY_S)){
        camera->Translate(-camera->GetForward()*trans_factor);
    }
    // Translate left/right
    if (Input::getKey(INPUT_KEY_A)){
        camera->Translate(-camera->GetSide()*trans_factor);
    }
    if (Input::getKey(INPUT_KEY_D)){
        camera->Translate(camera->GetSide()*trans_factor);
    }
    // Translate up/down
    if (Input::getKey(INPUT_KEY_Q)){
        camera->Translate(camera->GetUp()*trans_factor);
    }
    if (Input::getKey(INPUT_KEY_E)){
        camera->Translate(-camera->GetUp()*trans_factor);
    }
    // Rotate pitch
    if (Input::getKey(INPUT_KEY_UP)){
        camera->Pitch(rot_factor);
    }
    if (Input::getKey(INPUT_KEY_DOWN)){
        camera->Pitch(-rot_factor);
    }
    // Rotate yaw
    if (Input::getKey(INPUT_KEY_LEFT)){
        camera->Yaw(rot_factor);
    }
    if (Input::getKey(INPUT_KEY_RIGHT)){
        camera->Yaw(-rot_factor);
    }
    // Rotate roll
    if (Input::getKey(INPUT_KEY_COMMA)){
        camera->Roll(-rot_factor);
    }
    if (Input::getKey(INPUT_KEY_PERIOD)){
        camera->Roll(rot_factor);
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

Camera* Game::GetCamera() {
    return camera_;
}

Terrain* Game::GetTerrain() {
    return terrain_;
}

void Game::SetState(State state) {
    state_ = state;
}

} // namespace game
