#include "Camera.h"
/*
Camera::Camera(XMFLOAT3 startposition)
{
	mPosition = startposition;
	mFront = XMFLOAT3{ 0.0f, 0.0f, 1.0f };
	mUp = XMFLOAT3{ 0.0f, 1.0f, 0.0f };
	mRight = XMFLOAT3{ 1.0f, 0.0f, 0.0f };
}

Camera::Camera()
{
	mPosition = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	mFront = XMFLOAT3{ 0.0f, 0.0f, -1.0f };
	mUp = XMFLOAT3{ 0.0f, 1.0f, 0.0f };
	mRight = XMFLOAT3{ 1.0f, 0.0f, 0.0f };
}

XMMATRIX Camera::GetViewMatrix()
{
	XMVECTOR position = XMLoadFloat3(&mPosition);
	XMVECTOR front = XMLoadFloat3(&mFront);
	XMVECTOR up = XMLoadFloat3(&mUp);
	XMVECTOR right = XMLoadFloat3(&mRight);

    XMVECTOR eyeDirection = XMVector3Normalize(front);
	XMMATRIX viewMatrix = XMMatrixLookToLH(position, eyeDirection, -up);

	return viewMatrix;
	
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return XMMatrixPerspectiveFovLH(74.0f, 1280.0f/720.0f, 0.1f, 100.f);
}

void Camera::ProcessLookPosiyion(float xOffset, float yOffset)
{
}



void Camera::ProcessTransformation(GLFWwindow* window)
{
    float cameraSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mPosition = { mPosition.x, mPosition.y, mPosition.z + cameraSpeed };
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        mPosition = { mPosition.x, mPosition.y, mPosition.z - cameraSpeed };
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        mPosition = { mPosition.x - cameraSpeed, mPosition.y, mPosition.z };
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        mPosition = { mPosition.x + cameraSpeed, mPosition.y, mPosition.z };
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        mPosition = { mPosition.x, mPosition.y + cameraSpeed, mPosition.z };
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        mPosition = { mPosition.x, mPosition.y - cameraSpeed, mPosition.z };
    }
}
*/
