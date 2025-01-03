#ifndef __LAB_H__
#define __LAB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status.h"

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char *location;
    char *number;
    int maxCapacity;
    char *type;
    char *admin;
} LabInfo; // 实验室信息结构体

typedef struct
{
    Date data;
    Date startTime;
    Date endTime;
    char *personName;
    char *content;
    char *phoneNum;
    char *roomNum;
} LabReservation; // 实验室预约信息结构体

typedef struct LabReservationNode
{
    LabReservation labReservation;
    struct LabReservationNode *next;
} LabReservationNode, *LabReservationList; // 实验室预约信息链表结构体

typedef struct
{
    LabInfo *labInfo;
    LabReservationList labReservation;
} Lab; // 实验室结构体

typedef struct LabNode
{
    Lab lab;
    struct LabNode *next;
} LabNode, *LabList; // 实验室链表结构体

/* 实验室功能 */
// 添加实验室
Status addLab();
// 删除实验室
Status deleteLab();
// 查找指定实验室信息
Status searchLabInfo();
// 修改实验室信息
Status modifyLabInfo();
// 显示所有实验室
Status displayAllLabInfo();

/* 预约功能 */
// 添加预约
Status addReservation();
// 删除预约
Status deleteReservation();
// 查询预约
Status searchReservation();
// 修改预约
Status modifyReservation();
// 显示所有预约
Status displayAllLabReservations();

/* 统计功能 */
// 统计实验室月/年使用时间
Status calculateLabUsageTime();
// 统计某人月/年使用时间
Status calculatePersonUsageTime();
// 统计某实验室月/年使用情况
Status calculateLabUsageSituation();

#endif // __LAB_H__