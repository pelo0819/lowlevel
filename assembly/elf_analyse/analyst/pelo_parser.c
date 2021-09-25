#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char arr[253][128] = {""};

void parse()
{
    FILE *fp;
    fp = fopen("resources/e_machine_list.pelo", "r");
    if(fp == NULL)
    {
        printf("err open file\n");
    }

    char str[128];
    while (fgets(str, 128, fp) != NULL)
    {
        char *ptr = strtok(str, "\t");
        int idx = atoi(ptr);
        ptr = strtok(NULL, "\t");
        char *p = strchr(ptr, '\n');
        if(p != NULL){*p = '\0';}
        strcpy(arr[idx], ptr);
    }
    fclose(fp);
}

char *get_value(int id)
{
    return arr[id];
}