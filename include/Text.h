#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include "GameObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text : public Component {
public:
    enum TextStyle { SOLID, SHADED, BLENDED };
    Text(
        GameObject& associated, std::string fontFile,int fontsize,
        enum TextStyle style, std::string text, SDL_Color color
    );
    ~Text();

    void Update(double dt);
    void Render();
    bool Is(std::string type);

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    SDL_Color GetColor();
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);

private:
    void RemakeTexture();
    void DestroyTexture();

    TTF_Font* font;
    SDL_Texture* texture;

    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
};

#endif
