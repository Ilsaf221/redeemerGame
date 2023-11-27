#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "map.h"

void enemyAnimation(sf::Sprite &enemy, float &frame, sf::Clock &clock)
{
    // float time = clock.getElapsedTime().asMicroseconds();
    // time = time / 800;

    frame += 0.05;
    // std::cout << "frame1 " << frame << std::endl;

    if (frame > 2)
    {
        frame -= 2;
        // std::cout << "frame2 " << frame << std::endl;
        // clock.restart();
    }
    // std::cout << "frame3 " << frame << std::endl;

    enemy.setTextureRect(sf::IntRect(611 * int(frame), 0, 611, 590));
}

void enemyMove(sf::Sprite &enemy, float &frame, sf::Clock &clock)
{
    sf::Vector2f enemyPosition = enemy.getPosition();
    const float offsetX = -5 + (rand() % 11);
    const float offsetY = -5 + (rand() % 11);

    std::cout << "offsetX " << offsetX << std::endl;
    std::cout << "offsetY " << offsetY << std::endl;

    // float x = 0;
    // float y = 0;

    enemyPosition.x += offsetX;
    enemyPosition.y += offsetY;

    enemyAnimation(enemy, frame, clock);
    enemy.setPosition(enemyPosition);
}

void enemyAttack(sf::Sprite &enemy, sf::Sprite &hero)
{
    // sf::Texture enemyAttackTexture;
    // enemyAttackTexture.loadFromFile("images/enemiesModels/goblinSpearAttack.png");

    const sf::Vector2f heroPosition = hero.getPosition();
    sf::Vector2f enemyPosition = enemy.getPosition();
    if (((heroPosition.y - 0.15 * 167.5 >= enemyPosition.y - 0.16 * 255) && (heroPosition.y + 0.15 * 167.5 <= enemyPosition.y + 0.16 * 255)) && ((heroPosition.x + 0.15 * 295 <= enemyPosition.x + 0.16 * 312) && (heroPosition.x - 0.15 * 295 >= enemyPosition.x - 0.16 * 312)))
    {
        // enemy.setTexture(enemyAttackTexture);
        enemy.setTextureRect(sf::IntRect(2 * 611, 0, 611, 590));
        hero.setColor(sf::Color(217, 124, 121));
        if (enemy.getScale().x >= 0)
        {
            hero.setPosition(heroPosition.x + 10, heroPosition.y);
        }
        else
        {
            hero.setPosition(heroPosition.x - 10, heroPosition.y);
        }
    }
}

void enemyReaction(sf::Sprite &hero, sf::Sprite &enemy, float &frame, sf::Clock &clock)
{
    const sf::Vector2f heroPosition = hero.getPosition();
    sf::Vector2f enemyPosition = enemy.getPosition();

    const float step = 2;

    const sf::Vector2f motion = heroPosition - enemyPosition;

    if ((motion.x <= 200) && (motion.y <= 200))
    {
        sf::Vector2f direction;
        if (((motion.x <= 0.5) && (motion.x >= -0.5)) && ((motion.y <= 0.5) && (motion.y >= -0.5)))
        {
            direction = {0, 0};
        }
        else
        {
            direction = {motion.x / sqrt(pow(motion.x, 2) + pow(motion.y, 2)),
                         motion.y / sqrt(pow(motion.x, 2) + pow(motion.y, 2))};
        }

        if (motion.x < 0)
        {
            enemy.setScale(-0.16, 0.16);
        }
        else
        {
            enemy.setScale(0.16, 0.16);
        }

        enemyPosition = enemyPosition + direction * step;
        enemy.setPosition(enemyPosition);
        enemyAnimation(enemy, frame, clock);
        enemyAttack(enemy, hero);
    }
}

void heroAttack(sf::Sprite &hero, sf::Sprite &enemy, sf::Clock &clock)
{
    // float time = clock.getElapsedTime().asSeconds();

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        hero.setTextureRect(sf::IntRect(4 * 649, 0, 721, 649));

        const sf::Vector2f heroPosition = hero.getPosition();
        const sf::Vector2f enemyPosition = enemy.getPosition();

        if (((heroPosition.y + 0.15 * 167.5 >= enemyPosition.y - 0.16 * 255) && (heroPosition.y - 0.15 * 167.5 <= enemyPosition.y + 0.16 * 255)) && ((heroPosition.x + 0.15 * 295 >= enemyPosition.x - 0.16 * 312) && (heroPosition.x - 0.15 * 295 <= enemyPosition.x + 0.16 * 312)))
        {
            std::cout << "yes" << std::endl;
            enemy.setColor(sf::Color(217, 124, 121));
            if (hero.getScale().x >= 0)
            {
                enemy.setPosition(enemyPosition.x + 10, enemyPosition.y);
            }
            else
            {
                enemy.setPosition(enemyPosition.x - 10, enemyPosition.y);
            }
        }
        // time = clock.restart().asSeconds();

        // std::cout << "hero" << heroPosition.x;
        // std::cout << "hero" << heroPosition.y << std::endl;
        // std::cout << "enemy" << enemyPosition.x;
        // std::cout << "enemy" << enemyPosition.y << std::endl;
    }

    // if (time >= 0.4)
    // {
    //     hero.setTexture(heroTexture);
    //     hero.setTextureRect(sf::IntRect(0, 0, 649, 649));
    // }
}

void heroAnimation(sf::Sprite &hero, float &frame, sf::Clock &clock)
{
    float time = clock.getElapsedTime().asMicroseconds();
    time = time / 800;

    frame += 0.002 * time;
    if (frame > 4)
    {
        frame -= 4;
        clock.restart();
    }

    hero.setTextureRect(sf::IntRect(649 * int(frame), 0, 649, 649));
}

void move(sf::Sprite &hero, sf::Sprite &enemy, float frame, sf::Clock &clock)
{
    sf::Vector2f heroPosition = hero.getPosition();
    sf::Vector2f enemyOrigin = enemy.getPosition();
    // const float dt = clock.restart().asSeconds();
    // const float speed = 650;
    const float step = 5;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (heroPosition.y - step >= 44.675)
        {
            heroPosition.y -= step;
        }
        // heroAnimation(hero, frame, clock);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (heroPosition.y + step <= 887.325)
        {
            heroPosition.y += step;
        }
        // heroAnimation(hero, frame, clock);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (heroPosition.x - step >= 64.2)
        {
            heroPosition.x -= step;
            hero.setScale(-0.15f, 0.15f);
        }
        // heroAnimation(hero, frame, clock);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (heroPosition.x + step <= 1405.8)
        {
            heroPosition.x += step;
            hero.setScale(0.15f, 0.15f);
        }
        // heroAnimation(hero, frame, clock);
    }

    // heroAnimation(hero);

    hero.setPosition(heroPosition);
    heroAnimation(hero, frame, clock);
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        defaut:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &hero, sf::Sprite &enemySpear)
{
    window.clear();
    // window.draw(map);
    initializeMap(window);
    hpPanel(window);
    window.draw(enemySpear);
    window.draw(hero);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1470; //1465
    constexpr unsigned WINDOW_HEIGHT = 988; //986

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Redeemer",
        sf::Style::Default, settings);

    sf::Texture heroTexture;
    heroTexture.loadFromFile("images/heroesModels/animation/yodaAnimation2.png");

    sf::Texture enemySpearTexture;
    enemySpearTexture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimation2.png");

    sf::Sprite hero;
    hero.setTexture(heroTexture);
    hero.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    hero.setOrigin(295, 324.5);
    hero.setScale(0.15f, 0.15f);
    hero.setTextureRect(sf::IntRect(0, 0, 649, 649));

    sf::Sprite enemySpear;
    enemySpear.setTexture(enemySpearTexture);
    enemySpear.setPosition(300, 300);
    enemySpear.setOrigin(255, 312);
    enemySpear.setScale(
        0.16f,
        0.16f);
    enemySpear.setTextureRect(sf::IntRect(0, 0, 611, 590));

    sf::Clock clock;
    sf::Clock clock2;

    float enemyFrame = 0;
    float heroFrame = 0;

    while (window.isOpen())
    {
        pollEvents(window);
        move(hero, enemySpear, heroFrame, clock);
        // enemyMove(enemySpear, enemyFrame, clock2);
        enemyReaction(hero, enemySpear, enemyFrame, clock2);
        heroAttack(hero, enemySpear, clock);
        redrawFrame(window, hero, enemySpear);
    }
}
