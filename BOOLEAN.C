#include "Tries.h"

char * strval(boolean b) {
	return (b)?"true":"false";
}

boolean valueof(char *str) {
	if(!strcmpi(str, "true")) return true;
	if(!strcmpi(str, "false")) return false;

	return false;
}