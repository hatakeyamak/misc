
grep -v % SUS16050_Table2.tex | awk -f Table234_column_pred.awk >  SUS16050_Table2.yaml
grep -v % SUS16050_Table2.tex | awk -f Table234_column_obs.awk  >> SUS16050_Table2.yaml
grep -v % SUS16050_Table2.tex | awk -f Table234_column_1st.awk  >> SUS16050_Table2.yaml
cat SUS16050_Table2.yaml

grep -v % SUS16050_Table3.tex | awk -f Table234_column_pred.awk >  SUS16050_Table3.yaml
grep -v % SUS16050_Table3.tex | awk -f Table234_column_obs.awk  >> SUS16050_Table3.yaml
grep -v % SUS16050_Table3.tex | awk -f Table234_column_1st.awk  >> SUS16050_Table3.yaml
cat SUS16050_Table3.yaml

grep -v % SUS16050_Table4.tex | awk -f Table234_column_pred.awk >  SUS16050_Table4.yaml
grep -v % SUS16050_Table4.tex | awk -f Table234_column_obs.awk  >> SUS16050_Table4.yaml
grep -v % SUS16050_Table4.tex | awk -f Table234_column_1st.awk  >> SUS16050_Table4.yaml
cat SUS16050_Table4.yaml

echo "dependent_variables:" > SUS16050_Table4aux.yaml
grep -v % SUS16050_Table4aux.tex | awk -v signal="T2tt(1100,1)"  -v col=1 -f Table45aux_column_signals.awk  >> SUS16050_Table4aux.yaml
grep -v % SUS16050_Table4aux.tex | awk -v signal="T2tt(900,450)" -v col=2 -f Table45aux_column_signals.awk  >> SUS16050_Table4aux.yaml
grep -v % SUS16050_Table4aux.tex | awk -v signal="T2tt(500,325)" -v col=3 -f Table45aux_column_signals.awk  >> SUS16050_Table4aux.yaml
grep -v % SUS16050_Table4aux.tex | awk                                   -f Table45aux_column_1st.awk      >> SUS16050_Table4aux.yaml
cat SUS16050_Table4aux.yaml

echo "dependent_variables:" > SUS16050_Table5aux.yaml
grep -v % SUS16050_Table5aux.tex | awk -v signal="T1tttt(2000,100)"  -v col=1 -f Table45aux_column_signals.awk  >> SUS16050_Table5aux.yaml
grep -v % SUS16050_Table5aux.tex | awk -v signal="T1tttt(1800,1100)" -v col=2 -f Table45aux_column_signals.awk  >> SUS16050_Table5aux.yaml
grep -v % SUS16050_Table5aux.tex | awk -v signal="T5ttcc(1750,900)"  -v col=3 -f Table45aux_column_signals.awk  >> SUS16050_Table5aux.yaml
grep -v % SUS16050_Table5aux.tex | awk                                   -f Table45aux_column_1st.awk      >> SUS16050_Table5aux.yaml
cat SUS16050_Table5aux.yaml

