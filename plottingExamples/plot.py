# exec(open("plot.py").read())

import ROOT
import numpy as np

tf = ROOT.TFile('histOut.root')

tf.cd("plots")
tf.ls()

npdf=100;
th={}
xsec=[]

for i in range(0, npdf+1):
    th[i] = tf.Get("plots/mass"+str(i))
    if i>=1:
        xsec.append(th[i].GetSum())
        print(th[i].GetSum())
    th[i].Scale(1./th[i].GetSum());
    if i==0:
        th[i].SetLineWidth(5);
        th[i].SetLineColor(2);
        th[i].SetMaximum(th[i].GetMaximum()*2.)
        th[i].Draw("hist")
    else:
        th[i].Draw("sames,hist")

print(xsec)
nparr_xsec = np.array(xsec)
print(nparr_xsec)

nparr_xsec_mean = np.array(nparr_xsec.size * [np.mean(nparr_xsec)])
print(nparr_xsec_mean)

# mean yield
yield_mean=np.mean(nparr_xsec)
print(yield_mean)

# variation in the yield for PDF error
# https://arxiv.org/abs/1510.03865
yield_rms=np.sqrt(np.mean((nparr_xsec-nparr_xsec_mean)**2))
if nparr_xsec.size>0:
    yield_rms = yield_rms * nparr_xsec.size / (nparr_xsec.size - 1)
print(yield_rms / yield_mean)

