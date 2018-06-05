package icp

import "encoding/asn1"

type SubjectKeyIdentifierT []byte
type SignatureValueT []byte

type SignerInfoT struct {
	RawContent         asn1.RawContent
	Version            CMSVersionT
	Sid_V1             IssuerAndSerialNumberT `asn1:"tag:optional,omitempty"`
	Sid_V3             SubjectKeyIdentifierT  `asn1:"tag:optional,omitempty"`
	DigestAlgorithm    DigestAlgorithmIdentifierT
	SignedAttrs        []Attribute `asn1:"tag:0,set,optional"`
	SignatureAlgorithm SignatureAlgorithmIdentifierT
	Signature          SignatureValueT
	UnsignedAttrs      []Attribute `asn1:"tag:1,set,optional"`
}
