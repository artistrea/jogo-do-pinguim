#include "Text.h"
#include "Game.h"
#include "Component.h"
#include "GameObject.h"
#include "ThrowError.h"
#include "Resources.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Text::Text(
    GameObject& associated, std::string fontFile,int fontSize,
    enum TextStyle style, std::string text, SDL_Color color
): Component(associated), font(nullptr), texture(nullptr),
    text(text), style(style), fontFile(fontFile),
    fontSize(fontSize), color(color)
{
    this->font = Resources::GetFont(fontFile, fontSize);
    this->RemakeTexture();
}

Text::~Text() {
    this->DestroyTexture();
}


void Text::Update(double dt) {
    
}

void Text::Render() {
    SDL_Rect dest;
    dest.x = associated.box.topLeftCorner.x;
    dest.y = associated.box.topLeftCorner.y;
    dest.w = associated.box.dimensions.x;
    dest.h = associated.box.dimensions.y;
    
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = associated.box.dimensions.x;
    src.h = associated.box.dimensions.y;

    int result = SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        this->texture,
        &src,
        &dest,
        this->associated.angleDeg,
        nullptr,
        SDL_FLIP_NONE
    );

    if (result) ThrowError::SDL_Error();
}

bool Text::Is(std::string type) {
    return type == "Text";
}


void Text::SetText(std::string text) {
    this->text = text;
    this->RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    this->RemakeTexture();
}

SDL_Color Text::GetColor() {
    return this->color;
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    this->RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
    this->font = Resources::GetFont(fontFile, fontSize);

    this->RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    this->font = Resources::GetFont(fontFile, fontSize);

    this->RemakeTexture();
}

void Text::RemakeTexture() {
    this->DestroyTexture();

    SDL_Surface * surface;

    switch (this->style)
    {
    case TextStyle::SOLID:
        surface = TTF_RenderText_Solid(
            this->font, this->text.c_str(), this->color
        );
        break;
    
    case TextStyle::SHADED:
        surface = TTF_RenderText_Shaded(
            this->font, this->text.c_str(), this->color,
            (SDL_Color){0, 0, 0, 255}
        );
        break;

    case TextStyle::BLENDED:
        surface = TTF_RenderText_Blended(
            this->font, this->text.c_str(), this->color
        );
        break;
    default:
        ThrowError::Error("No TextStyleFound");
        break;
    }

    if (surface == nullptr) {
        SDL_Log("at Text::RemakeTexture make surface");
        ThrowError::SDL_Error();
    }


    this->texture = SDL_CreateTextureFromSurface(
        Game::GetInstance().GetRenderer(),
        surface
    );

    SDL_FreeSurface(surface);

    if (this->texture == nullptr) {
        SDL_Log("at Text::RemakeTexture make texture");
        ThrowError::SDL_Error();
    }
}

void Text::DestroyTexture() {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
    }
}
