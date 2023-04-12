# hertzlikeheck
Arduino code for our mains frequency analyser

It's a work in progress but we'll get there. Love you all - Charlie

Notes on how Arduino-cli seems to work:

	- The file that is run must have the same name as the directory it's in
	- Relative paths don't seem to work for including files (relative to what? The file? The Arduino core?)
	- Here's a guide on how to set it up: https://arduino.github.io/arduino-cli/0.19/getting-started/
	- Nano boards use avr core, as mentioned here https://github.com/arduino/arduino-cli/issues/550
	- Compile first: alias arduinoup="arduino-cli upload -v -p /dev/ttyUSB0 -b arduino:avr:nano:cpu=atmega328old"
	- Then upload: alias arduinoup="arduino-cli upload -v -p /dev/ttyUSB0 -b arduino:avr:nano:cpu=atmega328old"
