# zMultilogue
zMultilogue is a Multi-NPC dialogue system for Gothic 1 and Gothic 2 NotR, based on the solution form [AFSP Trialogue package](https://github.com/Bad-Scientists/AF-Script-Packet/blob/main/Standalone-Packages/G12-Trialogue/trialogue.d).
Its goal is to replace Trialoue packages based on [Ikarus](https://github.com/Lehona/Ikarus) and [LeGo](https://github.com/Lehona/LeGo/tree/dev) with an union-based plugin.

## Features
- System for creating dialogues with multiple NPCs that doesn't fuck up AI queue
- Script interface based on the LeGo [Trialogue package](https://github.com/Lehona/LeGo/blob/dev/Trialoge.d) (easy to port dialogues)
- Automatic increasing of dialog-box display distance if NPC is too far

## ToDo

- [x] Implement the basic functionality of the multilogue system
- [x] Increase the default display dialogue distance if needed
- [ ] Custom camera system
- [x] Gothic 1 compatibility

## Documentation
Documentation of a project is provided a GitHub wiki.

- [Home](https://github.com/Silver-Ore-Team/zMultilogue/wiki)
    - [Getting Started](https://github.com/Silver-Ore-Team/zMultilogue/wiki/Getting-Started)
    - [Script Interface](https://github.com/Silver-Ore-Team/zMultilogue/wiki/Script-Interface)

## Support

If you have found a bug in zMultilogue, please [create an issue](https://github.com/Silver-Ore-Team/zMultilogue/issues/new).

### Discord

You can contact the authors and maintainers on Discord. 
Look for [@muczciwek](https://discordapp.com/users/667438896594026517).

#### Gothic Modding Community

Biggest community of international Gothic modders.
https://discord.gg/SJfHUv5SRW

#### 🇵🇱 Historia Neka

Official Discord of Nek's History, the mod we are working on and started zMultilogue for it.
https://discord.gg/4E2CeQAeWS


## License

zMultilogue is licensed under [MIT license](LICENSE) excluding some dependencies.

[union-api](https://gitlab.com/union-framework/union-api) and [gothic-api](https://gitlab.com/union-framework/gothic-api) are licensed under [GNU GENERAL PUBLIC LICENSE V3](https://gitlab.com/union-framework/union-api/blob/main/LICENSE).


GothicVDFS 2.6 [Copyright (c) 2001-2003, Nico Bendlin, Copyright (c) 1994-2002, Peter Sabath / TRIACOM Software GmbH](vdf/License.txt)