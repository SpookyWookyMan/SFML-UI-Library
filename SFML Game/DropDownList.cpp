#include "UI.h"

using namespace GUI;

DropDownList::DropDownList(const sf::Vector2f& size)
{
	this->SetSize(size);
	this->optionDisplay.setFillColor(sf::Color::White);
	
	this->optionColor = sf::Color::White;
	this->optionHighlightColor = sf::Color::Blue;
}

DropDownList::DropDownList(void)
{
	this->SetSize({200.0f, 40.0f});
	this->optionDisplay.setFillColor(sf::Color::White);

	this->optionColor = sf::Color::White;
	this->optionHighlightColor = sf::Color::Blue;
}

DropDownList::~DropDownList(void) 
{
}

void DropDownList::SetPosition(const sf::Vector2f& pos)
{
	this->position = position;
	this->optionDisplay.setPosition(this->position);
	this->UpdateGlobalBounds();
}

void DropDownList::SetOrigin(const Pivot& pivot)
{
	this->optionDisplay.setOrigin(this->SwitchPivot(pivot, this->GetSize()));
}

void DropDownList::SetOrigin(const Pivot& pivot, sf::Vector2f* offset)
{
	this->optionDisplay.setOrigin(this->SwitchPivotOffset(pivot, this->GetSize(), *offset));
}

void DropDownList::SetSize(const sf::Vector2f& size)
{
	this->optionDisplay.setSize(size);
	this->optionDim.x = size.x;
	this->optionDim.y = 0.9f * size.y;
}

void DropDownList::SetFont(const char* path)
{
	if (!this->optionFont.loadFromFile(path))
		std::cout << "FAILURE: Couldn't load font from: " << path << "\n";
}

void DropDownList::SetFont(const sf::Font& font)
{
	this->optionFont = font;
}

sf::Vector2f* DropDownList::GetSize(void)
{
	sf::Vector2f* vec = new sf::Vector2f(this->optionDisplay.getSize().x, this->optionDisplay.getSize().y);

	return vec;

	delete vec;
}

const sf::Vector2f& DropDownList::GetOrigin(void) const
{
	return this->optionDisplay.getOrigin();
}

void DropDownList::AddOption(const char* optionString)
{
	Option* option = new Option(optionString);
	
	option->optionRect.setSize(this->optionDim);

	this->list.push_back(option);
}

void DropDownList::MouseClick(void)
{
	if (IsMouseOver())
	{
		if (this->manager->event->type == sf::Event::MouseButtonPressed)
		{
			if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left)
			{
				mouseHeld = true;
				this->showOptions = !this->showOptions;
				ClickFunc();
			}
		}
	}
	if (showOptions)
	{
		std::unique_ptr<sf::Vector2f> mousePos =
			std::make_unique<sf::Vector2f>(sf::Mouse::getPosition(*this->manager->window));

		for (auto o : this->list)
		{
			if (o->optionRect.getGlobalBounds().contains(*mousePos))
			{
				o->optionRect.setFillColor(this->optionHighlightColor);
				
				if (this->manager->event->mouseButton.button == sf::Mouse::Button::Left)
				{
					this->selectedOption = o;
					this->UpdateDisplay();
				}
			}
			else
			{
				o->optionRect.setFillColor(this->optionColor);
			}
		}
	}
}

void DropDownList::MouseClick(const sf::Mouse::Button& mb)
{
	if (IsMouseOver())
	{
		if (this->manager->event->type == sf::Event::MouseButtonPressed)
		{
			if (this->manager->event->mouseButton.button == mb)
			{
				mouseHeld = true;
				this->showOptions = !this->showOptions;
				ClickFunc();
			}
		}
	}
	if (showOptions)
	{
		std::unique_ptr<sf::Vector2f> mousePos =
			std::make_unique<sf::Vector2f>(sf::Mouse::getPosition(*this->manager->window));

		for (auto o : this->list)
		{
			if (o->optionRect.getGlobalBounds().contains(*mousePos))
			{
				o->optionRect.setFillColor(this->optionHighlightColor);

				if (this->manager->event->mouseButton.button == mb)
				{
					this->selectedOption = o;
					this->UpdateDisplay();
				}
			}
			else 
			{
				o->optionRect.setFillColor(this->optionColor);
			}
		}
	}
}

void DropDownList::UpdateGlobalBounds(void)
{
	this->globalBounds = this->optionDisplay.getGlobalBounds();
}

void DropDownList::Draw(void)
{
	if(showOptions)
		for (auto o : list) 
		{
			this->manager->window->draw(o->optionRect);
			this->manager->window->draw(o->text);
		}

	this->manager->window->draw(this->optionDisplay);
	if (!optionSelected) this->manager->window->draw(displayLabel);
}

void DropDownList::UpdateOptionBoxPosition(void)
{
	sf::Vector2f* pos = new sf::Vector2f(this->optionDisplay.getPosition());

	for (auto i = 0; i < sizeof(this->list) / sizeof(Option); i++)
	{
		sf::Vector2f* vec = nullptr;

		if (i == 0) 
		{
		    vec = new sf::Vector2f(pos->x, pos->y + this->GetSize()->y);
		}
		else 
		{
			vec = new sf::Vector2f(pos->x, pos->y + this->list.at(i)->optionRect.getSize().y * i);
		}
		
		this->list.at(i)->optionRect.setPosition(*vec);
		this->list.at(i)->text.setOrigin(SwitchPivot(Widget::Pivot::MID_LEFT, 
			new sf::Vector2f(this->list.at(i)->text.getLocalBounds().width, this->list.at(i)->text.getLocalBounds().height)));
		this->list.at(i)->text.setPosition({vec->x, vec->y + this->list.at(i)->optionRect.getSize().y / 2});

		delete vec;
	}

	delete pos;
}

void DropDownList::UpdateDisplay(void)
{
	this->displayLabel.setString(this->selectedOption->textString);
}