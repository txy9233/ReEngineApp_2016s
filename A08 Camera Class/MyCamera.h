#pragma once
#include "MyCameraManager.h"


class MyCamera {
	matrix4 m_m4Projection = matrix4(1.0f);
	matrix4 m_m4View = matrix4(1.0f);
public:
	//Constructor
	MyCamera(void);
};