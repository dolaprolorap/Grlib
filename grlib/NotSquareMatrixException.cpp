#include "NotSquareMatrixException.h"

NotSquareMatrixException::NotSquareMatrixException(int height, int width) : GrlibException(
	(*new StrFormater("There is non square matrix where square matrix is neccessary. Actual size: height: {0} | width: {1}", 
		std::to_string(height), std::to_string(width))).get_str().c_str()
) { }