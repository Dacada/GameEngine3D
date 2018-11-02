#include "stdafx.h"
#include "CppUnitTest.h"

extern "C" {
#include <engine3D_growingArray.h>
}

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(GrowingArrayUnitTests) {
public:

	TEST_METHOD(GrowingArrayTest1) {
		engine3D_growingArray_t arr;
		engine3D_growingArray_init(&arr, sizeof(double), 8);

		for (int i = 0; i < 1000; i++) {
			double *element = (double*)engine3D_growingArray_add(&arr);
			*element = (double)i;
		}

		double *elements = (double*)engine3D_growingArray_finish(&arr, true);

		for (int i = 0; i < 1000; i++) {
			Assert::AreEqual((double)i, elements[i]);
		}
	}

	TEST_METHOD(GrowingArrayTest2) {
		engine3D_growingArray_t arr;
		engine3D_growingArray_init(&arr, sizeof(double), 8);

		engine3D_growingArray_ensureGrowth(&arr, 1000);

		for (int i = 0; i < 1000; i++) {
			double *element = (double*)engine3D_growingArray_add(&arr);
			*element = (double)i;
		}

		double *elements = (double*)engine3D_growingArray_finish(&arr, false);

		for (int i = 0; i < 1000; i++) {
			Assert::AreEqual((double)i, elements[i]);
		}
	}

	};
}