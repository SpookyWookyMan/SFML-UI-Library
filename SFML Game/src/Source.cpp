#include <iostream>

#include "UI\UI.h"
#include "Entities/Object.h"

gui::UIManager manager;

int main() 
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Game");
	sf::Event e;

	manager.SetWindow(&window);
	manager.SetEvent(&e);

	Object o, o2;
	sf::RectangleShape r({75.0f, 75.0f});
	sf::RectangleShape r2({200.0f, 200.0f});

	r.setFillColor(sf::Color::Green);
	r2.setFillColor(sf::Color::White);

	o.collisionRect.size = r.getSize();

	o2.SetPosition({500.0f, 500.0f});
	o2.collisionRect.size = r2.getSize();
	r2.setPosition(o2.position);

	//gui::Slider slider;
	//slider.SetManager(&manager);

	//gui::InputTextField itf("Text", "Res/Fonts/VCR_OSD.ttf");
	//itf.SetPosition({ 500.0f, 500.0f });
	//itf.SetManager(&manager);

	//gui::Bar bar;
	//bar.SetPosition({100, 500});
	//bar.bBarDelay = 0;
	//bar.SetManager(&manager);

	while (window.isOpen()) 
	{
		while (window.pollEvent(e)) 
		{
			manager.Events();

			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::KeyReleased) 
			{
				if (e.key.code == sf::Keyboard::Space) 
				{
					//bar.ChangeValueBy(-25.0f);
				}
			}
		}

		o.SetPosition({ (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y });
		r.setPosition(o.position);

		if (o.collisionRect.GetCollisionDirection(o2.collisionRect) == coll::CollisionRect::CollisionDirection::NONE)
			printf("No collision\n");
		else if(o.collisionRect.GetCollisionDirection(o2.collisionRect) == coll::CollisionRect::CollisionDirection::RIGHT)
			printf("Collision from the right\n");
		else if(o.collisionRect.GetCollisionDirection(o2.collisionRect) == coll::CollisionRect::CollisionDirection::LEFT)
			printf("Collision from the left\n");
		else if (o.collisionRect.GetCollisionDirection(o2.collisionRect) == coll::CollisionRect::CollisionDirection::TOP)
			printf("Collision from the top\n");
		else if (o.collisionRect.GetCollisionDirection(o2.collisionRect) == coll::CollisionRect::CollisionDirection::BOTTOM)
			printf("Collision from the bottom\n");

		manager.Update();

		window.clear();

		window.draw(r);
		window.draw(r2);

		manager.Draw();

		window.display();
	}
	return 0;
}