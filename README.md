# ProjectOwls
Think Mega Man bosses, but with a boxer. Made for DMG and Game Gear. It aims to run on original hardware and uses MBC5 (for DMG).

[!WARNING]
> The Game Gear build is broken right now. I will focus on it when I add proper sprites.

# Controls

| Button Game Boy | Button Game Gear | Action |
|---|---|---|
| Directional Pad |  Joypad | Move Character |
| A | 2 | Jump |
| B | 1 | Jab |
| Up + B | Up + 1 | Uppercut, also possible in the air |
| Down + B | Down + 1 | Dash |
| Hold B and Release | Hold 1 and Release | Side Step, short invincible Dash |

# Compiling
Adjust paths to GDBK and your favourite emulator if necessary and run the makefile or `compile.bat`. You can use `compile.bat -nostart` To just compile the game.


## Parameters
```
compile.bat [-nostart]
compile.bat [-nostartgb] [-nostartgg]

-nostart : Don't start any emulator, combines -nostartgb and -nostartgg
-nostartgb: Don't start DMG emulator
-nostartgg: Don't start GG emulator

```

## Frameworks
Made with [GBDK 2020 version 4.3.0](https://github.com/gbdk-2020/gbdk-2020)
