#pragma once
#include "RE\ReEng.h"
#include "MyCamera.h"

class MyCameraManager {
	static MyCameraManager* instance;
	std::vector<MyCamera> cameraList;
public:
	matrix4 GetView(void);
	matrix4 GetProjection(bool ortho);
	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);
	void SetUp(vector3 v3Up);
	void MoveForward(float increment);
	void MoveSideways(float increment);
	void MoveVertical(float increment);
	void ChangePitch(float increment);
	void ChangeRoll(float increment);
	void ChangeYaw(float increment);


};