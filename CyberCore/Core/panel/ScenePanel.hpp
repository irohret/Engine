#pragma once

#include "PanelConfig.h"

#include "stb_image.h"
#include <iostream>
#include <memory>


#include "../Shader/CC_Shader.hpp"
#include "../Util/CC_Buffers.hpp"

#define WIDTH 1920
#define HEIGHT 1080
// files
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

void draw(ImVec2 windowSize);
void loadOBJ(const std::string& path);

namespace CyberCore {
    class ScenePanel {
    public:

        ScenePanel();
        void _render(ImVec2 windowSize);

    private:
        void _SceneWindow();
        std::shared_ptr<CyberCore::FrameBuffer> mFramebuffer;
        // std::shared_ptr<CyberCore::Mesh> mFramebuffer;
        // std::shared_ptr<CyberCore::Shader> _shader;
        // std::shared_ptr<CyberCore::Lights> Framebuffer;
    };
}

