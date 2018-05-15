BEGIN{
printf("- header: {name: signal yields}\n");
printf("  qualifiers:\n");
printf("    - {name: SQRT(S) = 13 TeV, value: .}\n");
printf("    - {name: '', value: %s}\n",signal);
printf("  value:\n");
}
{
    if (col==1) printf("  - {value: %s}\n",$11);    
    else if (col==2) printf("  - {value: %s}\n",$13);    
    else if (col==3) printf("  - {value: %s}\n",$15);    
}
