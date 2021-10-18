#include <exception>

#include "Control/resource.h"

namespace game {

Resource::Resource(ResourceType type, std::string name, GLuint resource, GLsizei size){
    type_ = type;
    name_ = name;
    resource_ = resource;
    size_ = size;
}

Resource::Resource(ResourceType type, std::string name, util::Vao* array_buffer, util::Ebo* element_array_buffer, GLsizei size){
    type_ = type;
    name_ = name;
    array_buffer_ = array_buffer;
    element_array_buffer_ = element_array_buffer;
    size_ = size;
}

Resource::~Resource(){}

ResourceType Resource::GetType(void) const {
    return type_;
}

const std::string Resource::GetName(void) const {
    return name_;
}

GLuint Resource::GetResource(void) const {
    return resource_;
}

util::Vao* Resource::GetArrayBuffer(void) const {
    return array_buffer_;
}

util::Ebo* Resource::GetElementArrayBuffer(void) const {
    return element_array_buffer_;
}

GLsizei Resource::GetSize(void) const {
    return size_;
}

} // namespace game
