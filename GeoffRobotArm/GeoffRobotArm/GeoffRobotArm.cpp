//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 



////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	int height = 900;
	int width = 700;
	sf::RenderWindow window(sf::VideoMode(height, width, 32), "SFML First Program");
	window.setFramerateLimit(60);

	
	const int size = 5;
	//create both arms the same
	sf::VertexArray upperArm(sf::LinesStrip, size);
	sf::VertexArray foreArm(sf::LinesStrip, size);

	//points for the arms 
	sf::Vector2f ArmPoints[size];
	ArmPoints[0] = sf::Vector2f(0, 55);
	ArmPoints[1] = sf::Vector2f(180, 55);
	ArmPoints[2] = sf::Vector2f(180, -30);
	ArmPoints[3] = sf::Vector2f(0, -30);
	ArmPoints[4] = ArmPoints[0];

	//set rotations of both arms
	float fullRotation = 0.0;
	float vel = 1.5;
	float foreRotation = 0.0;


	//set arm positions
	sf::Vector2f upperArmPos(150,300);
	sf::Vector2f foreArmPos(180, 0);

	//create claw 1
	const int clawSize = 7;
	sf::VertexArray claw1(sf::LinesStrip, clawSize);

	sf::Vector2f claw1Points[clawSize];
	claw1Points[0] = sf::Vector2f(0, 0);
	claw1Points[1] = sf::Vector2f(0, -10);
	claw1Points[2] = sf::Vector2f(80, -10);
	claw1Points[3] = sf::Vector2f(80, 40);
	claw1Points[4] = sf::Vector2f(70, 30);
	claw1Points[5] = sf::Vector2f(70, 10);
	claw1Points[6] = claw1Points[0];

	sf::Vector2f claw1Pos(180, -20);
	float claw1Rotation = 0.0;

	//create claw 2
	sf::VertexArray claw2(sf::LinesStrip, clawSize);

	sf::Vector2f claw2Points[clawSize];
	claw2Points[0] = sf::Vector2f(0, 0);
	claw2Points[1] = sf::Vector2f(0, 10);
	claw2Points[2] = sf::Vector2f(80, 10);
	claw2Points[3] = sf::Vector2f(80, -40);
	claw2Points[4] = sf::Vector2f(70, -30);
	claw2Points[5] = sf::Vector2f(70, -10);
	claw2Points[6] = claw2Points[0];

	sf::Vector2f claw2Pos(180, 45);
	float claw2Rotation = 0.0;

	//begin frame loop
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S))
			{
				if (fullRotation < 90)
				{
					fullRotation += vel;
				}
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A))
			{
				if (fullRotation >= -90)
				{
					fullRotation -= vel;
				}
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::X))
			{
				if (foreRotation <= 90)
				{
					foreRotation += vel;
				}
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Z))
			{
				if (foreRotation >= -90)
				{
					foreRotation -= vel;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
			{
				if (claw1Rotation >= -90 && claw2Rotation <= 90)
				{
					claw1Rotation -= vel;
					claw2Rotation += vel;
				}
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
			{
				if (claw1Rotation <= 0 && claw2Rotation >= 0)
				{
					claw1Rotation += vel;
					claw2Rotation -= vel;
				}
				
			}	
		}
			//transforms for upper arm
			sf::Transform TU;
			TU.translate(upperArmPos);

			sf::Transform RU;
			RU.rotate(fullRotation);

			sf::Transform MU = TU * RU;


			for (int i = 0; i < size; i++) {
				upperArm[i].position = MU.transformPoint(ArmPoints[i]);
				upperArm[i].color = sf::Color::Red;
			}

			//Transforms for forearm
			sf::Transform TF;
			TF.translate(foreArmPos);

			sf::Transform RF;
			RF.rotate(foreRotation);

			sf::Transform MF = TU * RU * TF * RF;

			for (int i = 0; i < size; i++) {
				foreArm[i].position = MF.transformPoint(ArmPoints[i]);
				foreArm[i].color = sf::Color::Blue;
			}

			//transforms for claw1
			sf::Transform TC1;
			TC1.translate(claw1Pos);

			sf::Transform RC1;
			RC1.rotate(claw1Rotation);

			sf::Transform MC1;
			MC1 = TU * RU * TF * RF * TC1 * RC1;

			for (int i = 0;i < clawSize;i++)
			{
				claw1[i].position = MC1.transformPoint(claw1Points[i]);
				claw1[i].color = sf::Color::Green;
			}

			//transforms for claw2
			sf::Transform TC2;
			TC2.translate(claw2Pos);

			sf::Transform RC2;
			RC2.rotate(claw2Rotation);

			sf::Transform MC2;
			MC2 = TU * RU * TF * RF * TC2 * RC2;

			for (int i = 0;i < clawSize;i++)
			{
				claw2[i].position = MC2.transformPoint(claw2Points[i]);
				claw2[i].color = sf::Color::Green;
			}


			//prepare frame
			window.clear();

			window.draw(upperArm);
			window.draw(foreArm);
			window.draw(claw1);
			window.draw(claw2);

			// Finally, display rendered frame on screen 
			window.display();
		} //loop back for next frame


	
		
	return EXIT_SUCCESS;
}
