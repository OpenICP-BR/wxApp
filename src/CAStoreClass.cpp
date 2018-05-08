#include "CAStoreClass.h"
#include "EntityInfoClass.h"
#include "CAStoreClass-Data.h"
#include <wx/dir.h>

CAStoreClass::CAStoreClass() {
	// Create X509_STORE_CTX
	store = X509_STORE_new();
	if (store == NULL) {
		cout << "Failed to create X509_STORE_CTX." << endl;
	}

	// Add root certificates
	addCA(PEM2X509(icp_raiz_v1_pem));
	addCA(PEM2X509(icp_raiz_v2_pem));
	addCA(PEM2X509(icp_raiz_v5_pem));
	#ifdef USE_FAKE_ICP_ROOT
	addCA(PEM2X509(icp_fake_raiz_pem));
	#endif
}

bool CAStoreClass::addCA(X509 *cert) {
	if (cert == NULL) {
		return false;
	}
	if (X509_STORE_add_cert(store, cert) == 0) {
		return false;
	}

	X509_NAME *xname;
	char buf[999];

	xname = X509_get_subject_name(cert);
	X509_NAME_oneline(xname, buf, 999);
	printf("Added CA: %s\n", buf);

	return true;
}

bool CAStoreClass::AddCA_PEM(const char data[]) {
	return AddCA(PEM2X509(data));
}

bool CAStoreClass::AddAllCAsFromDir(wxString dir_path) {
	bool has_added = true;
	wxString filename;
	wxFileName dir_as_file;

	dir_as_file.Assign(dir_path);
	dir_as_file.MakeAbsolute();
	wxDir dir(dir_as_file.GetFullPath());

	while (has_added) {
		has_added = false;

		cout << "New round of looking for certificates in " << dir.GetName() << endl;
		bool cont = dir.GetFirst(&filename);
		while (cont) {
			has_added |= AddCA(FILE2X509(dir.GetNameWithSep()+filename));
			cont = dir.GetNext(&filename);
		}
	} 
	return true;
}

bool CAStoreClass::AddCA(X509 *cert) {
	if (cert == NULL) {
		return false;
	}
	
	X509_STORE_CTX *ctx = X509_STORE_CTX_new();
	if (ctx == NULL) {
		cout << "Failed to create X509_STORE_CTX" << endl;
		return false;
	}
	if (X509_STORE_CTX_init(ctx, store, cert, NULL) != 1) {
		cout << "Failed to initialize X509_STORE_CTX" << endl;
		X509_STORE_CTX_free(ctx);
		return false;
	}
	int rc = X509_verify_cert(ctx);
	X509_STORE_CTX_free(ctx);

	if (rc == 1) {
		return addCA(cert);
	}
	EntityInfoClass sub;
	sub.FromCert(cert, ENTITY_SUBJECT);
	cout << "Invalid CA: " + sub.OneLine()  << endl;
	return false;
}

CAStoreClass::~CAStoreClass() {
	X509_STORE_free(store);
}