#include "CAStoreClass.h"
#include "EntityInfoClass.h"
#include "CAStoreClass-Data.h"
#include <wx/dir.h>

CAStoreClass::CAStoreClass() {
	// Create X509_STORE_CTX
	store = X509_STORE_new();
	if (store == NULL) {
		wxLogDebug("Failed to create X509_STORE_CTX.");
		return;
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
	wxLogDebug("Added CA: %s", buf);

	return true;
}

bool CAStoreClass::AddCA_PEM(const char data[]) {
	return AddCA(PEM2X509(data));
}

bool CAStoreClass::AddAllCAsFromDir(wxString dir_path) {
	int total_counter=0;
	int counter=-999;
	wxString filename;
	wxFileName dir_as_file;

	wxLogDebug("Loading all CAs from %s", dir_path);
	dir_as_file.Assign(dir_path);
	dir_as_file.MakeAbsolute();

	if (!dir_as_file.DirExists()) {
		return false;
	}

	wxDir dir(dir_as_file.GetFullPath());

	while (counter != 0) {
		counter = 0;

		wxLogDebug("New round of looking for certificates in %s", dir.GetName());
		bool cont = dir.GetFirst(&filename);
		while (cont) {
			wxString full_path = dir.GetNameWithSep()+filename;
			if (AddCA(FILE2X509(full_path.mb_str()))) {
				counter++;
				total_counter++;
			}
			cont = dir.GetNext(&filename);
		}
	}
	wxLogDebug("Finished adding %d CAs from: %s", total_counter, dir.GetName());
	return true;
}

bool CAStoreClass::AddCA(X509 *cert) {
	if (cert == NULL) {
		return false;
	}
	
	X509_STORE_CTX *ctx = X509_STORE_CTX_new();
	if (ctx == NULL) {
		wxLogDebug("Failed to create X509_STORE_CTX");
		return false;
	}
	if (X509_STORE_CTX_init(ctx, store, cert, NULL) != 1) {
		wxLogDebug("Failed to initialize X509_STORE_CTX");
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
	wxLogDebug("Invalid CA: %s", sub.OneLine());
	return false;
}

CAStoreClass::~CAStoreClass() {
	X509_STORE_free(store);
}