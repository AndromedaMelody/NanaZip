﻿// NsisDecode.h

#ifndef __NSIS_DECODE_H
#define __NSIS_DECODE_H

#include "../../../../../ThirdParty/LZMA/CPP/Common/MyBuffer.h"

#include "../../../../../ThirdParty/LZMA/CPP/7zip/Common/FilterCoder.h"
#include "../../../../../ThirdParty/LZMA/CPP/7zip/Common/StreamUtils.h"

#include "../../Compress/BZip2Decoder.h"
#include "../../Compress/DeflateDecoder.h"
#include "../../../../../ThirdParty/LZMA/CPP/7zip/Compress/LzmaDecoder.h"

namespace NArchive {
namespace NNsis {

namespace NMethodType
{
  enum EEnum
  {
    kCopy,
    kDeflate,
    kBZip2,
    kLZMA
  };
}

/* NanaZip installers 4.38 - 9.08 used modified version of NSIS that
   supported BCJ filter for better compression ratio.
   We support such modified NSIS archives. */

class CDecoder
{
  NMethodType::EEnum _curMethod; // method of created decoder

  CFilterCoder *_filter;
  CMyComPtr<ISequentialInStream> _filterInStream;
  CMyComPtr<ISequentialInStream> _codecInStream;
  CMyComPtr<ISequentialInStream> _decoderInStream;

  NCompress::NBZip2::CNsisDecoder *_bzDecoder;
  NCompress::NDeflate::NDecoder::CCOMCoder *_deflateDecoder;
  NCompress::NLzma::CDecoder *_lzmaDecoder;

public:
  CMyComPtr<IInStream> InputStream; // for non-solid
  UInt64 StreamPos; // the pos in unpacked for solid, the pos in Packed for non-solid

  NMethodType::EEnum Method;
  bool FilterFlag;
  bool Solid;
  bool IsNsisDeflate;

  CByteBuffer Buffer; // temp buf

  CDecoder():
      FilterFlag(false),
      Solid(true),
      IsNsisDeflate(true)
  {
    _bzDecoder = NULL;
    _deflateDecoder = NULL;
    _lzmaDecoder = NULL;
  }

  void Release()
  {
    _filterInStream.Release();
    _codecInStream.Release();
    _decoderInStream.Release();
    InputStream.Release();

    _bzDecoder = NULL;
    _deflateDecoder = NULL;
    _lzmaDecoder = NULL;
  }

  UInt64 GetInputProcessedSize() const;

  HRESULT Init(ISequentialInStream *inStream, bool &useFilter);

  HRESULT Read(void *data, size_t *processedSize)
  {
    return ReadStream(_decoderInStream, data, processedSize);;
  }


  HRESULT SetToPos(UInt64 pos, ICompressProgressInfo *progress); // for solid
  HRESULT Decode(CByteBuffer *outBuf, bool unpackSizeDefined, UInt32 unpackSize,
      ISequentialOutStream *realOutStream, ICompressProgressInfo *progress,
      UInt32 &packSizeRes, UInt32 &unpackSizeRes);
};

}}

#endif
