#include "../../CyberCore/src/config.h" // includes glm glfw glad iostream vector fstaream sstream
#include "../../CyberCore/Core/Util/CC_Buffers.hpp" // shaders

// Remove the struct Vertex

std::vector<glm::vec3> positions;
std::vector<glm::vec3> normals;
std::vector<glm::vec2> texCoords;
std::vector<unsigned int> indices;

// Transform stuff
void transformID(GLFWwindow* window, glm::mat4 &model);
void scaleControl();
void positionControl();
void positionControl(glm::mat4& model);
void resetTransformation(glm::mat4& model);

static glm::vec3 scaleValue = glm::vec3(1.0f);
glm::mat4 projection;
float zoomLevel = 1.0f;
static float rotationAngleX = 0.0f;
static float rotationAngleY = 0.0f;
static float rotationAngleZ = 0.0f;

void _loadOBJ(const std::string& path) {
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
            positions.push_back(vertex);
        } else if (type == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            texCoords.push_back(texCoord);
        } else if (type == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (type == "f") {
            unsigned int vertexIndex, normalIndex, texCoordIndex;
            char separator;
            while (iss >> vertexIndex >> separator >> texCoordIndex >> separator >> normalIndex) {
                indices.push_back(vertexIndex - 1); // OBJ indices start from 1
            }
        }
    }
    file.close();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Load .obj file
    _loadOBJ("../../CyberCore/Prims/cube.obj");

    // shader 
    CyberCore::CC_Shader shader;
    shader.createShader("../../shaders/vertex.shader", "../../shaders/fragment.shader");
    
   
    glEnable(GL_DEPTH_TEST); 

    // vertex buffer 
    CyberCore::VertexIndexBuffer vbuffer;
    vbuffer.createBuffer(positions, indices);
    

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Setup GLFW binding
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");


    // Transformation variables
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 modelScale = glm::mat4(1.0f);
    glm::mat4 modelRotation = glm::mat4(1.0f);


    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the framebuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("obj info");

        for (size_t i = 0; i < positions.size(); ++i) {
            ImGui::Text("Vertex %zu: (%f, %f, %f)", i, positions[i].x, positions[i].y, positions[i].z);
        }
        ImGui::End();

        transformID(window, model);

        // Use shader program
        shader.useShader();
        // Update uniform values
    
        glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.getShaderID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the object
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        vbuffer.draw(indices.size());

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    shader.deleteShader();
    vbuffer.deleteBuffer();

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Function to handle position control
void positionControl(glm::mat4& model) {
    ImGui::Text("Position\t\t\t");
    ImGui::SameLine();
    ImGui::PushItemWidth(75);

    ImGui::Text("X ");
    ImGui::SameLine();
    ImGui::DragFloat("##PosX", &model[3][0], 0.01f);
    ImGui::SameLine();

    ImGui::Text("Y ");
    ImGui::SameLine();
    ImGui::DragFloat("##PosY", &model[3][1], 0.01f);
    ImGui::SameLine();

    ImGui::Text("Z ");
    ImGui::SameLine();
    ImGui::DragFloat("##PosZ", &model[3][2], 0.01f);

    ImGui::PopItemWidth();
}

// Function to handle rotation control
void rotationControl() {
    ImGui::Text("Rotation\t\t\t");
     ImGui::SameLine();
    ImGui::PushItemWidth(75);

    ImGui::Text("X ");
    ImGui::SameLine();
    ImGui::DragFloat("##X", &rotationAngleX, 0.1f, -180.0f, 180.0f);
    ImGui::SameLine();

    ImGui::Text("Y ");
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &rotationAngleY, 0.1f, -180.0f, 180.0f);
    ImGui::SameLine();

    ImGui::Text("Z ");
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &rotationAngleZ, 0.1f, -180.0f, 180.0f);

    ImGui::PopItemWidth();
}

// Function to handle scale control
void scaleControl() {
    ImGui::Text("Scale   \t\t\t");
    ImGui::SameLine();
    ImGui::PushItemWidth(75);

    ImGui::Text("X ");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleX", &scaleValue[0], 0.01f);
    ImGui::SameLine();

    ImGui::Text("Y ");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleY", &scaleValue[1], 0.01f);
    ImGui::SameLine();

    ImGui::Text("Z ");
    ImGui::SameLine();
    ImGui::DragFloat("##ScaleZ", &scaleValue[2], 0.01f);

    ImGui::PopItemWidth();
}

// Function to reset transformation parameters
void resetTransformation(glm::mat4& model) {
    // Reset position
    model[3][0] = 0.0f;
    model[3][1] = 0.0f;
    model[3][2] = 0.0f;

    // Reset rotation
    rotationAngleX = 0.0f;
    rotationAngleY = 0.0f;
    rotationAngleZ = 0.0f;

    // Reset scale
    scaleValue = glm::vec3(1.0f);
}

void transformID(GLFWwindow* window, glm::mat4& model) {
	
    ImGui::Begin("Transform Controls", nullptr, ImGuiWindowFlags_NoMove);
		
    // Position control
    positionControl(model);

    // Rotation control
    rotationControl();

    // Scale control
    scaleControl();

    // Reset button
	if (ImGui::Button("Reset")) {
		resetTransformation(model);
	}

    // Apply transformations to model matrix
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(model[3]));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f))
                             * glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f))
                             * glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scaleValue);

    model = translationMatrix * rotationMatrix * scaleMatrix;

    // Get window size
    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);

    // Wrap mouse position within the ImGui window only when the DragFloat control is active
    if (ImGui::IsItemActive()) {
        ImVec2 mousePos = ImGui::GetMousePos();
        if (mousePos.x < 0) {
            glfwSetCursorPos(window, 0, mousePos.y); // left stopper
        } else if (mousePos.x > winWidth) {
            glfwSetCursorPos(window, winWidth, mousePos.y); // right stopper
        }
    }

    ImGui::End();
}
