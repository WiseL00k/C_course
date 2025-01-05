#include "Lab.h"
#include "time.h"

LabList labList = NULL; // ȫ�ֱ�����ָ��ʵ���������ͷ�ڵ�

Status addLab()
{
    system("cls");
    fflush(stdin);
    Lab newLab;
    newLab.labReservations = NULL;  // ��ʼ��ԤԼ����Ϊ��
    newLab.labReservationCount = 0; // ��ʼ��ԤԼ����Ϊ0
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
            // �����ͷ�,��ֹ�ڴ�й©
            LabReservationList labResPtr = p->lab.labReservations, tmp = NULL;
            while (labResPtr)
            {
                tmp = labResPtr;
                labResPtr = labResPtr->next;
                free(tmp);
            }
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
    system("cls");
    fflush(stdin);
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    Date bufferDate;
    LabReservation newReservation;
    Date *allDate[2] = {&newReservation.startTime, &newReservation.endTime};
    char *allVar[5] = {location, labNumber, newReservation.personName, newReservation.content, newReservation.phoneNum};

    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("������Ҫ���ԤԼ��ʵ���ҵص�(����q/Q����): ");
            break;
        case 1:
            puts("������Ҫ���ԤԼ��ʵ���ұ��(����q/Q����): ");
            break;
        }
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        strcpy(allVar[i], buffer);
    }

    LabPtr p = findLab(location, labNumber);
    if (!p)
        return -2;

    strcpy(newReservation.roomNum, p->labInfo.number);
    p->labReservationCount++;
    newReservation.reservationID = p->labReservationCount;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    newReservation.date.year = t->tm_year + 1900;
    newReservation.date.month = t->tm_mon + 1;
    newReservation.date.day = t->tm_mday;

    for (int i = 0; i <= 4; ++i)
    {
        switch (i)
        {
        case 0:
            puts("������Ҫ���ԤԼ��ԤԼ������(����q/Q����): ");
            break;
        case 1:
            puts("������Ҫ���ԤԼ��ԤԼ����(����q/Q����): ");
            break;
        case 2:
            puts("������Ҫ���ԤԼ��ԤԼ�˵绰(����q/Q����): ");
            break;
        case 3:
            puts("������Ҫ���ԤԼ����ʼʱ��: (��ʽ: yyyy-mm-dd)");
            break;
        case 4:
            puts("������Ҫ���ԤԼ�Ľ���ʱ��: (��ʽ: yyyy-mm-dd)");
            break;
        }
        if (i >= 0 && i <= 2)
        {
            scanf(" %s", buffer);
            if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
                return FALSE;
            strcpy(allVar[i + 2], buffer);
        }
        else
        {
            scanf(" %s", buffer);
            if (stringToDate(buffer, &bufferDate) == OK) // ���ַ���ת��Ϊ����
                *allDate[i - 3] = bufferDate;
            else
            {
                i--;
                puts("��������ڸ�ʽ����ȷ������������");
            }
        }
    }

    if (p->labReservations == NULL)
    {
        p->labReservations = (LabReservationList)malloc(sizeof(LabReservationNode));
        if (p->labReservations == NULL)
            return OVERFLOW;
        p->labReservations->labReservation = newReservation;
        p->labReservations->next = NULL;
    }
    else
    {
        LabReservationList q = p->labReservations;
        while (q->next != NULL)
            q = q->next;
        LabReservationList tmp = (LabReservationList)malloc(sizeof(LabReservationNode));
        if (tmp == NULL)
            return OVERFLOW;
        tmp->labReservation = newReservation;
        tmp->next = NULL;
        q->next = tmp;
    }

    return OK;
}

Status deleteReservation()
{
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("������Ҫɾ��ԤԼ��ʵ���ҵص�(����q/Q����): ");
            break;
        case 1:
            puts("������Ҫɾ��ԤԼ��ʵ���ұ��(����q/Q����): ");
            break;
        }
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        strcpy(allVar[i], buffer);
    }

    LabPtr p = findLab(location, labNumber);
    if (!p)
        return -2;
    LabReservationNode *labReserPtr = p->labReservations, *labReserPre = NULL;

    printf("%s��%sʵ����ԤԼ��Ϣ����: \n", p->labInfo.location, p->labInfo.number);
    puts("ԤԼ���\tԤԼ����\t��ʼʱ��\t����ʱ��\tԤԼ��\tʵ������\tԤԼ�˵绰");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        dateToString(labReserPtr->labReservation.startTime, startTime);
        dateToString(labReserPtr->labReservation.endTime, endTime);
        LabReservation t = labReserPtr->labReservation;
        printf("%d %s %s %s %s %s %s\n", t.reservationID, date, startTime, endTime, t.personName, t.content, t.phoneNum);
        labReserPtr = labReserPtr->next;
    }

    int reservationID = 0;
    while (1)
    {
        puts("������Ҫɾ����ԤԼ���(����q/Q����): ");
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        reservationID = atoi(buffer);
        if (reservationID <= 0 || reservationID > p->labReservationCount)
        {
            puts("ԤԼ��Ų����ڣ�����������");
            continue;
        }
        break;
    }

    labReserPtr = p->labReservations;
    while (labReserPtr)
    {
        if (labReserPtr->labReservation.reservationID == reservationID)
        {
            if (labReserPre == NULL)
                p->labReservations = labReserPtr->next;
            else
                labReserPre->next = labReserPtr->next;
            free(labReserPtr);
            break;
        }
        labReserPre = labReserPtr;
        labReserPtr = labReserPtr->next;
    }
    p->labReservationCount--;
    return OK;
}

Status searchReservation()
{
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("������Ҫ����ԤԼ��ʵ���ҵص�(����q/Q����): ");
            break;
        case 1:
            puts("������Ҫ����ԤԼ��ʵ���ұ��(����q/Q����): ");
            break;
        }
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        strcpy(allVar[i], buffer);
    }

    LabPtr p = findLab(location, labNumber);
    if (!p)
        return -2; // û���ҵ�ʵ����
    LabReservationNode *labReserPtr = p->labReservations;
    printf("%s��%sʵ����ԤԼ��Ϣ����: \n", p->labInfo.location, p->labInfo.number);
    puts("ԤԼ���\tԤԼ����\t��ʼʱ��\t����ʱ��\tԤԼ��\tʵ������\tԤԼ�˵绰");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        dateToString(labReserPtr->labReservation.startTime, startTime);
        dateToString(labReserPtr->labReservation.endTime, endTime);
        printf("%d %s %s %s %s %s %s\n", labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
        labReserPtr = labReserPtr->next;
    }
    return OK;
}

Status modifyReservation(ReservationInfoType infoType)
{
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("������Ҫ�޸�ԤԼ��ʵ���ҵص�(����q/Q����): ");
            break;
        case 1:
            puts("������Ҫ�޸�ԤԼ��ʵ���ұ��(����q/Q����): ");
            break;
        }
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        strcpy(allVar[i], buffer);
    }

    LabPtr p = findLab(location, labNumber);
    if (!p)
        return -2; // û���ҵ�ʵ����

    LabReservationNode *labReserPtr = p->labReservations;
    printf("%s��%sʵ����ԤԼ��Ϣ����: \n", p->labInfo.location, p->labInfo.number);
    puts("ԤԼ���\tԤԼ����\t��ʼʱ��\t����ʱ��\tԤԼ��\tʵ������\tԤԼ�˵绰");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        dateToString(labReserPtr->labReservation.startTime, startTime);
        dateToString(labReserPtr->labReservation.endTime, endTime);
        printf("%d %s %s %s %s %s %s\n", labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
        labReserPtr = labReserPtr->next;
    }
    int reservationID;
    while (1)
    {
        puts("������Ҫ�޸ĵ�ԤԼ���(����q/Q����): ");
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        reservationID = atoi(buffer);
        if (reservationID <= 0 || reservationID > p->labReservationCount)
        {
            puts("ԤԼ��Ų����ڣ�����������");
            continue;
        }
        break;
    }
    labReserPtr = p->labReservations; // ����ָ��ͷ���
    while (labReserPtr)
    {
        if (labReserPtr->labReservation.reservationID == reservationID)
            break;
        labReserPtr = labReserPtr->next;
    }

    while (1)
    {
        switch (infoType)
        {
        case STARTTIME:
            puts("�������µ���ʼʱ��(��ʽ: YYYY-MM-DD): ");
            scanf(" %s", startTime);
            if (stringToDate(startTime, &labReserPtr->labReservation.startTime) != OK)
            {
                puts("��������ڸ�ʽ����ȷ,������!");
                continue;
            }
            break;
        case ENDTIME:
            puts("�������µĽ���ʱ��(��ʽ: YYYY-MM-DD): ");
            scanf(" %s", endTime);
            if (stringToDate(endTime, &labReserPtr->labReservation.endTime) != OK)
            {
                puts("��������ڸ�ʽ����ȷ,������!");
                continue;
            }
            break;
        case PERSONNAME:
            puts("�������µ�ԤԼ������: ");
            scanf(" %s", labReserPtr->labReservation.personName);
            break;
        case CONTENT:
            puts("�������µ�ʵ������: ");
            scanf(" %s", labReserPtr->labReservation.content);
            break;
        case PHONENUM:
            puts("�������µ�ԤԼ�˵绰: ");
            scanf(" %s", labReserPtr->labReservation.phoneNum);
            break;
        }
        return OK;
    }
}

Status displayAllLabReservations()
{
    LabList p = labList;
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
    system("cls");
    puts("�ص�\t���\tԤԼ���\tԤԼ����\t��ʼʱ��\t����ʱ��\tԤԼ��\tʵ������\tԤԼ�˵绰");
    while (p)
    {
        LabReservationNode *labReserPtr = p->lab.labReservations;
        while (labReserPtr)
        {
            dateToString(labReserPtr->labReservation.date, date);
            dateToString(labReserPtr->labReservation.startTime, startTime);
            dateToString(labReserPtr->labReservation.endTime, endTime);
            printf("%s %s %d %s %s %s %s %s %s\n", p->lab.labInfo.location, p->lab.labInfo.number, labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
            labReserPtr = labReserPtr->next;
        }
        p = p->next;
    }
    return OK;
}

Status saveLabInfo()
{
    FILE *fp = fopen("./lab.txt", "w");
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
    FILE *fp = fopen("./lab.txt", "r");
    if (fp == NULL)
    {
        puts("�ļ���ʧ��");
        return ERROR;
    }
    Lab newLab;
    newLab.labReservationCount = 0;
    while (fscanf(fp, "%s %s %d %s %s %d", newLab.labInfo.location, newLab.labInfo.number, &newLab.labInfo.maxCapacity, newLab.labInfo.type, newLab.labInfo.admin) != EOF)
    {
        newLab.labReservations = NULL;
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

Status saveLabReservations()
{
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
    FILE *fp = fopen("./reservation.txt", "w");
    if (fp == NULL)
    {
        puts("�ļ���ʧ��");
        return ERROR;
    }
    LabList p = labList;
    while (p)
    {
        LabReservationNode *labReserPtr = p->lab.labReservations;
        while (labReserPtr)
        {
            dateToString(labReserPtr->labReservation.date, date);
            dateToString(labReserPtr->labReservation.startTime, startTime);
            dateToString(labReserPtr->labReservation.endTime, endTime);
            fprintf(fp, "%s %s %s %s %s %s %s %s\n", p->lab.labInfo.location, p->lab.labInfo.number, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
            labReserPtr = labReserPtr->next;
        }
        p = p->next;
    }
    fclose(fp);
    return OK;
}

Status loadLabReservations()
{
    FILE *fp = fopen("./reservation.txt", "r");
    if (fp == NULL)
    {
        puts("�ļ���ʧ��");
        return ERROR;
    }
    char location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'}, date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'}, personName[MAX_SIZE] = {'\0'};
    LabReservation newReservation;
    while (fscanf(fp, "%s %s", location, labNumber) != EOF)
    {
        LabPtr p = findLab(location, labNumber);
        if (!p)
            return -2;
        fscanf(fp, "%s %s %s %s %s %s", date, startTime, endTime, newReservation.personName, newReservation.content, newReservation.phoneNum);
        newReservation.reservationID = 0;

        stringToDate(date, &newReservation.date);
        stringToDate(startTime, &newReservation.startTime);
        stringToDate(endTime, &newReservation.endTime);

        strcpy(newReservation.roomNum, p->labInfo.number);
        p->labReservationCount++;
        newReservation.reservationID = p->labReservationCount;

        if (p->labReservations == NULL)
        {
            p->labReservations = (LabReservationList)malloc(sizeof(LabReservationNode));
            if (p->labReservations == NULL)
                return OVERFLOW;
            p->labReservations->labReservation = newReservation;
            p->labReservations->next = NULL;
        }
        else
        {
            LabReservationList q = p->labReservations;
            while (q->next != NULL)
                q = q->next;
            LabReservationList tmp = (LabReservationList)malloc(sizeof(LabReservationNode));
            if (tmp == NULL)
                return OVERFLOW;
            tmp->labReservation = newReservation;
            tmp->next = NULL;
            q->next = tmp;
        }
    }
    fclose(fp);
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
    LabList p = labList;
    while (p != NULL)
    {
        if (strcmp(location, p->lab.labInfo.location) == 0 && strcmp(number, p->lab.labInfo.number) == 0)
            return &(p->lab);
        p = p->next;
    }
    return NULL;
}

Status stringToDate(char *str, Date *date)
{
    if (sscanf(str, "%d-%d-%d", &date->year, &date->month, &date->day) == 3)
        return OK;
    return ERROR;
}

Status dateToString(Date date, char *str)
{
    sprintf(str, "%d-%d-%d", date.year, date.month, date.day);
    return OK;
}
