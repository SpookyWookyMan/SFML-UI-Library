#include "UI.h"

using PIVOT = gui::Widget::Pivot;

gui::UI::UI(sf::RenderWindow& target, sf::Event& event) : target{target}, _event{event} {
	
}
gui::UI::~UI() {
}
void gui::UI::Init(void) {
	
	this->uiManager.SetWindow(&this->target);
	this->uiManager.SetEvent(&this->_event);

	this->tb_gameOver.SetManager(&uiManager);
	this->tb_gameOver.SetFont("Res/Fonts/VCR_OSD.ttf");
	this->tb_gameOver.SetText("Game Over");
	this->tb_gameOver.SetColor(sf::Color::White);
	this->tb_gameOver.SetSize(24);
	this->tb_gameOver.SetOrigin(PIVOT::MID_CENTER);

	this->tb_gameOver.text.setOutlineThickness(1);
	this->tb_gameOver.text.setOutlineColor(sf::Color::Red);

	this->tb_gameOver.Hide(true);

}
void gui::UI::Events(void) {
	this->uiManager.Events();
}
void gui::UI::Update(const sf::View& view) {
	this->tb_gameOver.SetPosition(view.getCenter());
	this->uiManager.Update();
}
void gui::UI::Draw(void) {
	this->uiManager.Draw();
}