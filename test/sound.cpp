#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    // Load a sound buffer
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../sounds/HELLO!.mp3")) { // Make sure you have a 'beep.wav' file
        std::cerr << "Error loading sound file!" << std::endl;
        return -1;
    }

    // Create a sound object
    sf::Sound sound;
    sound.setBuffer(buffer);

    // Play the sound
    sound.play();

    // Keep the program running to allow sound to play completely
    sf::sleep(sf::seconds(2));
    return 0;
}
