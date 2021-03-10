#include "EventHandler.h"
#include "Engine.h"

EventHandler* EventHandler::sInstance = nullptr;

void EventHandler::Input()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: Engine::GetInstance()->Quit(); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
        }
    }
}

bool EventHandler::GetKeyDown(SDL_Scancode key)
{
    return (mKeyStates[key] == 1);
}

void EventHandler::KeyUp()
{
    mKeyStates = SDL_GetKeyboardState(nullptr);
}

void EventHandler::KeyDown()
{
    mKeyStates = SDL_GetKeyboardState(nullptr);
}
