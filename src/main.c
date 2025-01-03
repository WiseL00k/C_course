#include <stdio.h>
#include "simpleCMenu.h"
#include "menu.h"

int main(void)
{
    initMenuDisplayFunctions(displayMenuItem, displaySelectedMenuItem, goToxy);

    const char *topMenuInfo = "ʵ����ԤԼ��Ϣ����ϵͳ";
    const char *bottomMenuInfo = "";

    MenuHandle mainMenu = initMenu(mainMenuLoop, topMenuInfo, bottomMenuInfo);

    initAllMenus(mainMenu);

    runMainMenu(mainMenu);

    return 0;
}
