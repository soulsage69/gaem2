#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\Main.hpp"
#include "SFML\System.hpp"
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\Transformable.hpp"
#include "Definitions.h"
#include "animation.h"
#include <iostream>

using namespace std;
using namespace sf;

struct koordinates {
	float x;
	float y;
};

class charr{
protected:
	unsigned int HP;
	unsigned int ammo;
public:
	void Damage(int &dam) {
		HP -= dam;
	}
	virtual void consumeAmmo() = 0;
};//sablonas gyviems sutverimams

class player : public charr {
protected:

public:
	void consumeAmmo(int &amount) {
		ammo -= amount;
	}
};


inline void Menu() {

}

void resetsky(float& a) {
	if (a <= -626.f) {
		int temp = a;
		a = 1878+temp-0.5;
	}
	else {
		a = a - 0.5;
	}
}
void resetsprite(float &a) {
	if (a<=-56) {
		int temp = a;
		a = 896+temp-5;
	}
	else {
		a = a - 5;
	}
}

int main() {
	sf::RenderWindow Window_name(sf::VideoMode(Wlength, Wheight), "Game", Style::Close | Style::Titlebar );
	Window_name.setFramerateLimit(60);

	Texture Player_idle, Sky, Grass;
	Player_idle.loadFromFile("resources/Skeleton/Sprite Sheets/Skeleton Idle.png");
	Sky.loadFromFile("resources/sky.jpg");
	Grass.loadFromFile("resources/grass_s.png");
	Grass.setRepeated(true);

	Sprite* SGrass = new Sprite[17];
	koordinates* zole=new koordinates[17];
	for (int i(0); i < 17; i++) {
		zole[i].x = i * 56;
		zole[i].y = Wheight - 56;
		SGrass[i].setTexture(Grass);
		SGrass[i].setPosition(zole[i].x, zole[i].y);
	}
	
	Sprite* SSky = new Sprite[3];//aprasomos trys dangaus sprites
	koordinates dangus[3];
	for (int i(0); i < 3; i++) {
		SSky[i].setTexture(Sky);
		dangus[i].x = i * 626.f;
		dangus[i].y = 0;
		SSky[i].setPosition(dangus[i].x, dangus[i].y);
	}

	/*Sprite SPlayer_idle;
	SPlayer_idle.setTexture(Player_idle);*/
	RectangleShape player(Vector2f(24.0f, 32.0f));
	player.setTexture(&Player_idle);
	animation pagrindinisPlayer(&Player_idle, Vector2u(11, 1), 0.3f);

	float deltatime = 0.0f;
	Clock clock;
	//declarations and misc-----------------------------------------------------------------
	
	
	while (Window_name.isOpen()) {
		deltatime = clock.restart().asSeconds();
		Event Window_Action;
		while (Window_name.pollEvent(Window_Action)) {
			if (Window_Action.type == Window_Action.Closed) {
				//Veiksmai zaidimo isjungimui.
				Window_name.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {

			for (int i(0); i < 17; i++) {
				resetsprite(zole[i].x);
				//zole[i].x = zole[i].x - 5;
				SGrass[i].setPosition(zole[i].x, zole[i].y);
				
				/*if (zole[i].x >= -56.f) {
					zole[i].x == Wlength + 56.f;
				}*/
			}
			for (int i(0); i < 3; i++) {
				resetsky(dangus[i].x);
				SSky[i].setPosition(dangus[i].x, dangus[i].y);
			}
		}
		
		pagrindinisPlayer.update(0, deltatime);
		player.setTextureRect(pagrindinisPlayer.uvRect);

		Window_name.clear();
		for (int i(0); i < 3; i++) {
			Window_name.draw(SSky[i]);
		}
		
		for (int i(0); i < 17; i++) {
			/*if (zole[i].x >= -56.f) {
				zole[i].x == Wlength + 56.f;
			}*/
			Window_name.draw(SGrass[i]);
		}
		Window_name.draw(player);
		Window_name.display();
	}
	delete[] SSky;
	delete[] SGrass;
	delete[] zole;
	return 0;
}
