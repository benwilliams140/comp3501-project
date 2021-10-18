#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer/vao.h"
#include "Renderer/ebo.h"

namespace game {

    // Possible resource types
    typedef enum Type { Material, PointSet, Mesh, Texture } ResourceType;

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
                    util::Vao* array_buffer_; // Buffers for geometry
                    util::Ebo* element_array_buffer_;
                };
            };
            GLsizei size_; // Number of primitives in geometry

        public:
            Resource(ResourceType type, std::string name, GLuint resource, GLsizei size);
            Resource(ResourceType type, std::string name, util::Vao* array_buffer, util::Ebo* element_array_buffer, GLsizei size);
            ~Resource();
            ResourceType GetType(void) const;
            const std::string GetName(void) const;
            GLuint GetResource(void) const;
            util::Vao* GetArrayBuffer(void) const;
            util::Ebo* GetElementArrayBuffer(void) const;
            GLsizei GetSize(void) const;

    }; // class Resource

} // namespace game

#endif // RESOURCE_H_
