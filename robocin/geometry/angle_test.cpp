//
// Created by José Cruz <joseviccruz> on 15/04/23.
// Copyright (c) 2023 RobôCIn.
//

#include <ranges>

#include "robocin/geometry/angle.h"

#include <gtest/gtest.h>

#include "robocin/utility/internal/test/epsilon_injector.h"

namespace robocin {
namespace {

// NOLINTBEGIN(readability-function-cognitive-complexity)

using ::testing::Test;
using ::testing::Types;

using FloatingPointTestTypes = Types<float, double, long double>;

template <class>
class FloatingPointTest : public Test {};
TYPED_TEST_SUITE(FloatingPointTest, FloatingPointTestTypes);

// Static constructors -----------------------------------------------------------------------------
TYPED_TEST(FloatingPointTest, FromDegrees) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kTwoPiInDegrees = T{360};
  static constexpr T kDegreesToRadiansFactor = std::numbers::pi_v<T> / 180;

  for (const int kDegrees : std::ranges::iota_view{0, kTwoPiInDegrees}) {
    const Angle<T> kAngle = Angle<T>::fromDegrees(kDegrees);

    EXPECT_NEAR(static_cast<T>(kAngle), kDegrees * kDegreesToRadiansFactor, kEpsilon);
  }
}

// Constructors ------------------------------------------------------------------------------------
TYPED_TEST(FloatingPointTest, DefaultConstructor) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kZero = T{0};

  const Angle<T> kAngle;

  EXPECT_NEAR(static_cast<T>(kAngle), kZero, kEpsilon);
}

TYPED_TEST(FloatingPointTest, ConstructorGivenOtherFloatingPointAngle) {
  using T = TypeParam;

  if constexpr (not std::is_same_v<float, T>) {
    using U = common_floating_point_for_comparison_t<float, T>;

    static constexpr float kPi = std::numbers::pi_v<float>;
    static constexpr std::array kFloatAngles = {
        -kPi * 2,
        -kPi * 3 / 2,
        -kPi,
        -kPi / 2,
        0.0F,
        kPi / 2,
        kPi,
        kPi * 3 / 2,
        kPi * 2,
    };

    static constexpr float kEpsilon = epsilon_v<U>;

    for (const float kFloatAngle : kFloatAngles) {
      const Angle<T> kAngle = Angle<float>{kFloatAngle};

      EXPECT_NEAR(static_cast<U>(kAngle), static_cast<U>(kFloatAngle), kEpsilon);
    }
  }

  if constexpr (not std::is_same_v<double, T>) {
    using U = common_floating_point_for_comparison_t<double, T>;

    static constexpr double kPi = std::numbers::pi_v<double>;
    static constexpr std::array kDoubleAngles = {
        -kPi * 2,
        -kPi * 3 / 2,
        -kPi,
        -kPi / 2,
        0.0,
        kPi / 2,
        kPi,
        kPi * 3 / 2,
        kPi * 2,
    };

    static constexpr double kEpsilon = epsilon_v<U>;

    for (const double kDoubleAngle : kDoubleAngles) {
      const Angle<T> kAngle = Angle<double>{kDoubleAngle};

      EXPECT_NEAR(static_cast<U>(kAngle), static_cast<U>(kDoubleAngle), kEpsilon);
    }
  }

  if constexpr (not std::is_same_v<long double, T>) {
    using U = common_floating_point_for_comparison_t<long double, T>;

    static constexpr long double kPi = std::numbers::pi_v<long double>;
    static constexpr std::array kLongDoubleAngles = {
        -kPi * 2,
        -kPi * 3 / 2,
        -kPi,
        -kPi / 2,
        0.0L,
        kPi / 2,
        kPi,
        kPi * 3 / 2,
        kPi * 2,
    };

    static constexpr long double kEpsilon = epsilon_v<U>;

    for (const long double kLongDoubleAngle : kLongDoubleAngles) {
      const Angle<T> kAngle = Angle<long double>{kLongDoubleAngle};

      EXPECT_NEAR(static_cast<U>(kAngle), static_cast<U>(kLongDoubleAngle), kEpsilon);
    }
  }
}

TYPED_TEST(FloatingPointTest, ConstructorGivenExplicitAngleValue) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};

    EXPECT_NEAR(static_cast<T>(kAngle), kAngleValue, kEpsilon);
  }
}

// Arithmetic-assignment operators -----------------------------------------------------------------
TYPED_TEST(FloatingPointTest, AdditionAssignmentOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle += kAngleValue;

    EXPECT_NEAR(static_cast<T>(angle), kAngleValue * 2, kEpsilon);
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle += angle;

    EXPECT_NEAR(static_cast<T>(angle), kAngleValue * 2, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, SubtractionAssignmentOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle -= kAngleValue;

    EXPECT_NEAR(static_cast<T>(angle), T{0.0}, kEpsilon);
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle -= angle;

    EXPECT_NEAR(static_cast<T>(angle), T{0.0}, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, MultiplicationAssignmentOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle *= kAngleValue;

    EXPECT_NEAR(static_cast<T>(angle), kAngleValue * kAngleValue, kEpsilon);
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle *= angle;

    EXPECT_NEAR(static_cast<T>(angle), kAngleValue * kAngleValue, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, DivisionAssignmentOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle /= kAngleValue;

    if (fuzzyIsZero(kAngleValue)) {
      EXPECT_TRUE(std::isnan(static_cast<T>(angle)));
    } else {
      EXPECT_NEAR(static_cast<T>(angle), T{1.0}, kEpsilon);
    }
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    Angle<T> angle{kAngleValue};
    angle /= angle;

    if (fuzzyIsZero(kAngleValue)) {
      EXPECT_TRUE(std::isnan(static_cast<T>(angle)));
    } else {
      EXPECT_NEAR(static_cast<T>(angle), T{1.0}, kEpsilon);
    }
  }
}

// Arithmetic operators ----------------------------------------------------------------------------
TYPED_TEST(FloatingPointTest, AdditionOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle + kAngleValue;

    EXPECT_NEAR(static_cast<T>(kResult), kAngleValue * 2, kEpsilon);
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle + kAngle;

    EXPECT_NEAR(static_cast<T>(kResult), kAngleValue * 2, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, SubtractionOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle - kAngleValue;

    EXPECT_NEAR(static_cast<T>(kResult), T{0.0}, kEpsilon);
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle - Angle<T>{kAngle};

    EXPECT_NEAR(static_cast<T>(kResult), T{0.0}, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, MultiplicationOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle * kAngleValue;

    EXPECT_NEAR(static_cast<T>(kResult), kAngleValue * kAngleValue, kEpsilon);
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle * kAngle;

    EXPECT_NEAR(static_cast<T>(kResult), kAngleValue * kAngleValue, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, DivisionOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle / kAngleValue;

    if (fuzzyIsZero(kAngleValue)) {
      EXPECT_TRUE(std::isnan(static_cast<T>(kResult)));
    } else {
      EXPECT_NEAR(static_cast<T>(kResult), T{1.0}, kEpsilon);
    }
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle / Angle<T>{kAngle};

    if (fuzzyIsZero(kAngleValue)) {
      EXPECT_TRUE(std::isnan(static_cast<T>(kResult)));
    } else {
      EXPECT_NEAR(static_cast<T>(kResult), T{1.0}, kEpsilon);
    }
  }
}

// Arithmetic friend operator ----------------------------------------------------------------------
TYPED_TEST(FloatingPointTest, ScalarMutiplicationFriendOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  // scalar
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngleValue * kAngle;

    EXPECT_NEAR(static_cast<T>(kResult), kAngleValue * kAngleValue, kEpsilon);
  }

  // angle
  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = kAngle * kAngle;

    EXPECT_NEAR(static_cast<T>(kResult), kAngleValue * kAngleValue, kEpsilon);
  }
}

// Sign operators ----------------------------------------------------------------------------------
TYPED_TEST(FloatingPointTest, UnaryPlusOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = +kAngle;

    EXPECT_NEAR(static_cast<T>(kResult), kAngleValue, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, UnaryMinusOperator) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};
    const Angle<T> kResult = -kAngle;

    EXPECT_NEAR(static_cast<T>(kResult), -kAngleValue, kEpsilon);
  }
}

// Getters -----------------------------------------------------------------------------------------
TYPED_TEST(FloatingPointTest, GetRadians) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};

    EXPECT_NEAR(kAngle.radians(), kAngleValue, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, GetDegrees) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;
  static constexpr T kRadiansToDegreesFactor = 180 / kPi;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};

    EXPECT_NEAR(kAngle.degrees(), kAngleValue * kRadiansToDegreesFactor, kEpsilon);
  }
}

// Geometry ----------------------------------------------------------------------------------------
TYPED_TEST(FloatingPointTest, Sin) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;
  static constexpr T kDegreesToRadiansFactor = kPi / 180;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};

    EXPECT_NEAR(kAngle.sin(), std::sin(kAngleValue), kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, Cos) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;
  static constexpr T kDegreesToRadiansFactor = kPi / 180;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};

    EXPECT_NEAR(kAngle.cos(), std::cos(kAngleValue), kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, Tan) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;
  static constexpr T kDegreesToRadiansFactor = kPi / 180;

  static constexpr std::array kAngleValues = {
      -kPi * 2,
      -kPi * 3 / 2,
      -kPi,
      -kPi / 2,
      T{0.0},
      kPi / 2,
      kPi,
      kPi * 3 / 2,
      kPi * 2,
  };

  for (const T kAngleValue : kAngleValues) {
    const Angle<T> kAngle{kAngleValue};

    EXPECT_NEAR(kAngle.tan(), std::tan(kAngleValue), kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, NormalizeGivenAnglesBetweenPiAndMinusPi) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  struct AngleTestCase {
    Angle<T> angle;
    T expected;
  };

  static constexpr std::array kTestCases{
      AngleTestCase{Angle<T>{/*radians=*/0.0}, 0.0},           // 0.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/kPi / 2}, kPi / 2},   // 90.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/-kPi / 2}, -kPi / 2}, // -90.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/kPi}, kPi},           // 180.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/-kPi}, -kPi},         // -180.0 degrees
  };

  for (auto [angle, expected] : kTestCases) {
    angle.normalize();

    EXPECT_NEAR(static_cast<T>(angle), expected, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, NormalizeGivenAnglesGreaterThanPi) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  struct AngleTestCase {
    Angle<T> angle;
    T expected;
  };

  static constexpr std::array kTestCases{
      AngleTestCase{Angle<T>{/*radians=*/5 * kPi / 4}, -3 * kPi / 4}, // 225.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/-5 * kPi / 4}, 3 * kPi / 4}, // -225.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/3 * kPi / 2}, -kPi / 2},     // 270.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/-3 * kPi / 2}, kPi / 2},     // -270.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/7 * kPi / 3}, kPi / 3},      // 420.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/-7 * kPi / 3}, -kPi / 3},    // -420.0 degrees
  };

  for (auto [angle, expected] : kTestCases) {
    angle.normalize();

    EXPECT_NEAR(static_cast<T>(angle), expected, kEpsilon);
  }
}

TYPED_TEST(FloatingPointTest, NormalizeGivenAnglesLessThanMinusPi) {
  using T = TypeParam;

  static constexpr T kEpsilon = epsilon_v<T>;
  static constexpr T kPi = std::numbers::pi_v<T>;

  struct AngleTestCase {
    Angle<T> angle;
    T expected;
  };

  static constexpr std::array kTestCases{
      AngleTestCase{Angle<T>{/*radians=*/-9 * kPi / 4}, -kPi / 4}, // -405.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/9 * kPi / 4}, kPi / 4},   // 405.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/-5 * kPi / 2}, -kPi / 2}, // -450.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/5 * kPi / 2}, kPi / 2},   // 450.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/-11 * kPi / 3}, kPi / 3}, // -660.0 degrees
      AngleTestCase{Angle<T>{/*radians=*/11 * kPi / 3}, -kPi / 3}, // 660.0 degrees
  };

  for (auto [angle, expected] : kTestCases) {
    angle.normalize();

    EXPECT_NEAR(static_cast<T>(angle), expected, kEpsilon);
  }
}

// NOLINTEND(readability-function-cognitive-complexity)

} // namespace
} // namespace robocin
