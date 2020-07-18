#include "Game/Game.h"

int main() 
{
	Game game;
	game.Run();
	//manager.SetWindow(&window);
	//manager.SetEvent(&e);
	//
	//Map map("Res/Tileset/caves.png");
	//map.Init();
	//Player p;
	//p.player.
	//
	//Object o;
	//sf::Texture t;
	//t.loadFromFile("Res/Textures/default.png");
	//o.sprite.setTexture(t);
	//o.sprite.setScale({10.0f, 6.0f});
	//o.SetPosition({ 100.0f, 650.0f });
	//o.BindCollisionRectToObject();
	//
	//gui::Slider slider;
	//slider.SetManager(&manager);
	//
	//gui::InputTextField itf("Text", "Res/Fonts/VCR_OSD.ttf");
	//itf.SetPosition({ 500.0f, 500.0f });
	//itf.SetManager(&manager);
	//
	//gui::Bar bar;
	//bar.SetPosition({100, 500});
	//bar.bBarDelay = 0;
	//bar.SetManager(&manager);
	//while (window.isOpen()) 
	//{
	//	while (window.pollEvent(e)) 
	//	{
	//		manager.Events();
	//
	//		p.Events(e);
	//
	//		if (e.type == sf::Event::Closed)
	//			window.close();
	//		if (e.type == sf::Event::KeyReleased) 
	//		{
	//			if (e.key.code == sf::Keyboard::Space) 
	//			{
	//			}
	//			if (e.key.code == sf::Keyboard::Escape)
	//				return 0;
	//		}
	//	}
	//
	//	//map.Update();
	//	p.Update();
	//	o.Update();
	//	
	//	p.isGrounded = p.collisionRect.GetCollisionDirection(o.collisionRect) == CollisionRect::CollisionDirection::TOP;
	//	p.canMoveRight = !(p.collisionRect.GetCollisionDirection(o.collisionRect) == CollisionRect::CollisionDirection::LEFT);
	//	p.canMoveLeft = !(p.collisionRect.GetCollisionDirection(o.collisionRect) == CollisionRect::CollisionDirection::RIGHT);
	//
	//	manager.Update();
	//
	//	window.clear();
	//
	//	p.Draw(window);
	//	o.Draw(window);
	//	//map.Draw(window);
	//	manager.Draw();
	//
	//	window.display();
	//}
	return 0;
}