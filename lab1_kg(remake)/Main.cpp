#include <iostream>
#include "Grlib.h"

/*
* �������� ������ + ������� �����
* ����������� ������ ����� - ���������������� _coords
* ������� �������� �� ���-�� ����������� ������� � ������� ��� ������ � ���
*/

int main() {
	VectorSpace* vs = new VectorSpace(3);
	CoordinateSystem* cs = new CoordinateSystem(*(new Point(0.0, 0.0, 0.0)));

	for (auto& v : *VectorSpace::get_basis()) {
		std::cout << *v << std::endl;
	}

	std::cout << gram_matrix() << std::endl;

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

	std::cout << Matrix::rotation_matrix(0, 0, 0);

	return 0;
}