#include "TRIES.H"

void main() {
	Trie trie = createTrie();

	clrscr();

	addWord(trie, "Hello");
	addWord(trie, "Hi");
	addWord(trie, "Hifumi");
	addWord(trie, "Hellow");
	addWord(trie, "Here");
	addWord(trie, "Ball");
	addWord(trie, "Meow");

	if(searchWord(trie, "Hello")) printf("Found: Hello!\n");
	if(searchWord(trie, "Hell"))  printf("Found: Hell!\n");
	else printf("Hell: Not Found!\n");
	if(searchWord(trie, "Hi"))    printf("Found: Hi!\n");
	if(searchWord(trie, "Meow"))  printf("Found: Meow!\n\n");

	printf("Ball: %s (case 1)\n", strval(testCase(trie, "Ball", case1)));
	printf("Hi: %s (case 2)\n", strval(testCase(trie, "Hi", case2)));
	printf("Here: %s (case 3)\n", strval(testCase(trie, "Here", case3)));

	deleteWord(trie, "Ball");

	trieDelete(trie);

	getch();
}