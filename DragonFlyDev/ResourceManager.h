#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

//Included resources
#include <string>
#include <vector>
#include "Manager.h"
#include "Sprite.h"

using namespace std;
namespace df {

	//Maximum number of unique sprites
	const int MAX_SPRITES = 500;

	//Two letter acronym
	#define RM df::ResourceManager::getInstance()

	class ResourceManager : public Manager {

	private:

		//Header file delimiters
		const string HEADER_TOKEN = "HEADER";
		const string BODY_TOKEN = "BODY";
		const string FOOTER_TOKEN = "FOOTER";
		const string FRAMES_TOKEN = "frames";
		const string HEIGHT_TOKEN = "height";
		const string COLOR_TOKEN = "color";
		const string SLOWDOWN_TOKEN = "slowdown";
		const string END_FRAME_TOKEN = "end";
		const string VERSION_TOKEN = "version";

		//Singleton measures
		//Private constructer
		ResourceManager();
		//Prevent copying
		ResourceManager(ResourceManager const&);
		//Prevent assignment
		void operator=(ResourceManager const&);
		
		//Array of sprites
		Sprite* m_p_sprite[MAX_SPRITES];

		//Count of loaded sprites
		int m_sprite_count;
	public:

		//Get the one and only instance of the resource manager
		static ResourceManager& getInstance();

		//Get resource manager ready for resources
		//Return 0 if successful, -1 on failure
		int startUp();

		//Shut down resource manager and free up allocated space
		void shutDown();

		//Load sprite file
		//Assign to indicated sprite
		//Return 0 if successful, -1 on failure
		int loadSprite(string filename, string label);

		//Unload sprite with indicated label
		//Return 0 if successful, -1 on failure
		int unloadSprite(string label);

		//Find Sprite with indicated label
		//Return pointer if found found, NULL if not
		Sprite* getSprite(string label) const;

		//Remove \r from line
		void discardCR(string& str);

		//_____________________________
		//Resource Manager Helpers
		//-----------------------------
		//Get next line from file, with error (""means error).
		string getLine(std::ifstream* p_file);

		//Read in next section of data from file as vector of strings
		//Return vector(empty if error)
		std::vector<std::string> readData(std::ifstream * p_file, string delimiter);

		//Match token in vector of lines
		//Return corresponding value(-1 if not found).
		//Remove any line that matches from vector
		int matchLineInt(std::vector <std::string>* p_data, const char* token);

		//Match token in vector of lines
		//Return corresponding value("" if not found).
		//Remove any line that matches from vector
		string matchLineStr(std::vector <std::string>* p_data, const char* token);

		//Match frame lines until "end", clearing all from vector
		//Looks top to bottom
		//Return frame
		Frame matchFrame(std::vector<std::string>* p_data, int width, int height);

		//Translates a string into a df color
		Color stringToColor(string color);


	};//End of class
}//End of namespace
#endif // __RESOURCE_MANAGER_H__