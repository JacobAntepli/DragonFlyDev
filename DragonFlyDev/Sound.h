#ifndef __SOUND_H__
#define __SOUND_H__

//Included resources
#include <string>
#include <SFML/Audio.hpp>

using namespace std;
namespace df {

    class Sound{
    private:
        // The SFML sound.
        sf::Sound m_sound;

        // SFML sound buffer associated with sound.
        sf::SoundBuffer m_sound_buffer;

        // Text label to identify sound.
        string m_label;

    public:
        //Constructer 
        Sound();

        //Destructer 
        ~Sound();

        // Load sound buffer from file.
        // Return 0 if ok, else -1.
        int loadSound(string filename);

        // Set label associated with sound.
        void setLabel(string new_label);

        // Get label associated with sound.
        string getLabel() const;

        // Play sound.
        // If loop is true, repeat play when done.
        void play(bool loop = false);

        // Stop sound.
        void stop();

        // Pause sound.
        void pause();

        // Return SFML sound.
        sf::Sound getSound() const;

    };//End of class
}//End of namespace df
#endif //__SOUND_H__