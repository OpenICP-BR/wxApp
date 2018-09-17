#include "CAStoreClass.h"
#include <wx/dir.h>

CAStoreClass CAStore;

CAStoreClass::CAStoreClass() {
	store = icp_new_store(true);
	if (store == NULL) {
		wxLogDebug("Failed to create icp_store.");
		return;
	}
}

bool CAStoreClass::addCA(icp_cert cert) {
	if (cert == NULL) {
		return false;
	}

	icp_errc *errcs;
	int ans = icp_store_add_ca(store, cert, &errcs);
	for (int i=0; errcs[i] != NULL; i++) {
		wxLogDebug("CAStoreClass::addCA %s", icp_errc_code_str(errcs[i]));
	}
	icp_free_errcs(errcs);
	return ans == 0;
}

bool CAStoreClass::AddAllCAsFromDir(wxString dir_path) {
	return false;
}

bool CAStoreClass::Verify(CertClass cert) {
	icp_errc *errcs, *warns;
	icp_cert *chain;
	int ans = icp_store_verify(store, cert._get_raw(), &chain, &errcs, &warns);
	for (int i=0; errcs[i] != NULL; i++) {
		wxLogDebug("CAStoreClass::Verify %s", icp_errc_code_str(errcs[i]));
	}
	icp_free_errcs(errcs);
	for (int i=0; warns[i] != NULL; i++) {
		wxLogDebug("CAStoreClass::Verify %s", icp_errc_code_str(warns[i]));
	}
	icp_free_errcs(warns);
	icp_free_certs(chain);
	return ans == 0;
}

bool CAStoreClass::AddTestingRootCA(CertClass cert) {
	if (cert._get_raw() == NULL) {
		return false;
	}

	icp_errc *errcs;
	int ans = icp_store_add_ca(store, cert._get_raw(), &errcs);
	for (int i=0; errcs[i] != NULL; i++) {
		wxLogDebug("CAStoreClass::addCA %s", icp_errc_code_str(errcs[i]));
	}
	icp_free_errcs(errcs);
	return ans == 0;
}

CAStoreClass::~CAStoreClass() {
	icp_free_store(store);
}