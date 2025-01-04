#ifndef __LAB_H__
#define __LAB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "status.h"

#define MAX_SIZE 15

typedef enum
{
    LOCATION,
    NUMBER,
    MAXCAPACITY,
    TYPE,
    ADMIN,
} LabInfoType;

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char location[MAX_SIZE]; // ʵ���ҵص�
    char number[MAX_SIZE];   // ʵ���ұ��
    int maxCapacity;         // ʵ�����������
    char type[MAX_SIZE];     // ʵ��������
    char admin[MAX_SIZE];    // ʵ���ҹ���Ա
} LabInfo;                   // ʵ������Ϣ�ṹ��

typedef struct
{
    Date data;                 // ����
    Date startTime;            // ��ʼʱ��
    Date endTime;              // ����ʱ��
    char personName[MAX_SIZE]; // ԤԼ������
    char content[MAX_SIZE];    // ʵ������
    char phoneNum[MAX_SIZE];   // ԤԼ�˵绰
    char roomNum[MAX_SIZE];    // ԤԼʵ���ұ��
} LabReservation;              // ʵ����ԤԼ��Ϣ�ṹ��

typedef struct LabReservationNode
{
    LabReservation labReservation;
    struct LabReservationNode *next;
} LabReservationNode, *LabReservationList; // ʵ����ԤԼ��Ϣ����ṹ��

typedef struct
{
    LabInfo labInfo;
    LabReservationList labReservation;
} Lab, *LabPtr; // ʵ���ҽṹ��

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
Status modifyLabInfo(LabInfoType infoType);
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

/* �ļ��������� */
// ����ʵ������Ϣ
Status saveLabInfo();
// ��ȡʵ������Ϣ
Status loadLabInfo();
// ����ԤԼ��Ϣ
Status saveLabReservations();
// ��ȡԤԼ��Ϣ
Status loadLabReservations();
// ����ͳ����Ϣ
Status saveStatistics();
// ��ȡͳ����Ϣ
Status loadStatistics();

/* �������� */
// �ж�ʵ�����Ƿ��Ѵ���
Status isLabExist(Lab lab);
// ����ָ��ʵ���Ҳ�������ָ��
LabPtr findLab(char *location, char *number);

#endif // __LAB_H__