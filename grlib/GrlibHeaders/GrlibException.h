#pragma once
#include <exception>

class GrlibException : std::exception {
public:
	GrlibException(const char* str);
};