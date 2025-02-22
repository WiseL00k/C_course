#include <stdio.h>
#include "simpleCMenu.h"
#include "menu.h"
#include "login.h"
#include "lab.h"

int main(void)
{
    initMenuDisplayFunctions(displayMenuItem, displaySelectedMenuItem, goToxy);

    const char *bottomMenuInfo = "";
    MenuHandle mainMenu = initMenu(mainMenuLoop, topMenuInfo, bottomMenuInfo);
    initAllMenus(mainMenu);

    login();

    loadLabInfo();
    loadLabReservations();

    // printf("\033[30;42m");   // ��ɫ����
    runMainMenu(mainMenu);

    return 0;
}
