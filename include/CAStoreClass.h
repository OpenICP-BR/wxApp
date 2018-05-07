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
	bool AddCA(X509 *cert);
	bool AddCA_PEM(const char data[]);
	bool AddAllCAsFromDir(const char path[]);
	~CAStoreClass();
};