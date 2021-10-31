#include "SFML/Graphics.hpp"
#include "iostream"
#include <math.h>
#include "Collision.h"

int playerSpeed = 10;
bool fecesToggle = false;

unsigned int randomInt()
{
    unsigned int randomInt;
    asm("rdseed %%eax" : "=a"(randomInt));
    return randomInt;
}

bool collisionCheck(sf::RectangleShape &rect1, sf::RectangleShape &rect2)
{
    if (rect1.getGlobalBounds().intersects(rect2.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool ccollisionCheck(sf::RectangleShape &rect1, sf::RectangleShape &rect2)
{
    if (rect1.getGlobalBounds().intersects(rect2.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Seajam Game!!!!!", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    int garbageCount = 0;
    int score = 0;
    float time = 0;

    // Player object
    sf::RectangleShape player(sf::Vector2f(250, 250));
    player.setPosition(sf::Vector2f(1920/2, 1080/2 - 250));

    // Boss object
    sf::RectangleShape boss(sf::Vector2f(250, 250));
    boss.setPosition(sf::Vector2f(-50, 0));
    sf::RectangleShape urineDrop(sf::Vector2f(25, 125));
    urineDrop.setPosition(sf::Vector2f(50, 0));
    urineDrop.setFillColor(sf::Color::Yellow);
    sf::RectangleShape feces(sf::Vector2f(100, 150));
    feces.setPosition(sf::Vector2f(-1000, 5000));
    feces.setFillColor(sf::Color(159, 58, 0));

    // Garbage object
    sf::RectangleShape garbage(sf::Vector2f(200, 200));
    garbage.setPosition(sf::Vector2f(1487, 404));

    // Background
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setFillColor(sf::Color::Blue);

    // Land Object
    sf::RectangleShape land(sf::Vector2f(100, 1080));
    land.setPosition(sf::Vector2f(0, 0));
    land.setFillColor(sf::Color(21, 188, 31));

    // Depo Object
    sf::RectangleShape depo(sf::Vector2f(200, 200));
    depo.setPosition(sf::Vector2f(50, 1080/2-100));

    // Sign Object
    sf::RectangleShape sign(sf::Vector2f(150, 150));
    sign.setPosition(sf::Vector2f(0, 1080/4));

    // Garbage Textures
    sf::Texture garbageTexture1;
    garbageTexture1.setSmooth(true);
    if(!garbageTexture1.loadFromFile("garbage1.png"))
    {
        std::cout << "Error loading garbage1.png" << std::endl;
        return -1;
    }
    sf::Texture garbageTexture2;
    garbageTexture2.setSmooth(true);
    if(!garbageTexture2.loadFromFile("garbage2.png"))
    {
        std::cout << "Error loading garbage2.png" << std::endl;
        return -1;
    }
    sf::Texture garbageTexture3;
    garbageTexture3.setSmooth(true);
    if(!garbageTexture3.loadFromFile("garbage3.png"))
    {
        std::cout << "Error loading garbage3.png" << std::endl;
        return -1;
    }

    garbage.setTexture(&garbageTexture1);

    // Player textures
    sf::Texture playerTexture;
    playerTexture.setSmooth(true);
    if(!playerTexture.loadFromFile("player.png"))
    {
        std::cout << "Error loading player.png" << std::endl;
        return -1;
    }
    player.setTexture(&playerTexture);

    sf::Texture playerTextureFull;
    playerTextureFull.setSmooth(true);
    if(!playerTextureFull.loadFromFile("playerFull.png"))
    {
        std::cout << "Error loading playerFull.png" << std::endl;
        return -1;
    }

    // Boss Texture
    sf::Texture bossTexture;
    bossTexture.setSmooth(true);
    if(!bossTexture.loadFromFile("boss.png"))
    {
        std::cout << "Error loading boss.png" << std::endl;
        return -1;
    }
    boss.setTexture(&bossTexture);

    // Depo Texture
    sf::Texture depoTexture;
    depoTexture.setSmooth(true);
    if(!depoTexture.loadFromFile("depo.png"))
    {
        std::cout << "Error loading depo.png" << std::endl;
        return -1;
    }
    depo.setTexture(&depoTexture);

    // Sign Texture
    sf::Texture signTexture;
    signTexture.setSmooth(true);
    if(!signTexture.loadFromFile("sign.png"))
    {
        std::cout << "Error loading sign.png" << std::endl;
        return -1;
    }
    sign.setTexture(&signTexture);


    // Fonts
    sf::Font robotoFont;
    if (!robotoFont.loadFromFile("Roboto-Black.ttf"))
    {
        std::cout << "Error loading Roboto-Black.ttf" << std::endl;
        return -1;
    }

    // Text
    sf::Text garbageCountText;
    garbageCountText.setFont(robotoFont);
    garbageCountText.setCharacterSize(50);
    garbageCountText.setPosition(sf::Vector2f(1600, 50));
    garbageCountText.setString("Garbage: 0");

    sf::Text scoreText;
    scoreText.setFont(robotoFont);
    scoreText.setCharacterSize(50);
    scoreText.setPosition(sf::Vector2f(1600, 125));
    scoreText.setString("Score: 0");

    sf::Text fullGarbageText;
    fullGarbageText.setFont(robotoFont);
    fullGarbageText.setCharacterSize(50);
    fullGarbageText.setPosition(sf::Vector2f(1920/2+100, 50));
    fullGarbageText.setString("");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::F12:
                    score += 100;
                    break;
                case sf::Keyboard::F11:
                    score -= 100;
                    break;
                case sf::Keyboard::F10:
                    playerSpeed += 5;
                    break;
                case sf::Keyboard::F9:
                    playerSpeed -= 5;
                    break;
                case sf::Keyboard::F8:
                    fecesToggle = !fecesToggle;
                }
            }
        }

        if(urineDrop.getPosition().y > 1080 && int(time*100) % 50 == 0)
        {
            urineDrop.setPosition(sf::Vector2f(player.getPosition().x, -125));
        }
        else 
        {
            urineDrop.move(0, playerSpeed*0.75);
        }

        if(fecesToggle)
        {
            if(feces.getPosition().y > 1080)
            {
                feces.setPosition(sf::Vector2f(randomInt()%1920, -125));
            }
            else 
            {
                feces.move(0, playerSpeed*0.25);
            }
        }

        if (score >= 5)
        {
            fecesToggle = true;
        }

        if(garbageCount >= 10 && collisionCheck(player, depo))
        {
            score++;
            garbageCount = 0;
            garbageCountText.setString("Garbage: " + std::to_string(garbageCount));
            scoreText.setString("Score: " + std::to_string(score));
            player.setTexture(&playerTexture);
            fullGarbageText.setString("");
            playerSpeed += 5;
        }

        if(collisionCheck(player, garbage))
        {
            if (garbageCount >= 10)
            {
                player.setTexture(&playerTextureFull);
                fullGarbageText.setString("Boat is full of garbage!");
            }
            else {
                garbageCount++;
                if (garbageCount >= 10)
                {
                    player.setTexture(&playerTextureFull);
                    fullGarbageText.setString("Boat is full of garbage!");
                }
                garbageCountText.setString("Garbage: " + std::to_string(garbageCount));
                unsigned int x, y;
                x = (randomInt() % (1920 - 200)) + 100;
                y = (randomInt() % (1080 - 200)) + 100;
                if (garbage.getPosition().x - x < 500 && garbage.getPosition().x - x > -500)
                {
                    x = (randomInt() % (1920 - 200)) + 100;
                }
                if (garbage.getPosition().y - y < 500 && garbage.getPosition().y - y > -500)
                {
                    y = (randomInt() % (1080 - 00)) + 100;
                }
                if (x < 200)
                {
                    x = (randomInt() % (1920 - 200)) + 100;
                }
                else
                {
                    x = (randomInt() % (1920 - 200)) + 100;
                    y = (randomInt() % (1080 - 200)) + 100;
                }
                garbage.setPosition(x, y);
                float scale = (randomInt() % 10) / 100.0f;
                garbage.setScale(1 + scale, 1 + scale);
                switch(randomInt() % 3)
                {
                    case 0:
                        garbage.setTexture(&garbageTexture1);
                        break;
                    case 1:
                        garbage.setTexture(&garbageTexture2);
                        break;
                    case 2:
                        garbage.setTexture(&garbageTexture3);
                        break;
                }
                garbage.rotate(randomInt() % 360);
            }
        }

        if (collisionCheck(player, urineDrop) || collisionCheck(player, feces))
        {
            exit(0);
        }

        if (player.getPosition().x < 0 - player.getGlobalBounds().width - 250)
        {
            player.setPosition(1919, player.getPosition().y);
        }
        if (player.getPosition().x > 1919 + player.getGlobalBounds().width)
        {
            player.setPosition(0 - 249, player.getPosition().y);
        }
        if (player.getPosition().y < 0 - player.getGlobalBounds().height - 250)
        {
            player.setPosition(player.getPosition().x, 1079);
        }
        if (player.getPosition().y > 1079 + player.getGlobalBounds().height)
        {
            player.setPosition(player.getPosition().x, 0 - 249);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, playerSpeed);

        window.clear();
        window.draw(background);
        window.draw(land);
        window.draw(depo);
        window.draw(player);
        window.draw(boss);
        window.draw(sign);
        window.draw(garbage);
        window.draw(urineDrop);
        window.draw(feces);
        window.draw(garbageCountText);
        window.draw(scoreText);
        window.draw(fullGarbageText);
        window.display();
        time += 0.001 * (score + 1);
    }

    return 0;
}