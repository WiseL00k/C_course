#include "Lab.h"
#include "time.h"

// 全局变量，指向实验室链表的头节点
LabList labList = NULL;
// 每个月的天数，用于计算预约时间
static int monthDays[13] = {365, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Status addLab()
{
    printf("\033[H\033[J"); // 清屏
    fflush(stdin);
    Lab newLab;
    newLab.labReservations = NULL;                                             // 初始化预约链表为空
    memset(newLab.labReservationCount, 0, sizeof(newLab.labReservationCount)); // 初始化预约次数为0
    memset(newLab.labReservationTime, 0, sizeof(newLab.labReservationTime));   // 初始化预约时间为0
    puts("请输入实验室地点(输入q/Q返回): ");
    scanf(" %s", newLab.labInfo.location);
    if (strcmp(newLab.labInfo.location, "q") == 0 || strcmp(newLab.labInfo.location, "Q") == 0)
        return FALSE;
    puts("请输入实验室编号(输入q/Q返回): ");
    scanf(" %s", newLab.labInfo.number);
    if (strcmp(newLab.labInfo.location, "q") == 0 || strcmp(newLab.labInfo.location, "Q") == 0)
        return FALSE;
    if (isLabExist(newLab))
    {
        puts("实验室已存在，请重新输入");
        return -2;
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
    printf("\033[H\033[J"); // 清屏
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
            // 彻底释放,防止内存泄漏
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
    printf("\033[H\033[J"); // 清屏
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
            puts("==========================================");
            puts("实验室信息如下: ");
            puts("==========================================");
            printf("\n实验室地点: %s\n", p->lab.labInfo.location);
            printf("实验室编号: %s\n", p->lab.labInfo.number);
            printf("实验室最多人数: %d\n", p->lab.labInfo.maxCapacity);
            printf("实验室类型: %s\n", p->lab.labInfo.type);
            printf("实验室管理员: %s\n\n", p->lab.labInfo.admin);
            puts("==========================================");
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

Status modifyLabInfo(LabInfoType infoType)
{
    printf("\033[H\033[J"); // 清屏
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
    printf("\033[H\033[J"); // 清屏
    puts("====================================================================================");
    puts("实验室地点\t实验室编号\t实验室最多人数\t\t实验室类型\t实验室管理员");
    puts("====================================================================================");
    while (p)
    {
        printf("%s%16s%20d%20s%18s\n", p->lab.labInfo.location, p->lab.labInfo.number, p->lab.labInfo.maxCapacity, p->lab.labInfo.type, p->lab.labInfo.admin);
        p = p->next;
    }
    puts("====================================================================================");
    return OK;
}

Status addReservation()
{
    printf("\033[H\033[J"); // 清屏
    fflush(stdin);
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    Date bufferDate;
    LabReservation newReservation;
    int *allDate[2] = {&newReservation.startTime, &newReservation.endTime};
    char *allVar[5] = {location, labNumber, newReservation.personName, newReservation.content, newReservation.phoneNum};

    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("请输入要添加预约的实验室地点(输入q/Q返回): ");
            break;
        case 1:
            puts("请输入要添加预约的实验室编号(输入q/Q返回): ");
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

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    newReservation.date.year = t->tm_year + 1900;
    newReservation.date.month = t->tm_mon + 1;
    newReservation.date.day = t->tm_mday;

    for (int i = 0; i <= 5; ++i)
    {
        switch (i)
        {
        case 0:
            puts("请输入预约人姓名(输入q/Q返回): ");
            break;
        case 1:
            puts("请输入要预约内容(输入q/Q返回): ");
            break;
        case 2:
            puts("请输入预约人电话(输入q/Q返回): ");
            break;
        case 3:
            puts("请输入要预约的日期(格式:MM-DD,输入q/Q返回): ");
            break;
        case 4:
            puts("请输入预约的起始时间: (节次:01-12)");
            break;
        case 5:
            puts("请输入预约的结束时间: (节次:01-12)");
            break;
        }
        if (i >= 0 && i <= 2)
        {
            scanf(" %s", buffer);
            if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
                return FALSE;
            strcpy(allVar[i + 2], buffer);
        }
        else if (i == 3)
        {
            scanf(" %s", buffer);
            if (stringToDate(buffer, &bufferDate) == OK) // 将字符串转换为日期
                newReservation.date = bufferDate;
            else
            {
                i--;
                puts("输入的日期格式不正确，请重新输入");
            }
        }
        else
        {
            int tempTime = 0;
            scanf(" %d", &tempTime);
            if (tempTime >= 1 && tempTime <= 12) // 将字符串转换为日期
                *allDate[i - 4] = tempTime;
            else
            {
                i--;
                puts("输入的时间格式不正确，请重新输入");
            }
            if (i == 5)
            {
                p->labReservationCount[0]++;                              // 总预约次数加一
                newReservation.reservationID = p->labReservationCount[0]; // 生成预约ID
                LabReservationList labReserPtr = p->labReservations;
                while (labReserPtr)
                {
                    if (checkReservationConflict(&labReserPtr->labReservation, &newReservation) == ERROR)
                    {
                        p->labReservationCount[0]--; // 总预约次数减一
                        puts("输入的时间段与已有预约冲突，请重新输入");
                        printf("已有预约段: %02d节至 %02d节\n", labReserPtr->labReservation.startTime, labReserPtr->labReservation.endTime);
                        i = 3;
                        break;
                    }
                    labReserPtr = labReserPtr->next;
                }
            }
        }
    }
    p->labReservationCount[newReservation.date.month]++;
    p->labReservationTime[newReservation.date.month] += getReservatonUsageTime(newReservation);
    p->labReservationTime[0] += getReservatonUsageTime(newReservation);

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
    int startTime = 0, endTime = 0;
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("请输入要删除预约的实验室地点(输入q/Q返回): ");
            break;
        case 1:
            puts("请输入要删除预约的实验室编号(输入q/Q返回): ");
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

    printf("%s的%s实验室预约信息如下: \n", p->labInfo.location, p->labInfo.number);
    puts("===================================================================================");
    puts("预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t预约人电话");
    puts("===================================================================================");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        startTime = labReserPtr->labReservation.startTime;
        endTime = labReserPtr->labReservation.endTime;
        LabReservation t = labReserPtr->labReservation;
        printf("%d\t\t%s\t%02d\t%02d\t%s\t%s\t%s\n", t.reservationID, date, startTime, endTime, t.personName, t.content, t.phoneNum);
        labReserPtr = labReserPtr->next;
    }
    puts("===================================================================================");
    int reservationID = 0;
    while (1)
    {
        puts("请输入要删除的预约编号(输入q/Q返回): ");
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        reservationID = atoi(buffer);
        if (reservationID <= 0 || reservationID > p->labReservationCount[0])
        {
            puts("预约编号不存在，请重新输入");
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
            p->labReservationCount[labReserPtr->labReservation.date.month]--;
            p->labReservationCount[0]--;
            p->labReservationTime[labReserPtr->labReservation.date.month] -= getReservatonUsageTime(labReserPtr->labReservation);
            p->labReservationTime[0] -= getReservatonUsageTime(labReserPtr->labReservation);
            free(labReserPtr);
            break;
        }
        labReserPre = labReserPtr;
        labReserPtr = labReserPtr->next;
    }
    return OK;
}

Status searchReservation()
{
    int startTime = 0, endTime = 0;
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("请输入要查找预约的实验室地点(输入q/Q返回): ");
            break;
        case 1:
            puts("请输入要查找预约的实验室编号(输入q/Q返回): ");
            break;
        }
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        strcpy(allVar[i], buffer);
    }

    LabPtr p = findLab(location, labNumber);
    if (!p)
        return -2; // 没有找到实验室
    LabReservationNode *labReserPtr = p->labReservations;
    printf("%s的%s实验室预约信息如下: \n", p->labInfo.location, p->labInfo.number);
    puts("=================================================================================================================");
    puts("预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t预约人电话");
    puts("=================================================================================================================");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        startTime = labReserPtr->labReservation.startTime;
        endTime = labReserPtr->labReservation.endTime;
        printf("%d\t\t%s\t%02d\t\t%02d\t\t%s\t%s\t%s\n", labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
        labReserPtr = labReserPtr->next;
    }
    puts("=================================================================================================================");
    return OK;
}

Status modifyReservation(ReservationInfoType infoType)
{
    int startTime = 0, endTime = 0;
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("请输入要修改预约的实验室地点(输入q/Q返回): ");
            break;
        case 1:
            puts("请输入要修改预约的实验室编号(输入q/Q返回): ");
            break;
        }
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        strcpy(allVar[i], buffer);
    }

    LabPtr p = findLab(location, labNumber);
    if (!p)
    {
        puts("没有找到该实验室!");
        return -2; // 没有找到实验室
    }

    LabReservationNode *labReserPtr = p->labReservations;
    printf("%s的%s实验室预约信息如下: \n", p->labInfo.location, p->labInfo.number);
    puts("=====================================================================================================================");
    puts("预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t预约人电话");
    puts("=====================================================================================================================");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        startTime = labReserPtr->labReservation.startTime;
        endTime = labReserPtr->labReservation.endTime;
        printf("%d\t\t%s\t%02d\t%02d\t%s\t%s\t%s\n", labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
        labReserPtr = labReserPtr->next;
    }
    puts("=====================================================================================================================");
    int reservationID;
    while (1)
    {
        puts("请输入要修改的预约编号(输入q/Q返回): ");
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        reservationID = atoi(buffer);
        if (reservationID <= 0 || reservationID > p->labReservationCount[0])
        {
            puts("预约编号不存在，请重新输入");
            continue;
        }
        break;
    }
    labReserPtr = p->labReservations; // 重新指向头结点
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
            puts("请输入新的起始时间(节次：01-12): ");
            scanf(" %d", &startTime);
            if (startTime <= 0 || startTime > 12 || startTime > labReserPtr->labReservation.endTime)
            {
                puts("输入的时间格式不正确,请重试!");
                continue;
            }
            labReserPtr->labReservation.startTime = startTime;
            break;
        case ENDTIME:
            puts("请输入新的结束时间(节次：01-12): ");
            scanf(" %d", &endTime);
            if (endTime <= 0 || endTime > 12 || endTime < labReserPtr->labReservation.startTime)
            {
                puts("输入的时间格式不正确,请重试!");
                continue;
            }
            labReserPtr->labReservation.endTime = endTime;
            break;
        case PERSONNAME:
            puts("请输入新的预约人姓名: ");
            scanf(" %s", labReserPtr->labReservation.personName);
            break;
        case CONTENT:
            puts("请输入新的实验内容: ");
            scanf(" %s", labReserPtr->labReservation.content);
            break;
        case PHONENUM:
            puts("请输入新的预约人电话: ");
            scanf(" %s", labReserPtr->labReservation.phoneNum);
            break;
        }
        return OK;
    }
}

Status displayAllLabReservations()
{
    LabList p = labList;
    int startTime = 0, endTime = 0;
    char date[MAX_SIZE] = {'\0'};
    printf("\033[H\033[J"); // 清屏
    puts("====================================================================================================================================================");
    puts("地点\t\t编号\t预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t\t预约人电话");
    puts("====================================================================================================================================================");
    while (p)
    {
        LabReservationNode *labReserPtr = p->lab.labReservations;
        while (labReserPtr)
        {
            dateToString(labReserPtr->labReservation.date, date);
            startTime = labReserPtr->labReservation.startTime;
            endTime = labReserPtr->labReservation.endTime;
            printf("%s\t%s\t%d\t\t%s\t%02d\t\t%02d\t\t%s\t%s\t\t%s\n", p->lab.labInfo.location, p->lab.labInfo.number, labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
            labReserPtr = labReserPtr->next;
        }
        p = p->next;
    }
    puts("====================================================================================================================================================");
    return OK;
}

Status calculateAllLabSituation(StatiType statiType)
{
    fflush(stdin);
    switch (statiType)
    {
    case MONTHLY:
    {
        int month = 0;
        month = getMonthInput();
        printf("%d月全部实验室的预约情况(按时间降序排列)如下: \n", month);
        puts("=========================================");
        puts("地点\t\t编号\t预约次数\t使用节时");
        puts("=========================================");
        LabList sortedLabList = (LabList)malloc(sizeof(LabNode));
        sortedLabList->next = NULL;
        LabList p = labList, q = NULL, minptr = labList, minqtr = NULL, temp = p;
        while (labList)
        {
            p = labList, q = NULL, minptr = labList, minqtr = NULL;
            while (p)
            {
                if (p->lab.labReservationTime[month] < minptr->lab.labReservationTime[month])
                {
                    minqtr = q;
                    minptr = p;
                }
                q = p;
                p = p->next;
            }
            if (minqtr)
                minqtr->next = minptr->next;
            else
                labList = minptr->next;
            minptr->next = sortedLabList->next;
            sortedLabList->next = minptr;
        }

        labList = sortedLabList->next;
        p = labList;
        while (p)
        {
            printf("%s\t%s\t%7d\t\t%7d\n", p->lab.labInfo.location, p->lab.labInfo.number, p->lab.labReservationCount[month], p->lab.labReservationTime[month]);
            p = p->next;
        }
        break;
    }
    case YEARLY:
        printf("今年全部实验室的预约情况(按时间降序排列)如下: \n");
        puts("================================================");
        puts("地点\t\t编号\t预约次数\t使用节时");
        puts("================================================");
        LabList sortedLabList = (LabList)malloc(sizeof(LabNode));
        sortedLabList->next = NULL;
        LabList p = labList, q = NULL, minptr = labList, minqtr = NULL, temp = p;
        while (labList)
        {
            p = labList, q = NULL, minptr = labList, minqtr = NULL;
            while (p)
            {
                if (p->lab.labReservationTime[0] < minptr->lab.labReservationTime[0])
                {
                    minqtr = q;
                    minptr = p;
                }
                q = p;
                p = p->next;
            }
            if (minqtr)
                minqtr->next = minptr->next;
            else
                labList = minptr->next;
            minptr->next = sortedLabList->next;
            sortedLabList->next = minptr;
        }

        labList = sortedLabList->next;
        p = labList;

        while (p)
        {
            printf("%s\t%s\t%7d\t\t%7d\n", p->lab.labInfo.location, p->lab.labInfo.number, p->lab.labReservationCount[0], p->lab.labReservationTime[0]);
            p = p->next;
        }
        break;
    }
    puts("================================================");
    return OK;
}

Status calculatePersonUsageTime(StatiType statiType)
{
    char name[MAX_SIZE] = {'\0'};
    int month = 0, startTime = 0, endTime = 0;
    puts("请输入要查询的预约人姓名: ");
    fflush(stdin);
    scanf(" %s", name);
    if (statiType == MONTHLY)
    {
        month = getMonthInput();
    }

    LabList p = labList;
    int totalUsageTime = 0, totalCount = 0;
    printf("%s的各预约情况如下: \n", name);
    puts("=====================================================================================================================");
    puts("预约日期\t地点\t\t实验室编号\t起始时间\t结束时间\t实验内容\t使用时间");
    puts("=====================================================================================================================");
    while (p)
    {
        Lab tmpLab = p->lab;
        LabReservationNode *labReserPtr = tmpLab.labReservations;
        while (labReserPtr)
        {
            if (strcmp(labReserPtr->labReservation.personName, name) == 0)
            {
                int usageTime = getReservatonUsageTime(labReserPtr->labReservation);
                char date[MAX_SIZE] = {'\0'};
                dateToString(labReserPtr->labReservation.date, date);
                startTime = labReserPtr->labReservation.startTime;
                endTime = labReserPtr->labReservation.endTime;
                if (statiType == MONTHLY)
                {
                    if (labReserPtr->labReservation.date.month == month)
                    {
                        printf("%s\t%s\t%s\t\t%02d\t\t%02d\t\t%s\t%d节\n",
                               date,
                               tmpLab.labInfo.location,
                               tmpLab.labInfo.number,
                               startTime,
                               endTime,
                               labReserPtr->labReservation.content,
                               usageTime);
                        totalUsageTime += usageTime;
                        totalCount++;
                    }
                }
                else
                {
                    printf("%s\t%s\t%s\t\t%02d\t\t%02d\t\t%s\t%d节\n",
                           date,
                           tmpLab.labInfo.location,
                           tmpLab.labInfo.number,
                           startTime,
                           endTime,
                           labReserPtr->labReservation.content,
                           usageTime);
                    totalUsageTime += usageTime;
                    totalCount++;
                }
            }
            labReserPtr = labReserPtr->next;
        }
        p = p->next;
    }
    puts("=====================================================================================================================");
    if (totalCount != 0)
    {
        if (statiType == MONTHLY)
            printf("%d月份%s的预约实验总时间为: %d 节时, 预约总次数为%d \n", month, name, totalUsageTime, totalCount);
        else
            printf("今年%s的预约实验总时间为: %d 节时, 预约总次数为%d \n", name, totalUsageTime, totalCount);
    }
    else
    {
        printf("\033[H\033[J"); // 清屏
        printf("\n%s没有预约实验记录\n", name);
    }
    return OK;
}

Status calculateLabUsageSituation(StatiType statiType)
{
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    int month = 0, totalUsageTime = 0, totalCount = 0, startTime = 0, endTime = 0;
    for (int i = 0; i <= 1; ++i)
    {
        switch (i)
        {
        case 0:
            puts("请输入要统计的实验室地点(输入q/Q返回): ");
            break;
        case 1:
            puts("请输入要统计的实验室编号(输入q/Q返回): ");
            break;
        }
        scanf(" %s", buffer);
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            return FALSE;
        strcpy(allVar[i], buffer);
    }

    LabPtr p = findLab(location, labNumber);
    if (!p)
        return -2; // 没有找到实验室

    if (statiType == MONTHLY)
    {
        month = getMonthInput();
    }

    printf("%s%s实验室使用情况如下: \n", p->labInfo.location, p->labInfo.number);
    puts("======================================================================================");
    printf("预约编号\t预约日期\t起始时间\t结束时间\t使用时间\n");
    puts("======================================================================================");
    LabReservationNode *labReserPtr = p->labReservations;
    while (labReserPtr)
    {
        int usageTime = getReservatonUsageTime(labReserPtr->labReservation);
        dateToString(labReserPtr->labReservation.date, date);
        startTime = labReserPtr->labReservation.startTime;
        endTime = labReserPtr->labReservation.endTime;
        if (statiType == MONTHLY)
        {
            if (labReserPtr->labReservation.date.month == month)
            {
                printf("%d\t\t%s\t%02d\t\t%02d\t\t%d节\n",
                       labReserPtr->labReservation.reservationID,
                       date,
                       startTime,
                       endTime,
                       usageTime);
                totalUsageTime += usageTime;
                totalCount++;
            }
        }
        else
        {
            printf("%d\t\t%s\t%02d\t\t%02d\t\t%d节\n",
                   labReserPtr->labReservation.reservationID,
                   date,
                   startTime,
                   endTime,
                   usageTime);
            totalUsageTime += usageTime;
            totalCount++;
        }
        labReserPtr = labReserPtr->next;
    }
    puts("======================================================================================");
    if (totalCount != 0)
    {
        if (statiType == MONTHLY)
            printf("%d月份%s%s的预约实验总时间为: %d 节时, 预约总次数为%d \n", month, p->labInfo.location, p->labInfo.number, totalUsageTime, totalCount);
        else
            printf("今年%s%s的预约实验总时间为: %d 节时, 预约总次数为%d \n", p->labInfo.location, p->labInfo.number, totalUsageTime, totalCount);
    }
    else
    {
        printf("\033[H\033[J"); // 清屏
        printf("%s%s没有预约实验记录!\n", p->labInfo.location, p->labInfo.number);
    }
    return OK;
}

Status saveLabInfo()
{
    FILE *fp = fopen("./lab.txt", "w");
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
    FILE *fp = fopen("./lab.txt", "r");
    if (fp == NULL)
    {
        puts("文件打开失败");
        return ERROR;
    }
    Lab newLab;
    memset(newLab.labReservationCount, 0, sizeof(newLab.labReservationCount)); // 初始化预约次数为0
    memset(newLab.labReservationTime, 0, sizeof(newLab.labReservationTime));   // 初始化预约时间为0
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
    int startTime = 0, endTime = 0;
    char date[MAX_SIZE] = {'\0'};
    FILE *fp = fopen("./reservation.txt", "w");
    if (fp == NULL)
    {
        puts("文件打开失败");
        return ERROR;
    }
    LabList p = labList;
    while (p)
    {
        LabReservationNode *labReserPtr = p->lab.labReservations;
        while (labReserPtr)
        {
            dateToString(labReserPtr->labReservation.date, date);
            startTime = labReserPtr->labReservation.startTime;
            endTime = labReserPtr->labReservation.endTime;
            fprintf(fp, "%s %s %s %02d %02d %s %s %s\n", p->lab.labInfo.location, p->lab.labInfo.number, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
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
        puts("文件打开失败");
        return ERROR;
    }
    char location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'}, date[MAX_SIZE] = {'\0'}, personName[MAX_SIZE] = {'\0'};
    int startTime = 0, endTime = 0;
    LabReservation newReservation;
    while (fscanf(fp, "%s %s", location, labNumber) != EOF)
    {
        LabPtr p = findLab(location, labNumber);
        if (!p)
            return -2;
        // 读取预约信息
        fscanf(fp, "%s %02d %02d %s %s %s", date, &startTime, &endTime, newReservation.personName, newReservation.content, newReservation.phoneNum);
        newReservation.reservationID = 0;

        fstringToDate(date, &newReservation.date);
        newReservation.startTime = startTime;
        newReservation.endTime = endTime;
        strcpy(newReservation.roomNum, p->labInfo.number);
        p->labReservationCount[0]++;
        p->labReservationCount[newReservation.date.month]++;
        p->labReservationTime[newReservation.date.month] += getReservatonUsageTime(newReservation);
        p->labReservationTime[0] += getReservatonUsageTime(newReservation);

        newReservation.reservationID = p->labReservationCount[0];

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

Status fstringToDate(char *str, Date *date)
{
    if (sscanf(str, "%d-%d-%d", &date->year, &date->month, &date->day) == 3)
        return OK;
    return ERROR;
}

Status stringToDate(char *str, Date *date)
{
    date->year = 2025;
    if (sscanf(str, "%d-%d", &date->month, &date->day) == 2)
        if (date->month >= 1 && date->month <= 12 && date->day >= 1 && date->day <= 31)
            return OK;
    return ERROR;
}

Status dateToString(Date date, char *str)
{
    sprintf(str, "%d-%d-%d", date.year, date.month, date.day);
    return OK;
}

Status checkReservationConflict(LabReservation *labReservation1, LabReservation *labReservation2)
{
    // 不同实验室的预约,没有冲突
    if (labReservation1->reservationID == labReservation2->reservationID || strcmp(labReservation1->roomNum, labReservation2->roomNum) != 0)
        return OK;
    int labReservation1StartTime = labReservation1->startTime;
    int labReservation1EndTime = labReservation1->endTime;
    int labReservation2StartTime = labReservation2->startTime;
    int labReservation2EndTime = labReservation2->endTime;
    if ((labReservation2StartTime <= labReservation1StartTime && labReservation2EndTime >= labReservation1StartTime) ||
        (labReservation2StartTime >= labReservation1StartTime && labReservation2EndTime <= labReservation1EndTime) ||
        (labReservation2StartTime <= labReservation1EndTime && labReservation2EndTime >= labReservation1EndTime))
        return ERROR;
    return OK;
}

int getReservatonUsageTime(LabReservation reservation)
{
    // 返回预约使用时间
    return reservation.endTime - reservation.startTime;
}

int getMonthInput()
{
    int month = 0;
    while (1)
    {
        puts("请输入月份(范围: 1-12): ");
        scanf(" %d", &month);
        if (month <= 0 || month > 12)
        {
            puts("输入的月份不正确，请重新输入");
            continue;
        }
        break;
    }
    return month;
}