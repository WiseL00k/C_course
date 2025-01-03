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
} LabInfo; // ʵ������Ϣ�ṹ��

typedef struct
{
    Date data;
    Date startTime;
    Date endTime;
    char *personName;
    char *content;
    char *phoneNum;
    char *roomNum;
} LabReservation; // ʵ����ԤԼ��Ϣ�ṹ��

typedef struct LabReservationNode
{
    LabReservation labReservation;
    struct LabReservationNode *next;
} LabReservationNode, *LabReservationList; // ʵ����ԤԼ��Ϣ����ṹ��

typedef struct
{
    LabInfo *labInfo;
    LabReservationList labReservation;
} Lab; // ʵ���ҽṹ��

typedef struct LabNode
{
    Lab lab;
    struct LabNode *next;
} LabNode, *LabList; // ʵ��������ṹ��

/* ʵ���ҹ��� */
// ���ʵ����
Status addLab();
// ɾ��ʵ����
Status deleteLab();
// ����ָ��ʵ������Ϣ
Status searchLabInfo();
// �޸�ʵ������Ϣ
Status modifyLabInfo();
// ��ʾ����ʵ����
Status displayAllLabInfo();

/* ԤԼ���� */
// ���ԤԼ
Status addReservation();
// ɾ��ԤԼ
Status deleteReservation();
// ��ѯԤԼ
Status searchReservation();
// �޸�ԤԼ
Status modifyReservation();
// ��ʾ����ԤԼ
Status displayAllLabReservations();

/* ͳ�ƹ��� */
// ͳ��ʵ������/��ʹ��ʱ��
Status calculateLabUsageTime();
// ͳ��ĳ����/��ʹ��ʱ��
Status calculatePersonUsageTime();
// ͳ��ĳʵ������/��ʹ�����
Status calculateLabUsageSituation();

#endif // __LAB_H__