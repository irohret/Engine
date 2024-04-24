#version 330 core

layout(location = 0) out vec4 color;

out vec4 FragColor;
in vec2 TexCoord; 				// received from vertex shader
uniform sampler2D texture1; 	// texture sampler

void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // FragColor = texture(texture1, TexCoord);
}