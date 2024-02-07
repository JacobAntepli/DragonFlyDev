
//Included resources
#include "DisplayManager.h"
#include "LogManager.h"


namespace df {

	//Constructer definition
	DisplayManager::DisplayManager() {

		

		//Initialize Variables

		m_p_window = NULL;
		m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
		m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
		m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
		m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	}

	//Get the one an only instance of the DisplayManager
	DisplayManager& DisplayManager::getInstance()
	{
		static DisplayManager displayManager;
		return displayManager;
	}

	//Open window
	//Return 0 on success, -1 on failure	
	int DisplayManager::startUp()
	{
		//Check if window is already made
		if (m_p_window != NULL) {
			return 0;
		}

		//Get Window ready
		m_p_window = new sf::RenderWindow (sf::VideoMode(WINDOW_HORIZONTAL_PIXELS_DEFAULT, WINDOW_VERTICAL_PIXELS_DEFAULT), WINDOW_TITLE_DEFAULT);

		//Turn off mouse cursor for window
		m_p_window->setMouseCursorVisible(false);

		//Sync refresh rate
		m_p_window->setVerticalSyncEnabled(true);


		if (m_p_window != NULL) {
			//Base class start up
			Manager::startUp();

			LM.writeLog(1, "Display manager started successfully\n");
			return 0;
		}
	}

	//Close window
	void DisplayManager::shutDown()
	{
		//Base class shutdown
		Manager::shutDown();

		//Close window
		m_p_window->close();
		
		LM.writeLog(0, "Display manager shutdown\n");
	}

	//Draw character at given vector location
	//Return 0 on success, -1 on failure
	int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const 
	{
		//Check if there is a window
		if (m_p_window == NULL) {
			return -1;
		}

		Vector pixel_pos = spacesToPixels(world_pos);

		//Draw background rectangle
		static sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(charWidth(), charHeight()));
		rect.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
		rect.setPosition(pixel_pos.getX() - charWidth() / 10,
						pixel_pos.getY() + charHeight() / 5);
		m_p_window->draw(rect);

		//Create text to draw
		static sf::Text text("",m_font);
		text.setString(ch);
		text.setStyle(sf::Text::Bold);

		//Scale
		if (charWidth() < charHeight()) {
			text.setCharacterSize(charWidth() * 2);
		}
		else {
			text.setCharacterSize(charHeight() * 2);
		}

		//Set SFML color based on dragonfly color
		switch (color) {
		case BLACK:
			text.setFillColor(sf::Color::Black);
			break;
		case RED :
			text.setFillColor(sf::Color::Red);
			break;
		case GREEN:
			text.setFillColor(sf::Color::Green);
			break;
		case YELLOW:
			text.setFillColor(sf::Color::Yellow);
			break;
		case BLUE:
			text.setFillColor(sf::Color::Blue);
			break;
		case MAGENTA:
			text.setFillColor(sf::Color::Magenta);
			break;
		case CYAN:
			text.setFillColor(sf::Color::Cyan);
			break;
		case WHITE:
			text.setFillColor(sf::Color::White);
			break;
		default:
			text.setFillColor(sf::Color::White);
			break;
		}//End of switch
	}

	//Return horizontal max in characters
	int DisplayManager::getHorizontal() const
	{
		return m_window_horizontal_chars;
	}

	//Return vertical max in characters
	int DisplayManager::getVertical() const
	{
		return m_window_vertical_chars;
	}

	//Return horizontal max in pixels
	int DisplayManager::getHorizontalPixels() const
	{
		return m_window_horizontal_pixels;
	}

	//Return vertical max in pixels 
	int DisplayManager::getVerticalPixels() const
	{
		return m_window_vertical_pixels;
	}

	//Render current window buffer
	//Return 0 on success, -1 on failure
	int DisplayManager::swapBuffers()
	{
		//Check if there is a window
		if (m_p_window == NULL) {
			return -1;
		}

		//Display 
		m_p_window->display();

		//Clear window 
		m_p_window->clear();

		LM.writeLog(-1, "Successfully swapped buffer\n");

		return 0;
	}

	//Return pointer to window
	sf::RenderWindow* DisplayManager::getWindow() const
	{
		//Check if there is a window
		if (m_p_window != NULL) {
			return m_p_window;
		}
	}

	//Compute char height in pixels based on window
	float charHeight()
	{
		return DM.getVerticalPixels()/DM.getVertical();
	}

	//Compute char widrh in pixels based on window
	float charWidth()
	{
		return DM.getHorizontalPixels()/DM.getHorizontal();
	}

	//Convert ASCII spaces to window pixels
	Vector spacesToPixels(Vector spaces)
	{
		//Adjust x and y by charWidth and charHeight
		spaces.setXY(spaces.getX() * charWidth(), spaces.getY() * charHeight());
		return spaces;
	}

	//Convert window pixels to ASCII space
	Vector pixelsToSpaces(Vector pixels)
	{
		pixels.setXY(pixels.getX() / charWidth(), pixels.getY() / charHeight());
		return pixels;
	}
}//End of namespace