#include <engine3D_trie.h>
#include <engine3D_util.h>

engine3D_trie_t *engine3D_trie_new(void) {
	return engine3D_util_safeMalloc(sizeof(engine3D_trie_t));
}

void engine3D_trie_init(engine3D_trie_t *const trie) {
	trie->hasValue = false;
	trie->childrenCapacity = 4;
	trie->childrenKeys = engine3D_util_safeMalloc(sizeof(char)*trie->childrenCapacity);
	trie->children = engine3D_util_safeMalloc(sizeof(engine3D_trie_t)*trie->childrenCapacity);
	trie->childrenNextIndex = 0;
}

void engine3D_trie_add(engine3D_trie_t *const trie, const char *const key, int value) {
	if (*key == '\0') {
		if (trie->hasValue) {
			engine3D_util_bail("attempt to add repeated key to trie");
		}
		else {
			trie->hasValue = true;
			trie->value = value;
		}
	}
	else {
		size_t i;
		bool found = false;
		for (i = 0; i < trie->childrenNextIndex; i++) {
			if (trie->childrenKeys[i] == *key) {
				found = true;
				break;
			}
		}

		if (!found) {
			if (trie->childrenNextIndex == trie->childrenCapacity) {
				trie->childrenCapacity *= 2;
				trie->childrenKeys = engine3D_util_safeRealloc(trie->childrenKeys, sizeof(char)*trie->childrenCapacity);
				trie->children = engine3D_util_safeRealloc(trie->children, sizeof(engine3D_trie_t)*trie->childrenCapacity);
			}
			else {
				trie->childrenKeys[trie->childrenNextIndex] = *key;
				engine3D_trie_init(trie->children + trie->childrenNextIndex);
			}
			i = trie->childrenNextIndex;
			trie->childrenNextIndex++;
		}

		engine3D_trie_add(trie->children + i, key + 1, value);
	}
}

int engine3D_trie_get(const engine3D_trie_t *const trie, const char *const key) {
	if (*key == '\0') {
		if (trie->hasValue) {
			return trie->value;
		}
		else {
			engine3D_util_bail("attempt to get non existing key from trie");
		}
	}
	else {
		size_t i;
		bool found = false;
		for (i = 0; i < trie->childrenNextIndex; i++) {
			if (trie->childrenKeys[i] == *key) {
				found = true;
				break;
			}
		}

		if (!found) {
			engine3D_util_bail("attempt to get non existing key from trie");
		}

		engine3D_trie_get(trie->children + i, key + 1);
	}
}