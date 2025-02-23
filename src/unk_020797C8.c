#include "unk_020797C8.h"

#include <nitro.h>
#include <string.h>

#include "message.h"
#include "pokemon.h"
#include "savedata.h"
#include "strbuf.h"


static const u16 BOX_WIDTH = 6, BOX_HEIGHT = 5, BOX_COUNT = 18;

typedef struct PCBoxes {
    u32 unk_00;
    BoxPokemon boxedPokemonArray[18][30];
    u16 unk_10E4[18][20];
    u8 boxes[18];
    u8 unk_13C6;
} PCBoxes;

static void sub_020797DC(PCBoxes *pcBoxes);

void PCBoxes_Init(PCBoxes *pcBoxes)
{
    sub_020797DC(pcBoxes);
    SaveData_SetFullSaveRequired();
}

u32 PCBoxes_SaveSize(void)
{
    return sizeof(PCBoxes);
}

static void sub_020797DC(PCBoxes *pcBoxes)
{
    u32 boxIndex, pokemonBoxLocationIndex;
    MessageLoader *v2;

    for (boxIndex = 0; boxIndex < BOX_COUNT; boxIndex++) {
        for (pokemonBoxLocationIndex = 0; pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH); pokemonBoxLocationIndex++) {
            BoxPokemon_Init(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex]));
        }
    }

    //This pokemonBoxLocationIndex might be doing something different?
    for (boxIndex = 0, pokemonBoxLocationIndex = 0; boxIndex < BOX_COUNT; boxIndex++) {
        pcBoxes->boxes[boxIndex] = pokemonBoxLocationIndex++;

        if (pokemonBoxLocationIndex >= 16) {
            pokemonBoxLocationIndex = 0;
        }
    }

    pcBoxes->unk_13C6 = 0;
    v2 = MessageLoader_Init(1, 26, 18, 0);

    if (v2) {
        for (boxIndex = 0; boxIndex < BOX_COUNT; boxIndex++) {
            MessageLoader_Get(v2, 6 + boxIndex, pcBoxes->unk_10E4[boxIndex]);
        }

        MessageLoader_Free(v2);
    }

    pcBoxes->unk_00 = 0;
}

BOOL sub_02079868(PCBoxes *pcBoxes, BoxPokemon *boxedPokemon)
{
    u32 v0;

    v0 = pcBoxes->unk_00;

    do {
        sub_0207896C(boxedPokemon);

        if (sub_020798A0(pcBoxes, v0, boxedPokemon)) {
            SaveData_SetFullSaveRequired();
            return 1;
        }

        if (++v0 >= 18) {
            v0 = 0;
        }
    } while (v0 != pcBoxes->unk_00);

    return 0;
}

BOOL sub_020798A0(PCBoxes *pcBoxes, u32 boxIndex, BoxPokemon *boxedPokemon)
{
    u32 pokemonBoxLocationIndex;

    sub_0207896C(boxedPokemon);
    BoxPokemon_SetShayminForm(boxedPokemon, 0);

    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    for (pokemonBoxLocationIndex = 0; pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH); pokemonBoxLocationIndex++) {
        if (BoxPokemon_GetValue(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex]), MON_DATA_SPECIES, NULL) == 0) {
            pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex] = *boxedPokemon;
            SaveData_SetFullSaveRequired();
            return 1;
        }
    }

    return 0;
}

BOOL sub_02079914(PCBoxes *pcBoxes, u32 boxIndex, u32 pokemonBoxLocationIndex, BoxPokemon *boxedPokemon)
{
    sub_0207896C(boxedPokemon);
    BoxPokemon_SetShayminForm(boxedPokemon, 0);

    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    if ((boxIndex < BOX_COUNT) && (pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH))) {
        pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex] = *boxedPokemon;
        SaveData_SetFullSaveRequired();
        return 1;
    } else {
        GF_ASSERT(0);
    }

    return 0;
}

void sub_02079968(PCBoxes *pcBoxes, u32 boxIndex, u32 pokemonBoxLocationIndex)
{
    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    if ((pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH)) && (boxIndex < BOX_COUNT)) {
        BoxPokemon_Init(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex]));
        SaveData_SetFullSaveRequired();
    } else {
        GF_ASSERT(0);
    }
}

u32 sub_0207999C(const PCBoxes *pcBoxes)
{
    return pcBoxes->unk_00;
}

u32 PCBoxes_FirstEmptyBox(const PCBoxes *pcBoxes)
{
    int boxIndex, pokemonBoxLocationIndex;

    boxIndex = pcBoxes->unk_00;

    while (TRUE) {
        for (pokemonBoxLocationIndex = 0; pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH); pokemonBoxLocationIndex++) {
            if (BoxPokemon_GetValue((BoxPokemon *)(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex])), MON_DATA_SPECIES_EXISTS, NULL) == 0) {
                return boxIndex;
            }
        }

        if (++boxIndex >= BOX_COUNT) {
            boxIndex = 0;
        }

        if (boxIndex == pcBoxes->unk_00) {
            break;
        }
    }

    return BOX_COUNT;
}

BOOL sub_020799F0(const PCBoxes *pcBoxes, int *boxIndexParam, int *pokemonBoxLocationIndexParam)
{
    int boxIndex, pokemonBoxLocationIndex;

    if (*boxIndexParam == 0xffffffff) {
        *boxIndexParam = pcBoxes->unk_00;
    }

    boxIndex = *boxIndexParam;
    pokemonBoxLocationIndex = *pokemonBoxLocationIndexParam;

    while (TRUE) {
        for (; pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH); pokemonBoxLocationIndex++) {
            if (BoxPokemon_GetValue((BoxPokemon *)(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex])), MON_DATA_SPECIES_EXISTS, NULL) == 0) {
                *boxIndexParam = boxIndex;
                *pokemonBoxLocationIndexParam = pokemonBoxLocationIndex;
                return 1;
            }
        }

        if (++boxIndex >= BOX_COUNT) {
            boxIndex = 0;
        }

        if (boxIndex == (*boxIndexParam)) {
            break;
        }

        pokemonBoxLocationIndex = 0;
    }

    return BOX_COUNT;
}

u32 GetBoxedPokemonCount(const PCBoxes *pcBoxes)
{
    int boxIndex, pokemonBoxLocationIndex;
    u32 pokemonCount = 0;

    for (boxIndex = 0; boxIndex < BOX_COUNT; boxIndex++) {
        for (pokemonBoxLocationIndex = 0; pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH); pokemonBoxLocationIndex++) {
            if (BoxPokemon_GetValue((BoxPokemon *)(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex])), MON_DATA_SPECIES_EXISTS, NULL) != 0) {
                pokemonCount++;
            }
        }
    }

    return pokemonCount;
}

void sub_02079A94(PCBoxes *pcBoxes, u32 boxIndex)
{
    if (boxIndex < BOX_COUNT) {
        pcBoxes->unk_00 = boxIndex;
        SaveData_SetFullSaveRequired();
    } else {
        GF_ASSERT(0);
    }
}

u32 sub_02079AA8(const PCBoxes *pcBoxes, u32 boxIndex)
{
    if (boxIndex < BOX_COUNT) {
        return pcBoxes->boxes[boxIndex];
    } else {
        GF_ASSERT(0);
        return 0;
    }
}

void sub_02079AC4(PCBoxes *pcBoxes, u32 boxIndex, u32 param2)
{
    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    if ((boxIndex < BOX_COUNT) && (param2 < (16 + 8))) {
        if (param2 >= 16) {
            param2 += 8;
        }

        pcBoxes->boxes[boxIndex] = param2;
        SaveData_SetFullSaveRequired();
    } else {
        GF_ASSERT(0);
    }
}

void sub_02079AF4(const PCBoxes *pcBoxes, u32 boxIndex, Strbuf *param2)
{
    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    if (boxIndex < BOX_COUNT) {
        Strbuf_CopyChars(param2, pcBoxes->unk_10E4[boxIndex]);
    } else {
        GF_ASSERT(0);
    }
}

void sub_02079B24(PCBoxes *pcBoxes, u32 boxIndex, const Strbuf *param2)
{
    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    if (boxIndex < BOX_COUNT) {
        Strbuf_ToChars(param2, pcBoxes->unk_10E4[boxIndex], 20);
        SaveData_SetFullSaveRequired();
    }
}

u32 GetPokemonCountInBox(const PCBoxes *pcBoxes, u32 boxIndex)
{
    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    if (boxIndex < BOX_COUNT) {
        int pokemonBoxLocationIndex;
        u32 pokemonCount = 0;

        for (pokemonBoxLocationIndex = 0; pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH); pokemonBoxLocationIndex++) {
            if (BoxPokemon_GetValue((BoxPokemon *)(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex])), MON_DATA_SPECIES_EXISTS, NULL)) {
                pokemonCount++;
            }
        }

        return pokemonCount;
    } else {
        GF_ASSERT(0);
    }

    return 0;
}

u32 GetEggCountInBox(const PCBoxes *pcBoxes, u32 boxIndex)
{
    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    if (boxIndex < BOX_COUNT) {
        int pokemonBoxLocationIndex;
        u32 eggCount = 0;

        for (pokemonBoxLocationIndex = 0; pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH); pokemonBoxLocationIndex++) {
            if (BoxPokemon_GetValue((BoxPokemon *)(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex])), MON_DATA_SPECIES_EXISTS, NULL)) {
                if (BoxPokemon_GetValue((BoxPokemon *)(&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex])), MON_DATA_IS_EGG, NULL) == 0) {
                    eggCount++;
                }
            }
        }

        return eggCount;
    } else {
        GF_ASSERT(0);
    }

    return 0;
}

u32 GetTotalBoxedEggCount(const PCBoxes *pcBoxes)
{
    u32 eggCount, boxIndex;

    for (boxIndex = 0, eggCount = 0; boxIndex < BOX_COUNT; boxIndex++) {
        eggCount += GetEggCountInBox(pcBoxes, boxIndex);
    }

    return eggCount;
}

u32 GetBoxedPokemonData(const PCBoxes *pcBoxes, u32 boxIndex, u32 pokemonBoxLocationIndex, enum PokemonDataParam pokemonData, void *dest)
{
    GF_ASSERT((boxIndex < BOX_COUNT) || (boxIndex == 0xffffffff));
    GF_ASSERT(pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH));

    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    return BoxPokemon_GetValue((BoxPokemon *)(&pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex]), pokemonData, dest);
}

void SetBoxedPokemonDataWithSave(PCBoxes *pcBoxes, u32 boxIndex, u32 pokemonBoxLocationIndex, enum PokemonDataParam pokemonData, void *value)
{
    GF_ASSERT((boxIndex < BOX_COUNT) || (boxIndex == 0xffffffff));
    GF_ASSERT(pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH));

    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    BoxPokemon_SetValue((BoxPokemon *)(&pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex]), pokemonData, value);
    SaveData_SetFullSaveRequired();
}

BoxPokemon *GetBoxedPokemonFrom(const PCBoxes *pcBoxes, u32 boxIndex, u32 pokemonBoxLocationIndex)
{
    GF_ASSERT((boxIndex < BOX_COUNT) || (boxIndex == 0xffffffff));
    GF_ASSERT(pokemonBoxLocationIndex < (BOX_HEIGHT * BOX_WIDTH));

    if (boxIndex == 0xffffffff) {
        boxIndex = pcBoxes->unk_00;
    }

    return (BoxPokemon *)&(pcBoxes->boxedPokemonArray[boxIndex][pokemonBoxLocationIndex]);
}

void sub_02079CD8(PCBoxes *pcBoxes, u32 param1)
{
    GF_ASSERT(param1 < 8);

    pcBoxes->unk_13C6 |= (1 << param1);
    SaveData_SetFullSaveRequired();
}

BOOL sub_02079CFC(const PCBoxes *pcBoxes, u32 param1)
{
    GF_ASSERT(param1 < 8);

    return (pcBoxes->unk_13C6 & (1 << param1)) != 0;
}

u32 sub_02079D20(const PCBoxes *pcBoxes)
{
    u32 v0, v1;

    for (v0 = 0, v1 = 0; v0 < 8; v0++) {
        if (sub_02079CFC(pcBoxes, v0)) {
            v1++;
        }
    }

    return v1;
}
