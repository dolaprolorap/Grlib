#pragma once
#include "GrlibException.h"
#include <exception>

class InvalidObjectException : GrlibException {
public:
	InvalidObjectException(const char* str);
};