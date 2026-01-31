#include <iostream>
#include "shader.hpp"
#include "renderer.hpp"
#include "window.hpp"

#include "line.hpp"

int main() {

  Window window(1600, 900);
  Shader shader;

  int width, height;
  window.getSizeByRef(width, height);
  Renderer renderer(0, 0, width, height);

  // Line line(-0.5f, 0.4f, 0.5f, 0.0f, 0.1f, {0.0f, 0.0f, 1.0f});

  while (!window.shouldClose()) {
    window.processInput();

    renderer.clear(0.0f, 0.1f, 0.2f, 1.0f);
    shader.use();

    // Fix stretching and squishing
    int width, height;
    window.getSizeByRef(width, height);

    float aspect = (height > 0) ? (float)width / height : 1.0f;
    shader.setFloat1f("u_aspect", aspect);

    // renderer.drawElements(line.getVAO(), line.getIndices().size());

    window.swapBuffers();
    window.pollEvents();
  }
  return 0;
}
