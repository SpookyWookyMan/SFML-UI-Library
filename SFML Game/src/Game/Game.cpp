#include "Game.h"

Game::Game(void) {
}
Game::~Game() {

}

sf::RenderWindow window(sf::VideoMode(0x3E8, 0x3E8), "SFML Game", sf::Style::Default);
sf::Event _event;

gui::UI ui(window, _event);

Camera camera(window, { 15.0f, 500.0f }, {200.0f, 200.0f});

Player player;
Map map("Res/Tileset/caves.png");

void Game::Init(void) {
	srand(time(NULL));

	//test
	sf::Image icon;
	icon.loadFromFile("Res/Textures/default.png");
	window.setIcon(32, 32, icon.getPixelsPtr());
	//

	//window.setFramerateLimit(60);

	player.Init();
	map.Init(&player);
	ui.Init();
}
void Game::Events(void) {
	while (window.pollEvent(_event)) {
		player.Events(_event);
		ui.Events();
		if (_event.type == sf::Event::Closed)
			window.close();
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::Tab)
				this->paused = !this->paused;
		}
		if (_event.type == sf::Event::KeyReleased) {
			if (_event.key.code == sf::Keyboard::Escape)
				window.close();
		}
	}
}
void Game::UpdateDeltaTime(void) {
	this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}
void Game::Update(void) {
	this->UpdateDeltaTime();
	
	player.Update(this->deltaTime);
	camera.MoveToTarget(player.position, 4.0f, this->deltaTime);

	if (player.position.y > camera.position.y + camera.size.y / 2) {
		player.canMoveLeft = player.canMoveRight = false;
		ui.tb_gameOver.Hide(false);
	}

	map.Update(this->deltaTime);
	ui.Update(window.getView());
}
void Game::Draw(void) {
	player.Draw(window);
	map.Draw(window);
	ui.Draw();
}
void Game::Run(void) {
	this->Init();
	while (window.isOpen()) {
		this->Events();
		this->Update();
		window.clear();
		this->Draw();
		window.display();
	}
}