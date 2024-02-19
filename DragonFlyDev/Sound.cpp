
//Included resources
#include "Sound.h"
#include "LogManager.h"

using namespace std;
namespace df {

	Sound::Sound()
	{
		//Initialize variables
		m_label = "";
		
	}

	Sound::~Sound()
	{
		//Reset buffer 
		m_sound.resetBuffer();
	}

	int Sound::loadSound(std::string filename)
	{
		//Get sound file and check that it exists
		if (m_sound_buffer.loadFromFile(filename) == false) {
			LM.writeLog(3, "Failed to find sound with file name %s\n", filename.c_str());
			return -1;
		}
		m_sound.setBuffer(m_sound_buffer);

		return 0;
	}

	void Sound::setLabel(std::string new_label)
	{
		m_label = new_label;
	}

	string Sound::getLabel() const
	{
		return m_label;
	}

	void Sound::play(bool loop)
	{
		m_sound.setLoop(loop);
		m_sound.play();
	}

	void Sound::stop()
	{
		m_sound.stop();
	}

	void Sound::pause()
	{
		m_sound.pause();
	}

	sf::Sound Sound::getSound() const
	{
		return m_sound;
	}
}//End of namespace df