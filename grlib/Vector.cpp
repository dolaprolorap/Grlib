#include "Vector.h"

//copy constructor
Vector::Vector(const Vector& v) : Matrix(v.get_dim(), 1) {
	for (int i = 0; i < v.get_height(); i++) {
		(*this)(i) = v(i);
	}
}

Vector::Vector(int dim) : Matrix(dim, 1) {}

Vector::Vector(const Matrix& m) : Matrix(m.get_height(), 1) {
	if (m.get_width() != 1) {
		throw InvalidArgumentException(("Invalid width of matrix: (" + std::to_string(m.get_width()) + ")").c_str());
	}

	for (int i = 0; i < m.get_height(); i++) {
		(*this)(i) = m(i, 0);
	}
}

double& Vector::operator() (int n) {
	if (n < 0 || n >= _height) {
		throw InvalidVectorIndex(n);
	}

	return _values[n][0];
}

double Vector::operator() (int n) const {
	if (n < 0 || n >= _height) {
		throw InvalidVectorIndex(n);
	}

	return _values[n][0];
}

double Vector::orth_scalar_product (Vector v) {
	return (v.transpose() * (Matrix)(*this))(0, 0);
}

double Vector::operator*(const Vector& v) {
	return bilinear_form(gram_matrix(*VectorSpace::get_basis()), (*this), v);
}

Vector Vector::operator^(const Vector& v) {
	if (this->get_height() != v.get_height()) {
		throw IncompatibleVectorSizes(this->get_height(), v.get_height());
	}

	if (this->get_height() != 3) {
		throw InvalidArgumentException(("Vector product is defined only for 3 dimensions: this: " + std::to_string(this->get_height()) +
			" | v: " + std::to_string(v.get_height())).c_str());
	}

	Vector& new_vector = *(new Vector(3));
	new_vector(0) = (*this)(1) * v(2) - (*this)(2) * v(1);
	new_vector(1) = (*this)(2) * v(0) - (*this)(0) * v(2);
	new_vector(2) = (*this)(0) * v(1) - (*this)(1) * v(0);
	return new_vector;
}

double Vector::length() {
	return std::sqrt((*this) * (*this));
}

int Vector::get_dim() const {
	return _height;
}

std::string Vector::to_str() const {
	std::string str;
	str += "| ";
	for (int i = 0; i < this->get_height(); i++) {
		str += std::to_string((*this)(i)) + " ";	
	}
	str += "|\n";
	return str;
}