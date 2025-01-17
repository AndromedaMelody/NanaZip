﻿/*
 * PROJECT:   NanaZip
 * FILE:      Xxh3128Handler.cpp
 * PURPOSE:   Implementation for XXH3_128bits hash algorithm
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: MouriNaruto (KurikoMouri@outlook.jp)
 */

#include "../../../ThirdParty/LZMA/C/CpuArch.h"
#include "../../../ThirdParty/LZMA/CPP/Common/MyCom.h"
#include "../../../ThirdParty/LZMA/CPP/7zip/Common/RegisterCodec.h"

#include <cstring>

#define XXH_STATIC_LINKING_ONLY
#include <xxhash.h>

class CXxh3128Handler :
    public IHasher,
    public CMyUnknownImp
{
    XXH3_state_t* Context;
    Byte mtDummy[1 << 7];

public:

    CXxh3128Handler()
    {
        this->Context = ::XXH3_createState();
    }

    ~CXxh3128Handler()
    {
        ::XXH3_freeState(this->Context);
    }

    MY_UNKNOWN_IMP1(IHasher)
    INTERFACE_IHasher(;)
};

STDMETHODIMP_(void) CXxh3128Handler::Init() throw()
{
    ::XXH3_128bits_reset(this->Context);
}

STDMETHODIMP_(void) CXxh3128Handler::Update(
    const void* data,
    UInt32 size) throw()
{
    ::XXH3_128bits_update(this->Context, data, size);
}

STDMETHODIMP_(void) CXxh3128Handler::Final(Byte* digest) throw()
{
    XXH128_hash_t FinalDigest = ::XXH3_128bits_digest(this->Context);
    std::memcpy(digest, &FinalDigest, 16);
}

REGISTER_HASHER(
    CXxh3128Handler,
    0x2F4,
    "XXH3_128bits",
    16)
