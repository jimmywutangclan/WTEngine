#include "Components/Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float input_roll, float input_pitch, float input_yaw, float width, float height, float _viewingDist) {
	position = pos;
	startingDirection = dir;
	direction = dir;
	upward = up;

	// Set up projection matrix since it's constant
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, _viewingDist);


	// Set up roll, pitch and yaw
	roll = input_roll;
	pitch = input_pitch;
	yaw = input_yaw;

	viewingDist = _viewingDist;
}

Camera::~Camera() {

}

//  Move the camera position x,y,z relative to the camera's forwards, sideways and upwards
void Camera::moveRelativeToForward(float forward, float side, float up) {
	position += forward * direction;
	position += side * glm::cross(direction, upward);
}

void Camera::rotateDir(float input_pitch, float input_yaw, float input_roll) {
	// Update the direction of the camera
	pitch += input_pitch;
	yaw += input_yaw;
	roll += input_roll;

	/*
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));*/

	glm::quat directionRotationQuat = glm::quat(glm::vec3(-pitch, yaw, roll));
	glm::mat4 directionRotationMatrix = glm::mat4_cast(directionRotationQuat);
	direction = directionRotationMatrix * glm::vec4(startingDirection, 1);
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + direction, upward);
}

glm::mat4 Camera::getProjectionMatrix() {
	return projection;
}