#pragma once
#include "Matrix.h"
#include "Vector.h"
#include "GrlibException.h"

class Matrix;

double bilinear_form(const Matrix& scalar_matrix, const Vector& v1, const Vector& v2);
Matrix& gram_matrix();
double rad2eul(double rad);
double eul2rad(double eul);