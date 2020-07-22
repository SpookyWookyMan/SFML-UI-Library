#include "UI.h"

using PIVOT = gui::Widget::Pivot;

gui::UIManager uiManager;

gui::TextBox tb_gameOver;

gui::UI::UI(sf::RenderWindow& target, sf::Event& event) : target{target}, _event{event} {
	uiManager.SetWindow(&this->target);
	uiManager.SetEvent(&this->_event);
}
gui::UI::~UI() {
}
void gui::UI::Init(void) {
	
	tb_gameOver.SetManager(&uiManager);
	tb_gameOver.SetFont("Res/Fonts/VCR_OSD.ttf");
	tb_gameOver.SetText("Game Over");
	tb_gameOver.SetColor(sf::Color::White);
	tb_gameOver.SetOrigin(PIVOT::MID_CENTER);
	tb_gameOver.SetSize(12);

	tb_gameOver.text.setOutlineThickness(1);
	tb_gameOver.text.setOutlineColor(sf::Color::Red);
}
void gui::UI::Events(void) {
	uiManager.Events();
}
void gui::UI::Update(const sf::View& view) {
	tb_gameOver.SetPosition(view.getCenter());
	uiManager.Update();
}
void gui::UI::Draw(void) {
	uiManager.Draw();
}