#include <windows.h>
#include <stdio.h>
#include "login.h"

#define PASSWORD "gdut"

void login(void)
{
    char password[20];
    while (1)
    {
        printf("\033[H\033[J"); // ����
        printf("���������룺\n");
        scanf(" %s", password);
        if (strcmp(password, PASSWORD) == 0)
        {
            printf("��¼�ɹ���\n");
            Beep(1150, 350);
            Sleep(350);
            break;
        }
        printf("�������������\n");
        Beep(500, 200);
    }
}
