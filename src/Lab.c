#include "Lab.h"

LabList labList = NULL; // 全局变量，指向实验室链表的头节点

Status addLab()
{
    system("cls");
    fflush(stdin);
    Lab newLab;
    newLab.labReservation = NULL; // 初始化预约链表为空
    puts("请输入实验室地点: ");
    scanf(" %s", newLab.labInfo.location);
    puts("请输入实验室编号: ");
    scanf(" %s", newLab.labInfo.number);
    if (isLabExist(newLab))
    {
        puts("实验室已存在，请重新输入");
        return ERROR;
    }
    puts("请输入实验室最多人数: ");
    scanf(" %d", &newLab.labInfo.maxCapacity);
    puts("请输入实验室类型: ");
    scanf(" %s", newLab.labInfo.type);
    puts("请输入实验室管理员: ");
    scanf(" %s", newLab.labInfo.admin);

    if (labList == NULL)
    {
        labList = (LabList)malloc(sizeof(LabNode));
        if (labList == NULL)
            return OVERFLOW;
        labList->lab = newLab;
        labList->next = NULL;
    }
    else
    {
        LabList p = labList;
        while (p->next != NULL)
            p = p->next;
        LabList q = (LabList)malloc(sizeof(LabNode));
        q->lab = newLab;
        q->next = NULL;
        p->next = q;
    }
    return OK;
}

Status deleteLab()
{
    system("cls");
    fflush(stdin);
    char labNumber[MAX_SIZE], location[MAX_SIZE];
    puts("请输入要删除的实验室地点: ");
    scanf(" %s", location);
    puts("请输入要删除的实验室编号: ");
    scanf(" %s", labNumber);
    LabList p = labList;
    LabList q = NULL;
    while (p)
    {
        if (strcmp(p->lab.labInfo.location, location) == 0 && strcmp(p->lab.labInfo.number, labNumber) == 0)
        {
            if (q == NULL)
                labList = p->next;
            else
                q->next = p->next;
            free(p);
            return OK;
        }
        q = p;
        p = p->next;
    }
    return ERROR;
}

Status searchLabInfo()
{
    system("cls");
    fflush(stdin);
    char number[MAX_SIZE], location[MAX_SIZE];
    puts("请输入要查询的实验室地点: ");
    scanf(" %s", location);
    puts("请输入要查询的实验室编号: ");
    scanf(" %s", number);
    LabList p = labList;
    while (p)
    {
        if (strcmp(p->lab.labInfo.location, location) == 0 && strcmp(p->lab.labInfo.number, number) == 0)
        {
            printf("\n实验室地点: %s\n", p->lab.labInfo.location);
            printf("实验室编号: %s\n", p->lab.labInfo.number);
            printf("实验室最多人数: %d\n", p->lab.labInfo.maxCapacity);
            printf("实验室类型: %s\n", p->lab.labInfo.type);
            printf("实验室管理员: %s\n\n", p->lab.labInfo.admin);
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

Status modifyLabInfo(LabInfoType infoType)
{
    system("cls");
    fflush(stdin);
    char number[MAX_SIZE], location[MAX_SIZE];
    puts("请输入要修改的实验室地点: ");
    scanf(" %s", location);
    puts("请输入要修改的实验室编号: ");
    scanf(" %s", number);
    LabList p = labList;
    while (p)
    {
        if (strcmp(p->lab.labInfo.location, location) == 0 && strcmp(p->lab.labInfo.number, number) == 0)
        {
            switch (infoType)
            {
            case LOCATION:
                puts("请输入新的实验室地点: ");
                scanf(" %s", p->lab.labInfo.location);
                break;
            case NUMBER:
                puts("请输入新的实验室编号: ");
                scanf(" %s", p->lab.labInfo.number);
                break;
            case MAXCAPACITY:
                puts("请输入新的实验室最多人数: ");
                scanf(" %d", &p->lab.labInfo.maxCapacity);
                break;
            case TYPE:
                puts("请输入新的实验室类型: ");
                scanf(" %s", p->lab.labInfo.type);
                break;
            case ADMIN:
                puts("请输入新的实验室管理员: ");
                scanf(" %s", p->lab.labInfo.admin);
                break;
            }
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}
Status displayAllLabInfo()
{
    LabList p = labList;
    system("cls");
    puts("实验室地点\t实验室编号\t实验室最多人数\t实验室类型\t实验室管理员");
    while (p)
    {
        printf("%s%16s%20d%12s%18s\n", p->lab.labInfo.location, p->lab.labInfo.number, p->lab.labInfo.maxCapacity, p->lab.labInfo.type, p->lab.labInfo.admin);
        p = p->next;
    }
    return OK;
}

Status addReservation()
{
    
}

Status saveLabInfo()
{
    FILE *fp = fopen("lab.txt", "w");
    if (fp == NULL)
    {
        puts("文件打开失败");
        return ERROR;
    }
    LabList p = labList;
    while (p)
    {
        fprintf(fp, "%s %s %d %s %s\n", p->lab.labInfo.location, p->lab.labInfo.number, p->lab.labInfo.maxCapacity, p->lab.labInfo.type, p->lab.labInfo.admin);
        p = p->next;
    }
    fclose(fp);
    return OK;
}

Status loadLabInfo()
{
    FILE *fp = fopen("lab.txt", "r");
    if (fp == NULL)
    {
        puts("文件打开失败");
        return ERROR;
    }
    Lab newLab;
    while (fscanf(fp, "%s %s %d %s %s", newLab.labInfo.location, newLab.labInfo.number, &newLab.labInfo.maxCapacity, newLab.labInfo.type, newLab.labInfo.admin) != EOF)
    {
        newLab.labReservation = NULL;
        if (labList == NULL)
        {
            labList = (LabList)malloc(sizeof(LabNode));
            if (labList == NULL)
                return OVERFLOW;
            labList->lab = newLab;
            labList->next = NULL;
        }
        else
        {
            LabList p = labList;
            while (p->next != NULL)
                p = p->next;
            LabList q = (LabList)malloc(sizeof(LabNode));
            q->lab = newLab;
            q->next = NULL;
            p->next = q;
        }
    }
    return OK;
}

Status isLabExist(Lab newLab)
{
    LabList p = labList;
    while (p != NULL)
    {
        if (strcmp(newLab.labInfo.location, p->lab.labInfo.location) == 0 &&
            strcmp(newLab.labInfo.number, p->lab.labInfo.number) == 0)
            return TRUE;
        p = p->next;
    }
    return FALSE;
}

LabPtr findLab(char *location, char *number)
{
}