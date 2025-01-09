#include <windows.h>
#include <stdio.h>
#include "login.h"

#define PASSWORD "gdut"

void login(void)
{
    char password[20];
    while (1)
    {
        printf("\033[H\033[J"); // «Â∆¡
        printf("«Î ‰»Î√‹¬Î£∫\n");
        scanf(" %s", password);
        if (strcmp(password, PASSWORD) == 0)
        {
            printf("µ«¬º≥…π¶£°\n");
            Beep(1150, 350);
            Sleep(350);
            break;
        }
        printf("√‹¬Î¥ÌŒÛ£°«Î÷ÿ ‘\n");
        Beep(500, 200);
    }
}
