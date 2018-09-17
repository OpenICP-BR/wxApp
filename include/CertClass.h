#pragma once
#include <time.h>
#include "Common.h"

class CertClass {
protected:
	icp_cert cert;
	wxString fp_sha_256_human, fp_sha_256_fs;
public:
	CertClass();
	CertClass(icp_cert new_cert);
	bool LoadPEMString(char buf[]);
	bool LoadPEMFile(char path[]);
	bool LoadCert(icp_cert new_cert);
	wxString NotBeforeString();
	wxString NotAfterString();
	wxString NiceName();
	wxString FingerPrintSHA256_HumanReadable();
	wxString FingerPrintSHA256_FileFriendly();
	wxString Subject, Issuer;
	map<wxString, wxString> SubjectMap, IssuerMap;
	wxDateTime NotBefore, NotAfter;
	icp_cert _get_raw();
	~CertClass();
};
