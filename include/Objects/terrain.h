#pragma once

#include <string>
#include "Control/scene_node.h"

namespace game {
    class Terrain : public SceneNode {
    public:
        // Create terrain from given resources
        Terrain(const std::string name, const Resource* geometry, const Resource* material);

        // Destructor
        ~Terrain();

        // Get/set attributes specific to terrain
        // TODO - add terrain collider

        // Update geometry configuration
        void Update(void);

    private:
        float GetHeightAt(float x, float z);
    };
}