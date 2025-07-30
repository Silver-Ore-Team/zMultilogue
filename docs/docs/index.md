# zMultilogue
zMultilogue is a plugin that implements Multi-NPC dialog system for Gothic 1 and Gothic 2 NotR. Its working principle is based on the solution from [AFSP Trialogue package](https://github.com/Bad-Scientists/AF-Script-Packet/blob/main/Standalone-Packages/G12-Trialogue/trialogue.d). The main project goal is to replace Trialog packages based on [Ikarus](https://github.com/Lehona/Ikarus) and [LeGo](https://github.com/Lehona/LeGo/tree/dev) with an union-based plugin.

## Features
* System for creating dialogues with multiple NPCs that doesn't fuck up AI queue
* Manual script interface based on the [LeGo Trialoge package](https://github.com/Lehona/LeGo/blob/dev/Trialoge.d)
* Auto script interface for that makes writing multilogs as easy as normal dialogs
* Advanced camera manipulation system

## Authors
zMultilogue started as a quick replacement for Trialogs when getting rid of Ikarus in [The Story of Nek](https://silveroreteam.pl/en/projects/nek) codebase. Later evolved into a more complex dialog system enhancement. It was published as open-source project under [MIT License](https://github.com/Silver-Ore-Team/zMultilogue/blob/main/LICENSE)[^1] almost instantly when the main features were ready, since there were no union-based alternative available at the time.


The project is maintained under [Silver Ore Team](https://silveroreteam.pl) modding group
by [muczc1wek](https://github.com/muczc1wek):

* Email: [mateusz.uczciwek@silveroreteam.pl](mailto:mateusz.uczciwek@silveroreteam.pl)
* Discord: [@muczc1wek](https://discordapp.com/users/667438896594026517)

Below you can find the contributors to the project:

![zMultilogue contributors](https://contrib.nn.ci/api?repo=Silver-Ore-Team/zMultilogue)

[^1]: zMultilogue depends on [union-api](https://gitlab.com/union-framework/union-api)
and [gothic-api](https://gitlab.com/union-framework/gothic-api) libraries, which are
licensed under [BSD 3-Clause "New" or "Revised" License](https://gitlab.com/union-framework/union-api/-/blob/main/LICENSE)