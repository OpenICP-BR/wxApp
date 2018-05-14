#pragma once
#include "Common.h"
#include "CertClass.h"
#include <map>

class CAStoreClass {
	std::map<x509_hash, CertClass> CAs;
	X509_STORE *store;
protected:
	bool addCA(X509 *cert);
public:
	CAStoreClass();
	bool Verify(X509 *cert);
	bool Verify(X509 *cert, int &error_int, wxString &error_string, int &error_depth, CertClass &error_cert);
	bool AddCA(X509 *cert);
	bool AddCA_PEM(const char data[]);
	bool AddAllCAsFromDir(wxString dir_path);
	~CAStoreClass();
};

extern CAStoreClass CAStore;