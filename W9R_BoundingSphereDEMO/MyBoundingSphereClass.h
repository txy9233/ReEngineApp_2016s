#pragma once
#include "RE\ReEng.h"

class MyBoundingSphereClass
{
public:
	float m_fRadius = 0.0f;
	vector3 m_v3Center = vector3(0.0f);
	matrix4 m_m4ToWorld = IDENTITY_M4;
	MeshManagerSingleton* m_pMeshMngr = nullptr;
	MyBoundingSphereClass(std::vector<vector3> vertexList);
	void RenderSphere();
	void SetModelMatrix(matrix4 a_m4ToWorld);
};