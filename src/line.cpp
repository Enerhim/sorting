#include "line.hpp"
#include <vector>
#include <cmath>

std::vector<float> Line::calculateVertices(float x1, float y1, float x2,
                                           float y2, float width) {
  float r = width / 2;

  float meanA = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  // Calculating point A+
  float x1_ = x1 + (r * (-y2 + y1) / meanA);
  float y1_ = y1 + (r * (x2 - x1) / meanA);

  // Calculating point A-
  float x2_ = x1 - (r * (-y2 + y1) / meanA);
  float y2_ = y1 - (r * (x2 - x1) / meanA);

  // Calculating point B+
  float x3_ = x2 + (r * (-y2 + y1) / meanA);
  float y3_ = y2 + (r * (x2 - x1) / meanA);

  // Calculating point B-
  float x4_ = x2 - (r * (-y2 + y1) / meanA);
  float y4_ = y2 - (r * (x2 - x1) / meanA);

  return std::vector<float>{
      x3_, y3_, 0.0f, // Top Right / B+
      x4_, y4_, 0.0f, // Bottom Right / B-
      x2_, y2_, 0.0f, // Bottom Left / A-
      x1_, y1_, 0.0f, // Top Left / A+
  };
}

Line::Line(float x1, float y1, float x2, float y2, float width,
           std::vector<float> color)
    : Polygon(calculateVertices(x1, y1, x2, y2, width), color,
              {0, 1, 2, 2, 3, 0}, GL_STATIC_DRAW) {
  m_A = {x1, y1};
  m_B = {x2, y2};
  m_width = width;
}
