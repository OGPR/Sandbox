#include <Windows.h>
#include "Sound.h"
#include "MainWindowCallback.h"
#include "MessageHandling.h"
#include "FileReader.h"
#include <map>


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

            std::map < std::string, unsigned long> parameterMap
            {
                {"SamplesPerSecond", 48000},
                {"Frequency", 256},
                {"WriteStart", 0},
                {"BytesToWrite", 2},
                {"BufferSize", 48000 * sizeof(int16_t) * 2}
            };

            readFile("Win32DirectSound_ParamInput.txt", parameterMap);
            win32InitDSound(WindowHandle, parameterMap["SamplesPerSecond"], parameterMap["BufferSize"]);

            while (GlobalRunning)
            {
                win32HandleMessage(GlobalRunning);

                LPVOID Region1;
                DWORD Region1Size;
                LPVOID Region2;
                DWORD Region2Size;


                DWORD WriteStart = parameterMap["WriteStart"];
                DWORD BytesToWrite = parameterMap["BytesToWrite"];

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
                int SamplesPerSecond = parameterMap["SamplesPerSecond"];
                int Frequency = parameterMap["Frequency"];
                int SquareWavePeriod = SamplesPerSecond / Frequency;
                int BytesPerSample = win32SetWaveFormat(SamplesPerSecond).wBitsPerSample / 8;
                int16_t* SampleOut = (int16_t*)Region1;
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
