#include <glad/glad.h>
#include "renderer.hpp"

Renderer::Renderer(int viewPX, int viewPY, int viewPWidth, int viewPHeight) {
  glViewport(viewPX, viewPY, viewPWidth, viewPHeight);
}

Renderer::~Renderer() {}

void Renderer::drawArrays(unsigned int VAO, int vertexCount,
                          GLenum mode) const {
  glBindVertexArray(VAO);
  glDrawArrays(mode, 0, vertexCount);
}

void Renderer::drawElements(unsigned int VAO, int elementCount,
                            GLenum mode) const {
  glBindVertexArray(VAO);
  glDrawElements(mode, elementCount, GL_UNSIGNED_INT, 0);
}

void Renderer::clear(float r, float g, float b, float a) const {
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}
