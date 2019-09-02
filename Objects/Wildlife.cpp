#include "Wildlife.h"

//CONSTRUCTOR WILDLIFE
Wildlife::Wildlife(sf::Vector2f position) {
	this->position = position;
	velocity = sf::Vector2f(0.f, 0.f);
}

//UPDATE WILDLIFE
void Wildlife::update() {
	position += velocity;
}

//only draw when in view
//DRAW WILDLIFE
void Wildlife::draw(sf::RenderWindow &window, sf::Sprite* sprite) {
	window.draw(sprite);
}