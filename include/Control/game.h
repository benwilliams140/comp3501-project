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
#include "Control/GUI/Menus/hud.h"
#include "Control/GUI/Menus/upgrades.h"
#include "Control/path_config.h"
#include "Control/time.h"

#include "Renderer/camera.h"

#include "Objects/Hovertank/hovertank.h"
#include "Objects/Hovertank/hovertank_track.h"
#include "Objects/Hovertank/hovertank_turret.h"
#include "Objects/Hovertank/Abilities/machine_gun.h"
#include "Objects/Hovertank/Abilities/energy_cannon.h"
#include "Objects/Hovertank/scanner.h"
#include "Objects/terrain.h"
#include "Objects/Artifact.h"
#include "Objects/Player.h"
#include "Objects/EnergySource.h"
#include "Objects/EnvironmentObject.h"
#include "Objects/Rock.h"
#include "Objects/Tree.h"
#include "Objects/Projectiles/linear_projectile.h"
#include "Objects/Projectiles/parabolic_projectile.h"

// object/resource names
#define HOVERTANK_BASE "HovertankChassis"
#define HOVERTANK_TURRET "HovertankCylinder"
#define HOVERTANK_SCANNER "HovertankScanner"
#define HOVERTANK_SCANNER_CONE "HovertankScannerCone"
#define HOVERTANK_MACHINE_GUN "HovertankMachineGun"
#define HOVERTANK_TRACK_REAR "HovertankTrackRear"
#define HOVERTANK_TRACK_FRONT "HovertankTrackFront"

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
        STOPPED,
        UPGRADES
    };

    // Game application
    class Game {
        public:
            // Create singleton instance
            static Game& GetInstance() {
                static Game instance;
                return instance;
            }

        public:
            // Call Init() before calling any other method
            void Init(void); 
            // Set up resources for the game
            void SetupResources(void);
            // Set up initial scene
            void SetupScene(void);
            // Run the game: keep the application active
            void MainLoop(void); 

            // Create an instance of an object stored in the resource manager
            template <typename T>
            T* CreateInstance(std::string entity_name, std::string object_name, std::string material_name, std::string texture_name = std::string("")) {
                Resource* geom = GetResource(object_name);
                Resource* mat = GetResource(material_name);
                Resource* tex = nullptr;
                if (texture_name != "") {
                    tex = GetResource(texture_name);
                }
                return scene_.CreateNode<T>(entity_name, geom, mat, tex);
            }

            // Getters/Setters
            Camera* GetCamera();
            GLFWwindow* GetWindow();
            Player* GetPlayer();
            Terrain* GetTerrain();
            std::vector<Artifact*>& GetArtifacts();
            void SetState(State state);
            bool GetFreeroam() const;

            // Delete these function to be sure they don't accidentlly create copies of the instance
            Game(Game const&) = delete;
            void operator=(Game const&) = delete;           

        private:
            // Constructor and destructor
            Game(void);
            ~Game();

            // GLFW window
            GLFWwindow* window_;

            // Menus/GUI components
            std::unordered_map<MenuType, Menu*> menus_;

            // Scene graph containing all nodes to render
            SceneGraph scene_;

            // Resources available to the game
            ResourceManager resman_;

            // Game objects
            Camera* camera_;
            Terrain* terrain_;
            std::vector<Artifact*> artifacts_;

            // Player
            Player* player_;

            bool freeroam_;
            State state_;

            // Methods to initialize the game
            void InitWindow(void);
            void InitView(void);
            void InitEventHandlers(void);
            void InitMenus();
 
            // Methods to handle events
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            Resource* GetResource(std::string res); // get the resource listed
    }; // class Game
} // namespace game

#endif // GAME_H_
