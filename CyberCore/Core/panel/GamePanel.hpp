#pragma once

#include "PanelConfig.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace CyberCore {
    class GamePanel {
    public:
        GamePanel();
    private:
        void _gameWindow();
    };
}

