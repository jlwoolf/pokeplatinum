#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_GAME_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_GAME_H

#include <nnsys.h>

#include "struct_decls/struct_02012744_decl.h"

#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_animation_decl.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_context.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet_queue.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_3d_object.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_model.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_sequence_state.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_balloon_decl.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_gauge.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_pop_effect.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_confetti_manager.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_rank_icon.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_packet.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_balloon_sprites.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_balloons.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_opponent_balloons.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_display.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_intro_banner.h"

#include "bg_window.h"
#include "camera.h"
#include "g3d_pipeline.h"
#include "message.h"
#include "palette.h"
#include "particle_system.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task_manager.h"

typedef struct WiFiLobbyMinigameBalloonGame_t {
    WiFiLobbyMinigameBalloonContext *unk_00; // Shared context for the minigame.
    int unk_04; // Net ID of the winning player.
    u32 unk_08; // Number of score packets received.
    u32 unk_0C[4]; // Score per player slot.
    WiFiLobbyMinigameIntroAnimation *unk_1C; // Intro animation.
    int unk_20; // Intro sequence state.
    SpriteSystem *unk_24; // Sprite system.
    SpriteManager *unk_28; // Sprite manager.
    BgConfig *unk_2C; // Background configuration.
    Window unk_30[5]; // Text windows.
    MessageLoader *messageLoader;
    StringTemplate *stringTemplate;
    String *unk_88; // Scratch string for text rendering.
    PaletteData *paletteData;
    FontOAMManager *fontOAMManager;
    SysTask *drawTask;
    G3DPipelineBuffers *pipeline;
    Camera *camera1;
    Camera *camera2;
    ParticleSystem *particleSystem;
    NNSFndAllocator allocator;
    WiFiLobbyMinigameBalloonSequenceState sequenceState;
    WiFiLobbyMinigameBalloonBalloon *balloon;
    WiFiLobbyMinigameBalloonPlayerModel playerModel;
    WiFiLobbyMinigameBalloon3DObject balloon3DObject;
    WiFiLobbyMinigameBalloonScoreGauge scoreGauge;
    WiFiLobbyMinigameBalloonPlayerBalloonSprites playerBalloonSprites;
    WiFiLobbyMinigameBalloonPlayerBalloons playerBalloons;
    WiFiLobbyMinigameBalloonOpponentBalloons opponentBalloons;
    WiFiLobbyMinigameBalloonScoreDisplay scoreDisplay;
    WiFiLobbyMinigameBalloonIntroBanner introBanner;
    WiFiLobbyMinigameBalloonPacketQueue sendQueue;
    WiFiLobbyMinigameBalloonPacketQueue receiveQueues[4];
    WiFiLobbyMinigameBalloonPacket pendingSendPacket;
    WiFiLobbyMinigameBalloonPacket pendingReceivePacket;
    int receiveQueueWriteIndex[4];
    int receiveQueueReadIndex[4];
    int sendQueueWriteIndex;
    int sendQueueReadIndex;
    WiFiLobbyMinigameBalloonScorePacket scorePackets[8];
    int scorePacketReadIndex;
    int scorePacketWriteIndex;
    u32 gameTimer;
    int gameStarted;
    int gameEnded;
    int readyReceived;
    int sendCooldown;
    int balloonLevel;
    int gaugeActive;
    int popCount;
    int syncState;
    int syncId;
    WiFiLobbyMinigameBalloonPopEffect popEffects[40];
    WiFiLobbyMinigameBalloonConfettiManager confetti;
    WiFiLobbyMinigameBalloonRankIcon rankIcons[5];
    s32 localScore;
    u32 frameCounter;
} WiFiLobbyMinigameBalloonGame;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_GAME_H
