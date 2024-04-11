#include "ProjectPanel.hpp"

// --------------------------- project Window bools ---------------------------
bool showConsoleWindow = false;
bool showLogWindow = false;
bool showProfileWindow = false;

namespace CyberCore {
    ProjectPanel::ProjectPanel(){
        _ProjectWindow();
    }

    void ProjectPanel::_ProjectWindow(){
        ImVec2 minSize(600, 350);
        ImGui::SetNextWindowSizeConstraints(minSize, ImVec2(FLT_MAX, FLT_MAX));
        ImGui::Begin("Project", nullptr );

        // Check if right mouse button is clicked in an empty area
        if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right) && !ImGui::IsAnyItemHovered()) {
            ImGui::OpenPopup("AddTabPopup"); // Open the context menu popup
        }

        // Context menu for adding windows
        if (ImGui::BeginPopup("AddTabPopup")) {
            if (ImGui::MenuItem("Add Console")) {
                // Set the boolean variable to show the console window
                showConsoleWindow = true;
            }
            if (ImGui::MenuItem("Add Log")) {
                // Set the boolean variable to show the log window
                showLogWindow = true;
            }
            if (ImGui::MenuItem("Add Profile")) {
                // Set the boolean variable to show the profile window
                showProfileWindow = true;
            }
            ImGui::EndPopup();
        }

        ImGui::End();

        // Render windows based on their respective boolean variables
        // ImGuiWindowFlags_NoCollapse -> docks window by default
        if (showConsoleWindow) {
            ImGui::Begin("Console", &showConsoleWindow, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Console window content goes here");
            ImGui::End();
        }

        if (showLogWindow) {
            ImGui::Begin("Log", &showLogWindow, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Log window content goes here");
            ImGui::End();
        }

        if (showProfileWindow) {
            ImGui::Begin("Profile", &showProfileWindow, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Profile window content goes here");
            ImGui::End();
        }
    }
    
} 
