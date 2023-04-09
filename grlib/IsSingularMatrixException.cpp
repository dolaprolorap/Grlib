#include "IsSingularMatrixException.h"

IsSingularMatrixException::IsSingularMatrixException() : GrlibException(
	"There is singular matrix where it is forbidden"
) { };
