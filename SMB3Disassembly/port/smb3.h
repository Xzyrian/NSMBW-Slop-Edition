/* smb3.h - entry point of the SMB3 port (SMB3Disassembly/port).
 *
 * Everything SMB3 lives under SMB3Disassembly/: the original disassembly (smb3.asm, PRG/, CHR/)
 * is the reference source, this folder is the C port that runs inside the NSMBW runtime. The
 * runtime only talks to SMB3 through this header.
 *
 * Status: stub. The title menu's Game > SMB3 enters it (rt_menu.c); nothing is ported yet. */
#pragma once
#include <stdint.h>

void smb3_enter(void);          /* the menu chose SMB3 */
void smb3_frame(void);          /* once per frame while SMB3 is up */
void smb3_leave(void);          /* back to the menu (or the title was left) */
int  smb3_active(void);
const char *smb3_status(void);  /* one line for the placeholder screen */
