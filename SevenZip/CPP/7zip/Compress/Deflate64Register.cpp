﻿// Deflate64Register.cpp

#include "../../../../ThirdParty/LZMA/CPP/7zip/Compress/StdAfx.h"

#include "../../../../ThirdParty/LZMA/CPP/7zip/Common/RegisterCodec.h"

#include "DeflateDecoder.h"

#if !defined(EXTRACT_ONLY) && !defined(DEFLATE_EXTRACT_ONLY)
#include "DeflateEncoder.h"
#endif

namespace NCompress {
namespace NDeflate {

REGISTER_CODEC_CREATE(CreateDec, NDecoder::CCOMCoder64())

#if !defined(EXTRACT_ONLY) && !defined(DEFLATE_EXTRACT_ONLY)
REGISTER_CODEC_CREATE(CreateEnc, NEncoder::CCOMCoder64())
#else
#define CreateEnc NULL
#endif

REGISTER_CODEC_2(Deflate64, CreateDec, CreateEnc, 0x40109, "Deflate64")

}}
