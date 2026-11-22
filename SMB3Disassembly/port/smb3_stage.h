/* smb3_stage.h - the prototype stage (smb3_stage.c): NSMBW players in SMB3's 1-1. Needs rt.h. */
#pragma once
int  smb3_stage_begin(ppc_context *ctx, uint8_t *base);   /* (character select, Start Game) load 1-1, start the stage; 0 = failed */
void smb3_stage_player_draw(ppc_context *ctx, uint8_t *base, uint32_t player);   /* (dAcPy_c::draw) */
void smb3_stage_player_sensors(uint32_t player);                 /* (after dAcPy_c::setBcData) the sensors at the players' scale */
