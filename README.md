# Building the Flight Computer

## Requirements 

The code generator runs on python3 using the pyyaml package. It's recommended to
use a python virtual environment like this:

    $ sudo apt-get install python3 libyaml-0-2 python-pip virtualenvwrapper
    # Close the tab and re-open it if virtualenvwrapper was installed.
    $ mkvirtualenv -p `which python3` av3fc
    $ 
    (av3fc)$ pip install -r requirements.txt

Use `deactivate` to get out of the virtual environment. To get back into the virtual environment:

    $ workon av3fc

Don't forget to initialize your submodules:

    $ git submodule update --init

## Building

Due to the need for user module abstraction, the build process for the framework
is a little more complicated than that of a typical C application. Here is the
general build process:

 1. User module MIML files and the Main.miml file are passed into the code 
    generator.
 1. The code generator, upon successful parsing and validation, creates the
    fcfmain.c file that include the intermodular data handlers and a Miml.mk 
    Makefile include file.
 1. The Makefile imports the Miml.mk and should successfully compile, link and
    build the executable "fc."

To help uncomplicate this process, however, the Makefile has been created so
that the user only needs to run:

    $ make

BUT don't forget you need to be in your virtual environment for this to work (`workon av3fc`).

### Using the Makefile

As discussed in the introduction to this section, the easiest way to use the
Makefile is to just type `make`.

Here are some other possible uses: `make miml` generates Miml.mk.
`make` builds the project. Then, every repeated use of `make` rebuilds
the project. If one of the ".miml" files changes, make automatically runs
the code generator to rebuild fcfmain.c and fcfmain.h. If the miml files change
so that modules are added or removed, one would have to rebuild the Miml.mk
manually by rerunning `make miml`.

# rocket-flight-computer
🧑🏻‍🚀  Flight computer for model rockets

## Flight computer

The firmware is written with [ESP-IDF](https://github.com/espressif/esp-idf) development framework and ran on an [ESP-32](https://en.wikipedia.org/wiki/ESP32) microcontroller.

External sensors are connected to collect telemetry data:
- BNO055 Absolute Orientation Sensor (9-dof)
- BMP388 Precision Barometric Pressure and Altimeter

Telemetry data is serialized into a binary wire format using [protocol buffers](https://en.wikipedia.org/wiki/Protocol_Buffers).

Ground control software can log telemetry data broadcasted wirelessly by the flight controller.

On-board software can use the telemetry data stream as process variables in a PID control system.

## Visualizer

A companion visualizer application allows real-time visualization of the model rocket body.

Telemetry data is streamed over USB and processed as updates to a 3D graphical scene.

The visualizer uses [raylib](https://www.raylib.com/) for rendering and [protobuf-c](https://github.com/protobuf-c/protobuf-c) for packet deserialization.

# STM32-Flight-Computer

![Travis-CI Build Status](https://travis-ci.com/MVHS-Rocket-Group/STM32-Flight-Computer.svg?branch=master)

Travis CI Dashboard: [travis-ci.com/MVHS-Rocket-Group/STM32-Flight-Computer](https://travis-ci.com/MVHS-Rocket-Group/STM32-Flight-Computer)

## Repository Structure

- `.pio/*`: PlatformIO config files and build directory. (*Generated upon execution of  first build*)
- `.vscode/*`: VSCode config files.
- `include/*`: C/C++ header files.
  - `constants.h`: Provides constant definitions.
  - `helpers.h`: Provides development infrastructure for project.
  - `mean_sensor_filter.h`: Lightweight sensor noise filter taking a time-average for all inputs.
  - `state.h`: State `struct` providing convenient storage for all values in the state vector.
- `lib/*`: C/C++ libraries.
  - `Arduino_LSM9DS1_ID6589/*`: Slightly modified version of [this library from PlatformIO registry](https://platformio.org/lib/show/6589/Arduino_LSM9DS1) tweaked to use the correct addresses for the `LSM9DS1` chip as configured by Ozzymaker.
- `src/*`: C/C++ source code files.
  - `main.cpp`: Primary entry point for program.
- `.gitattributes`, `.gitignore`: Git SCM config files.
- `travis.yml`: Travis CI (*continuous integration*) automated build checker config.
- `platformio.ini`: PlatformIO build config.
- `STM32-Flight-Computer.code-workspace`: VSCode workspace file.
- `TODO.md`: TODO list for project.

## Description

STM32 (*Blue Pill development board, `STM32F103C8T6` MCU part*) flight computer and FDR for high-power SRM rockets. This program is developed in conjunction with the [PlatformIO](https://platformio.org) IDE system with integration into VSCode and Atom editors, a substantial upgrade from the oxymoron Arduino IDE.

Program upload and line-by-line debugging support is provided by the wonderful [ST-Link V2](https://smile.amazon.com/Aideepen-ST-Link-Programming-Emulator-Downloader/dp/B01J7N3RE6) connected to the STM32's SWD (***S**erial **W**ire **D**ebug*) port and a serial text terminal by an [FTDI breakout board](https://smile.amazon.com/HiLetgo-FT232RL-Converter-Adapter-Breakout/dp/B00IJXZQ7C) connected to `UART1` on the STM32.

### Relevant Peripherals

- [Ozzymaker BerryIMU](http://ozzmaker.com/product/berryimu-accelerometer-gyroscope-magnetometer-barometricaltitude-sensor) via I<sup>2</sup>C
- [SD Card breakout board](https://smile.amazon.com/SenMod-Adapter-Reader-Module-Arduino/dp/B01JYNEX56) via SPI
- [3v3 to 5v signal converter](https://smile.amazon.com/Logic-Converter-Bi-Directional-Module-Arduino/dp/B014MC1OAG)

## Principal control flow

- [Arduino framework](https://docs.platformio.org/en/latest/frameworks/arduino.html) for [STM32 targets](https://docs.platformio.org/en/latest/platforms/ststm32.html) in [PlatformIO](https://platformio.org)
- Control-loop paradigm with State and Goal messages logged.
- Gist of Features:
  - Flight controller (*PWM Output*)
  - Flight state data logger
    - [IMU board: Ozzymaker BerryIMU](http://ozzmaker.com/product/berryimu-accelerometer-gyroscope-magnetometer-barometricaltitude-sensor)
    - [LSM9DS1 PIO Library](https://platformio.org/lib/show/6589/Arduino_LSM9DS1)
    - [BMP280 PIO Library](http://platformio.org/lib/show/528/Adafruit%20BMP280%20Library)
    - [SD PIO Library](http://platformio.org/lib/show/868/SD)
  - Important flight events: e.g. Launch detection, arming of different systems, control loop decisions, deployments (detected via accelerometer edges?)
  - Camera recorder via “pressing” the record button?
  - Landing buzzer control?
  - Arming switch toggle (*software interrupt*)

## Background on PWM control for Servo Motors and ESCs

RC PWM has a "window" period of 20ms (milliseconds), with a pulse ranging in width from 1ms to 2ms, where 1ms is ~0% command and 2ms is ~100% command. Duty cycle, a percentage, is a ratio of on-time to off-time.

![ESC PWM Diagram](https://upload.wikimedia.org/wikipedia/commons/b/b7/Sinais_controle_servomotor.JPG)

Therefore:

- 0% throttle command --> 5% duty cycle
- 100% throttle command --> 10% duty cycle

[Documentation on PWM usage in Arduino](https://electronicshobbyists.com/arduino-pwm-tutorial)

## Rocket IMU Axes

From perspective of a cockpit at the nose cone: (***TODO: Verify if these are still correct!***)

![Originally defined like a fighter plane due to how early spacecraft were flight cockpits plopped on the top of rocket boosters.](https://qph.fs.quoracdn.net/main-qimg-67b906f1ec6e62819e16134e76b8830f-c)

| Vehicle Axis: | Axis Description: | IMU Measurement Axis: |
|--------------:|-------------------|:----------------------|
| X | *roll - vertical axis through center of rocket* | +X (*acc*), +X (*gyro*) |
| Y | *pitch - horizontal axis* | -Y (*acc*), +Y (*gyro*) |
| Z | *yaw - horizontal axis* | -Z (*acc*), +Z (*gyro*) |

## Helpful Resources

- ESC
  - [ESC Specs](https://hobbyking.com/en_us/turnigy-monster-2000-200a-4-12s-brushless-esc.html)
    - [ESC manual](https://cdn-global-hk.hobbyking.com/media/file/969150300X462171X21.pdf)
    - [ESC programming card](https://hobbyking.com/en_us/turnigy-monster-2000-esc-programming-card.html)

## PlatformIO STM32 linker scripts

For some reason, the default `STSTM32` linker scripts for the generic `STM32F103C8`, the chip on the Blue Pill, assume that the the MCU has 64K of program flash memory, which is just not the case, as most boards around have 128K of flash. This shouldn't be an issue, but for the extra headroom, this is a good mod. [Original post on PlatformIO Community forum.](https://community.platformio.org/t/stm32f1-blue-pill-stuck-in-dfu-mode-after-upload/6853/19?u=ifconfig)

| File | Original | Post-mod |
|------|----------|----------|
| `[USER_DIR]\.platformio\platforms\ststm32\boards\genericSTM32F103C8.json` | `"maximum_size": 65536,` | `"maximum_size": 131072,` |
| `[USER_DIR]\.platformio\platforms\ststm32\ldscripts\stm32f103x8.ld` | `FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K` | `FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K` |
