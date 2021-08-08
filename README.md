# PawnPath

PawnPath path walker game for the Arduboy system

<img src="https://github.com/franalvarez21/PawnPath/blob/main/PawnPath/title.png" width="200" height="100">
<img src="https://github.com/franalvarez21/PawnPath/blob/main/PawnPath/demo.gif" width="200" height="100">

## Arduboy

Please refer to https://community.arduboy.com/ on how to acquire, compile or upload games to the Arduboy system.

## Gameplay

- Pad: Movement
- B Button: Pause
- A Button: Action

Game contains 3 game modes (USE the left and right arrows to choose game mode IN the title menu)

# Endless mode
- Play for a high score.
- Higher levels means more risks.
- Start with 8 lives.
- Spikes, additional lives and restore all blocks available.

# Classic mode
- Play and beat all the levels.
- Start with 8 lives.
- No spikes, no additional lives and no restore all blocks.

# Advance mode
- Play and beat all the levels.
- Start with 8 lives.
- Spikes, additional lives and restore all blocks available.

# Blocks:


<img src="https://user-images.githubusercontent.com/1568995/128645936-0a152a81-df2b-4a49-9918-d8c0af2ca36a.png" width="32" height="32"> Breaks after 1 use

<img src="https://user-images.githubusercontent.com/1568995/128645887-37072af5-c2d5-41cb-8348-f72ec026e010.png" width="32" height="32"> Breaks after 2 uses

<img src="https://user-images.githubusercontent.com/1568995/128646048-f5fee9f6-e05e-43f2-9dac-4fe027735c90.png" width="32" height="32"> Solid block, never breaks

<img src="https://user-images.githubusercontent.com/1568995/128645913-1bf70c87-8498-4393-9998-bc07ec8aea5a.png" width="32" height="32"> Spike block, reduce 1 life point

<img src="https://user-images.githubusercontent.com/1568995/128646001-cbb660e2-5853-4267-a1fa-b4ade7231876.png" width="32" height="32"> Restore all broken blocks

<img src="https://user-images.githubusercontent.com/1568995/128646030-3ef93eb8-a42f-48f6-a363-895a9e3061d1.png" width="32" height="32"> Life block, adds 1 life point

<img src="https://user-images.githubusercontent.com/1568995/128645953-f56c861c-aa23-4419-9a6d-ab492d72d333.png" width="32" height="32"> Goal off, you must turn it on!

<img src="https://user-images.githubusercontent.com/1568995/128645977-898818f1-632f-4b5a-bc6b-7ff7947bdf00.png" width="32" height="32"> Goal on

<img src="https://user-images.githubusercontent.com/1568995/128645983-23664bc4-74b6-43d4-b615-d96269f9b8f4.png" width="32" height="32"> Crown, last objective in endless and advance mode

<img src="https://user-images.githubusercontent.com/1568995/128646075-79a96d74-e791-4032-9715-d34b5054280c.png" width="32" height="32"> Goal, last objective in classic mode

## Emulation notes

There is an emulator named 'ProjectABE' that can be used. Feel free to check it out!

https://github.com/felipemanga/ProjectABE

./ProjectABE PawnPath/distributable/PawnPath.ino.leonardo.hex

## Arduboy site post

WIP

## Compilation log

August 8, 2021. V0.1

Sketch uses 24588 bytes (85%) of program storage space. Maximum is 28672 bytes.
Global variables use 1645 bytes (64%) of dynamic memory, leaving 915 bytes for local variables. Maximum is 2560 bytes.
