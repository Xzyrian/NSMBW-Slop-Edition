# tools/memdiff.py a.mem b.mem [x.pages]: the words that differ between two RT_DET_DUMP_MEM dumps (rt_det.c),
# leaving out what RT_DET_HASH_LIVE leaves out (the "live" lines of a .pages file). docs/DECOMP.md.
import sys, struct
a=open(sys.argv[1],'rb').read(); b=open(sys.argv[2],'rb').read()
live=[]
if len(sys.argv)>3:
    for l in open(sys.argv[3]):
        if l.startswith('live'): _,lo,hi=l.split(); live.append((int(lo,16),int(hi,16)))
def addr(o): return 0x80000000+o if o < 24<<20 else 0x90000000+o-(24<<20)
n=0
for pg in range(0,len(a),0x1000):
    if a[pg:pg+0x1000]==b[pg:pg+0x1000]: continue
    for o in range(pg,pg+0x1000,4):
        if a[o:o+4]!=b[o:o+4]:
            ad=addr(o)
            if any(lo<=ad<hi for lo,hi in live): continue
            n+=1
            if n<=60: print('%08X %s %s' % (ad, a[o:o+4].hex(), b[o:o+4].hex()))
print('words:', n)
