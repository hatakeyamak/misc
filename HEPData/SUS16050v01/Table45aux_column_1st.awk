BEGIN{
printf("independent_variables:\n");
printf("- header: {name: Search Bin}\n");
printf("  value:\n");
nsearchbin=1;
}
{
    if ($1>=7)
	 printf("  - {value: '%d) Ntops=%d, Nbjets=%d, HT=%s, pTmiss=%s'}\n",$1,$3,$5,$7,$9);
    else printf("  - {value: '%d) Ntops=%d, Nbjets=%d, MT2=%s, pTmiss=%s'}\n",$1,$3,$5,$7,$9);
    nsearchbin++;
}
