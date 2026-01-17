#include "ShutdownBlock.h"
#include <winrt/base.h>
#include <WinUser.h>
#include <CommCtrl.h>

namespace NanaZip::Modern
{
    void BlockSystemShutdown(HWND hWnd)
    {
        winrt::check_bool(::ShutdownBlockReasonCreate(hWnd, L""));
        winrt::check_bool(::SetWindowSubclass(
            hWnd,
            [](
                _In_ HWND hWnd,
                _In_ UINT uMsg,
                _In_ WPARAM wParam,
                _In_ LPARAM lParam,
                _In_ UINT_PTR uIdSubclass,
                _In_ DWORD_PTR dwRefData) -> LRESULT
            {
                UNREFERENCED_PARAMETER(uIdSubclass);
                UNREFERENCED_PARAMETER(dwRefData);

                switch (uMsg)
                {
                case WM_DESTROY:
                {
                    winrt::check_bool(::ShutdownBlockReasonDestroy(hWnd));
                }
                case WM_QUERYENDSESSION:
                {
                    return false;
                }
                }
                return ::DefSubclassProc(
                    hWnd,
                    uMsg,
                    wParam,
                    lParam);
            },
            0,
            0));
    }
}
