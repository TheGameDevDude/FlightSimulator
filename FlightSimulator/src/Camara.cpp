#include "Camara.h"


Camara::Camara() {
	position = glm::vec3(0, 0, 0);
	angleX = 0;
	angleY = 0;
	direction = glm::vec3(0, 0, -1);
}

Camara::Camara(glm::vec3 position, float angleX, float angleY,float angleZ) {
	this->position = position;
	this->angleX = angleX;
	this->angleY = angleY;
	this->angleZ = angleZ;
	direction = glm::vec3(0, 0, -1);
}

glm::mat4 Camara::getViewMatrix(bool useQuaternion) const {
	if (useQuaternion == true) {
		return glm::toMat4(quaternion) * glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));
	}
	else {
		//rotation matrix (x rotation) * rotation matrix (y rotation) * translation matrix
		return  glm::rotate(glm::mat4(1.0f), glm::radians(-angleX), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(angleY), glm::vec3(0, 1, 0)) *  glm::rotate(glm::mat4(1.0f), glm::radians(-angleZ), glm::vec3(0, 0, 1)) * glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));
	}
}

void Camara::move(Controls control, float deltaTime) {
	//for getting the mouse and keyboard input
	control.tick();
	//updating x rotation and y rotation using the mouse input
	angleY += float(control.mouseDX) * mouseSensitivity;
	angleX += float(control.mouseDY) * mouseSensitivity;

	//clamping the x rotation to -90 to 90 so that the camara wont get upside down
	if (angleX > 90) {
		angleX = 90;
	}
	else if (angleX < -90) {
		angleX = -90;
	}

	glm::vec4 dir = glm::vec4(0, 0, -1, 0) * glm::rotate(glm::mat4(1.0f), glm::radians(-angleX), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(angleY), glm::vec3(0, 1, 0));
	direction = glm::vec3(dir.x, dir.y, dir.z);

	if (control.forward == true) {//move forward
		position.z -= speed * cos(glm::radians(angleY)) * deltaTime;
		position.x += speed * sin(glm::radians(angleY)) * deltaTime;
	}
	else if (control.backward == true) {//move backward
		position.z += speed * cos(glm::radians(angleY)) * deltaTime;
		position.x -= speed * sin(glm::radians(angleY)) * deltaTime;
	}

	if (control.rightArrow == true) {//strafe right
		position.x += speed * cos(glm::radians(angleY)) * deltaTime;
		position.z += speed * sin(glm::radians(angleY)) * deltaTime;
	}
	else if (control.leftArrow == true) {//strafe left
		position.x -= speed * cos(glm::radians(angleY)) * deltaTime;
		position.z -= speed * sin(glm::radians(angleY)) * deltaTime;
	}

	if (control.flyUp == true) {//fly up
		position.y += speed * deltaTime;
	}
	else if (control.flyDown == true) {//fly down
		position.y -= speed * deltaTime;
	}
}