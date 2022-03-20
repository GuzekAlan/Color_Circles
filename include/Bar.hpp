#pragma once

#include <SFML/Graphics.hpp>
#include "Component.hpp"


class Bar : public Component{
private:
    double _z;
    const int barX = 37;
	const int barY = 256;
    const float barValue = 0.5f;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Image _pixels;
    sf::RectangleShape _line;
    sf::RectangleShape _border;
public:
    Bar(sf::Vector2f leftCorner)
        : _z{0.5},
        _line(sf::Vector2f(62, 1)),
        _border(sf::Vector2f(barX, barY)) {
            _texture.create(barX, barY);
            _pixels.create(barX, barY);
            _sprite.setPosition(leftCorner);
            for (int x = 0; x < barX; ++x) {
                for (int y = 1; y < barY; ++y) {
                    _pixels.setPixel(x, y, sf::Color(y, y, y));
                }
            }
            _texture.update(_pixels);
            _sprite.setTexture(_texture);
            _line.setFillColor(sf::Color::Black);
            _line.setOutlineColor(sf::Color::Black);
            _line.setOutlineThickness(1.0f);
            _border.setPosition(leftCorner);
            _border.setFillColor(sf::Color::Transparent);
            _border.setOutlineColor({200, 200, 200});
            _border.setOutlineThickness(2.f);
            
        }
    void setZ(double z){
        _z = z;
    }
    void draw(sf::RenderTarget& target){
        _line.setPosition(617, 20 + _z * 255);
        
        target.draw(_line);
        target.draw(_sprite);
        target.draw(_border);
    }
};