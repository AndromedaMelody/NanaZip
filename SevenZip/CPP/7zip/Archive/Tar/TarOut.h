﻿// Archive/TarOut.h

#ifndef __ARCHIVE_TAR_OUT_H
#define __ARCHIVE_TAR_OUT_H

#include "../../../../../ThirdParty/LZMA/CPP/Common/MyCom.h"

#include "../../../../../ThirdParty/LZMA/CPP/7zip/IStream.h"

#include "TarItem.h"

namespace NArchive {
namespace NTar {

class COutArchive
{
  CMyComPtr<ISequentialOutStream> Stream;

  AString Glob_Name;
  AString Prefix;

  HRESULT WriteHeaderReal(const CItem &item, bool isPax = false
      // , bool zero_PackSize = false
      // , bool zero_MTime = false
      );

  HRESULT Write_Data(const void *data, unsigned size);
  HRESULT Write_Data_And_Residual(const void *data, unsigned size);

public:
  UInt64 Pos;
  bool IsPosixMode;
  // bool IsPrefixAllowed; // it's used only if (IsPosixMode == true)
  CTimeOptions TimeOptions;

  void Create(ISequentialOutStream *outStream)
  {
    Stream = outStream;
  }
  HRESULT WriteHeader(const CItem &item);
  HRESULT Write_AfterDataResidual(UInt64 dataSize);
  HRESULT WriteFinishHeader();

  COutArchive():
      Pos(0),
      IsPosixMode(false)
      // , IsPrefixAllowed(true)
      {}
};

}}

#endif
