#include "TextureManager.h"
#include "Engine.h"
#include "Global.h"

TextureManager* TextureManager::sInstance = nullptr;

bool TextureManager::Load(string id, string path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());

	if(surface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);

    if(texture == nullptr)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    Global::GetInstance()->mTextureMap[id] = texture;
    Global::GetInstance()->mProsMap[id] = surface->clip_rect;
    SDL_FreeSurface(surface);
	return true;
}

bool TextureManager::LoadText(string id, string path, int fontSize, SDL_Color textColor)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);

    if(font == nullptr)
	{
		printf("Unable to load font %s! SDL_ttf Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, id.c_str(), textColor);

    if(textSurface == nullptr)
	{
		printf("Unable to render text surface %s! SDL_image Error: \n", IMG_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), textSurface);

	if(texture == nullptr)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    Global::GetInstance()->mTextureMap[id] = texture;
    Global::GetInstance()->mProsMap[id] = textSurface->clip_rect;
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
	return true;
}

void TextureManager::Render(string id, int x, int y, int width, int height, int angle)
{
	SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), Global::GetInstance()->mTextureMap[id], &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

void TextureManager::Clean()
{
    map<string, SDL_Texture*>::iterator it;
    for(it = Global::GetInstance()->mTextureMap.begin(); it != Global::GetInstance()->mTextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    Global::GetInstance()->mTextureMap.clear();
    Global::GetInstance()->mProsMap.clear();
    Global::GetInstance()->enemy.clear();
    Global::GetInstance()->bullet.clear();
}
