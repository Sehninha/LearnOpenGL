#ifndef  CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

using namespace glm;

class Camera
{
public:
	vec3 position;
	vec3 right;
	vec3 up;
	vec3 forward;

	Camera(vec3 position)
	{
		this->position = position;

		right = vec3(1.0f, 0.0f, 0.0f);
		up = vec3(0.0f, 1.0f, 0.0f);
		forward = vec3(0.0f, 0.0f, 1.0f);
	}

	mat4 GetViewMatrix()
	{
		return lookAt(position, vec3(0.0f, 0.0f, 0.0f), up);
	}

	void SetOrthographicProjection(float width, float height, float nearPlaneDistance, float farPlaneDistance)
	{
		projectionMatrix = ortho(-(width / 2), width / 2, -(height / 2), height / 2, nearPlaneDistance, farPlaneDistance);
	}

	void SetPerspectiveProjection(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance, float fieldOfView)
	{
		projectionMatrix = perspective(fieldOfView, screenWidth / screenHeight, nearPlaneDistance, farPlaneDistance);
	}

	mat4 GetProjectionMatrix()
	{
		return projectionMatrix;
	}

private:
	mat4 projectionMatrix;
};

#endif