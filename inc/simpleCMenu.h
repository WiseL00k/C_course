#ifndef SIMPLE_CMENU_H
#define SIMPLE_CMENU_H

#define UP -1
#define DOWN 1

#define MAXSIZE 25

typedef char ChangeMenuItemAction;

typedef enum
{
    EXECUTIVE_FUNCTION_TYPE,
    ENTER_MENU_TYPE,
    EXIT_MENU_TYPE,
} MenuItemType;

typedef struct Menu *MenuHandle;

// �˵�������� �û���������Ӹ��Ĳ�ͬ�Ĳ�������
typedef struct ActionArgs
{
    int num;         // ��һ������������
    const char *str; // �ڶ����������ַ���
} ActionArgs;

// �˵���
typedef struct MenuItem
{
    MenuItemType type; // �˵�������
    char *name;        // �˵�������
    char tag;          // �˵����ǩ
    struct
    {
        int x; // ��
        int y; // ��
    } pos;     // �˵�������
    union
    {
        // ����ΪCHANGE_MENU_TYPE�ű���������
        struct
        {
            void (*enterMenuAction)(struct MenuItem *);

            MenuHandle nextMenu; // ��һ���˵�
        } enter;

        struct
        {
            void (*exitMenuAction)(struct MenuItem *);
            MenuHandle prevMenu; // ��һ���˵�
        } exit;

    } un;

    struct MenuItem *prevItem; // ��һ���˵���
    struct MenuItem *nextItem; // ��һ���˵���
} MenuItem, *MenuItemHandle;

typedef struct MenuItemList
{
    MenuItem *head; // �˵���ͷ
    MenuItem *tail; // �˵���β
    int count;      // �˵�������
} MenuItemList, *MenuItemListHandle;

// �˵�
typedef struct Menu
{
    char **topMenuInfo; // �����˵���Ϣ
    struct
    {
        int x;           // ��
        int y;           // ��
    } topMenuInfoPos;    // �����˵���Ϣ������
    int topMenuInfoRows; // �����˵���Ϣ����

    char *bottomMenuInfo; // �ײ��˵���Ϣ
    struct
    {
        int x;              // ��
        int y;              // ��
    } bottomMenuInfoPos;    // �ײ��˵���Ϣ��
    int bottomMenuInfoRows; // �ײ��˵���Ϣ����

    MenuItemList *menuItemListHandle;      // �˵����б�
    MenuItemHandle selectedMenuItemHandle; // ��ǰѡ�еĲ˵���
    char selectedMenuItemTag;              // ��ǰѡ�еĲ˵����ǩ
    void (*loop)(MenuHandle);              // �˵�ѭ������
} Menu, *MenuHandle;

typedef struct
{
    void (*displayMenuItem)(MenuItemHandle);         // ��ʾ�˵���
    void (*displaySelectedMenuItem)(MenuItemHandle); // ��ʾ��ǰѡ�еĲ˵���
    void (*moveCursor)(int x, int y);                // �ƶ����
} MenuDisplayFunctions;

/* ��ʼ���˵���
 * @param name �˵�������
 * @param type �˵�������
 * @param action �˵����, ���˵�������ΪEXECUTIVE_FUNCTION_TYPEʱ��Ч, ����ΪNULL
 */
MenuItemHandle initExecFuncMenuItem(const char *name);
MenuItemHandle initChangeMenuItem(const char *name, MenuItemType type, MenuHandle menuHandle);
MenuHandle initMenu(void (*loop)(MenuHandle), char *topMenuInfo, char *bottomMenuInfo);
void initMenuDisplayFunctions(void (*displayMenuItem)(MenuItemHandle), void (*displaySelectedMenuItem)(MenuItemHandle), void (*moveCursor)(int, int));
void registerMenu(MenuHandle menuHandle);
void registerMenuItem(MenuHandle menuHandle, MenuItemHandle menuItemHandle);
void updateCurrentMenu(MenuHandle menuHandle);
void updateSelectedMenuItem(ChangeMenuItemAction itemAction);
char getSelectedMenuItemTag();
void changeCurrentMenu();
int isCurrentMenu(MenuHandle menuHandle);
void runMainMenu(MenuHandle menuHandle);

#endif // SIMPLE_CMENU_H
