#pragma once
#include "GrlibException.h"

class NotSquareMatrixException : GrlibException {
public:
	NotSquareMatrixException(int width, int height);
};