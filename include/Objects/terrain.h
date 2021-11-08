#pragma once

#include <string>
#include "Control/scene_node.h"
#include "Control/mathematics.h"

namespace game {
    class Terrain : public SceneNode {
    public:
        // Create terrain from given resources
        Terrain(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture);

        // Destructor
        ~Terrain();

        // Update geometry configuration
        void Update(void);

        // Terrain collision detection
        bool Collision(Math::Point3 P, float d, Math::Point3& hitpoint);

    private:
        SceneNode *p0_node, *p1_node, *p2_node, *p3_node;

        float Terrain::GetHeightAt(int x, int z);
        Math::Point3 GetPointAt(int x, int z);
        bool CanHit(Math::Point3 A, Math::Point3 B, Math::Point3 p0, Math::Point3 p1, Math::Point3 p2, float& t, Math::Point3& hitPoint);
    };
}