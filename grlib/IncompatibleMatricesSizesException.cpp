#include "IncompatibleMatricesSizesException.h"

IncompatibleMatricesSizesException::IncompatibleMatricesSizesException(int width1, int height1, int width2, int height2, std::string operation) : InvalidArgumentException (
	(*new StrFormater("Incompatible matrices sizes for operation \"{0}\": \nwidth1: {1} | height1: {2} \nwidth2: {3} | height2: {4}", 
		operation, std::to_string(width1), std::to_string(height1), std::to_string(width2), std::to_string(height2))).get_str().c_str()
) { }