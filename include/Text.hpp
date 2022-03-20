#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "../fonts/font.h"
#include "Component.hpp"

class TextArea : public Component{
private:
    sf::Vector2f _leftCorner;
    sf::Uint32 _width, _height;
    sf::Font _font;
    sf::Text _text;

public:
    TextArea(sf::Vector2f leftCorner, sf::Uint32 width, sf::Uint32 height, const std::string& text = "Text") 
        : _leftCorner{leftCorner},
        _width{width},
        _height{height}{
            _font.loadFromMemory(font_data, font_data_size);
            _text.setFont(_font);
            _text.setCharacterSize(12);
            _text.setFillColor(sf::Color::Black);
            _text.setPosition(_leftCorner.x, _leftCorner.y);
            _text.setString(text);
        }
    void draw(sf::RenderTarget& target){
        target.draw(_text);
    }
    void setText(sf::String text){
        _text.setString(text);
    }

};