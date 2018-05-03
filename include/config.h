#pragma once
#include "common.h"
#include "cert_class.h"

class ConfigClass {
public:
	std::map<wxString, CertClass> user_certs;
	std::map<wxString, CertClass> cert_authorities;
};

//wxStandardPaths::GetUserDataDir