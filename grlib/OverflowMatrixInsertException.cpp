#include "OverflowMatrixInsertException.h"

OverflowMatrixInsertException::OverflowMatrixInsertException(int line, std::string line_name, int insert_arr_size, int actual_line_size) : InvalidArgumentException(
	(new StrFormater("Overflow insertion at {0} {1} of array size {2} when the actual size of line is {3}", line_name, std::to_string(line),
		std::to_string(insert_arr_size), std::to_string(actual_line_size)))->get_str().c_str()
) { }