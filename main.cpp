#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

struct Surface
{
    int Level;
    int LeftEdge;
    int RightEdge;
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Just Testing", sf::Style::Default);
    window.setKeyRepeatEnabled(true);
    sf::Event event;
    sf::Keyboard kbrd;
    //sf::Mouse mouse;
    sf::Texture BackgroundTxtr;
    BackgroundTxtr.loadFromFile("background.png");
    sf::Sprite Background(BackgroundTxtr);
    Background.setPosition(-500, 0);
    sf::Texture BigBackgroundTxtr;
    BigBackgroundTxtr.loadFromFile("1-wtc-america-architecture-374710.jpg");
    sf::Sprite BigBackground(BigBackgroundTxtr);
    BigBackground.setPosition(-1000, -200);
    sf::Texture txtr2;
    txtr2.loadFromFile("skeleton.png");
    sf::IntRect standardRect2(0,128,64,64);
    sf::IntRect initialRect2(standardRect2);
    sf::Sprite player2(txtr2, standardRect2);
    player2.setPosition(600, 100);
    char Direction;
    bool Moving=false;
    bool Jumping;
    //float Speed;
    float ISpeed;
    float Speed;
    float Yposition;
    float IYposition;
    float TimeInAir;
    float G=1000;
    bool GravityAffects;
    float CurrentY;
    float PreviousY=player2.getPosition().y;
    Surface surface1;
    surface1.LeftEdge=97;
    surface1.RightEdge=694;
    surface1.Level=435;
    sf::Clock myClock2;
    sf::Clock AirClock;

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::EventType::Closed || kbrd.isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            if(event.type==sf::Event::EventType::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Z)
                {
                    initialRect2.top=8*64;
                    Direction='U';
                    Moving=true;

                }
                if(event.key.code==sf::Keyboard::S)
                {
                    initialRect2.top=10*64;
                    Direction='D';
                    Moving=true;
                }
                if(event.key.code==sf::Keyboard::D)
                {
                    initialRect2.top=11*64;
                    Direction='R';
                    Moving=true;
                }
                if(event.key.code==sf::Keyboard::Q)
                {
                    initialRect2.top=9*64;
                    Direction='L';
                    Moving=true;
                }
                if(event.key.code==sf::Keyboard::Space)
                {
                    Jumping=true;
                    GravityAffects=true;
                    ISpeed=-400;
                    IYposition=player2.getPosition().y;
                    initialRect2.left=0;
                    AirClock.restart();
                }
            }
            if(event.type==sf::Event::EventType::KeyReleased)
            {
                if(event.key.code==sf::Keyboard::Z || event.key.code==sf::Keyboard::S
                   || event.key.code==sf::Keyboard::D || event.key.code==sf::Keyboard::Q)
                {
                    initialRect2.left=0;
                    Moving=false;
                }
            }
        }
        if(Moving)
        {
            if(myClock2.getElapsedTime()>=sf::milliseconds(0.5f))
            {
                ///Player 2 animation..........................
                if(!GravityAffects)
                {
                    if(initialRect2.left<512)
                    {
                        initialRect2.left+=64;
                    }
                    else
                    {
                        initialRect2.left=0;
                    }
                }
                if(Direction=='U')
                {
                    player2.move(0, -2);
                }
                if(Direction=='D')
                {
                    player2.move(0, 2);
                }
                if(Direction=='R')
                {
                    player2.move(20, 0);
                }
                if(Direction=='L')
                {
                    player2.move(-20, 0);
                }
                myClock2.restart();
            }
        }
        TimeInAir=AirClock.getElapsedTime().asSeconds();
        if(GravityAffects)
        {
            Speed=G*TimeInAir+ISpeed;
            Yposition=0.5*G*TimeInAir*TimeInAir+ISpeed*TimeInAir+IYposition;
            player2.setPosition(player2.getPosition().x, Yposition);
        }
        CurrentY=player2.getPosition().y;
        if(player2.getPosition().x > (surface1.LeftEdge-player2.getGlobalBounds().width+25) && player2.getPosition().x < (surface1.RightEdge-25)
           && PreviousY <= (surface1.Level-player2.getGlobalBounds().height+4) && CurrentY >= (surface1.Level-player2.getGlobalBounds().height+4))
        {
            player2.setPosition(player2.getPosition().x, surface1.Level-player2.getGlobalBounds().height+4);
            Jumping=false;
            GravityAffects=false;
            ISpeed=0;
            AirClock.restart();
        }
        else
        {
            if(!Jumping)
            {
                GravityAffects=true;
                ISpeed=0;
                IYposition=player2.getPosition().y;
            }
        }
        window.setView(sf::View(sf::Vector2f(player2.getPosition().x, window.getView().getCenter().y), window.getView().getSize()));
        system("cls");
        cout << Speed << "\n\n\n";
        cout << "\n\n\nX: " << player2.getPosition().x << " Y: " << player2.getPosition().y;
        //cout << "\n\n PushingSpeed: " << ISpeed << "\n Gravity: " << GravityAffects << "\n Initial Y Position: " << IYposition << endl;
        player2.setTextureRect(initialRect2);
        window.draw(BigBackground);
        window.draw(Background);
        window.draw(player2);
        window.display();
        PreviousY=CurrentY;
    }


    return 0;
}
