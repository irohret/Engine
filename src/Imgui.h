// ImGui.h
#pragma once

#include <imgui.h>

class ImGuiManager {
    public:
        ImGuiManager();
        ~ImGuiManager();

        void SetDisplaySize(float width, float height);

        void BeginFrame();
        void EndFrame();
        void Render();

    private:
        ImVec4 clearColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
};