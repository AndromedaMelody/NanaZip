﻿// Pbkdf2HmacSha1.h
// Password-Based Key Derivation Function (RFC 2898, PKCS #5) based on HMAC-SHA-1

#ifndef __CRYPTO_PBKDF2_HMAC_SHA1_H
#define __CRYPTO_PBKDF2_HMAC_SHA1_H

#include <stddef.h>

#include "../../../../ThirdParty/LZMA/CPP/Common/MyTypes.h"

namespace NCrypto {
namespace NSha1 {

void Pbkdf2Hmac(const Byte *pwd, size_t pwdSize, const Byte *salt, size_t saltSize,
    UInt32 numIterations, Byte *key, size_t keySize);

}}

#endif
