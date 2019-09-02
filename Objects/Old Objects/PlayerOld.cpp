#include "Player.h"

#define PI 3.14159265

Player::Player(float Xscale) {
	position = sf::Vector2f(10.f,10.f);
	velocity = sf::Vector2f(0,0);
	view.reset(sf::FloatRect(0, 0, Xscale * 1616 / 3, 1616 / 3)); //101 tiles of size 16 pixels
	view.setCenter(position + sf::Vector2f(8.f,8.f));
	if (!texture.loadFromFile("Resources/PlayerSprite.png", sf::IntRect(0, 0, 32, 32))) {
		std::cout << "Error Loading Player Sprite" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setOrigin(16.f, 16.f);
}

Player::Player(sf::Vector2f position, float Xscale) {
	this->position = position;
	velocity = sf::Vector2f(0, 0);
	view.reset(sf::FloatRect(0, 0, Xscale * 1616 / 3, 1616 / 3));
	view.setCenter(this->position);
}

void Player::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}

void Player::update(sf::Vector2f Lstick, sf::Vector2f Rstick) {

	//Calc Velocity
	if (Rstick != sf::Vector2f(0, 0) && Lstick != sf::Vector2f(0, 0)) {
		float speedMod = 2;
		float angleBet = angleBetween(Lstick, Rstick);
		angleBet *= 180 / PI;
		speedMod = speedMod / (1 + .00485 * angleBet);
		velocity.x = Lstick.x * speedMod;
		velocity.y = Lstick.y * speedMod;
	}
	else if (Rstick == sf::Vector2f(0, 0)) {
		velocity.x = Lstick.x;
		velocity.y = Lstick.y;
	}
	else velocity = sf::Vector2f(0, 0);
	//Calc Angle
	if (Rstick.x != 0 || Rstick.y != 0) {
		angle = 180 * angle2f(Rstick) / PI;
	}
	if (isnan(velocity.x) || isnan(velocity.y)) velocity = sf::Vector2f(0, 0);
	if (isnan(angle)) angle = 0;
	//Change main params
	position += velocity;
	sprite.setPosition(position.x, position.y);
	sprite.setRotation(angle);
	view.move(velocity);
}

sf::View Player::getView() {
	return view;
}