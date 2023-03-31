#include "Matrix.h"

int Matrix::get_height() const {
	return _height;
}

int Matrix::get_width() const {
	return _width;
}

bool Matrix::is_square() const {
	return _width == _height;
}

void Matrix::create_matrix(int height, int width) {
	if (height <= 0 || width <= 0) {
		std::string err_str = "Height and width must be positive numbers. Height: " + std::to_string(height) +
			" | Width: " + std::to_string(width);
		throw new GrlibException(err_str.c_str());
	}

	_height = height;
	_width = width;

	_values = new double* [_height];

	for (int i = 0; i < _height; i++) {
		_values[i] = new double[_width];
		for (int j = 0; j < _width; j++) _values[i][j] = 0;
	}
}

Matrix::Matrix(int height, int width) {
	create_matrix(height, width);
}

double& Matrix::operator() (int height, int width)
{
	if (height < 0 || width < 0 || height >= _height || width >= _width) {
		std::string err_str = "Invalid index: (" + std::to_string(height) + ", " + std::to_string(width) + ")";
		throw new GrlibException(err_str.c_str());
	}

	return _values[height][width];
}

//unsafe cause no checks for arrays length
double*& Matrix::operator() (int height)
{
	if (height < 0 || height >= _height) {
		std::string err_str = "Invalid index: (" + std::to_string(height) + ")";
		throw new GrlibException(err_str.c_str());
	}

	return _values[height];
}

void Matrix::set_row(int row, const std::initializer_list<double>& elems) {
	if (row >= _height) {
		std::string err_str = "Invalid row: " + std::to_string(row);
		throw new GrlibException(err_str.c_str());
	}

	if (elems.size() > _width) {
		std::string err_str = "Too much elems for that width: width: " + std::to_string(_width) + 
			" | elems.size: " + std::to_string(elems.size());
		throw new GrlibException(err_str.c_str());
	}

	int i = 0;
	for (auto e : elems) {
		_values[row][i++] = e;
	}
}

double Matrix::operator() (int height, int width) const
{
	if (height < 0 || width < 0 || height >= _height || width >= _width) {
		std::string err_str = "Invalid index: (" + std::to_string(height) + ", " + std::to_string(width) + ")";
		throw new GrlibException(err_str.c_str());
	}

	return _values[height][width];
}

Matrix Matrix::operator+(Matrix m) {
	if (m.get_height() != _height || m.get_width() != _width) {
		std::string err_str =
			"Height and width of both matrixes must be the same. \
			Heights of this: " + std::to_string(_height) +
			"; of m: " + std::to_string(m.get_height()) +
			" | Width of this: " + std::to_string(_width) +
			"; of m: " + std::to_string(m.get_width());
		throw new GrlibException(err_str.c_str());
	}

	Matrix& new_matrix = *(new Matrix(_height, _width));

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			new_matrix(i, j) = (*this)(i, j) + m(i, j);
		}
	}

	return new_matrix;
}

Matrix Matrix::operator*(double sc) {
	Matrix& new_matrix = *(new Matrix(_height, _width));

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			new_matrix(i, j) = (*this)(i, j) * sc;
		}
	}

	return new_matrix;
}

Matrix Matrix::operator-(Matrix m) {
	return (*this) + m * (-1);
}

Matrix Matrix::operator/(double sc) {
	return (*this) * (1 / sc);
}

bool Matrix::operator==(const Matrix& m) const {
	if (!equal_dims(m)) return false;

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			if (fabs(_values[i][j] - m(i, j)) >= EPS) return false;
		}
	}

	return true;
}

Matrix& Matrix::operator*(Matrix m) {
	if (m.get_height() != _width) {
		std::string err_str =
			"Heights and widths of both matrixes must match matrix product rule. \
			Heights of this: " + std::to_string(_height) +
			"; of m: " + std::to_string(m.get_height()) +
			" | Width of this: " + std::to_string(_width) +
			"; of m: " + std::to_string(m.get_width());
		throw new GrlibException(err_str.c_str());
	}

	Matrix& new_matrix = *(new Matrix(_height, m.get_width()));

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < m.get_width(); j++) {
			new_matrix(i, j) = 0;
			for (int k = 0; k < _width; k++) {
				new_matrix(i, j) += (*this)(i, k) * m(k, j);
			}
		}
	}

	return new_matrix;
}

double Matrix::det() {
	if (_height != _width) {
		std::string err_str = "For none square matrixes determinante is not defined";
		throw new GrlibException(err_str.c_str());
	}

	return (*this).inner_det();
}

double Matrix::inner_det() {
	double res = 0;
	if ((*this)._height == 1 && (*this)._width == 1) {
		return (*this)(0, 0);
	}
	else {
		for (int i = 0; i < (*this)._height; i++) {
			res += (*this)(i, 0) * (*this).delete_crest(i, 0).inner_det() * (i % 2 == 0 ? 1 : -1);
		}
	}
	return res;
}

Matrix Matrix::delete_crest(int height, int width) {
	if (height < 0 || width < 0 || height >= _height || width >= _width) {
		std::string err_str = "Invalid index: (" + std::to_string(height) + ", " + std::to_string(width) + ")";
		throw new GrlibException(err_str.c_str());
	}

	Matrix& new_matrix = *(new Matrix(_height - 1, _width - 1));
	int h_ptr = 0, w_ptr = 0;

	for (int i = 0; i < _height; i++) {
		if (i != height) {
			for (int j = 0; j < _width; j++) {
				if (j != width) {
					new_matrix(h_ptr, w_ptr) = (*this)(i, j);
					w_ptr++;
				}
			}
			w_ptr = 0;
			h_ptr++;
		}
	}

	return new_matrix;
}

Matrix Matrix::transpose() {
	int tr_height = (*this)._width;
	int tr_width = (*this)._height;

	Matrix& new_matrix = *(new Matrix(tr_height, tr_width));

	for (int i = 0; i < (*this)._height; i++) {
		for (int j = 0; j < (*this)._width; j++) {
			new_matrix(j, i) = (*this)(i, j);
		}
	}

	return new_matrix;
}

Matrix Matrix::inverse() {
	double det = (*this).det();
	if (det == 0) {
		std::string err_str = "Matrix det is equal 0";
		throw new GrlibException(err_str.c_str());
	}

	Matrix& new_matrix = *(new Matrix((*this)._height, (*this)._height));

	for (int i = 0; i < (*this)._height; i++) {
		for (int j = 0; j < (*this)._width; j++) {
			new_matrix(i, j) = (*this).delete_crest(i, j).inner_det() * ((i + j) % 2 == 0 ? 1 : -1);
		}
	}

	new_matrix = new_matrix.transpose();

	return new_matrix / det;
}

Matrix& Matrix::identity(int n) {
	if (n <= 0) {
		std::string err_str = "Wrong size of matrix: " + std::to_string(n);
		throw new GrlibException(err_str.c_str());
	}

	Matrix& new_matrix = *(new Matrix(n, n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) new_matrix(i, j) = 1;
			else new_matrix(i, j) = 0;
		}
	}

	return new_matrix;
}

Matrix::Matrix() { }

/// <summary></summary>
/// <param name="x_angle">In Euler angle</param>
/// <param name="y_angle">In Euler angle</param>
/// <param name="z_angle">In Euler angle</param>
/// <returns></returns>
Matrix& Matrix::rotation_matrix(double x_angle, double y_angle, double z_angle) {
	Matrix& x_matrix = x_rotation_matrix(x_angle);
	Matrix& y_matrix = y_rotation_matrix(y_angle);
	Matrix& z_matrix = z_rotation_matrix(z_angle);
	return x_matrix * y_matrix * z_matrix;
}

/// <summary></summary>
/// <param name="angle">In Euler angle</param>
/// <returns></returns>
Matrix& Matrix::x_rotation_matrix(double angle) {
	Matrix& rot_matrix = *new Matrix(3, 3);
	double rad = eul2rad(angle);
	rot_matrix.set_row(0, { 1.0, 0.0, 0.0 });
	rot_matrix.set_row(1, { 0.0, cos(rad), -sin(rad) });
	rot_matrix.set_row(2, { 0.0, sin(rad), cos(rad) });
	return rot_matrix;
}

/// <summary></summary>
/// <param name="angle">In Euler angle</param>
/// <returns></returns>
Matrix& Matrix::y_rotation_matrix(double angle) {
	Matrix& rot_matrix = *new Matrix(3, 3);
	double rad = eul2rad(angle);
	rot_matrix.set_row(0, { cos(rad), 0.0, sin(rad) });
	rot_matrix.set_row(1, { 0.0, 1.0, 0.0 });
	rot_matrix.set_row(2, { -sin(rad), 0.0, cos(rad) });
	return rot_matrix;
}

/// <summary></summary>
/// <param name="angle">In Euler angle</param>
/// <returns></returns>
Matrix& Matrix::z_rotation_matrix(double angle) {
	Matrix& rot_matrix = *new Matrix(3, 3);
	double rad = eul2rad(angle);
	rot_matrix.set_row(0, { cos(rad), -sin(rad), 0.0 });
	rot_matrix.set_row(1, { sin(rad), cos(rad), 0.0 });
	rot_matrix.set_row(2, { 0.0, 0.0, 1.0 });
	return rot_matrix;
}

bool Matrix::equal_dims(const Matrix& m) const {
	return this->_height == m.get_height() && this->_width == m.get_width();
}

std::ostream& operator<<(std::ostream& os, Matrix& m) {
	for (int i = 0; i < m.get_height(); i++) {
		os << "| ";
		for (int j = 0; j < m.get_width(); j++) {
			os << m(i, j) << " ";
		}
		os << "|" << std::endl;
	}
	return os;
}