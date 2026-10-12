#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_MODEL_MANAGER_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_MODEL_MANAGER_H

#include <nnsys.h>

#include "footprint_stamp/struct_footprint_stamp_model_decl.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_data.h"
#include "footprint_stamp/struct_footprint_stamp_slot.h"
#include "footprint_stamp/struct_footprint_stamp_fade.h"

typedef struct {
    FootprintStampCameraAnimData cameraAnim; // Data for the currently playing camera animation.
    FootprintStampFade fade; // Screen-brightness fade state.
    FootprintStampModel *models[128]; // All live footprint models, indexed by slot.
    FootprintStampModel *sortedModels[128]; // Scratch list used when sorting models for drawing.
    NNSG3dResTex *pendingTextures[32]; // Textures queued for upload to VRAM.
    u32 slotBitmap[2]; // Bitfield of allocated model slots.
    FootprintStampSlot slots[128]; // Per-slot reference counts.
    u8 cameraAnimState; // Camera animation currently playing.
    u8 pendingCameraAnim; // Camera animation requested to start.
    u8 cameraAnimFinished; // Set when the current camera animation has finished.
    u8 playerCount; // Number of players currently in the lobby.
    u8 isBrightnessPending; // Whether a master-brightness change is pending.
    s16 brightness; // Pending master-brightness value.
} FootprintStampModelManager;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_MODEL_MANAGER_H
