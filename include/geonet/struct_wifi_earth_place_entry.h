#ifndef POKEPLATINUM_STRUCT_WIFI_EARTH_PLACE_ENTRY_H
#define POKEPLATINUM_STRUCT_WIFI_EARTH_PLACE_ENTRY_H

// A single world-place entry from member 18 of wifi_earth_place.narc. Entries
// whose type is 2 have no coordinates and are skipped; every other entry places
// a marker for the country at the same index.
typedef struct WiFiEarthPlaceEntry {
    u16 type;
    s16 longitude;
    s16 latitude;
} WiFiEarthPlaceEntry;

#endif // POKEPLATINUM_STRUCT_WIFI_EARTH_PLACE_ENTRY_H
