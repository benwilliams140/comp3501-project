#ifndef SCENE_GRAPH_H_
#define SCENE_GRAPH_H_

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Control/scene_node.h"
#include "Objects/Hovertank/hovertank.h"
#include "Objects/Hovertank/hovertank_track.h"
#include "Objects/Hovertank/hovertank_turret.h"
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
            // templated to add classes that extend from SceneNode (definitions are in cpp file)
            template <typename T>
            T* CreateNode(std::string node_name, Resource *geometry, Resource *material, Resource *texture = NULL);
            // Add an already-created node
            void AddNode(SceneNode *node);
            // Find a scene node with a specific name
            SceneNode *GetNode(std::string node_name) const;
            // Get node const iterator
            std::vector<SceneNode *>::const_iterator begin() const;
            std::vector<SceneNode *>::const_iterator end() const;

            // Draw the entire scene
            void Draw(Camera *camera);

            // Update entire scene
            void Update(void);

    }; // class SceneGraph

} // namespace game

#endif // SCENE_GRAPH_H_
