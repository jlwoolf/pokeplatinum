#ifndef POKEPLATINUM_FOOTPRINT_STAMP_MODELS_H
#define POKEPLATINUM_FOOTPRINT_STAMP_MODELS_H

#include "footprint_stamp/struct_footprint_stamp_app_decl.h"
#include "footprint_stamp/struct_footprint_stamp_model_manager.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

#include "camera.h"
#include "narc.h"

void FootprintStampModels_Init(FootprintStampModelManager *param0, BOOL param1);
void FootprintStampModels_Free(FootprintStampModelManager *param0);
BOOL FootprintStampModels_Add(FootprintStampApp *param0, FootprintStampModelManager *param1, const FootprintStampEntry *param2, NARC *param3, NARC *param4, BOOL param5);
void FootprintStampModels_Update(FootprintStampModelManager *param0, Camera *camera, int param2, int param3);
void FootprintStampModels_Draw(FootprintStampModelManager *param0);
void FootprintStampModels_UpdateAnimations(FootprintStampModelManager *param0);
void FootprintStampModels_FlushTextures(FootprintStampModelManager *param0, int param1);

#endif // POKEPLATINUM_FOOTPRINT_STAMP_MODELS_H
