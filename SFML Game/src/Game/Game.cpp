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

	player.Init();
	map.Init(&player);
	ui.Init();

	//ui stuff
	ui.tb_menuInstruction.MouseEnterFunc = [&] {
		ui.tb_menuInstruction.text.setOutlineThickness(1);
	};
	ui.tb_menuInstruction.MouseExitFunc = [&] {
		ui.tb_menuInstruction.text.setOutlineThickness(0);
	};
	ui.tb_menuInstruction.ClickFunc = [&] {
		this->state = States::NORMAL;
	};

	this->state = States::MENU;
	ui.tb_gameTitle.Hide(false);
	ui.tb_menuInstruction.Hide(false);
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
			if (_event.key.code == sf::Keyboard::Space && player.gameOver) {
				player.Restart();
				camera.SetCameraPosition(player.position);

				map.chunkManager.generatedChunks.clear();
				map.Init(&player);
				
				ui.panel.hidden = true;
				ui.tb_gameOver.Hide(true);

				player.gameOver = false;
			}
		}
		if (_event.type == sf::Event::KeyReleased) {
			if (_event.key.code == sf::Keyboard::Escape)
				window.close();
		}
	}
}
void Game::UpdateDeltaTime(void) {
	//this->deltaTime = !paused ? this->deltaTimeClock.restart().asSeconds() : 0.0f;
	this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}
void Game::Update(void) {
	this->UpdateDeltaTime();
	
	if (this->state != States::MENU) {
		player.Update(this->deltaTime);
		camera.MoveToTarget(player.position, 4.0f, this->deltaTime);

		if (player.position.y > camera.position.y + camera.size.y / 2) {
			player.canMoveLeft = player.canMoveRight = false;
			ui.panel.hidden = false;
			ui.tb_gameOver.Hide(false);
			player.gameOver = true;
		}
		map.Update(this->deltaTime);
	} else {

	}
	ui.Update(window.getView());
}
void Game::Draw(void) {
	if (this->state != States::MENU) {
		player.Draw(window);
		map.Draw(window);
	}
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