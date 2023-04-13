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


			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(0, 0, 0) == Matrix::identity(3)));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(180, 0, 0) == except_rot_x));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(0, 180, 0) == except_rot_y));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(0, 0, 180) == except_rot_z));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(90, 0, 0) == except_rot90x));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(90, 0, 90) == except_rot90x90z));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(-90, 45, -30) == except_rot_90x45y_30z));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(90, 3, 1, 2) == Matrix::xyz_rotation_matrix(90, 0, 0)));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(90, 3, 2, 0) == Matrix::xyz_rotation_matrix(0, 90, 0)));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(45, 3, 0, 1) == Matrix::xyz_rotation_matrix(0, 0, 45)));
		}
	};

	TEST_CLASS(testvector)
	{
	public:
		TEST_METHOD(TestVectorOperations)
		{
			VectorSpace vs = *new VectorSpace(3);
			Engine::set_vs(&vs);

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

	TEST_CLASS(StrFormaterTest) {
	public:
		TEST_METHOD(GetStr) {
			StrFormater sf1("adsf", "sf");
			StrFormater sf2("adsf{0}", "sf");
			StrFormater sf3("adsf{0}{1}", "sf", "123");
			StrFormater sf4("{2}adsf{0}{1}", "sf", "123", "---");
			StrFormater sf5("{2}adsf{0}{1}", "sf", "123", "---", "qwe");
			StrFormater sf6("{2}adsf{0}{1}");

			Assert::AreEqual("true", boolstr(sf1.get_str() == "adsf"));
			Assert::AreEqual("true", boolstr(sf2.get_str() == "adsfsf"));
			Assert::AreEqual("true", boolstr(sf3.get_str() == "adsfsf123"));
			Assert::AreEqual("true", boolstr(sf4.get_str() == "---adsfsf123"));
			Assert::AreEqual("true", boolstr(sf5.get_str() == "---adsfsf123"));
			sf6.set_args("-1-", "-2-", "-3-");
			Assert::AreEqual("-3-adsf-1--2-", sf6.get_str().c_str());
			sf6.del_args();
			sf6.set_args("(1)", "(2)", "(3)");
			Assert::AreEqual("(3)adsf(1)(2)", sf6.get_str().c_str());
			sf6.del_args();
			sf6.set_args("", "", "");
			Assert::AreEqual("adsf", sf6.get_str().c_str());
		}
	};

	void Test1() {
		Matrix m = *new Matrix(-1, -1);
	}

	void Test2() {
		Matrix m = *new Matrix(1, 1);
		m(2, 2) = 9;
	}

	void Test3() {
		Matrix m = *new Matrix(2, 2);
		m.set_row(4, { 1, 2 });
	}

	void Test4() {
		Matrix m = *new Matrix(2, 2);
		m.set_row(1, { 1, 2, 3, 4, 5 });
	}

	void Test5() {
		Matrix m = *new Matrix(2, 2);
		double i = m(4, 4);
	}

	void Test6() {
		Matrix m1 = *new Matrix(2, 2);
		Matrix m2 = *new Matrix(3, 3);
		m1 + m2;
	}

	void Test7() {
		Matrix m1 = *new Matrix(1, 2);
		Matrix m2 = *new Matrix(3, 6);
		m1 * m2;
	}

	void Test8() {
		Matrix m = *new Matrix(2, 1);
		m.det();
	}

	void Test9() {
		Matrix m = *new Matrix(2, 2);
		m.inverse();
	}

	void Test10() {
		Matrix::identity(-2);
	}

	void Test11() {
		Matrix::rotation_matrix(34, 4, 5, 5);
	}

	TEST_CLASS(MatrixExceptionTest) {
	public:
		TEST_METHOD(General) {
			auto test1 = [] { Test1(); };
			Assert::ExpectException<InvalidArgumentException>(test1);

			auto test2 = [] { Test2(); };
			Assert::ExpectException<InvalidMatrixIndexException>(test2);

			auto test3 = [] { Test3(); };
			Assert::ExpectException<InvalidMatrixIndexException>(test3);

			auto test4 = [] { Test4(); };
			Assert::ExpectException<OverflowMatrixInsertException>(test4);

			auto test5 = [] { Test5(); };
			Assert::ExpectException<InvalidMatrixIndexException>(test5);

			auto test6 = [] { Test6(); };
			Assert::ExpectException<IncompatibleMatricesSizesException>(test6);

			auto test7 = [] { Test7(); };
			Assert::ExpectException<IncompatibleMatricesSizesException>(test7);

			auto test8 = [] { Test8(); };
			Assert::ExpectException<NotSquareMatrixException>(test8);

			auto test9 = [] { Test9(); };
			Assert::ExpectException<IsSingularMatrixException>(test9);

			auto test10 = [] { Test10(); };
			Assert::ExpectException<InvalidArgumentException>(test10);

			auto test11 = [] { Test11(); };
			Assert::ExpectException<InvalidArgumentException>(test11);
		}
	};

	void VectorExcTest1() {
		Matrix m = *new Matrix(2, 2);
		Vector v = *new Vector(m);
	}

	void VectorExcTest2() {
		Vector v = *new Vector(2);
		v(5) = 6;
	}

	void VectorExcTest3() {
		Vector v = *new Vector(2);
		double val = v(5);
	}

	void VectorExcTest4() {
		Vector v1 = *new Vector(3);
		Vector v2 = *new Vector(2);

		v1 ^ v2;
	}

	void VectorExcTest5() {
		Vector v1 = *new Vector(4);
		Vector v2 = *new Vector(4);
		
		v1 ^ v2;
	}

	TEST_CLASS(VectorExceptionTest) {
	public:
		TEST_METHOD(General) {
			auto test1 = [] { VectorExcTest1(); };
			Assert::ExpectException<InvalidArgumentException>(test1);

			auto test2 = [] { VectorExcTest2(); };
			Assert::ExpectException<InvalidVectorIndex>(test2);

			auto test3 = [] { VectorExcTest3(); };
			Assert::ExpectException<InvalidVectorIndex>(test3);

			auto test4 = [] { VectorExcTest4(); };
			Assert::ExpectException<IncompatibleVectorSizes>(test4);

			auto test5 = [] { VectorExcTest5(); };
			Assert::ExpectException<InvalidArgumentException>(test5);
		}
	};
	
	void BilinearFormExcTest1() {
		Vector v1 = *new Vector(4);
		Vector v2 = *new Vector(5);
		Matrix m = *new Matrix(6, 7);
		bilinear_form(m, v1, v2);
	}

	TEST_CLASS(BilinearFormException) {
	public:
		TEST_METHOD(General) {
			auto test1 = [] { BilinearFormExcTest1(); };
			Assert::ExpectException<InvalidArgumentException>(test1);
		}
	};

	void VectorSpaceExcTest1() {
		VectorSpace vs = *new VectorSpace(-2);
	}

	void VectorSpaceExcTest2() {
		std::vector<Vector*> basis = *new std::vector<Vector*>();
		VectorSpace vs = *new VectorSpace(&basis);
	}

	TEST_CLASS(VectorSpaceException) {
	public:
		TEST_METHOD(General) {
			auto test1 = [] { VectorSpaceExcTest1(); };
			Assert::ExpectException<InvalidArgumentException>(test1);

			auto test2 = [] { VectorSpaceExcTest2(); };
			Assert::ExpectException<InvalidArgumentException>(test2);
		}
	};
}
