

//Included resources
#include <fstream>
#include <algorithm>
#include "ResourceManager.h"
#include "LogManager.h"

namespace df {

	ResourceManager::ResourceManager() {
		//Set type
		setType("ResourceManager");

		//Initalize variables
		m_sprite_count = 0;
		m_sound_count = 0;
		m_music_count = 0;
	}

	ResourceManager& ResourceManager::getInstance()
	{
		// TODO: insert return statement here
		static ResourceManager resourceManager;
		return resourceManager;
	}

	int ResourceManager::startUp()
	{
		//Base class start up
		Manager::startUp();

		

		LM.writeLog(0, "Resource Manager successfully started");
		return 0;
	}

	void ResourceManager::shutDown()
	{
		//Base class shutdown
		Manager::shutDown();

		//Deallocate memory
		//Loop through sprites array to find sprites that are not null
		for (int i = 0; i < m_sprite_count - 1; i++) {
			if (m_p_sprite[i] != NULL) {
				//Once found, delete sprites
				delete m_p_sprite[i];
			}
		}
	}

	int ResourceManager::loadSprite(string filename, string label)
	{
		//Return -1 if full
		if (m_sprite_count == MAX_SPRITES) {
			LM.writeLog(5, "Error: Cannot add more sprites, attemting sprite label: %s\n", label.c_str());
			return -1;
		}

		//Open file
		ifstream spriteFile;
		spriteFile.open(filename);

		if (!spriteFile.is_open()) {
			LM.writeLog(5, "RESOURCE MANAGER ERROR: COULD NOT FIND FILE %s\n", filename.c_str());
			return -1;
		}

		//Read header 
		std::vector<string> headerData = readData(&spriteFile, HEADER_TOKEN);
		
		//Variables for new sprite
		int frame_count = matchLineInt(&headerData, "frames");
		int width = matchLineInt(&headerData, "width");
		int height = matchLineInt(&headerData, "height");
		int slowdown = matchLineInt(&headerData, "slowdown");
		int transparancy = matchLineInt(&headerData, "transparency");
		string color = matchLineStr(&headerData, "color ");

		//Check all variables
		if (frame_count == -1) {
			LM.writeLog(5, "Error: Filed to parse frame count of sprite with label %s\n", label.c_str());
			return -1;
		}

		if (slowdown == -1) {
			LM.writeLog(5, "Error: Filed to parse slowdown of sprite with label %s\n", label.c_str());
			return -1;
		}

		if (width == -1) {
			LM.writeLog(5, "Error: Failed to parse width of sprite with label %s\n", label.c_str());
			return -1;
		}

		if (height == -1) {
			LM.writeLog(5, "Error: Failed to parse height of sprite with label %s\n", label.c_str());
			return -1;
		}

		if (color == "") {
			LM.writeLog(5, "Error: Failed to parse color of sprite with label %s, set to default color white\n", label.c_str());
			color = "white";
		}


		//Set transparency to default if unable to find (not all sprites need it)
		if (transparancy == -1) {
			transparancy = 0;
		}

		//Read body
		std::vector<string> frameData = readData(&spriteFile, BODY_TOKEN);

		//Create new sprite with variables
		Sprite* new_sprite = new Sprite(frame_count);
		new_sprite->setWidth(width);
		new_sprite->setHeight(height);
		new_sprite->setTransparency(transparancy);
		new_sprite->setSlowdown(slowdown);
		Color col = stringToColor(color);
		new_sprite->setColor(col);
		new_sprite->setLabel(label);
		

		//Add frames to new sprite
		for (int f = 1; f < frame_count; f++) {
			new_sprite->addFrame(matchFrame(&frameData, width, height));
		}

		//Close file
		spriteFile.close();
	
		//Add sprite to array
		m_p_sprite[m_sprite_count] = new_sprite;

		//Incriment count
		m_sprite_count++;

		return 0;
	}

	int ResourceManager::unloadSprite(string label)
	{
		//Loop through sprites to find one to delete
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label) {
				//Once fond, delete sprite
				delete m_p_sprite[i];
				
				//Once found adjust the sprites array
				for (int j = i; i < m_sprite_count - 1; j++) {
					m_p_sprite[j] = m_p_sprite[j + i];
				}
				//Decrement
				m_sprite_count--;

				LM.writeLog(-1, "Succesfully deleted sprite with label %s\n", label.c_str());
				return 0;
			}
		}
		return -1;
	}

	Sprite* ResourceManager::getSprite(string label) const
	{
		//Loop through sprites array to find sprite
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label) {
				//Once fond, return sprite
				return m_p_sprite[i];
			}
		}
		return nullptr;
	}

	void ResourceManager::discardCR(string& str)
	{
		//Look to see if the end of a string is \r
		if (str.size() > 0 && strcmp(&str[str.size() - 1],"\r") == 0) {
			//if it is, erase it
			str.erase(str.size() - 1);
		}
	}

	string ResourceManager::getLine(std::ifstream* p_file)
	{
		//string that holds the information from line
		string line;

		//Get the line from the file
		getline(*p_file,line);
		//Check if its good (e.g not "")
		if (!p_file->good()) {
			LM.writeLog(5, "Error getting line\n");
			return "";
		}

		//Discard cr
		discardCR(line);

		return line;
	}

	std::vector<std::string> ResourceManager::readData(std::ifstream* p_file, string delimiter)
	{
		//Set beginning and end of section
		string beginning = "<" + delimiter + ">";
		string ending = "</" + delimiter + ">";

		//Variable that will hold read data
		std::vector<string> data;

		//Check for beginning
		string s;
		s = getLine(p_file);
	
		if (s != beginning) {
			LM.writeLog(5, "Error reading data beginning with delimiter %s\n", delimiter.c_str());
			return data;
		}

		s = getLine(p_file);
		//Read data until ending
		while (s != ending && !s.empty()) {
			//Push back to add to data and get new line
			data.push_back(s);
			s = getLine(p_file);
		}

		//Ending not found
		if (s.empty()) {
			LM.writeLog(5, "Error reading data ending with delimiter %s\n", delimiter.c_str());
			std::vector<string> empty;
			return empty;
		}

		return data;
	}

	int ResourceManager::matchLineInt(std::vector<std::string>* p_data, const char* token)
	{
		//Begin looping through all lines and make variables
		auto i = p_data->begin();
		int num = 0;
		string line;
		while (i != p_data->end()) {
			
			if (i->substr(0, strlen(token)) == token){
				//Get number from line
				line = *i;
				num = atoi(line.substr(strlen(token) + 1).c_str());
				//printf("NUM: %d\n", num);
				//Clear from vector
				i = p_data->erase(i);
				return num;	
			}
			else {
				i++;
			}
		}
		return num;
	}

	string ResourceManager::matchLineStr(std::vector<std::string>* p_data, const char* token)
	{
		//Begin looping through all lines and make variables
		auto i = p_data->begin();
		string line = "";
		while (i != p_data->end()) {
			if (i->substr(0, strlen(token)) == token) {
				//Get string from line
				line = *i;
				//Clear from vector
				i = p_data->erase(i);
				return line.substr(strlen(token));
			}
			else {
				i++;
			}
		}

		if (line == "") {
			LM.writeLog(5, "Unable to find token %s\n", token);
		}
		return line;
	}

	Frame ResourceManager::matchFrame(std::vector<std::string>* p_data, int width, int height)
	{
		//Strings to hold line and frame
		string line, frame_str;

		//Match height
		for (int h = 0; h < height; h++) {
			line = p_data->front();
		
			//Check that the length of the string is equal to the width
			if (line.length() != width) {
				LM.writeLog(5, "Error matching frame, expected: %d, recevied: %d\n", width, line.length());
				Frame empty;
				return empty;
			}
			
			//Erase this layer
			p_data->erase(p_data->begin());

			//Add line to frame
			frame_str += line;
		}

		//Get what should be the end frame token
		line = p_data->front();

		//Ensure data has been fully parsed for the frame
		if (line != END_FRAME_TOKEN) {
			LM.writeLog(5, "Error parsing frame with width %d and height %d (Could not find end token)\n", width,height);
			Frame empty;
			return empty;
		}

		//Erase final layer 
		p_data->erase(p_data->begin());

		//Create new frame and return
		Frame frame(width,height,frame_str);
		

		return frame;
	}

	Color ResourceManager::stringToColor(string color)
	{
		//Transform string into all lower case for filtering
		transform(color.begin(), color.end(), color.begin(), ::tolower);
		//Return a corrodsponding dragonfly color 
		if (color == "black") {
			return BLACK;
		}
		else if (color == "red") {
			return RED;
		}
		else if (color == "green") {
			return GREEN;
		}
		else if (color == "yellow") {
			return YELLOW;
		}
		else if (color == "blue") {
			return BLUE;
		}
		else if (color == "magenta") {
			return MAGENTA;
		}
		else if (color == "cyan") {
			return CYAN;
		}
		else if (color == "white") {
			return WHITE;
		}
		else {
			return UNEFINED_COLOR;
		}
	}

	int ResourceManager::loadSound(string filename, string label)
	{
		//Ensure there is room
		if (m_sound_count >= MAX_SOUNDS) {
			LM.writeLog(3, "Attempted to add additional sound but resource manager was full\n");
			return -1;
		}

		//Ensure file exists
		if (m_sound[m_sound_count].loadSound(filename) == -1) {
			LM.writeLog(3, "Failed to find sound with file name %s\n", filename.c_str());
			return -1;
		}

		//Set label and incriment 
		m_sound[m_sound_count].setLabel(label);
		m_sound_count++;

		return 0;
	}

	int ResourceManager::unloadSound(string label)
	{
		//Loop through every sound 
		for (int i = 0; i < m_sound_count; i++) {
			//Check label
			if (m_sound[i].getLabel() == label) {
				LM.writeLog(0, "Successfully unloaded sound with label %s\n", label);
				//Scoot over other sounds
				for (int j = i; i < m_sound_count - 1; j++) {
					m_sound[j] = m_sound[j + i];
				}
				//Decriment count
				m_sound_count--;
				return 0;
			}

		}
		return -1;
	}

	Sound* ResourceManager::getSound(string label)
	{
		//Loop through every sound 
		for (int i = 0; i < m_sound_count; i++) {
			//Check label
			if (m_sound[i].getLabel() == label) {
				return &m_sound[i];
			}
		}

		//Couldnt find sound
		return NULL;
	}

	int ResourceManager::loadMusic(string filename, string label)
	{
		//No empty labels allowed
		if (label == "") {
			LM.writeLog(3, "Error: Attempted to add music with empty label\n");
			return -1;
		}

		//Ensure there is room
		if (m_music_count >= MAX_MUSICS) {
			LM.writeLog(3, "Attempted to add additional music but resource manager was full\n");
			return -1;
		}

		//Ensure file exists
		if (m_music[m_music_count].loadMusic(filename) == -1) {
			LM.writeLog(3, "Failed to find music with file name %s\n", filename.c_str());
			return -1;
		}

		//Set label and incriment 
		m_music[m_music_count].setLabel(label);
		m_music_count++;

		return 0;
	}

	int ResourceManager::unloadMusic(string label)
	{
		// Loop through every music 
		for (int i = 0; i < m_music_count; i++) {
			// Check label
			if (m_music[i].getLabel() == label) {

				LM.writeLog(0, "Successfully unloaded music with label %s\n", label);

				//Set label to be empty
				m_music[i].setLabel("");

				// Decrement count
				m_music_count--;
				return 0;
			}
		}
		return -1;
	}

	Music* ResourceManager::getMusic(string label)
	{
		// Loop through every music
		for (int i = 0; i < m_music_count; i++) {
			// Check label
			if (m_music[i].getLabel() == label) {
				return &m_music[i];
			}
		}

		// Couldn't find music
		return NULL;
	}
}//End of namespace 
