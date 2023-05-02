#include "GLInit.h"

YSAoo::GLInit::GLInit()
{
	MainObjectManager = new ObjectManager();
}

YSAoo::GLInit::GLInit(const int WindowWidth, const int WindowHeight, const char* WindowName)
{
	MainObjectManager = new ObjectManager();
}

void YSAoo::GLInit::CalcAverageNormals(unsigned int* indices, unsigned int indexCount, GLfloat* vertices, unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset) {
	for (size_t i = 0; i < indexCount; i += 3) {
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 tempNormal = glm::normalize(glm::cross(v1, v2));
		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += tempNormal.x; vertices[in0 + 1] += tempNormal.y; vertices[in0 + 2] += tempNormal.z;
		vertices[in1] += tempNormal.x; vertices[in1 + 1] += tempNormal.y; vertices[in1 + 2] += tempNormal.z;
		vertices[in2] += tempNormal.x; vertices[in2 + 1] += tempNormal.y; vertices[in2 + 2] += tempNormal.z;
	}

	for (size_t i = 0; i < vertexCount / vLength; i++) {
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

int YSAoo::GLInit::MainLoop()
{
	if (InitializeGLFW() != 0) {
		return -1;
	}
	
	MainWindow = new Window();
	MainWindow->CreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Main Window");

	if (InitializeGLEW() != GLEW_OK) {
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, MainWindow->GetFrameBufferWidth(), MainWindow->GetFrameBufferHeight());

	ImGuiLayer* MainImGuiLayer = new ImGuiLayer(MainWindow, MainObjectManager);
	MainImGuiLayer->OnAttach();

	// Create Camera
	MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.3f);
	//glfwSetInputMode(MainWindow->GetMainWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)MainWindow->GetWindowWidth() / (GLfloat)MainWindow->GetWindowHeight(), 0.01f, 100.0f);

	unsigned int* Indices = new unsigned int[] {
		0, 1, 2,
			3, 1, 2,
			0, 4, 2,
			0, 1, 5,
			0, 4, 5,
			6, 4, 2,
			6, 3, 2,
			6, 7, 3,
			7, 1, 3,
			7, 1, 5,
			7, 4, 5,
			7, 4, 6,
	};

	GLfloat* Vertices = new GLfloat[]{
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f,0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 1.0f,0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,0.0f, 0.0f, 0.0f
	};

	GLfloat floorVertices[] = {
		30.0f, -1.0f, -30.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		30.0f, -1.0f, 30.0f,			1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-30.0f, -1.0f, 30.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-30.0f, -1.0f, -30.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	};

	unsigned int floorIndices[] = {
		0,3,1,
		1,3,2,
	};

	CalcAverageNormals(Indices, 36, Vertices, 64, 8, 5);
	
	Texture BrickTexture = Texture("Textures/brick.png");
	BrickTexture.LoadTextureA();

	Texture DirtTexture = Texture("Textures/dirt.png");
	DirtTexture.LoadTextureA();
	
	Material shinymaterial = Material(1.0f, 128.0f);

	Mesh* object = new Mesh();
	object->CreateObject("Floor", YObjectType::YMesh);
	
	object->InitMesh(floorVertices, floorIndices, 32, 6);
	object->AddMatTex(&shinymaterial, &BrickTexture);
	MainObjectManager->CreateCustomMesh(object);

	object = new Mesh();
	object->CreateObject("MainCube", YObjectType::YMesh);
	object->InitMesh(Vertices, Indices, 64, 36);
	object->SetTransform(glm::vec3(3.0f, 1.0f, 3.0f));
	object->AddMatTex(&shinymaterial, &DirtTexture);
	MainObjectManager->CreateCustomMesh(object);
	
	Model* Car = new Model();
	Car->CreateObject("Car", YObjectType::YModel);
	if (!Car->LoadModel("Models/sphere.obj")) {
		printf("COuldnt load model!\n");
	}
	Car->SetTransform(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3());
	MainObjectManager->CreateModel(Car);
	
	DirectionalLight* mainLight = new DirectionalLight(
		2048, 2048,
		1.0f, 1.0f, 1.0f,
		0.1f,
		0.0f, -1.0f, 0.0f,
		0.2f);
	mainLight->SetObjectName("MainLight");
	MainObjectManager->CreateLight(mainLight);

	DirectionalLight* mainLight2 = new DirectionalLight(
		2048, 2048,
		1.0f, 1.0f, 1.0f,
		0.1f,
		0.0f, -1.0f, -1.0f,
		0.2f);
	mainLight2->SetObjectName("MainLight1");
	MainObjectManager->CreateLight(mainLight2);

	PointLight* pointLight1 = new PointLight(
		2048, 2048, 0.01f, 100.f,
		1.0f, 1.0f, 1.0f,
		0.2f, 0.5f,
		3.0f, 3.0f, 0.0f,
		0.3f, 0.02f, 0.02f
	);
	pointLight1->SetObjectName("PointLight");
	MainObjectManager->CreateLight(pointLight1);

	/*PointLight* pointLight = new PointLight(
		2048, 2048, 0.01f, 100.f,
		1.0f, 1.0f, 1.0f,
		0.2f, 0.5f,
		0.0f, 3.0f, 0.0f,
		0.3f, 0.01f, 0.01f
	);
	pointLight->SetObjectName("PointLight1");
	MainObjectManager->CreateLight(pointLight);

	PointLight* pointLight2 = new PointLight(
		2048, 2048, 0.01f, 100.f,
		1.0f, 1.0f, 1.0f,
		0.2f, 0.5f,
		0.0f, 3.0f, 3.0f,
		0.3f, 0.1f, 0.1f
	);
	pointLight2->SetObjectName("PointLight2");
	MainObjectManager->CreateLight(pointLight2);*/

	/*std::vector<std::string> SkyboxFaces;
	SkyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	SkyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	SkyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	SkyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	SkyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	SkyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	MainSkybox = new Skybox(SkyboxFaces);*/
	if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::FORWARD_RENDERING) {
		ForwardRenderer = new ForwardRendering(WINDOW_WIDTH, WINDOW_HEIGHT);
		ForwardRenderer->AddShader("Shaders/lightingShader.vert", "Shaders/lightingShaderMult.frag");
		ForwardRenderer->AddShader("Shaders/directionalShadowMap.vert", "Shaders/directionalShadowMap.frag");
		ForwardRenderer->AddShader("Shaders/omniShadowMap.vert", "Shaders/omniShadowMap.frag", "Shaders/omniShadowMap.geom");
	}
	else if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::DEFERRED_RENDERING) {
		DeferredRenderer = new DeferredRendering(WINDOW_WIDTH, WINDOW_HEIGHT);
		DeferredRenderer->AddShader("Shaders/gBuffer.vert", "Shaders/gBuffer.frag");
		DeferredRenderer->AddShader("Shaders/stencilNull.vert", "Shaders/stencilNull.frag");
		DeferredRenderer->AddShader("Shaders/defLightShader.vert", "Shaders/defPointLightShader.frag");
		DeferredRenderer->AddShader("Shaders/defLightShader.vert", "Shaders/defDirectionalLightShader.frag");
		DeferredRenderer->AddShader("Shaders/directionalShadowMap.vert", "Shaders/directionalShadowMap.frag");
		DeferredRenderer->AddShader("Shaders/omniShadowMap.vert", "Shaders/omniShadowMap.frag", "Shaders/omniShadowMap.geom");
	}
	else if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::GBUFFER_RENDERING) {
		DeferredRenderer = new DeferredRendering(WINDOW_WIDTH, WINDOW_HEIGHT);
		DeferredRenderer->AddShader("Shaders/gBuffer.vert", "Shaders/gBuffer.frag");
	}


	int i = 0;
	//glm::vec3 ObjMovement;
	while (!MainWindow->WindowShouldClose()) {

		GLfloat Now = (GLfloat)glfwGetTime();
		DeltaTime = Now - LastTime;
		LastTime = GLfloat(Now);

		bool* Keys = MainWindow->GetInputManager()->GetKeys();

		MainCamera->CameraKeyControl(MainWindow->GetInputManager()->GetKeys(), DeltaTime);
		MainCamera->OnCtrlPress(MainWindow->GetMainWindow(), MainWindow->GetInputManager());

		// Poll for input events
		glfwPollEvents();

		if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::FORWARD_RENDERING) {
			ForwardRenderer->ForwardRender(MainObjectManager, projection, MainCamera->CalculateViewMatrix(), MainCamera->GetCameraPosition());
		}
		else if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::DEFERRED_RENDERING) {
			DeferredRenderer->DeferredRender(MainObjectManager, projection, MainCamera->CalculateViewMatrix(), MainCamera->GetCameraPosition());
		}
		else if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::GBUFFER_RENDERING) {
			DeferredRenderer->GBufferRender(MainObjectManager, projection, MainCamera->CalculateViewMatrix(), MainCamera->GetCameraPosition());
		}

		MainImGuiLayer->OnUpdate();

		MainWindow->SwapBuffers();
	}
	delete MainImGuiLayer;
	MainImGuiLayer = nullptr;

	return 0;
}

int YSAoo::GLInit::InitializeGLFW()
{
	glfwSetErrorCallback(&glfwError);
	if (!glfwInit()) {
		printf("Cannot Initializa GLFW");
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// This says throw error if older versions of opengl functions are used.
	// No Backward Compatability
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allows Forward Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	return 0;
}

int YSAoo::GLInit::InitializeGLEW()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("Cannot Initialize GLEW!!\n");
		glfwTerminate();
		return 1;
	}

	return GLEW_OK;
}

YSAoo::GLInit::~GLInit()
{
	glfwTerminate();
}