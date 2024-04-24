#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdio.h>


#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool rightMouseButtonPressed = false;
glm::mat4 projection;
float fov = 45.0f;
static glm::vec3 scaleValue = glm::vec3(1.0f);

#define WEIGHT 800
#define HEIGHT 600
// Vertex Shader source code
const char* vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 aTexCoord; // new texture coordinate attribute
	out vec2 TexCoord; // pass texture coordinates to fragment shader

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main() {
		// Apply transformations directly to the vertex position
		vec4 worldPosition = model * vec4(aPos, 1.0);
		gl_Position = projection * view * worldPosition;
		TexCoord = aTexCoord;
	}

)";

// Fragment Shader source code
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
	in vec2 TexCoord; 				// received from vertex shader
	uniform sampler2D texture1; 	// texture sampler
    void main() {
        //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		FragColor = texture(texture1, TexCoord);
    }
)";

void test(){
    ImGui::Begin("Test");
    ImGui::End();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Adjust width and height to ensure a padding of 100 pixels
    int padding = 100;
    width -= padding * 2;
    height -= padding * 2;

    // Prevent division by zero
    if (height == 0)
        height = 1;

    // Calculate the new aspect ratio
    float aspectRatio = static_cast<float>(width) / height;

    // Calculate the new projection matrix with the adjusted aspect ratio
    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);

    // Set the viewport with the padding
    glViewport(padding, padding, width, height);
}

// Transform stuff
void transformID(GLFWwindow* window, glm::mat4 &model);
void scaleControl();
void positionControl();
void positionControl(glm::mat4& model);
void resetTransformation(glm::mat4& model);


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

float zoomLevel = 1.0f;
static float rotationAngleX = 0.0f;
static float rotationAngleY = 0.0f;
static float rotationAngleZ = 0.0f;


void CamControl(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp) {
    // Camera control variables
    float cameraSpeed = 0.05f;
	
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            rightMouseButtonPressed = true;
            std::cout << "Right mouse button pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE) {
            rightMouseButtonPressed = false;
            std::cout << "Right mouse button released" << std::endl;
        }
    }
}

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WEIGHT, HEIGHT, "Object Selection and Transformation", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Compile and link vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    // Compile and link fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    // Create shader program and link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for shader program linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program linking failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers
    float vertices[] = {
		// positions         // texture coords
		-0.5f, -0.5f,  0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
        // back face
        -0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f,  
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        1, 5, 6,
        6, 2, 1,
        0, 4, 7,
        7, 3, 0,
        3, 2, 6,
        6, 7, 3,
        0, 1, 5,
        5, 4, 0
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    {
	const char *path = "CyberCoreEngine/src/assets/texture/pixel.png";

	// Texture
	GLuint textureID;
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data) {
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // Bind texture unit 0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }

    // Transformation variables
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 modelScale = glm::mat4(1.0f);
    glm::mat4 modelRotation = glm::mat4(1.0f);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // ImGui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // ImGui::Begin("ImGui Window");

        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        ImVec2 renderTargetMin = windowPos;
        ImVec2 renderTargetMax = ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y);
        ImGui::GetWindowDrawList()->AddRectFilled(renderTargetMin, renderTargetMax, IM_COL32(0, 0, 0, 255));
        
        transformID(window, model);

        // Camera control variables
        static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        float cameraSpeed = 0.05f;

        if (rightMouseButtonPressed) {
            CamControl(window, cameraPos, cameraFront, cameraUp);
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        }

        // Rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update transformation matrix
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

		// render the cube
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Terminate GLFW
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


/*

     std::vector<float> Vertices(_vertices, _vertices + sizeof(_vertices) / sizeof(_vertices[0]));
       std::vector<unsigned int> Indices(_indices, _indices + sizeof(_indices) / sizeof(_indices[0]));


        CyberCore::VertexIndexBuffer vBuffer;

        vBuffer.createBuffer(Vertices, Indices);
        vBuffer.draw(36);
*/