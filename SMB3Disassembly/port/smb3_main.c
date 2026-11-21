/* smb3_main.c - SMB3 port: lifecycle (stub). See smb3.h and README.md. */
#include "rt.h"
#include "smb3.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

static int active;
static uint64_t frames;

void smb3_enter(void) {
    active = 1; frames = 0;
    rt_log("smb3", "enter (stub: nothing ported yet)");
}
void smb3_frame(void) { if (active) frames++; }
void smb3_leave(void) {
    if (!active) return;
    active = 0;
    rt_log("smb3", "leave after %llu frames", (unsigned long long)frames);
}
int smb3_active(void) { return active; }
const char *smb3_status(void) { return "Nothing ported yet"; }
