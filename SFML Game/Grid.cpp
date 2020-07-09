#include "UI.h"

using namespace GUI;

Grid::Grid(const sf::Vector2f& size) : size(size),
position({0.0f, 0.0f}), wrapContent(false)
{
	
}

Grid::Grid(void) : size({ 200.0f, 200.0f }), position({ 0.0f, 0.0f }),
wrapContent(false)
{

}

Grid::~Grid(void) 
{

}

void Grid::AddToGrid(Widget& widget) 
{
	this->widgets.push_back(&widget);
}

void Grid::UpdateWidgetPosition(void) 
{
	unsigned int* rows = 0;

	for (auto i = 0; i < this->widgets.size(); i++) 
	{
		if (i == 0) 
		{ 
			this->widgets.at(i)->SetPosition(this->position);
			this->rowMap.insert(std::make_pair(++*rows, this->widgets.at(i)->GetSize()->y));
			continue;
		}

		Widget* w = this->GetWidgetAt(i - 1);

		std::unique_ptr<sf::Vector2f> newPos = nullptr;

		if (newPos.get()->x + this->widgets.at(i)->GetSize()->x
			> this->position.x + this->size.x)
		{
			newPos = std::make_unique<sf::Vector2f>(
				new sf::Vector2f(this->position.x, this->rowMap.at(*rows)));
			this->rowMap.insert(std::make_pair(++*rows, this->widgets.at(i)->GetSize()->y));
		}
		else 
		{
			newPos = std::make_unique<sf::Vector2f>(
				new sf::Vector2f(w->position.x + w->GetSize()->x,
					w->position.y)); //use biggest y value and check if row is 1
									 //in which case you'll just set it to position.y
		}

		if (this->widgets.at(i)->GetSize()->y > this->rowMap.at(*rows))
		{
			this->rowMap[*rows] = this->widgets.at(i)->GetSize()->y;
		}

		this->widgets.at(i)->SetPosition(*newPos);
		delete w;
	}
}

Widget* Grid::GetWidgetAt(unsigned int&& i)
{
	return this->widgets.at(i);
}

void Grid::FindMaximumRowHeight(void)
{
	// TODO: insert return statement here
}

