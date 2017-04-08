#pragma once
#include "RE\ReEng.h"

class MyCameraClass
{	
	vector3 m_v3Up;
	vector3 m_v3Position;
	vector3 m_v3Target;
	matrix4 m_m4View;
	matrix4 m_m4Projection;
	static MyCameraClass* instance;	
public:
	// Gets View Matrix
	matrix4 GetView(void);

	// set view matrix
	void SetView();

	// Gets Projection matrix, ortho or persp based on bool
	matrix4 GetProjection(bool bOrtho);

	// set position of cam using v3 passed
	void SetPosition(vector3 v3Position);

	//  what the camera is looking at (probably going to be using glm lookat)
	void SetTarget(vector3 v3Target);

	// set up vector of camera
	void SetUp(vector3 v3Up);


	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);


	static MyCameraClass* GetInstance() 
	{
		if (instance == nullptr) 
			instance = new MyCameraClass();
		return instance;
	}

	static void ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

private:
	MyCameraClass() {};
	MyCameraClass(MyCameraClass const& other) {};
	MyCameraClass& operator=(MyCameraClass const&other) {};
	~MyCameraClass() {};
	
};