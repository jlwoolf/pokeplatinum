#ifndef POKEPLATINUM_STRUCT_VISUAL_COMPETITION_SCORES_H
#define POKEPLATINUM_STRUCT_VISUAL_COMPETITION_SCORES_H

typedef struct {
    u8 contestantIDs[4];
    u8 currentContestant;
    s16 scores[4];
} VisualCompetitionScores;

#endif // POKEPLATINUM_STRUCT_VISUAL_COMPETITION_SCORES_H
