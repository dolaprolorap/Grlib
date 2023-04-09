#include <InvalidMatrixIndexException.h>

InvalidMatrixIndexException::InvalidMatrixIndexException(int height, int width) : InvalidArgumentException(
	("Invalid index: height: " + std::to_string(height) + " | width: " + std::to_string(width)).c_str()
) { }

InvalidMatrixIndexException::InvalidMatrixIndexException(int line_num, std::string line_name) : InvalidArgumentException(
	("Invalid index: " + line_name + ": " + std::to_string(line_num)).c_str()
) { }