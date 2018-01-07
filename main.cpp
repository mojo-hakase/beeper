#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>

int main () {
	const unsigned SAMPLES = 44100;
	const unsigned SAMPLE_RATE = 44100;
	const unsigned AMPLITUDE = 30000;
	
	sf::Int16 raw[SAMPLES];

	const double TWO_PI = 6.28318;
	const double increment = 440./44100;
	double x = 0;
	for (unsigned i = 0; i < SAMPLES; i++) {
		raw[i] = AMPLITUDE * sin(x*TWO_PI);
		x += increment;
	}
	
	sf::SoundBuffer Buffer;
	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		return 1;
	}

	struct KeyState {
		sf::Keyboard::Key keyCode;
		bool wasPressed;
		sf::Sound sound;
		KeyState(sf::Keyboard::Key keyCode, const sf::SoundBuffer &buffer)
			: keyCode(keyCode)
			, wasPressed(false)
			, sound(buffer)
		{
			sound.setLoop(true);
		}
	};
	std::vector<KeyState> keyStates;
	for (std::size_t idx = 0; idx < sf::Keyboard::KeyCount; ++idx) {
		keyStates.emplace_back(static_cast<sf::Keyboard::Key>(idx), Buffer);
	}
	while (1) {
		sf::sleep(sf::milliseconds(50));
		for (auto& ks : keyStates) {
			auto curState = sf::Keyboard::isKeyPressed(ks.keyCode);
			if (curState != ks.wasPressed) {
				if (curState ) {
					ks.sound.setPitch(1+20.f*static_cast<float>(ks.keyCode)/sf::Keyboard::KeyCount);
					ks.sound.play();
				} else {
					ks.sound.stop();
				}
				ks.wasPressed = curState;
			}
		}
	}
	return 0;

	sf::SoundBuffer sb;
	sf::Sound s;
}
