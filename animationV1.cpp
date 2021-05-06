#include "animation.h"

animation::animation(sf::Texture* texture, sf::Vector2u imagecount, float switchtime) {
	this->ImageCount = imagecount;
	this->switchtime = switchtime;
	totaltime = 0.0f;
	CurrentImage.x = 0;
	uvRect.width = texture->getSize().x / float(imagecount.x);
	uvRect.height = texture->getSize().y / float(imagecount.y);
}

animation::~animation() {

}

void animation::update(int row, float deltatime){
	CurrentImage.y = row;
	totaltime = deltatime;

	if (totaltime >= switchtime) {
		totaltime -= switchtime;
		CurrentImage.x++;

		if (CurrentImage.x >= ImageCount.x) {
			CurrentImage.x = 0;
		}
	}

	uvRect.left = CurrentImage.x * uvRect.width;
	uvRect.top = CurrentImage.y * uvRect.height;
}
