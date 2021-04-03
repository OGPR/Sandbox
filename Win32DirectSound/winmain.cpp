#include <Windows.h>
#include "Sound.h"
#include "MainWindowCallback.h"


int CALLBACK
WinMain(HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CmdLine,
    int ShowCmd)
{

    WNDCLASS WindowClass = {};


    WindowClass.style = CS_HREDRAW | CS_VREDRAW;

    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "Win32SoundTest";

    if (RegisterClassA(&WindowClass))
    {
        HWND WindowHandle = CreateWindowExA(
            0,
            WindowClass.lpszClassName,
            "HandMadeHero",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            Instance,
            0);
        if (WindowHandle)
        {
            win32InitDSound(WindowHandle, 48000, 48000 * sizeof(int16_t) * 2);

            MSG Message = {};
            GlobalRunning = true;

            while (GlobalRunning)
            {
                OutputDebugStringA("GlobalRunning\n");
                while (PeekMessageA(&Message, 0, 0, 0, PM_REMOVE))
                {
                    if (Message.message == WM_QUIT)
                    {
                        GlobalRunning = false;
                    }
                    TranslateMessage(&Message);
                    DispatchMessageA(&Message);

                }

                LPVOID Region1;
                DWORD Region1Size;
                LPVOID Region2;
                DWORD Region2Size;

                DWORD WriteStart = 0;
                DWORD BytesToWrite = 2;

                GlobalSecondarySoundBuffer->Lock(
                    WriteStart,
                    BytesToWrite,
                    &Region1,
                    &Region1Size,
                    &Region2,
                    &Region2Size,
                    0
                );

                int SquareWaveCounter = 0;
                int SamplesPerSecond = 48000;
                int Frequency = 256;
                int SquareWavePeriod = SamplesPerSecond / Frequency;
                int BytesPerSample = win32SetWaveFormat(SamplesPerSecond).wBitsPerSample / 8;
                int16_t* SampleOut = (int16_t*)Region1;
                DWORD Region1SampleCount = Region1Size / BytesPerSample;
                DWORD Region2SampleCount = Region2Size / BytesPerSample;
                for (DWORD SampleIndex = 0; SampleIndex < Region1Size; ++SampleIndex)
                {
                    if (!SquareWaveCounter)
                    {
                        SquareWaveCounter = SquareWavePeriod;
                    }
                    int16_t SampleValue = (SquareWaveCounter > SquareWavePeriod / 2) ? 16000 : -16000;

                    // 2 channels
                    *SampleOut++ = SampleValue;
                    *SampleOut++ = SampleValue;

                    --SquareWaveCounter;
                }

                for (DWORD SampleIndex = 0; SampleIndex < Region2Size; ++SampleIndex)
                {
                    if (!SquareWaveCounter)
                    {
                        SquareWaveCounter = SquareWavePeriod;
                    }
                    int16_t SampleValue = (SquareWaveCounter > SquareWavePeriod / 2) ? 16000 : -16000;

                    // 2 channels
                    *SampleOut++ = SampleValue;
                    *SampleOut++ = SampleValue;

                    --SquareWaveCounter;

                }

                GlobalSecondarySoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
            }
        }
    }

    return(0);
}
