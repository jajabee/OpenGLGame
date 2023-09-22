#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front_(glm::vec3(0.0f, 0.0f, -1.0f)), move_speed_(kSpeed), mouse_sensitivity_(kSensitivity), zoom_(kZoom)
{
    position_ = position;
    world_up_ = up;
    yaw_ = yaw;
    pitch_ = pitch;
    
    UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : front_(glm::vec3(0.0f, 0.0f, -1.0f)), move_speed_(kSpeed), mouse_sensitivity_(kSensitivity), zoom_(kZoom)
{
    position_ = glm::vec3(posX, posY, posZ);
    world_up_ = glm::vec3(upX, upY, upZ);
    yaw_ = yaw;
    pitch_ = pitch;

    UpdateCameraVectors();
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = move_speed_ * deltaTime;

    switch (direction)
    {
    case CameraMovement::kForward:
        position_ += front_ * velocity;
        break;
    case CameraMovement::kBackward:
        position_ -= front_ * velocity;
        break;
    case CameraMovement::kLeft:
        position_ -= right_ * velocity;
        break;
    case CameraMovement::kRight:
        position_ += right_ * velocity;
        break;
    }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= mouse_sensitivity_;
    yOffset *= mouse_sensitivity_;

    yaw_ += xOffset;
    pitch_ += yOffset;

    if (constrainPitch)
    {
        if (pitch_ > 89.0f)
        {
            pitch_ = 89.0f;
        }
        if (pitch_ < -89.0f)
        {
            pitch_ = -89.0f;
        }
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
    zoom_ -= yOffset;
    if (zoom_ < 1.0f)
    {
        zoom_ = 1.0f;
    }
    if (zoom_ > 45.0f)
    {
        zoom_ = 45.0f;
    }
}

glm::mat4 Camera::view_matrix() const
{
    return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::UpdateCameraVectors()
{
    // Calculate the new front vector.
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    // Calculate the new right and up vectors.
    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
}
