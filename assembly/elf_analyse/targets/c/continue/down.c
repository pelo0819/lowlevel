#include <stdio.h>

static int cnt;
extern int set_reg_dummy(int v);

int main()
{
    for(cnt = 0;;cnt++)
    {
        if(cnt == 0x123)
        {
            set_reg_dummy(0x57);
            *(int *)0 = 1;
        }
    }
    return 0;
}