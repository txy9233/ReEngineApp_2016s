#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - txy9233"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route
	
	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "Sun");
	m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "Earth");
	m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "Moon");

	//new code
	// relative distances
	matrix4 m_m4Sun;// Matrix for the Sun
	matrix4 m_m4Earth;// Matrix for the Earth
	matrix4 m_m4Moon;// Matrix for the Moon
	matrix4 earthDist = glm::translate(11.0f, 0.0f, 0.0f); // dist from sun
	matrix4 moonDist = glm::translate(2.0f, 0.0f, 0.0f);
	
	
	// quats for the Earth and Moon revolving about their own axis
	glm::quat earthRevo;
	glm::quat moonRevo;
	glm::quat earthOrb;
	glm::quat moonOrb;
	glm::quat angle1 = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat angle2 = glm::quat(vector3(0.0f, 360.0f, 0.0f));

	//map the value of earth orbit around sun in a percentage
	float fPercentage1 = MapValue((float)fRunTime, 0.0f, 2 * fEarthHalfRevTime, 0.0f, 1.0f); 
	float fPercentage2 = MapValue((float)fRunTime, 0.0f, 2 * fMoonHalfOrbTime, 0.0f, 1.0f);
	float fPercentage3 = MapValue((float)fRunTime, 0.0f, 2 * (float)fEarthHalfOrbTime, 0.0f, 1.0f);
	float fPercentage4 = MapValue((float)fRunTime, 0.0f, (float)fEarthHalfOrbTime/14, 0.0f, 1.0f);
	// the revolultion of the earth and moon about their own axis
	earthRevo = glm::mix(angle1, angle2, fPercentage1); 
	moonRevo = glm::mix(angle1, angle2, fPercentage2);
	earthOrb = glm::mix(angle1, angle2, fPercentage3);
	moonOrb = glm::mix(angle1, angle2, fPercentage4);

	// apply transformations 
	m_m4Earth = glm::scale(vector3(0.524f)) * glm::translate(glm::mat4_cast(earthOrb), vector3(11 * cos(fPercentage3), 0.0f, 0.0f)) * earthDist * glm::mat4_cast(earthOrb) * glm::mat4_cast(earthRevo);
	
	// couldn't figure out how to get the moon orbiting the earth
	//m_m4Moon = earthDist * moonDist * glm::scale(vector3(0.27f)) * glm::mat4_cast(moonRevo);
	//m_m4Moon = glm::scale(vector3(0.27f)) * glm::translate(m_m4Earth, vector3(2 * cos(fPercentage4), 0.0f, 0.0f)) * moonDist * glm::mat4_cast(moonOrb) * glm::mat4_cast(moonRevo) * earthDist;
	m_m4Sun = glm::scale(vector3(5.936));

	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}