#pragma once

#include <iostream>
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

//TODO:
//	INPUT FIELD:
//		-Fix text typing. (MAJOR)
//		-Draw the box itself. (MAJOR)

namespace GUI
{

	class Widget;
	class UIManager
	{
	public:
		sf::RenderWindow* window;
		sf::Event* event;

		std::vector<Widget*> widgets;

		UIManager(sf::RenderWindow* w);
		UIManager(void);
		virtual ~UIManager(void);

		void SetWindow(sf::RenderWindow* w);
		void SetEvent(sf::Event* e);

		void Update(void);
		void Events(void);
		void Draw(void);

		void InsertWidget(Widget* widget);

	};

	class Widget
	{
	public:

		UIManager* manager;

		enum class Pivot
		{
			TOP_LEFT,
			TOP_CENTER,
			TOP_RIGHT,
			MID_LEFT,
			MID_CENTER,
			MID_RIGHT,
			BOT_LEFT,
			BOT_CENTER,
			BOT_RIGHT
		};

		sf::Vector2f position;

		bool mouseHeld = false;

		std::function<void(void)> MouseEnterFunc = []{};
		std::function<void(void)> MouseExitFunc = []{};
		std::function<void(void)> ClickFunc = []{};
		std::function<void(void)> ReleaseFunc = []{};

		std::function<void(void)> UpdateFunc = []{};

		virtual void SetManager(UIManager* m = NULL);
		virtual void SetPosition(const sf::Vector2f& pos) = 0;
		virtual void SetActive(const bool& active);
		virtual void SetOrigin(const Pivot& pivot) = 0;
		virtual void SetOrigin(const Pivot& pivot, sf::Vector2f* offset) = 0;
		virtual void UpdateGlobalBounds(void) = 0;

		virtual sf::Vector2f* GetSize(void) = 0;
		virtual const sf::Vector2f& GetOrigin(void) const = 0;

		virtual const bool& IsActive(void) const;
		virtual const bool& IsHidden(void) const;
		inline bool IsMouseOver(void);

		virtual void Hide(const bool& hide);
		virtual void MouseEnter(void);
		virtual void MouseExit(void);
		virtual void MouseClick(void);
		virtual void MouseClick(const sf::Mouse::Button& mb);
		virtual void MouseRelease(void);
		virtual void MouseRelease(const sf::Mouse::Button& mb);

		virtual void Update(void);
		virtual void Draw(void) = 0;

	protected:

		sf::FloatRect globalBounds;

		bool active = true;
		bool hidden = false;

		virtual sf::Vector2f SwitchPivot(const Pivot& pivot, sf::Vector2f* v);
		virtual sf::Vector2f SwitchPivotOffset(const Pivot& pivot, sf::Vector2f* v, const sf::Vector2f& offset);

	};

	class Button : public Widget
	{
	public:

		sf::Sprite sprite;

		sf::Texture normal;
		sf::Texture highlight;
		sf::Texture clicked;

		sf::Text text;

		enum class TextureType
		{
			NORMAL,
			HIGHLIGHT,
			CLICKED
		};

		Button(const sf::Texture& normTex);
		Button(void);
		virtual ~Button(void);

		void SetPosition(const sf::Vector2f& pos) override;
		void SetOrigin(const Pivot& pivot) override;
		void SetOrigin(const Pivot& pivot, sf::Vector2f* offset) override;
		void SetTexture(const sf::Texture& texture);

		void SetText(const char* str);
		void SetTextSize(const unsigned int&& size);
		void SetTextFont(const char* path);
		void SetTextFont(const sf::Font& font);
		void SetTextOrigin(const Pivot& pivot);
		void SetTextOrigin(const Pivot& pivot, sf::Vector2f* offset);
		void SetTextColor(const sf::Color& clr);

		sf::Vector2f* GetSize(void) override;
		const sf::Vector2f& GetOrigin(void) const override;

		void UpdateGlobalBounds(void) override;
		void LoadTexture(const std::string& path, TextureType ttype);
		void LoadTextures(const char* path, const char* _path, const char* __path);
		void HideText(const bool& b);

		void Draw(void) override;

	private:

		sf::Font textFont;

		bool hideText = false;

		void UpdateTextPosition(void);

	};

	class TextBox : public Widget
	{
	public:

		sf::Text text;
		sf::Font font;

		TextBox(const char* path, const char* str);
		TextBox(const char* path);
		TextBox(const sf::Font& font, const char* str);
		TextBox(const sf::Font& font);
		virtual ~TextBox(void);

		void SetPosition(const sf::Vector2f& pos) override;
		void SetOrigin(const Pivot& pivot) override;
		void SetOrigin(const Pivot& pivot, sf::Vector2f* offset) override;
		void SetText(const char* str);
		void SetFont(const sf::Font& font);
		void SetFont(const char* path);
		void SetColor(const sf::Color& color);
		void SetSize(const unsigned int&& size);

		sf::Vector2f* GetSize(void) override;
		const sf::Vector2f& GetOrigin(void) const override;

		void UpdateGlobalBounds(void) override;

		void Draw(void) override;

	};

	class Bar : public Widget 
	{
	public:
		
		float maxValue;
		float minValue;
		float currentValue;

		int bBarDelay;
		int bBarDecraseInterval;
		float bBarDecreaseAmount;

		bool showBackBar = true;

		sf::RectangleShape valueBar;
		sf::RectangleShape backgroundBar;
		sf::RectangleShape background;

		Bar(const sf::Vector2f& dim, const float& maxValue, const float& minValue);
		Bar(const sf::Vector2f& dim);
		Bar(void);
		virtual ~Bar(void);

		void SetPosition(const sf::Vector2f& pos) override;
		void SetOrigin(const Pivot& pivot) override;
		void SetOrigin(const Pivot& pivot, sf::Vector2f* offset) override;
		
		void SetSize(const sf::Vector2f& dim);

		sf::Vector2f* GetSize(void) override;
		const sf::Vector2f& GetOrigin(void) const override;
		
		void ChangeValueBy(const float&& val);
		void UpdateGlobalBounds(void) override;
	
		void Update(void) override;
		void Draw(void) override;

	private:

		bool decreaseVal = false;

		void UpdateBarPos(void);

		sf::Clock clock;
		sf::Time timer;

	};

	class Image : public Widget
	{
	public:

		sf::Sprite sprite;
		sf::Texture texture;

		Image(const char* path);
		Image(const sf::Texture& texture);
		virtual ~Image(void);

		void SetPosition(const sf::Vector2f& pos) override;
		void SetOrigin(const Pivot& pivot) override;
		void SetOrigin(const Pivot& pivot, sf::Vector2f* offset) override;

		sf::Vector2f* GetSize(void) override;
		const sf::Vector2f& GetOrigin(void) const override;

		void UpdateGlobalBounds(void) override;
		void Draw(void) override;

	};

	class InputTextField : public Widget
	{
	public:

		InputTextField(const char* label);
		InputTextField(void);
		virtual ~InputTextField(void);

		void SetPosition(const sf::Vector2f& pos) override;
		void SetOrigin(const Pivot& pivot) override;
		void SetOrigin(const Pivot& pivot, sf::Vector2f* offset) override;

		sf::Vector2f* GetSize(void) override;
		const sf::Vector2f& GetOrigin(void) const override;

		void MouseClick(void) override;
		void MouseClick(const sf::Mouse::Button& mb) override;

		void UpdateGlobalBounds(void) override;
		void Update(void) override;
		void Draw(void) override;

	private:

		sf::Text text;
		sf::Text label;

		sf::RectangleShape box;

		bool typing = false;
		bool hasText = false;

		std::string textString;

	};
}