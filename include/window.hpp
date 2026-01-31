#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
  Window(int width, int height);
  ~Window();

  bool shouldClose() const { return glfwWindowShouldClose(m_window); };
  void swapBuffers() { glfwSwapBuffers(m_window); }
  void pollEvents() { glfwPollEvents(); }

  void processInput();

  GLFWwindow *native() const { return m_window; }

  void getSizeByRef(int &width, int &height) {
    glfwGetWindowSize(m_window, &width, &height);
  }

private:
  GLFWwindow *m_window = nullptr;
};
