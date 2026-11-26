/* smb3_stage_battle.inc - a map Hammer Bro's battle in the stage (included by smb3_stage_enemies.inc).
 *
 * Walking onto a map Hammer Bro (Map_EnterViaID 3-6, prg011 PRG011_B6A1) loads a small battle
 * level whose object list has the brothers ($81, ObjInit_HammerBro: the battle's kind of brother by
 * Map_EnterViaID) and OBJ_TREASUREBOXAPPEAR ($BA: Level_Event 7). From the disassembly:
 *  - ObjNorm_HammerBro (prg004): faces the Player, walks back and forth (X velocity +-6, turning
 *    every 64 ticks), jumps when Timer3 runs out (-$30 / -$60 by its height, Timer2 $28 / $20 -
 *    while Timer2 runs it doesn't land: a small jump drops it through the floor it stood on, a big
 *    one carries it up through the one above), throws a hammer when Var6's low bits come to $1F
 *    (Timer $0F: the throwing frame); EnemyBro_DrawAndHandleBump / Object_Draw16x32Sprite (ObjP81,
 *    8 below its Y), tile detection group 2 (feet $20 below), bound box 2. Stomped: OA2_NOSHELLORSQUASH
 *    - killed, falling, 1000 points (OCSPECIAL_HIGHSCORE).
 *  - SObj_Hammer (prg007): held in the hand for 15 frames (SpecialObj_Data's low bits; Hammer_XOff
 *    / Hammer_YOff, turned with its brother), then thrown (X +-$12 towards the Player, Y -$30, gravity
 *    2 a frame to $6E); Hammer_Draw's 8 frames; SObj_PlayerCollide every other frame.
 *  - LevelEvent_TreasureBox (prg005): no objects and no hammers left - the treasure box at Y $170,
 *    X $30 or $C0 into the screen (away from the Player); ObjNorm_TreasureBox (prg003): a poof after
 *    $1F ticks ($18), falls; touched: opens - the item (Level_TreasureItem) rises (-$30, +1 a frame),
 *    flashes $70 frames, goes into the inventory (Player_GetItem); $60 frames on, Level_ExitToMap
 *    with Map_ReturnStatus 0 (won: SMB3 takes the brother off its map).
 * The Boomerang Brother ($82, 1-3 - and its battles): ObjNorm_BoomerangBro (prg004) - faces the
 * Player every 16 ticks, Var5's low bits: stand $40 ticks, walk right (+8) $10, stand, walk left
 * (-8); now and then a little jump (-$30); a boomerang when Var6 & $BF comes to $1F (Timer $0F,
 * the throwing frame): SObj_Boomerang (prg007) - X +-$20 away towards the Player, Y -$16, held 15
 * frames, then: its X velocity eases (+-1) to the far limit, a pause ($30), back the other way;
 * its Y velocity eases every other frame to +-$12 and back; on its way back its thrower catches it
 * (16 x 16 of him). Palette 2 (the brother), 1 (the boomerang: Boomerang_Patterns, bank $4E).
 * Heavy and Fire Brothers (Worlds 2+) fight as Hammer Brothers for now. */

#define OBJ_HAMMERBRO 0x81
#define OBJ_BOOMERANGBRO 0x82
static void eh_quad(uint8_t pat, int pal, int x, int y, int hf, int vf, float z);
#define OBJ_TREASUREBOX 0x52
#define NHAM 6                                    /* (special object slots 0-5: HammerBro_ThrowHammer) */
static int obj_bro(int id) { return id == OBJ_HAMMERBRO || id == 0x82 || id == 0x86 || id == 0x87; }

static struct {
    int on;                                       /* (a map brother's battle: Map_EnterViaID 3-6) */
    int pics;                                     /* (the brothers' pictures made: a battle, or brothers in the level) */
    int mg_slot;                                  /* (the Micro-Goomba's picture: its slot, -1 none - smb3_stage_micro.inc) */
    int via, item;                                /* Map_EnterViaID, Level_TreasureItem */
    int slot0;                                    /* (atlas: 8 brother halves, 4 hammer halves, the box's 2, the item's 2) */
    int box_out, box_open, event_cnt, ended, clock_stop;
    int poof, poof_x, poof_y;                     /* (SOBJ_POOF: the box's) */
    uint32_t rnd;
} BT;
static struct { int on, boom, x, y, xvel, yvel, xfrac, yfrac, var1, var2, var3, timer, data; } ham[NHAM];   /* (boom: a boomerang - SOBJ_BOOMERANG) */

static int bt_rand(void) { BT.rnd = BT.rnd * 1103515245u + 12345u; return (int)(BT.rnd >> 16) & 0xFF; }   /* (RandomN) */
static void bt_reset(void) { int on = BT.on, via = BT.via, item = BT.item, s0 = BT.slot0, pics = BT.pics, mg = BT.mg_slot; memset(&BT, 0, sizeof BT);
    BT.on = on; BT.via = via; BT.item = item; BT.slot0 = s0; BT.pics = pics; BT.mg_slot = mg; BT.rnd = 0x1234567u; memset(ham, 0, sizeof ham); }

/* (level_load, before the pictures) brothers in the level's object list */
static int list_has(const uint8_t *wram, int id) {   /* (id -1: a brother) */
    uint16_t p = (uint16_t)(wram[0x1EBB] | wram[0x1EBC] << 8);
    if (p < 0xC000 || p >= 0xE000) return 0;
    const uint8_t *d = smb3_rom + 16 + 6 * 0x2000 + (p - 0xC000) + 1;
    for (int i = 0; d[0] != 0xFF && i < 96; i++, d += 3) if (id < 0 ? obj_bro(d[0]) : d[0] == id) return 1;
    return 0;
}
static int list_has_bros(const uint8_t *wram) { return list_has(wram, -1) || list_has(wram, 0x74); }
/* (level_load) the pictures */
static const uint8_t BT_BRO[8] = {0xB1, 0xB3, 0xB5, 0xB7, 0xA5, 0xA7, 0xBD, 0xBF};   /* ObjP81's halves */
static const uint8_t BT_HAM[8] = {0xA1, 0xA3, 0xB9, 0xAF, 0x89, 0x8B, 0x8D, 0x8F};   /* Hammer_Patterns', Boomerang_Patterns' */
static int bt_half(const uint8_t *t, int n, uint8_t p) { for (int i = 0; i < n; i++) if (t[i] == p) return i; return 0; }
static void bt_render(int *slot, const uint8_t *chr, uint32_t nchr, const uint8_t *ram, const uint8_t *wram) {
    BT.via = ram[0x1E]; BT.on = ram[0x70A] != 7 && BT.via >= 3 && BT.via <= 6;
    BT.item = wram[0x7963 - 0x6000];                                     /* Level_TreasureItem */
    bt_reset();
    BT.mg_slot = -1;
    BT.pics = BT.on || list_has(wram, -1) || list_has(wram, 0x74);   /* (the Micro-Goomba's picture is in the brothers' block: slot 12) */
    if (!BT.pics) return;
    if (*slot + 16 > (TEX_H_MAX / 16) * 16) { rt_log("smb3", "brothers: no room for the pictures (slot %d of %d)", *slot, (TEX_H_MAX / 16) * 16); BT.slot0 = -1; return; }
    BT.slot0 = *slot;
    /* an 8 x 16 sprite half from the $1000 table, bank index 2 forced (ObjectGroup_PatTableSel:
       OPTS_SETPT5 | $4E the brothers, | $05 the box), the colours given */
    #define HALF(sl, xo, n, bank2, c1, c2, c3) do { const uint8_t cc[4] = {0, (c1), (c2), (c3)}; \
        for (int y = 0; y < 16; y++) { \
            uint16_t a = (uint16_t)(0x1000 + ((n) & 0xFE) * 16 + (y >> 3) * 16 + (y & 7)); \
            int bi = (a - 0x1000) >> 10; uint8_t bank = bi == 2 ? (bank2) : ram[0x71B + bi]; \
            const uint8_t *c = chr + (size_t)(bank % nchr) * 0x400 + (a & 0x3FF); \
            for (int x = 0; x < 8; x++) { int p = ((c[0] >> (7 - x)) & 1) | (((c[8] >> (7 - x)) & 1) << 1); \
                atlas[(((sl) / 16) * 16 + y) * 256 + ((sl) % 16) * 16 + (xo) + x] = p ? ppu_rgb(cc[p]) : 0; } } } while (0)
    uint8_t p3[4], p1[4]; for (int i = 1; i < 4; i++) { p3[i] = ppu_peek_pal(16 + 12 + i); p1[i] = ppu_peek_pal(16 + 4 + i); }
    uint8_t p2[4]; for (int i = 1; i < 4; i++) p2[i] = ppu_peek_pal(16 + 8 + i);
    for (int k = 0; k < 8; k++) HALF(*slot + (k >> 1), (k & 1) * 8, BT_BRO[k], 0x4E, p3[1], p3[2], p3[3]);    /* (the Hammer Brother: OA1_PAL3) */
    for (int k = 0; k < 8; k++) HALF(*slot + 8 + (k >> 1), (k & 1) * 8, BT_BRO[k], 0x4E, p2[1], p2[2], p2[3]); /* (the Boomerang Brother: OA1_PAL2) */
    for (int k = 0; k < 8; k++) HALF(*slot + 4 + (k >> 1) + (k >= 4 ? 8 : 0), (k & 1) * 8, BT_HAM[k], 0x4E, p1[1], p1[2], p1[3]);  /* (hammers, boomerangs: SPR_PAL1) */
    HALF(*slot + 6, 0, 0xAB, 0x05, p3[1], p3[2], p3[3]); HALF(*slot + 6, 8, 0xAD, 0x05, p3[1], p3[2], p3[3]);  /* (the box: ObjP52's frame 0, OA1_PAL3) */
    if (BT.item >= 1 && BT.item <= 13) {          /* (the item: ObjInit_TreasureBox's palette 2 - $30, ToadItem_PalPerItem, $0F) */
        int i = BT.item - 1; uint8_t ic = TH_ITEM_PAL[BT.item];
        HALF(*slot + 7, 0, TH_ITEM_L[i], 0x05, 0x30, ic, 0x0F); HALF(*slot + 7, 8, TH_ITEM_R[i], 0x05, 0x30, ic, 0x0F);
    }
    if (list_has(wram, 0x74)) {                   /* (OBJ_PARAGOOMBAWITHMICROS: SObj_Microgoomba's $FF from bank $4F as PatTable_BankSel+5, PAL3) */
        BT.mg_slot = *slot + 12;
        for (int y = 0; y < 16; y++) {
            const uint8_t *c = chr + (size_t)(0x4F % nchr) * 0x400 + ((0xFE * 16 + (y >> 3) * 16 + (y & 7)) & 0x3FF);
            for (int x = 0; x < 8; x++) { int p = ((c[0] >> (7 - x)) & 1) | (((c[8] >> (7 - x)) & 1) << 1);
                atlas[((BT.mg_slot / 16) * 16 + y) * 256 + (BT.mg_slot % 16) * 16 + x] = p ? ppu_rgb(p3[p]) : 0; }
        }
    }
    #undef HALF
    *slot += 16;
    if (BT.on) rt_log("smb3", "battle: a map brother's battle (Map_EnterViaID %d), the treasure %d", BT.via, BT.item);
    else rt_log("smb3", "brothers: in the level - their pictures made");
}

/* the quads */
static void bt_quad(int half, int x, int y, int hf, int vf, float z) {   /* (one of bt_render's halves at level pixel x, y) */
    if (BT.slot0 < 0) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); return; }
    int sl = BT.slot0 + (half >> 1);
    float u0 = (sl % 16) * 16 / 256.0f + (half & 1) * 8 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
    if (hf) { float t = u0; u0 = u1; u1 = t; }
    if (vf) { float t = v0; v0 = v1; v1 = t; }
    quad(L.lx + x, -(L.ly + y), L.lx + x + 8, -(L.ly + y + 16), z, u0, v0, u1, v1);
}
/* Object_Draw16x32Sprite for a brother (8 below its Y): frame f's top pair and bottom pair (ObjP81
   from 4f), the halves swapped and turned when flipped, top and bottom swapped upside down */
static void bro_draw(const obj_t *o, int x, float z) {
    static const uint8_t top[2][2] = {{0xB1, 0xB3}, {0xBD, 0xBF}}, bot[2][2] = {{0xB5, 0xB7}, {0xA5, 0xA7}};
    int f = o->frame & 3, hf = (o->flip & SPR_HFLIP) != 0, vf = (o->flip & SPR_VFLIP) != 0, y = o->y + 8;
    const uint8_t *a = top[f >> 1], *b = bot[f & 1];
    if (vf) { const uint8_t *t = a; a = b; b = t; }
    for (int r = 0; r < 2; r++) {
        const uint8_t *p = r ? b : a;
        uint8_t l = hf ? p[1] : p[0], rr = hf ? p[0] : p[1];
        int pb = o->id == OBJ_BOOMERANGBRO ? 16 : 0;                     /* (its own palette's halves) */
        bt_quad(pb + bt_half(BT_BRO, 8, l), x, y + r * 16, hf, vf, z);
        bt_quad(pb + bt_half(BT_BRO, 8, rr), x + 8, y + r * 16, hf, vf, z);
    }
}

/* -- the brother -- */
static void bro_init(obj_t *o) {                  /* ObjInit_HammerBro (the battle: Var6 random) / ObjInit_BoomerangBro (Var5 random) */
    if (o->id == OBJ_BOOMERANGBRO) { o->pal = 2; o->var5 = bt_rand(); o->var7 = 0; o->flip = xdiff(o, near_pl(o)) == 0 ? SPR_HFLIP : 0; return; }
    if (o->id != OBJ_HAMMERBRO) rt_log("smb3", "brothers: brother %02X fights as a Hammer Brother (for now)", o->id);
    o->id = OBJ_HAMMERBRO; o->pal = 3; o->var7 = bt_rand();             /* (var7: Objects_Var6) */
    o->flip = xdiff(o, near_pl(o)) == 0 ? SPR_HFLIP : 0;
}
/* Object_WorldDetect4, group 2: the feet ($20, $08), going up the head ($0C, $08); walls ($15, $00 / $0F) */
static void bro_detect(obj_t *o) {
    o->det = 0;
    if (tile_at(o->x + (o->xvel < 0 ? 0 : 15), o->y + 0x15) == 2) o->det |= o->xvel < 0 ? 2 : 1;
    if (o->yvel < 0) { if (tile_at(o->x + 8, o->y + 0x0C) == 2) o->det |= 8; return; }
    if (tile_at(o->x + 8, o->y + 0x20) && (o->y & 15) < 4) o->det |= 4;
}
static void bro_move(obj_t *o) {                  /* Object_Move with group 2 */
    apply_xvel(o); apply_yvel(o); bro_detect(o);
    o->yvel += 3; if (o->yvel > 0x40) o->yvel = 0x40;
}
static void bro_throw(obj_t *o, int self, float cam_l, float cam_r) {   /* HammerBro_ThrowHammer */
    if (o->x < cam_l || o->x + 16 > cam_r) return;                      /* (Objects_SprHVis: a sprite off the screen) */
    int k = NHAM - 1; while (k >= 0 && ham[k].on) k--;
    if (k < 0) return;
    int n = near_pl(o);
    memset(&ham[k], 0, sizeof ham[k]);
    ham[k].on = 1; ham[k].x = o->x; ham[k].y = o->y; ham[k].yvel = -0x30;
    ham[k].xvel = xdiff(o, n) ? -0x12 : 0x12;                           /* (Hammer_XVel towards the Player) */
    ham[k].data = self << 4 | 0x0F;
}
static void norm_hammerbro(obj_t *o, int self, float cam_l, float cam_r) {   /* ObjNorm_HammerBro */
    int n = near_pl(o);
    o->flip = (o->flip & ~SPR_HFLIP) | (xdiff(o, n) == 0 ? SPR_HFLIP : 0);   /* (HammerBro_FacePlayerFlip) */
    o->var5++;
    o->xvel = (o->var5 & 0x40) ? 6 : -6;                                /* (walking back and forth) */
    if (!(o->det & 4)) o->var4 = 0;
    else if (!o->timer2) {
        o->var4++; hit_ground(o);
        if (!o->timer3) {
            o->timer3 = 0xC0 + (bt_rand() & 0x3E);
            int y = 2;                                                   /* (the lower part: the big jump) */
            if (!(o->y & 0x80)) { y = 0; if ((o->y & 0xFF) >= 0x30) y = bt_rand() & 2; }
            static const int jv[3] = {-0x30, 0, -0x60}, tr[3] = {0x28, 0, 0x20};   /* HammerBro_JumpYVel / _TimerReload */
            o->yvel = jv[y]; o->timer2 = tr[y];
        }
    }
    bro_move(o);
    if (counter1 & 7) o->var7++;
    int mask = (o->det & 4) ? 0x1F : 0x3F;
    if ((o->var7 & mask) == 0x1F && !o->timer) { o->timer = 0x0F; bro_throw(o, self, cam_l, cam_r); }
    o->frame = ((o->var4 & 0x10) ? 1 : 0) + (o->timer ? 2 : 0);           /* (EnemyBro_DrawAndHandleBump) */
}

static void bro_boomerang(obj_t *o, int self, float cam_l, float cam_r) {   /* BoomerangBro_ThrowBoomerang */
    if (o->x < cam_l || o->x + 16 > cam_r) return;
    int k = NHAM - 1; while (k >= 0 && ham[k].on) k--;
    if (k < 0) return;
    int y = xdiff(o, near_pl(o));
    memset(&ham[k], 0, sizeof ham[k]);
    ham[k].on = 1; ham[k].boom = 1; ham[k].x = o->x; ham[k].y = o->y;
    ham[k].xvel = y ? -0x20 : 0x20; ham[k].var2 = y ? 0 : 1;            /* Boomerang_XVel, Boomerang_ArrayValLoad */
    ham[k].yvel = -0x16; ham[k].var3 = 0; ham[k].timer = 0x40;
    ham[k].data = self << 4 | 0x0F;
}
static void norm_boomerangbro(obj_t *o, int self, float cam_l, float cam_r) {   /* ObjNorm_BoomerangBro */
    bro_move(o);
    if (o->det & 4) hit_ground(o);
    if (!(counter1 & 0x0F)) o->flip = (o->flip & ~SPR_HFLIP) | (xdiff(o, near_pl(o)) == 0 ? SPR_HFLIP : 0);   /* (BoomerangBro_FacePlayerFlip) */
    switch (o->var5 & 3) {
    case 0: case 2:                                                      /* BoomerangBro_WalkThenStop */
        if (!o->timer3) { o->var5++; o->timer3 = 0x40; }
        o->xvel = 0;
        break;
    default: {                                                           /* BoomerangBro_WalkRight / _WalkLeft */
        o->xvel = (o->var5 & 3) == 1 ? 8 : -8;
        o->var4 += 2;
        if (!(counter1 & 0xFF) && (bt_rand() & 0x80)) o->yvel = -0x30;   /* (a little jump) */
        if (!o->timer3) { o->var5++; o->timer3 = 0x10; }
        int v = o->var7; o->var7 = (o->var7 + 1) & 0xFF;
        if ((v & 0xBF) == 0x1F) { o->timer = 0x0F; bro_boomerang(o, self, cam_l, cam_r); }
        break; }
    }
    o->frame = ((o->var4 & 0x10) ? 1 : 0) + (o->timer ? 2 : 0);           /* (EnemyBro_DrawAndHandleBump) */
}
/* -- the hammers (SObj_Hammer) and boomerangs (SObj_Boomerang) -- */
static void hams_frame(float cam_l, float cam_r) {
    for (int k = 0; k < NHAM; k++) {
        if (!ham[k].on) continue;
        if (ham[k].data & 0x0F) {                                        /* (still in the hand) */
            ham[k].data--;
            obj_t *o = &ob[(ham[k].data >> 4) % NOBJ];
            if (o->state != OS_NORMAL || !obj_bro(o->id) || o->x + 8 < cam_l) { ham[k].on = 0; continue; }
            int hf = (o->flip & SPR_HFLIP) != 0;
            ham[k].x = o->x + (hf ? -8 : 8); ham[k].y = o->y + 3;        /* (Hammer_XOff / Hammer_YOff) */
            if ((ham[k].xvel < 0 ? 0 : SPR_HFLIP) != (o->flip & SPR_HFLIP)) { ham[k].xvel = -ham[k].xvel; ham[k].var2++; }   /* (turned with its brother) */
            continue;
        }
        if (ham[k].timer) ham[k].timer--;
        if (ham[k].boom) {                                               /* SObj_Boomerang */
            ham[k].var1++;
            if (ham[k].var2 >= 0 && !ham[k].timer) {
                int y = ham[k].var2 & 1;
                ham[k].xvel += y ? -1 : 1;                               /* Boomerang_XVelDelta */
                if (ham[k].xvel == (y ? -0x20 : 0x20)) {                 /* Boomerang_XVelLimit */
                    ham[k].timer = 0x30; ham[k].var2++;
                    if (ham[k].var3) ham[k].var2 = -1;                   /* (on its way back) */
                }
            }
            if (!(counter1 & 1) && !(ham[k].var3 >= 1 && ham[k].yvel == 0)) {
                int y = ham[k].var3 & 1;
                ham[k].yvel += y ? -1 : 1;                               /* Boomerang_YVelAccel */
                if (ham[k].yvel == (y ? -0x12 : 0x12)) ham[k].var3++;    /* Boomerang_YVelLimit */
            }
            int p = ham[k].x * 16 + ham[k].xfrac + ham[k].xvel; ham[k].x = p >> 4; ham[k].xfrac = p & 15;   /* SObj_AddXVelFrac / _AddYVelFrac */
            p = ham[k].y * 16 + ham[k].yfrac + ham[k].yvel; ham[k].y = p >> 4; ham[k].yfrac = p & 15;
            if (ham[k].var2 < 0 && !((k + counter1) & 1)) {             /* (its thrower catches it) */
                obj_t *o = &ob[(ham[k].data >> 4) % NOBJ];
                if (o->state == OS_NORMAL && o->id == OBJ_BOOMERANGBRO && (unsigned)(ham[k].y + 8 - o->y - 8) < 16 && (unsigned)(ham[k].x + 8 - o->x) < 16) { ham[k].on = 0; continue; }
            }
            if (ham[k].x < cam_l - 64 || ham[k].x > cam_r + 64 || ham[k].y > LH * 16 + 16 || ham[k].y < -64) { ham[k].on = 0; continue; }
            goto collide;
        }
        ham[k].var1++;
        int p = ham[k].x * 16 + ham[k].xfrac + ham[k].xvel; ham[k].x = p >> 4; ham[k].xfrac = p & 15;   /* SObj_ApplyXYVelsWithGravity */
        p = ham[k].y * 16 + ham[k].yfrac + ham[k].yvel; ham[k].y = p >> 4; ham[k].yfrac = p & 15;
        if (ham[k].yvel < 0x6E) ham[k].yvel += 2;
        if (ham[k].x < cam_l - 32 || ham[k].x > cam_r + 32 || ham[k].y > LH * 16 + 16 || ham[k].y < -64) { ham[k].on = 0; continue; }
    collide:
        if (!((k + counter1) & 1)) continue;                             /* SObj_PlayerCollide */
        for (int n = 0; n < 8; n++) {
            if (!pp[n].on || pp[n].star) continue;
            int dy = ham[k].y + 8 - pp[n].y - (pp[n].small ? 18 : 10), dx = ham[k].x + 6 - pp[n].x;
            if (dy >= 0 && dy < (pp[n].small ? 0x10 : 0x16) && dx >= 0 && dx < 16) pl_hurt(n);
        }
    }
}

/* -- the treasure box -- */
static void bt_poof(int x, int y) { BT.poof = 0x1F; BT.poof_x = x; BT.poof_y = y; }
static void box_frame(obj_t *o) {                 /* ObjNorm_TreasureBox */
    if (o->timer) { if (o->timer == 0x18) bt_poof(o->x, o->y); return; }
    if (!o->var4) {
        obj_move2(o);
        if ((o->det & 4) && o->yvel >= 0) { int yv = o->yvel; hit_ground(o); if (yv > 0x20) o->yvel = -(yv >> 2); }   /* (Object_DoMoveBounceConveyor) */
        for (int n = 0; n < 8; n++) if (pp[n].on && intersect(pl_box(n), obj_box(o))) {   /* (Object_HitTest: opened) */
            o->var4 = 1; o->yvel = -0x30; BT.box_open = 1; BT.clock_stop = 1; bt_poof(o->x, o->y);
            rt_log("smb3", "battle: player %d opens the treasure box (%d)", n + 1, BT.item);
            break;
        }
        return;
    }
    if (o->timer2) {
        if (o->timer2 == 1) {                                            /* (Player_GetItem, then the countdown to the map) */
            uint8_t *w = nes_wram_ptr(); int s = 0;
            while (s < 27 && w[(INVENTORY_ITEMS - 0x6000) + s]) s++;
            if (s < 27 && BT.item) w[(INVENTORY_ITEMS - 0x6000) + s] = (uint8_t)BT.item;
            rt_log("smb3", "battle: item %d into the inventory (slot %d)", BT.item, s);
            o->state = OS_DEAD; BT.event_cnt = 0x60;
        }
        return;
    }
    apply_yvel(o); o->yvel++;                                            /* Object_ApplyYVel_NoLimit */
    if (o->yvel >= 0) o->timer2 = 0x70;
}
/* (each frame, after the objects) LevelEvent_TreasureBox */
static void bt_frame(float cam_l, float cam_r) {
    if (!BT.pics) return;
    hams_frame(cam_l, cam_r);
    if (!BT.on) return;
    if (getenv("SMB3_BATTLE_TEST_WIN") && counter1 == atoi(getenv("SMB3_BATTLE_TEST_WIN")))   /* (testing: the brothers beaten at frame N) */
        for (int i = 0; i < NOBJ; i++) if (ob[i].state == OS_NORMAL && obj_bro(ob[i].id)) { ob[i].state = OS_KILLED; ob[i].yvel = -0x30; }
    if (BT.poof) BT.poof--;
    if (BT.event_cnt) {
        if (!--BT.event_cnt && !BT.ended) {
            BT.ended = 1;
            for (int i = 0; i < 8; i++) kept_rest[i] = (int)R32(MOD_PY_REST + 4 * (uint32_t)i);   /* (no life lost) */
            keep_rest = 1;
            if (map_level_end(blk_ctx, blk_base, 0)) rt_log("smb3", "battle: won - SMB3's map");
        }
        return;
    }
    if (BT.box_out || objs_started < 30) return;
    for (int k = 0; k < NHAM; k++) if (ham[k].on) return;
    for (int i = 0; i < NOBJ; i++) if (ob[i].state != OS_DEAD) return;
    for (int k = 0; k < OL.n; k++) if (obj_bro(OL.id[k]) && !OL.spawned[k]) return;   /* (one not out yet) */
    int s = 0; obj_t *o = &ob[s]; memset(o, 0, sizeof *o);
    int n = sb_first_player(); if (n < 0 || n > 7 || !pp[n].on) n = near_pl(o);
    int px = n >= 0 ? pp[n].x - (int)cam_l : 0;
    o->id = OBJ_TREASUREBOX; o->state = OS_NORMAL; o->spawn = -1; o->holder = -1; o->pal = 3;
    o->y = 0x170; o->x = (int)cam_l + ((px & 0x80) ? 0x30 : 0xC0); o->timer = 0x1F;   /* (ObjInit_TreasureBox: $1F ticks to the poof) */
    BT.box_out = 1;
    rt_log("smb3", "battle: the brothers beaten - the treasure box at (%d, %d)", o->x, o->y);
}
static void box_draw(const obj_t *o, float z) {   /* (2 quads) */
    if (o->timer) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); quad(0, 0, 0, 0, 0, 0, 0, 0, 0); return; }
    if (!o->var4) { bt_quad(12, o->x, o->y, 0, 0, z); bt_quad(13, o->x + 8, o->y, 0, 0, z); return; }
    if (o->timer2 && !(o->timer2 & 0x0C)) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); quad(0, 0, 0, 0, 0, 0, 0, 0, 0); return; }   /* (12 on, 12 off) */
    int m = BT.item >= 1 && BT.item <= 13 && (TH_ITEM_AR[BT.item - 1] & 0x40);   /* (TBoxItem_MirrorFlags: the right half the left turned) */
    bt_quad(14, o->x, o->y, 0, 0, z); bt_quad(15, o->x + 8, o->y, m, 0, z);
}
#define BT_QUADS (NHAM * 2 + 2)
static int bt_quads(void) { return BT.pics ? BT_QUADS : 0; }
static void bt_draw(float z) {                    /* the hammers (Hammer_Draw), boomerangs, the poof */
    if (!BT.pics) return;
    static const uint8_t HP[12] = {0xA1, 0xA3, 0xB9, 0xB9, 0xA3, 0xA1, 0xAF, 0xAF, 0xA1, 0xA3, 0xB9, 0xB9};
    static const uint8_t HA[8] = {0x00, SPR_HFLIP, SPR_HFLIP, SPR_HFLIP | SPR_VFLIP, SPR_HFLIP | SPR_VFLIP, SPR_VFLIP, SPR_VFLIP, 0x00};
    for (int k = 0; k < NHAM; k++) {
        if (!ham[k].on) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); quad(0, 0, 0, 0, 0, 0, 0, 0, 0); continue; }
        if (ham[k].boom) {                                               /* (PRG007_B798: Boomerang_Attributes / _Patterns by Var1 & %1100) */
            static const uint8_t BA[4] = {SPR_HFLIP | SPR_VFLIP, SPR_HFLIP | SPR_VFLIP, 0, 0}, BP[6] = {0x8B, 0x8F, 0x89, 0x8D, 0x8B, 0x8F};
            int t1 = ham[k].xvel >= 0 ? SPR_HFLIP : 0, x = (ham[k].var1 & 0x0C) >> 2, at = t1 ^ BA[x];
            if (t1) x += 2; x &= 3;
            int hf = (at & SPR_HFLIP) != 0, vf = (at & SPR_VFLIP) != 0;
            bt_quad(28 + bt_half(BT_HAM + 4, 4, BP[x]), ham[k].x, ham[k].y, hf, vf, z);
            bt_quad(28 + bt_half(BT_HAM + 4, 4, BP[x + 2]), ham[k].x + 8, ham[k].y, hf, vf, z);
            continue;
        }
        int fl = ham[k].xvel < 0 ? SPR_HFLIP : 0, f = (ham[k].var1 >> 2) & 7, at = fl ^ HA[f], pf = (f + (fl ? 4 : 0)) & 7;
        int hf = (at & SPR_HFLIP) != 0, vf = (at & SPR_VFLIP) != 0;
        bt_quad(8 + bt_half(BT_HAM, 4, HP[pf]), ham[k].x, ham[k].y, hf, vf, z);
        bt_quad(8 + bt_half(BT_HAM, 4, HP[pf + 4]), ham[k].x + 8, ham[k].y, hf, vf, z);
    }
    if (BT.poof) {                                /* (SOBJ_POOF: PoofDeath_Pats by timer / 8) */
        static const uint8_t poof[4] = {0x47, 0x45, 0x41, 0x43};
        uint8_t pt = poof[(BT.poof >> 3) & 3]; int vf = (counter1 >> 1) & 1;
        eh_quad(pt, 1, BT.poof_x, BT.poof_y, 0, vf, z); eh_quad(pt, 1, BT.poof_x + 8, BT.poof_y, 1, !vf, z);
    } else { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); quad(0, 0, 0, 0, 0, 0, 0, 0, 0); }
}
