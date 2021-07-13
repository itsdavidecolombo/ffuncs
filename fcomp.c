//
//  fcomp.c
//  
//
//  Created by Davide Colombo on 13/07/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 150

char *fgets_(char *, int, FILE *);

int main(int argc, char *argv[]){
    
    char *progname = argv[0];
    if(argc != 3){
        fprintf(stderr, "%s: wrong number of arguments. Usage: ./a.out f1 f2\n", progname);
        exit(1);
    }
    
    FILE *fp1, *fp2;                                /* pointers to the files to be compared */
    char *fn1, *fn2;
    
    if((fp1 = fopen((fn1 = *++argv), "r")) == NULL ||
       (fp2 = fopen((fn2 = *++argv), "r")) == NULL){        /* open and test */
        fprintf(stderr,
                "%s: can't open file %s\n",
                progname, *argv);
        exit(2);
    }
        
    char line1[MAXLEN];
    char line2[MAXLEN];
    
    int numline;
    for(numline = 0;
        fgets_(line1, MAXLEN, fp1) != NULL &&
        fgets_(line2, MAXLEN, fp2) != NULL;
        numline++)
        if(strcmp(line1, line2) != 0){
            printf("at line %d, file %s: %s\n", numline, fn1, line1);
            printf("at line %d, file %s: %s\n", numline, fn2, line2);
            exit(0);    /* calls 'fclose()' for each open file */
        }
    
    if(ferror(fp1)){
        printf("%s: output error occurred in file %s\n", progname, fn1);
        exit(3);
    }else if(ferror(fp2)){
        printf("%s: output error occurred in file %s\n", progname, fn2);
        exit(4);
    }
        
    exit(0);
}

char *fgets_(char *s, int n, FILE *fp){
    
    register int c;
    register char *cs;
    
    cs = s;
    while(--n > 0 && (c = getc(fp)) != EOF)
        if((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

