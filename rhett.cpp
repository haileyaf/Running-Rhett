
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>

const float gravity = 1;
int groundHeight = 440;
sf::Vector2f velocity(sf::Vector2f(0,0));

int main()
{
    sf::RenderWindow window{ sf::VideoMode(600,300), "Running Rhett" };
    sf::Texture t;
    sf::Texture r;
    sf::Texture b;
    b.loadFromFile("bike.png");
    r.loadFromFile("rhett.png");
    t.loadFromFile("BostonSkyline.png");
    sf::RectangleShape Road(sf::Vector2f(600,120));
    sf::RectangleShape roadlines(sf::Vector2f(400,80));
    sf::RectangleShape startscreen(sf::Vector2f(600,300));
    sf::RectangleShape popup(sf::Vector2f(350,100));
    sf::Sprite s(t);
    sf::Sprite B(b);
    sf::Sprite R(r);
    Road.setFillColor(sf::Color(128,128,128,255));
    Road.setPosition(0,180);
    s.setPosition(0,20);
    popup.setPosition(25,25);
    popup.setFillColor(sf::Color::Red);
    startscreen.setFillColor(sf::Color(255,255,255,200));
    sf::Font font;  // creates text for digital clock
    sf::Text words;
    sf::Text linetwo;
    sf::Text linethree;
    sf::Text linefour;
    sf::Text popupone;
    sf::Text popuptwo;
    sf::Text popupthree;

    linetwo.setOrigin(-70,-100);
    linethree.setOrigin(-200,-150);
    linefour.setOrigin(-130,-210);
    words.setOrigin(-140,-5);  // change origin points to center of the actual window
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf");
    words.setFont(font);
    linetwo.setFont(font);
    linethree.setFont(font);
    linefour.setFont(font);
    popupone.setFont(font);
    popuptwo.setFont(font);
    popupthree.setFont(font);
    popupthree.setCharacterSize(15);
    popupone.setCharacterSize(20);
    popuptwo.setCharacterSize(15);
    words.setCharacterSize(50);  // change size of font if needed
    linetwo.setCharacterSize(20);
    linethree.setCharacterSize(20);
    linefour.setCharacterSize(30);
    linetwo.setFillColor(sf::Color::Black);
    linethree.setFillColor(sf::Color::Black);
    linefour.setFillColor(sf::Color::Black);
    words.setFillColor(sf::Color::Red);
    words.setString("RUNNING RHETT");
    linetwo.setString("Run down Commonwealth Ave. and avoid obstacles!");
    linethree.setString("Use spacebar to jump");
    linefour.setString("Press any key to start!");
    popupone.setString("Uh oh! You've hit an obstacle!");
    popuptwo.setString("Your score: \nHigh score: ");
    popupthree.setString("Press spacebar to restart or esc to quit");
    words.setOutlineColor(sf::Color::Black);
    words.setOutlineThickness(4);
    words.setStyle(sf::Text::Bold);
    popupone.setFillColor(sf::Color::Black);
    popupone.setOrigin(-49,-30);
    popuptwo.setOrigin(-60,-60);
    popupthree.setOrigin(-49,-100);
    popuptwo.setFillColor(sf::Color::Black);
    popupthree.setFillColor(sf::Color::Black);
    R.setScale(0.25,0.25);
    B.setScale(0.125,0.125);
    B.setPosition(300,200);
    s.setScale(1.5,1.5);
    R.setPosition(0,200);


    while (window.isOpen())
    {

        sf::Event windowEvent;
        while (window.pollEvent(windowEvent)) {
            window.clear(sf::Color::White);
            window.draw(s);
            window.draw(Road);
            window.draw(startscreen);
            window.draw(words);
            window.draw(linetwo);
            window.draw(linethree);
            window.draw(linefour);
            window.draw(R);

            window.display();

            if (windowEvent.type == sf::Event::KeyPressed) {
                startscreen.setFillColor(sf::Color(255,255,255,0));
                words.setOutlineColor(sf::Color(255,255,255,0));
                words.setOutlineThickness(0);
                words.setFillColor(sf::Color(255,255,255,0));
                linetwo.setFillColor(sf::Color(255,255,255,0));
                linethree.setFillColor(sf::Color(255,255,255,0));
                linefour.setFillColor(sf::Color(255,255,255,0));
                
            }
                // window.draw(popuptwo);
                // window.draw(popupthree);
                //press spacebar to restart

      
        
                

        }

            // if rhett runs into obstacle
        // window.draw(popup);
          // window.draw(popupone);     
          //   window.draw(popuptwo);
          //   window.draw(popupthree);
          //   window.display();}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    window.close();


    }
    return 0;
}
