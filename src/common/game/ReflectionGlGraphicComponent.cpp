#include "ReflectionGlGraphicComponent.h"

#include <iostream>
#include "glwrapper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* _vertexSource = R"glsl(#version 300 es
in vec2 textureCoordinates;
in vec3 position;
in vec3 color;

out vec3 Color;
out vec2 TextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 overrideColor;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
    Color = overrideColor * color;
    TextureCoordinates = textureCoordinates;
}
)glsl";

const GLchar *_fragmentShader = R"glsl(#version 300 es
precision mediump float;
in vec3 Color;
in vec2 TextureCoordinates;
out vec4 outColor;
uniform sampler2D texKitten;
uniform sampler2D texPuppy;
void main()
{
    outColor = vec4(Color, 1.0) * mix(texture(texKitten, TextureCoordinates), texture(texPuppy, TextureCoordinates), 0.5);
}
)glsl";

using namespace Cenraurea::Common::GameEngine;

ReflectionGlGraphicComponent::ReflectionGlGraphicComponent(std::shared_ptr<Game> game)
:_game(game),
_textureLoader(game->textureLoader)
{}

bool ReflectionGlGraphicComponent::setupShaders(void) {
    GLint  success;
    char infoLog[512];
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &_vertexSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &_fragmentShader, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::GLPROGRAMM::LINK_FAILED\n" << infoLog << std::endl;
        return false;
    }
    glUseProgram(_shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void ReflectionGlGraphicComponent::update(float elapsed) {
    setupSizes();
    
    _rotationAngle += elapsed / 1000 * glm::radians(180.0f);
    glm::mat4 modelMatrix;
    modelMatrix = glm::rotate(
                              modelMatrix,
                              _rotationAngle,
                              glm::vec3(0.0f, 0.0f, 1.0f)
                              );
    
    GLint uniModel = glGetUniformLocation(_shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    
    GLint uniColor = glGetUniformLocation(_shaderProgram, "overrideColor");
    glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glEnable(GL_STENCIL_TEST);
    // Draw floor
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF); // Write to stencil buffer
    glDepthMask(GL_FALSE); // Don't write to depth buffer
    glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)
    glDrawArrays(GL_TRIANGLES, 36, 6);
    
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDepthMask(GL_TRUE);
    modelMatrix = glm::scale(
                             glm::translate(modelMatrix, glm::vec3(0, 0, -1)),
                             glm::vec3(1, 1, -1)
                             );
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glDisable(GL_STENCIL_TEST);
    
}

void ReflectionGlGraphicComponent::initialize() {
    
    if (!setupShaders()) {
        return;
    }
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        
        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };
    int rowSize = 8 * sizeof(GLfloat);
    
    glGenBuffers(1, &_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLint positionAttribute = glGetAttribLocation(_shaderProgram, "position");
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, rowSize, 0);
    
    GLuint colorAttribute = glGetAttribLocation(_shaderProgram, "color");
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, rowSize, (void*)(3*sizeof(float)));
    
    GLint textureCoordinatesAttribute = glGetAttribLocation(_shaderProgram, "textureCoordinates");
    glEnableVertexAttribArray(textureCoordinatesAttribute);
    glVertexAttribPointer(textureCoordinatesAttribute, 2, GL_FLOAT, GL_FALSE, rowSize, (void*)(6*sizeof(float)));
    
    glGenTextures(TEXTURE_COUNT, _textures);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textures[0]);
    _textureLoader->loadTexture("logo");
    glUniform1i(glGetUniformLocation(_shaderProgram, "texKitten"), 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _textures[1]);
    _textureLoader->loadTexture("logo2");
    glUniform1i(glGetUniformLocation(_shaderProgram, "texPuppy"), 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ReflectionGlGraphicComponent::setupSizes() {
        glm::mat4 view = glm::lookAt(
                                     glm::vec3(3.5f, 3.5f, 3.0f),
                                     glm::vec3(0.0f, 0.0f, 0.0f),
                                     glm::vec3(0.0f, 0.0f, 1.0f)
                                     );
        GLint uniView = glGetUniformLocation(_shaderProgram, "view");
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
    
        float_t screenRatio = ((float_t)_game->screen.size.width) / _game->screen.size.height;
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), screenRatio, 1.0f, 10.0f);
        GLint uniProj = glGetUniformLocation(_shaderProgram, "proj");
        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

void ReflectionGlGraphicComponent::dispose() {
    glDeleteTextures(TEXTURE_COUNT, _textures);
    glDeleteProgram(_shaderProgram);
    glDeleteBuffers(1, &_vertexBufferObject);
}
