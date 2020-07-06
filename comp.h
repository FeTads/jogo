int comps(char str1[40], char str2[40]){
	
    int i, j;
    char c1, c2;

    for(i=0; str1[i]!='\0'; i++);
    for(j=0; str2[j]!='\0'; j++);
    
    if (i != j) {
        return 1;
    }
    else {
        for(i=0; i<j; i++) {
            c1 = str1[i];
            c2 = str2[i];
            if (c1 >= 65 & c1 <= 90) c1 = c1 + 32;
            if (c2 >= 65 & c2 <= 90) c2 = c2 + 32;
    
            if (c1 != c2){
                return 1;                
            }
        }	
			//Retorna 0 para palavra igual e 1 para palavra diferente
        return 0;
    }
}
