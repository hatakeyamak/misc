#!/bin/bash

# Direct stop models
root.exe -b -q 'HEPData_dump.C("CMS-SUS-16-050_Figure_008.root","T2tt","t")'

# Gluino models
root.exe -b -q 'HEPData_dump.C("CMS-SUS-16-050_Figure_009-a.root","T1tttt","g")'
root.exe -b -q 'HEPData_dump.C("CMS-SUS-16-050_Figure_009-b.root","T1ttbb","g")'
root.exe -b -q 'HEPData_dump.C("CMS-SUS-16-050_Figure_009-c.root","T5tttt","g")'
root.exe -b -q 'HEPData_dump.C("CMS-SUS-16-050_Figure_009-d.root","T5ttcc","g")'


