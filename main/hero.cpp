#include <SFML/Graphics.hpp>
#include "hero.h"

void heroAttack(sf::Sprite &hero, sf::Texture &heroTexture, sf::Texture &heroAttackTexture, sf::Sprite &enemy, sf::Clock &clock)
{
    // float time = clock.getElapsedTime().asSeconds();

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        hero.setTexture(heroAttackTexture);
        hero.setTextureRect(sf::IntRect(0, 0, 721, 649));
        hero.setOrigin(295, 324.5);

        const sf::Vector2f heroPosition = hero.getPosition();
        const sf::Vector2f enemyPosition = enemy.getPosition();

        if (((heroPosition.y - 0.15 * 167.5 >= enemyPosition.y - 0.16 * 255) && (heroPosition.y + 0.15 * 167.5 <= enemyPosition.y + 0.16 * 255)) && ((heroPosition.x + 0.15 * 295 <= enemyPosition.x + 0.16 * 312) && (heroPosition.x - 0.15 * 295 >= enemyPosition.x - 0.16 * 312)))
        {
            enemy.setColor(sf::Color(217, 124, 121));
            enemy.setPosition(enemyPosition.x - 0.5, enemyPosition.y);
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

void animation(sf::Sprite &hero, float &frame, sf::Clock &clock)
{
    float time = clock.getElapsedTime().asMicroseconds();
    time = time / 800;

    frame += 0.003 * time;
    std::cout << "frame " << frame << std::endl;
    if (frame > 4)
    {
        std::cout << ">4 " << frame << std::endl;
        frame -= 4;
        clock.restart();
        std::cout << "frame2 " << frame << std::endl;
    }

    std::cout << "frame3 " << frame << std::endl;

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
        animation(hero, frame, clock);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (heroPosition.y + step <= 887.325)
        {
            heroPosition.y += step;
        }
        animation(hero, frame, clock);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (heroPosition.x - step >= 64.2)
        {
            heroPosition.x -= step;
            hero.setScale(-0.15f, 0.15f);
        }
        animation(hero, frame, clock);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (heroPosition.x + step <= 1405.8)
        {
            heroPosition.x += step;
            hero.setScale(0.15f, 0.15f);
        }
        animation(hero, frame, clock);
    }

    // animation(hero);

    hero.setPosition(heroPosition);
}

void initializeHero()
{
    sf::Texture heroTexture;
    heroTexture.loadFromFile("images/heroesModels/animation/yodaAnimation.png");

    sf::Sprite hero;
    hero.setTexture(heroTexture);
    hero.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    hero.setOrigin(295, 324.5);
    hero.setScale(0.15f, 0.15f);
    hero.setTextureRect(sf::IntRect(0, 0, 649, 649));
}

struct Hero
{
    sf::Sprite sprite;
};