#include <windows.h>
#include <stdio.h>
#include "login.h"

#define USERNAME "admin"
#define PASSWORD "gdut"

void login(void)
{
    char password[20], username[20];
    while (1)
    {
        printf("\033[H\033[J"); // ����
        puts("=================================");
        puts("   ��ӭʹ��ʵ����ԤԼ����ϵͳ��");
        puts("=================================");
        printf("�������û�����");
        scanf(" %s", username);
        if (strcmp(username, USERNAME) == 0)
        {
            printf("���������룺");
            scanf(" %s", password);
            if (strcmp(password, PASSWORD) == 0)
            {
                puts("��¼�ɹ���");
                Beep(1150, 350);
                Sleep(350);
                break;
            }
            puts("�������������");
        }
        else
            puts("�����ڸ��û���������");
        Beep(500, 200);
    }
}
