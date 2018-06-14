import sys,os
import math
from optparse import OptionParser

# define options
parser = OptionParser()
parser.add_option("-t", "--tower", dest="tower", default=28, help="tower number")
parser.add_option("-b", "--border", dest="border", default=0, help="tower border (0 = center, -1 = low eta, 1 = high eta")
parser.add_option("-p", "--phistep", dest="phistep", default=1, help="phi step")
parser.add_option("-d", "--dir", dest="dir", default="phi1", help="file directory")
(options, args) = parser.parse_args()

PHISTEP=int(options.phistep)
TOWERNUM=int(options.tower)
TBORNAME=""
if int(options.border)==1:
    TBORNAME="hi"
elif int(options.border)==-1:
    TBORNAME="lo"

TOWERNAME=str(abs(TOWERNUM))
if TOWERNUM<0:
    TOWERNAME="m"+TOWERNAME
    
output = open("log_results_tower"+TOWERNAME+TBORNAME+"_phi"+str(PHISTEP)+".txt",'w')
for PHINUM in range(0,360/PHISTEP):
    #phi spans 0 to 2pi
    phival = (PHISTEP*PHINUM)*math.pi/180
    
    cmd = "./matbudget_log_reader.exe "+options.dir+"/detailedInfo_tower"+TOWERNAME+TBORNAME+"_phi"+str(PHISTEP)+"_"+str(PHINUM)+".log "+options.dir+"/log_matbudget_tower"+TOWERNAME+TBORNAME+"_phi"+str(PHISTEP)+"_"+str(PHINUM)+".txt"
    print cmd
    pipe = os.popen(cmd)
    result = pipe.read().rstrip()
    exitcode = pipe.close()
    if exitcode!=None: continue
    result = str(TOWERNUM)+"\t"+str(phival)+"\t"+result
    output.write(result+"\n")
output.close()
