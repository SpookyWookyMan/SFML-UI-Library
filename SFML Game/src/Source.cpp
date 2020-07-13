#include <iostream>

#include "UI\UI.h"

gui::UIManager manager;

int main() 
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Game");
	sf::Event e;

	manager.SetWindow(&window);
	manager.SetEvent(&e);

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

		manager.Update();

		window.clear();

		manager.Draw();

		window.display();
	}
	return 0;
}