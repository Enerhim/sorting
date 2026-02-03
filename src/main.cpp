#include "shader.hpp"
#include "renderer.hpp"
#include "window.hpp"

#include "line.hpp"
#include "sort.hpp"

#include <iostream>
#include <algorithm>

#include <thread>
#include <chrono>
#include <random>

int random_int(int low, int high) {
  static std::random_device rd;
  static std::mt19937 gen(rd()); // Mersenne Twister
  std::uniform_int_distribution<int> dist(low, high);
  return dist(gen);
}

int main() {
  Window window(1600, 900);
  Shader shader;

  int width, height;
  window.getSizeByRef(width, height);
  Renderer renderer(0, 0, width, height);

  std::vector<int64_t> list;
  list.resize(50);

  for (uint64_t k = 0; k < list.size(); k++) {
    list[k] = random_int(-500, 500);
  }

  uint64_t i = list.size() - 1;

  std::vector<Line> lines;
  lines.reserve(list.size());

  int64_t max_ = *std::max_element(list.begin(), list.end());
  int64_t min_ = *std::min_element(list.begin(), list.end());

  std::vector<float> defcolor = {1.0f, 1.0f, 1.0f};
  std::vector<float> currentColor = {0.0f, 1.0f, 0.0f};

  float spacing = 1.8f / list.size();
  float lineWidth = spacing * 0.8f;

  for (uint64_t k = 0; k < list.size(); k++) {
    float xPos = spacing * k - 0.9f + spacing / 2.0f;
    lines.emplace_back(xPos, -((float)(list[k] - min_) / (max_ - min_)) * 0.5,
                       xPos, 0.9f, lineWidth, defcolor);
  }

  uint64_t current = list.size() - 1;

  while (!window.shouldClose()) {
    window.processInput();

    renderer.clear(0.0f, 0.1f, 0.2f, 1.0f);
    shader.use();

    if (i > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      i = selectionSort(list, i, current);

      for (uint64_t k = 0; k < list.size(); k++) {
        float xPos = spacing * k - 0.9f + spacing / 2.0f;
        lines[k].updateEndpoints(
            xPos, -((float)(list[k] - min_) / (max_ - min_)) * 0.5, xPos, 0.9f,
            defcolor);
      }
      float xPos = spacing * current - 0.9f + spacing / 2.0f;
      lines[current].updateEndpoints(
          xPos, -((float)(list[current] - min_) / (max_ - min_)) * 0.5, xPos,
          0.9f, currentColor);

    } else {
      for (uint64_t k = 0; k < list.size(); k++) {
        std::vector<float> A = lines[k].getA();
        std::vector<float> B = lines[k].getB();
        lines[k].updateEndpoints(A[0], A[1], B[0], B[1], {0.0f, 1.0f, 0.0f});
      }
    }

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
