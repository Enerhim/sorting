#include <glad/glad.h>
#include <stdexcept>
#include "window.hpp"

void resizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

Window::Window(int width, int height) {
  if (!glfwInit()) {
    throw std::runtime_error("Failure: Unable to initialize GLFW..");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, "Sorting", nullptr, nullptr);

  if (m_window == NULL) {
    throw std::runtime_error("Failure: Unable to create GLFW Window");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failure: Unable to initialize GLAD");
    glfwTerminate();
    exit(1);
  }

  glfwSetFramebufferSizeCallback(m_window, resizeCallback);
}

Window::~Window() {
  if (m_window) {
    glfwDestroyWindow(m_window);
  }
  glfwTerminate();
}

void Window::processInput() {
  if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(m_window, true);
  }
}
