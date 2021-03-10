#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

class TextureManager
{
	public:
		static TextureManager* GetInstance()
        {
            return sInstance = (sInstance != nullptr)? sInstance : new TextureManager();
        }

		bool Load(string id, string path);
		bool LoadText(string textureText, SDL_Color textColor);

		void Render(string id, int x, int y, int width, int height, int angle);
        void RenderFrame(string id, int x, int y, int width, int height, int angle, int row, int frame);

		void Drop(string id);
		void Clean();

	private:
	    TextureManager() {};
	    static TextureManager* sInstance;
	    map<string, SDL_Texture*> mTextureMap;
};

#endif // TEXTUREMANAGER_H
