////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}


XMFLOAT3 CameraClass::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}


void CameraClass::Render()
{
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float pitchRad = XMConvertToRadians(m_rotationX);
	float yawRad = XMConvertToRadians(m_rotationY);

	// Create rotation matrices
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitchRad, yawRad, 0.0f); // Zero roll

	// Default forward vector (looking down -Z axis)
	XMVECTOR defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR defaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Apply rotation to forward and up vectors
	m_forward = XMVector3TransformCoord(defaultForward, rotationMatrix);
	m_up = XMVector3TransformCoord(defaultUp, rotationMatrix);

	// Compute right vector
	m_right = XMVector3Cross(m_up, m_forward);



	XMVECTOR position = XMVectorSet(m_positionX, m_positionY, m_positionZ, 0.0f);

	XMVECTOR lookAt = position + m_forward;

	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, m_up);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}
