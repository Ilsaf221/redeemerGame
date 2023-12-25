#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>
#include "fight.h"

void gameOverScene(sf::RenderWindow &window)
{
    sf::Texture gameOverTexture;
    gameOverTexture.loadFromFile("images/screen/gameOver/gameOver.png");

    sf::Sprite gameOver;
    gameOver.setTexture(gameOverTexture);
    gameOver.setPosition(735, 494);
    gameOver.setOrigin(230, 128);
    window.draw(gameOver);
}

bool unitsCross(Hero &hero, Enemy &enemy)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    const sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const sf::Vector2f heroOrigin = hero.sprite.getOrigin();
    const sf::Vector2f enemyOrigin = enemy.sprite.getOrigin();

    if ((((heroPosition.y + 0.15 * heroOrigin.y / 2 >= enemyPosition.y - 0.16 * enemyOrigin.x) &&
          (heroPosition.y - 0.15 * heroOrigin.y / 2 <= enemyPosition.y + 0.16 * enemyOrigin.x)) &&
         ((heroPosition.x + 0.15 * heroOrigin.x >= enemyPosition.x - 0.16 * enemyOrigin.x) &&
          (heroPosition.x - 0.15 * heroOrigin.x <= enemyPosition.x + 0.16 * enemyOrigin.x))) &&
        (enemy.alive == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void enemyAnimationStand(Enemy &enemy, float &frame, sf::Clock &clock)
{
    if (enemy.alive == true)
    {
        if (enemy.type == 1)
        {
            enemy.texture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimationStand.png");
        }
        else if (enemy.type == 2)
        {
            enemy.texture.loadFromFile("images/enemiesModels/animation/goblinBowAnimationStand.png");
        }
        else
        {
            enemy.texture.loadFromFile("images/enemiesModels/animation/goblinGunAnimationStand.png");
        }
        // float time = clock.getElapsedTime().asMicroseconds();
        // time = time / 800;

        frame += 0.38;
        // std::cout << "frame1 " << frame << std::endl;

        if (frame > 8)
        {
            frame -= 8;
            // std::cout << "frame2 " << frame << std::endl;
            // clock.restart();
        }
        // std::cout << "frame3 " << frame << std::endl;

        enemy.sprite.setTextureRect(sf::IntRect(611 * int(frame), 0, 611, 590));
    }
}

void enemyAnimation(Enemy &enemy, float &frame, sf::Clock &clock)
{
    if (enemy.type == 1)
    {
        enemy.texture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimation.png");
    }
    else if (enemy.type == 2)
    {
        enemy.texture.loadFromFile("images/enemiesModels/animation/goblinBowAnimation.png");
    }
    else
    {
        enemy.texture.loadFromFile("images/enemiesModels/animation/goblinGunAnimation.png");
    }
    // float time = clock.getElapsedTime().asMicroseconds();
    // time = time / 800;

    frame += 0.07;
    // std::cout << "frame1 " << frame << std::endl;

    if (frame > 2)
    {
        frame -= 2;
        // std::cout << "frame2 " << frame << std::endl;
        // clock.restart();
    }
    // std::cout << "frame3 " << frame << std::endl;

    enemy.sprite.setTextureRect(sf::IntRect(611 * int(frame), 0, 611, 590));
}

void enemyMove(Enemy &enemy, float &frame, sf::Clock &clock)
{
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const float offsetX = -5 + (rand() % 11);
    const float offsetY = -5 + (rand() % 11);

    // float x = 0;
    // float y = 0;

    enemyPosition.x += offsetX;
    enemyPosition.y += offsetY;

    enemyAnimation(enemy, frame, clock);
    enemy.sprite.setPosition(enemyPosition);
}

void enemySpearAttack(Enemy &enemy, Hero &hero)
{
    // sf::Texture enemyAttackTexture;
    // enemyAttackTexture.loadFromFile("images/enemiesModels/goblinSpearAttack.png");

    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    if (((heroPosition.y + 0.15 * 167.5 >= enemyPosition.y - 0.16 * 255) && (heroPosition.y - 0.15 * 167.5 <= enemyPosition.y + 0.16 * 255)) && ((heroPosition.x + 0.15 * 164 >= enemyPosition.x - 0.16 * 312) && (heroPosition.x - 0.15 * 164 <= enemyPosition.x + 0.16 * 312)))
    {
        // enemy.sprite.setTexture(enemyAttackTexture);
        enemy.sprite.setTextureRect(sf::IntRect(2 * 611, 0, 611, 590));
        hero.sprite.setColor(sf::Color(217, 124, 121));
        if (enemy.sprite.getScale().x >= 0)
        {
            hero.sprite.setPosition(heroPosition.x + 20, heroPosition.y);
        }
        else
        {
            hero.sprite.setPosition(heroPosition.x - 20, heroPosition.y);
        }
        hero.hp -= 1;
    }
}

void initializeArrow(Arrow &arrow)
{
    arrow.texture.loadFromFile("images/enemiesModels/goblinBowSprites/arrow.png");
    arrow.sprite.setTexture(arrow.texture);
    arrow.sprite.setOrigin(330, 51);
    arrow.sprite.setScale(0.15f, 0.15f);
}

void enemyBowAttack(Enemy &enemy, Hero &hero, sf::RenderWindow &window)
{
    // sf::Texture enemyAttackTexture;
    // enemyAttackTexture.loadFromFile("images/enemiesModels/goblinSpearAttack.png");

    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();

    Arrow arrow;

    initializeArrow(arrow);
    arrow.sprite.setPosition(enemyPosition.x + 54, enemyPosition.y);

    window.draw(arrow.sprite);

    // if (((heroPosition.y + 0.15 * 167.5 >= enemyPosition.y - 0.16 * 255) && (heroPosition.y - 0.15 * 167.5 <= enemyPosition.y + 0.16 * 255)) && ((heroPosition.x + 0.15 * 164 >= enemyPosition.x - 0.16 * 312) && (heroPosition.x - 0.15 * 164 <= enemyPosition.x + 0.16 * 312)))
    // {
    //     // enemy.sprite.setTexture(enemyAttackTexture);
    //     enemy.sprite.setTextureRect(sf::IntRect(2 * 611, 0, 611, 590));
    //     hero.sprite.setColor(sf::Color(217, 124, 121));
    //     if (enemy.sprite.getScale().x >= 0)
    //     {
    //         hero.sprite.setPosition(heroPosition.x + 20, heroPosition.y);
    //     }
    //     else
    //     {
    //         hero.sprite.setPosition(heroPosition.x - 20, heroPosition.y);
    //     }
    //     hero.hp -= 1;
    // }
}

void enemyReaction(Hero &hero, Enemy &enemy, float &frame, sf::Clock &clock, sf::RenderWindow &window)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();

    const float step = 2;

    const sf::Vector2f motion = heroPosition - enemyPosition;

    if ((motion.x <= 200) && (motion.y <= 200))
    {
        sf::Vector2f direction;
        if (enemy.hp <= 0)
        {
            direction = {0, 0};
            enemy.sprite.setColor(sf::Color(94, 93, 88));
            enemy.sprite.setRotation(-90);
            enemy.alive = false;
        }
        else
        {
            direction = {motion.x / sqrt(pow(motion.x, 2) + pow(motion.y, 2)),
                         motion.y / sqrt(pow(motion.x, 2) + pow(motion.y, 2))};
            enemyAnimation(enemy, frame, clock);
            if (enemy.type == 1)
            {
                enemySpearAttack(enemy, hero);
            }
            else if (enemy.type == 2)
            {

                enemyBowAttack(enemy, hero, window);
            }

            if (motion.x < 0)
            {
                enemy.sprite.setScale(-0.16, 0.16);
            }
            else
            {
                enemy.sprite.setScale(0.16, 0.16);
            }
        }

        enemyPosition = enemyPosition + direction * step;
        enemy.sprite.setPosition(enemyPosition);
    }
}

void heroAttack(Hero &hero, Enemy &enemy, sf::Clock &clock)
{
    // float time = clock.getElapsedTime().asSeconds();

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        hero.sprite.setTextureRect(sf::IntRect(4 * 649, 0, 721, 649));

        const sf::Vector2f heroPosition = hero.sprite.getPosition();
        const sf::Vector2f enemyPosition = enemy.sprite.getPosition();

        if (unitsCross(hero, enemy) == true)
        {
            enemy.sprite.setColor(sf::Color(217, 124, 121));
            if (hero.sprite.getScale().x >= 0)
            {
                enemy.sprite.setPosition(enemyPosition.x + 10, enemyPosition.y);
            }
            else
            {
                enemy.sprite.setPosition(enemyPosition.x - 10, enemyPosition.y);
            }
            enemy.hp -= 1;
        }
        // time = clock.restart().asSeconds();

        // std::cout << "hero.sprite" << heroPosition.x;
        // std::cout << "hero.sprite" << heroPosition.y << std::endl;
        // std::cout << "enemy" << enemyPosition.x;
        // std::cout << "enemy" << enemyPosition.y << std::endl;
    }

    // if (time >= 0.4)
    // {
    //     hero.sprite.setTexture(hero.spriteTexture);
    //     hero.sprite.setTextureRect(sf::IntRect(0, 0, 649, 649));
    // }
}

void heroAnimation(Hero &hero, float &frame, sf::Clock &clock)
{
    float time = clock.getElapsedTime().asMicroseconds();
    time = time / 800;

    frame += 0.0021 * time;
    if (frame > 4)
    {
        frame -= 4;
        clock.restart();
    }

    hero.sprite.setTextureRect(sf::IntRect(649 * int(frame), 0, 649, 649));
}

void move(Hero &hero, Enemy &enemy, float frame, sf::Clock &clock)
{
    sf::Vector2f heroPosition = hero.sprite.getPosition();
    sf::Vector2f enemyOrigin = enemy.sprite.getPosition();
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
            hero.sprite.setScale(-0.15f, 0.15f);
        }
        // heroAnimation(hero, frame, clock);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (heroPosition.x + step <= 1405.8)
        {
            heroPosition.x += step;
            hero.sprite.setScale(0.15f, 0.15f);
        }
        // heroAnimation(hero, frame, clock);
    }

    // heroAnimation(hero.sprite);

    hero.sprite.setPosition(heroPosition);
    heroAnimation(hero, frame, clock);
}

void hpPanel(sf::RenderWindow &window, Hero &hero, bool &isGame)
{
    sf::Texture hpIcon;
    hpIcon.loadFromFile("images/screen/hp/hpPanel2.png");
    sf::Sprite hp;
    hp.setTexture(hpIcon);
    hp.setPosition(31, 30);
    hp.setOrigin(20.5, 30);
    hp.setTextureRect(sf::IntRect(0, 0, 41 * hero.hp, 60));

    sf::RectangleShape panelBG;
    panelBG.setSize({209, 50});
    panelBG.setPosition({8, 7});
    panelBG.setFillColor(sf::Color(168, 137, 93));
    panelBG.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    panelBG.setOutlineThickness(2);

    window.draw(panelBG);
    window.draw(hp);

    if (hero.hp <= 0)
    {
        isGame = false;
        gameOverScene(window);
    }

    // sf::Text text("6/6", "arial", 14);
    // // text.setString(oss.str());
    // text.setColor(sf::Color::Black);
    // text.setPosition(60, 35);
}

void initializeEnemySpear(Enemy &enemy)
{
    enemy.texture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimation.png");
    enemy.sprite.setTexture(enemy.texture);
    enemy.sprite.setPosition(300, 300);
    enemy.sprite.setOrigin(255, 312);
    enemy.sprite.setScale(
        0.16f,
        0.16f);
    enemy.sprite.setTextureRect(sf::IntRect(0, 0, 611, 590));
    enemy.type = 1;
}

void initializeEnemyBow(Enemy &enemy)
{
    enemy.texture.loadFromFile("images/enemiesModels/animation/goblinBowAnimation.png");
    enemy.sprite.setTexture(enemy.texture);
    enemy.sprite.setPosition(900, 900);
    enemy.sprite.setOrigin(255, 312);
    enemy.sprite.setScale(
        0.16f,
        0.16f);
    enemy.sprite.setTextureRect(sf::IntRect(0, 0, 611, 590));
    enemy.type = 2;
}

void initializeEnemyGun(Enemy &enemy)
{
    enemy.texture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimation.png");
    enemy.sprite.setTexture(enemy.texture);
    enemy.sprite.setPosition(900, 900);
    enemy.sprite.setOrigin(255, 312);
    enemy.sprite.setScale(
        0.16f,
        0.16f);
    enemy.sprite.setTextureRect(sf::IntRect(0, 0, 611, 590));
    enemy.type = 3;
}

void initializeHero(Hero &hero)
{
    hero.texture.loadFromFile("images/heroesModels/animation/yodaAnimation.png");

    hero.sprite.setTexture(hero.texture);
    hero.sprite.setPosition(735, 494);
    hero.sprite.setOrigin(295, 324.5);
    hero.sprite.setScale(0.15f, 0.15f);
    hero.sprite.setTextureRect(sf::IntRect(0, 0, 649, 649));
}