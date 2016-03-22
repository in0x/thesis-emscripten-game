#include "rendertext.h"

RenderText::RenderText(const std::string& fontPath, int textSize, const SDL_Color& color, const std::string& text, SDL_Renderer* renderer)
{
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), textSize);

    if (font == nullptr)
    {
        std::cout << "Failed to load font " << " fontPath" << std::endl;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

RenderText::~RenderText()
{
    SDL_DestroyTexture(m_texture);
}

void RenderText::render(SDL_Renderer* renderer, const SDL_Rect& drawRect)
{
    SDL_RenderCopy(renderer, m_texture, nullptr, &drawRect);
}
