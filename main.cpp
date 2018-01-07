#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

double pitches[] =
{
	32,
	0.25,0.257325559,0.264865774,0.272626933,0.280615512,0.288838174,0.297301779,0.306013386,0.314980262,0.324209889,0.333709964,0.343488412,0.353553391,0.363913296,0.374576769,0.385552706,0.396850263,0.408478863,0.420448208,0.432768281,0.445449359,0.458502022,0.471937156,0.485765971,0.5,0.514651118,0.529731547,0.545253866,0.561231024,0.577676348,0.594603558,0.612026772,0.629960525,0.648419777,0.667419927,0.686976824,0.707106781,0.727826591,0.749153538,0.771105413,0.793700526,0.816957727,0.840896415,0.865536561,0.890898718,0.917004043,0.943874313,0.971531941,1,1.029302237,1.059463094,1.090507733,1.122462048,1.155352697,1.189207115,1.224053543,1.25992105,1.296839555,1.334839854,1.373953647,1.414213562,1.455653183,1.498307077,1.542210825,1.587401052,1.633915453,1.681792831,1.731073122,1.781797436,1.834008086,1.887748625,1.943063882,2,2.058604473,2.118926189,2.181015465,2.244924097,2.310705394,2.37841423,2.448107087,2.5198421,2.593679109,2.669679708,2.747907295,2.828427125,2.911306366,2.996614154,3.084421651,3.174802104,3.267830906,3.363585661,3.462146244,3.563594873,3.668016173,3.775497251,3.886127765,4,4.117208947,4.237852377,4.362030931,4.489848193,4.621410787,4.75682846,4.896214173,5.0396842,5.187358219,5.339359417,5.49581459,5.656854249
};

int main () {
	std::cout << sf::Keyboard::KeyCount << std::endl;
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
					ks.sound.setPitch(pitches[ks.keyCode]*100);
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
