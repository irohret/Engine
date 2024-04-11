#include "../../CyberCore/src/config.h"

int main(void) {
    CyberCore::CC_Window window(WIDTH, HEIGHT, "CyberCore");
    CyberCore::CC_ImGui CC_ImGui(window);

    // Main loop
    while (!glfwWindowShouldClose(window.getWindow())) {
        // Poll and handle events
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create the toolbar at the top
        float menuBarHeight = CC_ImGui._MenuBar();
        menuBarHeight += 4;
        float toolBarHeight = CC_ImGui._ToolBar(menuBarHeight);
        toolBarHeight = 0;

        // // Create and dock the dockspace window
        CC_ImGui.CreateDockSpaceWindow(toolBarHeight + 20);

        //CC_ImGui._ProjectWindow();

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window.getWindow());
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}