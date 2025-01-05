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
    char location[MAX_SIZE]; // ʵ���ҵص�
    char number[MAX_SIZE];   // ʵ���ұ��
    int maxCapacity;         // ʵ�����������
    char type[MAX_SIZE];     // ʵ��������
    char admin[MAX_SIZE];    // ʵ���ҹ���Ա
} LabInfo;                   // ʵ������Ϣ�ṹ��

typedef struct
{
    int reservationID;         // ԤԼ���
    Date date;                 // ԤԼ����
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
    LabReservationList labReservations;
    int labReservationCount; // ʵ����ԤԼ����
} Lab, *LabPtr;              // ʵ���ҽṹ��

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
Status modifyReservation(ReservationInfoType infoType);
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
// ��ȡʵ������Ϣ
Status loadLabInfo();
// ����ʵ������Ϣ
Status saveLabInfo();
// ��ȡԤԼ��Ϣ
Status loadLabReservations();
// ����ԤԼ��Ϣ
Status saveLabReservations();

/* �������� */
// �ж�ʵ�����Ƿ��Ѵ���
Status isLabExist(Lab lab);
// ����ָ��ʵ���Ҳ�������ָ��
LabPtr findLab(char *location, char *number);

Status stringToDate(char *str, Date *date);
Status dateToString(Date date, char *str);
Status checkReservationConflict(LabReservation *labReservation1, LabReservation *labReservation2);

#endif // __LAB_H__