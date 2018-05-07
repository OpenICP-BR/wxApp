#pragma once
#include "Common.h"
#include "CertClass.h"

class ConfigClass {
public:
	std::map<wxString, CertClass> user_certs;
	std::map<wxString, CertClass> cert_authorities;
};

//wxStandardPaths::GetUserDataDir