#pragma once
#include <exception>
#include <string>
#include "StrFormater.h"

class GrlibException : std::exception {
public:
	GrlibException(const char* str);
};