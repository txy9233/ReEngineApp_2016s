#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bounding Spheres DEMO");
}

MyCameraClass* MyCameraClass::instance = nullptr;

void AppClass::InitVariables(void)
{
	//generate cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh manager
	//m_pMeshMngr->LoadModel("Minecraft\\Zombie.obj", "Zombie");
	//m_pBS0 = new MyBoundingSphereClass(m_pMeshMngr->GetVertexList("Zombie"));
	
	
	// create instance of camera
	m_pCamera = MyCameraClass::GetInstance();

	//set position, target, up
	m_pCamera->SetPosition(vector3(0.0f, 0.0f, 15.0f));
	m_pCamera->SetTarget(vector3(0.0f, 0.0f, 0.0f));
	m_pCamera->SetUp(vector3(0.0f, 1.0f, 0.0f));
	m_pCamera->SetView();
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

	//Call the arcball method
	ArcBall();

	//set the translate to create the transform matrix
	matrix4 m4Translate = glm::translate(m_v3Position);
	//m_pMeshMngr->SetModelMatrix(m4Translate, "Zombie"); //set the matrix to the model
	//m_pBS0->RenderSphere();//render the bounding sphere

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);

	/*m_pMeshMngr->Print("Radius: ");
	m_pMeshMngr->PrintLine(std::to_string(m_pBS0->m_fRadius), RERED);
	m_pMeshMngr->Print("Center: (");
	m_pMeshMngr->Print(std::to_string(m_pBS0->m_v3CenterGlobal.x), RERED);
	m_pMeshMngr->Print(" , ");
	m_pMeshMngr->Print(std::to_string(m_pBS0->m_v3CenterGlobal.y), RERED);
	m_pMeshMngr->Print(" , ");
	m_pMeshMngr->Print(std::to_string(m_pBS0->m_v3CenterGlobal.z), RERED);
	m_pMeshMngr->PrintLine(")");*/

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pCone->Render(
		m_pCamera->GetProjection(true), m_pCamera->GetView(), IDENTITY_M4
	);
	m_pMeshMngr->Render(); //renders the render list
	
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_pCone);
	MyCameraClass::ReleaseInstance();
	super::Release(); //release the memory of the inherited fields
}