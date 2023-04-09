#include <iostream>
#include "Grlib.h"

/*
* дописать вектор + сделать тесты
* конструктор класса точки - инициализировать _coords
* сделать проверку на кол-во компонентов вектора в методах для работы с ним
*/

int main() {
	VectorSpace* vs = new VectorSpace(3);
	CoordinateSystem* cs = new CoordinateSystem(*(new Point(0.0, 0.0, 0.0)));

	for (auto& v : *VectorSpace::get_basis()) {
		std::cout << *v << std::endl;
	}

	std::cout << gram_matrix(*VectorSpace::get_basis()) << std::endl;

	Matrix m1(3, 3);
	Matrix m(2, 1);

	m1(0, 0) = 3;
	m1(0, 1) = 0;
	m1(0, 2) = 2;

	m1(1, 0) = 2;
	m1(1, 1) = 2;
	m1(1, 2) = 0;

	m1(2, 0) = 2;
	m1(2, 1) = 0;
	m1(2, 2) = 2;

	std::cout << m1 << std::endl;

	Matrix mr = m1.inverse();

	std::cout << mr << std::endl;

	Vector* v = new Vector(1.0, 1.0, 0.0);
	Vector* vt = new Vector(2.0, 1.0, 2.0);

	std::cout << (*v) << std::endl;

	Point* p = new Point(1.0, 3.0, 4.0);

	Vector vp = (*v) ^ (*vt);

	std::cout << vp << std::endl;

	std::cout << v->length() << std::endl;

	std::cout << Matrix::xyz_rotation_matrix(90, 0, 0);

	std::cout << std::endl;

	Matrix rot_m = Matrix::rotation_matrix(90, 3, 0, 2);
	std::cout << rot_m;

	rot_m = Matrix::xyz_rotation_matrix(0, 90, 0);
	std::cout << rot_m;

	return 0;
}