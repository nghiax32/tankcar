#include "Engine.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Tank.h"
#include "Enemy.h"
#include "Timer.h"

Engine* Engine::sInstance = nullptr;
Tank* player = nullptr;
Enemy* enemy = nullptr;

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

	TextureManager::GetInstance()->Load("map", "images/map.png");

	TextureManager::GetInstance()->Load("player", "images/tank1.png");

	TextureManager::GetInstance()->Load("enemy", "images/tank2.png");

    player = new Tank(new Properties("player", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

    enemy = new Enemy(new Properties("enemy", 0, 0));

	return mIsRunning = true;
}

void Engine::Events()
{
    EventHandler::GetInstance()->Input();
}

void Engine::Update()
{
    player->Update();
    enemy->Update(player->mTransform->X, player->mTransform->Y);

}

void Engine::Render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    TextureManager::GetInstance()->Render("map", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    player->Render();
    enemy->Render();

    SDL_Color textColor = {0, 0, 0};
    TextureManager::GetInstance()->LoadText(Timer::GetInstance()->GetCurrentTime(), "fonts/FrederickatheGreat-Regular.ttf", 26, textColor);
    Timer::GetInstance()->Render();

    SDL_RenderPresent(mRenderer);
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
