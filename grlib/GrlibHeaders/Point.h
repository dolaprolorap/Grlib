#pragma once
#include "Vector.h"
#include "GrlibException.h"

class Point {
private:
	Vector* _coords;

public:
	Point(int dim);
	Point(const Vector& v);
	template<typename... point_coords>
	Point(point_coords... pc);
	Point(const Point& point);

	double& operator()(int n);
	double operator()(int n) const;
	Point operator+(Vector v);
	Point operator-(Vector v);

	operator Vector&() const;
	bool operator==(const Point& p) const;
};

template <typename... point_coords>
Point::Point(point_coords... pc) {
	std::initializer_list<double> pc_init_list = { pc... };

	_coords = new Vector((int)pc_init_list.size());
	
	int i = 0;
	for (auto coord : pc_init_list) {
		(*_coords)(i++) = coord;
	}
}