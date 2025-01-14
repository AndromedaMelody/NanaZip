﻿/*
 * PROJECT:   NanaZip
 * FILE:      Xxh32Handler.cpp
 * PURPOSE:   Implementation for XXH32 hash algorithm
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

class CXxh32Handler :
    public IHasher,
    public CMyUnknownImp
{
    XXH32_state_t* Context;
    Byte mtDummy[1 << 7];

public:

    CXxh32Handler()
    {
        this->Context = ::XXH32_createState();
    }

    ~CXxh32Handler()
    {
        ::XXH32_freeState(this->Context);
    }

    MY_UNKNOWN_IMP1(IHasher)
    INTERFACE_IHasher(;)
};

STDMETHODIMP_(void) CXxh32Handler::Init() throw()
{
    ::XXH32_reset(this->Context, 0);
}

STDMETHODIMP_(void) CXxh32Handler::Update(
    const void* data,
    UInt32 size) throw()
{
    ::XXH32_update(this->Context, data, size);
}

STDMETHODIMP_(void) CXxh32Handler::Final(Byte* digest) throw()
{
    XXH32_hash_t FinalDigest = ::XXH32_digest(this->Context);
    std::memcpy(digest, &FinalDigest, 4);
}

REGISTER_HASHER(
    CXxh32Handler,
    0x2F1,
    "XXH32",
    4)
