#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
	int start_app(int argc, char **argv);
	char** str_array_new(int n);
	void str_array_set(char **v, int i, char *s);
	void str_array_free(int n, char **v);
#ifdef __cplusplus
}
#endif