#pragma once
#include "InvalidArgumentException.h"

class IncompatibleMatricesSizesException : InvalidArgumentException {
public:
	IncompatibleMatricesSizesException(int width1, int height1, int width2, int height2, std::string operation);
};