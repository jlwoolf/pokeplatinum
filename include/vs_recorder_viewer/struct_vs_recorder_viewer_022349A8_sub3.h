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
        VsRecorderViewerTransferProfileData unk_00_val1;
        VsRecorderViewerTransferBoxData unk_00_val2;
        VsRecorderViewerRankingsUploadProfile unk_00_val3;
        VsRecorderViewerTransferRecordData *unk_00_val4;
        VsRecorderViewerTransferPlayTime unk_00_val5;
        VsRecorderViewerTransferValue unk_00_val6;
    };
    union {
        struct {
            u8 unk_00;
            u8 unk_01;
            u8 unk_02[2];
        } val1;
        struct {
            u16 unk_00;
            u16 unk_02;
        } val2;
        struct {
            u64 unk_00;
        } val3;
    } unk_21C;
} VsRecorderViewerTransferPayload;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022349A8_SUB3_H
