import subprocess, json, sys, numpy as np
def st(u,t):
    d=1+u*u; m1=(1-u*u)/d; m2=2*u/d
    r=json.loads(subprocess.run(['./ms3',f'{m1:.17g}',f'{m2:.17g}',f'{t}'],capture_output=True,text=True).stdout)
    return np.array(r['q']+r['v']).ravel()
u=float(sys.argv[1]); h=1e-9
for t in [0.3,0.4,0.44,0.46,0.47,0.475,0.48,0.49,0.50,0.52,0.55,0.6,0.7,0.8,1.0,1.5,2.0,3.0]:
    s=(st(u+h,t)-st(u-h,t))/(2*h)
    print(f"t={t:5.3f} |dstate/du|={np.abs(s).max():.3e}")
