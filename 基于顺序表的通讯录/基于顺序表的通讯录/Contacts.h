#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  月日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：
 *******************************************************************************************/
#pragma once

#define NAME_MAX 20
#define SEX_MAX 10
#define QQ_NUMBER_MAX 15
#define PHONE_MAX 15

typedef struct Period
{
	int year;
	int month;
	int day;
}Period;

typedef struct Contact
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	Period brith;
	char QQ_number[QQ_NUMBER_MAX];
	char phone[PHONE_MAX];
}Contact;

//前置声明
//Forward declaration
struct SeqList;

typedef struct SeqList Contacts;

//通讯录生成
//Generation of the contact list
Contact generateContactList(void);


//通讯录的初始化
//Initialization of the contacts
void initializeContacts(Contacts* ContactsPtr);

//通讯录的销毁
//Destruction of the contacts
void destroyContacts(Contacts* ContactsPtr);

//通讯录的指定位置插入
//Insert at specified position in the contacts
void insertAtPosition(Contacts* ContactsPtr, int Position, Contact x);

//通讯录的指定位置删除
//Delete at specified position in the contacts
void deleteAtPosition(Contacts* ContactsPtr, int Position);

//通讯录的开头插入
//Insert at the beginning of the contacts
void insertAtBeginning(Contacts* ContactsPtr, Contact x);

//通讯录的尾部插入
//Insert at the end of the contacts
void insertAtEnd(Contacts* ContactsPtr, Contact x);

//通讯录的开头删除
//Delete from the beginning of the contacts
void deleteFromBeginning(Contacts* ContactsPtr);

//通讯录的尾部删除
//Delete from the end of the contacts
void deleteFromEnd(Contacts* ContactsPtr);

//通讯录的查找
//Search in the contacts
int searchContacts(Contacts* ContactsPtr);

//单个通讯录的展示
//Display the contact
void displayContact(Contacts* ContactsPtr, int i);

//通讯录的展示
//Display the contacts
void displayContacts(Contacts* ContactsPtr);