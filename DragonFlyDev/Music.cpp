
//Included resources
#include "Music.h"
#include "LogManager.h"
using namespace std;
namespace df {

    Music::Music() 
    {
        //Initalize variables
        m_label = "";
        m_playing = false;
    }

    int Music::loadMusic(string filename) 
    {
        if (m_music.openFromFile(filename) == false) {
            LM.writeLog(3, "Failed to find music with file name %s\n", filename.c_str());
            return -1;
        }

        return 0;
    }

    void Music::setLabel(string new_label) 
    {
        m_label = new_label;
    }

    string Music::getLabel() const 
    {
        return m_label;
    }

    void Music::play(bool loop) 
    {
        m_music.setLoop(loop);
        m_music.play();
        m_playing = true;
    }

    void Music::stop() 
    {
        m_music.stop();
        m_playing = false;
    }

    void Music::pause() 
    {
        m_music.pause();
        m_playing = false;
    }

    sf::Music* Music::getMusic() 
    {
        return &m_music;
    }

    bool Music::isPlaying() const
    {
        return m_playing;
    }
     
}//End of namespace