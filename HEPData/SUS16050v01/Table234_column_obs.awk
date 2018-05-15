BEGIN{
printf("- header: {name: number of events}\n");
printf("  qualifiers:\n");
printf("    - {name: SQRT(S) = 13 TeV, value: .}\n");
printf("    - {name: '', value: observed data}\n");
printf("  value:\n");
}
{
    printf("  - {value: %d}\n",$11);    
}
