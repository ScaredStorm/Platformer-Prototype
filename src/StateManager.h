#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include <stdio.h>
#include <stack>
#include <memory>
#include <SDL.h>

#include "BaseState.h"

template<class Owner> class StateManager
{
public:
    //void switchState(BaseState* s);
    void pop();
    template<class T> void push(Owner *o);
    BaseState* current();
    
    void update();
    void handleInput(SDL_Event &e);
    void render(SDL_Renderer *renderer);
    
private:
    std::stack<BaseState*> m_states;
};

template<class Owner>
void StateManager<Owner>::pop()
{
    if(m_states.size())
    {
        m_states.pop();
    }
    else
    {
        throw std::runtime_error("[StateManager::pop()] runtime error, nothing left in stack.");
    }
}

template<class Owner>
template<class T>
void StateManager<Owner>::push(Owner *o)
{
    m_states.push(new T(o));
}

template<class Owner>
BaseState* StateManager<Owner>::current()
{
    if(m_states.size())
    {
        return m_states.top();
    }
    
    throw std::runtime_error("[StateManager::current()] runtime error, nothing left in stack.");
}

template<class Owner>
void StateManager<Owner>::update()
{
    //
    current()->update();
}

template<class Owner>
void StateManager<Owner>::handleInput(SDL_Event &e)
{
    //
    current()->handleInput(e);
}

template<class Owner>
void StateManager<Owner>::render(SDL_Renderer *renderer)
{
    //
    current()->render(renderer);
}

#endif
