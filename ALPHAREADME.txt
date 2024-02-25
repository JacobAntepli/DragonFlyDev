Names: Jacob Antepli, June Whittall
emails: jaantepli@wpi.edu, jwhittall@wpi.edu


The normal README has everything regarding the game engine.

Game title: Alphabet Soup
Team name: Flavorful Phonics

Game files are:
- player.h
- points.h
- enemy.h
- soup.cpp

and associated .cpp files for the header file.

Press ESC to quit the game; press WASD to move around. Left and right arrows increase or decrease the sprite index, for testing purposes (notice how this changes the score). 

Letters from A-D spawn in on every side of the screen; the player should aim to collect the next letter of the alphabet that is not yet on their sprite. Once the player reaches letter D, they will gain 10 points and their sprite will reset, signifing the end of a round. 

Every correct letter gained is 1 point, and every incorrect letter deducts 2. The score cannot be negative. 

There is no win condition, play continues forever.

