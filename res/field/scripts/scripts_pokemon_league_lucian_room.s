#include "macros/scrcmd.inc"
#include "res/text/bank/pokemon_league_lucian_room.h"

    .data

    ScriptEntry _000A
    ScriptEntry _00B7
    ScriptEntryEnd

_000A:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet 179, _00AC
    ScrCmd_0EA 0x108
    Message 0
    CloseMessage
    CallIfUnset 214, _007A
    CallIfSet 214, _0082
    CheckWonBattle 0x800C
    GoToIfEq 0x800C, FALSE, _00A6
    SetFlag 179
    PlayFanfare SEQ_SE_DP_KI_GASYAN
    RemoveObject 1
    CallIfUnset 214, _008A
    CallIfSet 214, _0098
    Message 1
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_007A:
    StartTrainerBattle TRAINER_ELITE_FOUR_LUCIAN
    Return

_0082:
    StartTrainerBattle TRAINER_ELITE_FOUR_LUCIAN_REMATCH
    Return

_008A:
    CreateJournalEvent LOCATION_EVENT_BEAT_ELITE_FOUR_MEMBER, TRAINER_ELITE_FOUR_LUCIAN, 0, 0, 0
    Return

_0098:
    CreateJournalEvent LOCATION_EVENT_BEAT_ELITE_FOUR_MEMBER, TRAINER_ELITE_FOUR_LUCIAN_REMATCH, 0, 0, 0
    Return

_00A6:
    BlackOutFromBattle
    ReleaseAll
    End

_00AC:
    Message 2
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_00B7:
    LockAll
    ApplyMovement LOCALID_PLAYER, _00DC
    WaitMovement
    PlayFanfare SEQ_SE_DP_KI_GASYAN
    ClearFlag 0x285
    AddObject 2
    SetVar 0x4001, 1
    ReleaseAll
    End

    .balign 4, 0
_00DC:
    MoveAction_012 2
    EndMovement
