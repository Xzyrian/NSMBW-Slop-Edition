/* smw.h - the SMW port (SMWDisassembly/port) as the runtime sees it.
 *
 * Everything SMW lives under SMWDisassembly/: the disassembly (smw.asm, bank_*.asm) is the
 * source; tools/build_smw.py assembles it with Asar and recompiles it (tools/recomp65816.py) into
 * out/; this folder is the SNES under it (snes_*.c) and this glue (smw_main.c).
 *
 * Flow (rt_gamesetup.c), as SMB3's first step: Game Select (SMW) -> File Select (SMW's own three
 * files, in NSMBW's cards) -> character select -> Start Game: SMW runs whole, recompiled, with its
 * own Mario - its title and file menu are passed unseen (that file, 1 player), so a new file
 * starts at the intro message, then Yoshi's House and the map. + opens the pause menu
 * (rt_menu.c): Continue / Save / Save & Quit / Quit. Silent for now (its SPC700 isn't run yet). */
#pragma once
#include <stdint.h>

void smw_enter(int file);           /* start SMW with save file 0-2 */
void smw_input(uint32_t remote);    /* player 1's Wii Remote buttons (held sideways), every frame */
void smw_frame(void);               /* one frame of SMW (rt_menu.c; not while paused) */
void smw_draw(void);                /* its screen over everything (640 x 480 UI space) */
void smw_audio(int16_t *lr, int frames);
int  smw_active(void);
const char *smw_status(void);       /* why SMW stopped (an error), or NULL */
void smw_set_paused(int on);
int  smw_paused(void);
int  smw_save(void);                /* SMW's save RAM to its file; 1 = written */
void smw_quit(void);
int  smw_take_quit(void);
/* SMW's files (its save RAM keeps three) for the File Select */
int  smw_file_info(int file, int *world, int *lives);   /* 1: the file exists */
const char *smw_file_summary(int file);
int  smw_file_copy(int from, int to);
int  smw_file_delete(int file);
void smw_presence(char *out, int n);
/* NSMBW players in SMW's levels (smw_stage.c; settings.ini smw_stage, default 1): SMW is held at a
   level's start and the level handed to an NSMBW stage */
int  smw_level_held(void);                  /* SMW has reached a level and waits there (smw_main.c) */
void smw_leave_level(int exit_mode);        /* the stage left: SMW out of its level to its map (OWLevelExitMode) */
int  smw_resume(void);                      /* (rt_gamesetup.c, the setup scene made) 1: SMW on again, to its map */
int  smw_cover(void);                       /* (rt_menu.c) 1: the screen black (a level held, the stage not up yet) */
int  smw_stage_on(void);
int  smw_stage_unit(uint32_t x, uint32_t y, uint64_t *flags);   /* (gm_bg.c) 1: the unit at (x, y) is SMW's */
int  smw_stage_suppress_actors(void);       /* (gm_d_actorcreate.c) the shell course's actors: not spawned */
