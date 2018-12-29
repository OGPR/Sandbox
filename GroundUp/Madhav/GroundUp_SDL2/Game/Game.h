#pragma once
#ifdef GAME_EXPORTS
#define GAME_EXPORTS_API __declspec(dllexport)
#else
#define GAME_EXPORTS_API __declspec(dllimport)
#endif

class GAME_EXPORTS_API Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
    //Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    //Window created by SDL TODO "include"/build with sdl (a dll)
    //SDL_Window* mWindow;
    
    bool mIsRunning;
};
