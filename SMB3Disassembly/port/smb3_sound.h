/* smb3_sound.h - SMB3's songs and sound effects, rendered into NSMBW's formats (smb3_sound.c) */
#pragma once
#include <stdint.h>
enum { SND_M1, SND_M2, SND_PLAYER, SND_LEVEL1, SND_LEVEL2, SND_MAP, SND_PAUSE };   /* (SMB3's sound queues) */
#define SMB3_SND_MAX 128
typedef struct {
    int kind, id, fast, ok;                       /* (fast: Music_RestH_Off $10 - after the time warning) */
    char name[40];                                /* the file: smb3_m1_XX.brstm, smb3_m2[f]_XX.brstm, smb3_sfx_K_XX.rwav */
    char label[32];                               /* its name in the sound archive: SMB3_M1_XX, SMB3_M2[F]_XX, SMB3_SE_<queue>_XX */
    int sound_id;                                 /* its sound ID in the expanded archive (-1: none) */
    int samples, loop, loop_len;                  /* 32 kHz; loop: its start (-1: none) */
    uint32_t bytes;
} smb3_snd_t;
int smb3_sound_render(const char *dir);           /* (build time) the files made into dir - 0 ok */
int smb3_sound_files(const char *root);           /* (start) the game files <root>/sound/smb3 - how many */
uint8_t *smb3_brsar_expand(const uint8_t *o, uint32_t n, uint32_t *out_n);   /* NSMBW's sound archive with SMB3's sounds after its own (malloc) */
int smb3_snd_id(int kind, int id, int fast);      /* (the expanded archive) a sound's ID, -1 none */
int smb3_snd_group(void);                         /* GROUP_SMB3's ID, -1 none */
const smb3_snd_t *smb3_snd_find(int kind, int id, int fast);   /* (NULL: none) */
int smb3_snd_count(void);
const smb3_snd_t *smb3_snd_at(int i);
const char *smb3_snd_dir(void);
extern int smb3_sound_rendering;                  /* (rendering: SMB3's engine runs as it is) */
