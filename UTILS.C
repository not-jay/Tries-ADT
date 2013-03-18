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