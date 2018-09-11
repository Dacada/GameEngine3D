#include "stdafx.h"
#include "CppUnitTest.h"

extern "C" {
#include <engine3D_vector.h>
}

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(VectorUnitTests) {
public:

	TEST_METHOD(Vector2fLengthTest) {
		engine3D_vector2f_t v;
		v.x = 3;
		v.y = 4;
		float r = engine3D_vector2f_length(&v);
		Assert::AreEqual(5.0f, r);
	}

	TEST_METHOD(Vector2fDotTest) {
		engine3D_vector2f_t v1, v2;
		v1.x = 1;
		v1.y = 2;
		v2.x = 4;
		v2.y = 8;
		float r = engine3D_vector2f_dot(&v1, &v2);
		Assert::AreEqual(20.0f, r);
	}

	TEST_METHOD(Vector3fDotTest) {
		engine3D_vector3f_t v1, v2;
		v1.x = 1;
		v1.y = 2;
		v1.z = -5;
		v2.x = 4;
		v2.y = 8;
		v2.z = 1;
		float r = engine3D_vector3f_dot(&v1, &v2);
		Assert::AreEqual(15.0f, r);
	}

	TEST_METHOD(Vector2fNormalizeTest) {
		engine3D_vector2f_t v;
		v.x = 3;
		v.y = 4;
		engine3D_vector2f_normalize(&v);
		Assert::AreEqual(0.6f, v.x);
		Assert::AreEqual(0.8f, v.y);
	}

	TEST_METHOD(Vector3fNormalizeTest) {
		engine3D_vector3f_t v;
		v.x = 3;
		v.y = 1;
		v.z = 2;
		engine3D_vector3f_normalize(&v);
		Assert::AreEqual(0.802f, v.x, 0.001f);
		Assert::AreEqual(0.267f, v.y, 0.001f);
		Assert::AreEqual(0.534f, v.z, 0.001f);
	}

	TEST_METHOD(Vector2fRotateTest) {
		engine3D_vector2f_t v, r;
		v.x = 1;
		v.y = 0;
		engine3D_vector2f_rotateDeg(&v, 45, &r);
		Assert::AreEqual(0.707f, r.x, 0.001f);
		Assert::AreEqual(0.707f, r.y, 0.001f);
	}

	TEST_METHOD(Vector3fRotateTest) {
		// TODO
	}

	TEST_METHOD(Vector3fCrossTest) {
		engine3D_vector3f_t v1, v2, r;
		v1.x = 3;
		v1.y = -3;
		v1.z = 1;
		v2.x = 4;
		v2.y = 9;
		v2.z = 2;
		engine3D_vector3f_cross(&v1, &v2, &r);
		Assert::AreEqual(-15.0f, r.x);
		Assert::AreEqual(-2.0f, r.y);
		Assert::AreEqual(39.0f, r.z);
	}

	TEST_METHOD(Vector2fAddTest) {
		engine3D_vector2f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v2.x = 8;
		v2.y = 2;
		engine3D_vector2f_add(&v1, &v2, &r);
		Assert::AreEqual(12.0f, r.x);
		Assert::AreEqual(7.0f, r.y);
	}

	TEST_METHOD(Vector2fAddfTest) {
		engine3D_vector2f_t v, r;
		v.x = 4;
		v.y = 5;
		engine3D_vector2f_addf(&v, 3, &r);
		Assert::AreEqual(7.0f, r.x);
		Assert::AreEqual(8.0f, r.y);
	}

	TEST_METHOD(Vector3fAddTest) {
		engine3D_vector3f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v1.z = 7;
		v2.x = 8;
		v2.y = 2;
		v2.z = 1;
		engine3D_vector3f_add(&v1, &v2, &r);
		Assert::AreEqual(12.0f, r.x);
		Assert::AreEqual(7.0f, r.y);
		Assert::AreEqual(8.0f, r.z);
	}

	TEST_METHOD(Vector3fAddfTest) {
		engine3D_vector3f_t v, r;
		v.x = 4;
		v.y = 5;
		v.z = 7;
		engine3D_vector3f_addf(&v, 3, &r);
		Assert::AreEqual(7.0f, r.x);
		Assert::AreEqual(8.0f, r.y);
		Assert::AreEqual(10.0f, r.z);
	}

	TEST_METHOD(Vector2fSubTest) {
		engine3D_vector2f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v2.x = 8;
		v2.y = 2;
		engine3D_vector2f_sub(&v1, &v2, &r);
		Assert::AreEqual(-4.0f, r.x);
		Assert::AreEqual(3.0f, r.y);
	}

	TEST_METHOD(Vector2fSubfTest) {
		engine3D_vector2f_t v, r;
		v.x = 4;
		v.y = 5;
		engine3D_vector2f_subf(&v, 3, &r);
		Assert::AreEqual(1.0f, r.x);
		Assert::AreEqual(2.0f, r.y);
	}

	TEST_METHOD(Vector3fSubTest) {
		engine3D_vector3f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v1.z = 7;
		v2.x = 8;
		v2.y = 2;
		v2.z = 1;
		engine3D_vector3f_sub(&v1, &v2, &r);
		Assert::AreEqual(-4.0f, r.x);
		Assert::AreEqual(3.0f, r.y);
		Assert::AreEqual(6.0f, r.z);
	}

	TEST_METHOD(Vector3fSubfTest) {
		engine3D_vector3f_t v, r;
		v.x = 4;
		v.y = 5;
		v.z = 7;
		engine3D_vector3f_subf(&v, 3, &r);
		Assert::AreEqual(1.0f, r.x);
		Assert::AreEqual(2.0f, r.y);
		Assert::AreEqual(4.0f, r.z);
	}

	TEST_METHOD(Vector2fMulTest) {
		engine3D_vector2f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v2.x = 8;
		v2.y = 2;
		engine3D_vector2f_mul(&v1, &v2, &r);
		Assert::AreEqual(32.0f, r.x);
		Assert::AreEqual(10.0f, r.y);
	}

	TEST_METHOD(Vector2fMulfTest) {
		engine3D_vector2f_t v, r;
		v.x = 4;
		v.y = 5;
		engine3D_vector2f_mulf(&v, 3, &r);
		Assert::AreEqual(12.0f, r.x);
		Assert::AreEqual(15.0f, r.y);
	}

	TEST_METHOD(Vector3fMulTest) {
		engine3D_vector3f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v1.z = 7;
		v2.x = 8;
		v2.y = 2;
		v2.z = 1;
		engine3D_vector3f_mul(&v1, &v2, &r);
		Assert::AreEqual(32.0f, r.x);
		Assert::AreEqual(10.0f, r.y);
		Assert::AreEqual(7.0f, r.z);
	}

	TEST_METHOD(Vector3fMulfTest) {
		engine3D_vector3f_t v, r;
		v.x = 4;
		v.y = 5;
		v.z = 7;
		engine3D_vector3f_mulf(&v, 3, &r);
		Assert::AreEqual(12.0f, r.x);
		Assert::AreEqual(15.0f, r.y);
		Assert::AreEqual(21.0f, r.z);
	}

	TEST_METHOD(Vector2fDivTest) {
		engine3D_vector2f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v2.x = 8;
		v2.y = 2;
		engine3D_vector2f_div(&v1, &v2, &r);
		Assert::AreEqual(0.5f, r.x);
		Assert::AreEqual(2.5f, r.y);
	}

	TEST_METHOD(Vector2fDivfTest) {
		engine3D_vector2f_t v, r;
		v.x = 4;
		v.y = 5;
		engine3D_vector2f_divf(&v, 3, &r);
		Assert::AreEqual(1.3f, r.x, 0.1f);
		Assert::AreEqual(1.6f, r.y, 0.1f);
	}

	TEST_METHOD(Vector3fDivTest) {
		engine3D_vector3f_t v1, v2, r;
		v1.x = 4;
		v1.y = 5;
		v1.z = 7;
		v2.x = 8;
		v2.y = 2;
		v2.z = 1;
		engine3D_vector3f_div(&v1, &v2, &r);
		Assert::AreEqual(0.5f, r.x, 0.1f);
		Assert::AreEqual(2.5f, r.y, 0.1f);
		Assert::AreEqual(7.0f, r.z, 0.1f);
	}

	TEST_METHOD(Vector3fDivfTest) {
		engine3D_vector3f_t v, r;
		v.x = 4;
		v.y = 5;
		v.z = 7;
		engine3D_vector3f_divf(&v, 3, &r);
		Assert::AreEqual(1.3f, r.x, 0.1f);
		Assert::AreEqual(1.6f, r.y, 0.1f);
		Assert::AreEqual(2.3f, r.z, 0.1f);
	}

	TEST_METHOD(Matrix4fIdentityTest) {
		engine3d_matrix4f_t m;
		engine3D_matrix4f_setIdentity(&m);

		Assert::AreEqual(1.0f, m.mat[0][0]);
		Assert::AreEqual(0.0f, m.mat[0][1]);
		Assert::AreEqual(0.0f, m.mat[0][2]);
		Assert::AreEqual(0.0f, m.mat[0][3]);

		Assert::AreEqual(0.0f, m.mat[1][0]);
		Assert::AreEqual(1.0f, m.mat[1][1]);
		Assert::AreEqual(0.0f, m.mat[1][2]);
		Assert::AreEqual(0.0f, m.mat[1][3]);

		Assert::AreEqual(0.0f, m.mat[2][0]);
		Assert::AreEqual(0.0f, m.mat[2][1]);
		Assert::AreEqual(1.0f, m.mat[2][2]);
		Assert::AreEqual(0.0f, m.mat[2][3]);

		Assert::AreEqual(0.0f, m.mat[3][0]);
		Assert::AreEqual(0.0f, m.mat[3][1]);
		Assert::AreEqual(0.0f, m.mat[3][2]);
		Assert::AreEqual(1.0f, m.mat[3][3]);
	}

	TEST_METHOD(Matrix4fMulTest) {
		engine3d_matrix4f_t m1, m2, r;

		m1.mat[0][0] = 3;		m2.mat[0][0] = 5;
		m1.mat[0][1] = 8;		m2.mat[0][1] = 6;
		m1.mat[0][2] = 7;		m2.mat[0][2] = 8;
		m1.mat[0][3] = 5;		m2.mat[0][3] = 0;

		m1.mat[1][0] = 2;		m2.mat[1][0] = 0;
		m1.mat[1][1] = 6;		m2.mat[1][1] = 7;
		m1.mat[1][2] = 8;		m2.mat[1][2] = 4;
		m1.mat[1][3] = 0;		m2.mat[1][3] = 2;

		m1.mat[2][0] = 9;		m2.mat[2][0] = 2;
		m1.mat[2][1] = 6;		m2.mat[2][1] = 5;
		m1.mat[2][2] = 4;		m2.mat[2][2] = 6;
		m1.mat[2][3] = 6;		m2.mat[2][3] = 8;

		m1.mat[3][0] = 8;		m2.mat[3][0] = 0;
		m1.mat[3][1] = 6;		m2.mat[3][1] = 8;
		m1.mat[3][2] = 8;		m2.mat[3][2] = 5;
		m1.mat[3][3] = 6;		m2.mat[3][3] = 4;

		engine3D_matrix4f_mul(&m1, &m2, &r);

		Assert::AreEqual(29.0f, r.mat[0][0]);
		Assert::AreEqual(149.0f, r.mat[0][1]);
		Assert::AreEqual(123.0f, r.mat[0][2]);
		Assert::AreEqual(92.0f, r.mat[0][3]);

		Assert::AreEqual(26.0f, r.mat[1][0]);
		Assert::AreEqual(94.0f, r.mat[1][1]);
		Assert::AreEqual(88.0f, r.mat[1][2]);
		Assert::AreEqual(76.0f, r.mat[1][3]);

		Assert::AreEqual(53.0f, r.mat[2][0]);
		Assert::AreEqual(164.0f, r.mat[2][1]);
		Assert::AreEqual(150.0f, r.mat[2][2]);
		Assert::AreEqual(68.0f, r.mat[2][3]);

		Assert::AreEqual(56.0f, r.mat[3][0]);
		Assert::AreEqual(178.0f, r.mat[3][1]);
		Assert::AreEqual(166.0f, r.mat[3][2]);
		Assert::AreEqual(100.0f, r.mat[3][3]);
	}

	};
}