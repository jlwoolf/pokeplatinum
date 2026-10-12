#ifndef POKEPLATINUM_FIELDMAP_021D5EB8_H
#define POKEPLATINUM_FIELDMAP_021D5EB8_H

#include "field/field_system_decl.h"
#include "fieldmap/struct_field_map_weather_decl.h"
#include "fieldmap/struct_weather_manager_decl.h"

FieldMapWeather *FieldMap_021D5EB8(FieldSystem *fieldSystem);
void FieldMap_021D5EF8(FieldMapWeather *param0);
void FieldMap_021D5F24(FieldMapWeather *param0, int param1);
BOOL FieldMap_021D5F7C(FieldMapWeather *param0, int param1);
u32 FieldMap_021D5FE0(FieldMapWeather *param0);
WeatherManager *FieldMap_021D6364(FieldSystem *fieldSystem);
void FieldMap_021D63A4(WeatherManager **param0);
BOOL FieldMap_021D6418(WeatherManager *param0, int param1, int param2);
int FieldMap_021D64D0(WeatherManager *param0, int param1);

#endif // POKEPLATINUM_FIELDMAP_021D5EB8_H
