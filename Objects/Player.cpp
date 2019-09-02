#include "Player.h"

#define PI 3.14159265

/*
 *
 * HEAD CLASS
 *
 */

//HEAD CONSTRUNCTOR
HeadPart::HeadPart(int headNum) {
	if (!texture.loadFromFile("Resources/Heads.png", sf::IntRect(0, 16 * headNum, 64, 16))) {
		std::cout << "Error Loading Head Texture" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	std::ifstream headInfo("Resources/headInfo.txt");
	if (headInfo.is_open()) {
		std::string currentLine;
		for (int i = 0; i < headNum + 1; i++) getline(headInfo, currentLine);
		getline(headInfo, currentLine);
		connector = getConnector(currentLine);
	}
	else std::cout << "Error Getting Head Info" << std::endl;
	headInfo.close();
	sprite.setOrigin(0,0);
}

/*
//HEAD DESTRUCTOR
HeadPart::~HeadPart() {
	delete texture;
	delete sprite;
}
*/

//UPDATE HEAD
void HeadPart::update(float angle) {
	if (angle < 45 || angle >= 315) {
		sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
	}
	if (angle >= 45 && angle < 135) {
		sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
	}
	if (angle >= 135 && angle < 225) {
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	if (angle >= 225 && angle < 315) {
		sprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
	}
}

//DRAW HEAD
void HeadPart::draw(sf::RenderWindow &window, sf::Vector2f position) {
	sprite.setPosition(position - connector);
	window.draw(sprite);
}

/*
 *
 * BODY CLASS
 *
 */

//BODY CONSTRUCTOR
BodyPart::BodyPart(int bodyNum) {
	if (!texture.loadFromFile("Resources/Bodys.png", sf::IntRect(0, 16 * bodyNum, 64, 16))) {
		std::cout << "Error Loading Body Texture" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	std::ifstream bodyInfo("Resources/bodyInfo.txt");
	if (bodyInfo.is_open()) {
		std::string currentLine;
		for (int i = 0; i < 9 * bodyNum + 1; i++) getline(bodyInfo, currentLine);
		getline(bodyInfo, currentLine);
		connectorArmL = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorArmR = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorArmF = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorArmB = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorLegL = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorLegR = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorLegF = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorLegB = getConnector(currentLine);
		getline(bodyInfo, currentLine);
		connectorHead = getConnector(currentLine);
	}
	else std::cout << "Error Getting Body Info" << std::endl;
	bodyInfo.close();
	sprite.setOrigin(0,0);
}

/*
//BODY DESTRUCTOR
BodyPart::~BodyPart() {
	delete texture;
	delete sprite;
}
*/

//UPDATE BODY
void BodyPart::update(float angle) {
	if (angle < 45 || angle >= 315) {
		sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
	}
	if (angle >= 45 && angle < 135) {
		sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
	}
	if (angle >= 135 && angle < 225) {
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	if (angle >= 225 && angle < 315) {
		sprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
	}
}

//DRAW BODY
void BodyPart::draw(sf::RenderWindow &window, sf::Vector2f position, float angle, LegPart * legL, LegPart * legR, ArmPart * armL, ArmPart * armR, HeadPart * head) {
	if (angle < 45 || angle >= 315) {
		legR->draw(window, position + connectorLegR);
		legL->draw(window, position + connectorLegL);
		sprite.setPosition(position);
		window.draw(sprite);
		armR->draw(window, position + connectorArmR);
		armL->draw(window, position + connectorArmL);
		head->draw(window, position + connectorHead);
	}
	else if (angle >= 45 && angle < 135) {
		legL->draw(window, position + connectorLegB);
		armL->draw(window, position + connectorArmB);
		legR->draw(window, position + connectorLegF);
		sprite.setPosition(position);
		window.draw(sprite);
		armR->draw(window, position + connectorArmF);
		head->draw(window, position + connectorHead);
	}
	else if (angle >= 135 && angle < 225) {
		legL->draw(window, position + connectorLegR);
		legR->draw(window, position + connectorLegL);
		sprite.setPosition(position);
		window.draw(sprite);
		armL->draw(window, position + connectorArmR);
		armR->draw(window, position + connectorArmL);
		head->draw(window, position + connectorHead);
	}
	else if (angle >= 225 && angle < 315) {
		legR->draw(window, position + connectorLegB);
		armR->draw(window, position + connectorArmB);
		legL->draw(window, position + connectorLegF);
		sprite.setPosition(position);
		window.draw(sprite);
		armL->draw(window, position + connectorArmF);
		head->draw(window, position + connectorHead);
	}
}

/*
 *
 * LEG CLASS
 *
 */

//LEG CONSTRUCTOR
LegPart::LegPart(int legNum, bool right) {
	if (!texture.loadFromFile("Resources/Legs.png", sf::IntRect(0, 56 * legNum, 32, 64))) {
		std::cout << "Error Loading Leg Texture" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 8, 8));
	std::ifstream legInfo("Resources/legInfo.txt");
	if (legInfo.is_open()) {
		std::string currentLine;
		for (int i = 0; i < 2 * legNum + 1; i++) getline(legInfo, currentLine);
		getline(legInfo, currentLine);
		topLeg = getConnector(currentLine);
		getline(legInfo, currentLine);
		botLeg = getConnector(currentLine);
	}
	else std::cout << "Error Getting Leg Info" << std::endl;
	legInfo.close();
	sprite.setOrigin(0, 0);
	animationPos = 0;
	if (right) offset = 6;
	else offset = 0;
	holdFrames = 0;
	animationSequence = std::vector<int>{0,1,2,3,2,1,4,5,6,5,4,0};
}

/*
//LEG DESTRUCTOR
LegPart::~LegPart() {
	delete texture;
	delete sprite;
}
*/

//UPDATE LEG
void LegPart::update(float angle, sf::Vector2f velocity) {
	if (velocity != sf::Vector2f(0,0)) {
		if (holdFrames == 6) {
			animationPos++;
			if (animationPos + offset == animationSequence.size())	animationPos = (-1)*offset;
			holdFrames = 0;
		}
		else holdFrames++;
	}
	else animationPos = 0;
	int frame = animationSequence[animationPos + offset];
	if (angle < 45 || angle >= 315) {
		sprite.setTextureRect(sf::IntRect(16, frame * 8, 8, 8));
	}
	if (angle >= 45 && angle < 135) {
		sprite.setTextureRect(sf::IntRect(8, frame * 8 , 8, 8));
	}
	if (angle >= 135 && angle < 225) {
		sprite.setTextureRect(sf::IntRect(0, frame * 8, 8, 8));
	}
	if (angle >= 225 && angle < 315) {
		sprite.setTextureRect(sf::IntRect(24, frame * 8, 8, 8));
	}
}

//DRAW LEG
void LegPart::draw(sf::RenderWindow &window, sf::Vector2f position) {
	sprite.setPosition(position - topLeg);
	window.draw(sprite);
}

/*
 *
 * ARM CLASS
 *
 */

//ARM CONSTRUCTOR
ArmPart::ArmPart(int armNum, bool right) {
	if (!texture.loadFromFile("Resources/Arms.png", sf::IntRect(0, 8 * armNum, 32, 8))) {
		std::cout << "Error Loading Arm Texture" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 8, 8));
	std::ifstream armInfo("Resources/armInfo.txt");
	if (armInfo.is_open()) {
		std::string currentLine;
		for (int i = 0; i < 2 * armNum + 1; i++) getline(armInfo, currentLine);
		getline(armInfo, currentLine);
		topArm = getConnector(currentLine);
		getline(armInfo, currentLine);
		botArm = getConnector(currentLine);
	}
	else std::cout << "Error Getting Arm Info" << std::endl;
	armInfo.close();
	sprite.setOrigin(topArm.x, topArm.y);
	if (right) forward = true;
	else forward = false;
	rotation = 0;
}

/*
//ARM DESTRUCTOR
ArmPart::~ArmPart() {
	delete texture;
	delete sprite;
}
*/

//UPDATE ARM
void ArmPart::update(float angle, sf::Vector2f velocity) {
	if (velocity != sf::Vector2f(0, 0)) {
		if (forward) {
			if (rotation > 45) {
				rotation = 45;
				forward = false;
			}
			rotation += 2;
		}
		else {
			if (rotation < -45) {
				rotation = -45;
				forward = true;
			}
			rotation -= 2;
		}
	}
	else rotation = 0;
	if (angle < 45 || angle >= 315) {
		sprite.setTextureRect(sf::IntRect(16, 0, 8, 8));
		sprite.setRotation(rotation / 9);
	}
	if (angle >= 45 && angle < 135) {
		sprite.setTextureRect(sf::IntRect(8, 0, 8, 8));
		sprite.setRotation(rotation);
	}
	if (angle >= 135 && angle < 225) {
		sprite.setTextureRect(sf::IntRect(0, 0, 8, 8));
		sprite.setRotation(rotation / 9);
	}
	if (angle >= 225 && angle < 315) {
		sprite.setTextureRect(sf::IntRect(24, 0, 8, 8));
		sprite.setRotation(rotation);
	}
}

//DRAW ARM
void ArmPart::draw(sf::RenderWindow &window, sf::Vector2f position) {
	sprite.setPosition(position);
	window.draw(sprite);
}

/*
 *
 * PLAYER CLASS
 *
 */

//PLAYER CONSTRUCTOR
Player::Player(float Xscale) {
	const float tileSize = 32.f;
	position = sf::Vector2f(1000 * tileSize, 1000 * tileSize);
	velocity = sf::Vector2f(0, 0);
	view.reset(sf::FloatRect(0, 0, Xscale * (55 * tileSize) / 3, (55 * tileSize) / 3)); //101 tiles of size 32 pixels
	view.setCenter(position + sf::Vector2f(tileSize / 2, tileSize / 2));
	head = new HeadPart(0);
	body = new BodyPart(0);
	legL = new LegPart(0, false);
	legR = new LegPart(0, true);
	armL = new ArmPart(0, false);
	armR = new ArmPart(0, true);
}

//PLAYER CONSTRUCTOR (SPECIFIC POSITION)
Player::Player(sf::Vector2f position, float Xscale) {
	const float tileSize = 32.f;
	this->position = position;
	velocity = sf::Vector2f(0, 0);
	view.reset(sf::FloatRect(0, 0, Xscale * (55 * tileSize) / 3, (55 * tileSize) / 3)); //101 tiles of size 32 pixels
	view.setCenter(position + sf::Vector2f(tileSize / 2, tileSize / 2));
	head = new HeadPart(0);
	body = new BodyPart(0);
	legL = new LegPart(0, false);
	legR = new LegPart(0, true);
	armL = new ArmPart(0, false);
	armR = new ArmPart(0, true);;
}

//UPDATE PLAYER
void Player::update(sf::Vector2f Lstick, sf::Vector2f Rstick) {
	const float tileSize = 32.f;

	//Calc Velocity
	if (Rstick != sf::Vector2f(0, 0) && Lstick != sf::Vector2f(0, 0)) {
		float speedMod = 2;
		float angleBet = angleBetween(Lstick, Rstick);
		angleBet *= 180 / PI;
		speedMod = tileSize / 16.f * speedMod / (1 + .00485 * angleBet);
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
	view.move(velocity);

	head->update(angle);
	body->update(angle);
	armL->update(angle, velocity);
	armR->update(angle, velocity);
	legL->update(angle, velocity);
	legR->update(angle, velocity);

}

//DRAW PLAYER
void Player::draw(sf::RenderWindow &window) {
	body->draw(window, position, angle, legL, legR, armL, armR, head);
}

//Get view of player
sf::View Player::getView() {
	return view;
}