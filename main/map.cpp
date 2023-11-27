#include <SFML/Graphics.hpp>
#include "map.h"

void initializeMap(sf::RenderWindow &window)
{
    sf::Texture mapTexture;
    mapTexture.loadFromFile("D:/2ndCourse/cPlus/myGame/images/map/level1/whole_map.png");

    sf::Sprite map;
    map.setTexture(mapTexture);
    map.setPosition(0, 0);
    window.draw(map);
}

void hpPanel(sf::RenderWindow &window)
{
    sf::Texture hpIcon;
    hpIcon.loadFromFile("D:/2ndCourse/cPlus/myGame/images/screen/hp_panel.png");
    sf::Sprite hp;
    hp.setTexture(hpIcon);
    hp.setPosition(36, 35);
    hp.setOrigin(20.5, 30);
    hp.setTextureRect(sf::IntRect(0, 0, 146, 60)); // (99, 60), (46, 60)

    sf::RectangleShape panelBG;
    panelBG.setSize({160, 60});
    panelBG.setPosition({8, 7});
    panelBG.setFillColor(sf::Color(168, 137, 93));
    panelBG.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    panelBG.setOutlineThickness(2);

    window.draw(panelBG);
    window.draw(hp);

    // sf::Text text("6/6", "arial", 14);
    // // text.setString(oss.str());
    // text.setColor(sf::Color::Black);
    // text.setPosition(60, 35);
}