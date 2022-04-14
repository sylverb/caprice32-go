# CAPRICE32 4.5+ LIBRETRO - [changelog](CHANGES.md)

**All the credit of the caprice32 Emulator to Ulrich Doewich**

You can download the caprice32 original source code [here](http://sourceforge.net/projects/caprice32/)


This core also use some code from [wiituka/pituka](http://code.google.com/p/wiituka/) (c) 2004-2016 David Colmenero


CPC464+/CPC6128+/GX4000 (c) 2016-2019 Colin Pitrat : https://github.com/ColinPitrat/caprice32


And of course for the RetroArch/Libretro team : "http://www.libretro.com"

The core work pretty well and give the fantastic ability to use the RetroArch Shaders.

Try some CRT shaders and welcome back to the 80s on you're good old CPC.

## Usage

Launch a TAPE (cdt), DSK or M3U, and game should autostart.

### Keyboard emulated layout
#### English layout
![keyb_en](https://user-images.githubusercontent.com/560310/54316312-abdeb180-45e0-11e9-9063-faf78fec9d6d.png)
#### Spanish layout
![keyb_es](https://user-images.githubusercontent.com/560310/54316295-9ff2ef80-45e0-11e9-9ae4-a2e3fb064600.png)
#### French layout
![keyb_fr](https://user-images.githubusercontent.com/560310/54316280-97021e00-45e0-11e9-91b5-da73a87534d6.png)


### Keyboard Custom Binds
Choose **AMSTRAD KEYBOARD** in _Quick Menu > Controls_ and **User 1/2 config different than joystick** to map your retropad keys per game/rom.

Caprice brings some default keymaps confings, these configs are detailed at libretro docs: https://docs.libretro.com/library/caprice32/

## Features not covered in docs

 * New Model: [cap32_model] (6128 | 464 | 664 | 6128+)

Choose which Amstrad CPC model to emulate, currently added 646 to allow BASIC 1.0 games and DSK

### New filename flags (case insensitive)

* "[664]": Force BASIC 1.0 and AMSDOS ROMs, to allow play correctly first CPC games.
* "BASIC 1.0": Force 464 model when you load CDT or 664 model if use DSK.
* "[CPM]": Force load CPM BIOS first, useful for some infocom CPM games (WIP).

Examples :

```
Alive (1990)(Company)(fr)[664].dsk => 664
Manic Miner (UK) (1984) (Version Basic 1.0) [Amsoft].dsk => 664
Harrier Attack (1986)(Amsoft) [Basic 1.0].cdt => 464
```

# Known Bugs

- [CPC+ Emulation have some issues](https://github.com/libretro/libretro-cap32/issues/59)

- Old3DS need some optimizations (~18fps).
