﻿// MemBlocks.h

#ifndef __MEM_BLOCKS_H
#define __MEM_BLOCKS_H

#include "../../../../ThirdParty/LZMA/CPP/Common/MyVector.h"

#include "../../../../ThirdParty/LZMA/CPP/Windows/Synchronization.h"

#include "../../../../ThirdParty/LZMA/CPP/7zip/IStream.h"

class CMemBlockManager
{
  void *_data;
  size_t _blockSize;
  void *_headFree;
public:
  CMemBlockManager(size_t blockSize = (1 << 20)): _data(NULL), _blockSize(blockSize), _headFree(NULL) {}
  ~CMemBlockManager() { FreeSpace(); }

  bool AllocateSpace_bool(size_t numBlocks);
  void FreeSpace();
  size_t GetBlockSize() const { return _blockSize; }
  void *AllocateBlock();
  void FreeBlock(void *p);
};


class CMemBlockManagerMt: public CMemBlockManager
{
  NWindows::NSynchronization::CCriticalSection _criticalSection;
public:
  SYNC_OBJ_DECL(Synchro);
  NWindows::NSynchronization::CSemaphore_WFMO Semaphore;

  CMemBlockManagerMt(size_t blockSize = (1 << 20)): CMemBlockManager(blockSize) {}
  ~CMemBlockManagerMt() { FreeSpace(); }

  HRes AllocateSpace(size_t numBlocks, size_t numNoLockBlocks);
  HRes AllocateSpaceAlways(size_t desiredNumberOfBlocks, size_t numNoLockBlocks = 0);
  void FreeSpace();
  void *AllocateBlock();
  void FreeBlock(void *p, bool lockMode = true);
  // WRes ReleaseLockedBlocks_WRes(unsigned number) { return Semaphore.Release(number); }
};


class CMemBlocks
{
  void Free(CMemBlockManagerMt *manager);
public:
  CRecordVector<void *> Blocks;
  UInt64 TotalSize;

  CMemBlocks(): TotalSize(0) {}

  void FreeOpt(CMemBlockManagerMt *manager);
  HRESULT WriteToStream(size_t blockSize, ISequentialOutStream *outStream) const;
};

struct CMemLockBlocks: public CMemBlocks
{
  bool LockMode;

  CMemLockBlocks(): LockMode(true) {};
  void Free(CMemBlockManagerMt *memManager);
  void FreeBlock(unsigned index, CMemBlockManagerMt *memManager);
  // HRes SwitchToNoLockMode(CMemBlockManagerMt *memManager);
  void Detach(CMemLockBlocks &blocks, CMemBlockManagerMt *memManager);
};

#endif
