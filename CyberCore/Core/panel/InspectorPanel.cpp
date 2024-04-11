#include "InspectorPanel.hpp"

// --------------------------- Inspector Window bools ---------------------------
bool showAssetWindow = false;

namespace CyberCore {

    InspectorPanel::InspectorPanel(){
        _InspectorWindow();
    }

    void InspectorPanel::_InspectorWindow() {

        ImVec2 minSize(600, 800);
        ImGui::SetNextWindowSizeConstraints(minSize, ImVec2(FLT_MAX, FLT_MAX));

        ImGui::Begin("Inspector", nullptr);

        if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right) && !ImGui::IsAnyItemHovered()) {
            ImGui::OpenPopup("AddTabPopup"); // Open the context menu popup
        }   

        if (ImGui::BeginPopup("AddTabPopup")) {
            if (ImGui::MenuItem("Add Asset")) {
                // Set the boolean variable to true to show the console window
                showAssetWindow = true;
            } 
            ImGui::EndPopup();
        }
        
        ImGui::End();

        if (showAssetWindow) {
            ImGui::Begin("Asset", &showAssetWindow, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Asset window content goes here");
            ImGui::End();
        }
    }

}