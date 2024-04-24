#include "ScenePanel.hpp"

// --------------------------- Scene Window bools ---------------------------
bool GuiEditorWindow = false;
bool sceneWindow = true;
bool gameWindow = true;


std::vector<glm::vec3> _positions;
std::vector<glm::vec3> _normals;
std::vector<glm::vec2> _texCoords;
std::vector<unsigned int> _indices;

static glm::vec3 scaleValue = glm::vec3(1.0f);
float _zoomLevel = 1.0f;
static float rotationAngleX = 0.0f;
static float rotationAngleY = 0.0f;
static float rotationAngleZ = 0.0f;

glm::mat4 _model = glm::mat4(1.0f);
glm::mat4 _view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 _projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

void loadOBJ(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            _positions.push_back(vertex);
        } else if (type == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            _texCoords.push_back(texCoord);
        } else if (type == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            _normals.push_back(normal);
        } else if (type == "f") {
            unsigned int vertexIndex, normalIndex, texCoordIndex;
            char separator;
            while (iss >> vertexIndex >> separator >> texCoordIndex >> separator >> normalIndex) {
                _indices.push_back(vertexIndex - 1); // OBJ indices start from 1
            }
        }
    }
    file.close();
}



//200, 115

namespace CyberCore {
    ScenePanel::ScenePanel() {
        _SceneWindow();
    }

    void ScenePanel::_SceneWindow() {
        // Set the minimum size for the scene window
        ImVec2 minSize(600, 800);

        // Set the constraints for the scene window
        ImGui::Begin("obj info");
        for (size_t i = 0; i < _positions.size(); ++i) {
            ImGui::Text("Vertex %zu: (%f, %f, %f)", i, _positions[i].x, _positions[i].y, _positions[i].z);
        }
        ImGui::End();

        ImGui::SetNextWindowSizeConstraints(minSize, ImVec2(FLT_MAX, FLT_MAX));

        int flags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
        // Create a texture to render a scene inside a window
        ImGui::Begin("Scene View", nullptr, flags);
        {
            ImVec2 windowSize = ImGui::GetContentRegionAvail();
            // ImGui::Text("Window Size: %.1f, %.1f", windowSize.x, windowSize.y);
            
            // draw(windowSize);

            _render(windowSize);
        }

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
           CyberCore::GamePanel();
        }
    }

    void ScenePanel::_render(ImVec2 windowSize){
    // add rendered texture to ImGUI scene window

        loadOBJ("../../CyberCore/Prims/cube.obj");

        CyberCore::CC_Shader shader;
        shader.createShader("../../shaders/vertex.shader", "../../shaders/fragment.shader");
        shader.useShader();

        mFramebuffer = std::make_unique<CyberCore::FrameBuffer>();
        // mFramebuffer->createFrameBuffer((int32_t)windowSize.x, (int32_t)windowSize.y);
        mFramebuffer->createFrameBuffer(WIDTH, HEIGHT);
        /// mFramebuffer->FrameBuffer::bind();
        mFramebuffer->bind();

        CyberCore::VertexIndexBuffer vbuffer;
        vbuffer.createBuffer(_positions, _indices);
        
        vbuffer.draw(_indices.size());
        

    
      

 
        glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "model"), 1, GL_FALSE, glm::value_ptr(_model));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "view"), 1, GL_FALSE, glm::value_ptr(_view));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

       //  mFramebuffer->unbind();
        
       

        ImGui::BeginChild("screne");
        auto text = mFramebuffer->FrameBuffer::getTextureID();
        uint64_t textureID = text;
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ windowSize.x, windowSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::EndChild();

        // cleanup
        // shader.deleteShader();
        // vbuffer.deleteBuffer();
    }
}
