#include "TextureManager.h"
#include "Engine.h"

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

    mTextureMap[id] = texture;
	return true;
}

void TextureManager::Render(string id, int x, int y, int width, int height, int angle)
{
	SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), mTextureMap[id], &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

void TextureManager::RenderFrame(string id, int x, int y, int width, int height, int angle, int row, int frame)
{
    SDL_Rect srcRect = {width*frame, height*row, width, height};
    SDL_Rect dstRect = {x, y, width, height};
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), mTextureMap[id], &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

void TextureManager::Drop(string id)
{
    SDL_DestroyTexture(mTextureMap[id]);
    mTextureMap.erase(id);
}

void TextureManager::Clean()
{
    map<string, SDL_Texture*>::iterator it;
    for(it = mTextureMap.begin(); it != mTextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    mTextureMap.clear();

}
