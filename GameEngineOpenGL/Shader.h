#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    GLuint getID() const;

private:
    GLuint programID;

    std::string readFile(const std::string& filePath) const;
    GLuint compileShader(const std::string& source, GLenum shaderType) const;
};

#endif // SHADER_H
