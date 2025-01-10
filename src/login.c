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
        printf("\033[H\033[J"); // 清屏
        printf("请输入用户名：\n");
        scanf(" %s", username);
        if (strcmp(username, USERNAME) == 0)
        {
            printf("请输入密码：\n");
            scanf(" %s", password);
            if (strcmp(password, PASSWORD) == 0)
            {
                printf("登录成功！\n");
                Beep(1150, 350);
                Sleep(350);
                break;
            }
            printf("密码错误！请重试\n");
        }
        else
            printf("不存在该用户！请重试\n");
        Beep(500, 200);
    }
}
