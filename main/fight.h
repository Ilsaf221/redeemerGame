#include <SFML/Graphics.hpp>

struct Hero
{
    sf::Texture texture;
    sf::Sprite sprite;
    int hp = 5;
};

struct Enemy
{
    sf::Texture texture;
    sf::Sprite sprite;
    int type;
    int hp = 5;
    bool alive = true;
};

struct Arrow
{
    sf::Texture texture;
    sf::Sprite sprite;
    bool hit = false;
};

void initializeHero(Hero &hero);
void initializeEnemySpear(Enemy &enemy);
void initializeEnemyBow(Enemy &enemy);
void initializeEnemyGun(Enemy &enemy);
void hpPanel(sf::RenderWindow &window, Hero &hero, bool &isGame);
void move(Hero &hero, Enemy &enemy, float frame, sf::Clock &clock);
void heroAnimation(Hero &hero, float &frame, sf::Clock &clock);
void heroAttack(Hero &hero, Enemy &enemy, sf::Clock &clock);
void enemyReaction(Hero &hero, Enemy &enemy, float &frame, sf::Clock &clock, sf::RenderWindow &window);
void enemyAttack(Enemy &enemy, Hero &hero);
void enemyMove(Enemy &enemy, float &frame, sf::Clock &clock);
void enemyAnimation(Enemy &enemy, float &frame, sf::Clock &clock);
void enemyAnimationStand(Enemy &enemy, float &frame, sf::Clock &clock);