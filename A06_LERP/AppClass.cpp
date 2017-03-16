#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");
	m_pMeshMngr->LoadModel("BackedUp\\Sphere.obj", "Sphere");
	fDuration = 1.0f;
	/*locations[] {
		vector3(-4.0f,-2.0f, 5.0f),
		
		vector3(-3.0f,-1.0f, 3.0f),
		vector3(2.0f,-1.0f, 3.0f),
		vector3(-2.0f, 0.0f, 0.0f),
		vector3(3.0f, 0.0f, 0.0f),
		vector3(-1.0f, 1.0f,-3.0f),
		vector3(4.0f, 1.0f,-3.0f),
		vector3(0.0f, 2.0f,-5.0f),
		vector3(5.0f, 2.0f,-5.0f),
		vector3(1.0f, 3.0f,-5.0f)
	};*/ // I tried to do the assignment of values all at once
	locations[0] = vector3(-4.0f, -2.0f, 5.0f);
	locations[1] = vector3(1.0f, -2.0f, 5.0f);
	locations[2] = vector3(-3.0f, -1.0f, 3.0f);
	locations[3] = vector3(2.0f, -1.0f, 3.0f);
	locations[4] = vector3(-2.0f, 0.0f, 0.0f);
	locations[5] = vector3(3.0f, 0.0f, 0.0f);
	locations[6] = vector3(-1.0f, 1.0f, -3.0f);
	locations[7] = vector3(4.0f, 1.0f, -3.0f);
	locations[8] = vector3(0.0f, 2.0f, -5.0f);
	locations[9] = vector3(5.0f, 2.0f, -5.0f);
	locations[10] = vector3(1.0f, 3.0f, -5.0f);
	locCounter = 0; // used for stepping through array for values
	mapValue = 0;
	m_m4Model = IDENTITY_M4;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	float fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static float fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "WallEye");
	//for (int i = 0; i < 11; i++) {
	//	//matrix4 transform = glm::translate(locations[i]);
	//	m_pMeshMngr->SetModelMatrix(transform, "Sphere");
	//} I was trying to figure out how to draw the spheres but couldn't
	
	// lerp the two locations from the array, set a mat4 equal to the returned vec3
	
	if (locCounter == 10) { // special case - manually input the positions in the array to calc for
			translation = glm::lerp(locations[locCounter], locations[0], mapValue); 
			
			
	} else{
			translation = glm::lerp(locations[locCounter], locations[locCounter + 1], mapValue);
					
	}	
	mapValue += fTimeSpan; // move along the scaled value at this time until t = 1	
	m_m4Model = glm::translate(translation);
	m_pMeshMngr->SetModelMatrix(m_m4Model, "WallEye");
	
	if (mapValue >= fDuration)
	{
		mapValue = 0;
		if (locCounter == 10) { //once we reach the end of the array reset back to 0 and start over
			locCounter = 0;
		}
		else {
			locCounter++;
		}
	}
	
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("fTimeSpan:");
	m_pMeshMngr->Print(std::to_string(fTimeSpan));
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->Print("fRunTime:");
	m_pMeshMngr->Print(std::to_string(fRunTime));
	
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}