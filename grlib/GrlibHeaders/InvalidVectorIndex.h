#pragma once
#include "GrlibException.h"

class InvalidVectorIndex : GrlibException {
public:
	InvalidVectorIndex(int index);
};