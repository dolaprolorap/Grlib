#pragma once
#include "Vector.h"
#include <vector>
#include "GrlibException.h"

class Vector;

class VectorSpace {
private:
	static int dim;
	static std::vector<Vector*>* basis_vectors;

public:
	static int get_dim();
	static std::vector<Vector*>* get_basis();
	
	VectorSpace(std::vector<Vector*>* basis_vectors);
	VectorSpace(int dim);
};