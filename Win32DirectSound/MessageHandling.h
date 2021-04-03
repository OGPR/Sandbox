#ifndef MESSAGEHANDLING__H
#define MESSAGEHANDLING__H

#include <Windows.h>
#include <stdint.h>
void win32HandleMessage(int32_t GlobalRunning)
{
    MSG Message = {};
    while (PeekMessageA(&Message, 0, 0, 0, PM_REMOVE))
    {
        if (Message.message == WM_QUIT)
        {
            GlobalRunning = false;
        }
        TranslateMessage(&Message);
        DispatchMessageA(&Message);
    }
}
#endif // !MESSAGEHANDLING__H
