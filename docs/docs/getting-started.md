# Getting Started
This guide will help you to install and set up zMultilogue plugin for your gothic mod.

## Installation
You have to have [Union](https://drive.google.com/file/d/1AkU5qvxIx7zc3kdpGAwlgA-2WiGS7sU5/view) installed to use zMultilogue.

### Global
1. Download the `zMultilogue-<version>.vdf` form [latest release](https://github.com/Silver-Ore-Team/zMultilogue/releases/latest).
2. Place the file inside `<GOTHIC_ROOT>/Data` with to automatically load the plugin at the start of the game.

!!! Warning
    Global installation is recommended for mod development phase. You should not use it for your final mod release.

### Mod
1. Download the `zMultilogue-<version>.vdf` form [latest release](https://github.com/Silver-Ore-Team/zMultilogue/releases/latest).
2. Rename the file to `zMultilogue.mod`, place it inside `<GOTHIC_ROOT>/Data/ModVDF`.
3. In `YourMod.ini` add the file into `[FILES].VDF` key:

```ini
[FILES]
; NOTICE DOUBLE SPACE!
; If you use multiple VDF files, 
; you have to separate them with TWO spaces
VDF=YourMod.mod  zMultilogue.mod
```

## Setup
Since [`v0.1.9`](https://github.com/Silver-Ore-Team/zMultilogue/releases/tag/v0.1.9) there is no need to include `ZS_MULTILOGUE` routine. It is now done automatically with [zParserExtender](https://auronen.cokoliv.eu/gmc/zengin/scripts/extenders/zparserextender/).

!!! failure "Deprecated"
    To make the plugin work you have to add the `ZS_MULTILOGUE` routine to your scripts.
    ```cpp
    func void ZS_MULTILOGUE() {
    };

    func int ZS_MULTILOGUE_LOOP() {
        if (InfoManager_hasFinished()) {
            return LOOP_END;
        } else {
            return LOOP_CONTINUE;
        };
    };

    func void ZS_MULTILOGUE_END() {
    };
    ```
    The best way to do it is to create a new file, for example `ZS_MULTILOGUE.d` and place it among other routines.

    **MAKE SURE THAT THIS FILE IS INCLUDED IN `GOTHIC.SRC`**

## Configuration
zMultilogue allows you to set some options with .ini parameters.

### Logging

By default, we print only the severity `>=INFO` to Union Console and `>=DEBUG` to ZSpy. To print all logs to the console, you can set `TRACE` logging level in `Gothic.ini`:
```ini
[ZMULTILOGUE]
; Logger levels:
; NONE, FATAL, ERROR, WARN, INFO, DEBUG, TRACE
LoggerLevelUnion=TRACE
LoggerLevelZSpy=TRACE
```

!!! Tip
    Logs form zMultilogue start with `zMul` prefix, so you can recognize them easily.