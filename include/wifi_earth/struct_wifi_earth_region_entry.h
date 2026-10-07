#ifndef POKEPLATINUM_STRUCT_WIFI_EARTH_REGION_ENTRY_H
#define POKEPLATINUM_STRUCT_WIFI_EARTH_REGION_ENTRY_H

// A region entry loaded from a country's wifi_earth_place.narc member. The
// first entry of each member is a header and is skipped.
typedef struct WiFiEarthRegionEntry_t {
    s16 longitude;
    s16 latitude;
} WiFiEarthRegionEntry;

#endif // POKEPLATINUM_STRUCT_WIFI_EARTH_REGION_ENTRY_H
