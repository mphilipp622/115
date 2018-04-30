#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SOIL.h>
#include <GL\GL.h>
#include <iostream>
#include <string>

using namespace std;

// Handles wrapping textures onto openGL models
class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();

        // Initializes Texture from a file
        void BindTexture(string); //char* is filename

        // Wraps texture onto model
        void Binder();

    protected:

    private:
        unsigned char* image; // filename for the image.
        int width, height; // width and height of texture
        GLuint tex;
};

#endif // TEXTURELOADER_H
