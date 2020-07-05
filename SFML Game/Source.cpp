#include <iostream>

#include "UI.h"

GUI::UIManager manager;

int main() 
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "UI");
	sf::Event e;

	manager.SetWindow(&window);
	manager.SetEvent(&e);

	GUI::InputTextField itf("Text", "Res/Fonts/VCR_OSD.ttf");
	itf.SetManager(&manager);

	//GUI::Bar bar;
	//bar.SetPosition({100, 500});
	//bar.SetManager(&manager);

	//GUI::TextBox textBox("Res/Fonts/VCR_OSD.ttf");
	//textBox.SetSize(150);
	//textBox.SetOrigin(GUI::Widget::Pivot::MID_CENTER);
	//textBox.SetPosition({500, 500});
	//
	//textBox.SetManager(&manager);
	
	//GUI::Button button;
	//
	//button.LoadTextures("Res/Textures/normal.png", "Res/Textures/highlight.png", "Res/Textures/clicked.png");
	//
	//button.SetTexture(button.normal);
	//button.SetOrigin(GUI::Widget::Pivot::MID_CENTER, new sf::Vector2f(-5.0f, -45.0f));
	//button.SetPosition({500.0f, 500.0f});
	//
	//button.SetTextFont("Res/Fonts/VCR_OSD.ttf");
	//button.SetTextColor(sf::Color::White);
	//button.SetTextOrigin(GUI::Widget::Pivot::MID_CENTER);
	//
	//button.MouseEnterFunc = [&] { button.SetTexture(button.highlight); };
	//button.MouseExitFunc = [&] { button.SetTexture(button.normal); };
	//button.ClickFunc = [&] { button.SetTexture(button.clicked); printf("clicked\n"); };
	//button.ReleaseFunc = [&] { printf("released\n"); };
	//
	//button.SetManager(&manager);

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