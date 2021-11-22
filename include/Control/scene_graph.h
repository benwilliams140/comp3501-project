#ifndef SCENE_GRAPH_H_
#define SCENE_GRAPH_H_

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Control/scene_node.h"
#include "Objects/Hovertank/hovertank.h"
#include "Objects/terrain.h"
#include "Objects/Hovertank/hovertank_track.h"
#include "Objects/Hovertank/hovertank_turret.h"
#include "Objects/Hovertank/Abilities/machine_gun.h"
#include "Objects/Hovertank/Abilities/energy_cannon.h"
#include "Objects/Projectiles/linear_projectile.h"
#include "Objects/Projectiles/parabolic_projectile.h"
#include "Objects/Artifact.h"
#include "Objects/EnvironmentObject.h"
#include "Control/resource.h"
#include "Renderer/camera.h"

namespace game {

    // Class that manages all the objects in a scene
    class SceneGraph {

        private:
            // Background color
            glm::vec3 background_color_;

            // Scene nodes to render
            std::vector<SceneNode *> node_;

        public:
            // Constructor and destructor
            SceneGraph(void);
            ~SceneGraph();

            // Background color
            void SetBackgroundColor(glm::vec3 color);
            glm::vec3 GetBackgroundColor(void) const;
            
            // Create a scene node from the specified resources
           // generic CreateNode function
            template <typename T>
            T* CreateNode(std::string node_name, Resource* geometry, Resource* material, Resource* texture) {

                // Create scene node with the specified resources
                T* scn = new T(node_name, geometry, material, texture);

                // Add node to the scene
                AddNode(scn);

                return scn;
            }

            template <typename T>
            std::vector<T*> GetSimilarNodes() {
                std::vector<T*> nodes;
                for (auto it = begin(); it != end(); ++it) {
                    if (dynamic_cast<const T*>(*it)) {
                        nodes.push_back((T*) *it);
                    }
                }
                return nodes;
            }

            // Add an already-created node
            void AddNode(SceneNode *node);
            // Find a scene node with a specific name
            SceneNode *GetNode(std::string node_name) const;
            void RemoveNode(std::string node_name);
            // Get node const iterator
            std::vector<SceneNode *>::const_iterator begin() const;
            std::vector<SceneNode *>::const_iterator end() const;

            // Draw the entire scene
            void Draw(Camera *camera);

            // Update entire scene
            void Update();

    }; // class SceneGraph

} // namespace game

#endif // SCENE_GRAPH_H_
