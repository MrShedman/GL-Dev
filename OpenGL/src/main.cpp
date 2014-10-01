
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  

#include <iostream>

#include "3DEngine.h"
#include "components/freeLook.h"
#include "components/freeMove.h"
#include "physics\physicsEngine.h"
#include "physics\boundingSphere.h"
#include "physics\physicsObject.h"
#include "components\physicsEngineComponent.h"
#include "components\physicsObjectComponent.h"
#include "core\FileSystem.h"

#define FRUSTUM_TEST 0
#define FILESYSTEM_TEST 0

class TestGame : public Game
{
public:
	TestGame(){}
	
	virtual void Init(Window& window);
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}
};

void TestGame::Init(Window& window)
{

#if FILESYSTEM_TEST == 1

	std::cout << getUserPath() << std::endl;
	std::cout << getAppPath() << std::endl;

	std::vector<std::string> extensions;
	extensions.push_back("txt");
	extensions.push_back("obj");
	extensions.push_back("log");

	std::cout << getOpenFilePath(window.getSystemHandle(), "C:\\Users\\Ross\\Documents\\Visual Studio 2013\\cinder_0.8.6_vc2013\\samples\\TextSDF\\vc2013\\Release", extensions);

#endif

	Material default("default", Texture("defaultTexture.png"), 0.f, 0.f);
	Material bricks("bricks", Texture("bricks.jpg"), 0.0f, 0, Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);
	Material bricks2("bricks2", Texture("bricks2.jpg"), 0.0f, 0, Texture("bricks2_normal.png"), Texture("bricks2_disp.jpg"), 0.04f, -1.0f);
	Material grass("grass", Texture("grass.jpg"), 0.f, 0.f, Texture("grass_normal.jpg"), Texture("grass_disp.jpg"), 0.03f, -0.5f);
	Material rock("rock", Texture("rock.jpg"), 0.f, 0.f, Texture("rock_normal.jpg"), Texture("rock_disp.jpg"), 0.03f, -0.5f);
	
#if FRUSTUM_TEST == 1

	AddToScene((new Entity(Vector3f(0, -1, 5), Quaternion(), 32.0f))
		->AddComponent(new MeshRenderer(Mesh("terrain02.obj"), Material("bricks"))));
		
	AddToScene((new Entity(Vector3f(7,0,7)))
		->AddComponent(new PointLight(Vector3f(0,1,0), 0.4f, Attenuation(0,0,1))));
	
	AddToScene((new Entity(Vector3f(), Quaternion(Vector3f(1,0,0), ToRadians(-30))))
		->AddComponent(new DirectionalLight(Vector3f(1,1,1), 0.4f, 10, 80.0f, 1.0f)));
	
	AddToScene((new Entity(Vector3f(0, 2, 10), Quaternion(Vector3f(0, 1, 0), 0.4f), 0.2f))
		->AddComponent(new MeshRenderer(Mesh("plane2.obj"), Material("bricks2"))));

	AddToScene((new Entity(Vector3f(0, 5, 10), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f)), 2.0f))
		->AddComponent(new MeshRenderer(Mesh("panel.obj"), Material("bricks"))));
	
	AddToScene((new Entity())
		->AddComponent(new CameraComponent(Matrix4f().InitPerspective(ToRadians(60.0f), window.getAspect(), 0.1f, 1000.0f)))
		->AddComponent(new FreeLook(window.getCentre(), window, 0.3f))
		->AddComponent(new FreeMove(12.0f))
		->AddComponent(new SpotLight(Vector3f(0.0f, 0.5f, 1.0f), 0.3f, Attenuation(0, 0, 0.02f), ToRadians(70.f), 7, 1.0f, 0.5f)));
	
	AddToScene((new Entity(Vector3f(24,-12,5), Quaternion(Vector3f(0,1,0), ToRadians(30.0f))))
		->AddComponent(new MeshRenderer(Mesh("sphere.obj"), Material("bricks")))
		->AddComponent(new SpotLight(Vector3f(0, 1, 1), 0.4f, Attenuation(0, 0, 0.02f), ToRadians(91.1f), 7, 1.0f, 0.5f)));

	AddToScene((new Entity(Vector3f(24, -4, 5), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
	AddToScene((new Entity(Vector3f(28, -4, 5), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
	AddToScene((new Entity(Vector3f(28, -4, 7), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
	AddToScene((new Entity(Vector3f(28, -4, 9), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
	AddToScene((new Entity(Vector3f(26, -4, 9), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
	AddToScene((new Entity(Vector3f(24, -4, 9), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
	AddToScene((new Entity(Vector3f(24, -4, 7), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
		->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));

	int size = 10;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				AddToScene((new Entity(Vector3f(i * 2, j * 2, k * 2 + 20), Quaternion(Vector3f(1, 0, 0), ToRadians(90.0f))))
					->AddComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks2"))));
			}
		}
	}

	PhysicsEngine physicsEngine;

	physicsEngine.AddObject(PhysicsObject(
		new BoundingSphere(Vector3f(0.0f, 0.0f, 0.0f), 1.0f),
		Vector3f(0.0f, 0.0f, 1.141f / 2.0f)));

	physicsEngine.AddObject(PhysicsObject(
		new BoundingSphere(Vector3f(1.414f / 2.0f * 7.0f, 0.0f, 1.414f / 2.0f * 7.0f), 1.0f),
		Vector3f(-1.414f / 2.0f, 0.0f, -1.414f / 2.0f)));


	PhysicsEngineComponent* physicsEngineComponent
		= new PhysicsEngineComponent(physicsEngine);

	for (unsigned int i = 0;
		i < physicsEngineComponent->GetPhysicsEngine().GetNumObjects();
		i++)
	{

		AddToScene((new Entity(Vector3f(0, 0, 0), Quaternion(),
			1.0f))
			->AddComponent(new PhysicsObjectComponent(
			&physicsEngineComponent->GetPhysicsEngine().GetObject(i)))
			->AddComponent(new MeshRenderer(Mesh("sphere.obj"), Material("bricks"))));
	}

	AddToScene((new Entity())
		->AddComponent(physicsEngineComponent));
	
#else
	AddToScene((new Entity())
		->AddComponent(new CameraComponent(Matrix4f().InitPerspective(
		ToRadians(70.0f), window.getAspect(), 0.1f, 1000.0f)))
		->AddComponent(new FreeLook(window.getCentre(), window, 0.3f))
		->AddComponent(new FreeMove(10.0f))
		->AddComponent(new SpotLight(Vector3f(0.0f, 0.5f, 1.0f), 0.5f, Attenuation(0, 0, 0.005f), ToRadians(70.f), 7, 1.0f, 0.5f)));

	static const int CUBE_SIZE = 6;

	AddToScene((new Entity())
		->AddComponent(new PointLight(Vector3f(1, 1, 1),
		(CUBE_SIZE * CUBE_SIZE) * 2, Attenuation(0, 0, 1))));

	int objectCount = 0;

	for (int i = -CUBE_SIZE; i <= CUBE_SIZE; i++)
	{
		for (int j = -CUBE_SIZE; j <= CUBE_SIZE; j++)
		{
			for (int k = -CUBE_SIZE; k <= CUBE_SIZE; k++)
			{
				if (i == -CUBE_SIZE || i == CUBE_SIZE ||
					j == -CUBE_SIZE || j == CUBE_SIZE ||
					k == -CUBE_SIZE || k == CUBE_SIZE)
				{
					if (i == 0 || j == 0 || k == 0)
					{
						AddToScene((new Entity(Vector3f(i * 2, j * 2, k * 2)))
							->AddComponent(new MeshRenderer(Mesh("sphere.obj"),
							Material("bricks"))));
						objectCount++;
					}
					else
					{
						AddToScene((new Entity(Vector3f(i * 2, j * 2, k * 2)))
							->AddComponent(new MeshRenderer(Mesh("cube.obj"),
							Material("bricks2"))));
						objectCount++;
					}

				}
			}
		}
	}

	std::cout << "Object count: " << objectCount << std::endl;
#endif
}

int main()
{
	ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 2;
	settings.core = true;

	TestGame game;
	Window window(VideoMode(1280, 720), "3D Game Engine", Style::Default, settings);
	RenderingEngine renderer(window);
		
	std::cout << "GPU: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	CoreEngine engine(60, &window, &renderer, &game);
	engine.Start();
	
	return 0;
}