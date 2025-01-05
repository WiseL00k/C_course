#ifndef __LAB_H__
#define __LAB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "status.h"

#define MAX_SIZE 20

typedef enum
{
    LOCATION,
    NUMBER,
    MAXCAPACITY,
    TYPE,
    ADMIN,
} LabInfoType;

typedef enum
{
    STARTTIME,
    ENDTIME,
    PERSONNAME,
    CONTENT,
    PHONENUM,
} ReservationInfoType;

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char location[MAX_SIZE]; // 实验室地点
    char number[MAX_SIZE];   // 实验室编号
    int maxCapacity;         // 实验室最多人数
    char type[MAX_SIZE];     // 实验室类型
    char admin[MAX_SIZE];    // 实验室管理员
} LabInfo;                   // 实验室信息结构体

typedef struct
{
    int reservationID;         // 预约编号
    Date date;                 // 预约日期
    Date startTime;            // 起始时间
    Date endTime;              // 结束时间
    char personName[MAX_SIZE]; // 预约人姓名
    char content[MAX_SIZE];    // 实验内容
    char phoneNum[MAX_SIZE];   // 预约人电话
    char roomNum[MAX_SIZE];    // 预约实验室编号
} LabReservation;              // 实验室预约信息结构体

typedef struct LabReservationNode
{
    LabReservation labReservation;
    struct LabReservationNode *next;
} LabReservationNode, *LabReservationList; // 实验室预约信息链表结构体

typedef struct
{
    LabInfo labInfo;
    LabReservationList labReservations;
    int labReservationCount; // 实验室预约次数
} Lab, *LabPtr;              // 实验室结构体

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
Status modifyLabInfo(LabInfoType infoType);
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
Status modifyReservation(ReservationInfoType infoType);
// 显示所有预约
Status displayAllLabReservations();

/* 统计功能 */
// 统计实验室月/年使用时间
Status calculateLabUsageTime();
// 统计某人月/年使用时间
Status calculatePersonUsageTime();
// 统计某实验室月/年使用情况
Status calculateLabUsageSituation();

/* 文件操作功能 */
// 读取实验室信息
Status loadLabInfo();
// 保存实验室信息
Status saveLabInfo();
// 读取预约信息
Status loadLabReservations();
// 保存预约信息
Status saveLabReservations();

/* 辅助函数 */
// 判断实验室是否已存在
Status isLabExist(Lab lab);
// 查找指定实验室并返回其指针
LabPtr findLab(char *location, char *number);

Status stringToDate(char *str, Date *date);
Status dateToString(Date date, char *str);
Status checkReservationConflict(LabReservation *labReservation1, LabReservation *labReservation2);

#endif // __LAB_H__