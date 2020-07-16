#include "Game.h"

Game::Game(void) 
{

}

Game::~Game()
{
}

void Game::Init(void)
{
}

void Game::Events(void)
{
	while (this->window->pollEvent(this->event)) 
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::UpdateDeltaTime(void)
{
	this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}

void Game::Update(void)
{

}

void Game::Draw(void)
{
	
}

void Game::Run(void)
{
	while (this->window->isOpen()) 
	{
		this->Update();
		this->window->clear();
		this->Draw();
		this->window->display();
	}
}