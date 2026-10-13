#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223F1B4_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223F1B4_H

// One BG affine-parameter entry streamed to the G2 registers by DMA.
typedef struct {
    u16 bg2PA;
    u16 bg2PB;
    u16 bg2PC;
    u16 bg2PD;
    u32 bg2X;
    u32 bg2Y;
    u16 bg3PA;
    u16 bg3PB;
    u16 bg3PC;
    u16 bg3PD;
    u32 bg3X;
    u32 bg3Y;
} FrontierFacilitiesAffineEntry;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223F1B4_H
