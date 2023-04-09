#pragma once
#include <string>
#include "InvalidArgumentException.h"

class InvalidMatrixIndexException : InvalidArgumentException{
public:
	InvalidMatrixIndexException(int height, int width);
	InvalidMatrixIndexException(int line, std::string line_name);
};