// Copyright 2022 Hailey Fox foxh@bu.edu
// Copyright 2022 Claire Cropper ccropper@bu.edu
// Copyright 2022 Antoine Baize baizea@bu.edu
// Copyright 2022 Xinyu Lei tllrllsa@bu.edu

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>

using namespace std;
using namespace sf;
using std::cout;

float speed = -7.f ;

// Sprite initialization

const int windowWidth = 1080;
const int windowHeight = 560;
int scoreint = 0;

Sprite RhettSprite;
Sprite Rhettbegin;
Sprite Rhettend;
Sprite roadSprite1;
Sprite roadSprite2;
Sprite skylineSprite1;
Sprite skylineSprite2;
Sprite busstop[5];
Sprite birdSprite;
FloatRect skyline_bound;
FloatRect road_bound;
FloatRect birdSpriteRect;
int birdcounter, birdy, newy;

// Sprite coordinates

int laststop = 0;
int rhett_x = 50;
int rhett_y = 400;
float dy;



// Sprite texture index

int RhettTextureIndex = 0;
int birdTextureIndex = 0;
Texture RhettTexture0;
Texture RhettTexture1;
Texture RhettTexture2;
Texture RhettTexture3;
Texture RhettTexture4;
Texture RhettTextures[5];
Texture birdTextures[6];
Texture RhettTexture_menu;
Texture RhettTexture_end;
Texture roadTexture;
Texture skylineTexture;
Texture busstopTexture;

// Words initialization

Font font;
Text Title;
Text Instruction1;
Text Instruction2;
Text Instruction3;

Text score;
Text highscore;
Text finscore;

Text GameOverTitle;
Text GameOverInstruction1;
Text GameOverInstruction2;
Text GameOverInstruction3;
Text RhettSays;



bool menu_bool = true, game_start = false, game_over = false;

double besttime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto dur = now.time_since_epoch();
    return dur.count()/1'000'000'000.0;
}

void threadFunc() {
    double accurate_time = besttime();
    std::time_t time = std::time(NULL);
    std::tm now = *std::localtime(&time);
    scoreint += 1;
}

// set up game menu
void Game_Menu() {
    //set game menu image
    //image position
    Rhettbegin.setPosition(rhett_x-50,windowHeight/2);
    RhettSprite.setPosition(rhett_x-50,windowHeight/2);
    Rhettend.setPosition(rhett_x-50,windowHeight/2+8);
    roadSprite1.setPosition(0, windowHeight - 110);
    roadSprite2.setPosition(road_bound.width, windowHeight - 110);
    skylineSprite1.setPosition(0, 0);
    skylineSprite2.setPosition(skyline_bound.width, 0);

    // image texture
    RhettTexture_menu.loadFromFile("images/rhett_menu.png");
    RhettTexture_end.loadFromFile("images/rhett_end.png");
    RhettTexture0.loadFromFile("images/rhett5.png");
    RhettTextures[0] = RhettTexture0;
    RhettTexture1.loadFromFile("images/rhett1.png");
    RhettTextures[1] = RhettTexture1;
    RhettTexture2.loadFromFile("images/rhett2.png");
    RhettTextures[2] = RhettTexture2;
    RhettTexture3.loadFromFile("images/rhett3.png");
    RhettTextures[3] = RhettTexture3;
    RhettTexture4.loadFromFile("images/rhett4.png");
    RhettTextures[4] = RhettTexture4;
    Texture birdTexture0;
    birdTexture0.loadFromFile("images/bird1.png");
    birdTextures[0] = birdTexture0;
    Texture birdTexture1;
    birdTexture1.loadFromFile("images/bird2.png");
    birdTextures[1] = birdTexture1;
    Texture birdTexture2;
    birdTexture2.loadFromFile("images/bird3.png");
    birdTextures[2] = birdTexture2;
    Texture birdTexture3;
    birdTexture3.loadFromFile("images/bird4.png");
    birdTextures[3] = birdTexture3;
    Texture birdTexture4;
    birdTexture4.loadFromFile("images/bird5.png");
    birdTextures[4] = birdTexture4;
    Texture birdTexture5;
    birdTexture5.loadFromFile("images/bird6.png");
    birdTextures[5] = birdTexture5;
    busstopTexture.loadFromFile("images/busstop.png");
    birdSprite.setTexture(birdTexture0);
    birdSprite.setPosition(1300,300);
    roadTexture.loadFromFile("images/road.png");
    skylineTexture.loadFromFile("images/skyline.png");
    busstopTexture.loadFromFile("images/busstop.png");
    skylineSprite1.setTexture(skylineTexture);
    skylineSprite2.setTexture(skylineTexture);
    Rhettbegin.setTexture(RhettTexture_menu);
    Rhettend.setTexture(RhettTexture_end);
    roadSprite1.setTexture(roadTexture);
    roadSprite2.setTexture(roadTexture);

for (int i = 0; i < 5; i++) {
                busstop[i] = Sprite(busstopTexture);
                busstop[i].setScale(.2,.2);
            }
    

    //image scale
    Rhettbegin.setScale(.3,.3);
    Rhettend.setScale(.26,.26);
    roadSprite1.setScale(3,1);
    roadSprite2.setScale(3,1);
    skylineSprite1.setScale(.7, .7);
    skylineSprite2.setScale(.7, .7);
    birdSprite.setScale(0.2,0.2);

    //Game menu Texts

    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf");

    Title.setOrigin(-windowWidth*1/3.3,-150);  // text placement
    Instruction1.setOrigin(-windowWidth*1/5.45,-70);
    Instruction2.setOrigin(-windowWidth*1/2.7,-265);
    Instruction3.setOrigin(-windowWidth*1/3.4,-305);

    Title.setFont(font);  // text font
    Instruction1.setFont(font);
    Instruction2.setFont(font);
    Instruction3.setFont(font);

    Title.setCharacterSize(70);  // text size
    Instruction1.setCharacterSize(30);
    Instruction2.setCharacterSize(30);
    Instruction3.setCharacterSize(40);

    Title.setFillColor(Color(164,0,0));  // text color
    Instruction1.setFillColor(Color(255, 255, 255));
    Instruction2.setFillColor(Color(255,255,255));
    Instruction3.setFillColor(Color(255,255,255));

    Title.setString("RUNNING RHETT");  // text
    Instruction1.setString("Run down Commonwealth Ave and avoid obstacles!");
    Instruction2.setString("Use spacebar to jump");
    Instruction3.setString("Press any key to start!");

    Title.setOutlineColor(sf::Color::Black);  // text outline color
    Instruction1.setOutlineColor(sf::Color::Black);
    Instruction2.setOutlineColor(sf::Color::Black);
    Instruction3.setOutlineColor(sf::Color::Black);

    Title.setOutlineThickness(5);  // text outline thickness
    Instruction1.setOutlineThickness(3);
    Instruction2.setOutlineThickness(3);
    Instruction3.setOutlineThickness(3);

    GameOverTitle.setString("Uh oh! Your journey down Commonwealth Ave. \n  has unfortunately come to an end.");
    GameOverInstruction1.setString("Press escape to quit");
    GameOverInstruction2.setString("Press R to retry!");

    GameOverTitle.setOrigin(-windowWidth*1/9.75,-70);  // text placement
    GameOverInstruction1.setOrigin(-windowWidth*1/2.8,-330);
    GameOverInstruction2.setOrigin(-windowWidth*1/2.9,-365);
    RhettSays.setOrigin(-windowWidth*2/6,-500); 

    GameOverTitle.setFont(font);  // text font
    GameOverInstruction1.setFont(font);
    GameOverInstruction2.setFont(font);
    RhettSays.setFont(font);

    GameOverTitle.setCharacterSize(40);  // text size
    GameOverInstruction1.setCharacterSize(30);
    GameOverInstruction2.setCharacterSize(30);
    RhettSays.setCharacterSize(40);

    GameOverTitle.setFillColor(Color(164,0,0));  // text color
    GameOverInstruction1.setFillColor(Color(164,0,0));
    GameOverInstruction2.setFillColor(Color(164,0,0));
    RhettSays.setFillColor(Color(255,255,255));

    GameOverTitle.setOutlineColor(sf::Color::Black);  // text outline color
    GameOverInstruction1.setOutlineColor(sf::Color::Black);
    GameOverInstruction2.setOutlineColor(sf::Color::Black);
    RhettSays.setOutlineColor(sf::Color::Black);

    GameOverTitle.setOutlineThickness(4);  // text outline thickness
    GameOverInstruction1.setOutlineThickness(3);
    GameOverInstruction2.setOutlineThickness(3);
    RhettSays.setOutlineThickness(1.5);

    GameOverTitle.setStyle(sf::Text::Bold);
    Title.setStyle(sf::Text::Bold);

    finscore.setFillColor(Color(255,255,255));
    finscore.setOutlineThickness(3);
    finscore.setFont(font);
    finscore.setCharacterSize(40);
    finscore.setPosition(270, 210);

    highscore.setFillColor(Color(255,255,255));
    highscore.setOutlineThickness(3);
    highscore.setFont(font);
    highscore.setCharacterSize(40);
    highscore.setPosition(600, 210);

    score.setFillColor(Color(255, 255, 255));
    score.setOutlineThickness(2);
    score.setFont(font);
    score.setCharacterSize(40);
    score.setPosition(50, 30);

}

void Game_start() {
    game_start = true;

    // rhett image setting
    RhettSprite.setTexture(RhettTexture0);
    RhettSprite.setScale(.4,.4);
    RhettSprite.setPosition(rhett_x,rhett_y);

    road_bound = roadSprite1.getGlobalBounds();
    skyline_bound = skylineSprite1.getGlobalBounds();

    roadSprite1.setPosition(0, windowHeight - 110);
    roadSprite2.setPosition(road_bound.width, windowHeight - 110);
    skylineSprite1.setPosition(0, 0);
    skylineSprite2.setPosition(skyline_bound.width, 0);
    birdSprite.setPosition(1300,200);

    for (int i = 0; i < 5; i++) {
        busstop[i].setPosition(Vector2f(-1000, -1000));
    }

}

int getHighscore(int score) {

    string highscores("highscore.txt");  // initializes the file
    int highscore;

    ifstream input_file(highscores);  // creates an input file

    while (input_file >> highscore) {  // reads the current highscore and compares it to current score
        if (highscore < score) highscore = score;
        input_file.close();
    }

    ofstream output_file(highscores);  // creates an output file
    output_file.open(highscores); // clears the file
    output_file.close();
    output_file.open(highscores, ios::out);  // opens output file

    if (output_file.is_open()) {  // stores the highscore in file
        output_file << highscore;
        output_file.close();
    }

    return highscore;
}

int main() {
    //initialize window

    RenderWindow window{ sf::VideoMode(windowWidth,windowHeight), "Running Rhett" };
    window.setFramerateLimit(150);

    Game_Menu();
    Clock clock;
    while (window.isOpen())
    {
        Event menu; 
        if (menu_bool) {

            //game menu
            window.clear(Color::White);
            window.draw(skylineSprite1);

            window.draw(roadSprite1);
            window.draw(roadSprite2);
            window.draw(Rhettbegin);

            window.draw(Title);
            window.draw(Instruction1);
            window.draw(Instruction2);
            window.draw(Instruction3);

            window.display();

            while (window.pollEvent(menu)) {
                if (menu.type == Event::KeyPressed) {
                    if (menu.key.code == Keyboard::Escape) {
                        window.close();
                    } else {
                        Game_start();
                        menu_bool = false;
                    }
                }
            }

        }

        if (game_start) {

            skylineSprite1.move(Vector2f(speed/5, 0.f));
            skylineSprite2.move(Vector2f(speed/5, 0.f));
            if (skylineSprite1.getPosition().x < -skyline_bound.width) {
                skylineSprite1.setPosition(skyline_bound.width, 0);
            }
            if (skylineSprite2.getPosition().x < -skyline_bound.width) {
                skylineSprite2.setPosition(skyline_bound.width, 0);
            }

            // move ground
            roadSprite1.move(Vector2f(speed/3, 0.f));
            roadSprite2.move(Vector2f(speed/3, 0.f));
            if (roadSprite1.getPosition().x < -road_bound.width) {
                roadSprite1.setPosition(road_bound.width, windowHeight - 110);
            }

            if (roadSprite2.getPosition().x < -road_bound.width) {
                roadSprite2.setPosition(road_bound.width, windowHeight - 110);
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                if (rhett_y > windowHeight - 110) {
                    dy = -12;
                    RhettSprite.setTexture(RhettTexture0);
                }
                if (dy > 0) {
                    dy -= 0.3;
                }
            }

            birdSprite.move(Vector2f(speed, 0.f));
            if(birdSprite.getPosition().x < 0) {
			int newx = 1300;
                if (busstop[laststop-1].getPosition().x == 1280){
                    newx = newx + 150;
                    newy = newy +100;
                }

                birdcounter++;
                birdy = birdSprite.getPosition().y;
                newy = birdy + 100*pow(-1,birdcounter);
                birdSprite.setPosition(newx, newy);
            }


            if ((rand() % 60 == 0) && busstop[laststop-1].getPosition().x < windowWidth / 2) {
                busstop[laststop].setPosition(windowWidth, windowHeight - 200);
                laststop = (laststop + 1) % 5;
            }

             

            for (int i = 0; i < 5; i++) {
                busstop[i].move(Vector2f(speed, 0.f));
            }


            // Gravity

            dy += 0.35;
            rhett_y += dy;
            if (rhett_y > windowHeight - 110) {
                dy = 0;
            }

            RhettSprite.setPosition(rhett_x, rhett_y-55);

            if (((int)clock.getElapsedTime().asMilliseconds() / 10) % 8 == 0 && rhett_y > windowHeight - 110) {
                RhettTextureIndex = (RhettTextureIndex + 1) % 4;
                RhettSprite.setTexture(RhettTextures[RhettTextureIndex]);
                scoreint += 1;
            }
            if (((int)clock.getElapsedTime().asMilliseconds() / 10) % 8 == 0) {
                birdTextureIndex = (birdTextureIndex +1) % 6;
                birdSprite.setTexture(birdTextures[birdTextureIndex]);
            }

         

            sf::Thread thread(&threadFunc);
            thread.launch();
            score.setString("Score: " + to_string(scoreint));
            window.clear(Color::White);
            window.draw(skylineSprite1);
            window.draw(skylineSprite2);
            window.draw(roadSprite1);
            window.draw(roadSprite2);
            window.draw(RhettSprite);
            window.draw(birdSprite);
            window.draw(score);

            for (int i = 0; i < 5; i++) {
            window.draw(busstop[i]);
        }

            window.display();

            for (int i = 0; i < 5; i++) {
                if (RhettSprite.getGlobalBounds().intersects(busstop[i].getGlobalBounds())) {
                    RhettSays.setString("I don't like the T shuttle :<");
                    game_start = false;
                    goto ENDSCREEN;
                }
            }

            if (RhettSprite.getGlobalBounds().intersects(birdSprite.getGlobalBounds())) {
                //cout << busstop[i].getGlobalBounds() << ".\n";
                RhettSays.setString("The Boston pigeons are scary... ");
                game_start = false;
            }
        }
            ENDSCREEN:
            if (!menu_bool){
            if (!game_start) {

            Event endpage;

            int highscoreint = getHighscore(scoreint);
            window.clear(Color::White);
            window.draw(skylineSprite1);
            window.draw(skylineSprite2);
            window.draw(roadSprite1);
            window.draw(roadSprite2);
            window.draw(Rhettend);
            window.draw(GameOverTitle);
            window.draw(GameOverInstruction1);
            window.draw(GameOverInstruction2);
            window.draw(RhettSays);

            finscore.setString("Your Score: \n   "+to_string(scoreint));
            highscore.setString("High Score: \n  "+to_string(highscoreint));
            window.draw(finscore);
            window.draw(highscore);
            window.display();

            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                scoreint = 0;
                Game_start();
            }
        }
    }


        window.display();
    }


    return 0;
}
