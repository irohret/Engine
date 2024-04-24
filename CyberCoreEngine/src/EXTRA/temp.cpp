
#include "../../CyberCore/Core/CC_PrimitiveShape.hpp"
#include "../../CyberCore/src/config.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

#include <iostream>


void _HierarchyWindow(CyberCore::CC_PrimitiveShape& primitiveShape);
void _scene();
void addObject(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 600, "OpenGL Cube", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

 	CyberCore::CC_PrimitiveShape primitiveShape(PrimitiveType::CUBE);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		_HierarchyWindow(primitiveShape);
		_scene();

		

        // Render the cube
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        
		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void _HierarchyWindow(CyberCore::CC_PrimitiveShape& primitiveShape) {
	ImVec2 minSize(200, 400);
	ImGui::SetNextWindowSizeConstraints(minSize, ImVec2(FLT_MAX, FLT_MAX));

	ImGui::Begin("Hierarchy", nullptr);


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
				// send to senve window to rendber
				//primitiveShape.createShape(PrimitiveType::CUBE);
				// CyberCore::CC_PrimitiveShape.createShape(PrimitiveType::CUBE);
				// std::vector<unsigned int> indices = primitiveShape.getIndices();
				// for (unsigned int index : indices) {
				// 	std::cout << index << " ";
				// }
				// std::cout << std::endl;

			}
			if (ImGui::MenuItem("Sphere")) {
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


void _scene(){
	ImGui::Begin("scene", nullptr);
	ImGui::BeginChild("test");

	ImGui::EndChild();
	ImGui::End();
}

void addObject(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
	// Store the vertices and indices of the cube
	// Render the cube in the scene panel using the provided vertices and indices
	GLuint VBO, VAO, EBO;

	// Create Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Create an Element Buffer Object and copy the index data to it
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind the VAO (Vertex Array Object)
	glBindVertexArray(VAO);

	// Render the cube
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

// 	// Cleanup
// 	glDeleteVertexArrays(1, &VAO);
// 	glDeleteBuffers(1, &VBO);
// 	glDeleteBuffers(1, &EBO);
}
