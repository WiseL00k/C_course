#include "Lab.h"

LabList labList = NULL; // ȫ�ֱ�����ָ��ʵ���������ͷ�ڵ�

Status addLab()
{
    system("cls");
    fflush(stdin);
    Lab newLab;
    newLab.labReservation = NULL; // ��ʼ��ԤԼ����Ϊ��
    puts("������ʵ���ҵص�: ");
    scanf(" %s", newLab.labInfo.location);
    puts("������ʵ���ұ��: ");
    scanf(" %s", newLab.labInfo.number);
    if (isLabExist(newLab))
    {
        puts("ʵ�����Ѵ��ڣ�����������");
        return ERROR;
    }
    puts("������ʵ�����������: ");
    scanf(" %d", &newLab.labInfo.maxCapacity);
    puts("������ʵ��������: ");
    scanf(" %s", newLab.labInfo.type);
    puts("������ʵ���ҹ���Ա: ");
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
    puts("������Ҫɾ����ʵ���ҵص�: ");
    scanf(" %s", location);
    puts("������Ҫɾ����ʵ���ұ��: ");
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
    puts("������Ҫ��ѯ��ʵ���ҵص�: ");
    scanf(" %s", location);
    puts("������Ҫ��ѯ��ʵ���ұ��: ");
    scanf(" %s", number);
    LabList p = labList;
    while (p)
    {
        if (strcmp(p->lab.labInfo.location, location) == 0 && strcmp(p->lab.labInfo.number, number) == 0)
        {
            printf("\nʵ���ҵص�: %s\n", p->lab.labInfo.location);
            printf("ʵ���ұ��: %s\n", p->lab.labInfo.number);
            printf("ʵ�����������: %d\n", p->lab.labInfo.maxCapacity);
            printf("ʵ��������: %s\n", p->lab.labInfo.type);
            printf("ʵ���ҹ���Ա: %s\n\n", p->lab.labInfo.admin);
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
    puts("������Ҫ�޸ĵ�ʵ���ҵص�: ");
    scanf(" %s", location);
    puts("������Ҫ�޸ĵ�ʵ���ұ��: ");
    scanf(" %s", number);
    LabList p = labList;
    while (p)
    {
        if (strcmp(p->lab.labInfo.location, location) == 0 && strcmp(p->lab.labInfo.number, number) == 0)
        {
            switch (infoType)
            {
            case LOCATION:
                puts("�������µ�ʵ���ҵص�: ");
                scanf(" %s", p->lab.labInfo.location);
                break;
            case NUMBER:
                puts("�������µ�ʵ���ұ��: ");
                scanf(" %s", p->lab.labInfo.number);
                break;
            case MAXCAPACITY:
                puts("�������µ�ʵ�����������: ");
                scanf(" %d", &p->lab.labInfo.maxCapacity);
                break;
            case TYPE:
                puts("�������µ�ʵ��������: ");
                scanf(" %s", p->lab.labInfo.type);
                break;
            case ADMIN:
                puts("�������µ�ʵ���ҹ���Ա: ");
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
    puts("ʵ���ҵص�\tʵ���ұ��\tʵ�����������\tʵ��������\tʵ���ҹ���Ա");
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
        puts("�ļ���ʧ��");
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
        puts("�ļ���ʧ��");
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