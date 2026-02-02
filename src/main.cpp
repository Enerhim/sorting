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

  std::vector<int64_t> list = {-5, 4,  6, 7,  8, 9,  10, 5,  20,
                               30, 13, 5, -6, 7, -8, -7, 10, 44};
  uint64_t i = list.size() - 1;

  std::vector<Line> lines;
  lines.reserve(list.size());

  int64_t max_ = *std::max_element(list.begin(), list.end());
  int64_t min_ = *std::min_element(list.begin(), list.end());

  std::cout << "Minimum: " << min_ << std::endl;
  std::cout << "Maximum: " << max_ << std::endl;

  std::vector<float> defcolor = {1.0f, 1.0f, 1.0f};
  std::vector<float> currentColor = {0.0f, 1.0f, 0.0f};

  float spacing = 1.8f / list.size(); // Total width of 1.8 (from -0.9 to 0.9)
  float lineWidth =
      spacing * 0.8f; // 80% of spacing for line width, 20% for gaps

  for (uint64_t k = 0; k < list.size(); k++) {
    float xPos =
        spacing * k - 0.9f + spacing / 2.0f; // Center each line in its space
    lines.emplace_back(xPos, -((float)(list[k] - min_) / (max_ - min_)) * 0.5,
                       xPos, 0.9f, lineWidth, defcolor);
  }

  uint64_t current = list.size() - 1;

  while (!window.shouldClose()) {
    window.processInput();

    renderer.clear(0.0f, 0.1f, 0.2f, 1.0f);
    shader.use();

    if (i > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(400));
      i = selectionSort(list, i, current);
      printList(list);
    } else {
      defcolor = {0.0f, 1.0f, 0.0f};
    }

    for (uint64_t k = 0; k < list.size(); k++) {
      float xPos = spacing * k - 0.9f + spacing / 2.0f;
      lines[k].updateEndpoints(xPos,
                               -((float)(list[k] - min_) / (max_ - min_)) * 0.5,
                               xPos, 0.9f, defcolor);
    }
    float xPos = spacing * current - 0.9f + spacing / 2.0f;
    lines[current].updateEndpoints(
        xPos, -((float)(list[current] - min_) / (max_ - min_)) * 0.5, xPos,
        0.9f, currentColor);

    // Fix stretching and squishing
    int width, height;
    window.getSizeByRef(width, height);

    float aspect = (height > 0) ? (float)width / height : 1.0f;
    shader.setFloat1f("u_aspect", aspect);

    for (auto &line : lines) {
      renderer.drawElements(line.getVAO(), line.getIndices().size());
    }

    window.swapBuffers();
    window.pollEvents();
  }
  return 0;
}
