//
// Created by Marcos Oliveira <mhco@cin.ufpe.br> on 10/22/2023.
// Copyright (c) 2023 RobôCIn.
//

#include "robocin/geometry/point2d.h"
#include "robocin/geometry/rect2d.h"

#include <gtest/gtest.h>
#include <utility>

namespace robocin {

namespace {
using ::testing::Test;
using ::testing::Types;

template <class T>
class Rect2DTest : public Test {};

using TestTypes = Types<std::int16_t, std::int32_t, std::int64_t, float, double, long double>;
TYPED_TEST_SUITE(Rect2DTest, TestTypes);

// Static constructors -----------------------------------------------------------------------------

TYPED_TEST(Rect2DTest, Create) {
  const Rect2D<TypeParam> kRect = Rect2D<TypeParam>::create();

  EXPECT_EQ(kRect.top_left.x, 0);
  EXPECT_EQ(kRect.top_left.y, 0);
  EXPECT_EQ(kRect.width, 0);
  EXPECT_EQ(kRect.height, 0);
}

// Constructors ------------------------------------------------------------------------------------
TYPED_TEST(Rect2DTest, DefaultConstructor) {
  const Rect2D<TypeParam> kRect{};

  EXPECT_EQ(kRect.top_left.x, 0);
  EXPECT_EQ(kRect.top_left.y, 0);
  EXPECT_EQ(kRect.width, 0);
  EXPECT_EQ(kRect.height, 0);
}

TYPED_TEST(Rect2DTest, CopyConstructor) {
  const Rect2D<TypeParam> kOther(Point2D<TypeParam>(/*x*/ 1, /*y*/ 2), 30, 40);
  const Rect2D<TypeParam> kRect(kOther);

  EXPECT_EQ(kRect.top_left.x, 1);
  EXPECT_EQ(kRect.top_left.y, 2);
  EXPECT_EQ(kRect.width, 30);
  EXPECT_EQ(kRect.height, 40);
}

TYPED_TEST(Rect2DTest, MoveConstructor) {
  const Rect2D<TypeParam> kOther(Point2D<TypeParam>(/*x*/ 1, /*y*/ 2), 30, 40);
  const Rect2D<TypeParam> kRect(std::move(kOther));

  EXPECT_EQ(kRect.top_left.x, 1);
  EXPECT_EQ(kRect.top_left.y, 2);
  EXPECT_EQ(kRect.width, 30);
  EXPECT_EQ(kRect.height, 40);
}

TYPED_TEST(Rect2DTest, ConstructorGivenParams) {
  const Rect2D<TypeParam> kRect(Point2D<TypeParam>(/*x*/ 1, /*y*/ 2), 30, 40);

  EXPECT_EQ(kRect.top_left.x, 1);
  EXPECT_EQ(kRect.top_left.y, 2);
  EXPECT_EQ(kRect.width, 30);
  EXPECT_EQ(kRect.height, 40);
}

TYPED_TEST(Rect2DTest, ConstructorGivenTopAndBottom) {
  const Rect2D<TypeParam> kRect(Point2D<TypeParam>(/*x*/ 10, /*y*/ 0),
                                Point2D<TypeParam>(/*x*/ 110, /*y*/ 100));

  EXPECT_EQ(kRect.top_left.x, 10);
  EXPECT_EQ(kRect.top_left.y, 0);
  EXPECT_EQ(kRect.width, 100);
  EXPECT_EQ(kRect.height, 100);
}

TYPED_TEST(Rect2DTest, MoveConstructorGivenTopAndBottom) {
  const Rect2D<TypeParam> kOther(Point2D<TypeParam>(/*x*/ 10, /*y*/ 0),
                                 Point2D<TypeParam>(/*x*/ 110, /*y*/ 100));
  const Rect2D<TypeParam> kRect(std::move(kOther));

  EXPECT_EQ(kRect.top_left.x, 10);
  EXPECT_EQ(kRect.top_left.y, 0);
  EXPECT_EQ(kRect.width, 100);
  EXPECT_EQ(kRect.height, 100);
}

TYPED_TEST(Rect2DTest, ConstructorGivenStructRect) {
  struct SomePairStruct {
    TypeParam x;
    TypeParam y;
  };

  struct OtherRect2D {

    SomePairStruct top_left;
    TypeParam width;
    TypeParam height;
  };

  const OtherRect2D kOtherRect2d{.top_left = SomePairStruct{.x = 0, .y = 1},
                                 .width = 10,
                                 .height = 20};
  const Rect2D<TypeParam> kRect(kOtherRect2d);

  EXPECT_EQ(kRect.top_left.x, 0);
  EXPECT_EQ(kRect.top_left.y, 1);
  EXPECT_EQ(kRect.width, 10);
  EXPECT_EQ(kRect.height, 20);
}

// Validators --------------------------------------------------------------------------------------

TYPED_TEST(Rect2DTest, IsNull) {
  const Rect2D<TypeParam> kRect(Point2D<TypeParam>(/*x*/ 0, /*y*/ 0), 0, 0);
  EXPECT_TRUE(kRect.isNull());

  const Rect2D<TypeParam> kRect2(Point2D<TypeParam>(/*x*/ 1, /*y*/ 2), 30, 40);
  EXPECT_FALSE(kRect2.isNull());
}

// Comparison operators --------------------------------------------------------------------------

TYPED_TEST(Rect2DTest, IsEq) {
  const Rect2D<TypeParam> kRect(Point2D<TypeParam>(/*x*/ 0, /*y*/ 0), 0, 0);
  EXPECT_TRUE(kRect == kRect);
  const Rect2D<TypeParam> kRect2(Point2D<TypeParam>(/*x*/ 1, /*y*/ 2), 30, 40);
  EXPECT_TRUE(kRect2 == kRect2);

  EXPECT_FALSE(kRect == kRect2);

  const Rect2D<TypeParam> kRect3(Point2D<TypeParam>(/*x*/ 0, /*y*/ 0), 0, 0);
  EXPECT_TRUE(kRect == kRect3);
}

TYPED_TEST(Rect2DTest, ContainsPoint) {
  const Rect2D<TypeParam> kRect(Point2D<TypeParam>(/*x*/ 0, /*y*/ 0), 10, 10);
  const Point2D<TypeParam> kPoint(/*x*/ 0, /*y*/ 0);
  EXPECT_TRUE(kRect.contains(kPoint));
  const Point2D<TypeParam> kPoint2(/*x*/ 11, /*y*/ 11);
  EXPECT_FALSE(kRect.contains(kPoint2));
}

TYPED_TEST(Rect2DTest, ContainsRect) {
  const Rect2D<TypeParam> kRect(Point2D<TypeParam>(/*x*/ 0, /*y*/ 0), 10, 10);
  const Rect2D<TypeParam> kRect2(Point2D<TypeParam>(/*x*/ 5, /*y*/ 5), 2, 2);
  EXPECT_TRUE(kRect.contains(kRect2));
  EXPECT_FALSE(kRect2.contains(kRect));
}

TYPED_TEST(Rect2DTest, Intersects) {
  const Rect2D<TypeParam> kRect(Point2D<TypeParam>(/*x*/ 0, /*y*/ 0), 10, 10);
  const Rect2D<TypeParam> kRect2(Point2D<TypeParam>(/*x*/ 5, /*y*/ 5), 2, 2);
  const Rect2D<TypeParam> kRect3(Point2D<TypeParam>(/*x*/ 10, /*y*/ 10), 10, 10);

  EXPECT_TRUE(kRect.intersects(kRect2) == kRect2.intersects(kRect));

  EXPECT_TRUE(kRect.intersects(kRect2));
  EXPECT_TRUE(kRect.intersects(kRect3));
  EXPECT_FALSE(kRect3.intersects(kRect2));
}

// Swap --------------------------------------------------------------------------------------------

TYPED_TEST(Rect2DTest, Swapping) {
  Rect2D<TypeParam> rect1(Point2D<TypeParam>(/*x*/ 1, /*y*/ 2), 30, 40);
  Rect2D<TypeParam> rect2(Point2D<TypeParam>(/*x*/ 2, /*y*/ 3), 45, 20);

  rect1.swap(rect2);

  EXPECT_EQ(rect1.top_left.x, 2);
  EXPECT_EQ(rect1.top_left.y, 3);
  EXPECT_EQ(rect1.width, 45);
  EXPECT_EQ(rect1.height, 20);
  EXPECT_EQ(rect2.top_left.x, 1);
  EXPECT_EQ(rect2.top_left.y, 2);
  EXPECT_EQ(rect2.width, 30);
  EXPECT_EQ(rect2.height, 40);
}

} // namespace
} // namespace robocin
