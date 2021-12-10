#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

#include "Control/scene_node.h"

namespace game {

    SceneNode::SceneNode(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) {
        // Set name of scene node
        name_ = name;

        // Set geometry
        if (geometry->GetType() == ResourceType::PointSet) {
            mode_ = GL_POINTS;
        }
        else if (geometry->GetType() == ResourceType::Mesh) {
            mode_ = GL_TRIANGLE_STRIP;
        }
        else if (geometry->GetType() == ResourceType::Terrain) {
            mode_ = GL_TRIANGLE_STRIP;
        }
        else {
            throw(std::invalid_argument(std::string("Invalid type of geometry")));
        }

        vao_ = geometry->GetVAO();
        ebo_ = geometry->GetEBO();
        size_ = geometry->GetSize();
        geometry_ = geometry;

        // Set material (shader program)
        if (material->GetType() != ResourceType::Material) {
            throw(std::invalid_argument(std::string("Invalid type of material")));
        }

        material_ = material->GetResource();

        // Set texture
        if (texture) {
            texture_ = texture->GetResource();
        }
        else {
            texture_ = 0;
        }

        // Other attributes
        scale_ = glm::vec3(1.0, 1.0, 1.0);
        parent_ = nullptr;
        texOffset_ = glm::mat4(1.0);

        active_ = true;
        instanced_ = false;
        alphaBlend_ = false;
        instanceAmount_ = 1;
    }

    SceneNode::~SceneNode() {}

    std::string SceneNode::GetName(void) const {
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

    glm::quat SceneNode::GetAngM(void) const {
        return angm_;
    }

    void SceneNode::SetAngM(glm::quat angm) {
        angm_ = angm;
    }

    bool SceneNode::GetActive(void) const {
        return active_;
    }

    void SceneNode::SetActive(bool active) {
        active_ = active;
    }

    bool SceneNode::IsAlphaBlended(void) const {
        return alphaBlend_;
    }

    void SceneNode::SetAlphaBlended(bool alphaBlend) {
        alphaBlend_ = alphaBlend;
    }

    void SceneNode::SetPosition(glm::vec3 position) {
        position_ = position;
    }

    void SceneNode::SetOrientation(glm::quat orientation) {
        orientation_ = orientation;
    }

    void SceneNode::SetScale(glm::vec3 scale) {
        scale_ = scale;
    }

    void SceneNode::SetParent(SceneNode* parent) {
        parent_ = parent;
    }

    void SceneNode::SetTexOffset(glm::mat4 offset) {
        texOffset_ = offset;
    }

    void SceneNode::Translate(glm::vec3 trans) {
        position_ += trans;
    }

    void SceneNode::Rotate(glm::quat rot) {
        orientation_ *= rot;
        orientation_ = glm::normalize(orientation_);
    }

    void SceneNode::Scale(glm::vec3 scale) {
        scale_ *= scale;
    }

    GLenum SceneNode::GetMode(void) const {
        return mode_;
    }

    util::Vao* SceneNode::GetVAO(void) const {
        return vao_;
    }

    util::Ebo* SceneNode::GetEBO(void) const {
        return ebo_;
    }

    GLsizei SceneNode::GetSize(void) const {
        return size_;
    }

    GLuint SceneNode::GetMaterial(void) const {
        return material_;
    }

    const Resource* SceneNode::GetGeometry(void) const {
        return geometry_;
    }

    glm::mat4 SceneNode::GetWorldTransform(void) const {
        // Calculate world transformation without scale
        glm::mat4 transf = glm::translate(glm::mat4(1.0), position_) * glm::mat4_cast(orientation_);

        // Multiply by parent's transformation
        if (parent_ != nullptr) transf = parent_->GetWorldTransform() * transf;

        // Return transf
        return transf;
    }

    void SceneNode::Draw(Camera* camera) {
        // Select proper material (shader program)
        glUseProgram(material_);
        
        // Select particle blending or not
        // work in progress
        if (alphaBlend_) {
            // Enable blending
            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
        }
        else {
            glDisable(GL_BLEND);
        }

        // Set geometry to draw
        vao_->bind();
        if (ebo_) ebo_->bind();

        // Set globals for camera
        camera->SetupShader(material_);

        // Set world matrix and other shader input variables
        SetupShader(material_);

        // Draw geometry
        if (mode_ == GL_POINTS) {
            if (instanced_) {
                glDrawArraysInstanced(mode_, 0, size_, instanceAmount_);
            }
            else {
                glDrawArrays(mode_, 0, size_);
            }
        }
        else {
            if(instanced_)
                glDrawElementsInstanced(mode_, size_, GL_UNSIGNED_INT, 0, instanceAmount_);
            else
                glDrawElements(mode_, size_, GL_UNSIGNED_INT, 0);
        }
    }

    void SceneNode::Init() {
        // Init shader uniforms
        glUseProgram(material_);
        this->InitShaderUniform(material_);
    }

    void SceneNode::Update() {
        // Do nothing for this generic type of scene node
    }

    void SceneNode::InitShaderUniform(GLuint program) {}
    void SceneNode::UpdateShaderUniform(GLuint program) {}

    void SceneNode::SetupShader(GLuint program) {
        // Multiply world transformation with scale
        glm::mat4 scaling = glm::scale(glm::mat4(1.0), scale_);
        glm::mat4 transf = GetWorldTransform() * scaling;

        GLint world_mat = glGetUniformLocation(program, "world_mat");
        glUniformMatrix4fv(world_mat, 1, GL_FALSE, glm::value_ptr(transf));

        // Normal matrix
        glm::mat3 normal_matrix = glm::mat3(glm::transpose(glm::inverse(transf)));
        GLint normal_mat = glGetUniformLocation(program, "normal_mat");
        glUniformMatrix3fv(normal_mat, 1, GL_FALSE, glm::value_ptr(normal_matrix));

        // UV transformation matrix
        GLint uv_mat = glGetUniformLocation(program, "uv_mat");
        glUniformMatrix4fv(uv_mat, 1, GL_FALSE, glm::value_ptr(texOffset_));

        // Sunlight direction
        glm::vec3 light_dir = glm::vec3(-0.2f, -1.0f, -0.3f);
        GLint light_var = glGetUniformLocation(program, "light_dir");
        glUniform3f(light_var, light_dir.x, light_dir.y, light_dir.z);

        // Texture
        if (texture_) {
            GLint tex = glGetUniformLocation(program, "texture_map");
            glUniform1i(tex, 0); // Assign the first texture to the map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_); // First texture we bind
            // Define texture interpolation
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        }

        // Timer
        GLint timer_var = glGetUniformLocation(program, "timer");
        double current_time = glfwGetTime();
        glUniform1f(timer_var, (float)current_time);

        // Updates uniforms depending on type of object
        this->UpdateShaderUniform(program);
    }

} // namespace game;