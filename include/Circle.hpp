#pragma once

// #define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Component.hpp"
#include "Utility.hpp"
#include <cmath>
// #include <math.h>
#include <iostream>
#include <functional>

#define PI 3.1415926535


class Circle : public Component{
protected:
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _leftCorner;
    sf::Image _pixels;
    double _radius;
    float _z;
    std::function<sf::Color(double, double, double)> _color;
public:
    Circle(sf::Vector2f leftCorner, double radius, ColorTypes colorType)
        : _leftCorner{leftCorner}, 
        _radius{radius}, 
        _z{0.5}{
            _pixels.create(radius*2, radius*2, sf::Color::White);
            _texture.create(radius*2, radius*2);
            _sprite.setPosition(_leftCorner);
            switch(colorType){
                case ColorTypes::RGB: _color = getRGB; break;
                case ColorTypes::HSL: _color = getHSL; break;
                case ColorTypes::HSV: _color = getHSV; break;
                case ColorTypes::CMY: _color = getCMY; break;
                default: _color = getRGB; break;
            }
            updateColor();
    }
    
    void setZ(double z){
        _z = z;
    }

    void updateColor(){
        double r, fi;
        for (float x = -_radius; x < _radius; x++) {
            for (float y = -_radius; y < _radius; y++) {
                r = sqrtf(x*x + y*y);
                if(r < _radius){
                    fi = -atan2f(-y, -x) + PI;
                    // fi = 2*PI-fi;
                    _pixels.setPixel(static_cast<unsigned int>(x+_radius), static_cast<unsigned int>(y+_radius), _color(r/_radius, fi/2/PI, _z));
                } 
            }
        }
        _texture.update(_pixels);
        _sprite.setTexture(_texture);
    }

    void draw(sf::RenderTarget& target) override {
        target.draw(_sprite);
    }
};




// class CircleHSL : public Circle{
// public:
//     CircleHSL(sf::Vector2u leftCorner, double radius)
//         : Circle(leftCorner, radius) {}
//     sf::Color color(double r, double fi, double z) override {
//         return sf::Color::Green;
//     }
// };

// class CircleHSV : public Circle{
// public:
//     CircleHSV(sf::Vector2u leftCorner, double radius)
//         : Circle(leftCorner, radius) {}
//     sf::Color color(double r, double fi, double z) override {
//         return sf::Color::Red;
//     }
// };

// class CircleCMY : public Circle{
// public:
//     CircleCMY(sf::Vector2u leftCorner, double radius)
//         : Circle(leftCorner, radius) {}
//     sf::Color color(double r, double fi, double z) override {
//         return sf::Color::Blue;
//     }
// };

// class CircleRGB : public Circle{
// public:
//     CircleRGB(sf::Vector2u leftCorner, double radius)
//         : Circle(leftCorner, radius) {}
//     sf::Color color(double r, double fi, double z) override {
//         return sf::Color::Black;
//     }
// };
