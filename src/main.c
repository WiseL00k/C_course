#include <stdio.h>
#include "simpleCMenu.h"
#include "menu.h"

#include "lab.h"

int main(void)
{
    initMenuDisplayFunctions(displayMenuItem, displaySelectedMenuItem, goToxy);

    const char *topMenuInfo = "实验室预约信息管理系统";
    const char *bottomMenuInfo = "";

    MenuHandle mainMenu = initMenu(mainMenuLoop, topMenuInfo, bottomMenuInfo);

    initAllMenus(mainMenu);

    loadLabInfo();
    runMainMenu(mainMenu);

    return 0;
}
