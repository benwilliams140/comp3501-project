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

// generic CreateNode function
template <typename T>
T* SceneGraph::CreateNode(std::string node_name, Resource *geometry, Resource *material, Resource *texture){

    // Create scene node with the specified resources
    T* scn = new T(node_name, geometry, material, texture);

    // Add node to the scene
    AddNode(scn);

    return scn;
}

// definitions for generic function
// NOTE: Add more explicit function definitions here (eg. for terrain, other hovertank parts)
template SceneNode* SceneGraph::CreateNode<SceneNode>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);
template SceneNode* SceneGraph::CreateNode<Terrain>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);
template HoverTank* SceneGraph::CreateNode<HoverTank>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);
template HoverTankTrack* SceneGraph::CreateNode<HoverTankTrack>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);
template HoverTankTurret* SceneGraph::CreateNode<HoverTankTurret>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);
template MachineGun* SceneGraph::CreateNode<MachineGun>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);
template EnergyCannon* SceneGraph::CreateNode<EnergyCannon>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);
template Artifact* SceneGraph::CreateNode<Artifact>(std::string node_name, Resource* geometry, Resource* material, Resource* texture);

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


std::vector<SceneNode *>::const_iterator SceneGraph::begin() const {

    return node_.begin();
}


std::vector<SceneNode *>::const_iterator SceneGraph::end() const {

    return node_.end();
}


void SceneGraph::Draw(Camera *camera) {

    // Draw all scene nodes
    for (int i = 0; i < node_.size(); i++){
        node_[i]->Draw(camera);
    }
}


void SceneGraph::Update(){

    for (int i = 0; i < node_.size(); i++){
        node_[i]->Update();
        
    }
}

} // namespace game
