#pragma once
#include "Common.h"
#include "CertClass.h"
#include <map>

class CAStoreClass {
	icp_store store;
protected:
	bool addCA(icp_cert cert);
public:
	CAStoreClass();
	bool Verify(CertClass cert);
	bool AddTestingRootCA(CertClass cert);
	bool AddCA(CertClass cert);
	bool AddCA_PEM(char data[]);
	bool AddAllCAsFromDir(wxString dir_path);
	~CAStoreClass();
};

extern CAStoreClass CAStore;