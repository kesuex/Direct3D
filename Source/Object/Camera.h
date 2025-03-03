#pragma once

#include <GLFW/glfw3.h>
#include<DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera(XMFLOAT3 startposition);
	Camera();
	~Camera() = default;

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();

	//void ProcessMouseMovement(float xOffset, float yOffset);
	void ProcessLookPosiyion(float xOffset, float yOffset);
	void ProcessTransformation(GLFWwindow* window);


	//void SetPosition(XMFLOAT3 position);
	//void SetRotation(XMFLOAT3 rotation);
	//void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);


private:
	XMFLOAT3 mPosition;
	XMFLOAT3 mFront;
	XMFLOAT3 mUp;
	XMFLOAT3 mRight;
};