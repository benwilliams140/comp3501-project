#include <stdexcept>
#include <iostream>
#include <fstream>
#include <iterator>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Control/scene_graph.h"
#include "Control/game.h"

namespace game {

SceneGraph::SceneGraph(void){

    background_color_ = glm::vec3(0.0, 0.0, 0.0);
}


SceneGraph::~SceneGraph(){
}


void SceneGraph::SetBackgroundColor(glm::vec3 color){

    background_color_ = color;
}

void SceneGraph::SetBloodEffectTexture(GLuint texture) {
    bloodTexture_ = texture;
}

glm::vec3 SceneGraph::GetBackgroundColor(void) const {

    return background_color_;
}

void SceneGraph::AddNode(SceneNode *node){
    node_.push_back(node);
}

SceneNode *SceneGraph::GetNode(std::string node_name) const {

    // Find node with the specified name
    for (int i = 0; i < node_.size(); i++){
        if (node_[i]->GetName() == node_name){
            return node_[i];
        }
    }
    return NULL;

}

void SceneGraph::RemoveNode(std::string node_name) {
    //deletes the specified node
    for (int i = 0; i < node_.size(); i++) {
        if (node_[i]->GetName() == node_name) {
            SceneNode* node = node_[i];
            node_.erase(begin() + i);
            delete node;
            return;
        }
    } 
}

void SceneGraph::RemoveNode(SceneNode* node) {
    // finds and deletes the specified node
    auto itr = std::find(node_.begin(), node_.end(), node);
    if((*itr) == node) node_.erase(itr);
}


std::vector<SceneNode *>::const_iterator SceneGraph::begin() const {

    return node_.begin();
}


std::vector<SceneNode *>::const_iterator SceneGraph::end() const {

    return node_.end();
}


void SceneGraph::Draw(Camera *camera) {
    struct BlendNode { 
        SceneNode* node; 
        float distance; 
    };
    std::vector<BlendNode> blendNodes;
    
    // Draw all scene nodes
    for (int i = 0; i < node_.size(); i++){
        if (node_[i]->GetActive()) {
            if (node_[i]->IsAlphaBlended()) {
                // Find distance between node and camera
                float distance = glm::distance(node_[i]->GetPosition(), camera->GetPosition());
                
                if (blendNodes.size() == 0) {
                    // Add node to the begining of vector if it is empty
                    blendNodes.push_back({node_[i], distance});
                } else {
                    // Add node to blendNodes in the correct location sorted by distance to camera
                    for (auto itr = blendNodes.begin(); itr != blendNodes.end(); itr++) {
                        // Compare distances and insert if the next distance is larger
                        if (distance < (*itr).distance) {
                            blendNodes.insert(itr, {node_[i], distance}); 
                            break;
                        } else if (std::next(itr) == blendNodes.end()) {
                            blendNodes.push_back({node_[i], distance}); 
                            break;
                        }
                    }
                }
            } else {
                // Draw non-blended nodes per usual
                node_[i]->Draw(camera);
            }
        }
    }
    for (auto itr = blendNodes.rbegin(); itr != blendNodes.rend(); itr++) {
        (*itr).node->Draw(camera);
    }
}


void SceneGraph::Update(){
    // Update all scene nodes
    for (int i = 0; i < node_.size(); i++){
        if(node_[i]->GetActive()) node_[i]->Update();
    }
}

void SceneGraph::SetupDrawToTexture(void){

    // Set up frame buffer
    glGenFramebuffers(1, &frame_buffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);

    // Set up target texture for rendering
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Set up an image for the texture
    GLint windowWidth = Game::GetInstance().GetWindowWidth();
    GLint windowHeight = Game::GetInstance().GetWindowHeight();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set up a depth buffer for rendering
    glGenRenderbuffers(1, &depth_buffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);

    // Configure frame buffer (attach rendering buffers)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    // Check if frame buffer was setup successfully 
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        throw(std::ios_base::failure(std::string("Error setting up frame buffer")));
    }

    // Reset frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Set up quad for drawing to the screen
    static const GLfloat quad_vertex_data[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    };

    // Create buffer for quad
    glGenBuffers(1, &quad_array_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, quad_array_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_data), quad_vertex_data, GL_STATIC_DRAW);
}


void SceneGraph::DrawToTexture(Camera *camera){

    // Save current viewport
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Enable frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
    
    GLint windowWidth = Game::GetInstance().GetWindowWidth();
    GLint windowHeight = Game::GetInstance().GetWindowHeight();
    glViewport(0, 0, windowWidth, windowHeight); 

    // Clear background
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw all scene nodes
    Draw(camera);

    // Reset frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Restore viewport
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}


void SceneGraph::DisplayTexture(GLuint program){

    // Configure output to the screen
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);

    // Unbind any VAOs
    glBindVertexArray(0);

    // Set up quad geometry
    glBindBuffer(GL_ARRAY_BUFFER, quad_array_buffer_);

    // Select proper material (shader program)
    glUseProgram(program);

    // Setup attributes of screen-space shader
    GLint pos_att = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(pos_att);
    glVertexAttribPointer(pos_att, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint tex_att = glGetAttribLocation(program, "uv");
    glEnableVertexAttribArray(tex_att);
    glVertexAttribPointer(tex_att, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3*sizeof(GLfloat)));

    // Timer
    GLint timer_var = glGetUniformLocation(program, "timer");
    float current_time = glfwGetTime();
    glUniform1f(timer_var, current_time);

    // Bind scene texture
    GLint tex1 = glGetUniformLocation(program, "texture_map");
    glUniform1i(tex1, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Bind blood effect texture
    GLint tex2 = glGetUniformLocation(program, "blood_texture_map");
    glUniform1i(tex2, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bloodTexture_);

    GLint stun_start_time_var = glGetUniformLocation(program, "stun_start_time");
    glUniform1f(stun_start_time_var, Game::GetInstance().GetPlayer()->GetStunnedStartTime());

    GLint stun_max_time_var = glGetUniformLocation(program, "stun_max_time");
    glUniform1f(stun_max_time_var, Game::GetInstance().GetPlayer()->GetStunnedMaxTime());

    GLint blood_start_time_var = glGetUniformLocation(program, "blood_start_time");
    glUniform1f(blood_start_time_var, Game::GetInstance().GetPlayer()->GetInjuredStartTime());

    GLint blood_max_time_var = glGetUniformLocation(program, "blood_max_time");
    glUniform1f(blood_max_time_var, Game::GetInstance().GetPlayer()->GetInjuredMaxTime());

    // Draw geometry
    glDrawArrays(GL_TRIANGLES, 0, 6); // Quad: 6 coordinates

    // Reset current geometry
    glEnable(GL_DEPTH_TEST);
}


void SceneGraph::SaveTexture(char *filename){
    GLint windowWidth = Game::GetInstance().GetWindowWidth();
    GLint windowHeight = Game::GetInstance().GetWindowHeight();
    unsigned char* data = new unsigned char[windowWidth*windowHeight*4];

    // Retrieve image data from texture
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
    glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Create file in ppm format
    // Open the file
    std::ofstream f;
    f.open(filename);
    if (f.fail()){
        throw(std::ios_base::failure(std::string("Error opening file ")+std::string(filename)));
    }

    // Write header
    f << "P3" << std::endl;
    f << windowWidth << " " << windowHeight << std::endl;
    f << "255" << std::endl;

    // Write data
    for (int i = 0; i < windowWidth; i++){
        for (int j = 0; j < windowHeight; j++){
            for (int k = 0; k < 3; k++){
                int dt = data[i*windowHeight*4 + j*4 + k];
                f << dt << " ";
            }
        }
        f << std::endl;
    }

    // Close the file
    f.close();

    delete[] data;

    // Reset frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace game
