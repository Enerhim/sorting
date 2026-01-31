#include "polygon.hpp"

Polygon::Polygon(std::vector<float> vertices, std::vector<float> color,
                 std::vector<unsigned int> indices, GLenum drawMode) {
  m_vertices = vertices;
  m_indices = indices;
  m_color = color;
  colorVertices();

  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);
  glGenVertexArrays(1, &m_VAO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  glBufferData(GL_ARRAY_BUFFER, m_colored_vertices.size() * sizeof(float),
               m_colored_vertices.data(), drawMode);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
               m_indices.data(), drawMode);

  // Position Data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Color Data
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(m_VAO);
}

Polygon::~Polygon() {
  if (m_VBO != 0) {
    glDeleteBuffers(1, &m_VBO);
  }
  if (m_EBO != 0) {
    glDeleteBuffers(1, &m_EBO);
  }
  if (m_VAO != 0) {
    glDeleteVertexArrays(1, &m_VAO);
  }
}

void Polygon::colorVertices() {
  m_colored_vertices.resize(m_vertices.size());
  m_colored_vertices = m_vertices;

  for (size_t i = 3; i < m_vertices.size() * 2; i += 6) {
    m_colored_vertices.insert(m_colored_vertices.begin() + i, m_color.begin(),
                              m_color.end());
  }
}
