#include "Engine.h"
#include "TextureManager.h"
#include "EventHandler.h"

#include "Tank.h"

Engine* Engine::sInstance = nullptr;
Tank* player = nullptr;

bool Engine::Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("TANKCAR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if(mWindow == nullptr)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(mRenderer == nullptr)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
    }

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    if(TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	TextureManager::GetInstance()->Load("tank1", "images/tank1.png");
    player = new Tank(new Properties("tank1", 100, 100, 256, 256, 0));

	return mIsRunning = true;
}

void Engine::Update()
{
    player->Update();
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    player->Render();

    SDL_RenderPresent(mRenderer);
}

void Engine::Events()
{
    EventHandler::GetInstance()->Input();
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

    Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Engine::Quit()
{
    mIsRunning = false;
}
