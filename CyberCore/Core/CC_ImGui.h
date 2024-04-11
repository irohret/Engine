#pragma once

// Includes
#include <iostream>              // Standard Input/Output Stream Library
#include <string>                // String Library
#include <vector>                // Vector Library

#include "imgui.h"              // ImGui Library
#include "imgui_impl_glfw.h"    // ImGui GLFW Implementation
#include "imgui_impl_opengl3.h" // ImGui OpenGL Implementation

#include "CC_Window.h"          // CyberCore Window Header

#include "../../CyberCore/Core/panel/InspectorPanel.hpp"
#include "../../CyberCore/Core/panel/HierarchyPanel.hpp"
#include "../../CyberCore/Core/panel/ProjectPanel.hpp"
#include "../../CyberCore/Core/panel/ScenePanel.hpp"


// HierarchyPanel::_HierarchyWindow()
namespace CyberCore {

    // Class declaration for handling ImGui functionalities
    class CC_ImGui {

    public:
      
        // Constructor to initialize CC_ImGui object with a CyberCore window
        CC_ImGui(CyberCore::CC_Window& window);
        
        // Methods for different ImGui windows
        // void _InspectorWindow();   // Contains the inspector side panel. A list of a (selected) GameObject or asset
        // void _ProjectWindow();     // Project window. List of the assets, sceneces, and script in the working porject.  
        // void _HierarchyWindow();   // Hierarchy window. A list of the GameObejcts in the current Scene.
        // void _SceneWindow();       // Scene window. This is the main work area for the editor

        // Method to create a dock space window with a specified toolbar height
        // this is control the 4 main ImGui windows 
        void CreateDockSpaceWindow(float toolBarHeight);

        // Method to create a menu bar and return its height
        // responsible for settings 
        float _MenuBar();

        // Method to create a toolbar and return its height, given the menu bar height
        // responsible for play controls along with other tools to perform different actiosn on a selected obejct in Scene Window
        float _ToolBar(float menubarHeight);
        
    private:
        // Private method to initialize ImGui with a CyberCore window
        void init_ImGui(CyberCore::CC_Window& window);    
    };
}
