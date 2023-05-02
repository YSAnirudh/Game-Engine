#include "ImGuiLayer.h"

namespace YSAoo {
	ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer")
	{
		ImGuiWindowRef = nullptr;
	}

	ImGuiLayer::ImGuiLayer(Window* ImGuiWindow) : Layer("ImGui Layer")
	{
		SetImGuiWindow(ImGuiWindow);
		ImGuiObjectManagerRef = nullptr;
	}

	ImGuiLayer::ImGuiLayer(Window* ImGuiWindow, ObjectManager* ImGuiObjectManager)
	{
		SetImGuiWindow(ImGuiWindow);
		SetImGuiObjectManager(ImGuiObjectManager);
	}

	void ImGuiLayer::OnAttach()
	{
		if (!ImGuiWindowRef && !ImGuiWindowRef->GetMainWindow()) {
			return;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui_ImplGlfw_InitForOpenGL(ImGuiWindowRef->GetMainWindow(), true);
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		if (ImGui::GetCurrentContext() == nullptr) {
			return;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::ShowDemoWindow();

		bool* p_open = NULL;

		ImGuiMainViewport();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::ImGuiMainViewport(bool* pOpen)
	{
		ImGuiWindowFlags window_flags = 0;
		//window_flags |= ImGuiWindowFlags_NoTitleBar;
		//window_flags |= ImGuiWindowFlags_NoScrollbar;
		window_flags |= ImGuiWindowFlags_MenuBar;
		//window_flags |= ImGuiWindowFlags_NoMove;
		//window_flags |= ImGuiWindowFlags_NoResize;
		//window_flags |= ImGuiWindowFlags_NoCollapse;
		//window_flags |= ImGuiWindowFlags_NoNav;
		//window_flags |= ImGuiWindowFlags_NoBackground;
		//window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		//window_flags |= ImGuiWindowFlags_NoDocking;
		//window_flags |= ImGuiWindowFlags_UnsavedDocument;

		//ImGuiWindowFlags

		//ImGui::SetNextWindowSize(ImVec2(400, 600));
		if (!ImGui::Begin("Scene Manager", pOpen, window_flags))
		{
			// Early out if the window is collapsed, as an optimization.
			ImGui::End();
			return;
		}

		float PositionRestriction = 10.0f;
		float RotationRestriction = 180.0f;
		float ScaleRestriction = 10.0f;

		for (auto object : ImGuiObjectManagerRef->GetModelsList()) {
			if (ImGui::TreeNode(object.first)) {
				float xPos = object.second->GetObjectPosition().x;
				float yPos = object.second->GetObjectPosition().y;
				float zPos = object.second->GetObjectPosition().z;

				float xRot = object.second->GetObjectRotation().x;
				float yRot = object.second->GetObjectRotation().y;
				float zRot = object.second->GetObjectRotation().z;

				float xScale = object.second->GetObjectScale().x;
				float yScale = object.second->GetObjectScale().y;
				float zScale = object.second->GetObjectScale().z;

				float position[3] = { xPos, yPos, zPos };
				float rotation[3] = { glm::degrees(xRot), glm::degrees(yRot), glm::degrees(zRot) };
				float scale[3] = { xScale, yScale, zScale };
				ImGui::SliderFloat3("Object Position", position, -PositionRestriction, PositionRestriction);
				ImGui::SliderFloat3("Object Rotation", rotation, -RotationRestriction, RotationRestriction);
				ImGui::SliderFloat3("Object Scale", scale, -ScaleRestriction, ScaleRestriction);
				object.second->SetTransform(
					glm::vec3(position[0], position[1], position[2]),
					glm::vec3(glm::radians(rotation[0]), glm::radians(rotation[1]), glm::radians(rotation[2])),
					glm::vec3(scale[0], scale[1], scale[2])
				);
				ImGui::TreePop();
			}
		}

		for (auto object : ImGuiObjectManagerRef->GetMeshList()) {
			if (ImGui::TreeNode(object.first)) {
				float x = object.second->GetObjectPosition().x;
				float y = object.second->GetObjectPosition().y;
				float z = object.second->GetObjectPosition().z;

				float position[3] = { x, y, z };
				ImGui::SliderFloat3("Object Position", position, -PositionRestriction, PositionRestriction);
				object.second->SetTransform(glm::vec3(position[0], position[1], position[2]));
				ImGui::TreePop();
			}
		}

		for (auto object : ImGuiObjectManagerRef->GetLightsList()) {
			if (ImGui::TreeNode(object.first)) {
				float x = object.second->GetObjectPosition().x;
				float y = object.second->GetObjectPosition().y;
				float z = object.second->GetObjectPosition().z;

				float position[3] = { x, y, z };
				ImGui::SliderFloat3("Object Position", position, -PositionRestriction, PositionRestriction);
				object.second->SetTransform(glm::vec3(position[0], position[1], position[2]));
				ImGui::TreePop();
			}
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("InputManager")) {

				if (ImGui::MenuItem("Transform")) {
					
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	void ImGuiLayer::SetImGuiWindow(Window* TempWindow)
	{
		ImGuiWindowRef = TempWindow;
	}

	void ImGuiLayer::SetImGuiObjectManager(ObjectManager* ImGuiObjectManager)
	{
		ImGuiObjectManagerRef = ImGuiObjectManager;
	}

	ImGuiLayer::~ImGuiLayer()
	{
		OnDetach();
	}
}