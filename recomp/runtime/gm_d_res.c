/* gm_d_res.c - dRes_c, the archive manager: setRes / deleteRes (the reference counts), getRes
 * (three overloads: the file, with its size, with its size and compression - a missing file
 * tried again as "<path>.LZ"), getResSilently (two), copyRes (two), syncAllRes and the lookups
 * getResInfo / newResInfo / getResInfoLoaded. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_res.cpp) and checked against the recompiled
 * USA rev 2 code (0x800DF080-0x800DF660). Register-exact (R(n)): the calls with their real return
 * addresses, the loops' back-edge polls, r11 left at the frame top where the PowerPC code's
 * __save_gpr / __restore_gpr leave it. Part 60 added the rest of d_res.cpp / d_res_info.cpp:
 * dRes_c's ctor / dtor / init, info_c (ctor / dtor / cleanup / set / setRes / loadRes) and the
 * archive search callback.
 *
 * dRes_c: +0 the info_c array, +4 its count (u16), +8 the callback. info_c (64 bytes): +0 the
 * name (32), +32 the reference count (u16), +36 the DVD command, +40 the EGG::Archive. */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

#define F_GET_INFO        0x800DF570u   /* dRes_c::getResInfo */
#define F_NEW_INFO        0x800DF600u   /* dRes_c::newResInfo */
#define F_GET_INFO_LOADED 0x800DF640u   /* dRes_c::getResInfoLoaded */
#define F_COPY_RES        0x800DF3A0u
#define F_INFO_SET        0x800DEAD0u   /* dRes_c::info_c::set */
#define F_INFO_CLEANUP    0x800DE9F0u   /* dRes_c::info_c::cleanup */
#define F_INFO_SETRES     0x800DEBA0u   /* dRes_c::info_c::setRes */
#define F_STRCMP          0x802E1AB4u
#define F_SNPRINTF        0x802E16E8u
#define F_MEMCPY          0x80004364u
#define F_CX_UNCOMP_LZ    0x801D8190u
#define F_CX_UNCOMP_SIZE  0x801D8150u
#define F_ARC_GET_FILE    0x802B76C0u   /* EGG::Archive::getFile(path, FileInfo *) */
#define F_ARC_ENTRY_ID    0x802B7760u   /* EGG::Archive::convertPathToEntryID */
#define F_ARC_GET_FAST    0x802B7770u   /* EGG::Archive::getFileFast(id, FileInfo *) */
#define SDA_LZ_FMT        30472         /* (r13 - : "%s.LZ") */
#define F_NEW_ARR         0x802B9250u   /* operator new[] */
#define F_OP_DELETE       0x802B9280u
#define F_CONSTRUCT_NEW_ARR 0x802DC7E0u
#define F_DESTROY_NEW_ARR 0x802DCB10u
#define F_INFO_LOADRES    0x800DEDB0u
#define F_VI_WAIT         0x801BCCF0u   /* VIWaitForRetrace */
#define F_ARC_BINARY      0x8016BE60u   /* mDvd_mountMemArchive_c::getArcBinary */
#define F_DVD_DESTROY     0x8016B7E0u   /* mDvd_command_c::destroy */
#define F_DVD_MOUNT_CREATE 0x8016BCC0u  /* mDvd_mountMemArchive_c::create */
#define F_DESTROY_FRM_HEAP 0x8016E740u  /* mHeap::destroyFrmHeap */
#define F_FRM_HEAP_TO_CUR 0x8016E9B0u   /* mHeap::createFrmHeapToCurrent */
#define F_RESTORE_HEAP    0x8016E980u   /* mHeap::restoreCurrentHeap */
#define F_ADJUST_FRM_HEAP 0x8016E760u   /* mHeap::adjustFrmHeap */
#define F_DC_STORE_NOSYNC 0x801AC500u
#define F_ARC_UNMOUNT     0x802B7680u
#define F_ARC_COUNT       0x802B7830u   /* EGG::Archive::countFile */
#define F_ARC_SEARCH      0x802B7A40u   /* EGG::Archive::searchInside */
#define F_ARC_FILE_ARRAY  0x802B78A0u   /* EGG::Archive::getFileArray */
#define F_HEAP_FREE       0x802B8F70u   /* EGG::Heap::free */
#define F_STRNCPY         0x802E19F8u
#define F_STRLEN          0x802DC69Cu
#define SDA_SET_CALLBACK  22096         /* dRes_c::mSetCallback */
#define F_RES_CHECK_REV   0x8023A860u   /* nw4r::g3d::ResFile::CheckRevision */
#define F_RES_INIT        0x8023A590u   /* nw4r::g3d::ResFile::Init */
#define F_RES_BIND        0x8023A350u   /* nw4r::g3d::ResFile::Bind */

/* ================================================================== the lookups */
/* getResInfo(name): the referenced info with that name */
static void rs_get_info(GM_CTX) {
    GM_FN(0x800DF570); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = gm_u16(R(3) + 4);
    R(30) = gm_u32(R(3));
    R(29) = 0;
    R(28) = R(4);
    goto test;
body:
    R(0) = gm_u16(R(30) + 32);
    if (cmps(ctx, (int32_t)R(0), 0) > 0) {
        R(3) = R(28); R(4) = R(30);
        GM_CALLV(0x800DF5B8u, F_STRCMP, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = R(30); goto out; }
    }
    R(30) = R(30) + 64;
    R(29) = R(29) + 1;
test:
    if (cmps(ctx, (int32_t)R(29), (int32_t)R(31)) < 0) { GM_LOOP(); goto body; }
    R(3) = 0;
out:
    R(0) = lr;
}
/* newResInfo(): the first info without references (a CTR loop) */
static void rs_new_info(GM_CTX) {
    R(0) = gm_u16(R(3) + 4);
    R(3) = gm_u32(R(3));
    ctx->ctr = R(0);
    if (cmps(ctx, (int32_t)R(0), 0) > 0) {
        for (;;) {
            R(0) = gm_u16(R(3) + 32);
            if (cmps(ctx, (int32_t)R(0), 0) == 0) return;
            R(3) = R(3) + 64;
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    }
    R(3) = 0;
}
/* getResInfoLoaded(name): getResInfo, if its archive is there */
static void rs_get_info_loaded(GM_CTX) {
    GM_FN(0x800DF640); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(0x800DF650u, F_GET_INFO, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) R(3) = 0;
    else {
        R(0) = gm_u32(R(3) + 40);
        if (cmps(ctx, (int32_t)R(0), 0) == 0) R(3) = 0;
    }
    R(0) = lr;
}

/* ================================================================== set / delete */
/* setRes(name, folder, allocDir, heap): a new info if the archive is not there, then a reference */
static void rs_set_res(GM_CTX) {
    GM_FN(0x800DF080); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 32;
    R(26) = R(3); R(27) = R(4); R(28) = R(5); R(29) = R(6); R(30) = R(7);
    GM_CALLV(0x800DF0ACu, F_GET_INFO, 0);
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);
    if (c == 0) {
        R(3) = R(26);
        GM_CALLV(0x800DF0C0u, F_NEW_INFO, 0);
        c = cmps(ctx, (int32_t)R(3), 0);
        R(31) = R(3);
        if (c == 0) { R(3) = 0; goto out; }
        R(4) = R(27); R(5) = R(28); R(6) = R(29); R(7) = R(30);
        GM_CALLV(0x800DF0E8u, F_INFO_SET, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) {
            R(3) = R(31);
            GM_CALLV(0x800DF0F8u, F_INFO_CLEANUP, 0);
            R(3) = 0;
            goto out;
        }
    }
    R(4) = gm_u16(R(31) + 32);
    R(3) = 1;
    R(0) = R(4) + 1;
    gm_set_u16(R(31) + 32, (uint16_t)R(0));
out:
    R(11) = f + 32;
    R(0) = lr;
}
/* deleteRes(name): a reference less; the last one cleans the info up */
static void rs_delete_res(GM_CTX) {
    GM_FN(0x800DF130); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(0x800DF140u, F_GET_INFO, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    R(4) = gm_u16(R(3) + 32);
    R(0) = R(4) - 1;
    gm_set_u16(R(3) + 32, (uint16_t)R(0));
    R(0) = R(0) & 0xFFFF;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) GM_CALLV(0x800DF168u, F_INFO_CLEANUP, 0);
    R(3) = 1;
out:
    R(0) = lr;
}

/* ================================================================== getRes */
/* getRes(name, path) */
static void rs_get_res2(GM_CTX) {
    GM_FN(0x800DF180); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = 0;
    R(30) = R(5);
    GM_CALLV(0x800DF1A0u, F_GET_INFO_LOADED, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(3) = gm_u32(R(3) + 40);
        if (cmps(ctx, (int32_t)R(3), 0) != 0) {
            R(4) = R(30); R(5) = 0;
            GM_CALLV(0x800DF1C0u, F_ARC_GET_FILE, 0);
            R(31) = R(3);
        }
    }
    R(3) = R(31);
    R(0) = lr;
}
/* getRes(name, path, &size) */
static void rs_get_res3(GM_CTX) {
    GM_FN(0x800DF1E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(31) = 0; R(30) = 0;
    R(29) = R(6); R(28) = R(5);
    GM_CALLV(0x800DF210u, F_GET_INFO_LOADED, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(3) = gm_u32(R(3) + 40);
        if (cmps(ctx, (int32_t)R(3), 0) != 0) {
            R(0) = 0;
            gm_set_u32(f + 8, 0);
            R(4) = R(28); R(5) = f + 8;
            gm_set_u32(f + 12, 0);
            GM_CALLV(0x800DF23Cu, F_ARC_GET_FILE, 0);
            R(31) = R(3);
            R(30) = gm_u32(f + 12);
        }
    }
    gm_set_u32(R(29), R(30));
    R(3) = R(31);
    R(0) = lr;
}
/* getRes(name, path, &size, &compression): the path, else "<path>.LZ" */
static void rs_get_res4(GM_CTX) {
    GM_FN(0x800DF270); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 304;
    R(31) = R(5); R(27) = R(6); R(28) = R(7);
    R(29) = 0;
    GM_CALLV(0x800DF298u, F_GET_INFO_LOADED, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) goto out;
    R(30) = gm_u32(R(3) + 40);
    if (cmps(ctx, (int32_t)R(30), 0) == 0) goto out;
    R(3) = R(30); R(4) = R(31);
    GM_CALLV(0x800DF2B8u, F_ARC_ENTRY_ID, 0);
    {
        int c = cmps(ctx, (int32_t)R(3), 0);
        R(4) = R(3);
        if (c >= 0) {
            R(31) = 0;
            gm_set_u32(f + 8, 0);
            R(3) = R(30); R(5) = f + 8;
            gm_set_u32(f + 12, 0);
            GM_CALLV(0x800DF2DCu, F_ARC_GET_FAST, 0);
            c = cmps(ctx, (int32_t)R(3), 0);
            R(29) = R(3);
            if (c == 0) goto out;
            if (cmps(ctx, (int32_t)R(28), 0) != 0) gm_set_u32(R(28), R(31));      /* CX_COMPRESSION_NONE */
            if (cmps(ctx, (int32_t)R(27), 0) == 0) goto out;
            R(0) = gm_u32(f + 12);
            gm_set_u32(R(27), R(0));
            goto out;
        }
    }
    R(6) = R(31); R(3) = f + 16; R(4) = 256;
    R(5) = R(13) - SDA_LZ_FMT;
    CR_SETBIT(ctx, 6, 0);                                                    /* (crclr 6: no float arguments) */
    GM_CALLV(0x800DF320u, F_SNPRINTF, 0);
    R(3) = R(30); R(4) = f + 16;
    GM_CALLV(0x800DF32Cu, F_ARC_ENTRY_ID, 0);
    {
        int c = cmps(ctx, (int32_t)R(3), 0);
        R(4) = R(3);
        if (c < 0) goto out;
    }
    R(3) = R(30); R(5) = 0;
    GM_CALLV(0x800DF344u, F_ARC_GET_FAST, 0);
    {
        int c = cmps(ctx, (int32_t)R(3), 0);
        R(29) = R(3);
        if (c == 0) goto out;
    }
    if (cmps(ctx, (int32_t)R(28), 0) != 0) {
        R(0) = gm_u8(R(3));
        R(0) = R(0) & 0xF0;
        gm_set_u32(R(28), R(0));
    }
    if (cmps(ctx, (int32_t)R(27), 0) != 0) {
        R(3) = R(29);
        GM_CALLV(0x800DF374u, F_CX_UNCOMP_SIZE, 0);
        gm_set_u32(R(27), R(3));
    }
out:
    R(11) = f + 304;
    R(3) = R(29);
    R(0) = lr;
}
/* getResSilently(name, path) */
static void rs_get_silently2(GM_CTX) {
    GM_FN(0x800DF3C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = 0;
    R(29) = R(5);
    GM_CALLV(0x800DF3E4u, F_GET_INFO_LOADED, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(31) = gm_u32(R(3) + 40);
        if (cmps(ctx, (int32_t)R(31), 0) != 0) {
            R(3) = R(31); R(4) = R(29);
            GM_CALLV(0x800DF404u, F_ARC_ENTRY_ID, 0);
            int c = cmps(ctx, (int32_t)R(3), 0);
            R(4) = R(3);
            if (c >= 0) {
                R(3) = R(31); R(5) = 0;
                GM_CALLV(0x800DF41Cu, F_ARC_GET_FAST, 0);
                R(30) = R(3);
            }
        }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* getResSilently(name, path, &size) */
static void rs_get_silently3(GM_CTX) {
    GM_FN(0x800DF440); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 48;
    R(27) = R(5); R(28) = R(6);
    R(30) = 0; R(29) = 0;
    GM_CALLV(0x800DF468u, F_GET_INFO_LOADED, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(31) = gm_u32(R(3) + 40);
        if (cmps(ctx, (int32_t)R(31), 0) != 0) {
            R(3) = R(31); R(4) = R(27);
            GM_CALLV(0x800DF488u, F_ARC_ENTRY_ID, 0);
            int c = cmps(ctx, (int32_t)R(3), 0);
            R(4) = R(3);
            if (c >= 0) {
                R(0) = 0;
                gm_set_u32(f + 8, 0);
                R(3) = R(31); R(5) = f + 8;
                gm_set_u32(f + 12, 0);
                GM_CALLV(0x800DF4ACu, F_ARC_GET_FAST, 0);
                R(30) = R(3);
                R(29) = gm_u32(f + 12);
            }
        }
    }
    gm_set_u32(R(28), R(29));
    R(11) = f + 48;
    R(3) = R(30);
    R(0) = lr;
}
/* syncAllRes(): every info with a DVD command loads on; true while one is still loading */
static void rs_sync_all(GM_CTX) {
    GM_FN(0x800DF4E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = 0;
    R(29) = R(3);
    R(31) = gm_u32(R(3));
    goto test;
body:
    R(0) = gm_u32(R(31) + 36);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(4) = gm_u32(R(29) + 8);
        R(3) = R(31);
        GM_CALLV(0x800DF520u, F_INFO_SETRES, 0);
        if (cmps(ctx, (int32_t)R(3), 0) > 0) { R(3) = 1; goto out; }
    }
    R(31) = R(31) + 64;
    R(30) = R(30) + 1;
test:
    R(0) = gm_u16(R(29) + 4);
    if (cmps(ctx, (int32_t)R(30), (int32_t)R(0)) < 0) { GM_LOOP(); goto body; }
    R(3) = 0;
out:
    R(0) = lr;
}

/* ================================================================== dRes_c's life */
static void rs_ctor(GM_CTX) {                                               /* dRes_c::dRes_c */
    R(0) = 0;
    gm_set_u32(R(3), 0); gm_set_u16(R(3) + 4, 0); gm_set_u32(R(3) + 8, 0);
}
static void rs_dtor(GM_CTX) {                                               /* dRes_c::~dRes_c (self, flags) */
    GM_FN(0x800DEF70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(3) = gm_u32(R(3));
        if (cmps(ctx, (int32_t)R(3), 0) != 0) {
            R(4) = 0x800DE970u;                                              /* (info_c::~info_c) */
            GM_CALLV(0x800DEFACu, F_DESTROY_NEW_ARR, 0);
            R(0) = 0;
            gm_set_u32(R(30), 0); gm_set_u16(R(30) + 4, 0);
        }
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800DEFC8u, F_OP_DELETE, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
static void rs_init(GM_CTX) {                                               /* dRes_c::init(count, callback) */
    GM_FN(0x800DEFF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(5); R(30) = R(4);
    R(4) = (R(4) << 6) & 0x3FFFC0u;
    R(29) = R(3);
    R(3) = R(4) + 16;
    GM_CALLV(0x800DF020u, F_NEW_ARR, 0);
    R(4) = 0x800DE940u; R(5) = 0x800DE970u;                                  /* (info_c's ctor / dtor) */
    R(7) = R(30); R(6) = 64;
    GM_CALLV(0x800DF03Cu, F_CONSTRUCT_NEW_ARR, 0);
    int c = cmps(ctx, (int32_t)R(3), 0);
    gm_set_u32(R(29), R(3));
    if (c == 0) R(3) = 0;
    else { gm_set_u16(R(29) + 4, (uint16_t)R(30)); R(3) = 1; gm_set_u32(R(29) + 8, R(31)); }
    R(0) = lr;
}

/* ================================================================== dRes_c::info_c */
static void in_ctor(GM_CTX) {
    R(0) = 0;
    gm_set_u16(R(3) + 32, 0);
    gm_set_u32(R(3) + 36, 0); gm_set_u32(R(3) + 40, 0); gm_set_u32(R(3) + 44, 0);
    gm_set_u32(R(3) + 48, 0); gm_set_u32(R(3) + 56, 0); gm_set_u32(R(3) + 60, 0);
}
/* ~info_c: wait (VIWaitForRetrace) for the DVD command, then cleanup */
static void in_dtor(GM_CTX) {
    GM_FN(0x800DE970); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(3) = gm_u32(R(3) + 36);
        R(0) = gm_u8(R(3) + 8);
        if (cmps(ctx, (int32_t)R(0), 0) == 0) {
            for (;;) {
                GM_CALLV(0x800DE9A8u, F_VI_WAIT, 0);
                R(3) = gm_u32(R(30) + 36);
                R(0) = gm_u8(R(3) + 8);
                if (cmps(ctx, (int32_t)R(0), 0) != 0) break;
                GM_LOOP();
            }
        }
        R(3) = R(30);
        GM_CALLV(0x800DE9C0u, F_INFO_CLEANUP, 0);
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800DE9D0u, F_OP_DELETE, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* the DVD command's results into the info (archive, binary, mount heap, size), then destroy it */
static void in_take_cmd(GM_CTX, uint32_t self, uint32_t ra) {
    R(0) = gm_u32(R(4) + 16);
    gm_set_u32(R(3) + 40, R(0));
    R(3) = R(4);
    GM_CALLV(ra, F_ARC_BINARY, 0);
    gm_set_u32(self + 48, R(3));
    R(3) = gm_u32(self + 36);
    R(0) = gm_u32(R(3) + 20); gm_set_u32(self + 44, R(0));
    R(0) = gm_u32(R(3) + 24); gm_set_u32(self + 52, R(0));
    GM_CALLV(ra + 0x1C, F_DVD_DESTROY, 0);
}
/* cleanup(): false while the DVD command runs; the archive's heap, the archive, the binary */
static void in_cleanup(GM_CTX) {
    GM_FN(0x800DE9F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    R(4) = gm_u32(R(3) + 36);
    if (cmps(ctx, (int32_t)R(4), 0) != 0) {
        R(0) = gm_u8(R(4) + 8);
        if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = 0; goto out; }
        in_take_cmd(GM_PASS, R(31), 0x800DEA34u);
        R(0) = 0; gm_set_u32(R(31) + 36, 0);
    }
    R(0) = gm_u32(R(31) + 40);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(3) = gm_u32(R(31) + 56);
        if (cmps(ctx, (int32_t)R(3), 0) != 0) {
            GM_CALLV(0x800DEA74u, F_DESTROY_FRM_HEAP, 0);
            R(0) = 0; gm_set_u32(R(31) + 56, 0);
        }
        R(3) = gm_u32(R(31) + 40);
        GM_CALLV(0x800DEA84u, F_ARC_UNMOUNT, 0);
        R(0) = 0; gm_set_u32(R(31) + 40, 0); gm_set_u32(R(31) + 60, 0);
    }
    R(3) = gm_u32(R(31) + 48);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(4) = 0;
        GM_CALLV(0x800DEAA4u, F_HEAP_FREE, 0);
        R(0) = 0; gm_set_u32(R(31) + 48, 0);
    }
    R(3) = 1;
out:
    R(0) = lr;
}
/* set(name, folder, allocDir, heap): mount "/<folder>/<name>.arc" */
static void in_set(GM_CTX) {
    GM_FN(0x800DEAD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(0) = R(5);
    R(5) = 0x80320000u;
    R(31) = R(7);
    R(5) = R(5) - 27352;                                                     /* "/%s/%s.arc" */
    R(30) = R(6);
    R(6) = R(0);
    R(29) = R(4);
    R(7) = R(29);
    R(4) = 80;
    R(28) = R(3);
    R(3) = f + 8;
    CR_SETBIT(ctx, 6, 0);
    GM_CALLV(0x800DEB20u, F_SNPRINTF, 0);
    R(4) = R(30); R(5) = R(31); R(3) = f + 8;
    GM_CALLV(0x800DEB30u, F_DVD_MOUNT_CREATE, 0);
    {
        int c = cmps(ctx, (int32_t)R(3), 0);
        gm_set_u32(R(28) + 36, R(3));
        if (c == 0) { R(3) = 0; goto out; }
    }
    R(3) = R(28); R(4) = R(29); R(5) = 32;
    GM_CALLV(0x800DEB54u, F_STRNCPY, 0);
    R(12) = gm_u32(R(13) - SDA_SET_CALLBACK);
    if (cmps(ctx, (int32_t)R(12), 0) != 0) {
        R(4) = R(31); R(3) = f + 8; ctx->ctr = R(12);
        GM_CALLV(0x800DEB70u, R(12), 0);                                     /* mSetCallback(path, heap) */
    }
    R(3) = 1;
out:
    R(0) = lr;
}
/* setRes(callback): once the DVD command is done - its results, a frame heap for the data, loadRes */
static void in_set_res(GM_CTX) {
    GM_FN(0x800DEBA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4); R(30) = R(3);
    R(0) = gm_u32(R(3) + 40);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = 0; goto out; }
    R(4) = gm_u32(R(3) + 36);
    if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(3) = (uint32_t)-1; goto out; }
    R(0) = gm_u8(R(4) + 8);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = 1; goto out; }
    in_take_cmd(GM_PASS, R(30), 0x800DEC00u);
    R(0) = gm_u32(R(30) + 40);
    R(3) = 0;
    gm_set_u32(R(30) + 36, 0);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = (uint32_t)-1; goto out; }
    R(4) = gm_u32(R(30) + 44);
    R(3) = (uint32_t)-1;
    if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(4) = 0x80370000u; R(4) = gm_u32(R(4) + 31816); }   /* g_gameHeaps[0] */
    R(5) = 0x80320000u; R(6) = 32;
    R(5) = R(5) - 27340;                                                     /* "dRes_c::info_c::mDataHeap" */
    R(7) = 0;
    GM_CALLV(0x800DEC68u, F_FRM_HEAP_TO_CUR, 0);
    {
        int c = cmps(ctx, (int32_t)R(3), 0);
        gm_set_u32(R(30) + 56, R(3));
        if (c == 0) { R(3) = (uint32_t)-1; goto out; }
    }
    R(3) = R(30); R(4) = R(31);
    GM_CALLV(0x800DEC88u, F_INFO_LOADRES, 0);
    R(31) = R(3);
    GM_CALLV(0x800DEC90u, F_RESTORE_HEAP, 0);
    R(3) = gm_u32(R(30) + 56);
    GM_CALLV(0x800DEC98u, F_ADJUST_FRM_HEAP, 0);
    if (cmps(ctx, (int32_t)R(31), -1) == 0) { R(3) = R(31); goto out; }
    R(3) = gm_u32(R(30) + 56);
    R(4) = gm_u32(R(3) + 16);
    R(0) = gm_u32(R(4) + 28);
    R(4) = R(0) - R(3);
    GM_CALLV(0x800DECBCu, F_DC_STORE_NOSYNC, 0);
    R(3) = 0;
out:
    R(0) = lr;
}
/* loadRes(callback): the file pointer array (cleared: 8 at a time, then the rest), filled by the
   callback's archive search or by getFileArray */
static void in_load_res(GM_CTX) {
    GM_FN(0x800DEDB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(30) = R(4); R(29) = R(3);
    R(3) = gm_u32(R(3) + 40);
    GM_CALLV(0x800DEDD8u, F_ARC_COUNT, 0);
    R(31) = R(3);
    R(3) = R(3) << 2;
    GM_CALLV(0x800DEDE4u, F_NEW_ARR, 0);
    {
        int c = cmps(ctx, (int32_t)R(3), 0);
        gm_set_u32(R(29) + 60, R(3));
        if (c == 0) { R(3) = (uint32_t)-1; goto out; }
    }
    {
        int c = cmps(ctx, (int32_t)R(31), 0);
        R(6) = 0;
        if (c != 0) {
            c = cmpu(ctx, R(31), 8);
            R(3) = R(31) - 8;
            if (c > 0) {
                R(0) = R(3) + 7; R(5) = 0;
                R(0) = R(0) >> 3;
                R(4) = 0;
                ctx->ctr = R(0);
                if (cmpu(ctx, R(3), 0) > 0) {
                    for (;;) {
                        R(3) = gm_u32(R(29) + 60);
                        R(6) = R(6) + 8;
                        gm_set_u32(R(3) + R(5), R(4));
                        for (uint32_t k = 4; k < 32; k += 4) {
                            R(0) = gm_u32(R(29) + 60);
                            R(3) = R(0) + R(5);
                            if (k == 28) R(5) = R(5) + 32;
                            gm_set_u32(R(3) + k, R(4));
                        }
                        if (--ctx->ctr == 0) break;
                        GM_LOOP();
                    }
                }
            }
            R(0) = R(31) - R(6);
            R(5) = R(6) << 2;
            R(4) = 0;
            ctx->ctr = R(0);
            if (cmpu(ctx, R(6), R(31)) < 0) {
                for (;;) {
                    R(3) = gm_u32(R(29) + 60);
                    gm_set_u32(R(3) + R(5), R(4));
                    R(5) = R(5) + 4;
                    if (--ctx->ctr == 0) break;
                    GM_LOOP();
                }
            }
        }
    }
    if (cmps(ctx, (int32_t)R(30), 0) != 0) {
        R(12) = gm_u32(R(30)); R(3) = R(30); R(4) = R(29);
        R(12) = gm_u32(R(12) + 8); ctx->ctr = R(12);
        GM_CALLV(0x800DEEDCu, R(12), 0);                                     /* callback->init(mName) */
        R(6) = gm_u32(R(29) + 60);
        R(3) = 0x20200000u; R(0) = R(3) + 8224;                              /* '    ' */
        R(4) = 0x800E0000u; R(3) = 0;
        gm_set_u32(f + 8, R(30));
        R(4) = R(4) - 4704;                                                  /* searchCallback_c::callback (0x800DEDA0) */
        R(5) = f + 8;
        gm_set_u32(f + 12, R(6)); gm_set_u32(f + 16, R(31));
        gm_set_u32(f + 20, R(3)); gm_set_u32(f + 24, R(0));
        R(3) = gm_u32(R(29) + 40);
        GM_CALLV(0x800DEF14u, F_ARC_SEARCH, 0);
    } else {
        R(3) = gm_u32(R(29) + 40);
        R(5) = R(31);
        R(4) = gm_u32(R(29) + 60);
        GM_CALLV(0x800DEF28u, F_ARC_FILE_ARRAY, 0);
    }
    R(3) = 0;
out:
    R(0) = lr;
}
/* searchCallback_c::callback(file, dirEntry, path): a folder sets the signature (4 characters,
   space padded), a file goes through the callback into the next slot */
static void sc_callback(GM_CTX) {
    GM_FN(0x800DECE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = gm_u32(R(5) + 8);
    int c = cmps(ctx, (int32_t)R(0), 0);
    R(30) = R(3);
    if (c != 0) {
        R(4) = 0x20200000u;
        R(31) = gm_u32(R(5) + 12);
        R(0) = R(4) + 8224;
        gm_set_u32(R(3) + 16, R(0));
        R(3) = R(31);
        GM_CALLV(0x800DED1Cu, F_STRLEN, 0);
        R(0) = R(3); R(4) = R(31);
        c = cmps(ctx, (int32_t)R(0), 4);
        R(3) = R(30) + 16; R(5) = 4;
        if (c <= 0) R(5) = R(0);
        GM_CALLV(0x800DED3Cu, F_MEMCPY, 0);
    } else {
        R(3) = gm_u32(R(3));
        R(5) = gm_u32(R(30) + 16);
        R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 12); ctx->ctr = R(12);
        GM_CALLV(0x800DED58u, R(12), 0);                                     /* execute(file, sig, path) */
        R(4) = gm_u32(R(30) + 12);
        R(0) = gm_u32(R(30) + 8);
        if (cmpu(ctx, R(4), R(0)) < 0) {
            R(5) = gm_u32(R(30) + 4);
            R(0) = R(4) << 2;
            R(4) = R(4) + 1;
            gm_set_u32(R(5) + R(0), R(3));
            gm_set_u32(R(30) + 12, R(4));
        }
    }
    R(0) = lr;
}

/* ================================================================== dResMng_c (d_res_mng.cpp) */
/* dResMng_c: +0 vtable, +4 the dRes_c, +16 the resCallback_c; dResMng_c::m_instance r13 - 22088 */
#define SDA_RESMNG        22088
static void rm_ctor(GM_CTX) {
    GM_FN(0x800DF680); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(4) = 0x80320000u;
    R(4) = R(4) - 27312;
    R(31) = R(3);
    gm_set_u32(R(3), R(4));
    R(3) = R(3) + 4;
    GM_CALLV(0x800DF6A8u, 0x800DEF50u, 0);                                   /* dRes_c::dRes_c */
    R(4) = 0x80320000u;
    R(3) = R(31) + 4;
    R(4) = R(4) - 27296;
    gm_set_u32(R(31) + 16, R(4));
    R(5) = R(31) + 16;
    gm_set_u32(R(13) - SDA_RESMNG, R(31));
    R(4) = 300;
    GM_CALLV(0x800DF6C8u, 0x800DEFF0u, 0);                                   /* mRes.init(300, &mCallback) */
    R(3) = R(31);
    R(0) = lr;
}
static void rm_dtor(GM_CTX) {
    GM_FN(0x800DF6E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(0) = 0;
        gm_set_u32(R(13) - SDA_RESMNG, 0);
        R(4) = (uint32_t)-1;
        R(3) = R(3) + 4;
        GM_CALLV(0x800DF718u, 0x800DEF70u, 0);                               /* mRes.~dRes_c() */
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800DF728u, F_OP_DELETE, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* resCallback_c::execute(data, folderSig, path): a g3d file is checked, initialised and bound */
static void rm_execute(GM_CTX) {
    GM_FN(0x800DF760); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(0) = R(5) + 0x98CD0000u;
    int c = cmpu(ctx, R(0), 0x6420);                                         /* 'g3d ' */
    R(31) = R(4);
    if (c == 0) {
        gm_set_u32(f + 12, R(4));
        R(3) = f + 12;
        GM_CALLV(0x800DF78Cu, F_RES_CHECK_REV, 0);
        if (cmps(ctx, (int32_t)R(3), 0) != 0) {
            R(3) = f + 12;
            GM_CALLV(0x800DF79Cu, F_RES_INIT, 0);
            R(0) = gm_u32(f + 12);
            R(3) = f + 12;
            gm_set_u32(f + 8, R(0));
            R(4) = f + 8;
            GM_CALLV(0x800DF7B0u, F_RES_BIND, 0);
        }
    }
    R(3) = R(31);
    R(0) = lr;
}
/* setRes(path, names, count, heap) */
static void rm_set_res_list(GM_CTX) {
    GM_FN(0x800DF7D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 32;
    R(26) = R(3); R(27) = R(4); R(31) = R(5); R(28) = R(6); R(29) = R(7);
    R(30) = 0;
    goto test;
body:
    R(4) = gm_u32(R(31));
    R(5) = R(27); R(7) = R(29);
    R(3) = R(26) + 4;
    R(6) = 0;
    GM_CALLV(0x800DF818u, 0x800DF080u, 0);                                   /* mRes.setRes */
    R(31) = R(31) + 4;
    R(30) = R(30) + 1;
test:
    if (cmps(ctx, (int32_t)R(30), (int32_t)R(28)) < 0) { GM_LOOP(); goto body; }
    R(11) = f + 32;
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
/* (the destructors and the plain copyRes are written but off - no test reaches them: plain GM_HLE,
   not in hle_funcs.txt) */
#ifdef GM_RES_VERIFY          /* (testing, as GM_WIPE_VERIFY in gm_d_wipe.c: the calls run twice) */
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_RES_COUNT)   /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_800DF570, 8)  { rs_get_info(GM_PASS); }                                       /* dRes_c::getResInfo */
E(fn_800DF600, 8)  { rs_new_info(GM_PASS); }                                       /* ::newResInfo */
E(fn_800DF640, 8)  { rs_get_info_loaded(GM_PASS); }                                /* ::getResInfoLoaded */
E(fn_800DF080, 8)  { rs_set_res(GM_PASS); }                                        /* ::setRes */
E(DVD_FreeFile__FPvPc, 8) { rs_delete_res(GM_PASS); }                              /* ::deleteRes */
E(_Z19RetrieveFileFromArcPvPcS0_, 8) { rs_get_res2(GM_PASS); }                     /* ::getRes(name, path) */
E(DVD_GetFile__FPvPCcPCcPUi, 8) { rs_get_res3(GM_PASS); }                         /* ::getRes(name, path, &size) */
E(fn_800DF270, 8)  { rs_get_res4(GM_PASS); }                                       /* ::getRes(..., &size, &compression) */
GM_HLE(fn_800DF3A0)  { R(0) = R(3); R(3) = R(4); R(4) = R(0); GM_TAIL(F_MEMCPY, 0); } /* ::copyRes(from, to, size) */
E(fn_800DF3B0, 8)  { if (cmps(ctx, (int32_t)R(6), 0) == 0) GM_TAIL(F_COPY_RES, 0); else GM_TAIL(F_CX_UNCOMP_LZ, 0); }
E(RetrieveFileFromArcAlt, 8) { rs_get_silently2(GM_PASS); }                        /* ::getResSilently(name, path) */
E(fn_800DF440, 8)  { rs_get_silently3(GM_PASS); }                                  /* ::getResSilently(name, path, &size) */
E(EnsureAllArcsAreLoaded, 8) { rs_sync_all(GM_PASS); }                             /* ::syncAllRes */
E(fn_800DEF50, 12) { rs_ctor(GM_PASS); }                                         /* dRes_c::dRes_c */
GM_HLE(fn_800DEF70) { rs_dtor(GM_PASS); }                                         /* dRes_c::~dRes_c */
E(fn_800DEFF0, 12) { rs_init(GM_PASS); }                                         /* dRes_c::init */
E(fn_800DE940, 64) { in_ctor(GM_PASS); }                                         /* info_c::info_c */
GM_HLE(fn_800DE970) { in_dtor(GM_PASS); }                                         /* info_c::~info_c */
E(fn_800DE9F0, 64) { in_cleanup(GM_PASS); }                                      /* info_c::cleanup */
E(fn_800DEAD0, 64) { in_set(GM_PASS); }                                          /* info_c::set */
E(fn_800DEBA0, 64) { in_set_res(GM_PASS); }                                      /* info_c::setRes */
E(fn_800DEDB0, 64) { in_load_res(GM_PASS); }                                     /* info_c::loadRes */
E(fn_800DECE0, 20) { sc_callback(GM_PASS); }                                     /* searchCallback_c::callback */
E(fn_800DEDA0, 20) { GM_TAIL(0x800DECE0u, 0); }                                  /* ... the static one */
E(fn_800DF680, 20) { rm_ctor(GM_PASS); }                                         /* dResMng_c::dResMng_c */
GM_HLE(fn_800DF6E0) { rm_dtor(GM_PASS); }                                         /* dResMng_c::~dResMng_c */
E(fn_800DF750, 4)  { }                                                           /* resCallback_c::init */
E(fn_800DF760, 4)  { rm_execute(GM_PASS); }                                      /* resCallback_c::execute */
E(fn_800DF7D0, 4)  { rm_set_res_list(GM_PASS); }                                 /* dResMng_c::setRes(path, names, n, heap) */
E(QueueArcLoad, 4) { R(0) = R(4); R(4) = R(5); R(7) = R(6); R(6) = 0; R(5) = R(0); /* dResMng_c::setRes(path, name, heap) */
                     R(3) = R(3) + 4; GM_TAIL(0x800DF080u, 0); }
