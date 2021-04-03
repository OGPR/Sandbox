#ifndef MAINWINDOWCALLBACK__H
#define MAINWINDOWCALLBACK__H
#include <Windows.h>
#include <stdint.h>
using uint32 = uint32_t;
using bool32 = int32_t;

static bool GlobalRunning;

LRESULT CALLBACK
MainWindowCallback(HWND WindowHandle,
    UINT Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;

    switch (Message)
    {
        case WM_DESTROY:
        {
            //TODO: Handle this as an error - recreate window?
            GlobalRunning = false;
        } break;

        case WM_CLOSE:
        {
            //TODO: Handle this with a message to the user?
            GlobalRunning = false;
        } break;

        default:
        {
            Result = DefWindowProcA(WindowHandle, Message, WParam, LParam);
        } break;
    }

    return(Result);
}

#endif //!MAINWINDOWCALLBACK__H
