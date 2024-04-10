#include "../../CyberCore/src/config.h"

// global
#define WIDTH 1920
#define HEIGHT 1080

char INPUT_BUF[2048];
bool ToolBarActive = true;

// vertex shader source code
const char* vertexShaderSource = R"(
    #version 410 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// fragment shader source code
const char* fragmentShaderSource = R"(
    #version 410 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);
    }
)";

struct Tab {
    std::string name;
};

std::vector<Tab> tabs;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void SceneRenderer() {
}



void _SceneWindow() {
}

void _ProjectWindow() {
}

void AddTab(const std::string& tabName) {
    // Add tab based on the selected option
    tabs.push_back({tabName});
}

void _InspectorWindow() {
}


void _HierarchyWindow() {
}

// Function to create the dockspace window
void CreateDockSpaceWindow(float MenuBarHeight) {
}

// Function to create the toolbar at the top
float  _MenuBar(){
}

float _toolBar(float menubarHeight) {
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "\tCyberCore", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set OpenGL viewport size
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking

    // Setup ImGui GLFW binding
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    // Setup ImGui OpenGL binding
    ImGui_ImplOpenGL3_Init("#version 410");

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create the toolbar at the top
        float menuBarHeight = _MenuBar();

        float toolBarHeight = _toolBar(menuBarHeight);
        //std::cout << toolBarHeight << std::endl;

        toolBarHeight = 0;
        // Create and dock the dockspace window
        CreateDockSpaceWindow(toolBarHeight + 20); // 20px offset for tab height
        
        

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}