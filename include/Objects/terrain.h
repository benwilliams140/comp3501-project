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

        // Approximation of the height of the terrain at a specified point
        // Use collision function to get a precise height instead
        float GetHeightAt(float x, float z);
        Math::Normal GetNormalAt(float x, float z);

        float GetWidth(void) const;
        float GetLength(void) const;

    private:
        virtual void InitShaderUniform(GLuint program);
        virtual void UpdateShaderUniform(GLuint program);

        float GetVertexHeightAt(int x, int z);
        Math::Point3 GetPointAt(int x, int z);
        Math::Normal GetVertexNormalAt(int x, int z);
        bool CanHit(Math::Point3 A, Math::Point3 B, Math::Point3 p0, Math::Point3 p1, Math::Point3 p2, float& t, Math::Point3& hitPoint);
    };
}