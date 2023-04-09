#pragma once
#include "GrlibException.h"

class IncompatibleVectorSizes : GrlibException {
public:
	IncompatibleVectorSizes(int v1_size, int v2_size);
};