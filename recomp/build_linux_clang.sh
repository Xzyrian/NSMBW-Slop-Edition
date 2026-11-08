#!/bin/sh
# Linux build using the same compiler as the Windows build (zig/clang -O2) to reproduce
# compiler-specific issues locally.
set -e
cd "$(dirname "$0")"
ZCC="python3 -m ziglang cc -target x86_64-linux-gnu"
FLAGS="-std=gnu11 -O2 -g -w -fno-stack-protector -fcf-protection=none -Iruntime -Iout -DPPC_TRACE"
sh tools/gen.sh
mkdir -p out/objclang
for f in out/recomp_*.c; do o=out/objclang/$(basename $f).o; [ -f "$o" ] && [ "$o" -nt "$f" ] && continue; echo "$f"; done | \
  xargs -r -P "$(nproc)" -I{} sh -c "$ZCC $FLAGS -c {} -o out/objclang/\$(basename {}).o || { rm -f out/objclang/\$(basename {}).o; exit 1; }"
python3 tools/version_header.py >/dev/null
for f in rt_core rt_bootscreen rt_hw rt_ios rt_disc rt_gx rt_gxrender rt_wiimote rt_threads rt_ax rt_hdtex rt_aspect rt_menu rt_gamesetup rt_title rt_lyt rt_mod smb1_physics rt_retro rt_sfx rt_chars rt_charmdl rt_remotes rt_net rt_det rt_state rt_profiles rt_crypto rt_update rt_si rt_discord rt_dvd rt_vi rt_exi rt_audio rt_os gm_verify gm_mj2d_game gm_mj2d_header gm_save_mng gm_info gm_c_list gm_f_list gm_f_base gm_f_manager gm_s_state gm_d_base gm_d_actor gm_d_enemy gm_d_enemy_death gm_d_enemy_carry gm_bg gm_m3d gm_m3d_scene gm_m3d_anm gm_m_mtx gm_m_heap gm_m_allocator gm_m_fader gm_d_cc gm_m_2d gm_m_frustum gm_s_lib gm_c_lib gm_m_color gm_d_cd gm_d_rail gm_d_actorcreate gm_d_wipe gm_d_smallscore gm_d_scene gm_d_next gm_d_lytbase gm_d_wm gm_d_stage gm_d_2d gm_d_res gm_d_lytbuild gm_d_lyttextbox gm_d_message gm_d_selectcursor gm_d_util gm_d_misc gm_nw4r_ut gm_egg gm_nw4r_g3d gm_state_ids gm_prologue gm_py_mng gm_py_demo gm_d_gamedisplay rt_plat_linux; do $ZCC $FLAGS -c runtime/$f.c -o out/objclang/$f.o; done
BUILD_TMP=${BUILD_TMP:-/tmp/nsmbw_build}; mkdir -p "$BUILD_TMP"
rm -f out/objclang/rt_bt.o   # (removed: WUD is native, rt_wiimote.c)
$ZCC out/objclang/*.o -lm -lpthread -ldl -o "$BUILD_TMP/nsmbw_clang"
echo built $BUILD_TMP/nsmbw_clang   "# test build: run from recomp/ as  \$BUILD_TMP/nsmbw_clang . ../extracted"
find . \( -name '.fuse_hidden*' -o -name '*.tmp*' \) -type f -exec rm -f {} + 2>/dev/null || true
