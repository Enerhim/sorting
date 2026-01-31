#pragma once
#include "polygon.hpp"
#include <vector>
#include <glad/glad.h>

class Line : public Polygon {
public:
  Line(float x1, float y1, float x2, float y2, float width,
       std::vector<float> color);

private:
  std::vector<float> m_A, m_B;
  float m_width;
  std::vector<float> calculateVertices(float x1, float y1, float x2, float y2,
                                       float width);
};
