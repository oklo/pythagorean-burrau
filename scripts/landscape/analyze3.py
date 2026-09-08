import json, sys, re, numpy as np
rows=[json.loads(re.sub(r"-?(nan|inf)","null",l)) for l in open(sys.argv[1])]
umin=float(sys.argv[2]) if len(sys.argv)>2 else 0.10
rows=[r for r in rows if r["u"]>=umin]; rows.sort(key=lambda r:r['u'])
for r in rows:
    for k in ('Herr','Herrmax'):
        if r[k] is None: r[k]=1.0
u=np.array([r['u'] for r in rows]); v=np.array([r['verdict'] for r in rows]); te=np.array([r['t_end'] for r in rows])
He=np.array([r['Herrmax'] for r in rows])
print("n",len(rows),"escape",np.sum(v==1),"collision(<1e-9)",np.sum(v==2),"unresolved(t=80)",np.sum(v==0))
print("Herrmax quantiles:",np.quantile(He,[0.5,0.9,0.99,0.999]))
good=[r for r in rows if r['Herrmax']<1e-9]
print("good (Herrmax<1e-9):",len(good))
bad=[r for r in rows if r['t_syz1']>0 and r['t_imin1']>0 and r['t_imin1']<r['t_syz1']]
print("first I-min before first syzygy:",len(bad))
ratio=np.array([r['Kmin_over_U0'] for r in good]); idx=np.argsort(ratio)[:40]
print("closest approaches to a second brake (min K/U0 over events, good runs):")
for i in idx:
    r=good[i]; st=[int(s) for s in r['stut'].split(',') if s]
    print(f"  u={r['u']:.5f} K/U0={ratio[i]:.3e} t={r['t_Kmin']:.3f} arc={r['arc_Kmin']} type={r['type_Kmin']} in_stutter={r['arc_Kmin'] in st} nsyz={r['nsyz']} nstut={r['nstut']} t_end={r['t_end']:.2f} verdict={r['verdict']} esc={r['escaper']+1} rmin={r['rmin']:.1e}")
ns=np.array([r['nstut'] for r in good]); print("nstut hist (good):",np.bincount(ns))
cnt=sum(1 for r in good if r['nstut']>0 and r['arc_Kmin'] in [int(s) for s in r['stut'].split(',') if s])
print("good runs with >=1 stutter:",int(np.sum(ns>0)),"; min-K event lies in a stutter arc:",cnt)
ins=[];outs=[]
for r in good:
    st=set(int(s) for s in r['stut'].split(',') if s)
    for ev in r['ev']:
        t,arc,typ,KU,z,Idot,rm=ev
        if typ!=1: continue
        (ins if arc in st else outs).append(KU)
ins=np.array(ins);outs=np.array(outs)
print("K-minima in stutter arcs:",len(ins),"K/U0 quantiles",np.quantile(ins,[0,0.01,0.1,0.5]).round(5) if len(ins) else None)
print("K-minima (K/U0<0.05) in non-stutter arcs:",len(outs),"K/U0 quantiles",np.quantile(outs,[0,0.01,0.1,0.5]).round(5) if len(outs) else None)
for T in [5,10,20,40,80]:
    print(f"fraction escaped by t={T}: {np.mean((v==1)&(te<=T)):.3f}")
bins=np.arange(0.10,0.42,0.02)
for a,b in zip(bins[:-1],bins[1:]):
    sel=(u>=a)&(u<b)
    if sel.sum()==0: continue
    esc=np.array([r['escaper'] for r in rows])
    print(f"u in [{a:.2f},{b:.2f}): esc%={100*np.mean(v[sel]==1):5.1f} coll%={100*np.mean(v[sel]==2):4.1f} med_t={np.median(te[sel]):5.2f} p90={np.quantile(te[sel],0.9):5.2f} escapers={[int(np.sum(esc[sel]==k)) for k in range(3)]} Herr_bad%={100*np.mean(He[sel]>1e-9):4.1f}")
