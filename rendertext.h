#ifndef RENDERTEXT_HPP_INCLUDED
#define RENDERTEXT_HPP_INCLUDED

#include "stdafx.h"

class RenderText
{
public:
    RenderText(const std::string& fontPath, int textSize, const SDL_Color& color, const std::string& text, SDL_Renderer* renderer);
    ~RenderText();

    void render(SDL_Renderer* renderer, const SDL_Rect& drawRect);

private:
    SDL_Texture* m_texture;
};

#endif // RENDERTEXT_HPP_INCLUDED
