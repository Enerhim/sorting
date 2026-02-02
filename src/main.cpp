#include "shader.hpp"
#include "renderer.hpp"
#include "window.hpp"

#include "line.hpp"
#include "sort.hpp"

#include <iostream>
#include <algorithm>

#include <thread>
#include <chrono>

int main() {

  Window window(1600, 900);
  Shader shader;

  int width, height;
  window.getSizeByRef(width, height);
  Renderer renderer(0, 0, width, height);

  std::vector<int64_t> list = {-5, 4, 6, 7, 8, 9, 10, 5};
  uint64_t i = list.size() - 1;

  std::vector<Line> lines;
  lines.reserve(list.size());

  int64_t max_ = *std::max_element(list.begin(), list.end());
  int64_t min_ = *std::min_element(list.begin(), list.end());

  std::cout << "Minimum: " << min_ << std::endl;
  std::cout << "Maximum: " << max_ << std::endl;

  std::vector<float> defcolor = {1.0f, 1.0f, 1.0f};

  for (uint64_t k = 0; k < list.size(); k++) {
    lines.emplace_back(0.05f * (k) + -0.9,
                       -((float)(list[k] - min_) / (max_ - min_)) * 0.5,
                       0.05f * (k) + -0.9f, 0.9f, 0.04f, defcolor);
  }

  while (!window.shouldClose()) {
    window.processInput();

    renderer.clear(0.0f, 0.1f, 0.2f, 1.0f);
    shader.use();

    if (i > 0) {
      i = selectionSort(list, lines, i);
      printList(list);
    }

    for (uint64_t k = 0; k < list.size(); k++) {
      lines[k].updateEndpoints(0.05f * (k) + -0.9,
                               -((float)(list[k] - min_) / (max_ - min_)) * 0.5,
                               0.05f * (k) + -0.9f, 0.9f, defcolor);
    }
    // Fix stretching and squishing
    int width, height;
    window.getSizeByRef(width, height);

    float aspect = (height > 0) ? (float)width / height : 1.0f;
    shader.setFloat1f("u_aspect", aspect);

    for (auto &line : lines) {
      renderer.drawElements(line.getVAO(), line.getIndices().size());
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    window.swapBuffers();
    window.pollEvents();
  }
  return 0;
}
