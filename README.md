# Clashborn

Clashborn is a school project where [Mixemand](https://github.com/Mixemand) and I
combine software-centric computer gaming with the real world.

The concept centers around two RFID readers that scan custom character tokens,
which are then summoned in-game to fight each other.

The art style for the game is intentionally simplistic, drawing inspiration from
games like [Pizza Tower](https://store.steampowered.com/app/2231450/Pizza_Tower/),
totally not because none of us know how to draw

## Important info

Due to time constraints (yes we know) the project has died. I JJoe had
to come up with shortcuts, and now the project has a seg fault when a player dies.

Other than that we cannot get the RFID readers to work reliably, maybe because
they are super cheap, or maybe because the arduino can't run two at the same time.

Any how, no more time, no more development. Project had potential, but at last, it died.
Feel free to use the code however you want (no ai training please).

## Features of the game

- [x] Movement (walks and jumps)
- [x] Attacks (Players can attack each other)
- [x] Different character stats
- [x] **DEATH** (includes health on players)
- [x] Health bar
- [X] 4 characters
- [x] Map (With falling to once death, well platforms at least)
- [ ] Interaction between Arduino & RFID readers
- [x] Controls for the arcade cabinet
- [ ] Audio
- [x] Sprites and assets
- [x] Character selections

## Libraries we use
- [Raylib](https://github.com/raysan5/raylib) for rendering, windowing, and inputs
- [simple_serial_port](https://github.com/dmicha16/simple_serial_port) for serial
communication with the Arduino