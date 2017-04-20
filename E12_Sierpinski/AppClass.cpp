#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("E12 - Instance Rendering");
	m_v4ClearColor = vector4(REBLACK, 1.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	
	//Creating the Mesh points
	/*m_pMesh->AddVertexPosition(vector3(-1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3( 1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	*/
	m_pMesh->AddVertexPosition(vector3(-0.5f,  0.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3( 0.5f, 0.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(0.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	
	//tried to implement the solution at http://cs.lmu.edu/~ray/notes/openglexamples/ on sierpinski2d
	vector2 vertices[] = { vector2(0.0f, 0.0f), vector2(250.0f, 500.0f), vector2(500.0f, 0.0f) };
	vector2 pointInside(75.0f, 50.0f);
	
	m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObject(s)											   //clear the screen
	for (int i = 0; i < 250; i++)
	{
		int j = rand() % 3;
		
		// find the midpoint of the given point and the point inside
		pointInside.x = (pointInside.x + vertices[j].x/2.0f);
		pointInside.y = (pointInside.y + vertices[j].y/2.0f);

		//render a triangle at that coordinate
		m_pMesh->Render(m4Projection, m4View, glm::translate(vector3(pointInside, 0.0f)));
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}