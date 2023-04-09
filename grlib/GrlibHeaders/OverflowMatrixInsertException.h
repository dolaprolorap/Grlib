#pragma once
#include "InvalidArgumentException.h"

class OverflowMatrixInsertException : InvalidArgumentException {
public:
	OverflowMatrixInsertException(int line, std::string line_name, int insert_arr_size, int actual_line_size);
};