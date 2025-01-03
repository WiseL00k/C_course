#include <stdio.h>
#include "simpleCMenu.h"
#include "menu.h"


int main(void)
{
    initMenuDisplayFunctions(displayMenuItem, displaySelectedMenuItem, goToxy);

    MenuHandle mainMenu = initMenu(mainMenuLoop);

    initAllMenus(mainMenu);

    runMainMenu(mainMenu);

    return 0;
}



