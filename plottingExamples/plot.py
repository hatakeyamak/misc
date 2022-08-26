# exec(open("plot.py").read())

import ROOT
import numpy as np

tf = ROOT.TFile('histOut.root')

tf.cd("plots")
tf.ls()

npdf=100
th={}
xsec=[]
signal_peak_frac=[]

# ---
def get_mean_PDFerror(arr):
    #print(arr)
    nparr = np.array(arr)
    nparr_mean = np.array(nparr.size * [np.mean(nparr)])

    # mean yield
    mean=np.mean(nparr)

    # variation in the yield for PDF error
    # https://arxiv.org/abs/1510.03865
    err=np.sqrt(np.mean((nparr-nparr_mean)**2))
    if nparr.size>0:
        err = err * nparr.size / (nparr.size - 1)

    return mean, err

# ---
mpeak=5000

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
        signal_peak_frac.append(th[i].Integral(th[i].FindBin(mpeak*0.85),th[i].FindBin(mpeak*1.15)))

# ---
# xsec(yield) array
#
print("yields mean and fractional error")

yield_mean, yield_err = get_mean_PDFerror(xsec)
print(yield_mean, yield_err/yield_mean)

# ---
# mean signal peak fraction
#

print("signal_peak_frac (+-15% of the resonance mass) mean and fractional error")

signal_peak_frac_mean, signal_peak_frac_err = get_mean_PDFerror(signal_peak_frac)
print(signal_peak_frac_mean, signal_peak_frac_err/signal_peak_frac_mean)
