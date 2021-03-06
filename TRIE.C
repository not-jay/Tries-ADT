#include "TRIES.H"

Trie createTrie() {
	Trie trie = (Trie)calloc(1, sizeof(struct trie));
	trie->dummy = createNode();

	return trie;
}

void deleteTrie(Trie trie) {
	nodeDelete(trie->dummy);
	free(trie);
}

void addWord(Trie trie, char *str) {
	Node current = trie->dummy, child = NULL;
	int i;

	if(strlen(str) == 0) {
		current->endMarker = true;
		return;
	}

	for(i = 0; i < strlen(str); i++) {
		child = findChild(current, str[i]);

		if(child != NULL) current = child;
		else current = insertNode(current, str[i], false);

		if(i == (strlen(str) - 1)) current->endMarker = true;
	}
}

boolean searchWord(Trie trie, char *str) {
	Node current = trie->dummy, temp = NULL;
	int i;

	if(current == NULL) return false;

	for(i = 0; i < strlen(str); i++) {
		temp = findChild(current, str[i]);
		if(temp == NULL) return false;
		current = temp;
	}
	return current->endMarker;
}
/*
 * Trie deletion has 3 cases
 *
 * Case 1: The word is a separate branch in the tree and it doesn't have
 *         any other children. Simply delete the starting node.
 * Case 2: The word contains suffices. Only remove the "word" marker
 * Case 3: The reverse of Case 2. The word is a suffix. Delete only the
 *		   suffix
 *
 * This only replaces the deleted node with NULL and then calling the
 * sortChild() function and then realloc()
 *
 * realloc() only fails if size == 0 or if the block cannot be reallocated
 */
void deleteWord(Trie trie, char *str) {
	Node current = trie->dummy, temp = NULL;
	int i, tmp;

	if(!searchWord(trie, str)) return;

	/* Test for case 1*/
	if(testCase(trie, str, case1)) {
		/* Simply remove the node */
		i = findChildID(current, str[0]);
		nodeDelete(current->child[i]);
		resizeChildren(current);
	} else if(testCase(trie, str, case2)) { /* Test for case 2 */
		/* No real deletion occurs here, the nodes would
		 * still be there, but it makes the word unsearchable
		 */
		for(i = 0; i < strlen(str); i++) {
			current = findChild(current, str[i]);
		}
		current->endMarker = false;
	} else if(testCase(trie, str, case3)) { /* Test for case 3 */
		/* Traverse the word and keep track on which node
		 * had children > 1, then find the next matching node
		 * and delete it
		 */
		 temp = trie->dummy;

		 for(i = 0; i < strlen(str); i++) {
			temp = findChild(temp, str[i]);
			if(temp->children > 1) {
				current = temp;
				tmp = i+1;
			}
		 }
		 i = findChildID(current, str[tmp]);
		 nodeDelete(current->child[i]);
		 resizeChildren(current);
	}
}

boolean testCase(Trie trie, char *str, DeleteCase caseNum) {
	Node current = trie->dummy;
	boolean result = false;
	int i;

	switch(caseNum) {
		case case1:
			for(i = 0; i < strlen(str) - 1; i++) {
				current = findChild(current, str[i]);
				if(current->children > 1) return false;
			}
			result = !(current->children > 1);
			break;
		case case2:
			for(i = 0; i < strlen(str); i++) {
				current = findChild(current, str[i]);
			}
			result = (current->children >= 1);
			break;
		case case3:
			result = !testCase(trie, str, case2);
			break;
	}

	return result;
}