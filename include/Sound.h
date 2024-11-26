#ifndef SOUND_H
#define SOUND_H
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

sf::SoundBuffer click;

void loadSounds()
{
  click.loadFromFile("sounds/click_sound.wav");
}

void clickSound(int ms)
{
  sf::Time duration = click.getDuration();
  for (int i = 0; i < ms; i+=duration.asMilliseconds()+50)
  {
    // Create a sound object
    sf::Sound sound;
    sound.setBuffer(click);

    // Play the sound
    sound.play();

    sf::sleep(sf::milliseconds(duration.asMilliseconds()+50));
  }
}

#endif