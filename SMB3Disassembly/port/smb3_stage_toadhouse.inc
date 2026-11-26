/* smb3_stage_toadhouse.inc - SMB3's Toad House as a stage (included by smb3_stage_enemies.inc).
 *
 * The Toad House (Level_Tileset 7) is a level SMB3 loads like any other; here it is played as a
 * stage by the NSMBW players, its logic ported from the disassembly:
 *  - Toad (OBJ_TOAD $34, ObjInit_Toad / ObjNorm_Toad): turned to the nearest player, drawn by
 *    Object_Draw16x32Sprite (ObjP34 $B9 $BB / $BD $BF, palette 2, sprite bank $05 - his
 *    OPTS_SETPT5 | $05); his message by Toad_Speak: Toad_DrawDiagBox (TDiagBox_R1-R3, a row a
 *    frame, at VRAM $28C8), then Toad_DoToadText (a letter each 4 frames from $28E9, 15 to a line,
 *    6 lines; ToadMsg_WarpWhistle / _Standard / _AnchorPWing by where he stands and
 *    Map_EnterViaID). Drawn from the level's own BG patterns, in the level's place.
 *  - The chests (TILE7_CHEST_*): a player whose head or body is at one pressing B (NSMBW's run /
 *    1 button) opens it - ToadHouse_ChestPressB: the box by the player's X ($60 / $90), its top
 *    tiles to TILE7_CHEST_OPEN_UL / _UR (TileChng_ToadBoxOpen at row $180), the item from
 *    THouse_Treasure (ToadHouse_Item2Inventory / _ItemOff / _RandomItem), one box only.
 *  - The item (OBJ_TOADHOUSEITEM, ToadHouse_GiveItem / ObjNorm_ToadHouseItem): out of the box at
 *    Y velocity -$30, falling 2 a frame back to it, then flashing; put in Mario's inventory
 *    (Inventory_Items, the first empty slot) - SMB3 throws it into its inventory panel, which
 *    the stage has no picture of; after $FF frames the level ends cleared (Map_ReturnStatus 0,
 *    Level_ExitToMap: the house shown as used on the map).
 *  - The clock stays stopped (Level_TimerEn).
 */
#define OBJ_TOAD          0x34
#define INVENTORY_ITEMS   0x7D80                /* (Inventory_Items: Mario's, 4 rows of 7) */
static const uint8_t TH_BOX_R1[17] = {0x94, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x96};
static const uint8_t TH_BOX_R2[17] = {0x92, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x93};
static const uint8_t TH_BOX_R3[17] = {0x95, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x97};
static const uint8_t TH_MSG[3][90] = {
    {   /* ToadMsg_WarpWhistle: "One toot on" / "this whistle" / "will send you" / "to a far away" / "land!" */
        0xBE, 0xDD, 0xD4, 0xFE, 0xCD, 0xDE, 0xDE, 0xCD, 0xFE, 0xDE, 0xDD, 0xFE, 0xFE, 0xFE, 0xFE,
        0xCD, 0xD7, 0xD8, 0xCC, 0xFE, 0x81, 0xD7, 0xD8, 0xCC, 0xCD, 0xDB, 0xD4, 0xFE, 0xFE, 0xFE,
        0x81, 0xD8, 0xDB, 0xDB, 0xFE, 0xCC, 0xD4, 0xDD, 0xD3, 0xFE, 0x8C, 0xDE, 0xCE, 0xFE, 0xFE,
        0xCD, 0xDE, 0xFE, 0xD0, 0xFE, 0xD5, 0xD0, 0xCB, 0xE5, 0xD0, 0x81, 0xD0, 0x8C, 0xFE, 0xFE,
        0xDB, 0xD0, 0xDD, 0xD3, 0xEA, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE },
    {   /* ToadMsg_Standard: "Pick a box." / "Its contents" / "will help you" / "on your way." */
        0xFE, 0xBF, 0xD8, 0xD2, 0xDA, 0xFE, 0xD0, 0xFE, 0xD1, 0xDE, 0x88, 0xE9, 0xFE, 0xFE, 0xFE,
        0xFE, 0xB8, 0xCD, 0xCC, 0xFE, 0xD2, 0xDE, 0xDD, 0xCD, 0xD4, 0xDD, 0xCD, 0xCC, 0xFE, 0xFE,
        0xFE, 0x81, 0xD8, 0xDB, 0xDB, 0xFE, 0xD7, 0xD4, 0xDB, 0xDF, 0xFE, 0x8C, 0xDE, 0xCE, 0xFE,
        0xFE, 0xDE, 0xDD, 0xFE, 0x8C, 0xDE, 0xCE, 0xCB, 0xFE, 0x81, 0xD0, 0x8C, 0xE9, 0xFE, 0xFE,
        0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE },
    {   /* ToadMsg_AnchorPWing: "Hello! You" / "found my shop" / "of strange and" / "wonderful" / "things!" */
        0xFE, 0xB7, 0xD4, 0xDB, 0xDB, 0xDE, 0xEA, 0xFE, 0xC8, 0xDE, 0xCE, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFE, 0xD5, 0xDE, 0xCE, 0xDD, 0xD3, 0xFE, 0xDC, 0x8C, 0xFE, 0xCC, 0xD7, 0xDE, 0xDF, 0xFE,
        0xFE, 0xDE, 0xD5, 0xFE, 0xCC, 0xCD, 0xCB, 0xD0, 0xDD, 0xD6, 0xD4, 0xFE, 0xD0, 0xDD, 0xD3,
        0xFE, 0x81, 0xDE, 0xDD, 0xD3, 0xD4, 0xCB, 0xD5, 0xCE, 0xDB, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFE, 0xCD, 0xD7, 0xD8, 0xDD, 0xD6, 0xCC, 0xEA, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE } };
/* the items (1-13, as Inventory_Items keeps them): ToadItem_PatternLeft / _PatternRight / _AttrRight, ToadItem_PalPerItem */
static const uint8_t TH_ITEM_L[13] = {0x85, 0x87, 0x9D, 0x81, 0x83, 0x8B, 0xB5, 0x91, 0xA9, 0x95, 0x99, 0xA1, 0x89};
static const uint8_t TH_ITEM_R[13] = {0x85, 0x87, 0x9F, 0x81, 0x83, 0x8B, 0xB7, 0x93, 0xA9, 0x97, 0x9B, 0xA3, 0x8D};
static const uint8_t TH_ITEM_AR[13] = {0x43, 0x43, 0x03, 0x43, 0x43, 0x43, 0x03, 0x03, 0x43, 0x03, 0x03, 0x03, 0x03};
static const uint8_t TH_ITEM_PAL[14] = {0x30, 0x16, 0x2A, 0x2A, 0x2A, 0x17, 0x27, 0x36, 0x27, 0x30, 0x07, 0x36, 0x27, 0x27};
static const uint8_t TH_TOAD[4] = {0xB9, 0xBB, 0xBD, 0xBF};               /* ObjP34 */

static struct {
    int on;                                      /* (this level is a Toad House) */
    int treasure;                                /* THouse_Treasure */
    int opened, item, ix, iy, iyv, iyf, landed, timer, ended;
    int halt, toad_in;
    int ixv, ixf, slot, inv, inv_start, inv_wait; /* (the item: X velocity; Objects_Var1 its slot; the inventory open in the bar, from its row's first) */                           /* Player_HaltTick ($FF at ObjInit_Toad, -1 a frame); Toad's there */
    int dash[8];
    int slot0;                                   /* (atlas: Toad's 2 slots, then 13 items' 13) */
    int gl_row, ng; uint8_t gl[64];              /* (atlas: the BG letters, 8 x 8, a row of 32) */
} TH;

static int th_gl(uint8_t t) { for (int i = 0; i < TH.ng; i++) if (TH.gl[i] == t) return i; return -1; }
static void th_reset(void) { int on = TH.on, tr = TH.treasure, s0 = TH.slot0, gr = TH.gl_row, ng = TH.ng; uint8_t gl[64]; memcpy(gl, TH.gl, sizeof gl);
    memset(&TH, 0, sizeof TH); TH.on = on; TH.treasure = tr; TH.slot0 = s0; TH.gl_row = gr; TH.ng = ng; memcpy(TH.gl, gl, sizeof gl); }

/* (level_load) the pictures: Toad, the items (bank $05 at PatTable_BankSel+4), the letters (the BG banks) */
static void th_render(int *slot, const uint8_t *chr, uint32_t nchr, const uint8_t *ram) {
    TH.on = ram[0x70A] == 7; TH.treasure = ram[0x03EB];                   /* (THouse_Treasure) */
    th_reset();
    if (!TH.on) return;
    #define SPR_HALF(sl, xo, n, palidx, c2) do { \
        for (int y = 0; y < 16; y++) { \
            uint16_t a = (uint16_t)(0x1000 + ((n) & 0xFE) * 16 + (y >> 3) * 16 + (y & 7)); \
            int bi = (a - 0x1000) >> 10; uint8_t bank = bi == 2 ? 0x05 : ram[0x71B + bi]; \
            const uint8_t *c = chr + (size_t)(bank % nchr) * 0x400 + (a & 0x3FF); \
            for (int x = 0; x < 8; x++) { int p = ((c[0] >> (7 - x)) & 1) | (((c[8] >> (7 - x)) & 1) << 1); \
                uint8_t col = (p == 2 && (c2) >= 0) ? (uint8_t)(c2) : ppu_peek_pal(16 + (palidx) * 4 + p); \
                atlas[(((sl) / 16) * 16 + y) * 256 + ((sl) % 16) * 16 + (xo) + x] = p ? ppu_rgb(col) : 0; } } } while (0)
    if (*slot + 15 > (TEX_H_MAX / 16) * 16) { rt_log("smb3", "toad house: no room for Toad's pictures"); TH.slot0 = -1; TH.ng = 0; return; }
    TH.slot0 = *slot;
    for (int k = 0; k < 4; k++) SPR_HALF(*slot + (k >> 1), (k & 1) * 8, TH_TOAD[k], 2, -1);
    for (int i = 0; i < 13; i++) {
        int sl = *slot + 2 + i;
        SPR_HALF(sl, 0, TH_ITEM_L[i], 3, TH_ITEM_PAL[i + 1]);
        SPR_HALF(sl, 8, TH_ITEM_R[i], 3, TH_ITEM_PAL[i + 1]);
    }
    #undef SPR_HALF
    *slot += 15;
    /* the letters: the box's and the three messages' BG tiles, 8 x 8, from the BG banks as the
       level has them (BG at $0000: PatTable_BankSel+0 / +1, 2 KB each), BG palette 1 - the house's
       background ($48) under the box - and its colour 0 */
    TH.ng = 0;
    #define ADDG(t) do { if (th_gl(t) < 0 && TH.ng < 64) TH.gl[TH.ng++] = (t); } while (0)
    for (int k = 0; k < 17; k++) { ADDG(TH_BOX_R1[k]); ADDG(TH_BOX_R2[k]); ADDG(TH_BOX_R3[k]); }
    for (int m = 0; m < 3; m++) for (int k = 0; k < 90; k++) ADDG(TH_MSG[m][k]);
    #undef ADDG
    *slot = (*slot + 15) / 16 * 16; TH.gl_row = (*slot / 16) * 16;
    if (TH.gl_row + 16 > TEX_H_MAX) { rt_log("smb3", "toad house: no room for the letters"); TH.ng = 0; return; }
    for (int g = 0; g < TH.ng; g++) for (int y = 0; y < 8; y++) {
        uint16_t a = (uint16_t)(TH.gl[g] * 16 + y);
        uint8_t bank = (uint8_t)((ram[0x719 + (a >> 11)] & 0xFE) | ((a >> 10) & 1));
        const uint8_t *c = chr + (size_t)(bank % nchr) * 0x400 + (a & 0x3FF);
        for (int x = 0; x < 8; x++) {
            int p = ((c[0] >> (7 - x)) & 1) | (((c[8] >> (7 - x)) & 1) << 1);
            atlas[(TH.gl_row + (g / 32) * 8 + y) * 256 + (g % 32) * 8 + x] = ppu_rgb(p ? ppu_peek_pal(4 + p) : ppu_peek_pal(0));
        }
    }
    *slot += 16;
    rt_log("smb3", "toad house: treasure %d, %d letters", TH.treasure, TH.ng);
}

/* ObjInit_Toad: always in the lower screen space (YHi 1); his message by where he was placed */
static void toad_init(obj_t *o) {
    int yhi = o->y >> 8;
    o->var5 = yhi ? 1 + (nes_ram_ptr()[0x1E] != 0) : 0;                 /* (Map_EnterViaID: a White Toad House) */
    o->y = 0x100 | (o->y & 0xFF);
    o->pal = 2; o->var4 = 0; o->var1 = 0; o->var2 = 0;
    if (!TH.toad_in) { TH.toad_in = 1; TH.halt = 0xFF; }               /* (ObjInit_Toad: the Player halted $FF frames - prg029 counts it down) */
}
/* (dAcPy_c::executeMain, before it: a halted Player's buttons are none - from the house's start until
   Player_HaltTick runs out) */
static int th_halted(void) { return TH.on && (!TH.toad_in || TH.halt); }
/* ObjNorm_Toad / Toad_Speak (Var4: 0 the box, a row a frame; 1 the letters; 2 done) */
static void toad_frame(obj_t *o) {
    int n = near_pl(o);
    o->flip = xdiff(o, n) == 0 ? SPR_HFLIP : 0;                           /* (Object_CalcCoarseXDiff: towards the player) */
    switch (o->var4) {
    case 0: if (++o->var2 >= 8) { o->var4 = 1; o->timer = 0x10; } break;
    case 1: if (!o->timer) { o->var1++; o->timer = 4; if (o->var1 >= 90) o->var4 = 2; } break;
    }
}
static void toad_draw(obj_t *o, float z) {                               /* Object_Draw16x32Sprite */
    if (TH.slot0 < 0) { for (int k = 0; k < 4; k++) quad(0, 0, 0, 0, 0, 0, 0, 0, 0); return; }
    int hf = (o->flip & SPR_HFLIP) != 0;
    for (int r = 0; r < 2; r++) for (int k = 0; k < 2; k++) {
        int h = r * 2 + (hf ? 1 - k : k), sl = TH.slot0 + (h >> 1);
        float u0 = (sl % 16) * 16 / 256.0f + (h & 1) * 8 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
        if (hf) { float t = u0; u0 = u1; u1 = t; }
        float x = L.lx + o->x + 8 * k, y = -(L.ly + o->y + 16 * r);
        quad(x, y, x + 8, y - 16, z, u0, v0, u1, v1);
    }
}

/* ToadHouse_ChestPressB / ToadHouse_GiveItem for a player n (B pressed this frame) */
static void th_try_open(int n) {
    if (TH.opened || !pp[n].on) return;
    int cx = pp[n].x + 8, hit = 0;
    for (int dy = 8; dy <= 24 && !hit; dy += 8) {                        /* (Level_Tile_Head: at its head, or lower for a small one) */
        int tx = cx >> 4, ty = (pp[n].y + 32 - dy) >> 4;
        if (tx < 0 || tx >= L.w || ty < 0 || ty >= LH) continue;
        uint8_t t = L.tile[ty * L.w + tx];
        if ((uint8_t)(0x84 - t) < 4) hit = 1;                             /* (TILE7_CHEST_LR - tile < 4) */
    }
    if (!hit) return;
    static const int box_x[3] = {0x40, 0x70, 0xA0};                       /* ToadHouse_Box_X */
    int px = pp[n].x, b = px < 0x60 ? 0 : px < 0x90 ? 1 : 2;
    int col = box_x[b] >> 4, row = 0x180 >> 4;
    if (col + 1 < L.w && row < LH) { L.tile[row * L.w + col] = 0x86; L.tile[row * L.w + col + 1] = 0x87; }   /* TileChng_ToadBoxOpen */
    static const uint8_t item2inv[15] = {0x0C, 0x08, 0x04, 0x05, 0x06, 0x04, 0x05, 0x06, 0x01, 0x02, 0x03, 0x04, 0x02, 0x03, 0x05};   /* ToadHouse_Item2Inventory */
    static const uint8_t itemoff[7] = {0x02, 0x03, 0x0A, 0x0A, 0x0A, 0x05, 0x08};                                                 /* ToadHouse_ItemOff */
    static const uint8_t rnd[16] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0};                                              /* ToadHouse_RandomItem */
    int x = TH.treasure - 1;
    if (x < 0 || x >= 5) { if (x < 5 || x > 6) x = 6; x = rnd[rand() & 15] + itemoff[x]; }
    TH.item = item2inv[x];
    /* ToadHouse_GiveItem: the first empty slot (Objects_Var1), its row of 7 shown (InventoryRow_BaseIndex),
       Y $90 on SMB3's screen, Y velocity -$30, X velocity Inventory_DestX / 4 - box X / 4 - so it lands
       in its slot; the inventory flips open in the bar (Inventory_Open) before it moves (InvFlip_Counter 4) */
    static const uint8_t dest_x[7] = {0x48, 0x60, 0x78, 0x90, 0xA8, 0xC0, 0xD8};   /* Inventory_DestX */
    uint8_t *w = nes_wram_ptr(); int sl = 0;
    while (sl < 27 && w[(INVENTORY_ITEMS - 0x6000) + sl]) sl++;
    TH.slot = sl; TH.inv_start = (sl / 7) * 7; TH.inv = 1; TH.inv_wait = 16;
    TH.opened = 1; TH.ix = box_x[b]; TH.ixf = 0; TH.ixv = (int8_t)(uint8_t)((dest_x[sl % 7] >> 2) - (box_x[b] >> 2));
    TH.iy = 0x90; TH.iyv = -0x30; TH.iyf = 0; TH.timer = 0xFF;
    rt_log("smb3", "toad house: player %d opened box %d: item %d", n + 1, b, TH.item);
}
static void th_frame(void) {
    if (!TH.on) return;
    if (TH.halt) TH.halt--;
    for (int n = 0; n < 8; n++) {
        int d = pp[n].on && pp[n].dash;
        if (d && !TH.dash[n]) { if (getenv("SMB3_TH_LOG")) rt_log("smb3", "toad house: player %d B at (%d, %d)", n + 1, pp[n].x, pp[n].y); th_try_open(n); }
        TH.dash[n] = d;
    }
    if (!TH.opened) return;
    if (TH.inv_wait) TH.inv_wait--;                                      /* (the inventory flipping open) */
    else if (!TH.landed) {                                                /* ObjNorm_ToadHouseItem: X, Y, gravity 2, down to Y 200 - its slot */
        int p = TH.ix * 16 + TH.ixf + TH.ixv; TH.ix = p >> 4; TH.ixf = p & 15;
        p = TH.iy * 16 + TH.iyf + TH.iyv; TH.iy = p >> 4; TH.iyf = p & 15; TH.iyv += 2;
        if (TH.iyv > 0 && TH.iy >= 200) {
            TH.iy = 200; TH.landed = 1;
            static const uint8_t dest_x[7] = {0x48, 0x60, 0x78, 0x90, 0xA8, 0xC0, 0xD8};
            TH.ix = dest_x[TH.slot % 7];
            uint8_t *w = nes_wram_ptr();
            if (TH.slot < 27) w[(INVENTORY_ITEMS - 0x6000) + TH.slot] = (uint8_t)TH.item;
            rt_log("smb3", "toad house: item %d into the inventory (slot %d)", TH.item, TH.slot);
        }
    }
    if (TH.timer && !--TH.timer && !TH.ended) {                           /* (Objects_Timer out: Map_ReturnStatus 0, Level_ExitToMap) */
        TH.ended = 1;
        for (int i = 0; i < 8; i++) kept_rest[i] = (int)R32(MOD_PY_REST + 4 * (uint32_t)i);
        keep_rest = 1;
        if (map_level_end(blk_ctx, blk_base, 0)) rt_log("smb3", "toad house: done - SMB3's map");
    }
}
/* the box, the letters and the item: a fixed number of quads (unused ones empty) */
#define TH_QUADS (8 * 17 + 90 + 2)
static int th_quads(void) { return TH.on ? TH_QUADS : 0; }
static void th_draw(float z) {
    if (!TH.on) return;
    int used = 0;
    obj_t *t = NULL; for (int i = 0; i < NOBJ; i++) if (ob[i].state == OS_NORMAL && ob[i].id == OBJ_TOAD) t = &ob[i];
    #define GLQ(tile, px, py) do { int g_ = th_gl(tile); if (g_ >= 0 && TH.ng) { \
        float u0 = (g_ % 32) * 8 / 256.0f, v0 = (TH.gl_row + (g_ / 32) * 8) / (float)tex_h; \
        float x_ = L.lx + (px), y_ = -(L.ly + (py)); quad(x_, y_, x_ + 8, y_ - 8, z, u0, v0, u0 + 8 / 256.0f, v0 + 8 / (float)tex_h); used++; } } while (0)
    if (t) {
        int rows = t->var4 ? 8 : t->var2;                                 /* VRAM $28C8: nametable 2 (level y 240 on), row 6, column 8 */
        for (int r = 0; r < rows; r++) {
            const uint8_t *row = r == 0 ? TH_BOX_R1 : r == 7 ? TH_BOX_R3 : TH_BOX_R2;
            for (int c = 0; c < 17; c++) GLQ(row[c], (8 + c) * 8, 240 + (6 + r) * 8);
        }
        if (t->var4 >= 1) {                                               /* $28E9: row 7, column 9; 15 to a line */
            const uint8_t *m = TH_MSG[t->var5 % 3];
            for (int k = 0; k < t->var1 && k < 90; k++) if (m[k] != 0xFE) GLQ(m[k], (9 + k % 15) * 8, 240 + (7 + k / 15) * 8);
        }
    }
    #undef GLQ
    while (used < TH_QUADS - 2) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); used++; }
    quad(0, 0, 0, 0, 0, 0, 0, 0, 0); quad(0, 0, 0, 0, 0, 0, 0, 0, 0);   /* (the item: over the bar - th_bar_draw) */
}

/* (the bar, its inventory open: Flip_Video_Data_Opening - Flip_TopBarInv, Flip_MidTItems / _MidBItems with
   7 items of the row from InvItem_Tile_Layout at columns 9 + 3k, Flip_BottomBarInv) - rows 24-27 of t */
static int th_bar_inventory(uint8_t *t, const uint8_t *nt) {
    if (!TH.on || !TH.inv) return 0;
    static const uint8_t lay[14][4] = {{0xFE, 0xFE, 0xFE, 0xFE}, {0x20, 0x21, 0x30, 0x31}, {0x22, 0x23, 0x32, 0x33}, {0x0E, 0x0F, 0x1E, 0x1F},
        {0x0A, 0x0B, 0x1A, 0x1B}, {0x00, 0x01, 0x10, 0x11}, {0x28, 0x29, 0x38, 0x39}, {0x08, 0x09, 0x18, 0x19}, {0x2A, 0x2B, 0x3A, 0x3B},
        {0x24, 0x25, 0x34, 0x35}, {0x02, 0x03, 0x12, 0x13}, {0x06, 0x07, 0x16, 0x17}, {0x04, 0x05, 0x14, 0x15}, {0x0C, 0x0D, 0x1C, 0x1D}};
    uint8_t *r0 = t, *r1 = t + 32, *r2 = t + 64, *r3 = t + 96, keep[5];
    memcpy(keep, t + 64 + 2, 5);                                         /* (<M> x and the lives, as filled) */
    for (int c = 0; c < 32; c++) { r0[c] = 0xA1; r3[c] = 0xA4; r1[c] = 0xFE; r2[c] = 0xFE; }
    r0[0] = 0xFC; r0[1] = 0xA0; r0[30] = 0xA2; r0[31] = 0xFC;
    r3[0] = 0xFC; r3[1] = 0xA8; r3[30] = 0xA5; r3[31] = 0xFC;
    r1[0] = r2[0] = 0xFC; r1[1] = r2[1] = 0xA6; r1[30] = r2[30] = 0xA7; r1[31] = r2[31] = 0xFC;
    for (int c = 2; c <= 7; c++) r1[c] = nt[32 + c];                    /* (WORLD n: the bar's own) */
    memcpy(r2 + 2, keep, 5);
    const uint8_t *w = nes_wram_ptr() + (INVENTORY_ITEMS - 0x6000);
    for (int k = 0; k < 7; k++) {
        int it = TH.inv_start + k < 28 ? w[TH.inv_start + k] : 0; if (it > 13) it = 0;
        r1[9 + 3 * k] = lay[it][0]; r1[10 + 3 * k] = lay[it][1]; r2[9 + 3 * k] = lay[it][2]; r2[10 + 3 * k] = lay[it][3];
    }
    return 1;
}
/* (sb_draw, after the bar) the item over it, on SMB3's screen as the bar is (x bx + X sc, y y0 - Y sc);
   once in its slot it flashes (Counter_1 & %00011000) */
static void th_bar_draw(ppc_context *ctx, uint8_t *base, float bx, float y0, float sc) {
    if (!TH.on || !TH.opened || TH.inv_wait || TH.slot0 < 0 || TH.item < 1 || TH.item > 13) return;
    if (TH.landed && !(counter1 & 0x18)) return;
    int i = TH.item - 1, sl = TH.slot0 + 2 + i;
    float u0 = (sl % 16) * 16 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, v1 = v0 + 16 / (float)tex_h;
    float ur0 = u0 + 8 / 256.0f, ur1 = u0 + 16 / 256.0f;
    if (TH_ITEM_AR[i] & 0x40) { float t = ur0; ur0 = ur1; ur1 = t; }
    float x = bx + TH.ix * sc, y = y0 - TH.iy * sc;
    gcall(ctx, base, A_GXLoadTexObj, 2, SM_TEXOBJ, 0);
    gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 8);
    quad(x, y, x + 8 * sc, y - 16 * sc, pz, u0, v0, u0 + 8 / 256.0f, v1);
    quad(x + 8 * sc, y, x + 16 * sc, y - 16 * sc, pz, ur0, v0, ur1, v1);
}
