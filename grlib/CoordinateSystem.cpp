#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(const Point& init_point) {
	_init_point = new Point(init_point);
}

Point& CoordinateSystem::get_init_point() {
	return *(new Point(*_init_point));
}