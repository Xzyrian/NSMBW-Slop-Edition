/* gm_d_wm_map.c - daWmMap_c: route-access queries (track B, gm_i2.h).
 * Map objects and route data remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define WMMAP_ALL_ROUTES_OPEN (0x81860000u - 508 + 1)

static uint32_t wmmap_isRouteOpen(GM_CTX) {
    I2_FN(0x81828808u);
    R(5) = gm_u8(WMMAP_ALL_ROUTES_OPEN); CMPU(R(5), 0); R(5) = 1;
    if (CR_BIT(ctx, 2)) {
        BL(0x81828830u, ext_fn_2_174AB0_81845410);
        R(5) = R(3);
    }
    R(3) = R(5); return R(3);
}

static uint32_t wmmap_isIbaraRouteOpen(GM_CTX) {
    I2_FN(0x81828848u);
    R(6) = gm_u8(WMMAP_ALL_ROUTES_OPEN); CMPU(R(6), 0); R(6) = 1;
    if (CR_BIT(ctx, 2)) {
        BL(0x81828870u, ext_fn_2_174BE0_81845418);
        R(6) = R(3);
    }
    R(3) = R(6); return R(3);
}

GM_HLE_VERIFIED_(mod_fn_2_174AB0, GMV_IGNORE_POLLS, 0, 0) { R(3) = wmmap_isRouteOpen(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_174BE0, GMV_IGNORE_POLLS, 0, 0) { R(3) = wmmap_isIbaraRouteOpen(GM_PASS); }
