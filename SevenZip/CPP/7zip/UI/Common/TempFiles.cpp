﻿// TempFiles.cpp

#include "StdAfx.h"

#include "../../../../../ThirdParty/LZMA/CPP/Windows/FileDir.h"

#include "TempFiles.h"

using namespace NWindows;
using namespace NFile;

void CTempFiles::Clear()
{
  while (!Paths.IsEmpty())
  {
    NDir::DeleteFileAlways(Paths.Back());
    Paths.DeleteBack();
  }
}
