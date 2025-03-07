#ifndef POKEPLATINUM_STRUCT_OV16_0225E300_H
#define POKEPLATINUM_STRUCT_OV16_0225E300_H

#include "struct_decls/battle_system.h"
#include "struct_defs/pokemon_sprite.h"

#include "battle/struct_ov16_0225BFFC_decl.h"

typedef struct {
    BattleSystem *unk_00;
    BattlerData *unk_04;
    PokemonSprite *unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F[1];
} UnkStruct_ov16_0225E300;

#endif // POKEPLATINUM_STRUCT_OV16_0225E300_H
