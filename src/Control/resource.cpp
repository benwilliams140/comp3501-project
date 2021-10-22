#include <exception>

#include "Control/resource.h"

namespace game {

    Resource::Resource(ResourceType type, std::string name, GLuint resource, GLsizei size) {
        type_ = type;
        name_ = name;
        resource_ = resource;
        size_ = size;
    }

    Resource::Resource(ResourceType type, std::string name, util::Vao* vao, util::Ebo* ebo, GLsizei size) {
        type_ = type;
        name_ = name;
        vao_ = vao;
        ebo_ = ebo;
        size_ = size;
    }

    Resource::Resource(ResourceType type, std::string name, util::Vao* vao, util::Ebo* ebo, GLsizei size, int width, int length, glm::vec3 scale, float* heightMatrix) {
        type_ = type;
        name_ = name;
        vao_ = vao;
        ebo_ = ebo;
        size_ = size;
        width_ = width;
        length_ = length;
        scale_ = scale;
        heightMatrix_ = heightMatrix;
    }

    Resource::~Resource() {}

    ResourceType Resource::GetType(void) const {
        return type_;
    }

    const std::string Resource::GetName(void) const {
        return name_;
    }

    GLuint Resource::GetResource(void) const {
        return resource_;
    }

    util::Vao* Resource::GetVAO(void) const {
        return vao_;
    }

    util::Ebo* Resource::GetEBO(void) const {
        return ebo_;
    }

    GLsizei Resource::GetSize(void) const {
        return size_;
    }

    int Resource::GetWidth(void) const {
        return width_;
    }

    int Resource::GetLength(void) const {
        return length_;
    }

    glm::vec3 Resource::GetScale(void) const {
        return scale_;
    }

    float* Resource::GetHeightMatrix(void) const {
        return heightMatrix_;
    }

} // namespace game