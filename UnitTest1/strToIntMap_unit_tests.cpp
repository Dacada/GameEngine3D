#include "stdafx.h"
#include "CppUnitTest.h"

extern "C" {
#include <engine3D_strToIntMap.h>
}

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(StrToIntMapUnitTests) {
public:

	TEST_METHOD(StrToIntMapTest1) {
		engine3D_strToIntMap_t *map = engine3D_strToIntMap_new();
		engine3D_strToIntMap_init(map);
		engine3D_strToIntMap_add(map, "a", 1);
		engine3D_strToIntMap_add(map, "b", 2);
		engine3D_strToIntMap_add(map, "c", 3);
		engine3D_strToIntMap_add(map, "d", 4);
		engine3D_strToIntMap_add(map, "e", 5);
		engine3D_strToIntMap_add(map, "f", 6);
		engine3D_strToIntMap_add(map, "g", 7);
		engine3D_strToIntMap_add(map, "h", 8);
		engine3D_strToIntMap_add(map, "i", 9);
		engine3D_strToIntMap_add(map, "j", 10);
		engine3D_strToIntMap_add(map, "k", 11);
		Assert::AreEqual(1, engine3D_strToIntMap_get(map, "a"));
		Assert::AreEqual(2, engine3D_strToIntMap_get(map, "b"));
		Assert::AreEqual(3, engine3D_strToIntMap_get(map, "c"));
		Assert::AreEqual(4, engine3D_strToIntMap_get(map, "d"));
		Assert::AreEqual(5, engine3D_strToIntMap_get(map, "e"));
		Assert::AreEqual(6, engine3D_strToIntMap_get(map, "f"));
		Assert::AreEqual(7, engine3D_strToIntMap_get(map, "g"));
		Assert::AreEqual(8, engine3D_strToIntMap_get(map, "h"));
		Assert::AreEqual(9, engine3D_strToIntMap_get(map, "i"));
		Assert::AreEqual(10, engine3D_strToIntMap_get(map, "j"));
		Assert::AreEqual(11, engine3D_strToIntMap_get(map, "k"));
		free(map);
	}

	TEST_METHOD(GrowingArrayTest2) {
		engine3D_strToIntMap_t *map = engine3D_strToIntMap_new();
		engine3D_strToIntMap_init(map);
		engine3D_strToIntMap_add(map, "aat", 1);
		engine3D_strToIntMap_add(map, "aqd", 2);
		engine3D_strToIntMap_add(map, "boe", 3);
		engine3D_strToIntMap_add(map, "cmf", 4);
		engine3D_strToIntMap_add(map, "dkg", 5);
		engine3D_strToIntMap_add(map, "dzx", 6);
		engine3D_strToIntMap_add(map, "eih", 7);
		engine3D_strToIntMap_add(map, "exy", 8);
		engine3D_strToIntMap_add(map, "fgi", 9);
		engine3D_strToIntMap_add(map, "fvz", 10);
		engine3D_strToIntMap_add(map, "gej", 11);
		Assert::AreEqual(1, engine3D_strToIntMap_get(map, "aat"));
		Assert::AreEqual(2, engine3D_strToIntMap_get(map, "aqd"));
		Assert::AreEqual(3, engine3D_strToIntMap_get(map, "boe"));
		Assert::AreEqual(4, engine3D_strToIntMap_get(map, "cmf"));
		Assert::AreEqual(5, engine3D_strToIntMap_get(map, "dkg"));
		Assert::AreEqual(6, engine3D_strToIntMap_get(map, "dzx"));
		Assert::AreEqual(7, engine3D_strToIntMap_get(map, "eih"));
		Assert::AreEqual(8, engine3D_strToIntMap_get(map, "exy"));
		Assert::AreEqual(9, engine3D_strToIntMap_get(map, "fgi"));
		Assert::AreEqual(10, engine3D_strToIntMap_get(map, "fvz"));
		Assert::AreEqual(11, engine3D_strToIntMap_get(map, "gej"));
		free(map);
	}

	};
}