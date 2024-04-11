#include "CC_ImGui.h"

bool ToolBarActive = true;

struct Tab {
    std::string name;
};

std::vector<Tab> tabs;

namespace CyberCore {

    CC_ImGui::CC_ImGui(CyberCore::CC_Window& window){
        init_ImGui(window);
    }

    // Function to create the dockspace window
    void CC_ImGui::CreateDockSpaceWindow(float toolBarHeight) {
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 offset(0.0f, toolBarHeight); // MenuBar Offset

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
        CyberCore::InspectorPanel();
        CyberCore::ProjectPanel();
        CyberCore::HierarchyPanel();
        CyberCore::ScenePanel();

        ImGui::End(); // Close the dockspace window

        // Pop style vars
        ImGui::PopStyleVar(4);
    }

    // Function to create the toolbar at the top
    float CC_ImGui::_MenuBar(){

       // ImVec4 bck_color1 = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // white
        ImVec4 color_grey = ImVec4(0.30f, 0.31f, 0.34f, 1.0f); // grey
        ImVec4 color_black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // balck
        ImVec4 color_white = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        
        
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        ImGui::SetNextWindowPos(ImVec2({0, -1})); // (-1) remove single pixel padding
        ImGui::SetNextWindowSize(ImVec2(displaySize.x, 0));

        // Set background color
        ImGui::PushStyleColor(ImGuiCol_WindowBg, color_grey);
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, color_black);
        ImGui::PushStyleColor(ImGuiCol_Text, color_white);
  

        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 4.0f));
    
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

        ImGui::PopStyleColor(3); // pop color changes
        ImGui::PopStyleVar(3);

        // std::cout << ImGui::GetWindowSize().y << std::endl;

        return ImGui::GetWindowSize().y;
    }

    float CC_ImGui::_ToolBar(float menubarHeight) {
        ImVec4 bck_color = ImVec4(0.30f, 0.31f, 0.34f, 1.0f);

        ImVec2 displaySize = ImGui::GetIO().DisplaySize;

        ImGui::SetNextWindowPos(ImVec2({0, 0})); // (-1) remove single pixel padding
        ImGui::SetNextWindowSize(ImVec2(displaySize.x, 0));

        ImGui::PushStyleColor(ImGuiCol_WindowBg, bck_color);

        ImGui::Begin(" ", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);
        
        // Calculate the center position of the toolbar
        ImVec2 toolbarCenter(displaySize.x / 2.0f, menubarHeight + ImGui::GetWindowSize().y / 2.0f);

        // Calculate the width of the two buttons combined
        float totalButtonWidth = 80.0f + 80.0f + 16.0f; // 80 for each button + 16 for spacing

        // Position the "Play" button at the center
        ImGui::SetCursorPos(ImVec2(toolbarCenter.x - totalButtonWidth / 2.0f, ImGui::GetCursorPosY()));
        if (ImGui::Button("Play", ImVec2(80, 0))) {
            // Handle play button click
        }

        // Position the "Pause" button next to the "Play" button
        ImGui::SameLine();
        if (ImGui::Button("Pause", ImVec2(80, 0))) {
            // Handle pause button click
        }

        ImGui::PopStyleColor();
        ImGui::End();
        return ImGui::GetWindowSize().y;
    }
    
    void CC_ImGui::init_ImGui(CyberCore::CC_Window& window) {
        // Setup ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking

        // Setup ImGui GLFW binding using the window parameter
        ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);

        // Setup ImGui OpenGL binding
        ImGui_ImplOpenGL3_Init("#version 410");
    }
}

