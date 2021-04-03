#include <Windows.h>
#include "Sound.h"
#include "MainWindowCallback.h"
#include "MessageHandling.h"
#include "FileReader.h"
#include <vector>


int CALLBACK
WinMain(HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CmdLine,
    int ShowCmd)
{


    std::string commandLineArg = GetCommandLineA();
    
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
            WindowClass.lpszClassName,
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
            GlobalRunning = true;




            win32InitDSound(WindowHandle, 48000, 48000 * sizeof(int16_t) * 2);

            while (GlobalRunning)
            {
                win32HandleMessage(GlobalRunning);

                LPVOID Region1;
                DWORD Region1Size;
                LPVOID Region2;
                DWORD Region2Size;

                std::vector<unsigned long> parameters;
                readFile("Win32DirectSound_ParamInput.txt", parameters);

                DWORD WriteStart = parameters[2];
                DWORD BytesToWrite = parameters[3];

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
                int SamplesPerSecond = parameters[0];
                int Frequency = parameters[1];
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
