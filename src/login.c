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
        puts("=================================");
        puts("   欢迎使用实验室预约管理系统！");
        puts("=================================");
        printf("请输入用户名：");
        scanf(" %s", username);
        if (strcmp(username, USERNAME) == 0)
        {
            printf("请输入密码：");
            scanf(" %s", password);
            if (strcmp(password, PASSWORD) == 0)
            {
                puts("登录成功！");
                Beep(1150, 350);
                Sleep(350);
                break;
            }
            puts("密码错误！请重试");
        }
        else
            puts("不存在该用户！请重试");
        Beep(500, 200);
    }
}
