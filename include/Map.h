#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Helper.h"

using namespace std;

class Map
{
    public:
        Map( string path, SDL_Renderer* r, int width, int height );
        virtual ~Map();
        SDL_Rect get_cropper();
        void render();
    protected:
    private:
        string _path;
        SDL_Texture* _texture;
        SDL_Renderer* _renderer;
        int _width;
        int _height;
};

#endif // MAP_H
