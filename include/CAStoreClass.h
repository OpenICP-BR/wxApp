#include "Common.h"
#include "CertClass.h"
#include <map>

class CAStoreClass {
	std::map<x509_hash, CertClass> CAs;
	X509_STORE_CTX *ctx;
public:
	CAStoreClass();
	bool Verify(X509 *cert);
	bool AddIfValid(X509 *cert);
	~CAStoreClass();
};