#include <iostream>
#include <time.h>
#include <sstream>

#include "Control/game.h"
#include "Control/path_config.h"

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Main window settings
const std::string window_title_g = "Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const bool window_full_screen_g = false;

// Viewport and camera settings
float camera_near_clip_distance_g = 0.01;
float camera_far_clip_distance_g = 1000.0;
float camera_fov_g = 60.0; // Field-of-view of camera
const glm::vec3 viewport_background_color_g(0.1, 0.1, 0.1);
glm::vec3 camera_position_g(0.5, 0.5, 10.0);
glm::vec3 camera_look_at_g(0.0, 0.0, 0.0);
glm::vec3 camera_up_g(0.0, 1.0, 0.0);

// Materials 
const std::string material_directory_g = MATERIAL_DIRECTORY;

// Forward function declarations
void UpdateCameraMovement(Camera*);

Game::Game(void){
    state_ = State::STOPPED;
}

void Game::Init(void){
    // Run all initialization steps
    InitWindow();
    InitView();
    InitEventHandlers();

    // Set variables
    animating_ = true;
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
    // Set current view
    camera_.SetView(camera_position_g, camera_look_at_g, camera_up_g);
    // Set projection
    camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
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
    resman_.LoadResource(ResourceType::Terrain, "Terrain", filename.c_str(), glm::vec3(1.0f));

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

    game::SceneNode* wall = CreateInstance("Canvas", "Cube", "Simple", "uv6"); // must supply a texture, even if not used	
    wall->Rotate(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0)));
    wall->Translate(glm::vec3(0.0f, 0.0f, -5.0f));

    game::Terrain* terrain = (game::Terrain*)CreateInstance("Terrain Object", "Terrain", "Simple", "uv6");
}

void Game::MainLoop(void){
    // Loop while the user did not close the window
    while (!glfwWindowShouldClose(window_)){
        // Press "Q" key to close application
        if (Input::getKey(INPUT_KEY_ESCAPE)) {
            switch (state_) {
            case State::PAUSED: state_ = State::RUNNING; break;
            case State::RUNNING: state_ = State::PAUSED; break;
            default: break;
            }
        }
        // Press "Space" key to toggle animation
        if (Input::getKey(INPUT_KEY_SPACE)) {
            animating_ = !animating_;
        }
        
        // Updates camera movement
        UpdateCameraMovement(&camera_);

        // Animate the scene
        if (animating_){
            static double last_time = 0;
            double current_time = glfwGetTime();
            if ((current_time - last_time) > 0.01){
                // Animate the scene
                //scene_.Update();

				// make the torus fly away from the camera:
                //SceneNode *node = scene_.GetNode("MyTorus1");
				//node->Translate(glm::vec3(0, 0, -1));

				SceneNode *node = scene_.GetNode("Canvas");

				glm::quat rotation = glm::angleAxis(0.15f*glm::pi<float>()/180.0f, glm::vec3(0.0, 1.0, 0.0));
                node->Rotate(rotation);

                last_time = current_time;
            }
        }

        // Draw the scene
        scene_.Draw(&camera_);

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);

        // Update other events like input handling
        glfwPollEvents();
    }
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
    game->camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
}

Game::~Game(){
    
    glfwTerminate();
}

SceneNode *Game::CreateInstance(std::string entity_name, std::string object_name, std::string material_name, std::string texture_name){
    Resource *geom = resman_.GetResource(object_name);
    if (!geom){
        throw(GameException(std::string("Could not find resource \"")+object_name+std::string("\"")));
    }

    Resource *mat = resman_.GetResource(material_name);
    if (!mat){
        throw(GameException(std::string("Could not find resource \"")+material_name+std::string("\"")));
    }

    Resource *tex = NULL;
    if (texture_name != ""){
        tex = resman_.GetResource(texture_name);
        if (!tex){
            throw(GameException(std::string("Could not find resource \"")+texture_name+std::string("\"")));
        }
    }

    SceneNode *scn = scene_.CreateNode(entity_name, geom, mat, tex);
    return scn;
}

} // namespace game
