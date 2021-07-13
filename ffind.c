//
//  ffind.c
//  
//
//  Created by Davide Colombo on 13/07/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 150

char *fgets_(char *, int, FILE *);
int getline_(char *, int);
char *sfind(char *, char *);

int main(int argc, char *argv[]){
    
    char line[MAXLEN];
    char *pattern, *prog, *match, *fn;
    int found = 0;
    FILE *fp;
    
    prog = argv[0];
    if(argc == 1){
        fprintf(stderr, "%s: wrong number of args. Usage: name pattern (files)", prog);
        exit(1);
    }else if(argc == 2){
        pattern = *++argv;                  /* save the pattern */
        while(getline_(line, MAXLEN) > 0){
            if((match = sfind(line, pattern)) != NULL){
                printf("match at:\n %s - %s\n", match, pattern);
                found++;
            }
        }
    }else{
        pattern = *++argv;
        argc--;
        while(--argc > 0 && (fp = fopen((fn = *++argv), "r")) != NULL){
            while(fgets_(line, MAXLEN, fp) != NULL)
                if((match = sfind(line, pattern)) != NULL){
                    printf("match in file %s:\n %s - %s\n", fn, match, pattern);
                    found++;
                }
            fclose(fp);
        }
    }
    
    if(ferror(fp)){
        fprintf(stderr, "%s: output error occurred on file %s\n", prog, fn);
        exit(2);
    }else{
        fclose(fp);
    }
    
    exit(0);
}

/* =================================================================================================== */

char *sfind(char *line, char *p){
    
    int i, j;
    for(i = 0; *(line+i); i++){
        if(*(line+i) == *p){
            for(j = 0; *(p+j); i++, j++)
                if(*(line+i) != *(p+j))
                    break;
            if(*(p+j) == '\0')
                return (line+i-j);
        }
    }
    return NULL;
}

/* =================================================================================================== */

int getline_(char *s, int lim){
    
    if(fgets_(s, lim, stdin) == NULL)
        return 0;
    else
        return strlen(s);
}

/* =================================================================================================== */

char *fgets_(char *s, int lim, FILE *fp){
    register int c;
    register char *cs;
    
    cs = s;
    while(--lim > 0 && (c = getc(fp)) != EOF)
        if((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

