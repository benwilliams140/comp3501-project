#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer/vao.h"
#include "Renderer/ebo.h"

namespace game {

    // Possible resource types
    enum class ResourceType { Material, PointSet, Mesh, Texture, Terrain };

    // Class that holds one resource
    class Resource {

    private:
        ResourceType type_; // Type of resource
        std::string name_; // Reference name
        union {
            struct {
                GLuint resource_; // OpenGL handle for resource
            };
            struct {
                util::Vao* vao_; // Buffers for geometry
                util::Ebo* ebo_;
            };
            struct {
                util::Vao* vao_; // Buffers for geometry
                util::Ebo* ebo_;
                int width_, length_; // Width equals amount of edges (amount of vertices + 1) in the x-axis, Length equals amount of edges (amount of vertices + 1) in the z-axis.
                glm::vec3 scale_; // The terrain's initial scaling
                float* heightMatrix_; // Matrix which holds height information per vertex
            };
        };
        GLsizei size_; // Number of primitives in geometry

    public:
        Resource(ResourceType type, std::string name, GLuint resource, GLsizei size);
        Resource(ResourceType type, std::string name, util::Vao* vao, util::Ebo* ebo, GLsizei size);
        Resource(ResourceType type, std::string name, util::Vao* vao, util::Ebo* ebo, GLsizei size, int width, int length, glm::vec3 scale, float* heightMatrix);
        ~Resource();
        ResourceType GetType(void) const;
        const std::string GetName(void) const;
        GLuint GetResource(void) const;
        util::Vao* GetVAO(void) const;
        util::Ebo* GetEBO(void) const;
        GLsizei GetSize(void) const;
        int GetWidth(void) const;
        int GetLength(void) const;
        glm::vec3 GetScale(void) const;
        float* GetHeightMatrix(void) const;

    }; // class Resource

} // namespace game

#endif // RESOURCE_H_