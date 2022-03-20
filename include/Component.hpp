#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Component{
public:
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual ~Component() {}
};