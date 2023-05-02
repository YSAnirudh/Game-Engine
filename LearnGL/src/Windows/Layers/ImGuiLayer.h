#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "Layer.h"

#include "Windows/Window.h"
#include "Managers/ObjectManager.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

namespace YSAoo {
    class ImGuiLayer :
        public Layer
    {
    public:
        ImGuiLayer();
        ImGuiLayer(Window* ImGuiWindow);
        ImGuiLayer(Window* ImGuiWindow, ObjectManager* ImGuiObjectManager);

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;

        // Window ImGui Draw Function Calls
        void ImGuiMainViewport(bool* pOpen = nullptr);

        // Setters
        void SetImGuiWindow(Window* ImGuiWindow);
        void SetImGuiObjectManager(ObjectManager* ImGuiObjectManager);

        //Getters
        inline Window* const GetImGuiWindow() { return ImGuiWindowRef; };
        inline ObjectManager* const GetImGuiObjectManager() { return ImGuiObjectManagerRef; };
        
        ~ImGuiLayer();
    protected:
        Window* ImGuiWindowRef = nullptr;
        ObjectManager* ImGuiObjectManagerRef = nullptr;

    };
}

#endif