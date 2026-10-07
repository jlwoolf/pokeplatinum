#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_MODEL_MANAGER_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_MODEL_MANAGER_H

#include <nnsys.h>

#include "footprint_stamp/struct_footprint_stamp_model_decl.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_data.h"
#include "footprint_stamp/struct_footprint_stamp_slot.h"
#include "footprint_stamp/struct_footprint_stamp_fade.h"

typedef struct {
    FootprintStampCameraAnimData unk_00; // Data for the currently playing camera animation.
    FootprintStampFade unk_B0; // Screen-brightness fade state.
    FootprintStampModel *unk_B4[128]; // All live footprint models, indexed by slot.
    FootprintStampModel *unk_2B4[128]; // Scratch list used when sorting models for drawing.
    NNSG3dResTex *unk_4B4[32]; // Textures queued for upload to VRAM.
    u32 unk_534[2]; // Bitfield of allocated model slots.
    FootprintStampSlot unk_53C[128]; // Per-slot reference counts.
    u8 unk_73C; // Camera animation currently playing.
    u8 unk_73D; // Camera animation requested to start.
    u8 unk_73E; // Set when the current camera animation has finished.
    u8 unk_73F; // Number of players currently in the lobby.
    u8 unk_740; // Whether a master-brightness change is pending.
    s16 unk_742; // Pending master-brightness value.
} FootprintStampModelManager;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_MODEL_MANAGER_H
