#include "CertClass.h"
#include "gtest/gtest.h"

TEST(CertClassTest, LoadPEMString_1) {
	// ciclano.cert.pem
	const char *pem = "-----BEGIN CERTIFICATE-----\nMIIEMjCCAhoCAhAEMA0GCSqGSIb3DQEBCwUAMEAxCzAJBgNVBAYTAkJSMQswCQYD\nVQQIDAJGTjERMA8GA1UECgwIRmFrZUJhbmsxETAPBgNVBAMMCEZha2VCYW5rMB4X\nDTE4MDUwMzE4NDQxMloXDTE5MDUxMzE4NDQxMlowfTELMAkGA1UEBhMCQlIxCzAJ\nBgNVBAgMAkZOMQ0wCwYDVQQHDARJbGhhMRAwDgYDVQQKDAdGYWtlUEtJMRwwGgYD\nVQQDDBNDaWNsYW5vIENpY2xhbsOzaWRlMSIwIAYJKoZIhvcNAQkBFhNjaWNsYW5v\nQGV4YW1wbGUuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtisx\nUQVMBok9YmudWUub1IGDFSyq68OARHD5Rajdu0Ap9kmXv662kMMwJDeMn+hZSuww\n+5nrezSG7N0fqtBJf9mdyIf2JnEYnfkT65eyNbQjyKogzM++RYQ7K+maPEeo/ip1\nues2kC2+VkalRSGkbBKd5tvvbI9fPprVdT5Ky+/GNVAkva0elPVpEJh4jEMqalPT\nx18xCPXNYb7U7QdJf3oIETr5BtLBcmffVggYcDiYX+BwA5701YjwbuHmJ/I+mD1M\nF6IDosvCVaXXprfJkrjUoY/kS2hcWLAb4SYMJwcK/fo4IS9+OHQ4APqjLSuj1phz\nIPJV3UfrtM9KYCfDtwIDAQABMA0GCSqGSIb3DQEBCwUAA4ICAQDDiMj07xBFtte6\nn1WbfKKBTARnBA9K6egbKeKtOjRJPpv3SKUE8Np55rNMH5Rtv8sLwUEgIR1K/Hep\nSPseOQ41rmvsy3XUx/ohw/yAo6dgNUvY8ZpXZvRreObe42rdi22bU3fNlrduArF5\nUvFlgM03KKzpnm64JNuc5tZ+NoZDUmKruZlB6h481xBCRUxElCMMC52r2/jvUz+d\nAWwdi3DvZlhr+Fdv/aUrQwrecJ/0Ot8h9w18GeurygyLO6Z/C7lKN7sfy49gJzHG\nnhlvKkl7sN6ZJ/mI+IEnc4F+9Bnfohj1rQFKeVjNH4lOb5F6ZnmzOyvwIoNBUTmk\n8rfOphcxhQmSvSrl4xGDOD6LrL5GUt+D8V9dj8nFnVidWR9vJzTXPgjucZy9CFb4\nzBdc9jPL544x3xmoCQfZIrKTKsJDmujjbFooF2V0VxGWZ+uXQmHy53kgiHbvCU7G\nThSAHv4vM8PSWSYKZ0FRC3LYJaULhuJGw5j/YDN2lF8utkMEsodEjwjeShR49Wmu\ns2tjSJmqSRqnkFkIX4d1twqEakBtqTMGbVuArMm+pXA42RGLaLHH/3/EreXrp8A0\nAT40KxMmK4+e9ioRmSm2D+CAi+nFTQKsr13Q9aosuCt/vboTTB4D5LlQU7AITsyp\ny+5qaw5AI5Hl+ogIxTW2LmqmuPNXMA==\n-----END CERTIFICATE-----";
    CertClass cert;
    EXPECT_EQ(cert.LoadPEMString(pem), true);

    EXPECT_EQ(cert.Subject.Country(), wxString("BR"));
    EXPECT_EQ(cert.Subject.State(), wxString("FN"));
    EXPECT_EQ(cert.Subject.Locality(), wxString("Ilha"));
    EXPECT_EQ(cert.Subject.Organization(), wxString("FakePKI"));
    EXPECT_EQ(cert.Subject.OrganizationUnit(), wxString(""));
    EXPECT_EQ(cert.Subject.CommonName(), wxString::FromUTF8("Ciclano Ciclan\xC3\xB3ide"));
    EXPECT_EQ(cert.Subject.DocID(), wxString::FromUTF8("---n\xC3\xA3o consta---"));
    EXPECT_EQ(cert.Subject.Email(), wxString("ciclano@example.com"));
    EXPECT_EQ(cert.Subject.OneLine(), wxString("/C=BR/ST=FN/L=Ilha/O=FakePKI/CN=Ciclano Ciclan\\xC3\\xB3ide/emailAddress=ciclano@example.com"));
    EXPECT_EQ(cert.Subject.Hash(), 0x0be9bcaa);
    EXPECT_EQ(cert.Subject.HashString(), wxString("0be9bcaa"));

    EXPECT_EQ(cert.NotBeforeString(), wxString("2018-05-03 18:44:12+00:00"));
    EXPECT_EQ(cert.NotAfterString(), wxString("2019-05-13 18:44:12+00:00"));

    EXPECT_EQ(cert.FingerPrintSHA256(), wxString("EC:E3:7D:A8:8B:2E:C7:69:06:DE:70:1D:38:08:AE:1E:37:B5:F5:E3:46:77:A5:82:56:D2:B0:99:BB:6A:79:C5"));

    EXPECT_EQ(cert.Issuer.Country(), wxString("BR"));
    EXPECT_EQ(cert.Issuer.State(), wxString("FN"));
    EXPECT_EQ(cert.Issuer.Locality(), wxString(""));
    EXPECT_EQ(cert.Issuer.Organization(), wxString("FakeBank"));
    EXPECT_EQ(cert.Issuer.OrganizationUnit(), wxString(""));
    EXPECT_EQ(cert.Issuer.CommonName(), wxString("FakeBank"));
    EXPECT_EQ(cert.Issuer.DocID(), wxString::FromUTF8("---n\xC3\xA3o consta---"));
    EXPECT_EQ(cert.Issuer.Email(), wxString(""));
    EXPECT_EQ(cert.Issuer.OneLine(), wxString("/C=BR/ST=FN/O=FakeBank/CN=FakeBank"));
    EXPECT_EQ(cert.Issuer.Hash(), 0x4dfa8cfc);
    EXPECT_EQ(cert.Issuer.HashString(), wxString("4dfa8cfc"));
}