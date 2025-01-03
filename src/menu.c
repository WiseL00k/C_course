#include "menu.h"

void quit()
{
    puts("are you sure to exit? y/n");
    char c = getch();
    if (c == 'y' || c == 'Y')
        exit(0);
}

void goToxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);           // 两个参数分别是指定哪个窗体，具体位置
}

void displayMenuItem(MenuItemHandle menuItemHandle)
{
    printf("%s  \n", menuItemHandle->name);
}

void displaySelectedMenuItem(MenuItemHandle menuItemHandle)
{
    printf("  \033[7m%s\033[0m\n", menuItemHandle->name);
}

void hideCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // 设置光标不可见
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void showCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE; // 设置光标可见
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void mainMenuLoop(MenuHandle menuHandle)
{
    struct node *head = NULL;
    char c;

    while (isCurrentMenu(menuHandle))
    {
        if (kbhit())
        {
            if (GetAsyncKeyState(VK_UP))
            {
                updateSelectedMenuItem(UP);
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                updateSelectedMenuItem(DOWN);
            }
            c = getch();
            if (c <= 'z' && c >= 'a')
                c -= ('a' - 'A');
            if (c <= 'D' && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                switch (getSelectedMenuItemTag())
                {
                case 'A':
                    changeCurrentMenu();
                    break;
                case 'B':
                {

                    system("pause");
                    break;
                }
                case 'C':

                    system("pause");
                    break;
                case 'D':
                    quit();
                default:
                    break;
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            else if (c == 'C')
                exit(0);
            Sleep(100); // 软件延时消抖
        }
    }
}

void subMenu1Loop(MenuHandle menuHandle)
{
    char c;
    while (isCurrentMenu(menuHandle))
    {
        if (kbhit())
        {
            if (GetAsyncKeyState(VK_UP))
            {
                updateSelectedMenuItem(UP);
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                updateSelectedMenuItem(DOWN);
            }
            c = getch();
            if (c <= 'z' && c >= 'a')
                c -= ('a' - 'A');
            if (c <= 'B' && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                switch (getSelectedMenuItemTag())
                {
                case 'A':
                    changeCurrentMenu();
                    break;
                case 'B':
                    changeCurrentMenu();
                default:
                    break;
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100); // 软件延时消抖
        }
    }
}

void subMenu2Loop(MenuHandle menuHandle)
{
    char c;
    while (isCurrentMenu(menuHandle))
    {
        if (kbhit())
        {
            if (GetAsyncKeyState(VK_UP))
            {
                updateSelectedMenuItem(UP);
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                updateSelectedMenuItem(DOWN);
            }
            c = getch();
            if (c <= 'z' && c >= 'a')
                c -= ('a' - 'A');
            if (c <= 'A' && c >= 'A')
            {
                updateSelectedMenuItem(c);
                printf("command is [%c]\n", c);
            }
            else if (c == '\r')
            {
                switch (getSelectedMenuItemTag())
                {
                case 'A':
                    changeCurrentMenu();
                    break;
                default:
                    break;
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100); // 软件延时消抖
        }
    }
}

void initAllMenus(MenuHandle mainMenu)
{
    hideCursor();
    MenuHandle subMenu1 = initMenu(subMenu1Loop);
    MenuHandle subMenu2 = initMenu(subMenu2Loop);

    MenuItemHandle mainMenuItem1 = initChangeMenuItem("enter subMenu1", ENTER_MENU_TYPE, subMenu1);
    MenuItemHandle mainMenuItem2 = initExecFuncMenuItem("MenuItem2");
    MenuItemHandle mainMenuItem3 = initExecFuncMenuItem("MenuItem3");
    MenuItemHandle mainMenuItem4 = initExecFuncMenuItem("exit");
    registerMenuItem(mainMenu, mainMenuItem1);
    registerMenuItem(mainMenu, mainMenuItem2);
    registerMenuItem(mainMenu, mainMenuItem3);
    registerMenuItem(mainMenu, mainMenuItem4);

    MenuItemHandle subMenu1Item1 = initChangeMenuItem("return mainMenu", EXIT_MENU_TYPE, mainMenu);
    registerMenuItem(subMenu1, subMenu1Item1);
    MenuItemHandle subMenu1Item2 = initChangeMenuItem("enter subMenu2", ENTER_MENU_TYPE, subMenu2);
    registerMenuItem(subMenu1, subMenu1Item2);

    MenuItemHandle subMenu2Item1 = initChangeMenuItem("return subMenu1", EXIT_MENU_TYPE, subMenu1);
    registerMenuItem(subMenu2, subMenu2Item1);
}
