#include "InvalidVectorIndex.h"

InvalidVectorIndex::InvalidVectorIndex(int index) : GrlibException(
	("Invalid vector index: " + std::to_string(index)).c_str()
) { }