﻿// FindSignature.h

#ifndef __FIND_SIGNATURE_H
#define __FIND_SIGNATURE_H

#include "../../../../../ThirdParty/LZMA/CPP/7zip/IStream.h"

HRESULT FindSignatureInStream(ISequentialInStream *stream,
    const Byte *signature, unsigned signatureSize,
    const UInt64 *limit, UInt64 &resPos);

#endif
