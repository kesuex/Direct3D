#pragma once

#include <DirectXMath.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include<cmath>

using namespace DirectX;

class Camera
{
public:
    Camera(XMFLOAT3 pos, XMINT2 windowSize) : mPosition(pos), mWindowSize(windowSize)
    {
        mView = XMMatrixIdentity();
        mProjection = XMMatrixIdentity();
        mSpeed = 0.2f;
        mSensitivity = 100.0f;
    }

    void UpdateMatrix()
    {
        mView = XMMatrixLookAtLH(XMLoadFloat3(&mPosition), 
               (XMLoadFloat3(&mOrientation) + XMLoadFloat3(&mPosition)), 
                XMLoadFloat3(&mUp));

        mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(70.0f), 
                        (float)mWindowSize.x / (float)mWindowSize.y, 
                        0.1f, 
                        100.0f);
    }

    XMMATRIX GetViewMatrix() { return mView; }
    XMMATRIX GetProjectionMatrix() { return mProjection; }

    void HandleInputs(GLFWwindow* window)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                mPosition.x = mPosition.x + mSpeed * mOrientation.x;
                mPosition.y = mPosition.y + mSpeed * mOrientation.y;
                mPosition.z = mPosition.z + mSpeed * mOrientation.z;
            }

            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                mPosition.x = mPosition.x - mSpeed * mOrientation.x;
                mPosition.y = mPosition.y - mSpeed * mOrientation.y;
                mPosition.z = mPosition.z - mSpeed * mOrientation.z;
            }

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp)));
                XMFLOAT3 rightFloat;
                XMStoreFloat3(&rightFloat, right);
                mPosition.x = mPosition.x + mSpeed * rightFloat.x;
                mPosition.y = mPosition.y + mSpeed * rightFloat.y;
                mPosition.z = mPosition.z + mSpeed * rightFloat.z;
            }

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp)));
                XMFLOAT3 rightFloat;
                XMStoreFloat3(&rightFloat, right);
                mPosition.x = mPosition.x - mSpeed * rightFloat.x;
                mPosition.y = mPosition.y - mSpeed * rightFloat.y;
                mPosition.z = mPosition.z - mSpeed * rightFloat.z;
            }

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                mPosition.x = mPosition.x + mSpeed * mUp.x;
                mPosition.y = mPosition.y + mSpeed * mUp.y;
                mPosition.z = mPosition.z + mSpeed * mUp.z;
            }

            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            {
                mPosition.x = mPosition.x - mSpeed * mUp.x;
                mPosition.y = mPosition.y - mSpeed * mUp.y;
                mPosition.z = mPosition.z - mSpeed * mUp.z;
            }

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                mSpeed = 0.4f;
            }
            else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
            {
                mSpeed = 0.1f;
            }

            // Hides mouse cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (firstMouse)
            {
                glfwSetCursorPos(window, mWindowSize.x / 2, mWindowSize.y / 2);
                firstMouse = false;
            }

            // Stores the coordinates of the cursor
            double mouseX, mouseY;
            // Fetches the coordinates of the cursor
            glfwGetCursorPos(window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then transforms them into degrees
            float rotX = mSensitivity * (float)(mouseY - (mWindowSize.y / 2)) / mWindowSize.y;
            float rotY = mSensitivity * (float)(-mouseX + (mWindowSize.x / 2)) / mWindowSize.x;

            XMFLOAT3 tempAxis;
            XMStoreFloat3(&tempAxis, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&mOrientation), XMLoadFloat3(&mUp))));
            // Calculate a moving vertical change in the Orientation
            XMFLOAT3 newOrientation = RotateVector(mOrientation, -rotX, tempAxis);

            // Decides whether or not the next vertical Orientation is legal or not
            if (abs(XMVectorGetX(XMVector3AngleBetweenNormals(XMLoadFloat3(&newOrientation), XMLoadFloat3(&mUp))) - XMConvertToRadians(90.0f)) <= XMConvertToRadians(85.0f))
            {
                mOrientation = newOrientation;
            }

            // Rotates the Orientation left and right
            mOrientation = RotateVector(mOrientation, -rotY, mUp);

            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(window, mWindowSize.x / 2, mWindowSize.y / 2);

            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
            {
                // Unhides cursor since camera is not looking around anymore
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                // Makes sure the next time the camera looks around it doesn't jump
                firstMouse = true;
            }
        }

        
    }

  
private:
    XMFLOAT3 mPosition;
    XMFLOAT3 mOrientation = { 0.0f, 0.0f, 1.0f };
    XMFLOAT3 mUp = { 0.0f, 1.0f, 0.0f };

    XMINT2 mWindowSize;
    bool firstMouse = true;

    float mSpeed;
    float mSensitivity;

    XMMATRIX mView;
    XMMATRIX mProjection;

    XMFLOAT3 RotateVector(XMFLOAT3 vector, float angle, XMFLOAT3 axis) {
        XMVECTOR xmVector = XMLoadFloat3(&vector);
        XMVECTOR xmAxis = XMLoadFloat3(&axis);
        XMMATRIX rotationMatrix = XMMatrixRotationAxis(xmAxis, XMConvertToRadians(angle));
        xmVector = XMVector3TransformCoord(xmVector, rotationMatrix);
        XMStoreFloat3(&vector, xmVector);
        return vector;
    }
};