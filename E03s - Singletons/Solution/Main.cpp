/*--------------------------------------------------------------------------------------------------
Comments about this program
--------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>

class Mesh
{
	std::string name;
public:
	Mesh(std::string _name) : name(_name) {}
	friend std::ostream& operator<<(std::ostream& os, const Mesh other)
	{
		return os << other.name.c_str();
	}
};

class MeshManager
{
	static MeshManager* instance;
	std::vector<Mesh> model;
public:
	static MeshManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new MeshManager();
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
	void AddModel(std::string name)
	{
		model.push_back(Mesh(name));
	}
	void PrintContents(void)
	{
		std::cout << "Meshes in list: " << model.size() << std::endl;
		for each (Mesh object in model)
		{
			std::cout << object << std::endl;
		}
		std::cout << std::endl;
	}
private:
	MeshManager() {};
	MeshManager(MeshManager const& other) {};
	MeshManager& operator=(MeshManager const& other) {};
	~MeshManager() { Release(); }
	void Release()
	{
		model.clear();
	}

};
MeshManager* MeshManager::instance = nullptr;
int main(void)
{
	MeshManager* oMeshManager = MeshManager::GetInstance();

	oMeshManager->PrintContents();

	oMeshManager->AddModel("Duck.obj");
	oMeshManager->AddModel("Horse.obj");
	oMeshManager->AddModel("Bird.obj");
	oMeshManager->AddModel("Dog.obj");

	oMeshManager->PrintContents();

	MeshManager::ReleaseInstance();

	getchar();
	return 0;
}