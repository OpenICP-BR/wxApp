#include "common.h"

class ConfigCertClass {
public:
	wxString name, email, cpf;
};

class ConfigClass {
public:
	std::map<wxString, ConfigCertClass> certificates;

};

//wxStandardPaths::GetUserDataDir