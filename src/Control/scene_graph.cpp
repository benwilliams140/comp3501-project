#include <stdexcept>
#include <iostream>
#include <fstream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Control/scene_graph.h"

namespace game {

SceneGraph::SceneGraph(void){

    background_color_ = glm::vec3(0.0, 0.0, 0.0);
}


SceneGraph::~SceneGraph(){
}


void SceneGraph::SetBackgroundColor(glm::vec3 color){

    background_color_ = color;
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
    // Draw all scene nodes
    for (int i = 0; i < node_.size(); i++){
        if(node_[i]->GetActive()) node_[i]->Draw(camera);
    }
}


void SceneGraph::Update(){
    // Update all scene nodes
    for (int i = 0; i < node_.size(); i++){
        if(node_[i]->GetActive()) node_[i]->Update();
    }
}

} // namespace game
