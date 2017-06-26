#include "my_list.h"
#pragma once
#define TRUE        (0)
#define FALSE       (1)
#define SCENE_DEBUG 100
#define SCENE_DEMO  0
#define INIT_GAME   100
#define PALYER_MODE 200
#define HIT         300
#define STAND       400
#define DOUBLE      500
#define PLAYER_LOSE 600
#define PLAYER_WIN  700
#define DRAW        800
#define RESULT      900
#define DEF_CREDITS 1000


int     is_finish       (void);
void    initialize      (void);
void    finalize        (void);
void    show_all_card   (void);
void    exec            (void);
void    game_init        (void);
int     load_credit     (void);
int     get_score       (list lst,int firstCardOnly);
