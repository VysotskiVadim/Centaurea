#include "game.h"
#include "glwrapper.h"
#include <iostream>

using Cenraurea::Common::Game::Game;

const char* _vertexSource = R"glsl(#version 300 es
in vec2 position;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";

const GLchar *_fragmentShader = R"glsl(#version 300 es
precision mediump float;
out vec4 outColor;
void main()
{
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
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

    GLfloat vertices[] = {
            0.0f,  0.5f, // Vertex 1 (X, Y)
            0.5f, -0.5f, // Vertex 2 (X, Y)
            -0.5f, -0.5f  // Vertex 3 (X, Y)
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(_shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(posAttrib);
}

void Game::on_surface_changed(void) {
    // No-op
}

void Game::on_draw_frame(void) {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

