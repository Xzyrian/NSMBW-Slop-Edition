/* smb3.h - the SMB3 port (SMB3Disassembly/port) as the runtime sees it.
 *
 * Everything SMB3 lives under SMB3Disassembly/: the disassembly (smb3.asm, PRG/, CHR/) is the
 * source; tools/build_smb3.py assembles and recompiles it into out/; this folder is the machine
 * under it (nes_*.c), native code inside it (smb3_game.c, hooks.txt) and this glue (smb3_main.c).
 *
 * Flow (rt_gamesetup.c): Game Select (SMB3) -> File Select (SMB3's own three files) -> character
 * select -> Start Game: SMB3 on the map of that file (World 1 for a new one). + opens the pause
 * menu (rt_menu.c): Continue / Save / Save & Quit / Quit; quitting goes to the title. */
#pragma once
#include <stdint.h>

void smb3_enter(int file);          /* start SMB3 with save file 0-2 */
void smb3_input(uint32_t remote);   /* player 1's Wii Remote buttons (held sideways), every frame */
void smb3_frame(void);              /* one frame of SMB3 (rt_menu.c, once per drawn frame; not while paused) */
void smb3_draw(void);               /* the SMB3 screen over everything (640 x 480 UI space) */
void smb3_audio(int16_t *lr, int frames);   /* the sound while SMB3 runs (32 kHz stereo): replaces the game's */
int  smb3_active(void);
const char *smb3_status(void);      /* why SMB3 stopped (an error), or NULL */
/* the pause menu */
void smb3_set_paused(int on);
int  smb3_paused(void);
int  smb3_save(void);               /* the progress to its file; 1 = saved */
void smb3_quit(void);               /* leave SMB3; the setup scene goes on to the title */
int  smb3_take_quit(void);          /* (rt_gamesetup.c) quit was chosen: once */
/* save files and presence */
const char *smb3_file_summary(int file);    /* "World 3", or NULL for an empty file */
int smb3_file_info(int file, int *world, int *lives);   /* 1: the file exists (its world 0-8, lives) */
int smb3_file_copy(int from, int to);        /* the File Select's Copy / Delete */
int smb3_file_delete(int file);
void smb3_presence(char *out, int n);       /* Discord: what is being played */
/* the prototype stage (smb3_stage.c, smb3_stage.h): NSMBW players in SMB3's 1-1 */
int  smb3_stage_on(void);                                    /* that stage is running */
int  smb3_stage_suppress_actors(void);                       /* (gm_d_actorcreate.c) the shell course's actors: not spawned */
int  smb3_stage_unit(uint32_t x, uint32_t y, uint64_t *flags);   /* (gm_bg.c) 1: the unit at (x, y) is SMB3's, in *flags */
