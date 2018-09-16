#include "stdafx.h"
#include "CppUnitTest.h"

extern "C" {
#include <engine3D_time.h>
}

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(TimeUnitTests) {
	public:

		TEST_METHOD(GetTimeTest) {
			engine3D_timer_init();
			double t = engine3D_timer_getTime();
			Sleep(100);
			double diff = engine3D_timer_getTime() - t;

			Assert::AreEqual(0.1, diff / engine3D_timer_second, 0.01);
		}

		TEST_METHOD(GetDeltaTest) {
			double d = 123.456;
			engine3D_time_setDelta(d);
			Assert::AreEqual(d, engine3D_time_getDelta());
		}

	};
}