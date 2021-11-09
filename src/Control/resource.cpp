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

    Resource::Resource(ResourceType type, std::string name, util::Vao* vao, util::Ebo* ebo, GLsizei size, TerrainData* terrainData) {
        type_ = type;
        name_ = name;
        vao_ = vao;
        ebo_ = ebo;
        size_ = size;
        terrainData_ = terrainData;
    }

    Resource::~Resource() {
        if (type_ == ResourceType::Mesh) {
            delete vao_;
            delete ebo_;
        } else if (type_ == ResourceType::Terrain) {
            delete vao_;
            delete ebo_;
            delete terrainData_;
        }
    }

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

    TerrainData* Resource::GetTerrainData(void) const {
        return terrainData_;
    }

} // namespace game