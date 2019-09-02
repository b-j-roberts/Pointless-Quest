#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "../Include/Functions.h"//possibly remove this and add functions?
#include <SFML/Graphics/View.hpp>
#include <fstream>

class HeadPart {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f connector;
	public:
		HeadPart(int headNum);
//		~HeadPart();
		void update(float angle);
		void draw(sf::RenderWindow &window, sf::Vector2f position);
};

class LegPart {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f topLeg, botLeg;
		int animationPos, holdFrames, offset;
		std::vector<int> animationSequence;
	public:
		LegPart(int legNum, bool right);
//		~LegPart();
		void update(float angle, sf::Vector2f velocity);
		void draw(sf::RenderWindow &window, sf::Vector2f position);
};

class ArmPart {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f topArm, botArm;
	bool forward;
	int rotation;
public:
	ArmPart(int armNum, bool right);
//	~ArmPart();
	void update(float angle, sf::Vector2f velocity);
	void draw(sf::RenderWindow &window, sf::Vector2f position);
};

class BodyPart {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f connectorArmL, connectorArmR;
	sf::Vector2f connectorLegL, connectorLegR;
	sf::Vector2f connectorArmB, connectorArmF;
	sf::Vector2f connectorLegB, connectorLegF;
	sf::Vector2f connectorHead;
public:
	BodyPart(int bodyNum);
//	~BodyPart();
	void update(float angle);
	void draw(sf::RenderWindow &window, sf::Vector2f position, float angle, LegPart * legL, LegPart * legR, ArmPart * armL, ArmPart * armR, HeadPart * head);

};

class Player {
	private:
		HeadPart *head;
		BodyPart *body;
		LegPart *legL, *legR;
		ArmPart *armL, *armR;
		sf::Vector2f position, velocity;
		float angle;
		sf::View view;
	public:
		Player(float Xscale);
		Player(sf::Vector2f position, float Xscale);
		void update(sf::Vector2f Lstick, sf::Vector2f Rstick);
		void draw(sf::RenderWindow &window);
		sf::View getView();
};

#endif