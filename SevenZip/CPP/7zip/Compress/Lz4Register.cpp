﻿// (C) 2016 Tino Reichardt

#include "../../../../ThirdParty/LZMA/CPP/7zip/Compress/StdAfx.h"

#include "../../../../ThirdParty/LZMA/CPP/7zip/Common/RegisterCodec.h"

#include "Lz4Decoder.h"

#ifndef EXTRACT_ONLY
#include "Lz4Encoder.h"
#endif

REGISTER_CODEC_E(
  LZ4,
  NCompress::NLZ4::CDecoder(),
  NCompress::NLZ4::CEncoder(),
  0x4F71104, "LZ4")
