/* gm_d_nand.c - dNandThread_c's module replacements: existence checks, save-command queuing,
 * JSON save/load and file deletion (track B, gm_i2.h, docs/DECOMP.md, instance 2).
 * The staging buffer, NAND objects and paths remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define NAND_PATH           (0x81850000u - 21223)
#define NAND_ERROR_MANAGER  (0x81860000u - 5004)
#define NAND_STACK_GUARD    (0x81860000u - 300)
#define NAND_SAVE_BUFFER    (0x80360000u - 9024)
#define NAND_SERIALIZED     16288

static void nand_existCheck(GM_CTX, gptr self) {
    I2_FN(0x818118ECu);
    R(4) = gm_frame_sp + 11; NV_R(30, self); R(3) = 0x81860000u; R(3) = gm_u32(NAND_STACK_GUARD);
    gm_set_u32(gm_frame_sp + 12, R(3)); R(3) = 0x81850000u; NV_R(28, R(3) - 21223);
    R(3) = R(28); BL(0x81811928u, fn_801DAE70); NV_R(29, R(3));
    if (CMPS(R(3), -12) == 0) {
        R(3) = R(28) + 53; R(4) = gm_frame_sp + 11; BL(0x81811940u, fn_801DAE70); NV_R(29, R(3));
    }
    R(3) = self; R(4) = R(29); BL(0x81811950u, fn_800CFB30);
    R(3) = gm_u32(self + 120);
    if (CMPU(R(3), 0) == 0) {
        R(3) = gm_u8(gm_frame_sp + 11) & 0xFF; R(3) ^= 1; R(3) = R(29) | R(3);
        R(3) = cntlzw(R(3)); R(3) = i2_rotl(R(3), 27) & 0x7FFFFFFu; gm_set_u8(self + 124, R(3));
    }
    R(3) = 0x81860000u; R(3) = gm_u32(NAND_STACK_GUARD); R(4) = gm_u32(gm_frame_sp + 12);
    if (CMPU(R(3), R(4)) != 0) BL(0x818119ACu, mfn_81844FCC);
}

static void nand_cmdSave(GM_CTX, gptr self, gptr source) {
    I2_FN(0x81811A10u);
    NV_R(28, self + 84); NV_R(29, self); R(3) = R(28); NV_R(27, source);
    BL(0x81811A40u, OSTryLockMutex_801B3080); NV_R(30, R(3));
    if (CMPU(R(3), 0) != 0) {
        R(3) = 0; gm_set_u32(self + 120, R(3)); R(3) = 0x80360000u; R(4) = R(3) - 9024; R(5) = 4;
        CMPU(source, R(4)); gm_set_u32(self + 116, R(5));
        if (!CR_BIT(ctx, 2)) {
            R(3) = source - 1; R(5) = NAND_SERIALIZED; R(4)--; ctx->ctr = R(5);
            do {
                R(3)++; R(5) = gm_u8(R(3)); R(4)++; gm_set_u8(R(4), R(5));
                if (--ctx->ctr) GM_LOOP(); else break;
            } while (1);
        }
        R(3) = R(28); BL(0x81811A90u, OSUnlockMutex_801B2F40);
        R(3) = self + 108; BL(0x81811A98u, fn_801B3230);
    }
    NONZERO(3, 3, R(30));
}

static void nand_deleteFile(GM_CTX, gptr self) {
    I2_FN(0x818120C0u);
    NV_R(30, self); R(3) = 0x81850000u; R(3) = NAND_PATH; BL(0x818120E0u, fn_801D87E0);
    R(4) = R(3); R(3) = self; BL(0x818120ECu, fn_800CFB30);
}

static uint32_t nand_load(GM_CTX, gptr self) {
    I2_FN(0x81811EB4u);
    R(4) = NAND_SERIALIZED; NV_R(30, self); R(3) = 0x81860000u; R(3) = gm_u32(NAND_STACK_GUARD);
    gm_set_u32(gm_frame_sp + 52, R(3)); R(3) = NAND_SAVE_BUFFER - 1; ctx->ctr = R(4); R(4) = 0;
    do {
        R(3)++; gm_set_u8(R(3), R(4)); if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    R(3) = 0x81850000u; R(4) = 0x81860000u; NV_R(26, NAND_PATH); NV_R(27, NAND_ERROR_MANAGER);
    R(3) = R(26); R(4) = R(27); R(5) = 1; NV_R(29, 1); BL(0x81811F28u, fn_801D95B0);
    CMPU(R(3), 0); NV_R(28, 0);
    if (!CR_BIT(ctx, 2)) {
        R(3) = R(26) + 101; R(4) = R(27); R(5) = 1; BL(0x81811F44u, fn_801D95B0); CMPU(R(3), 0);
        if (!CR_BIT(ctx, 2)) {
            R(3) = 0x81860000u; R(5) = 0x81850000u; R(4) = R(3) - 5004; R(3) = R(5) - 21223;
            R(3) += 53; R(5) = 1; BL(0x81811F68u, fn_801D95B0); NV_R(28, R(3));
        }
    }
    R(3) = self; R(4) = R(28); BL(0x81811F78u, fn_800CFB30);
    R(3) = gm_u32(self + 120);
    if (CMPU(R(3), 0) == 0) {
        R(3) = NAND_SAVE_BUFFER; NV_R(28, 3); NV_R(29, R(3) + 8992);
        do {
            R(3) = R(29) - 7296; BL(0x81811F9Cu, hle_mod_fn_800CDED0);
            R(3) = R(29); BL(0x81811FA4u, hle_mod_fn_800CDED0);
            R(28)--; CMPU(R(28), 0); R(29) += 2432;
            if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
        } while (1);
        R(3) = 8; R(4) = 255; gm_set_u16(gm_frame_sp + 20, R(3)); R(5) = 0x81810000u;
        gm_set_u8(gm_frame_sp + 40, R(4)); R(4) = 0x81850000u; gm_set_u32(gm_frame_sp + 44, R(3));
        R(3) = 2602; gm_set_u16(gm_frame_sp + 48, R(3)); R(3) = R(4) + 8516; gm_set_u32(gm_frame_sp + 16, R(3));
        R(3) = 4; R(4) = 0x80360000u; NV_R(29, 0); gm_set_u8(gm_frame_sp + 50, R(3));
        R(3) = gm_frame_sp + 16; R(4) -= 25408; R(6) = R(5) + 8448; R(5) = 16384; R(7) = self;
        gm_set_u8(gm_frame_sp + 22, R(29)); gm_set_u32(gm_frame_sp + 24, R(29));
        gm_set_u32(gm_frame_sp + 28, R(29)); gm_set_u32(gm_frame_sp + 32, R(29)); gm_set_u32(gm_frame_sp + 36, R(29));
        BL(0x8181201Cu, mfn_81838F14); NV_R(28, R(3));
        R(3) = NAND_ERROR_MANAGER; BL(0x8181202Cu, fn_801D9850); R(4) = R(3); R(3) = self; BL(0x81812038u, fn_800CFB30);
        if (CMPU(R(28), 0) == 0) {
            R(3) = 0x81850000u; R(4) = R(3) - 21223; R(3) = R(4) + 211; R(4) += 18;
            CR_SETBIT(ctx, 6, CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)); R(5) = 223; BL(0x8181205Cu, hle_OSReport);
            R(3) = NAND_SERIALIZED; R(4) = 0x80360000u; ctx->ctr = R(3); R(3) = R(4) - 9024; R(3)--; R(4) = 0;
            do {
                R(3)++; gm_set_u8(R(3), R(4)); if (--ctx->ctr) GM_LOOP(); else break;
            } while (1);
            NV_R(29, 1);
        }
    }
    R(3) = 0x81860000u; R(3) = gm_u32(NAND_STACK_GUARD); R(4) = gm_u32(gm_frame_sp + 52);
    if (CMPU(R(3), R(4)) != 0) BL(0x818120C0u, mfn_81844FCC);
    return R(29);
}

static uint32_t nand_save(GM_CTX, gptr self) {
    I2_FN(0x81811AC0u);
    R(4) = 0x81850000u; R(4) = NAND_PATH; NV_R(23, R(4) + 18); NV_R(24, R(4) + 249);
    NV_R(25, R(4) + 36); NV_R(26, R(4) + 165); NV_R(27, R(4) + 75); NV_R(28, gm_frame_sp + 296);
    NV_R(30, self); R(3) = 0x81860000u; R(3) = gm_u32(NAND_STACK_GUARD); gm_set_u32(gm_frame_sp + 500, R(3));

save_retry:
    R(3) = R(28); R(4) = 0; R(5) = 64; BL(0x81811B30u, mod_memset_81844D68);
    R(3) = R(27); R(4) = 60; R(5) = 0; BL(0x81811B40u, fn_801D84E0);
    if (CMPS(R(3), -8) != 0) { R(4) = R(3); R(29) = R(27); NV_R(22, 0); goto save_checkOpen; }
    R(3) = R(28); BL(0x81811B50u, fn_801DAAF0); R(4) = R(3); R(3) = self; BL(0x81811B5Cu, fn_800CFB30);
    R(3) = gm_u32(self + 120); CMPU(R(3), 0); if (!CR_BIT(ctx, 2)) goto save_fail_simple;
    R(3) = R(28); R(4) = R(26); BL(0x81811B74u, _Z6strcatPKcS0__802E1A3C);
    R(3) = R(28); R(4) = 60; R(5) = 0; NV_R(22, 0); BL(0x81811B88u, fn_801D84E0);
    if (CMPS(R(3), -8) != 0) { R(4) = R(3); R(29) = R(28); goto save_checkOpen; }
    R(3) = R(25); R(4) = 60; R(5) = 0; BL(0x81811BA0u, fn_801D84E0);
    R(4) = R(3); NV_R(22, 1); R(29) = R(25);

save_checkOpen:
    if (CMPS(R(4), -6) != 0) goto save_open;
    CR_SETBIT(ctx, 6, CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)); R(3) = R(24); R(4) = R(23); R(5) = 114; R(6) = R(29);
    BL(0x81811BE8u, hle_OSReport); R(3) = R(29); BL(0x81811BF0u, fn_801D87E0);
    R(4) = R(3); R(3) = self; BL(0x81811BFCu, fn_800CFB30); R(3) = gm_u32(self + 120);
    if (CMPU(R(3), 0) == 0) { GM_LOOP(); goto save_retry; }
    NV_R(28, 1); goto save_end;

save_open:
    R(3) = self; BL(0x81811C18u, fn_800CFB30); R(3) = gm_u32(self + 120); NV_R(28, 1);
    if (CMPU(R(3), 0) != 0) goto save_end;
    R(3) = 0x81860000u; NV_R(27, R(3) - 5004); R(3) = R(29); R(4) = R(27); R(5) = 2; BL(0x81811C40u, fn_801D95B0);
    R(4) = R(3); R(3) = self; BL(0x81811C4Cu, fn_800CFB30); R(3) = gm_u32(self + 120);
    if (CMPU(R(3), 0) != 0) {
        R(3) = R(29); BL(0x81811C60u, fn_801D87E0); R(4) = R(3); R(3) = self; BL(0x81811C6Cu, fn_800CFB30);
        goto save_end;
    }
    NV_R(28, gm_frame_sp + 360); R(4) = R(27); R(3) = R(28); R(5) = 140; BL(0x81811C84u, mod_memcpy_81844C38);
    R(3) = 0x81850000u + 17024; R(4) = 0; gm_set_u32(gm_frame_sp + 148, R(3)); R(3) = gm_frame_sp + 160; R(5) = 131;
    gm_set_u32(gm_frame_sp + 152, R(4)); gm_set_u32(gm_frame_sp + 156, R(4)); gm_set_u32(gm_frame_sp + 292, R(4));
    BL(0x81811CACu, mod_memset_81844D68); NV_R(27, gm_frame_sp + 148); R(3) = R(27); R(4) = R(28); BL(0x81811CBCu, mfn_8183B794);
    R(3) = 0x80360000u; R(4) = 0x81850000u; NV_R(28, gm_frame_sp + 360); R(6) = R(3) - 25408;
    R(3) = R(4) - 21223; R(5) = R(3) + 98; R(4) = R(27); R(3) = R(28); R(7) = 16384; BL(0x81811CE4u, mfn_8183C344);
    R(3) = R(28); BL(0x81811CECu, mfn_8180F618); NV_R(26, R(3)); R(3) = R(28); BL(0x81811CF8u, fclose_802DE91C);
    R(3) = R(27); BL(0x81811D00u, mfn_8183B7D4); R(4) = gm_u32(gm_frame_sp + 292); R(3) = self; BL(0x81811D0Cu, fn_800CFB30);
    if (CMPU(R(26), 0) == 0) goto save_fail;
    R(3) = gm_u32(self + 120); if (CMPU(R(3), 0) != 0) goto save_fail;
    R(4) = gm_u32(gm_frame_sp + 292); R(3) = self; BL(0x81811D2Cu, fn_800CFB30);
    R(3) = gm_u32(self + 120); if (CMPU(R(3), 0) != 0) goto save_fail;
    NV_R(28, gm_frame_sp + 84); R(4) = 0; R(3) = R(28); R(5) = 64; BL(0x81811D4Cu, mod_memset_81844D68);
    R(3) = R(28); BL(0x81811D54u, fn_801DAAF0); R(4) = R(3); R(3) = self; BL(0x81811D60u, fn_800CFB30);
    R(3) = gm_u32(self + 120); if (CMPU(R(3), 0) != 0) goto save_fail;
    if (CMPU(R(22), 0) == 0) {
        R(3) = 0x81850000u; R(3) = NAND_PATH; R(4) = R(3) + 113; R(3) = gm_frame_sp + 84;
        BL(0x81811D88u, _Z6strcatPKcS0__802E1A3C); goto save_rename;
    }
    NV_R(28, gm_frame_sp + 20); NV_R(27, gm_frame_sp + 84); R(3) = R(28); R(4) = R(27); BL(0x81811DA0u, strcpy_802E1938);
    R(3) = 0x81850000u; NV_R(26, R(3) - 21223); R(4) = R(26) + 126; R(3) = R(27); BL(0x81811DB4u, _Z6strcatPKcS0__802E1A3C);
    R(4) = R(26) + 188; R(3) = R(28); BL(0x81811DC0u, _Z6strcatPKcS0__802E1A3C);
    R(3) = R(27); R(4) = R(28); BL(0x81811DCCu, ISFS_Rename_80227040); BL(0x81811DD0u, nandConvertErrorCode_801DA570);
    if (CMPS(R(3), -12) != 0 && CMPU(R(3), 0) != 0) { R(3) = gm_frame_sp + 84; BL(0x81811DE8u, fn_801D87E0); }

save_rename:
    R(4) = gm_frame_sp + 84; R(3) = R(29); BL(0x81811DF4u, ISFS_Rename_80227040); BL(0x81811DF8u, nandConvertErrorCode_801DA570);
    R(4) = R(3); R(3) = self; BL(0x81811E04u, fn_800CFB30); R(3) = gm_u32(self + 120);
    if (CMPU(R(3), 0) == 0) {
        R(3) = 0x81850000u; R(4) = R(3) - 21223; R(3) = R(4) + 145; R(4) += 18;
        CR_SETBIT(ctx, 6, CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)); R(5) = 181; BL(0x81811EA8u, hle_OSReport);
        NV_R(28, 0); GM_LOOP(); goto save_cleanup;
    }

save_fail:
    R(3) = R(29); BL(0x81811E18u, fn_801D87E0); R(4) = R(3); R(3) = self; BL(0x81811E24u, fn_800CFB30);
    NV_R(28, 1); goto save_cleanup;

save_fail_simple:
    NV_R(28, 1); goto save_end;

save_cleanup:
    R(3) = gm_frame_sp + 360; R(4) = (uint32_t)-1; BL(0x81811E34u, mfn_8183C530);
    R(3) = gm_frame_sp + 148; R(4) = (uint32_t)-1; BL(0x81811E40u, mfn_8183B68C);

save_end:
    R(3) = 0x81860000u; R(3) = gm_u32(NAND_STACK_GUARD); R(4) = gm_u32(gm_frame_sp + 500);
    if (CMPU(R(3), R(4)) != 0) BL(0x81811EB4u, mfn_81844FCC);
    return R(28);
}

GM_HLE_VERIFIED_(mod_fn_800CEE90, GMV_IGNORE_POLLS, 0, 0) { nand_existCheck(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_800CF080, GMV_IGNORE_POLLS, 0, 0) { nand_cmdSave(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_800CF110, GMV_IGNORE_POLLS, 0, 0) { R(3) = nand_save(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_800CF590, GMV_IGNORE_POLLS, 0, 0) { R(3) = nand_load(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_800CF960, GMV_IGNORE_POLLS, 0, 0) { nand_deleteFile(GM_PASS, GM_ARG(0)); }
