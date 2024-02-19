#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <string>
#include <SFML/Audio.hpp>

using namespace std;
namespace df {

    class Music {
    private:
        // SFML doesn't allow music copy.
        Music(Music const&);
        // SFML doesn't allow music assignment.
        void operator=(Music const&);
        // The SFML music.
        sf::Music m_music;
        // Text label to identify music.
        string m_label;

        //Bool is the current music play
        bool m_playing;

    public:
        //Constructer
        Music();

        // Associate music buffer with file.
        // Return 0 if ok, else -1.
        int loadMusic(string filename);

        // Set label associated with music.
        void setLabel(string new_label);

        // Get label associated with music.
        string getLabel() const;

        // Play music.
        // If loop is true, repeat play when done.
        void play(bool loop = true);

        // Stop music.
        void stop();

        // Pause music.
        void pause();

        // Return pointer to SFML music.
        sf::Music* getMusic();

        //Return if music is playing or not
        bool isPlaying() const;


    };//End of class
}//End of namespace
#endif //__MUSIC_H__