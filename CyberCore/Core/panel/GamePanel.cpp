#include "GamePanel.hpp"

namespace CyberCore {
    GamePanel::GamePanel(){
        _gameWindow();
    }

    void GamePanel::_gameWindow(){
        ImGui::Begin("Game View", nullptr, ImGuiWindowFlags_NoCollapse); // Docked by default
        ImGui::Text("Game View window content goes here");
        ImGui::End();
    }
}