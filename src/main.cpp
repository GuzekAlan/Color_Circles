#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <format>
#include <cstdlib>
#include <thread>
#include "Circle.hpp"
#include "Text.hpp"
#include "Bar.hpp"
#include "ThreadPool.hpp"

void updates(std::vector<Circle*>& Circles, std::vector<TextArea*>& Texts, Bar* bar, double Z, ThreadPool& pool){
    std::vector<std::future<void>> results;
    for(auto circle : Circles){
        circle->setZ(Z);
        // results.push_back(pool.enqueue([](Circle* circle){circle->updateColor();}, circle));
        pool.enqueue([](Circle* circle){circle->updateColor();}, circle);
    }
    // for(auto &result : results){
    //     result.get();
    // }
    bar->setZ(Z);
    Texts[5]->setText(sf::String("L=") += std::to_string(Z));
    Texts[6]->setText(sf::String("V=") += std::to_string(Z));
    Texts[7]->setText(sf::String("Y=") += sf::String(std::to_string((int)(Z*100))) += "%");
    Texts[8]->setText(sf::String("B=") += std::to_string((int)(Z*255)));
}


int main(){
    sf::Color testColor = getHSV(0.3, 0.5, 0.1);
    testColor = getHSV(0.3, 0.5, 0.2);
    testColor = getHSV(0.3, 0.5, 0.4);
    testColor = getHSV(0.3, 0.6, 0.5);
    testColor = getHSV(0.3, 0.6, 0.8);

    sf::RenderWindow window(sf::VideoMode(750, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    unsigned int FPS = 0 , frame_counter = 0;
    std::vector<Circle*> Circles;
    std::vector<TextArea*> Texts;
    double Z = 0.5;

    Circles.push_back(new Circle(sf::Vector2f(20, 20), 125, ColorTypes::HSL));
    Circles.push_back(new Circle(sf::Vector2f(330, 20), 125, ColorTypes::HSV));
    Circles.push_back(new Circle(sf::Vector2f(20, 330), 125, ColorTypes::CMY));
    Circles.push_back(new Circle(sf::Vector2f(330, 330), 125, ColorTypes::RGB));
    
    Texts.push_back(new TextArea(sf::Vector2f(20, 20), 20, 10, "HSL"));
    Texts.push_back(new TextArea(sf::Vector2f(330, 20), 20, 10, "HSV"));
    Texts.push_back(new TextArea(sf::Vector2f(20, 330), 20, 10, "CMY"));
    Texts.push_back(new TextArea(sf::Vector2f(330, 330), 20, 10, "RGB"));

    Texts.push_back(new TextArea(sf::Vector2f(630, 300), 20, 10, "FPS"));

    Texts.push_back(new TextArea(sf::Vector2f(250, 250), 20, 10, "L="));
    Texts.push_back(new TextArea(sf::Vector2f(550, 250), 20, 10, "V="));
    Texts.push_back(new TextArea(sf::Vector2f(250, 550), 20, 10, "Y="));
    Texts.push_back(new TextArea(sf::Vector2f(550, 550), 20, 10, "B="));

    Bar* bar = new Bar(sf::Vector2f(630, 20));

    ThreadPool pool(4);

    //inicjalizacja 
    clock.restart().asMilliseconds();
    while (window.isOpen()){
        sf::Event event;
        window.clear(sf::Color::White);

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left 
                && event.mouseButton.x < 650 
                && event.mouseButton.x > 600
                && event.mouseButton.y > 20
                && event.mouseButton.y < 277){
                    Z=(event.mouseButton.y-20)/256.;
                    updates(Circles, Texts, bar, Z, pool);
                }
            }
            if(event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(event.mouseMove.x < 650 
                && event.mouseMove.x > 600
                && event.mouseMove.y > 20
                && event.mouseMove.y < 277){
                    Z=(event.mouseMove.y-20)/256.;
                    updates(Circles, Texts, bar, Z, pool);
                }
            }
        }
        //tu wyrysować wszystko na ekran

///////////////////////////////////////////////////////////////////////       
        //tu wypisać na ekran wartość FPS
        if (clock.getElapsedTime().asSeconds() >= 0.5f){
            FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
            clock.restart();
            frame_counter = 0;
        }
        frame_counter++;

///////////////////////////////////////////////////////////////////


        Texts[4]->setText(sf::String("FPS: ") += std::to_string(FPS));
        for(auto circle : Circles){
            circle->draw(window);
        }
        for(auto text : Texts){
            text->draw(window);
        }
        bar->draw(window);
        
        window.display();
    }

    return 0;
}