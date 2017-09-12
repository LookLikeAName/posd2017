#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"

using namespace std;

const double epsilon = 0.000001;

TEST (Shapes, perimeterOfCircle) {
  Circle cir(0, 0, 12);
  ASSERT_NEAR((2 * M_PI * 12), cir.perimeter(), epsilon);
}
  
TEST (Shapes, perimeterOfRectangle) {
  Rectangle rect(0, 0, 8, 9);
  ASSERT_NEAR(34, rect.perimeter(), epsilon);
}

TEST (Shapes, createTriangle) {
  vertex vertex_1 = {1, 4};
  vertex vertex_2 = {2, 1};
  vertex vertex_3 = {4, 3};

  try {
    // This is a triangle
    Triangle tri(vertex_1, vertex_2, vertex_3);
    EXPECT_TRUE(true);
  } catch (std::string msg) {
    FAIL() << "It's a triangle.";
  }

  vertex vertex_4 = {1, 1};
  vertex vertex_5 = {2, 2};
  vertex vertex_6 = {3, 3};

  try {
    // This is not a triangle
    Triangle tri(vertex_4, vertex_5, vertex_6);
    FAIL() << "It's not a triangle.";
  } catch (std::string msg) {
    EXPECT_TRUE(msg == std::string("It's not a triangle."));
  }
}
  
TEST (Shapes, perimeterOfTriangle) {
  vertex vertex_1 = {1, 4};
  vertex vertex_2 = {2, 1};
  vertex vertex_3 = {4, 3};

  Triangle tri(vertex_1, vertex_2, vertex_3);

  ASSERT_NEAR(9.1529824, tri.perimeter(), epsilon);
}
  
TEST (Shapes, areaOfTriangle) {
  vertex vertex_1 = {1, 4};
  vertex vertex_2 = {2, 1};
  vertex vertex_3 = {4, 3};

  Triangle tri(vertex_1, vertex_2, vertex_3);
  ASSERT_NEAR(4, tri.area(), epsilon);
}

TEST (Shapes, sumOfPerimetersOfaNumberOfShapes) {
  Circle cir(2, 7, 11);
  Rectangle rect(3, 8, 12, 21);
  Triangle tri({1, 1}, {3, 1}, {3, 4});

  std::vector<Shape *> shapes;
  shapes.push_back(&cir);
  shapes.push_back(&rect);
  shapes.push_back(&tri);

  ASSERT_NEAR(143.7205896, sumOfPerimeter(shapes), epsilon);
}


TEST (Media, addShapeMediaIntoComboMedia) {
  Triangle t1({0, 0}, {-1, 1.732}, {0, 3.464});
  Rectangle r1(0, 3.464, 3.464, 2);
  Triangle t2({2, 0}, {3, 1.732}, {2, 3.464});

  ShapeMedia smT1(&t1);
  ShapeMedia smR1(&r1);
  ShapeMedia smT2(&t2);

  ComboMedia cb1;
  ComboMedia cb2;

  cb1.add(&smT1);
  cb1.add(&smR1);

  cb2.add(&cb1);
  cb2.add(&smT2);

  ASSERT_NEAR(10.392, cb2.area(), epsilon);
  ASSERT_NEAR(25.855824, cb2.perimeter(), epsilon);
}

#endif
