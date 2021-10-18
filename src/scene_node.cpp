#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

#include "scene_node.h"

namespace game {

SceneNode::SceneNode(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture) {
    // Set name of scene node
    name_ = name;

    // Set geometry
    if (geometry->GetType() == PointSet){
        mode_ = GL_POINTS;
    } else if (geometry->GetType() == Mesh){
        mode_ = GL_TRIANGLE_STRIP;
    } else {
        throw(std::invalid_argument(std::string("Invalid type of geometry")));
    }

    array_buffer_ = geometry->GetArrayBuffer();
    element_array_buffer_ = geometry->GetElementArrayBuffer();
    size_ = geometry->GetSize();

    // Set material (shader program)
    if (material->GetType() != Material){
        throw(std::invalid_argument(std::string("Invalid type of material")));
    }

    material_ = material->GetResource();

    // Set texture
    if (texture){
        texture_ = texture->GetResource();
    } else {
        texture_ = 0;
    }

    // Other attributes
    scale_ = glm::vec3(1.0, 1.0, 1.0);
    parent_ = nullptr;
}

SceneNode::~SceneNode(){}

const std::string SceneNode::GetName(void) const {
    return name_;
}

glm::vec3 SceneNode::GetPosition(void) const {
    return position_;
}

glm::quat SceneNode::GetOrientation(void) const {
    return orientation_;
}

glm::vec3 SceneNode::GetScale(void) const {
    return scale_;
}

SceneNode* SceneNode::GetParent(void) const {
    return parent_;
}

void SceneNode::SetPosition(glm::vec3 position){
    position_ = position;
}

void SceneNode::SetOrientation(glm::quat orientation){
    orientation_ = orientation;
}

void SceneNode::SetScale(glm::vec3 scale){
    scale_ = scale;
}

void SceneNode::SetParent(SceneNode* parent) {
    parent_ = parent;
}

void SceneNode::Translate(glm::vec3 trans){
    position_ += trans;
}

void SceneNode::Rotate(glm::quat rot){
    orientation_ *= rot;
    orientation_ = glm::normalize(orientation_);
}

void SceneNode::Scale(glm::vec3 scale){
    scale_ *= scale;
}

GLenum SceneNode::GetMode(void) const {
    return mode_;
}

util::Vao* SceneNode::GetArrayBuffer(void) const {
    return array_buffer_;
}

util::Ebo* SceneNode::GetElementArrayBuffer(void) const {
    return element_array_buffer_;
}

GLsizei SceneNode::GetSize(void) const {
    return size_;
}

GLuint SceneNode::GetMaterial(void) const {
    return material_;
}

glm::mat4 SceneNode::GetWorldTransform(void) const{
    // Calculate world transformation without scale
    glm::mat4 transf = glm::translate(glm::mat4(1.0), position_) * glm::mat4_cast(orientation_);

    // Multiply by parent's transformation
    if (parent_ != nullptr) transf = parent_->GetWorldTransform() * transf;

    // Return transf
    return transf;
}

void SceneNode::Draw(Camera *camera){
    // Select proper material (shader program)
    glUseProgram(material_);

    // Set geometry to draw
    array_buffer_->bind();
    element_array_buffer_->bind();

    // Set globals for camera
    camera->SetupShader(material_);

    // Set world matrix and other shader input variables
    SetupShader(material_);

    // Draw geometry
    if (mode_ == GL_POINTS){
        glDrawArrays(mode_, 0, size_);
    } else {
        glDrawElements(mode_, size_, GL_UNSIGNED_INT, 0);
    }
}

void SceneNode::Update(void){
    // Do nothing for this generic type of scene node
}

void SceneNode::SetupShader(GLuint program){
    // Multiply world transformation with scale
    glm::mat4 scaling = glm::scale(glm::mat4(1.0), scale_);
    glm::mat4 transf = GetWorldTransform() * scaling;

    GLint world_mat = glGetUniformLocation(program, "world_mat");
    glUniformMatrix4fv(world_mat, 1, GL_FALSE, glm::value_ptr(transf));

    // Normal matrix
    glm::mat4 normal_matrix = glm::transpose(glm::inverse(transf));
    GLint normal_mat = glGetUniformLocation(program, "normal_mat");
    glUniformMatrix4fv(normal_mat, 1, GL_FALSE, glm::value_ptr(normal_matrix));

    // Texture
    if (texture_){
        GLint tex = glGetUniformLocation(program, "texture_map");
        glUniform1i(tex, 0); // Assign the first texture to the map
        glActiveTexture(GL_TEXTURE0); 
        glBindTexture(GL_TEXTURE_2D, texture_); // First texture we bind
        // Define texture interpolation
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_REPEAT);

    }

    // Timer
    GLint timer_var = glGetUniformLocation(program, "timer");
    double current_time = glfwGetTime();
    glUniform1f(timer_var, (float) current_time);
}

} // namespace game;
