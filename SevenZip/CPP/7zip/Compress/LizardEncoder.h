﻿// (C) 2017 Tino Reichardt

#define LIZARD_STATIC_LINKING_ONLY
#include "../../../../ThirdParty/LZMA/C/Alloc.h"
#include "../../../../ThirdParty/LZMA/C/Threads.h"
#include <lizard_compress.h>
#include <lizard_frame.h>
#include "../../../C/zstdmt/lizard-mt.h"

#include "../../../../ThirdParty/LZMA/CPP/Common/Common.h"
#include "../../../../ThirdParty/LZMA/CPP/Common/MyCom.h"
#include "../../../../ThirdParty/LZMA/CPP/7zip/ICoder.h"
#include "../../../../ThirdParty/LZMA/CPP/7zip/Common/StreamUtils.h"

#ifndef EXTRACT_ONLY
namespace NCompress {
namespace NLIZARD {

struct CProps
{
  CProps() { clear (); }
  void clear ()
  {
    memset(this, 0, sizeof (*this));
    _ver_major = LIZARD_VERSION_MAJOR;
    _ver_minor = LIZARD_VERSION_MINOR;
    _level = LIZARDMT_LEVEL_MIN;
  }

  Byte _ver_major;
  Byte _ver_minor;
  Byte _level;
};

class CEncoder:
  public ICompressCoder,
  public ICompressSetCoderMt,
  public ICompressSetCoderProperties,
  public ICompressWriteCoderProperties,
  public CMyUnknownImp
{
  CProps _props;

  UInt64 _processedIn;
  UInt64 _processedOut;
  UInt32 _inputSize;
  UInt32 _numThreads;

  LIZARDMT_CCtx *_ctx;

public:
  MY_QUERYINTERFACE_BEGIN2(ICompressCoder)
  MY_QUERYINTERFACE_ENTRY(ICompressSetCoderMt)
  MY_QUERYINTERFACE_ENTRY(ICompressSetCoderProperties)
  MY_QUERYINTERFACE_ENTRY(ICompressWriteCoderProperties)
  MY_QUERYINTERFACE_END
  MY_ADDREF_RELEASE

  STDMETHOD (Code)(ISequentialInStream *inStream, ISequentialOutStream *outStream, const UInt64 *inSize, const UInt64 *outSize, ICompressProgressInfo *progress);
  STDMETHOD (SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps);
  STDMETHOD (WriteCoderProperties)(ISequentialOutStream *outStream);
  STDMETHOD (SetNumberOfThreads)(UInt32 numThreads);

  CEncoder();
  virtual ~CEncoder();
};

}}
#endif
