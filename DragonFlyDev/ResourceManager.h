#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

//Included resources
#include <string>
#include <vector>
#include "Manager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

using namespace std;
namespace df {

	//Maximum number of unique sprites
	const int MAX_SPRITES = 500;

	//Maximum number of unique music
	const int MAX_MUSICS = 50;

	//Maximum number of unique sounds
	const int MAX_SOUNDS = 50;

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

		// Array of sound buffers.
		Sound m_sound[MAX_SOUNDS];

		// Count of number of loaded sounds.
		int m_sound_count;

		// Array of music buffers.
		Music m_music[MAX_MUSICS];

		// Count of number of loaded musics.
		int m_music_count;

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

		// Load Sound from file.
		// Return 0 if ok, else -1.
		int loadSound(string filename, string label);

		// Remove Sound with indicated label.
		// Return 0 if ok, else -1.
		int unloadSound(string label);

		// Find Sound with indicated label.
		// Return pointer to it if found, else NULL.
		Sound* getSound(string label);

		// Associate file with Music.
		// Return 0 if ok, else -1.
		int loadMusic(string filename, string label);

		// Remove label for Music with indicated label.
		// Return 0 if ok, else -1.
		int unloadMusic(string label);

		// Find Music with indicated label.
		// Return pointer to it if found, else NULL.
		Music* getMusic(string label);


	};//End of class
}//End of namespace
#endif // __RESOURCE_MANAGER_H__