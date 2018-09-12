#include "setup_cgo.h"

const char OpenICP_Version[] = OPENICP_VERSION;
const int OpenICP_Version_Major = OPENICP_VERSION_MAJOR;
const int OpenICP_Version_Minor = OPENICP_VERSION_MINOR;
const int OpenICP_Version_Patch = OPENICP_VERSION_PATCH;
#ifdef OPENICP_VERSION_SUFFIX_EMPTY
const char OpenICP_Version_Suffix[] = OPENICP_VERSION_SUFFIX;
#else
const char OpenICP_Version_Suffix[] = "";
#endif

int get_openicp_version_major() {
	return OpenICP_Version_Major;
}

int get_openicp_version_minor() {
	return OpenICP_Version_Minor;
}

int get_openicp_version_patch() {
	return OpenICP_Version_Patch;
}

const char* get_openicp_version_suffix() {
	return OpenICP_Version_Suffix;
}
