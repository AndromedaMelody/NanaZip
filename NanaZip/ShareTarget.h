#pragma once

#ifndef NANAZIP_FILEMANAGER_SHARETARGET
#define NANAZIP_FILEMANAGER_SHARETARGET

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#else
#error "[Mile] You should use a C++ compiler with the C++17 standard."
#endif

namespace NanaZip::FileManager::ShareTarget
{
    bool Handel();
}

#endif // NANAZIP_FILEMANAGER_SHARETARGET
