#ifndef __TRIES_H
#define __TRIES_H

#include <string.h>
#include <stdlib.h>

/* Utility Macros
 * Mostly used for assigning a recently free()'d ptr to NULL
 * Preventing invalid memory location access and thereby preventing
 * undefined program behavior
 */
#define arraysize(A, B) (sizeof(A)/sizeof(B))
#define nodeDelete(A) deleteNode(A); A = NULL
#define freeAndClean(A) free(A); A = NULL
#define trieDelete(A) deleteTrie(A); A = NULL

typedef enum {false, true} boolean;
typedef enum {case1, case2, case3} DeleteCase;

struct node {
	char c;
	boolean endMarker;
	int children;
	struct node **child;
};

struct trie {
	struct node *dummy;
};

typedef struct node *Node;
typedef struct trie *Trie;

/* Node functions */
Node createNode();
boolean deleteNode(Node);
int findChildID(Node, char);
Node findChild(Node, char);
Node insertNode(Node, char, boolean);
void resizeChildren(Node);

/* Trie functions */
Trie createTrie();
void deleteTrie(Trie);
void addWord(Trie, char *);
boolean searchWord(Trie, char *);
void deleteWord(Trie, char *);
boolean testCase(Trie, char *, DeleteCase);
char ** getMatchingWords(Node, char *);

/* Misc. (Boolean) functions */
char * strval(boolean);
boolean valueof(char *);
boolean isProperWord(char *);

#endif