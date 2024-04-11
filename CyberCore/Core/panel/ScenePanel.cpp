#include "ScenePanel.hpp"

// --------------------------- Scene Window bools ---------------------------
bool GuiEditorWindow = false;
bool sceneWindow = true;
bool gameWindow = true;


namespace CyberCore{
    ScenePanel::ScenePanel(){
        _SceneWindow();
    }

    void ScenePanel::_SceneWindow(){
        ImVec2 minSize(600, 800);
        ImGui::SetNextWindowSizeConstraints(minSize, ImVec2(FLT_MAX, FLT_MAX));

        ImGui::Begin("Scene View", nullptr);
       
        // Check if right mouse button is clicked in an empty area
        if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right) && !ImGui::IsAnyItemHovered()) {
            ImGui::OpenPopup("AddTabPopup"); // Open the context menu popup
        }

        if (ImGui::BeginPopup("AddTabPopup")) { 

            if (ImGui::MenuItem("ImGuI Editor")) {
                GuiEditorWindow = true;
            }

            if (ImGui::MenuItem("Game View")) {
                gameWindow = true;
            }
            
            ImGui::EndPopup();
        }

        ImGui::End();

        if (GuiEditorWindow) {
            ImGui::Begin("ImGuI Editor", &GuiEditorWindow, ImGuiWindowFlags_NoCollapse); // Docked by default
            ImGui::Text("GUI Editor window content goes here");
            ImGui::End();
        }

        if (gameWindow) {
            ImGui::Begin("Game View", &gameWindow, ImGuiWindowFlags_NoCollapse); // Docked by default
            ImGui::Text("Game View window content goes here");
            ImGui::End();
        }
    }

}