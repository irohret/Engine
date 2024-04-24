#include "CC_Shader.hpp"

namespace CyberCore {

    unsigned int CC_Shader::load(unsigned int shaderType, const std::string& shaderSRC){
        unsigned int shaderProgramId = glCreateShader(shaderType);

        const char* src = shaderSRC.c_str();
        glShaderSource(shaderProgramId, 1, &src, nullptr);
        glCompileShader(shaderProgramId);

        GLint result;
        glGetShaderiv(shaderProgramId, GL_COMPILE_STATUS, &result);

        if(result == GL_FALSE){
            int length;
            glGetShaderiv(shaderProgramId, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> message(length);
            glGetShaderInfoLog(shaderProgramId, length, &length, &message[0]);
            std::cerr << "Failed to compile shader: " << message.data() << std::endl;
            glDeleteShader(shaderProgramId);
            return 0;
        }

        return shaderProgramId;
    }

    bool CC_Shader::createShader(const std::string& VertexShader, const std::string& fragmentShader){
        std::ifstream inputVS(VertexShader);
        std::ifstream inputFS(fragmentShader);

        const std::string f_vs((std::istreambuf_iterator<char>(inputVS)), std::istreambuf_iterator<char>());
        const std::string f_fs((std::istreambuf_iterator<char>(inputFS)), std::istreambuf_iterator<char>());

        shaderID = glCreateProgram();

        unsigned int vs = load(GL_VERTEX_SHADER, f_vs);
		unsigned int fs = load(GL_FRAGMENT_SHADER, f_fs);

        glAttachShader(shaderID, vs);
        glAttachShader(shaderID, fs);

        glLinkProgram(shaderID);
        glValidateProgram(shaderID);

        glDeleteShader(vs);
        glDeleteShader(fs);
        return true;
    }

    void CC_Shader::useShader(){
        glUseProgram(shaderID);
    }

    void CC_Shader::deleteShader(){
        glDeleteProgram(shaderID);
    }

    
    void CC_Shader::setMat4(const glm::mat4& mat4, const std::string& src) {
        GLint shaderLocation = glGetUniformLocation(getShaderID(), src.c_str());
        glUniformMatrix4fv(shaderLocation, 1, GL_FALSE, glm::value_ptr(mat4));
    }

    
    void CC_Shader::setVec3(const glm::vec3& vec3, const std::string& src){
        GLint shaderLocation = glGetUniformLocation(getShaderID(), src.c_str());
        glUniformMatrix4fv(shaderLocation, 1, GL_FALSE, glm::value_ptr(vec3));
    }


    void CC_Shader::setVec4(const glm::vec3& vec3, const std::string& src) {
        GLint shaderLocation = glGetUniformLocation(getShaderID(), src.c_str());
        glUniformMatrix4fv(shaderLocation, 1, GL_FALSE, glm::value_ptr(vec3));
    }
}