#include "Point.h"

Point::Point(int dim) {
	_coords = new Vector(dim);
}

Point::Point(const Vector& v) {
	_coords = new Vector(v);
}

Point::Point(const Point& point) {
	_coords = new Vector(*point._coords);
}

double& Point::operator()(int n) {
	return (*_coords)(n);
}

double Point::operator()(int n) const {
	return (*_coords)(n);
}

Point Point::operator+(Vector v) {
	//check for right dimension count has already been in constructor
	Point& new_point = *(new Point(*this));
	for (int i = 0; i < v.get_height(); i++) {
		new_point(i) += v(i);
	}
	return new_point;
}

Point Point::operator-(Vector v) {
	//check for right dimension count has already been in constructor
	Vector inv_v = *new Vector((Matrix)v * -1);
	return (*this) + inv_v;
}

Point::operator Vector&() const {
	//check for right dimension count has already been in constructor
	return *(new Vector(*_coords));
}

bool Point::operator==(const Point& p) const {
	Vector this_vec = *this;
	Vector p_vec = p;

	return this_vec == p_vec;
}