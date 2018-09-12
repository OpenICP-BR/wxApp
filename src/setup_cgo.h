#include <stdlib.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define OPENICP_VERSION_MAJOR 0
#define OPENICP_VERSION_MINOR 3
#define OPENICP_VERSION_PATCH 0
#ifndef OPENICP_VERSION_SUFFIX
	#define OPENICP_VERSION_SUFFIX "dev"
#endif

#ifdef OPENICP_VERSION_SUFFIX_EMPTY
	#define OPENICP_VERSION STR(OPENICP_VERSION_MAJOR) "." STR(OPENICP_VERSION_MINOR) "." STR(OPENICP_VERSION_PATCH)
#else
	#define OPENICP_VERSION STR(OPENICP_VERSION_MAJOR) "." STR(OPENICP_VERSION_MINOR) "." STR(OPENICP_VERSION_PATCH) "-" OPENICP_VERSION_SUFFIX
#endif

extern const char OpenICP_Version[];
extern const int OpenICP_Version_Major;
extern const int OpenICP_Version_Minor;
extern const int OpenICP_Version_Patch;
extern const char OpenICP_Version_Suffix[];

#ifdef __cplusplus
extern "C" {
#endif
	int    start_app(int argc, char **argv);
	char** str_array_new(int n);
	void   str_array_set(char **v, int i, char *s);
	void   str_array_free(int n, char **v);
	int    get_openicp_version_major();
	int    get_openicp_version_minor();
	int    get_openicp_version_patch();
	const char* get_openicp_version_suffix();
#ifdef __cplusplus
}
#endif