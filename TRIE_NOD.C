#include "TRIES.H"

Node createNode() {
	Node node = (Node)calloc(1, sizeof(struct node));
	node->c = ' ';
	node->endMarker = false;
	node->children = 0;
	node->child = NULL;

	return node;
}

boolean deleteNode(Node node) {
	int i;

	if(node->child != NULL) {
		for(i = 0; i < node->children; i++) {
			nodeDelete(node->child[i]);
		}
		freeAndClean(node->child);
	}

	freeAndClean(node);

	return true;
}

int findChildID(Node node, char c) {
	int i;

	if(node->child == NULL) return -1;

	for(i = 0; i < node->children; i++) {
		if(node->child[i]->c == c) return i;
	}

	return -1;
}

Node findChild(Node node, char c) {
	int i;

	if(node->child == NULL) return NULL;

	for(i = 0; i < node->children; i++) {
		if(node->child[i]->c == c) return node->child[i];
	}

	return NULL;
}

Node insertNode(Node node, char c, boolean b) {
	if(node->child != NULL) {
		node->child = realloc(node->child, sizeof(Node) * (node->children + 1));
		node->children++;
	} else {
		node->child = (struct node **)calloc(1, sizeof(Node));
		node->children++;
	}

	node->child[node->children - 1] = createNode();
	node->child[node->children - 1]->c = c;
	node->child[node->children - 1]->endMarker = b;

	return node->child[node->children - 1];
}

/* Algo:
 * "Sorts" the node->child array so that the proper nodes come first
 * and the NULLs afterward, then trims down the array to the proper size
 *
 * Revision:
 * Instead of using realloc() for trimming, a new array is made and the
 * proper nodes are transferred.
 */
void resizeChildren(Node node) {
	int tmp, i, count = 0;
	Node *newArray = NULL;

	/* Count number of nulls */
	for(i = 0; i < node->children; i++) {
		if(node->child[i] == NULL) count++;
	}

	/* Update counter to reflect the number of proper nodes
	   and prep newArray. */
	node->children -= count;
	newArray = (Node *)calloc(node->children, sizeof(Node));

	/* Add all proper nodes into newArray, since it hasn't been
	   sorted yet, we'll use node->children+count */
	for(i = 0, tmp = 0; i < (node->children + count); i++) {
		if(node->child[i] != NULL) {
			newArray[tmp] = createNode();
			newArray[tmp]->c = node->child[i]->c;
			newArray[tmp]->endMarker = node->child[i]->endMarker;
			newArray[tmp]->children = node->child[i]->children;
			newArray[tmp]->child = node->child[i]->child;
			tmp++;
		}
	}

	/* Delete the child node and replace it with newArray */
	freeAndClean(node->child);
	node->child = newArray;
}

/* Creates a string of the node's children separated by a space
 * It doesn't include the character in the node
 * ie.
 * For a tries wi;th the words "Hi" and "Hello"
 * calling this function getWords(trie->dummy->child[0], "")
 * would return the string "i ello "
 * calling the function as getWords(trie->dummy->child[0], "H") however
 * would return the string "Hi Hello " */
char * getWords(Node node, char *prefix) {
	char *words = (char *)calloc(80, sizeof(char));
	char *temp = (char *)calloc(80, sizeof(char));
	int i;

	if(node->endMarker) {
		words = strcat(words, prefix);
		words = strcat(words, " ");
	}

	for(i = 0; i < node->children; i++) {
		temp = strcpy(temp, prefix);
		temp = strncat(temp, &(node->child[i]->c), 1);
		words = strcat(words, getWords(node->child[i], temp));
	}

	return words;
}