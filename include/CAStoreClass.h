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
	bool Verify(CertClass cert);
	bool Verify(CertClass cert, int &error_int, wxString &error_string, int &error_depth, CertClass &error_cert);
	bool Verify(CertClass cert, wxString &error_string, STACK_OF(X509) *chain);
	bool Verify(X509 *cert);
	bool Verify(X509 *cert, int &error_int, wxString &error_string, int &error_depth, CertClass &error_cert);
	bool Verify(X509 *cert, int &error_int, wxString &error_string, int &error_depth, CertClass &error_cert, STACK_OF(X509) *chain);
	bool Verify(X509 *cert, wxString &error_string, STACK_OF(X509) *chain);
	bool AddCA(X509 *cert);
	bool AddCA_PEM(const char data[]);
	bool AddAllCAsFromDir(wxString dir_path);
	~CAStoreClass();
};

extern CAStoreClass CAStore;