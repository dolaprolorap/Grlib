#include "IncompatibleVectorSizes.h"

IncompatibleVectorSizes::IncompatibleVectorSizes(int v1_size, int v2_size) : GrlibException(
	("Incompatible vectors sizes: first: " + std::to_string(v1_size) + " | second: " + std::to_string(v2_size)).c_str()
) { }