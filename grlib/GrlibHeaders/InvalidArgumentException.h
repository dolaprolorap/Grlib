#pragma once
#include "GrlibException.h"

class InvalidArgumentException : GrlibException {
public:
	InvalidArgumentException(const char* str);
};