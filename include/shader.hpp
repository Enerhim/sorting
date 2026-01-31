#pragma once
#include <glad/glad.h>

class Shader {
public:
  Shader();
  ~Shader();

  void use() const;
  void setFloat1f(const char *name, float value) const;
  void setFloat4f(const char *name, float x, float y, float z, float w);
  unsigned int id() const { return shaderProgram; }

private:
  unsigned int shaderProgram = 0;
  unsigned int compile(unsigned int type, const char *src);
};
