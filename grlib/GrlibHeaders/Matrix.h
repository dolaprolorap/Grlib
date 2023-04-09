#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include <string>
#include "GrlibConsts.h"
#include "InvalidMatrixIndexException.h"
#include "OverflowMatrixInsertException.h"
#include "IncompatibleMatricesSizesException.h"
#include "NotSquareMatrixException.h"
#include "IsSingularMatrixException.h"

class Vector;
double rad_to_deg(double rad);
double deg_to_rad(double deg);

class Matrix {
public:
	int get_height() const;
	int get_width() const;
	bool is_square() const;

	Matrix(int height, int width);

	Matrix operator + (Matrix m);
	Matrix operator - (Matrix m);
	Matrix operator * (double sc);
	Matrix operator / (double sc);
	Matrix& operator * (Matrix m);
	double& operator ()(int height, int width);
	double*& operator ()(int height);
	void set_row(int row, const std::initializer_list<double>& elems);
	double operator ()(int height, int width) const;

	bool operator == (const Matrix& m) const;

	double det();
	Matrix inverse();
	Matrix transpose();
	static Matrix& identity(int n);
	static Matrix& xyz_rotation_matrix(double x_angle, double y_angle, double z_angle);
	static Matrix& rotation_matrix(double angle, int dim, int first_axis_num, int second_axis_num);
	static Matrix& x_rotation_matrix(double angle);
	static Matrix& y_rotation_matrix(double angle);
	static Matrix& z_rotation_matrix(double angle);
	bool equal_dims(const Matrix& m) const;

protected:
	void create_matrix(int height, int width);
	Matrix();
	int _height, _width;
	double** _values;

private:
	double inner_det();
	Matrix delete_crest(int height, int width);
};

std::ostream& operator<<(std::ostream& os, Matrix& m);