#include "UI.h"

using PIVOT = gui::Widget::Pivot;

gui::UI::UI(sf::RenderWindow& target, sf::Event& event) : target{target}, _event{event} {
}
gui::UI::~UI() {
}

void gui::UI::Init(void) {
	
	this->uiManager.SetWindow(&this->target);
	this->uiManager.SetEvent(&this->_event);

	//BLACK BACKGROUND PANEL
	this->panel.rect.setFillColor(sf::Color::Black);
	this->panel.rect.setSize(this->target.getView().getSize());
	this->panel.rect.setOrigin(this->panel.rect.getSize().x / 2, this->panel.rect.getSize().y / 2);

	//GAME OVER
	this->tb_gameOver.SetManager(&uiManager);
	this->tb_gameOver.SetFont("Res/Fonts/VCR_OSD.ttf");
	this->tb_gameOver.SetText("Game Over");
	this->tb_gameOver.SetColor(sf::Color::White);
	this->tb_gameOver.SetSize(24);
	this->tb_gameOver.SetOrigin(PIVOT::MID_CENTER);

	this->tb_gameOver.text.setOutlineThickness(1);
	this->tb_gameOver.text.setOutlineColor(sf::Color::Red);

	//TITLE
	this->tb_gameTitle.SetManager(&uiManager);
	this->tb_gameTitle.SetFont("Res/Fonts/VCR_OSD.ttf");
	this->tb_gameTitle.SetText("TITLE");
	this->tb_gameTitle.SetColor(sf::Color::White);
	this->tb_gameTitle.SetSize(24);
	this->tb_gameTitle.SetOrigin(PIVOT::MID_CENTER);

	this->tb_gameTitle.text.setOutlineThickness(1);
	this->tb_gameTitle.text.setOutlineColor(sf::Color::Yellow);

	//MENU TEXTBTN
	this->tb_menuInstruction.SetManager(&uiManager);
	this->tb_menuInstruction.SetFont("Res/Fonts/VCR_OSD.ttf");
	this->tb_menuInstruction.SetText("PLAY");
	this->tb_menuInstruction.SetColor(sf::Color::White);
	this->tb_menuInstruction.SetSize(12);
	this->tb_menuInstruction.SetOrigin(PIVOT::MID_CENTER);

	this->tb_menuInstruction.text.setOutlineThickness(1);
	this->tb_menuInstruction.text.setOutlineColor(sf::Color::Green);

	//INIT
	this->panel.hidden = true;
	this->tb_gameOver.Hide(true);
	this->tb_gameTitle.Hide(true);
	this->tb_menuInstruction.Hide(true);

}
void gui::UI::Events(void) {
	this->uiManager.Events();
}
void gui::UI::Update(const sf::View& view) {
	this->tb_gameOver.SetPosition(view.getCenter());
	this->tb_gameTitle.SetPosition(view.getCenter());
	this->tb_menuInstruction.SetPosition({ view.getCenter().x, view.getCenter().y + 24.0f });
	this->panel.rect.setPosition(this->target.getView().getCenter());
	this->uiManager.Update();
}
void gui::UI::Draw(void) {
	if(!this->panel.hidden)
		this->target.draw(this->panel.rect);
	this->uiManager.Draw();
}