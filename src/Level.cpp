#include "Level.h"

Level::Level(int tileSize)
{
    this->m_tileSize = tileSize;
}

void Level::loadMap(const char *map)
{
    std::ifstream file(map);
    if(file.is_open())
    {
        if(!(file >> m_width)) return;
        if(!(file >> m_height)) return;
        if(!(file >> m_depth)) return;
        
        // Temporary map
        m_level.resize(m_depth);
        for(int i = 0; i < m_depth; ++i)
        {
            m_level[i].resize(m_height);
            for(int j = 0; j < m_height; ++j)
            {
                m_level[i][j].resize(m_width);
            }
        }
        
        // read the tilemap
        for(int z = 0; z < m_depth; ++z)
        {
            for(int y = 0; y < m_height; ++y)
            {
                for(int x = 0; x < m_width; ++x)
                {
                    if(!(file >> m_level[z][y][x].tid)) return;
                    m_level[z][y][x].x = x * m_tileSize;
                    m_level[z][y][x].y = y * m_tileSize;
                    m_level[z][y][x].z = z;
                }
            }
        }
        
        // Debug render id's
        for(int z = 0; z < m_depth; ++z)
        {
            std::cout << "Drawing layer: " << z << std::endl;
            for(int y = 0; y < m_height; ++y)
            {
                for(int x = 0; x < m_width; ++x)
                {
                    std::cout << m_level[z][y][x].tid << " ";
                }
                std::cout << std::endl;
            }
        }
        
    }
}

bool Level::canCollide(int x, int y)
{
    return (m_level[0][y][x].tid != -1);
}

int Level::getTileSize()
{
    return m_tileSize;
}

void Level::render(SDL_Renderer *renderer, TextureManager* man)
{
    for(int z = 0; z < m_depth; ++z)
    {
        for(int y = 0; y < m_height; ++y)
        {
            for(int x = 0; x < m_width; ++x)
            {
                m_level[z][y][x].render(renderer, man);
            }
        }
    }
}