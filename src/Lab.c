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
    printf("\033[H\033[J"); // 清屏
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

    for (int i = 0; i <= 4; ++i)
    {
        switch (i)
        {
        case 0:
            puts("请输入要添加预约的预约人姓名(输入q/Q返回): ");
            break;
        case 1:
            puts("请输入要添加预约的预约内容(输入q/Q返回): ");
            break;
        case 2:
            puts("请输入要添加预约的预约人电话(输入q/Q返回): ");
            break;
        case 3:
            puts("请输入要添加预约的起始时间: (格式: mm-dd)");
            break;
        case 4:
            puts("请输入要添加预约的结束时间: (格式: mm-dd)");
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
            if (stringToDate(buffer, &bufferDate) == OK) // 将字符串转换为日期
                *allDate[i - 3] = bufferDate;
            else
            {
                i--;
                puts("输入的日期格式不正确，请重新输入");
            }
            if (i == 4)
            {
                p->labReservationCount[0]++;                              // 总预约次数加一
                newReservation.reservationID = p->labReservationCount[0]; // 生成预约ID
                LabReservationList labReserPtr = p->labReservations;
                while (labReserPtr)
                {
                    if (checkReservationConflict(&labReserPtr->labReservation, &newReservation) == ERROR)
                    {
                        char startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
                        p->labReservationCount[0]--; // 总预约次数减一
                        dateToString(labReserPtr->labReservation.startTime, startTime);
                        dateToString(labReserPtr->labReservation.endTime, endTime);
                        puts("输入的时间段与已有预约冲突，请重新输入");
                        printf("已有预约段: %s 至 %s\n", startTime, endTime);
                        i = 2;
                        break;
                    }
                    labReserPtr = labReserPtr->next;
                }
            }
        }
    }
    p->labReservationCount[newReservation.startTime.month]++;
    p->labReservationTime[newReservation.startTime.month] += getReservatonUsageTime(newReservation);
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
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
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
    puts("预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t预约人电话");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        dateToString(labReserPtr->labReservation.startTime, startTime);
        dateToString(labReserPtr->labReservation.endTime, endTime);
        LabReservation t = labReserPtr->labReservation;
        printf("%d\t\t%s\t%s\t%s\t%s\t%s\t%s\n", t.reservationID, date, startTime, endTime, t.personName, t.content, t.phoneNum);
        labReserPtr = labReserPtr->next;
    }

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
            p->labReservationCount[labReserPtr->labReservation.startTime.month]--;
            p->labReservationCount[0]--;
            p->labReservationTime[labReserPtr->labReservation.startTime.month] -= getReservatonUsageTime(labReserPtr->labReservation);
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
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
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
    puts("预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t预约人电话");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        dateToString(labReserPtr->labReservation.startTime, startTime);
        dateToString(labReserPtr->labReservation.endTime, endTime);
        printf("%d\t\t%s\t%s\t%s\t%s\t%s\t%s\n", labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
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
    puts("预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t预约人电话");
    while (labReserPtr)
    {
        dateToString(labReserPtr->labReservation.date, date);
        dateToString(labReserPtr->labReservation.startTime, startTime);
        dateToString(labReserPtr->labReservation.endTime, endTime);
        printf("%d\t\t%s\t%s\t%s\t%s\t%s\t%s\n", labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
        labReserPtr = labReserPtr->next;
    }
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
            puts("请输入新的起始时间(格式: MM-DD): ");
            scanf(" %s", startTime);
            if (stringToDate(startTime, &labReserPtr->labReservation.startTime) != OK)
            {
                puts("输入的日期格式不正确,请重试!");
                continue;
            }
            break;
        case ENDTIME:
            puts("请输入新的结束时间(格式: MM-DD): ");
            scanf(" %s", endTime);
            if (stringToDate(endTime, &labReserPtr->labReservation.endTime) != OK)
            {
                puts("输入的日期格式不正确,请重试!");
                continue;
            }
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
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
    printf("\033[H\033[J"); // 清屏
    puts("地点\t\t编号\t预约编号\t预约日期\t起始时间\t结束时间\t预约人\t实验内容\t预约人电话");
    while (p)
    {
        LabReservationNode *labReserPtr = p->lab.labReservations;
        while (labReserPtr)
        {
            dateToString(labReserPtr->labReservation.date, date);
            dateToString(labReserPtr->labReservation.startTime, startTime);
            dateToString(labReserPtr->labReservation.endTime, endTime);
            printf("%s\t%s\t%d\t\t%s\t%s\t%s\t%s\t%s\t%s\n", p->lab.labInfo.location, p->lab.labInfo.number, labReserPtr->labReservation.reservationID, date, startTime, endTime, labReserPtr->labReservation.personName, labReserPtr->labReservation.content, labReserPtr->labReservation.phoneNum);
            labReserPtr = labReserPtr->next;
        }
        p = p->next;
    }
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
        printf("%d月全部实验室的预约情况如下: \n", month);
        puts("地点\t\t编号\t预约次数\t使用天数");
        LabList p = labList;
        while (p)
        {
            printf("%s\t%s\t%7d\t\t%7d\n", p->lab.labInfo.location, p->lab.labInfo.number, p->lab.labReservationCount[month], p->lab.labReservationTime[month]);
            p = p->next;
        }
        break;
    }
    case YEARLY:
        printf("今年全部实验室的预约情况如下: \n");
        puts("地点\t\t编号\t预约次数\t使用天数");
        LabList p = labList;
        while (p)
        {
            printf("%s\t%s\t%7d\t\t%7d\n", p->lab.labInfo.location, p->lab.labInfo.number, p->lab.labReservationCount[0], p->lab.labReservationTime[0]);
            p = p->next;
        }
        break;
    }

    return OK;
}

Status calculatePersonUsageTime(StatiType statiType)
{
    char name[MAX_SIZE] = {'\0'};
    int month = 0;
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
    puts("预约日期\t地点\t\t实验室编号\t起始时间\t结束时间\t实验内容\t使用时间");
    while (p)
    {
        Lab tmpLab = p->lab;
        LabReservationNode *labReserPtr = tmpLab.labReservations;
        while (labReserPtr)
        {
            if (strcmp(labReserPtr->labReservation.personName, name) == 0)
            {
                int usageTime = getReservatonUsageTime(labReserPtr->labReservation);
                char startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'}, date[MAX_SIZE] = {'\0'};
                dateToString(labReserPtr->labReservation.date, date);
                dateToString(labReserPtr->labReservation.startTime, startTime);
                dateToString(labReserPtr->labReservation.endTime, endTime);
                if (statiType == MONTHLY)
                {
                    if (labReserPtr->labReservation.date.month == month)
                    {
                        printf("%s\t%s\t\t%s\t%s\t%s\t%s\t\t%d天\n",
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
                    printf("%s\t%s\t%s\t\t%s\t%s\t%s\t\t%d天\n",
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
    if (totalCount != 0)
    {
        if (statiType == MONTHLY)
            printf("%d月份%s的预约实验总时间为: %d 天, 预约总次数为%d \n", month, name, totalUsageTime, totalCount);
        else
            printf("今年%s的预约实验总时间为: %d 天, 预约总次数为%d \n", name, totalUsageTime, totalCount);
    }
    else
        printf("\n%s没有预约实验记录\n", name);
    return OK;
}

Status calculateLabUsageSituation(StatiType statiType)
{
    char buffer[MAX_SIZE] = {'\0'}, location[MAX_SIZE] = {'\0'}, labNumber[MAX_SIZE] = {'\0'};
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
    char *allVar[2] = {location, labNumber};
    int month = 0, totalUsageTime = 0, totalCount = 0;
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
    printf("预约编号\t预约日期\t起始时间\t结束时间\t使用时间\n");
    LabReservationNode *labReserPtr = p->labReservations;
    while (labReserPtr)
    {
        int usageTime = getReservatonUsageTime(labReserPtr->labReservation);
        dateToString(labReserPtr->labReservation.date, date);
        dateToString(labReserPtr->labReservation.startTime, startTime);
        dateToString(labReserPtr->labReservation.endTime, endTime);
        if (statiType == MONTHLY)
        {
            if (labReserPtr->labReservation.date.month == month)
            {
                printf("%d\t\t%s\t%s\t%s\t%d天\n",
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
            printf("%d\t\t%s\t%s\t%s\t%d天\n",
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
    if (totalCount != 0)
    {
        if (statiType == MONTHLY)
            printf("%d月份%s%s的预约实验总时间为: %d 天, 预约总次数为%d \n", month, p->labInfo.location, p->labInfo.number, totalUsageTime, totalCount);
        else
            printf("今年%s%s的预约实验总时间为: %d 天, 预约总次数为%d \n", p->labInfo.location, p->labInfo.number, totalUsageTime, totalCount);
    }
    else
        printf("%s%s没有预约实验记录!\n", p->labInfo.location, p->labInfo.number);
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
    char date[MAX_SIZE] = {'\0'}, startTime[MAX_SIZE] = {'\0'}, endTime[MAX_SIZE] = {'\0'};
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
        puts("文件打开失败");
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

        fstringToDate(date, &newReservation.date);
        fstringToDate(startTime, &newReservation.startTime);
        fstringToDate(endTime, &newReservation.endTime);

        strcpy(newReservation.roomNum, p->labInfo.number);
        p->labReservationCount[0]++;
        p->labReservationCount[newReservation.startTime.month]++;
        p->labReservationTime[newReservation.startTime.month] += getReservatonUsageTime(newReservation);
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
    int labReservation1StartTime = labReservation1->startTime.month * monthDays[labReservation1->startTime.month] + labReservation1->startTime.day;
    int labReservation1EndTime = labReservation1->endTime.month * monthDays[labReservation1->endTime.month] + labReservation1->endTime.day;
    int labReservation2StartTime = labReservation2->startTime.month * monthDays[labReservation2->startTime.month] + labReservation2->startTime.day;
    int labReservation2EndTime = labReservation2->endTime.month * monthDays[labReservation2->endTime.month] + labReservation2->endTime.day;
    if ((labReservation2StartTime <= labReservation1StartTime && labReservation2EndTime >= labReservation1StartTime) ||
        (labReservation2StartTime >= labReservation1StartTime && labReservation2EndTime <= labReservation1EndTime) ||
        (labReservation2StartTime <= labReservation1EndTime && labReservation2EndTime >= labReservation1EndTime))
        return ERROR;
    return OK;
}

int getReservatonUsageTime(LabReservation reservation)
{
    // 加1是因为要包含结束时间
    return 1 + reservation.endTime.month * monthDays[reservation.endTime.month] + reservation.endTime.day - reservation.startTime.month * monthDays[reservation.startTime.month] - reservation.startTime.day;
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