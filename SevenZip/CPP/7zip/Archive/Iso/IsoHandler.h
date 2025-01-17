﻿// IsoHandler.h

#ifndef __ISO_HANDLER_H
#define __ISO_HANDLER_H

#include "../../../../../ThirdParty/LZMA/CPP/Common/MyCom.h"

#include "../../../../../ThirdParty/LZMA/CPP/7zip/Archive/IArchive.h"

#include "IsoIn.h"
#include "IsoItem.h"

namespace NArchive {
namespace NIso {

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
  CMyComPtr<IInStream> _stream;
  CInArchive _archive;
public:
  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

}}

#endif
