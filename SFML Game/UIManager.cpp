#include "UI.h"

using namespace GUI;

UIManager::UIManager(sf::RenderWindow* w)
	: window(w), event(NULL)
{
}

UIManager::UIManager(void)
	: window(NULL), event(NULL)
{
}

UIManager::~UIManager(void)
{
}

void UIManager::SetWindow(sf::RenderWindow* w)
{
	this->window = w;
}

void UIManager::SetEvent(sf::Event* e)
{
	this->event = e;
}

void UIManager::Update(void)
{
	for (Widget*& w : widgets)
	{
		w->Update();
	}
}

void UIManager::Events(void)
{
	for (Widget*& w : widgets)
	{
		w->MouseEnter();
		w->MouseExit();
		w->MouseClick();
		w->MouseRelease();
	}
}

void UIManager::Draw(void)
{
	for (Widget*& w : widgets)
	{
		if(!w->IsHidden())
			w->Draw();
	}
}

void UIManager::InsertWidget(Widget* widget)
{
	widgets.push_back(widget);
}