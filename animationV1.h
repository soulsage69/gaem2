#pragma once
#include "SFML\Graphics.hpp"
class animation{
private:
	sf::Vector2u ImageCount, CurrentImage;
	float totaltime;
	float switchtime;
public:
	animation(sf::Texture* texture, sf::Vector2u imagecount, float switchtime);
	~animation();
	sf::IntRect uvRect;

	void update(int row, float deltatime);
};

