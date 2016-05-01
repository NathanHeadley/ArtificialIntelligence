#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "FuzzyTriangle.h"

using namespace sf;

FuzzyTriangle distanceSet[5];
FuzzyTriangle velocitySet[5];
std::vector<double> distanceRules;
std::vector<double> velocityRules;
Font font;
Sprite car;
Texture carTexture;
Sprite drivingLine;
Texture drivingTexture;
Text actionText;
float oldPosition = 0.0f, newPosition = 0.0f;
int stepX = 1;

double getDistance();

int main() {
	RenderWindow window(VideoMode(800, 600), "Car Driving");

	#pragma region distanceSet
	distanceSet[0].setInterval(-6, -3);
	distanceSet[0].setMiddle(-4.5);

	distanceSet[1].setInterval(-3.075, -0.075);
	distanceSet[1].setMiddle(-1.575);

	distanceSet[2].setInterval(-0.1, 0.1);
	distanceSet[2].setMiddle(0);

	distanceSet[3].setInterval(0.075, 3.075);
	distanceSet[3].setMiddle(1.575);

	distanceSet[4].setInterval(3, 6);
	distanceSet[4].setMiddle(4.5);
	#pragma endregion distanceSet

	#pragma region velocitySet
	velocitySet[0].setInterval(-1, -0.5);
	velocitySet[0].setMiddle(-0.75);

	velocitySet[1].setInterval(-0.5, 0);
	velocitySet[1].setMiddle(-0.25);

	velocitySet[2].setInterval(-0.25, 0.25);
	velocitySet[2].setMiddle(0);
	
	velocitySet[3].setInterval(0, 0.5);
	velocitySet[3].setMiddle(0.25);

	velocitySet[4].setInterval(0.5, 1);
	velocitySet[4].setMiddle(0.75);
	#pragma endregion velocitySet

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
					stepX = 30;
				}
			}
		}

		car.setPosition(car.getPosition() + forwardVector);
		float ROChange = car.getPosition().x - oldPosition;

		distanceRules.clear();
		velocityRules.clear();

#pragma region distanceValues
		for each(FuzzyTriangle fuzzyTriangle in distanceSet) {
			double value = fuzzyTriangle.isInInterval(getDistance()/100);
			distanceRules.push_back(value);
		}

		double highest = distanceRules[0];
		int distance = -2;
		for (int i = 0; i < distanceRules.size(); i++) {
			if (distanceRules[i] > highest) {
				highest = distanceRules[i];
				distance = i - 2;
			}
		}
#pragma endregion distanceValues

#pragma region velocityValues
		for each(FuzzyTriangle fuzzyTriangle in velocitySet) {
			double value = fuzzyTriangle.isInInterval(ROChange*10);
			velocityRules.push_back(value);
		}

		highest = velocityRules[0];
		int velocity = 0;
		for (int i = 0; i < velocityRules.size(); i++) {
			if (velocityRules[i] > highest) {
				highest = velocityRules[i];
				velocity = i;
			}
		}
#pragma endregion velocityValues

		if (distance == -2 && velocity == 0) {
			forwardVector.x += 0.001;
			actionText.setString("Turning sharp right! 0");
		} else if (distance == -2 && velocity == 1) {
			forwardVector.x += 0.025;
			actionText.setString("Turning sharp right! 1");
		} else if (distance == -2 && velocity == 2) {
			forwardVector.x += 0.05;
			actionText.setString("Turning sharp right! 2");
		} else if (distance == -2 && velocity == 3) {
			forwardVector.x += 0.075;
			actionText.setString("Turning sharp right! 3");
		} else if (distance == -2 && velocity == 4) {
			forwardVector.x += 0.1;
			actionText.setString("Turning sharp right! 4");


		} else if (distance == -1 && velocity == 0) {
			forwardVector.x += 0.001;
			actionText.setString("Turning right! 0");
		} else if (distance == -1 && velocity == 1) {
			forwardVector.x += 0.025;
			actionText.setString("Turning right! 1");
		} else if (distance == -1 && velocity == 2) {
			forwardVector.x += 0.05;
			actionText.setString("Turning right! 2");
		} else if (distance == -1 && velocity == 3) {
			forwardVector.x += 0.075;
			actionText.setString("Turning right! 3");
		} else if (distance == -1 && velocity == 4) {
			forwardVector.x += 0.1;
			actionText.setString("Turning right! 4");


		} else if (distance == 0 && velocity == 0) {
			forwardVector.x = 0;
			actionText.setString("Straight! 0");
		} else if (distance == 0 && velocity == 1) {
			forwardVector.x = 0;
			actionText.setString("Straight! 1");
		} else if (distance == 0 && velocity == 2) {
			forwardVector.x = 0;
			actionText.setString("Straight! 2");
		} else if (distance == 0 && velocity == 3) {
			forwardVector.x = 0;
			actionText.setString("Straight! 3");
		} else if (distance == 0 && velocity == 4) {
			forwardVector.x = 0;
			actionText.setString("Straight! 4");


		} else if (distance == 1 && velocity == 0) {
			forwardVector.x -= 0.001;
			actionText.setString("Turning left! 0");
		} else if (distance == 1 && velocity == 1) {
			forwardVector.x -= 0.025;
			actionText.setString("Turning left! 1");
		} else if (distance == 1 && velocity == 2) {
			forwardVector.x -= 0.05;
			actionText.setString("Turning left! 2");
		} else if (distance == 1 && velocity == 3) {
			forwardVector.x -= 0.075;
			actionText.setString("Turning left! 3");
		} else if (distance == 1 && velocity == 4) {
			forwardVector.x -= 0.1;
			actionText.setString("Turning left! 4");


		} else if (distance == 2 && velocity == 0) {
			forwardVector.x -= 0.001;
			actionText.setString("Turning left! 0");
		} else if (distance == 2 && velocity == 1) {
			forwardVector.x -= 0.025;
			actionText.setString("Turning left! 1");
		} else if (distance == 2 && velocity == 2) {
			forwardVector.x -= 0.05;
			actionText.setString("Turning left! 2");
		} else if (distance == 2 && velocity == 3) {
			forwardVector.x -= 0.075;
			actionText.setString("Turning left! 3");
		} else if (distance == 2 && velocity == 4) {
			forwardVector.x -= 0.1;
			actionText.setString("Turning left! 4");
		}

		oldPosition = car.getPosition().x;

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