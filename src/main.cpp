#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "../include/imgui/imgui.h"
#include "../include/imgui/backend/imgui_impl_glfw.h"
#include "../include/imgui/backend/imgui_impl_opengl3.h"

// global
#define WIDTH 1920
#define HEIGHT 1080

char INPUT_BUF[2048];
bool ToolBarActive = true;

// vertex shader source code
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// fragment shader source code
const char* fragmentShaderSource = R"(
    #version 330 core
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
    // Define the vertices of the triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // bottom-left corner
         0.5f, -0.5f, 0.0f,  // bottom-right corner
         0.0f,  0.5f, 0.0f   // top corner
    };

    unsigned int VAO, VBO;
    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate VBO and buffer vertex data
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create and bind a Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Render the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Clean up VBO and VAO
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}



void _SceneWindow() {
    ImGui::Begin("Scene View");
    ImVec2 MousePos = ImGui::GetCursorScreenPos();
   
    if (ImGui::BeginTabBar("SceneTabs")) {
        if (ImGui::BeginTabItem("Scene")) {
            SceneRenderer(); // Call the scene rendering function here
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("GUIEditor")) {
            ImGui::Text("GUI Editor");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Game View")) {
            ImGui::Text("Game Screen");
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void _ProjectWindow() {

    ImGui::Begin("Window 4", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiDockNodeFlags_AutoHideTabBar );

    // Check if right mouse button is clicked in an empty area
    if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right) && !ImGui::IsAnyItemHovered()) {
        ImGui::OpenPopup("AddTabPopup"); // Open the context menu popup
    }

    if (ImGui::BeginTabBar(" ")) {
        // "Project" tab
        if (ImGui::BeginTabItem("Project")) {
            ImGui::InputText("search", INPUT_BUF, IM_ARRAYSIZE(INPUT_BUF));
            ImGui::EndTabItem();
        }

        // Other tabs
        for (const auto& tab : tabs) {
            if (ImGui::BeginTabItem(tab.name.c_str())) {
                ImGui::InputText("search", INPUT_BUF, IM_ARRAYSIZE(INPUT_BUF));
                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }

    // Context menu for adding tabs
    if (ImGui::BeginPopup("AddTabPopup")) {
        if (ImGui::MenuItem("Add Console")) {
            // Add "Console" tab to the tabs vector
            tabs.push_back({"Console"});
        }
        if (ImGui::MenuItem("Add Log")) {
            // Add "Log" tab to the tabs vector
            tabs.push_back({"Log"});
        }
        if (ImGui::MenuItem("Add Profile")) {
            // Add "Profile" tab to the tabs vector
            tabs.push_back({"Profile"});
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void AddTab(const std::string& tabName) {
    // Add tab based on the selected option
    tabs.push_back({tabName});
}

void _InspectorWindow() {
    ImGui::Begin("Window 3", nullptr, ImGuiDockNodeFlags_AutoHideTabBar );

    if (ImGui::BeginTabBar("Inspector#left_tabs_bar")) {
        if (ImGui::BeginTabItem("Inspector View")) {
            ImGui::InputText("search", INPUT_BUF, IM_ARRAYSIZE(INPUT_BUF));
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Asset inspector")) {
            ImGui::InputText("search", INPUT_BUF, IM_ARRAYSIZE(INPUT_BUF));
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }

    ImGui::End();
}


void _HierarchyWindow() {
    ImGui::Begin("Window 1", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiDockNodeFlags_AutoHideTabBar);
    
    ImVec2 size = ImGui::GetWindowSize();
    
    if (ImGui::BeginTabBar("Hierarchy#left_tabs_bar")) {
        if (ImGui::BeginTabItem("Hierarchy")) {
            ImGui::InputText("search", INPUT_BUF, IM_ARRAYSIZE(INPUT_BUF));

            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }

    for (const auto& tab : tabs) {
       // TODO:: ADD a GameObject
    }

    // Check if right mouse button is clicked in an empty area
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

// Function to create the dockspace window
void CreateDockSpaceWindow(float MenuBarHeight) {
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 offset(0.0f, MenuBarHeight); // MenuBar Offset

    // Calculate the new position with the offset
    ImVec2 window_pos = ImVec2(viewport->Pos.x + offset.x, viewport->Pos.y + offset.y);
    
    ImGui::SetNextWindowPos(window_pos); // Set window position with offset
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);


    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.f, 0.f));


    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    // Call functions to create and dock windows
    _InspectorWindow();
    _ProjectWindow();
    _HierarchyWindow();
    _SceneWindow();

    ImGui::End(); // Close the dockspace window

    // Pop style vars
    ImGui::PopStyleVar(4);
}

// Function to create the toolbar at the top
float  _MenuBar(){

    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

    ImGui::SetNextWindowPos(ImVec2({0, 0}));
    ImGui::SetNextWindowSize(ImVec2(displaySize.x, 0));
    ImGui::Begin(" ", &ToolBarActive, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);
     if(ImGui::BeginMenuBar()){
        if(ImGui::BeginMenu("file")){
            if(ImGui::MenuItem("New Scence..")){ }
            if(ImGui::MenuItem("Open Scene..")){ }
            if(ImGui::MenuItem("Save Scenes..")){ }
            if(ImGui::MenuItem("Save Scenes as..")){ }
            if(ImGui::MenuItem("New Project..")){ }
            if(ImGui::MenuItem("Open Project..")){ }
            if(ImGui::MenuItem("Save Project..")){ }
            if(ImGui::MenuItem("Build/Project Setting..")){ }
            if(ImGui::MenuItem("Build & Run..")){ }

            if(ImGui::MenuItem("Exit")){
                ToolBarActive = false;
            }   
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();  
    }

    if(ImGui::BeginMenuBar()){
        if(ImGui::BeginMenu("Edit")){
            if(ImGui::MenuItem("Open..")){ }

            if(ImGui::MenuItem("Close..")){
                ToolBarActive = false;
            }   
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();  
    }

    if(ImGui::BeginMenuBar()){
        if(ImGui::BeginMenu("Tools")){
            if(ImGui::MenuItem("Open..")){ }

            if(ImGui::MenuItem("Close..")){
                ToolBarActive = false;
            }   
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();  
    }

    if(ImGui::BeginMenuBar()){
        if(ImGui::BeginMenu("View")){
            if(ImGui::MenuItem("Open..")){ }

            if(ImGui::MenuItem("Close..")){
                ToolBarActive = false;
            }   
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();  
    }

    ImGui::End();

    // std::cout << ImGui::GetWindowSize().y << std::endl;

    return ImGui::GetWindowSize().y;
}


int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Double ImGui Layout", NULL, NULL);
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
    ImGui_ImplOpenGL3_Init("#version 330");

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
        // Create and dock the dockspace window
        CreateDockSpaceWindow(menuBarHeight - 370.0f);
        

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
