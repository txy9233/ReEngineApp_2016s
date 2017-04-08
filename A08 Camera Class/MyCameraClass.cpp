#include "MyCameraClass.h"

matrix4 MyCameraClass::GetView(void)
{
	return m_m4View;
}

void MyCameraClass::SetView()
{
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Up);
}

matrix4 MyCameraClass::GetProjection(bool bOrtho)
{
	if (bOrtho) { 
		m_m4Projection = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);
	}
	else {
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}
	return m_m4Projection;
}


void MyCameraClass::SetPosition(vector3 v3Position)
{
	m_v3Position = v3Position;
	
}

void MyCameraClass::SetTarget(vector3 v3Target)
{
	m_v3Target = v3Target;
	
}

void MyCameraClass::SetUp(vector3 v3Up)
{
	m_v3Up = v3Up;
	
}

void MyCameraClass::MoveForward(float fIncrement)
{
	vector3 temp = m_v3Target;
	temp.z += fIncrement;	
	SetTarget(temp);

	m_m4View = ToMatrix4(quaternion(temp));
	//SetView();
}

void MyCameraClass::MoveSideways(float fIncrement)
{
	vector3 temp = m_v3Target;
	temp.x += fIncrement;
	SetTarget(temp);

	m_m4View = ToMatrix4(quaternion(temp));
}

void MyCameraClass::MoveVertical(float fIncrement)
{
	vector3 temp = m_v3Target;
	temp.y += fIncrement;
	SetTarget(temp);

	m_m4View = ToMatrix4(quaternion(temp));
}



