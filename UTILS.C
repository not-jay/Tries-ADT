#include "TRIES.H"

boolean isProperWord(char *str) {
	int i;

	for(i = 0; i < strlen(str); i++) {
		if(str[i] >= 'a' || str[i] <= 'z' || str[i] >= 'A' || str[i] <= 'Z')
			continue;
		else
			return false;
	}

	return true;
}

StringArray createStringArray() {
	StringArray array = (StringArray)calloc(1, sizeof(struct stra));
	array->strings = NULL;
	array->size = 0;

	return array;
}

/* Splits the string returned by getWords()
 * creating a StringArray */
StringArray stringSplit(char *str) {
	StringArray array = createStringArray();
	int i, spaces, temp;

	/* Count spaces */
	for(i = 0, spaces = 0; i < strlen(str); i++) {
		if(str[i] == ' ') spaces++;
	}

	/* Since #ofSpaces = #ofWords... */
	array->strings = (char **)calloc(spaces, sizeof(char *));
	array->size = spaces;

	for(i = 0, temp = 0; i < spaces; i++) {
		array->strings[i] = (char *)calloc(80, sizeof(char));
		while(str[temp] != ' ') {
			array->strings[i] = strncat(array->strings[i], &(str[temp++]), 1);
		}
		temp++;
	}

	return array;
}

void printArray(StringArray array) {
	int i;

	for(i = 0; i < array->size; i++) {
		puts(array->strings[i]);
	}
}