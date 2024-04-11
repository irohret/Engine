#include "HierarchyPanel.hpp"

char INPUT_BUF[2048];

namespace CyberCore {

    HierarchyPanel::HierarchyPanel(){
        _HierarchyWindow();
    }

    void HierarchyPanel::_HierarchyWindow() {
        ImVec2 minSize(200, 400);
        ImGui::SetNextWindowSizeConstraints(minSize, ImVec2(FLT_MAX, FLT_MAX));

        ImGui::Begin("Hierarchy", nullptr);
        ImGui::InputText("search", INPUT_BUF, IM_ARRAYSIZE(INPUT_BUF));

        if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right) && !ImGui::IsAnyItemHovered()) {
            ImGui::OpenPopup("HierarchyPopup"); // Open the context menu popup
        }

        if (ImGui::BeginPopup("HierarchyPopup")) {
            if (ImGui::MenuItem("Create Empty")) {
                // Add Empty GameObject
            }
            if (ImGui::BeginMenu("3D Object")) {
                if (ImGui::MenuItem("Cube")) {
                    // Add code to create a cube
                }
                if (ImGui::MenuItem("Sphere")) {
                    // Add code to create a cube
                }
                if (ImGui::MenuItem("Capsule")) {
                    // Add code to create a cube
                }
                if (ImGui::MenuItem("Cylinder")) {
                    // Add code to create a cube
                }
                if (ImGui::MenuItem("Plane")) {
                    // Add code to create a cube
                }
                if (ImGui::MenuItem("Quad")) {
                    // Add code to create a cube
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Camera")) {
                // Add a new Camera 
            }
            ImGui::EndPopup();
        }
        
        ImGui::End();
    }
}