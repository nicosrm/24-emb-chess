# Embedded Chess Pieces

This repository is a fork of [`dezibot/dezibot`](https://github.com/dezibot/dezibot). and contains our project for the module C999.1 "Software Development for Embedded Systems" lectured by [Prof. Dr. rer. nat. Jens Wagner](https://fim.htwk-leipzig.de/fakultaet/personen/professorinnen-und-professoren/jens-wagner/). We call it *Embedded Chess Pieces*.

> [!IMPORTANT]
> The project is still under development. This note will be removed once the project is submitted.


## Idea

The idea is to place a Dezibot 4 on a chess board and assign a chess piece to it. The user can select which piece the robot represents and how it should move. The selected figure shall be displayed on the built-in display and the move shall be validated first. The result should be shown via the built-in LEDs. If there is time, the moves shall be communicated wirelessly.


## Repository Structure

This repository is a fork of [`dezibot/dezibot`](https://github.com/dezibot/dezibot). Changes to the `Dezibot` library are made directly where necessary. Our main contribution – the `EmbeddedChessPieces` library -- is stored in [example/EmbeddedChessPieces/](./example/EmbeddedChessPieces/). It includes project specific code that is not generally sensible to add to the Dezibot library.

In [`example/EmbeddedChessPieces/examples`](./example/EmbeddedChessPieces/examples/) you can find tests and example use cases for our project. This includes Arduino sketches we developed to test our library developments as well as the heart of this project – the code to run our project.


## Context

| Context    | Description                                                                         |
|------------|-------------------------------------------------------------------------------------|
| Module     | C377.2 Prinzipien von Programmiersprachen                                           |
| Lecturer   | Prof. Dr. rer. nat. Jens Wagner, M. Eng. Marian Ulbricht                            |
| Institute  | Leipzig University of Applied Sciences                                              |
| Semester   | Winter Semester 2024/25                                                             |


## Roadmap

- [x] Recognise colours of the chess board [#1](https://github.com/nicosrm/24-emb-chess/issues/1)
- [ ] Simulate Pawn [#4](https://github.com/nicosrm/24-emb-chess/issues/4)
    - [x] Walk straight a specified number of fields [#2](https://github.com/nicosrm/24-emb-chess/issues/2)
    - [ ] Turn in a given direction to simulate diagonal movement [#3](https://github.com/nicosrm/24-emb-chess/issues/3)
- [ ] Find centre of a chess field [#5](https://github.com/nicosrm/24-emb-chess/issues/5)
- [ ] Draw selected figure to the display [#6](https://github.com/nicosrm/24-emb-chess/issues/6)
- [ ] Logic on which field the robot is at any given moment (show on the display if shaken) [#7](https://github.com/nicosrm/24-emb-chess/issues/7)
- [ ] Calibrate black / white threshold [#15](https://github.com/nicosrm/24-emb-chess/issues/15)
- [x] Expand selectable pieces [#9](https://github.com/nicosrm/24-emb-chess/issues/9)
- [ ] Validate if move is allowed and colour LED green or red accordingly [#10](https://github.com/nicosrm/24-emb-chess/issues/10)
- [ ] Wireless connection for initial field and movements [#8](https://github.com/nicosrm/24-emb-chess/issues/8)


## Usage

- Install [Arduino IDE 2](https://github.com/arduino/arduino-ide)
- Add [`esp32`](https://github.com/espressif/arduino-esp32/releases/tag/2.0.15) board manager by Espressif Systems (version 2.0.15)
- Install all necessary libraries mentioned under [Licence](#licence)
- Create a symbolic link from this repository and the `EmbeddedChessPieces` library to the Arduino library directory on your machine

```sh
$ cd /path/to/Arduino/library
$ ln -s /path/to/24-emb-chess Dezibot
$ ln -s /path/to/24-emb-chess/example/EmbeddedChessPieces/EmbeddedChessPieces EmbeddedChessPieces
```


## Team

- [@irooori](https://github.com/irooori)
- [@nicosrm](https://github.com/nicosrm)


## Licence

This repository is licenced under the GNU General Public License ([GPL-3.0](./LICENSE)).

We also require using the following (third-party) libraries that are licenced as follows:

| Library                                                               | Version | Author       | Licence      |
|-----------------------------------------------------------------------|---------|--------------|--------------|
| [`Adafruit NeoPixel`](https://github.com/adafruit/Adafruit_NeoPixel)* | 1.12.3  | Adafruit     | LGPL-3.0     |
| [`ArduinoJson`](https://github.com/bblanchon/ArduinoJson)*            | 7.2.0   | bblanchon    | MIT          |
| [`AsyncTCP`](https://github.com/dvarrel/AsyncTCP)*                    | 1.1.4   | dvarrel      | LGPL-3.0     |
| [`Dezibot`](https://github.com/dezibot/dezibot) (modified)            | -       | dezibot      | GPL-3.0      |
| [`Painless Mesh`](https://gitlab.com/painlessMesh/painlessMesh)*      | 1.5.0   | PainlessMesh | GPL-3.0      |
| [`TaskScheduler`](https://github.com/arkhipenko/TaskScheduler)*       | 3.8.5   | arkhipenko   | BSD-3-Clause |
| [`VEML6040`](https://github.com/thewknd/VEML6040)*                    | 0.3.2   | thewknd      | MIT          |

`*`: Dependency of Dezibot library
