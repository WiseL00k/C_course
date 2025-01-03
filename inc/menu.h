#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "simpleCMenu.h"

// Init menus
void initAllMenus(MenuHandle mainMenu);

// Menu loops
void mainMenuLoop(MenuHandle menuHandle);
void subMenu1Loop(MenuHandle menuHandle);
void subMenu2Loop(MenuHandle menuHandle);
void subMenu3Loop(MenuHandle menuHandle);

// Display functions
void displayMenuItem(MenuItemHandle menuItemHandle);
void displaySelectedMenuItem(MenuItemHandle menuItemHandle);
void hideCursor();
void showCursor();
void goToxy(int x, int y);

// Other functions
void quit();

#endif // __MENU_H__
