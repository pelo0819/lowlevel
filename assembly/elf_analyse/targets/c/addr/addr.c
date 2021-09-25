#include <stdio.h>
#include <stdlib.h>

extern int value;
extern int8_t cvalue;
extern int16_t svalue;
extern int32_t lvalue;
extern int stext, etext;
extern int srdata, erdata;
extern int sdata, edata;

int main(int argc, char *argv[])
{
    // printf("&value  = 0x%08x\n", (int)&value);
    // printf("stext   = 0x%08x, etext   = 0x%08x\n", stext, etext);
    // printf("sdata   = 0x%08x, edata   = 0x%08x\n", sdata, edata);
    // printf("&stext  = 0x%08x, &etext  = 0x%08x\n", (int)&stext, (int)&etext);
    // printf("&srdata = 0x%08x, &erdata = 0x%08x\n", (int)&srdata, (int)&erdata);
    // printf("&sdata  = 0x%08x, &edata  = 0x%08x\n", (int)&sdata, (int)&edata);
    
    printf("&value  = 0x%08lx\n", (u_int64_t)&value);
    printf("etext   = 0x%08x\n", etext);
    printf("edata   = 0x%08x\n", edata);
    printf("&etext  = 0x%08lx\n", (u_int64_t)&etext);
    printf("&edata  = 0x%08lx\n", (u_int64_t)&edata);

    printf("\n");

    printf("&cvalue = 0x%08lx, cvalue = %d\n", (u_int64_t)&cvalue, cvalue);
    printf("&svalue = 0x%08lx, svalue = %d\n", (u_int64_t)&svalue, svalue);
    printf("&lvalue = 0x%08lx, lvalue = %d\n", (u_int64_t)&lvalue, lvalue);
    return 0;
}


