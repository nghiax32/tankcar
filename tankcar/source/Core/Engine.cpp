#include "Engine.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Timer.h"
#include "Global.h"

Engine* Engine::sInstance = nullptr;
Player* player = nullptr;

int last_time_spawn = 0;

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

    Mix_Music *music = Mix_LoadMUS("sounds/music.mp3");
    Mix_PlayMusic(music, 1);

	return true;
}

void Engine::Load()
{
    TextureManager::GetInstance()->Load("MAP", "images/map.png");
	TextureManager::GetInstance()->Load("TANK_PLAYER", "images/tank1.png");
    TextureManager::GetInstance()->Load("MENU_BACKGROUND", "images/menu_background.png");
    SDL_Color textColor = {255, 255, 255};
    TextureManager::GetInstance()->LoadText("TANKCAR", "fonts/FrederickatheGreat-Regular.ttf", 100, textColor);
    TextureManager::GetInstance()->LoadText("PRESS ENTER TO PLAY", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->LoadText("USE WASD TO MOVE AND SPACE TO FIRE", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->LoadText("PRESS P TO PAUSE OR ESC TO QUIT", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->LoadText("PAUSED", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->LoadText("PRESS ENTER TO CONTINUE OR ESC TO END", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->LoadText("ENDED", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->LoadText("YOUR SCORE IS", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->LoadText("PRESS BACKSPACE TO GO BACK TO MENU", "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);

    player = new Player("TANK_PLAYER", (SCREEN_WIDTH - TANK_SIZE) / 2, 0, 0);

    Global::GetInstance()->spawn(0, 0, 0);
    Global::GetInstance()->spawn(SCREEN_WIDTH - TANK_SIZE, 0, 0);
    Global::GetInstance()->spawn(0, SCREEN_HEIGHT - TANK_SIZE, 0);
    Global::GetInstance()->spawn(SCREEN_WIDTH - TANK_SIZE, SCREEN_HEIGHT - TANK_SIZE, 0);
    last_time_spawn = 0;

    Global::GetInstance()->place();

    Timer::GetInstance()->start_time = int(SDL_GetTicks()) / 1000;

    mIsMenu = true;
    mIsRunning = true;
}

void Engine::Menu()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    TextureManager::GetInstance()->Render("MENU_BACKGROUND", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Global::GetInstance()->print("TANKCAR", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["TANKCAR"].h) / 6);
    Global::GetInstance()->print("PRESS ENTER TO PLAY", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["PRESS ENTER TO PLAY"].h) / 2);
    Global::GetInstance()->print("USE WASD TO MOVE AND SPACE TO FIRE", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["USE WASD TO MOVE AND SPACE TO FIRE"].h) * 2 / 3);
    Global::GetInstance()->print("PRESS P TO PAUSE OR ESC TO QUIT", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["PRESS P TO PAUSE OR ESC TO QUIT"].h) * 3 / 4);


    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN))
    {
        mIsMenu = false;
        mIsPlaying = true;
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
    {
        mIsMenu = false;
        mIsRunning = false;
    }

    SDL_RenderPresent(mRenderer);
}

void Engine::Pause()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    TextureManager::GetInstance()->Render("MENU_BACKGROUND", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Global::GetInstance()->print("TANKCAR", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["TANKCAR"].h) / 6);
    Global::GetInstance()->print("PAUSED", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["PAUSED"].h) / 2);
    Global::GetInstance()->print("PRESS ENTER TO CONTINUE OR ESC TO END", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["PRESS ENTER TO CONTINUE OR ESC TO END"].h) * 2 / 3);

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN))
    {
        mIsPaused = false;
        mIsPlaying = true;
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
    {
        mIsPaused = false;
        mIsEnded = true;
    }

    SDL_RenderPresent(mRenderer);
}

void Engine::End()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    TextureManager::GetInstance()->Render("MENU_BACKGROUND", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Global::GetInstance()->print("TANKCAR", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["TANKCAR"].h) / 6);
    Global::GetInstance()->print("ENDED", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["ENDED"].h) / 2);
    Global::GetInstance()->print("YOUR SCORE IS", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["YOUR SCORE IS"].h) * 2 / 3);

    SDL_Color textColor = {255, 255, 255};
    TextureManager::GetInstance()->LoadText(Global::GetInstance()->convert(player->Score), "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->Render(Global::GetInstance()->convert(player->Score),
                                          (SCREEN_WIDTH - Global::GetInstance()->mProsMap[Global::GetInstance()->convert(player->Score)].w) / 2,
                                          (SCREEN_HEIGHT - Global::GetInstance()->mProsMap[Global::GetInstance()->convert(player->Score)].h) * 3 / 4,
                                          Global::GetInstance()->mProsMap[Global::GetInstance()->convert(player->Score)].w,
                                          Global::GetInstance()->mProsMap[Global::GetInstance()->convert(player->Score)].h,
                                          0);
    SDL_DestroyTexture(Global::GetInstance()->mTextureMap[Global::GetInstance()->convert(player->Score)]);
    Global::GetInstance()->mTextureMap.erase(Global::GetInstance()->convert(player->Score));
    Global::GetInstance()->mProsMap.erase(Global::GetInstance()->convert(player->Score));

    player->HP = 10;
    player->Del = false;

    Global::GetInstance()->print("PRESS BACKSPACE TO GO BACK TO MENU", (SCREEN_HEIGHT - Global::GetInstance()->mProsMap["PRESS SPACE TO GO BACK TO MENU"].h) * 5 / 6);

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_BACKSPACE))
    {
        mIsEnded = false;
        mIsMenu = true;
        TextureManager::GetInstance()->Clean();
        Engine::Load();
    }

    SDL_RenderPresent(mRenderer);
}

void Engine::Events()
{
    EventHandler::GetInstance()->Input();
}

void Engine::Update()
{
    player->Update();

    int CurrentTime = Timer::GetInstance()->GetTime()/1000;
    if(CurrentTime <= 30 && CurrentTime % 5 == 0 && CurrentTime != last_time_spawn)
    {
        Global::GetInstance()->spawn(0, 0, 0);
        Global::GetInstance()->spawn(SCREEN_WIDTH - TANK_SIZE, 0, 0);
        Global::GetInstance()->spawn(0, SCREEN_HEIGHT - TANK_SIZE, 0);
        Global::GetInstance()->spawn(SCREEN_WIDTH - TANK_SIZE, SCREEN_HEIGHT - TANK_SIZE, 0);
        last_time_spawn = CurrentTime;
    }
    else if(CurrentTime > 30 && CurrentTime % 3 == 0 && CurrentTime != last_time_spawn)
    {
        Global::GetInstance()->spawn(0, 0, 0);
        Global::GetInstance()->spawn(SCREEN_WIDTH - TANK_SIZE, 0, 0);
        Global::GetInstance()->spawn(0, SCREEN_HEIGHT - TANK_SIZE, 0);
        Global::GetInstance()->spawn(SCREEN_WIDTH - TANK_SIZE, SCREEN_HEIGHT - TANK_SIZE, 0);
        last_time_spawn = CurrentTime;
    }

    vector<Enemy*> :: iterator it;
    for(it = Global::GetInstance()->enemy.begin(); it != Global::GetInstance()->enemy.end();)
    {
        if((*it)->Del == false)
        {
            (*it)->Update(player->mX, player->mY);
            it++;
        }
        else
        {
            SDL_DestroyTexture(Global::GetInstance()->mTextureMap[(*it)->mTextureID]);
            Global::GetInstance()->mTextureMap.erase((*it)->mTextureID);
            delete(*it);
            Global::GetInstance()->mProsMap.erase((*it)->mTextureID);
            Global::GetInstance()->enemy.erase(it);
            player->Score++;
        }
    }

    vector<Bullet*> :: iterator it1;
    for(it1 = Global::GetInstance()->bullet.begin(); it1 != Global::GetInstance()->bullet.end();)
    {
        if((*it1)->Del == false)
        {
            (*it1)->Update();
            it1++;
        }
        else
        {
            SDL_DestroyTexture(Global::GetInstance()->mTextureMap[(*it1)->mTextureID]);
            Global::GetInstance()->mTextureMap.erase((*it1)->mTextureID);
            delete(*it1);
            Global::GetInstance()->mProsMap.erase((*it1)->mTextureID);
            Global::GetInstance()->bullet.erase(it1);
        }
    }

    if(player->Del)
    {
        mIsPlaying = false;
        mIsEnded = true;
    }

    if(EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_P))
    {
        mIsPlaying = false;
        mIsPaused = true;
    }
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    TextureManager::GetInstance()->Render("MAP", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    player->Render();

    vector<Enemy*> :: iterator it;
    for(it = Global::GetInstance()->enemy.begin(); it != Global::GetInstance()->enemy.end();)
    {
        (*it)->Render();
        it++;
    }

    vector<Bullet*> :: iterator it1;
    for(it1 = Global::GetInstance()->bullet.begin(); it1 != Global::GetInstance()->bullet.end();)
    {
        (*it1)->Render();
        it1++;
    }

    Global::GetInstance()->render_block();

    SDL_Color textColor = {255, 255, 255};
    TextureManager::GetInstance()->LoadText(Timer::GetInstance()->GetCurrentTime(), "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    Timer::GetInstance()->Render();
    SDL_DestroyTexture(Global::GetInstance()->mTextureMap[Timer::GetInstance()->GetCurrentTime()]);
    Global::GetInstance()->mTextureMap.erase(Timer::GetInstance()->GetCurrentTime());
    Global::GetInstance()->mProsMap.erase(Timer::GetInstance()->GetCurrentTime());

    string SCORE = "SCORE: ";
    TextureManager::GetInstance()->LoadText(SCORE + Global::GetInstance()->convert(player->Score), "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->Render(SCORE + Global::GetInstance()->convert(player->Score), 650, 10,
                                          Global::GetInstance()->mProsMap[SCORE + Global::GetInstance()->convert(player->Score)].w,
                                          Global::GetInstance()->mProsMap[SCORE + Global::GetInstance()->convert(player->Score)].h,
                                          0);
    SDL_DestroyTexture(Global::GetInstance()->mTextureMap[SCORE + Global::GetInstance()->convert(player->Score)]);
    Global::GetInstance()->mTextureMap.erase(SCORE + Global::GetInstance()->convert(player->Score));
    Global::GetInstance()->mProsMap.erase(SCORE + Global::GetInstance()->convert(player->Score));

    string HP = "HP: ";
    TextureManager::GetInstance()->LoadText(HP + Global::GetInstance()->convert(player->HP), "fonts/FrederickatheGreat-Regular.ttf", 25, textColor);
    TextureManager::GetInstance()->Render(HP + Global::GetInstance()->convert(player->HP), 650, 550,
                                          Global::GetInstance()->mProsMap[HP + Global::GetInstance()->convert(player->HP)].w,
                                          Global::GetInstance()->mProsMap[HP + Global::GetInstance()->convert(player->HP)].h,
                                          0);
    SDL_DestroyTexture(Global::GetInstance()->mTextureMap[HP + Global::GetInstance()->convert(player->HP)]);
    Global::GetInstance()->mTextureMap.erase(HP + Global::GetInstance()->convert(player->HP));
    Global::GetInstance()->mProsMap.erase(HP + Global::GetInstance()->convert(player->HP));

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

