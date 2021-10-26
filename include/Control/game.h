#ifndef GAME_H_
#define GAME_H_

#include <exception>
#include <string>
#include <unordered_map>
#include <iostream>
#include <time.h>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Control/input.h"
#include "Control/scene_graph.h"
#include "Control/resource_manager.h"
#include "Control/GUI/menu.h"
#include "Control/GUI/Menus/main_menu.h"
#include "Control/GUI/Menus/pause_menu.h"
#include "Control/path_config.h"

#include "Renderer/camera.h"

#include "Objects/Hovertank/hovertank.h"
#include "Objects/Hovertank/hovertank_track.h"
#include "Objects/Hovertank/hovertank_turret.h"
#include "Objects/Hovertank/machine_gun.h"
#include "Objects/Hovertank/scanner.h"
#include "Objects/terrain.h"

namespace game {

    // Exception type for the game
    class GameException: public std::exception
    {
        private:
            std::string message_;
        public:
            GameException(std::string message) : message_(message) {};
            virtual const char* what() const throw() { return message_.c_str(); };
            virtual ~GameException() throw() {};
    };

    enum class State {
        PAUSED,
        RUNNING,
        STOPPED
    };

    // Game application
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();
            // Call Init() before calling any other method
            void Init(void); 
            // Set up resources for the game
            void SetupResources(void);
            // Set up initial scene
            void SetupScene(void);
            // Run the game: keep the application active
            void MainLoop(void); 

        private:
            // GLFW window
            GLFWwindow* window_;

            // Menus/GUI components
            std::unordered_map<MenuType, Menu*> menus_;

            // Scene graph containing all nodes to render
            SceneGraph scene_;

            // Resources available to the game
            ResourceManager resman_;

            // Camera abstraction
            Camera camera_;

            // Flag to turn animation on/off
            bool animating_;
            State state_;

            // Methods to initialize the game
            void InitWindow(void);
            void InitView(void);
            void InitEventHandlers(void);
            void InitMenus();
 
            // Methods to handle events
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            // Create an instance of an object stored in the resource manager
            SceneNode *CreateInstance(std::string entity_name, std::string object_name, std::string material_name, std::string texture_name = std::string(""));


    }; // class Game

} // namespace game

#endif // GAME_H_
