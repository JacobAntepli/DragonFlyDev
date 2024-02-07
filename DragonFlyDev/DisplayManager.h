#ifndef __DISPLY_MANAGER_H__
#define __DISPLY_MANAGER_H__

//Included resources
#include <SFML/Graphics.hpp>
#include "Manager.h"
#include "Color.h"
#include "Vector.h"

using namespace std;
namespace df {

	//Compute char height in pixels based on window
	float charHeight();

	//Compute char widrh in pixels based on window
	float charWidth();

	//Convert ASCII spaces to window pixels
	Vector spacesToPixels(Vector spaces);

	//Convert window pixels to ASCII space
	Vector pixelsToSpaces(Vector pixels);

	//Two letter acronym 
	#define DM df::DisplayManager::getInstance()

	//Defaults for window 
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar | sf::Style::Close;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const string FONT_FILE_DEFAULT = "Fonts/df-AnonymousPro.ttf";
	const float FONT_SCALE_DEFAULT = 2.0;

	class DisplayManager : public Manager {

	private:
		//Constructer private for singleton
		DisplayManager();

		//Don't allow copies
		DisplayManager(DisplayManager const&);

		//Dont allow assignment 
		void operator=(DisplayManager const&);

		//Font
		sf::Font m_font;

		//Pointer to main window
		sf::RenderWindow* m_p_window;

		//Horizontal pixels in window
		int m_window_horizontal_pixels;

		//Vertical pixels in window
		int m_window_vertical_pixels;  

		//Horizontal ASCII space in window
		int m_window_horizontal_chars;  

		//Vertical ASCII space in window
		int m_window_vertical_chars;

	public:
		//Get the one an only instance of the DisplayManager
		static DisplayManager& getInstance();

		//Open window
		//Return 0 on success, -1 on failure
		int startUp();

		//Close window
		void shutDown();

		//Draw character at given vector location
		//Return 0 on success, -1 on failure
		int drawCh(Vector world_pos, char ch, Color color) const;

		//Return horizontal max in characters
		int getHorizontal() const;

		//Return vertical max in characters
		int getVertical() const;

		//Return horizontal max in pixels
		int getHorizontalPixels() const;

		//Return vertical max in pixels 
		int getVerticalPixels() const;

		//Render current window buffer
		//Return 0 on success, -1 on failure
		int swapBuffers();

		//Return pointer to window
		sf::RenderWindow* getWindow() const;
		
	};//End of class
}//End of namespace
#endif __DISPLY_MANAGER_H__