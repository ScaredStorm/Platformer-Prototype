#include "Entity.h"

Entity::Entity(SDL_Texture* sprite, float x, float y)
{
    m_sprite = sprite;
    m_x = x;
    m_y = y;
}
