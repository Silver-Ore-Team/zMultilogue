# zMultilogue
Multi-NPC dialogue system for Gothic, 
based on the solution form [AFSP Trialogue package](https://github.com/Bad-Scientists/AF-Script-Packet/blob/main/Standalone-Packages/G12-Trialogue/trialogue.d).

## ToDo

- [x] Implement the basic functionality of the multilogue system
- [x] Increase the default display dialogue distance if needed
- [ ] Custom camera system
- [x] Gothic 1 compatibility

## Usage
1. Download `zMultilogue.vdf` and place it inside `<GOTHIC_ROOT>/Data` with Union installed to automatically load the plugin at the start of the game.

2. Copy the `ZS_MULTILOGUE` routine from [`_externals/zMultilogue.d`](https://github.com/Silver-Ore-Team/zMultilogue/blob/main/_externals/zMultilogue.d) into any file parsed by the game.

3. Use the plugin's externals to create multilogues :smile:

## Example
The following example demonstrates how to create a simple multilogue with two NPCs.
```cpp
instance DIA_TEST_ZMUL(C_INFO)
{
	npc         = NONE_100_Xardas;
	nr          = 0;
	condition   = DIA_TEST_ZMUL_Condition;
	information = DIA_TEST_ZMUL_Info;
	permanent   = FALSE;
	description = "Multilogue test";
};

FUNC INT DIA_TEST_ZMUL_Condition()
{
	return TRUE;
};

FUNC VOID DIA_TEST_ZMUL_Info()
{
	var C_NPC diego; diego = Hlp_GetNpc(PC_Thief_NW);
	var C_NPC xardas; xardas = Hlp_GetNpc(NONE_100_Xardas);
	zMul_Invite(diego);
	zMul_Start();
	AI_Output(other, self, "DIA_TEST_ZMUL_15_00"); //I found your gold!
	zMul_Next(diego);
	AI_Output(self, other, "DIA_TEST_ZMUL_11_01"); //Great. Show me.
	zMul_Next(xardas);
	AI_Output(self, other, "DIA_TEST_ZMUL_14_02"); //What gold?
	AI_Output(other, self, "DIA_TEST_ZMUL_15_03"); //None of your business.
	AI_Output(self, other, "DIA_TEST_ZMUL_14_04"); //Okay. I will be in the tower.
	zMul_Next(diego);
	AI_Output(self, other, "DIA_TEST_ZMUL_11_05"); //Give me the gold now.
	zMul_Finish();
};
```

## Support

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

[union-api](https://gitlab.com/union-framework/union-api) and [gothic-api](https://gitlab.com/union-framework/gothic-api) are licensed under [GNU GENERAL PUBLIC LICENSE V3](https://gitlab.com/union-framework/union-api-/blob/main/LICENSE).


GothicVDFS 2.6 [Copyright (c) 2001-2003, Nico Bendlin, Copyright (c) 1994-2002, Peter Sabath / TRIACOM Software GmbH](vdf/License.txt)