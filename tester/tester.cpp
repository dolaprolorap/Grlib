#include "pch.h"
#include "CppUnitTest.h"
#include "Grlib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testcppgrlib
{
	const char* boolstr(bool val) {
		return val ? "true" : "false";
	}

	const char* intstr(int val) {
		std::string text = std::to_string(val);
		char* new_char = new char[text.length() + 1];
		strcpy_s(new_char, sizeof new_char, text.c_str());
		return new_char;
	}

	TEST_CLASS(testcppgrlib)
	{
	public:
		TEST_METHOD(TestMatrixEqs)
		{
			bool are_equal = false;
			Matrix& m1 = *new Matrix(3, 3);
			Matrix& m2 = *new Matrix(3, 3);
			Matrix& m3 = *new Matrix(2, 2);

			are_equal = m1 == m2;
			Assert::AreEqual("true", boolstr(are_equal));

			are_equal = m2 == m1;
			Assert::AreEqual("true", boolstr(are_equal));

			m1(1, 1) = 1000;
			are_equal = m1 == m2;
			Assert::AreEqual("false", boolstr(are_equal));

			are_equal = m3 == m1;
			Assert::AreEqual("false", boolstr(are_equal));

			are_equal = m1 == m3;
			Assert::AreEqual("false", boolstr(are_equal));

			are_equal = m1 == m1;
			Assert::AreEqual("true", boolstr(are_equal));
		}

		TEST_METHOD(MatrixOperationsTest)
		{
			Matrix* m1 = new Matrix(1, 1);
			Matrix* m2 = new Matrix(1000, 1);
			Matrix* m3 = new Matrix(1, 1000);

			Matrix& ml = *new Matrix(2, 2);
			Matrix& mr = *new Matrix(2, 2);
			Matrix& msum = *new Matrix(2, 2);
			Matrix& mdif = *new Matrix(2, 2);
			Matrix& mscdot = *new Matrix(2, 2);
			Matrix& mscdel = *new Matrix(2, 2);
			Matrix& mmprod = *new Matrix(2, 2);
			Matrix& mdet = Matrix::identity(3);

			ml(0, 0) = ml(1, 1) = 1;
			mr(0, 0) = mr(1, 1) = 2;

			msum(0, 0) = msum(1, 1) = 3;
			Assert::AreEqual("true", boolstr(msum == ml + mr));

			mdif(0, 0) = mdif(1, 1) = -1;
			Assert::AreEqual("true", boolstr(mdif == ml - mr));

			mscdot(0, 0) = mscdot(1, 1) = 2;
			Assert::AreEqual("true", boolstr(mscdot == ml * 2));

			mscdel(0, 0) = mscdel(1, 1) = 0.5;
			Assert::AreEqual("true", boolstr(mscdel == ml / 2));

			mmprod(0, 0) = mmprod(1, 0) = mmprod(1, 1) = 2;
			Assert::AreEqual("false", boolstr(mmprod == ml * mr));

			ml(1, 0) = 1;
			Assert::AreEqual("true", boolstr(mmprod == ml * mr));

			Assert::AreEqual("1", intstr(mdet.det()));

			mdet = mdet * 34;
			Assert::AreEqual("39304", intstr(mdet.det()));

			mdet(0, 0) = 0;
			Assert::AreEqual("0", intstr(mdet.det()));
		}

		TEST_METHOD(MatrixInverseTest)
		{
			Matrix m = *new Matrix(3, 3);
			double d1[3] = { 2, 2, 0 };
			m(0) = d1;
			double d2[3] = { 0, 2, 0 };
			m(1) = d2;
			double d3[3] = { 1, 1, 1 };
			m(2) = d3;

			Matrix minv = *new Matrix(3, 3);
			double dd1[3] = { 0.5, -0.5, 0 };
			minv(0) = dd1;
			double dd2[3] = { 0, .5, 0 };
			minv(1) = dd2;
			double dd3[3] = { -0.5, 0, 1 };
			minv(2) = dd3;

			Assert::AreEqual("true", boolstr(minv == m.inverse()));
		}

		TEST_METHOD(MatrixTransposeTest)
		{
			Matrix m = *new Matrix(3, 3);
			double d1[3] = { 2, 2, 0 };
			m(0) = d1;
			double d2[3] = { 0, 2, 0 };
			m(1) = d2;
			double d3[3] = { 1, 1, 1 };
			m(2) = d3;

			Matrix mtran = *new Matrix(3, 3);
			double dd1[3] = { 2, 0, 1 };
			mtran(0) = dd1;
			double dd2[3] = { 2, 2, 1 };
			mtran(1) = dd2;
			double dd3[3] = { 0, 0, 1 };
			mtran(2) = dd3;
			
			Assert::AreEqual("true", boolstr(mtran == m.transpose()));
		}

		TEST_METHOD(RotationMatrix) {
			Matrix except_rot_0 = Matrix::identity(3);
			Matrix except_rot_x = Matrix::identity(3);
			except_rot_x(1, 1) = -1;
			except_rot_x(2, 2) = -1;
			Matrix except_rot_y = Matrix::identity(3);
			except_rot_y(0, 0) = -1;
			except_rot_y(2, 2) = -1;
			Matrix except_rot_z = Matrix::identity(3);
			except_rot_z(1, 1) = -1;
			except_rot_z(0, 0) = -1;

			Matrix except_rot90x = Matrix::identity(3);
			except_rot90x.set_row(1, { 0, 0, -1 });
			except_rot90x.set_row(2, { 0, 1, 0 });

			Matrix except_rot90x90z = Matrix::identity(3);
			except_rot90x90z.set_row(0, { 0, -1, 0 });
			except_rot90x90z.set_row(1, { 0, 0, -1 });
			except_rot90x90z.set_row(2, { 1, 0, 0 });

			double sqr = sqrt(2);
			Matrix except_rot90x45y90z = Matrix::identity(3);
			except_rot90x45y90z.set_row(0, { 0, -sqr, sqr });
			except_rot90x45y90z.set_row(1, { 0, -sqr, -sqr });
			except_rot90x45y90z.set_row(2, { 2, 0, 0 });
			except_rot90x45y90z = except_rot90x45y90z * 0.5;

			double sqr3 = sqrt(3);
			Matrix except_rot_90x45y_30z = Matrix::identity(3);
			except_rot_90x45y_30z.set_row(0, { sqr3 * sqr, sqr, 2 * sqr });
			except_rot_90x45y_30z.set_row(1, { -sqr3 * sqr, -sqr, 2 * sqr });
			except_rot_90x45y_30z.set_row(2, { 2, -2 * sqr3, 0 });
			except_rot_90x45y_30z = except_rot_90x45y_30z * 0.25;

			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(0, 0, 0) == Matrix::identity(3)));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(180, 0, 0) == except_rot_x));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(0, 180, 0) == except_rot_y));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(0, 0, 180) == except_rot_z));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(90, 0, 0) == except_rot90x));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(90, 0, 90) == except_rot90x90z));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(-90, 45, -30) == except_rot_90x45y_30z));
		}
	};

	TEST_CLASS(testvector)
	{
	public:
		TEST_METHOD(TestVectorOperations)
		{
			VectorSpace vs = *new VectorSpace(3);

			Vector v1 = *new Vector(1.0, 2.0, 4.0);
			Vector vcpy = *new Vector(v1);

			Assert::AreEqual("true", boolstr(v1 == vcpy));

			Vector v2 = *new Vector(2.0, 3.0, 5.0);

			Assert::AreEqual("28", intstr(v1 * v2));

			Vector crosprod = *new Vector(-2., 3., -1.);
			Assert::AreEqual("true", boolstr((v1 ^ v2) == crosprod));

			Assert::AreEqual("true", boolstr((fabs(v1.length() - 4.58257)) < 0.0001));
		}
	};

	TEST_CLASS(testpoint)
	{
	public:
		TEST_METHOD(TestPointOperations)
		{
			VectorSpace vs = *new VectorSpace(3);

			Vector v = *new Vector(1., 2., 3.);
			Vector shift = *new Vector(0., 2., 4.);

			Point p1 = *new Point(3);
			Point p2 = *new Point(v);
			Point p3 = *new Point(1., 2., 3.);
			Point p4 = *new Point(p2);

			Point pplus = *new Point(1., 4., 7.);
			Point pminus = *new Point(1., 0., -1.);

			Assert::AreEqual("true", boolstr(p2 == p3));
			Assert::AreEqual("true", boolstr(p2 == p4));
			Assert::AreEqual("true", boolstr(p2 == v));
			Assert::AreEqual("true", boolstr(pplus == p3 + shift));
			Assert::AreEqual("true", boolstr(pminus == p3 - shift));/**/
		}
	};

	TEST_CLASS(globalobjects) {
	public:
		TEST_METHOD(TestGlobalObjs) {
			VectorSpace vs = *new VectorSpace(3);
			CoordinateSystem cs = *new CoordinateSystem(*new Point(1., 3., 4.));
		}
	};
}
