#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022349A8_SUB3_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022349A8_SUB3_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub3.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub5.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223D518_sub1.h"

typedef struct {
    union {
        VsRecorderViewerTransferProfileData profilePhotoData;
        VsRecorderViewerTransferBoxData boxData;
        VsRecorderViewerRankingsUploadProfile rankingsProfile;
        VsRecorderViewerTransferRecordData *recordData;
        VsRecorderViewerTransferPlayTime playTime;
        VsRecorderViewerTransferValue value;
    };
    union {
        struct {
            u8 id;
            u8 box;
            u8 unused_02[2];
        } val1;
        struct {
            u16 id;
            u16 unused_02;
        } val2;
        struct {
            u64 value;
        } val3;
    } uploadParams;
} VsRecorderViewerTransferPayload;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022349A8_SUB3_H
