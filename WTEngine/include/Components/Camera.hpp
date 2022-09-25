#ifndef CAMERA_HPP
#define CAMERA_HPP

// Import GLM stuff
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
public:	
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float input_roll, float input_pitch, float input_yaw, float width, float height);
	
	~Camera();

	// Move the camera position x,y,z relative to the camera's forwards, sideways and upwards
	void moveRelativeToForward(float forward, float side, float up);

	// Add pitch, yaw and roll to the Camera and accordingly adjust the viewing direction
	void rotateDir(float input_pitch, float input_yaw, float input_roll);

	glm::mat4 getViewMatrix();
	
	glm::mat4 getProjectionMatrix();
private:
	float roll;
	float pitch;
	float yaw;

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 upward;

	// projection is a constant
	glm::mat4 projection;
};

#endif