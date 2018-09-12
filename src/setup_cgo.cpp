#include "common.h"

char** str_array_new(int n) {
	return (char**) malloc(n * sizeof(char *));
}

void str_array_set(char **v, int i, char *s) {
	v[i] = s;
}

void str_array_free(int n, char **v) {
	for (int i=0; i < n; i++) {
		free(v[i]);
	}
	free(v);
}

int start_app(int argc, char **argv) {
	return wxEntry(argc, argv);
}
