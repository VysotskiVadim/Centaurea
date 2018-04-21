#include "game.h"
#include "glwrapper.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using Cenraurea::Common::Game::Game;

const char* _vertexSource = R"glsl(#version 300 es
in vec2 textureCoordinates;
in vec2 position;
in vec3 color;

out vec3 Color;
out vec2 TextureCoordinates;

uniform mat4 trans;

void main()
{
    gl_Position = trans * vec4(position, 0.0, 1.0);
    Color = color;
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
    vec4 colKitten = texture(texKitten, TextureCoordinates);
    vec4 colPuppy = texture(texPuppy, TextureCoordinates);
    outColor = mix(colKitten, colPuppy, 0.5);
}
)glsl";


bool Game::setupShaders(void) {
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

void Game::on_surface_created(void) {

    if (!setupShaders()) {
        return;
    }

    float vertices[] = {
        //  Position      Color             Texcoords
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
            0, 1, 2,
            2, 3, 0
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLint positionAttribute = glGetAttribLocation(_shaderProgram, "position");
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);

    GLuint colorAttribute = glGetAttribLocation(_shaderProgram, "color");
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));

    GLint textureCoordinatesAttribute = glGetAttribLocation(_shaderProgram, "textureCoordinates");
    glEnableVertexAttribArray(textureCoordinatesAttribute);
    glVertexAttribPointer(textureCoordinatesAttribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));

    GLuint textures[2];
    glGenTextures(2, textures);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    _textureLoader->loadTexture("logo");
    glUniform1i(glGetUniformLocation(_shaderProgram, "texKitten"), 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    _textureLoader->loadTexture("logo2");
    glUniform1i(glGetUniformLocation(_shaderProgram, "texPuppy"), 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    _startTime = std::chrono::high_resolution_clock::now();
    
}

void Game::on_surface_changed(void) {
    // No-op
}

void Game::on_draw_frame(void) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - _startTime).count();
    
    glm::mat4 trans;
    trans = glm::rotate(
                        trans,
                        time * glm::radians(180.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                        );
    
    GLint uniTrans = glGetUniformLocation(_shaderProgram, "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Game::Game(std::shared_ptr<ITextureLoader> textureLoader)
    : _textureLoader(textureLoader)
{
}
