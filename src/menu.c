#include "menu.h"

void quit()
{
    puts("你确定要退出吗? (Y/N)");
    char c = getch();
    if (c == 'y' || c == 'Y')
        exit(0);
}

void goToxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
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
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void showCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
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
            if (c <= 'A' + menuHandle->menuItemListHandle->count - 1 && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                switch (getSelectedMenuItemTag())
                {
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                    changeCurrentMenu();
                    break;
                case 'E':
                    quit();
                    break;
                default:
                    break;
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100);
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
            if (c <= 'A' + menuHandle->menuItemListHandle->count - 1 && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                char tag = getSelectedMenuItemTag();
                switch (tag)
                {
                case 'A':
                    if (addLab())
                        puts("添加成功!");
                    else
                        puts("添加失败");
                    break;
                case 'B':
                    if (deleteLab())
                        puts("删除成功!");
                    else
                        puts("删除失败,请不要删除不存在的实验室");
                    break;
                case 'C':
                    if (searchLabInfo())
                        puts("查找成功!");
                    else
                        puts("查找失败");
                    break;
                case 'D':
                    changeCurrentMenu();
                    break;
                case 'E':
                    displayAllLabInfo();
                    break;
                case 'F':
                    changeCurrentMenu();
                    break;
                default:
                    break;
                }
                if (tag != 'F' && tag != 'D')
                {
                    puts("按任意键返回...");
                    getch();
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100);
        }
    }
}

void subMenu1_4Loop(MenuHandle menuHandle)
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
            if (c <= 'A' + menuHandle->menuItemListHandle->count - 1 && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                LabInfoType infoType;
                char tag = getSelectedMenuItemTag();
                switch (tag)
                {
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                    infoType = tag - 'A';
                    if (modifyLabInfo(infoType))
                        puts("修改成功!");
                    else
                        puts("修改失败");
                    break;
                case 'F':
                    changeCurrentMenu();
                    break;
                default:
                    break;
                }
                if (tag != 'F')
                {
                    puts("按任意键返回...");
                    getch();
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100);
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
            if (c <= 'A' + menuHandle->menuItemListHandle->count - 1 && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                char tag = getSelectedMenuItemTag();
                switch (tag)
                {
                case 'A':
                    break;
                case 'B':
                    break;
                case 'C':
                    break;
                case 'D':
                    break;
                case 'E':
                    break;
                case 'F':
                    changeCurrentMenu();
                    break;
                default:
                    break;
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100);
        }
    }
}

void subMenu3Loop(MenuHandle menuHandle)
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
            if (c <= 'A' + menuHandle->menuItemListHandle->count - 1 && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                char tag = getSelectedMenuItemTag();
                switch (tag)
                {
                case 'A':
                    break;
                case 'B':
                    break;
                case 'C':

                    break;
                case 'D':
                    changeCurrentMenu();
                    break;

                default:
                    break;
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100);
        }
    }
}

void subMenu4Loop(MenuHandle menuHandle)
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
            if (c <= 'A' + menuHandle->menuItemListHandle->count - 1 && c >= 'A')
            {
                updateSelectedMenuItem(c);
            }
            else if (c == '\r')
            {
                char tag = getSelectedMenuItemTag();
                switch (tag)
                {
                case 'A':
                    if (loadLabInfo())
                        puts("实验室信息加载成功");
                    else
                        puts("加载失败");
                    break;
                case 'B':
                    if (saveLabInfo() == OK)
                        puts("实验室信息保存成功");
                    else
                        puts("保存失败");

                    break;
                case 'C':

                    break;
                case 'D':

                    break;
                case 'E':
                    changeCurrentMenu();
                    break;

                default:
                    break;
                }
                if (tag != 'E')
                {
                    puts("按任意键返回...");
                    getch();
                }
                if (isCurrentMenu(menuHandle))
                    updateCurrentMenu(menuHandle);
            }
            Sleep(100);
        }
    }
}

void initAllMenus(MenuHandle mainMenu)
{
    hideCursor();
    MenuHandle subMenu1 = initMenu(subMenu1Loop, mainMenu->topMenuInfo, mainMenu->bottomMenuInfo);
    MenuHandle subMenu2 = initMenu(subMenu2Loop, mainMenu->topMenuInfo, mainMenu->bottomMenuInfo);
    MenuHandle subMenu3 = initMenu(subMenu3Loop, mainMenu->topMenuInfo, mainMenu->bottomMenuInfo);
    MenuHandle subMenu4 = initMenu(subMenu4Loop, mainMenu->topMenuInfo, mainMenu->bottomMenuInfo);
    MenuHandle subMenu1_4 = initMenu(subMenu1_4Loop, mainMenu->topMenuInfo, mainMenu->bottomMenuInfo);

    MenuItemHandle mainMenuItem1 = initChangeMenuItem("实验室管理", ENTER_MENU_TYPE, subMenu1);
    MenuItemHandle mainMenuItem2 = initChangeMenuItem("实验室预约", ENTER_MENU_TYPE, subMenu2);
    MenuItemHandle mainMenuItem3 = initChangeMenuItem("统计数据", ENTER_MENU_TYPE, subMenu3);
    MenuItemHandle mainMenuItem4 = initChangeMenuItem("数据管理", ENTER_MENU_TYPE, subMenu4);
    MenuItemHandle mainMenuItem5 = initExecFuncMenuItem("退出");
    registerMenuItem(mainMenu, mainMenuItem1);
    registerMenuItem(mainMenu, mainMenuItem2);
    registerMenuItem(mainMenu, mainMenuItem3);
    registerMenuItem(mainMenu, mainMenuItem4);
    registerMenuItem(mainMenu, mainMenuItem5);

    MenuItemHandle subMenu1Item1 = initExecFuncMenuItem("添加实验室信息");
    MenuItemHandle subMenu1Item2 = initExecFuncMenuItem("删除实验室信息");
    MenuItemHandle subMenu1Item3 = initExecFuncMenuItem("查找实验室信息");
    MenuItemHandle subMenu1Item4 = initChangeMenuItem("修改实验室信息", ENTER_MENU_TYPE, subMenu1_4);
    MenuItemHandle subMenu1Item5 = initExecFuncMenuItem("显示所有实验室信息");
    MenuItemHandle subMenu1Item6 = initChangeMenuItem("返回", EXIT_MENU_TYPE, mainMenu);
    registerMenuItem(subMenu1, subMenu1Item1);
    registerMenuItem(subMenu1, subMenu1Item2);
    registerMenuItem(subMenu1, subMenu1Item3);
    registerMenuItem(subMenu1, subMenu1Item4);
    registerMenuItem(subMenu1, subMenu1Item5);
    registerMenuItem(subMenu1, subMenu1Item6);

    MenuItemHandle subMenu1_4Item1 = initExecFuncMenuItem("修改实验室地点");
    MenuItemHandle subMenu1_4Item2 = initExecFuncMenuItem("修改实验室编号");
    MenuItemHandle subMenu1_4Item3 = initExecFuncMenuItem("修改实验室最大人数");
    MenuItemHandle subMenu1_4Item4 = initExecFuncMenuItem("修改实验室类型");
    MenuItemHandle subMenu1_4Item5 = initExecFuncMenuItem("修改实验室管理员");
    MenuItemHandle subMenu1_4Item6 = initChangeMenuItem("返回", EXIT_MENU_TYPE, subMenu1);
    registerMenuItem(subMenu1_4, subMenu1_4Item1);
    registerMenuItem(subMenu1_4, subMenu1_4Item2);
    registerMenuItem(subMenu1_4, subMenu1_4Item3);
    registerMenuItem(subMenu1_4, subMenu1_4Item4);
    registerMenuItem(subMenu1_4, subMenu1_4Item5);
    registerMenuItem(subMenu1_4, subMenu1_4Item6);

    MenuItemHandle subMenu2Item1 = initExecFuncMenuItem("添加预约信息");
    MenuItemHandle subMenu2Item2 = initExecFuncMenuItem("删除预约信息");
    MenuItemHandle subMenu2Item3 = initExecFuncMenuItem("查找预约信息");
    MenuItemHandle subMenu2Item4 = initExecFuncMenuItem("修改预约信息");
    MenuItemHandle subMenu2Item5 = initExecFuncMenuItem("显示所有预约信息");
    MenuItemHandle subMenu2Item6 = initChangeMenuItem("返回", EXIT_MENU_TYPE, mainMenu);
    registerMenuItem(subMenu2, subMenu2Item1);
    registerMenuItem(subMenu2, subMenu2Item2);
    registerMenuItem(subMenu2, subMenu2Item3);
    registerMenuItem(subMenu2, subMenu2Item4);
    registerMenuItem(subMenu2, subMenu2Item5);
    registerMenuItem(subMenu2, subMenu2Item6);

    MenuItemHandle subMenu3Item1 = initExecFuncMenuItem("统计实验室月/年使用时间");
    MenuItemHandle subMenu3Item2 = initExecFuncMenuItem("统计某人月/年使用时间");
    MenuItemHandle subMenu3Item3 = initExecFuncMenuItem("统计某实验室月/年使用情况");
    MenuItemHandle subMenu3Item4 = initChangeMenuItem("返回", EXIT_MENU_TYPE, mainMenu);
    registerMenuItem(subMenu3, subMenu3Item1);
    registerMenuItem(subMenu3, subMenu3Item2);
    registerMenuItem(subMenu3, subMenu3Item3);
    registerMenuItem(subMenu3, subMenu3Item4);

    MenuItemHandle subMenu4Item1 = initExecFuncMenuItem("加载实验室信息");
    MenuItemHandle subMenu4Item2 = initExecFuncMenuItem("保存实验室信息");
    MenuItemHandle subMenu4Item3 = initExecFuncMenuItem("加载预约信息");
    MenuItemHandle subMenu4Item4 = initExecFuncMenuItem("保存预约信息");
    MenuItemHandle subMenu4Item5 = initChangeMenuItem("返回", EXIT_MENU_TYPE, mainMenu);
    registerMenuItem(subMenu4, subMenu4Item1);
    registerMenuItem(subMenu4, subMenu4Item2);
    registerMenuItem(subMenu4, subMenu4Item3);
    registerMenuItem(subMenu4, subMenu4Item4);
    registerMenuItem(subMenu4, subMenu4Item5);
}
