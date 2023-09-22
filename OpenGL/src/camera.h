#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


enum CameraMovement
{
    kForward,
    kBackward,
    kLeft,
    kRight
};

const float kYaw = -90.0f;
const float kPitch = 0.0f;
const float kSpeed = 2.5f;
const float kSensitivity = 0.1f;
const float kZoom = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kYaw, float pitch = kPitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yOffset);

    glm::mat4 view_matrix() const;
    
    inline float zoom() const { return zoom_; }

private:
    void UpdateCameraVectors();

    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_;

    float yaw_;
    float pitch_;
    float move_speed_;
    float mouse_sensitivity_;
    float zoom_;
};

