"""List the sounds of NSMBW's sound archive: id, name, type, player, volume.

usage: brsar_sounds.py game/disc/files/Sound/wii_mj2d_sound.brsar

(port/smb3_stage_music.inc: NSMBW's BGM are the sounds on players 16-19 and 21 - the streams
STRM_BGM_* and the SEQ_BGM_*_V voices - plus SE_SYS_HURRY_UP and SE_BGM_CS_STAR)"""
import struct,sys
d=open(sys.argv[1],'rb').read()
be=lambda o:struct.unpack('>I',d[o:o+4])[0]
assert d[:4]==b'RSAR'
symb=be(0x10); info=be(0x18)
# SYMB
sb=symb+8
strtab=sb+be(sb)
n=be(strtab)
names=[]
for i in range(n):
    o=sb+be(strtab+4+4*i); e=d.index(b'\0',o); names.append(d[o:e].decode())
ib=info+8
def ref(o): # DataRef: u8 isOffset, u8 dtype, u16 pad, u32 value
    return be(o+4)
snd_tab=ib+ref(ib)
cnt=be(snd_tab)
out=[]
for i in range(cnt):
    so=ib+ref(snd_tab+4+8*i)
    nameidx=be(so); fileid=be(so+4); player=be(so+8)
    vol=d[so+0x14]; prio=d[so+0x15]; typ=d[so+0x16]
    out.append((i,names[nameidx] if nameidx<len(names) else '?',typ,player,vol))
for i,nm,t,p,v in out: print(i,nm,{1:'SEQ',2:'STRM',3:'WAVE'}.get(t,t),p,v)
