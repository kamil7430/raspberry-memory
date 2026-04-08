# Memory Game (GPIO)
This project is a classic memory game written in C, utilizing the c-periphery library to handle GPIO interfaces. The game challenges players to observe a random sequence of flashing LEDs and accurately recreate it using the corresponding buttons.

The game phases are printed into terminal and guide you through the game. Your goal is to watch the LEDs (a sequence of 5 flashes by default), and then try to repeat the sequence. The program includes a 20ms software debounce mechanism and waits for the button to be properly released before registering the next move.

## Usage

### Requirements
* A Linux-based board with GPIO pins (e.g., Raspberry Pi).
* The [c-periphery](https://github.com/vsergeev/c-periphery) library installed.
* A C compiler, such as `gcc`.

### Compilation
Make sure to set proper environment variables for cross-compilation. The project can be built using the CMake files provided.
```bash
mkdir build
cd build
cmake ..
make
```

### Buildroot Package
This project is prepared to be used as a Buildroot package. To add the package to the Buildroot, follow the steps:
1. Create the directory `<buildroot>/package/memory_game` and paste there the project files.
2. Add the following line to a submenu of your choice in `<buildroot>/package/Config.in`:
```
	source "package/memory_game/Config.in"
```
3. In Buildroot's `menuconfig` add the c-periphery dependency and this package. Et voila!

## Hardware Setup
The project interacts with the `/dev/gpiochip0` path. To play the game, you need 4 LEDs configured as outputs and 4 push buttons configured as inputs. 

The buttons are set to trigger on a falling edge (`GPIO_EDGE_FALLING`), which means pressing a button should pull the corresponding pin to ground (active low). Each button is logically paired with a specific LED (e.g., Button 1 corresponds to LED 1).

### Outputs (LEDs)
* LED 1: **GPIO 27**
* LED 2: **GPIO 23**
* LED 3: **GPIO 22**
* LED 4: **GPIO 24**

### Inputs (Buttons)
* Button 1: **GPIO 18**
* Button 2: **GPIO 17**
* Button 3: **GPIO 10**
* Button 4: **GPIO 25**
