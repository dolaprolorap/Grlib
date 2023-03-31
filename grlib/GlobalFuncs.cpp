#include "GlobalFuncs.h"

double bilinear_form(const Matrix& scalar_matrix, const Vector& v1, const Vector& v2) {
	if (v1.get_height() != v2.get_height() ||
		!scalar_matrix.is_square() ||
		scalar_matrix.get_height() != v1.get_height()) {
		std::string err_str = "Invalid sizes of operands: v1 height: " + std::to_string(v1.get_height()) +
			" | v2 height: " + std::to_string(v2.get_height()) + " | scalar_matrix: (" +
			std::to_string(scalar_matrix.get_height()) + ", " + std::to_string(scalar_matrix.get_width()) + ")";
		throw new GrlibException(err_str.c_str());
	}

	int n = v1.get_height();
	double res = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res += scalar_matrix(i, j) * v1(i) * v2(j);
		}
	}

	return res;
}

Matrix& gram_matrix() {
	std::vector<Vector*>* basis_vectors = VectorSpace::get_basis();
	int n = basis_vectors->size();

	Matrix& res_matrix = *(new Matrix(n, n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res_matrix(i, j) = (*basis_vectors)[i]->orth_scalar_product(*(*basis_vectors)[j]);
		}
	}

	return res_matrix;
}

double rad2eul(double rad) {
	return (rad * 180.0) / PI;
}

double eul2rad(double eul) {
	return (eul * PI) / 180.0;
}