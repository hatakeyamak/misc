BEGIN{
OFS = " ; ";
printf("dependent_variables:\n");
printf("- header: {name: number of events}\n");
printf("  qualifiers:\n");
printf("    - {name: SQRT(S) = 13 TeV, value: .}\n");
printf("    - {name: '', value: predicted background}\n");
printf("  value:\n");
}
{
    # first line
    printf("  - errors:\n");
    # stat error
    if ($14=="\\pm") printf("    - {label: stat, symerror: %s}\n",$15);
    else {
	printf("    - asymerror: {minus: %s, plus: %s}\n",-$18,$15);
	printf("      label: stat\n");
	
    }
    # syst error
    if ($16=="\\pm") printf("    - {label: sys, symerror: %s}\n",$17);
    # syst error
    else if ($20=="\\pm") printf("    - {label: sys, symerror: %s}\n",$21);
    else if ($16=="\^{+"){
	printf("    - asymerror: {minus: %s, plus: %s}\n",-$20,$17);
	printf("      label: sys\n");	
    }
    else {
	printf("    - asymerror: {minus: %s, plus: %s}\n",-$24,$21);
	printf("      label: sys\n");
	
    }
    # central
    printf("    value: %s\n",$13);
    #print $0
    #print $1,$2,$3,$4,$5,$6,$7,$8,$9,$10
    #print $11,$12,$13,$14,$15,$16,$17,$18,$19,$20
    #print $21,$22,$23,$24,$25,$26,$27,$28,$29,$30
}
