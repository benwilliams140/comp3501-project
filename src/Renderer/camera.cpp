#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Renderer/camera.h"
#include "Control/time.h"
#include "Control/input.h"
#include "Objects/Hovertank/hovertank.h"
#include "Objects/Hovertank/hovertank_turret.h"

namespace game {

Camera::Camera(glm::vec3 position, glm::vec3 lookAtPosition, glm::vec3 up, int windowWidth, int windowHeight) :
    fov_(60.f), nearPlane_(0.01f), farPlane_(1000.f), aspect_(windowWidth / windowHeight) {
    SetProjection(windowWidth, windowHeight);
    SetView(position, lookAtPosition, up);
}


Camera::~Camera(){
}


glm::vec3 Camera::GetPosition(void) const {

    return position_;
}


glm::quat Camera::GetOrientation(void) const {

    return orientation_;
}


void Camera::SetPosition(glm::vec3 position){

    position_ = position;
}


void Camera::SetOrientation(glm::quat orientation){

    orientation_ = orientation;
}

void Camera::SetFOV(float fov, GLfloat w, GLfloat h) {
    fov_ = fov;
    SetProjection(w, h);
}

float Camera::GetFOV() {
    return fov_;
}


void Camera::Translate(glm::vec3 trans){

    position_ += trans;
}


void Camera::Rotate(glm::quat rot){

    orientation_ = rot * orientation_;
    orientation_ = glm::normalize(orientation_);
}


glm::vec3 Camera::GetForward(void) const {

    glm::vec3 current_forward = orientation_ * forward_;
    return -current_forward; // Return -forward since the camera coordinate system points in the opposite direction
}


glm::vec3 Camera::GetSide(void) const {

    glm::vec3 current_side = orientation_ * side_;
    return current_side;
}


glm::vec3 Camera::GetUp(void) const {

    glm::vec3 current_forward = orientation_ * forward_;
    glm::vec3 current_side = orientation_ * side_;
    glm::vec3 current_up = glm::cross(current_forward, current_side);
    current_up = glm::normalize(current_up);
    return current_up;
}


void Camera::Pitch(float angle){

    glm::quat rotation = glm::angleAxis(angle, GetSide());
    orientation_ = rotation * orientation_;
    orientation_ = glm::normalize(orientation_);
}


void Camera::Yaw(float angle){

    glm::quat rotation = glm::angleAxis(angle, GetUp());
    orientation_ = rotation * orientation_;
    orientation_ = glm::normalize(orientation_);
}


void Camera::Roll(float angle){

    glm::quat rotation = glm::angleAxis(angle, GetForward());
    orientation_ = rotation * orientation_;
    orientation_ = glm::normalize(orientation_);
}


void Camera::SetView(glm::vec3 position, glm::vec3 look_at, glm::vec3 up){

    // Store initial forward and side vectors
    // See slide in "Camera control" for details
    forward_ = look_at - position;
    forward_ = -glm::normalize(forward_);
    side_ = glm::cross(up, forward_);
    side_ = glm::normalize(side_);

    // Reset orientation and position of camera
    position_ = position;
    orientation_ = glm::quat();
}


void Camera::SetProjection(GLfloat w, GLfloat h){

    // Set projection based on field-of-view
    float top = tan((fov_/2.0)*(glm::pi<float>()/180.0))*nearPlane_;
    float right = top * w/h;
    projection_matrix_ = glm::frustum(-right, right, -top, top, nearPlane_, farPlane_);
}


void Camera::SetupShader(GLuint program){

    // Update view matrix
    SetupViewMatrix();

    // Set view matrix in shader
    GLint view_mat = glGetUniformLocation(program, "view_mat");
    glUniformMatrix4fv(view_mat, 1, GL_FALSE, glm::value_ptr(view_matrix_));
    
    // Set projection matrix in shader
    GLint projection_mat = glGetUniformLocation(program, "projection_mat");
    glUniformMatrix4fv(projection_mat, 1, GL_FALSE, glm::value_ptr(projection_matrix_));
}


void Camera::SetupViewMatrix(void){

    //view_matrix_ = glm::lookAt(position, look_at, up);

    // Get current vectors of coordinate system
    // [side, up, forward]
    // See slide in "Camera control" for details
    glm::vec3 current_forward = orientation_ * forward_;
    glm::vec3 current_side = orientation_ * side_;
    glm::vec3 current_up = glm::cross(current_forward, current_side);
    current_up = glm::normalize(current_up);

    // Initialize the view matrix as an identity matrix
    view_matrix_ = glm::mat4(1.0); 

    // Copy vectors to matrix
    // Add vectors to rows, not columns of the matrix, so that we get
    // the inverse transformation
    // Note that in glm, the reference for matrix entries is of the form
    // matrix[column][row]
    view_matrix_[0][0] = current_side[0]; // First row
    view_matrix_[1][0] = current_side[1];
    view_matrix_[2][0] = current_side[2];
    view_matrix_[0][1] = current_up[0]; // Second row
    view_matrix_[1][1] = current_up[1];
    view_matrix_[2][1] = current_up[2];
    view_matrix_[0][2] = current_forward[0]; // Third row
    view_matrix_[1][2] = current_forward[1];
    view_matrix_[2][2] = current_forward[2];

    // Create translation to camera position
    glm::mat4 trans = glm::translate(glm::mat4(1.0), -position_);

    // Combine translation and view matrix in proper order
    view_matrix_ *= trans;
}

// Update camera to be in third person view of the tank object
void Camera::UpdateCameraToTarget(HoverTank* tank) {
    HoverTankTurret* turret = tank->GetTurret();
    glm::vec3 pos = glm::vec3(turret->GetWorldTransform() * glm::vec4(turret->GetPosition(), 1));
    glm::vec3 forward = tank->GetOrientation() * turret->GetForward();
    SetPosition(pos - forward * 10.f + tank->GetUp() * 3.0f);
    SetView(GetPosition(), pos, tank->GetUp());
}

// Update camera to be in freeroam
void Camera::UpdateCameraFreeroam() {
    float rot_factor(glm::pi<float>() / 180);
    float trans_factor = 1.0 * Time::GetDeltaTime();
    if (Input::getKey(INPUT_KEY_LEFT_SHIFT)) {
        trans_factor *= 10;
    }
    
    // Translate forward/backward
    if (Input::getKey(INPUT_KEY_W)){
        Translate(GetForward()*trans_factor);
    }
    if (Input::getKey(INPUT_KEY_S)){
        Translate(-GetForward()*trans_factor);
    }
    // Translate left/right
    if (Input::getKey(INPUT_KEY_A)){
        Translate(-GetSide()*trans_factor);
    }
    if (Input::getKey(INPUT_KEY_D)){
        Translate(GetSide()*trans_factor);
    }
    // Translate up/down
    if (Input::getKey(INPUT_KEY_Q)){
        Translate(GetUp()*trans_factor);
    }
    if (Input::getKey(INPUT_KEY_E)){
        Translate(-GetUp()*trans_factor);
    }
    // Rotate pitch
    if (Input::getKey(INPUT_KEY_UP)){
        Pitch(rot_factor);
    }
    if (Input::getKey(INPUT_KEY_DOWN)){
        Pitch(-rot_factor);
    }
    // Rotate yaw
    if (Input::getKey(INPUT_KEY_LEFT)){
        Yaw(rot_factor);
    }
    if (Input::getKey(INPUT_KEY_RIGHT)){
        Yaw(-rot_factor);
    }
    // Rotate roll
    if (Input::getKey(INPUT_KEY_COMMA)){
        Roll(-rot_factor);
    }
    if (Input::getKey(INPUT_KEY_PERIOD)){
        Roll(rot_factor);
    }
}

} // namespace game
