#ifndef POKEPLATINUM_UNK_020797C8_H
#define POKEPLATINUM_UNK_020797C8_H

#include "struct_decls/struct_020797DC_decl.h"

#include "pokemon.h"
#include "strbuf.h"

#define MAX_PC_BOXES     18
#define MAX_PC_ROWS      5
#define MAX_PC_COLS      6
#define MAX_MONS_PER_BOX (MAX_PC_ROWS * MAX_PC_COLS)

void PCBoxes_Init(PCBoxes *pcBoxes);
u32 PCBoxes_SaveSize(void);
BOOL sub_02079868(PCBoxes *pcBoxes, BoxPokemon *param1);
BOOL sub_020798A0(PCBoxes *pcBoxes, u32 param1, BoxPokemon *param2);
BOOL sub_02079914(PCBoxes *pcBoxes, u32 param1, u32 param2, BoxPokemon *param3);
void sub_02079968(PCBoxes *pcBoxes, u32 param1, u32 param2);
u32 sub_0207999C(const PCBoxes *pcBoxes);
u32 PCBoxes_FirstEmptyBox(const PCBoxes *pcBoxes);
BOOL sub_020799F0(const PCBoxes *pcBoxes, int *param1, int *param2);
u32 GetBoxedPokemonCount(const PCBoxes *pcBoxes);
void sub_02079A94(PCBoxes *pcBoxes, u32 param1);
u32 sub_02079AA8(const PCBoxes *pcBoxes, u32 param1);
void sub_02079AC4(PCBoxes *pcBoxes, u32 param1, u32 param2);
void sub_02079AF4(const PCBoxes *pcBoxes, u32 param1, Strbuf *param2);
void sub_02079B24(PCBoxes *pcBoxes, u32 param1, const Strbuf *param2);
u32 GetPokemonCountInBox(const PCBoxes *pcBoxes, u32 boxIndex);
u32 GetEggCountInBox(const PCBoxes *pcBoxes, u32 boxIndex);
u32 GetTotalBoxedEggCount(const PCBoxes *pcBoxes);
u32 GetBoxedPokemonData(const PCBoxes *pcBoxes, u32 boxIndex, u32 pokemonBoxLocationIndex, enum PokemonDataParam pokemonData, void *dest);
void SetBoxedPokemonDataWithSave(PCBoxes *pcBoxes, u32 boxIndex, u32 pokemonBoxLocationIndex, enum PokemonDataParam pokemonData, void *value);
BoxPokemon *GetBoxedPokemonFrom(const PCBoxes *pcBoxes, u32 param1, u32 param2);
void sub_02079CD8(PCBoxes *pcBoxes, u32 param1);
BOOL sub_02079CFC(const PCBoxes *pcBoxes, u32 param1);
u32 sub_02079D20(const PCBoxes *pcBoxes);

#endif // POKEPLATINUM_UNK_020797C8_H
