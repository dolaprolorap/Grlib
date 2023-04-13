#pragma once
#include "VectorSpace.h"
#include "GlobalFunctions.h"
#include "Matrix.h"
#include "InvalidVectorIndex.h"
#include "IncompatibleVectorSizes.h"
#include "Engine.h"

class Vector : public Matrix {
public:
    Vector(const Vector& v);
    Vector(int dim);
    template<typename... vec_comps>
	Vector(vec_comps... vc);
	Vector(const Matrix& m);

    double& operator ()(int n);
    double operator ()(int n) const;
    double operator*(const Vector& v);
    Vector operator^(const Vector& v);

    double orth_scalar_product(Vector v);
    double length();

	std::string to_str() const;

	int get_dim() const;
};

template <typename... vec_comps>
Vector::Vector(vec_comps... vc) : Matrix() {
	std::initializer_list<double> vc_init_list = { vc... };

	create_matrix(vc_init_list.size(), 1);

	int i = 0;
	for (auto& coord : vc_init_list) {
		_values[i++][0] = coord;
	}
}