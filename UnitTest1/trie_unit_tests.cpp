#include "stdafx.h"
#include "CppUnitTest.h"

extern "C" {
#include <engine3D_trie.h>
}

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(TrieUnitTests) {
public:

	TEST_METHOD(TrieTest) {
		engine3D_trie_t *trie;
		trie = engine3D_trie_new();
		engine3D_trie_init(trie);

		engine3D_trie_add(trie, "a", 15);
		engine3D_trie_add(trie, "to", 7);
		engine3D_trie_add(trie, "tea", 3);
		engine3D_trie_add(trie, "ted", 4);
		engine3D_trie_add(trie, "ten", 12);
		engine3D_trie_add(trie, "i", 11);
		engine3D_trie_add(trie, "in", 5);
		engine3D_trie_add(trie, "inn", 9);

		Assert::AreEqual(15, engine3D_trie_get(trie, "a"));
		Assert::AreEqual(7, engine3D_trie_get(trie, "to"));
		Assert::AreEqual(3, engine3D_trie_get(trie, "tea"));
		Assert::AreEqual(4, engine3D_trie_get(trie, "ted"));
		Assert::AreEqual(12, engine3D_trie_get(trie, "ten"));
		Assert::AreEqual(11, engine3D_trie_get(trie, "i"));
		Assert::AreEqual(5, engine3D_trie_get(trie, "in"));
		Assert::AreEqual(9, engine3D_trie_get(trie, "inn"));
	}

	};
}