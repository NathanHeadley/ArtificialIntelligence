#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "FuzzyTriangle.h"

using namespace sf;

FuzzyTriangle fuzzySet[7];
std::vector<double> rules;
Font font;
Sprite car;
Texture carTexture;
Sprite drivingLine;
Texture drivingTexture;
Text actionText;
int stepX = 1;

double getDistance();

int main() {
	RenderWindow window(VideoMode(800, 600), "Car Driving");

	fuzzySet[0].setInterval(-600, -300);
	fuzzySet[0].setMiddle(-450);

	fuzzySet[1].setInterval(-400, -150);
	fuzzySet[1].setMiddle(-275);

	fuzzySet[2].setInterval(-200, 0);
	fuzzySet[2].setMiddle(-100);

	fuzzySet[3].setInterval(-25, 25);
	fuzzySet[3].setMiddle(0);

	fuzzySet[4].setInterval(0, 200);
	fuzzySet[4].setMiddle(100);

	fuzzySet[5].setInterval(150, 400);
	fuzzySet[5].setMiddle(275);

	fuzzySet[6].setInterval(300, 600);
	fuzzySet[6].setMiddle(450);
	
	font.loadFromFile("aero.ttf");

	carTexture.loadFromFile("carTexture.png");
	car.setTexture(carTexture);
	car.setPosition(389.0f, 450.0f);

	drivingTexture.loadFromFile("drivingTexture.png");
	drivingLine.setTexture(drivingTexture);
	drivingLine.setPosition(395.0f, 0.0f);

	actionText.setFont(font);
	actionText.setCharacterSize(20);
	actionText.setColor(Color::Blue);
	actionText.setPosition(100, 100);

	Vector2f forwardVector(0.0f, 0.0f);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == Keyboard::Left) {
					drivingLine.setPosition(drivingLine.getPosition().x - stepX, drivingLine.getPosition().y);
				} 
				if (event.key.code == Keyboard::Right) {
					drivingLine.setPosition(drivingLine.getPosition().x + stepX, drivingLine.getPosition().y);
				} 
				if (event.key.code == Keyboard::Num1) {
					stepX = 1;
				}
				if (event.key.code == Keyboard::Num2) {
					stepX = 2;
				}
				if (event.key.code == Keyboard::Num3) {
					stepX = 4;
				}
				if (event.key.code == Keyboard::Num4) {
					stepX = 6;
				}
				if (event.key.code == Keyboard::Num5) {
					stepX = 8;
				}
				if (event.key.code == Keyboard::Num6) {
					stepX = 10;
				}
				if (event.key.code == Keyboard::Num7) {
					stepX = 12;
				}
				if (event.key.code == Keyboard::Num8) {
					stepX = 14;
				}
				if (event.key.code == Keyboard::Num9) {
					stepX = 16;
				}
			}
		}

		rules.clear();

		for each(FuzzyTriangle fuzzyTriangle in fuzzySet) {
			double value = fuzzyTriangle.isInInterval(getDistance());
			rules.push_back(value);
		}

		double highest = rules[0];
		int highestNum = 0;
		for (int i = 0; i < rules.size(); i++) {
			if (rules[i] > highest) {
				highest = rules[i];
				highestNum = i;
			}
		}

		if (highestNum == 0) {
			// Turn Full Right
			forwardVector.x = 0.1 * cos(45 * 3.14159 / 180);
			forwardVector.y = -0.01 * sin(45 * 3.14159 / 180);
			car.setRotation(65);
			actionText.setString("Turning full right!");
		} else if (highestNum == 1) {
			// Turn Very Right
			forwardVector.x = 0.08 * cos(45 * 3.14159 / 180);
			forwardVector.y = -0.02 * sin(45 * 3.14159 / 180);
			car.setRotation(55);
			actionText.setString("Turning sharp right!");
		} else if (highestNum == 2) {
			// Turn Right
			forwardVector.x = 0.06 * cos(45 * 3.14159 / 180);
			forwardVector.y = -0.03 * sin(45 * 3.14159 / 180);
			car.setRotation(45);
			actionText.setString("Turning right!");
		} else if (highestNum == 3) {
			// Drive Straight
			forwardVector = Vector2f(0.0f, -0.04f);
			car.setRotation(0);
			actionText.setString("Driving straight!");
		} else if (highestNum == 4) {
			// Turn Left
			forwardVector.x = -0.06 * cos(45 * 3.14159 / 180);
			forwardVector.y = -0.03 * sin(45 * 3.14159 / 180);
			car.setRotation(315);
			actionText.setString("Turning left!");
		} else if (highestNum == 5) {
			// Turn Very Left
			forwardVector.x = -0.08 * cos(45 * 3.14159 / 180);
			forwardVector.y = -0.02 * sin(45 * 3.14159 / 180);
			car.setRotation(305);
			actionText.setString("Turning sharp left!");
		} else if (highestNum == 6) {
			// Turn Full Left
			forwardVector.x = -0.1 * cos(45 * 3.14159 / 180);
			forwardVector.y = -0.01 * sin(45 * 3.14159 / 180);
			car.setRotation(295);
			actionText.setString("Turning full left!");
		}

		if (car.getPosition().y + forwardVector.y > 0) {
			car.setPosition(car.getPosition() + forwardVector);
		} else {
			car.setPosition(car.getPosition().x, 556);
		}

		window.clear();
		window.draw(drivingLine);
		window.draw(car);
		window.draw(actionText);
		window.display();
	}

	return 0;
}

double getDistance() {
	int x1 = drivingLine.getPosition().x + drivingTexture.getSize().x / 2;
	int x2 = car.getPosition().x + carTexture.getSize().x / 2;
	int distance = sqrt((x1 - x2) * (x1 - x2));
	if (x1 > x2) {
		return -distance;
	} else {
		return distance;
	}
}