#ifndef POKEPLATINUM_IMAGE_CLIP_APP_0225A428_H
#define POKEPLATINUM_IMAGE_CLIP_APP_0225A428_H

#include "image_clip_app/struct_image_clip_app_02256BAC.h"
#include "image_clip_app/struct_image_clip_app_0225A428.h"

void ContestScoreDisplay_Init(ContestScoreDisplay *param0, ContestScoreDisplayTemplate *param1, int param2);
void ContestScoreDisplay_Free(ContestScoreDisplay *param0);
void ContestScoreDisplay_CommitScore(ContestScoreDisplay *param0);
void ContestScoreDisplay_DrawMessage(ContestScoreDisplay *param0, int param1, int param2, int param3);
s32 ContestScoreDisplay_DrawMessageWithString(ContestScoreDisplay *param0, int param1, int param2, int param3);
void ContestScoreDisplay_FreeMessageString(ContestScoreDisplay *param0);
void ContestScoreDisplay_SetVisibleIcons(ContestScoreDisplay *param0, int param1);
int ContestScoreDisplay_GetScore(const ContestScoreDisplay *param0);
void ContestScoreDisplay_SetScoreTimer(ContestScoreDisplay *param0, int param1);
BOOL ContestScoreDisplay_IsScoreAnimationDone(const ContestScoreDisplay *param0);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_0225A428_H
