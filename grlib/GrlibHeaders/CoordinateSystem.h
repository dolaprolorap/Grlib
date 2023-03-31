#pragma once
#include "Point.h"
#include "VectorSpace.h"

class CoordinateSystem {
private:
	Point* _init_point;

public:
	Point& get_init_point();

	CoordinateSystem(const Point& init_point);
};