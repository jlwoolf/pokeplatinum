#ifndef POKEPLATINUM_STRUCT_DANCE_SCORE_STATE_H
#define POKEPLATINUM_STRUCT_DANCE_SCORE_STATE_H

typedef struct {
    u8 contestantIDs[CONTEST_NUM_PARTICIPANTS];
    u8 round;
    u8 judgeVotes[CONTEST_NUM_PARTICIPANTS];
    s16 scores[4];
    u32 difficulty;
    u32 maxScore;
    u32 scorePerBeat;
    u32 bonus1;
    u32 bonus2;
    u32 beatDuration;
    u16 maxBeats;
    u8 roundCount;
    u8 contestRank;
} DanceScoreState;

#endif // POKEPLATINUM_STRUCT_DANCE_SCORE_STATE_H
