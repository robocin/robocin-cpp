# geometry

A collection of geometric classes.

## Table of Contents

- [Point2D](#point2d)

<a name="point2d"></a>

## [`Point2D`](point2d.h)

The `Point2D` templated struct represents a 2-dimensional point (vector) in a Cartesian coordinate system. It provides
various methods and operators for manipulating and performing calculations with 2d-points.

### Member Types

- `value_type`: The type of the point's coordinates;
- `reference`: A reference to `value_type`;
- `size_type`: An unsigned integer type used for size and indexing;
- `iterator`: An iterator type for iterating over mutable `Point2D` objects;
- `const_iterator`: An iterator type for iterating over const `Point2D` objects;
- `reverse_iterator`: A reverse iterator type for reverse iteration over mutable `Point2D` objects;
- `const_reverse_iterator`: A reverse iterator type for reverse iteration over const `Point2D` objects;

### Static Constructors

- `static Point2D origin()`: Returns a point representing the origin (0, 0);
- `static Point2D fromPolar(value_type angle) requires(std::floating_point<value_type>)`: Creates a point from polar
  coordinates with the given angle;
- `static Point2D fromPolar(value_type angle, value_type length) requires(std::floating_point<value_type>)`: Creates a
  point from polar coordinates with the given angle and length;

### Constructors

- `Point2D()`: Default constructor. Initializes the point with coordinates (0, 0);
- `Point2D(const Point2D& point)`: Creates a new point by copying the coordinates of another point;
- `Point2D(Point2D&& point)`: Creates a new point by moving the coordinates of another point;
- `Point2D(value_type x, value_type y)`: Initializes the point with the specified coordinates;
- `explicit Point2D(const OtherStructPoint auto& point)`: Initializes the point from coordinates (`point.x`, `point.y`);
- `explicit Point2D(const OtherClassPoint auto& point)`: Initializes the point from
  coordinates (`point.x()`, `point.y()`);
- `explicit Point2D(const std::pair<U, V>& pair)`: Constructor. Initializes the point with the coordinates from
  a `std::pair`;

### Assignment Operators

- `constexpr Point2D& operator=(const Point2D& other) = default`: Copy assignment operator. Assigns the coordinates of
  another point to this point;
- `constexpr Point2D& operator=(Point2D&& other) noexcept = default`: Move assignment operator. Moves the coordinates of
  another point to this point;

### Validators

- `bool isNull() const`: Checks if the point (vector) is null (coordinates are both zero). Returns `true` if the point
  is null, `false` otherwise;

### Arithmetic-Assignment Operators

- `Point2D& operator+=(const Point2D& other)`: Adds the coordinates of another point to this point and updates its
  value. Returns a reference to the modified point;
- `Point2D& operator-=(const Point2D& other)`: Subtracts the coordinates of another point from this point and updates
  its value. Returns a reference to the modified point;
- `Point2D& operator*=(value_type factor)`: Multiplies the coordinates of this point by a scalar factor and updates its
  value. Returns a reference to the modified point;
- `Point2D& operator/=(value_type factor)`: Divides the coordinates of this point by a scalar factor and updates its
  value. Returns a reference to the modified point;

### Arithmetic Operators

- `Point2D operator+(const Point2D& other) const`: Addition operator that returns the sum of two points;
- `Point2D operator-(const Point2D& other) const`: Subtraction operator that returns the difference between two points;
- `Point2D operator*(value_type factor) const`: Multiplication operator that scales the point by a factor;
- `Point2D operator/(value_type factor) const`: Division operator that scales the point by the inverse of a factor;

### Arithmetic Friend Operators

- `friend Point2D operator*(value_type factor, const Point2D& point)`: Friend operator that allows multiplication of a
  point by a factor in the reverse order;

### Sign Operators

- `Point2D operator+() const`: Unary plus operator that returns the point itself;
- `Point2D operator-() const`: Unary minus operator that returns the negation of the point;

### Comparison Operators

- `bool operator==(const Point2D& other) const`: Equality operator that checks if two points are equal;
- `auto operator<=>(const Point2D& other) const`: Three-way comparison operator that compares
  two points and returns their relative ordering;

### Swap

- `void swap(Point2D& other) noexcept`: Swaps the contents of the current point with another point;

### Geometry

- `value_type dot(const Point2D& other) const`: Computes the dot product of the current point and another point;
- `value_type cross(const Point2D& other) const`: Computes the cross product of the current point and another point;
- `value_type manhattanLength() const`: Computes the Manhattan distance between the origin and the current point;
- `value_type manhattanDistTo(const Point2D& other) const`: Computes the Manhattan distance between the current point
  and another point;
- `value_type lengthSquared() const`: Computes the square of the Euclidean length of the current point;
- `std::floating_point auto length() const`: Computes the Euclidean length of the current point;
- `std::floating_point auto norm() const`: Computes the Euclidean length of the current point;
- `value_type distSquaredTo(const Point2D& other) const`: Computes the square of the Euclidean distance between the
  current point and another point;
- `std::floating_point auto distTo(const Point2D& other) const`: Computes the Euclidean distance between the current
  point and another point;
- `std::floating_point auto angle() const`: Computes the angle (in radians) [-PI , +PI] between the positive x-axis and
  the origin to the current point;
- `std::floating_point auto angleTo(const Point2D& other) const`: Computes the angle (in radians) [-PI , +PI] between
  the origin to the current point and the origin to another point;

### Rotations

- `void rotateCW90() &`: Rotates the current point 90 degrees clockwise;
- `Point2D rotatedCW90() &&`: Returns a new point obtained by rotating the current point 90 degrees clockwise;
- `Point2D rotatedCW90() const&`: Returns a new point obtained by rotating a copy of the current point 90 degrees
  clockwise;


- `void rotateCCW90() &`: Rotates the current point 90 degrees counterclockwise;
- `Point2D rotatedCCW90() &&`: Returns a new point obtained by rotating the current point 90 degrees counterclockwise;
- `Point2D rotatedCCW90() const&`: Returns a new point obtained by rotating a copy of the current point 90 degrees
  counterclockwise;


- `void rotateCW(value_type t) &`: Rotates the current point clockwise by a specified angle `t` (in radians);
- `Point2D rotatedCW(value_type t) &&`: Returns a new point obtained by rotating the current point clockwise by a
  specified angle `t` (in radians);
- `Point2D rotatedCW(value_type t) const&`: Returns a new point obtained by rotating a copy of the current point
  clockwise by a specified angle `t` (in radians);


- `void rotateCCW(value_type t) &`: Rotates the current point counterclockwise by a specified angle `t` (in radians);
- `Point2D rotatedCCW(value_type t) &&`: Returns a new point obtained by rotating the current point counterclockwise by
  a specified angle `t` (in radians);
- `Point2D rotatedCCW(value_type t) const&`: Returns a new point obtained by rotating a copy of the current point
  counterclockwise by a specified angle `t` (in radians);

### Resizing and Normalization

- `void resize(value_type t) &`: Resizes the current point by a factor `t`;
- `Point2D resized(value_type t) &&`: Returns a new point obtained by resizing the current point by a factor `t`;
- `Point2D resized(value_type t) const&`: Returns a new point obtained by resizing a copy of the current point by a
  factor `t`;

- `void normalize() &`: Normalizes the current point to have unit length.

> **Note:** The normalization differs for real and integer numbers, being equivalent to `resize(1)` for real numbers,
> and the division of coordinates by their gcd for integer numbers.

- `Point2D normalized() &&`: Returns a new point obtained by normalizing the current point to have unit length;
- `Point2D normalized() const&`: Returns a new point obtained by normalizing a copy of the current point to have unit
  length;


- `void axesNormalize() &`: Normalizes the current point to have coordinates of -1, 0, or 1;
- `Point2D axesNormalized() &&`: Returns a new point obtained by normalizing the current point to have coordinates of
  -1, 0, or 1;
- `Point2D axesNormalized() const&`: Returns a new point obtained by normalizing a copy of the current point to have
  coordinates of -1, 0, or 1;

### Array-like

- `static size_type size()`: Returns the size of the point (always 2);
- `reference operator[](size_type pos)`: Provides access to the elements of the point using the subscript operator;
- `value_type operator[](size_type pos) const`: Provides access to the elements of the point using the subscript
  operator;

### Iterators

The following iterator methods provide support for iterating over the elements of the point:

- `iterator begin() noexcept`;
- `const_iterator begin() const noexcept`;
- `iterator end() noexcept`;
- `const_iterator end() const noexcept`;
- `reverse_iterator rbegin() noexcept`;
- `const_reverse_iterator rbegin() const noexcept`;
- `reverse_iterator rend() noexcept`;
- `const_reverse_iterator rend() const noexcept`;
- `const_iterator cbegin() const noexcept`;
- `const_iterator cend() const noexcept`;
- `const_reverse_iterator crbegin() const noexcept`;
- `const_reverse_iterator crend() const noexcept`;

### Input/Output Operators

The following operators allow input and output of `Point2D` objects:

- `std::istream& operator>>(std::istream& is, Point2D& point)`: Reads a `Point2D` object from an input stream.
- `std::ostream& operator<<(std::ostream& os, const Point2D& point)`: Writes a `Point2D` object to an output stream.

### Deduction Guides

The following deduction guides are provided:

- `Point2D() -> Point2D<double>`: Constructs a `Point2D` with `double` coordinates when no arguments are provided;
- `Point2D(T, U) -> Point2D<std::common_type_t<T, U>>`: This deduction guide ensures that when constructing a `Point2D`
  with different coordinate types `T` and `U`, the resulting `Point2D` type will have a coordinate type that is the
  common type of `T` and `U`;
