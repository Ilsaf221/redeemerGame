#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "map.h"
#include "fight.h"

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

void redrawFrame(sf::RenderWindow &window, Hero &hero, bool &isGame)
{
    window.clear();
    initializeMap(window);
    hpPanel(window, hero, isGame);
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

    Hero hero;
    Enemy enemySpear;
    Enemy enemyBow;

    initializeHero(hero);
    initializeEnemySpear(enemySpear);
    initializeEnemyBow(enemyBow);

    sf::Clock clock;
    sf::Clock clock2;

    bool isGame = true;
    float enemyFrame = 0;
    float enemyStandFrame = 0;
    float heroFrame = 0;

    while (window.isOpen())
    {
        redrawFrame(window, hero, isGame);
        if (isGame == true)
        {
            move(hero, enemySpear, heroFrame, clock);
            move(hero, enemyBow, heroFrame, clock);
            enemyAnimationStand(enemySpear, enemyStandFrame, clock2);
            enemyAnimationStand(enemyBow, enemyStandFrame, clock2);
            // enemyMove(enemySpear, enemyFrame, clock2);
            enemyReaction(hero, enemySpear, enemyFrame, clock2, window);
            enemyReaction(hero, enemyBow, enemyFrame, clock2, window);
            heroAttack(hero, enemySpear, clock);
            heroAttack(hero, enemyBow, clock);
        }
        pollEvents(window);
        window.draw(enemySpear.sprite);
        window.draw(enemyBow.sprite);
        window.draw(hero.sprite);
        window.display();
    }
}
