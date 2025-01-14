﻿// LzhDecoder.h

#ifndef __COMPRESS_LZH_DECODER_H
#define __COMPRESS_LZH_DECODER_H

#include "../../../../ThirdParty/LZMA/CPP/Common/MyCom.h"

#include "../../../../ThirdParty/LZMA/CPP/7zip/ICoder.h"

#include "../../../../ThirdParty/LZMA/CPP/7zip/Common/InBuffer.h"

#include "BitmDecoder.h"
#include "HuffmanDecoder.h"
#include "LzOutWindow.h"

namespace NCompress {
namespace NLzh {
namespace NDecoder {

const unsigned kMatchMinLen = 3;
const unsigned kMatchMaxLen = 256;
const unsigned NC = (256 + kMatchMaxLen - kMatchMinLen + 1);
const unsigned NUM_CODE_BITS = 16;
const unsigned NUM_DIC_BITS_MAX = 25;
const unsigned NT = (NUM_CODE_BITS + 3);
const unsigned NP = (NUM_DIC_BITS_MAX + 1);
const unsigned NPT = NP; // Max(NT, NP)

class CCoder:
  public ICompressCoder,
  public CMyUnknownImp
{
  CLzOutWindow _outWindow;
  NBitm::CDecoder<CInBuffer> _inBitStream;

  int _symbolT;
  int _symbolC;

  NHuffman::CDecoder<NUM_CODE_BITS, NPT> _decoderT;
  NHuffman::CDecoder<NUM_CODE_BITS, NC> _decoderC;

  class CCoderReleaser
  {
    CCoder *_coder;
  public:
    CCoderReleaser(CCoder *coder): _coder(coder) {}
    void Disable() { _coder = NULL; }
    ~CCoderReleaser() { if (_coder) _coder->_outWindow.Flush(); }
  };
  friend class CCoderReleaser;

  bool ReadTP(unsigned num, unsigned numBits, int spec);
  bool ReadC();

  HRESULT CodeReal(UInt64 outSize, ICompressProgressInfo *progress);
public:
  MY_UNKNOWN_IMP

  UInt32 DictSize;
  bool FinishMode;

  STDMETHOD(Code)(ISequentialInStream *inStream, ISequentialOutStream *outStream,
      const UInt64 *inSize, const UInt64 *outSize, ICompressProgressInfo *progress);

  void SetDictSize(unsigned dictSize) { DictSize = dictSize; }

  CCoder(): DictSize(1 << 16), FinishMode(false) {}

  UInt64 GetInputProcessedSize() const { return _inBitStream.GetProcessedSize(); }
};

}}}

#endif
