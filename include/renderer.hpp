#pragma once
#include <glad/glad.h>

class Renderer {
public:
  Renderer(int viewpX, int viewPY, int viewPWidth, int viewPHeight);
  ~Renderer();

  void drawArrays(unsigned int VAO, int vertexCount,
                  GLenum mode = GL_TRIANGLES) const;
  void drawElements(unsigned int VAO, int elementCount,
                    GLenum mode = GL_TRIANGLES) const;
  void clear(float r, float g, float b, float a) const;

private:
};
