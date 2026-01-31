#include "shader.hpp"
#include <GL/glext.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

std::string loadShader(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    throw std::runtime_error("Failure: Unable to open shader file: " + path);

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

unsigned int Shader::compile(unsigned int type, const char *src) {
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(shader, 512, NULL, log);
    std::cerr << "Failed to compile shader: " << log << std::endl;
    throw std::runtime_error("Failed to compile shader");
  }
  return shader;
}

Shader::Shader() {
  unsigned int vertexShader =
      compile(GL_VERTEX_SHADER, loadShader("shaders/vertex.glsl").c_str());
  unsigned int fragmentShader =
      compile(GL_FRAGMENT_SHADER, loadShader("shaders/fragment.glsl").c_str());

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(shaderProgram, 512, NULL, log);
    std::cerr << "Failed to link shader program: " << log << std::endl;
    throw std::runtime_error("Failed to link shader program");
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() {
  if (shaderProgram)
    glDeleteProgram(shaderProgram);
}

void Shader::use() const { glUseProgram(shaderProgram); }

void Shader::setFloat1f(const char *name, float value) const {
  glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setFloat4f(const char *name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(shaderProgram, name), x, y, z, w);
}
