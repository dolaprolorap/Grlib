#include "VectorSpace.h"

int VectorSpace::dim;
std::vector<Vector*>* VectorSpace::basis_vectors;

VectorSpace::VectorSpace(int dim) {
	if (dim <= 0) {
		std::string err_str = "Wrong dim number: " + std::to_string(dim);
		throw new GrlibException(err_str.c_str());
	}

	VectorSpace::dim = dim;
	VectorSpace::basis_vectors = new std::vector<Vector*>();

	for (int i = 0; i < dim; i++) {
		Vector* basis_vec = new Vector(dim);
		(*basis_vec)(i) = 1;
		VectorSpace::basis_vectors->push_back(basis_vec);
	}
}

VectorSpace::VectorSpace(std::vector<Vector*>* basis_vectors) {
	if (basis_vectors->size() <= 0) {
		std::string err_str = "Wrong dim number: " + basis_vectors->size();
		throw new GrlibException(err_str.c_str());
	}

	VectorSpace::dim = basis_vectors->size();
	VectorSpace::basis_vectors = new std::vector<Vector*>();

	for (int i = 0; i < basis_vectors->size(); i++) {
		Vector* basis_vec = new Vector(VectorSpace::dim);
		(*basis_vec)(i) = 1;
		VectorSpace::basis_vectors->push_back(basis_vec);
	}
}

std::vector<Vector*>* VectorSpace::get_basis() {
	std::vector<Vector*>* return_vector = new std::vector<Vector*>();
	for (auto& vec : *basis_vectors) {
		return_vector->push_back(new Vector(*vec));
	}
	return return_vector;
}

int VectorSpace::get_dim() {
	return dim;
}