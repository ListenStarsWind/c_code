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
#include"SeqList.h"

#define STDIN(Prompt,Ptr,Format) printf(Prompt"\n");         \
		if(scanf(Format,Ptr) != 1)                           \
		{                                                    \
			printf("发生输入错误！请向管理员反馈该问题。\n");   \
		}


Contact generateContactList(void)
{
	Contact t;
	STDIN("请输入你的名字：", t.name, "%s");
	STDIN("请输入你的性别：", t.sex, "%s");
	STDIN("你的出生年份是？", &(t.brith.year), "%d");
	STDIN("你的出生月份是？", &(t.brith.month), "%d");
	STDIN("你的出生日期是？", &(t.brith.day), "%d");
	STDIN("请输入你的QQ号：", t.QQ_number, "%s");
	STDIN("请输入你的电话号码:", t.phone, "%s");
	return t;
}

void initializeContacts(Contacts* ContactsPtr)
{
	SeqListInit(ContactsPtr);
}

void destroyContacts(Contacts* ContactsPtr)
{
	SeqListDestroy(ContactsPtr);
}

void insertAtPosition(Contacts* ContactsPtr, int Position, Contact x)
{
	SeqListInsertAtPosition(ContactsPtr, Position, x);
}

void deleteAtPosition(Contacts* ContactsPtr, int Position)
{
	SeqListDeleteAtPosition(ContactsPtr, Position);
}

void insertAtBeginning(Contacts* ContactsPtr, Contact x)
{
	SeqListInsertAtBeginning(ContactsPtr, x);
}

void insertAtEnd(Contacts* ContactsPtr, Contact x)
{
	SeqListInsertAtEnd(ContactsPtr, x);
}

void deleteFromBeginning(Contacts* ContactsPtr)
{
	SeqListDeleteAtBeginning(ContactsPtr);
}

void deleteFromEnd(Contacts* ContactsPtr)
{
	SeqListDeleteAtEnd(ContactsPtr);
}

//注意：字节数和字符数不是同一概念。字节数是字符串在内存中实际占用的存储空间；而字符数是字符串中字符的数量，不包括结尾的空字符 '\0'。
//对于一个汉字来说，不同的编码模式下，单个汉字所占的字节数是不同的；在UTF-8模式下，一个汉字占三个字节，所以对于"能放六个汉字"这个
//字符串来说，其字节数是3*6==18，在加上末尾的'\0'。一共19字节大小；而若要用strlen计算该字符串的长度时，则会显示12,即把单个汉字
//当做两个字符来看。

//以姓名方式查找
//Search by Name
static void searchByName(Contacts* ContactsPtr, int* x)
{
	char key[NAME_MAX] = { 0 };
	STDIN("请输入你要查找的名字，注意，最多六个汉字。", key, "%s");
	int i = 0;
	for (i = 0; i < ContactsPtr->datacount; i++)
	{
		if (strstr(ContactsPtr->ptr[i].name, key) != NULL)
		{
			*x = i;
			break;
		}
	}
}

//以QQ号方式查找
//Search by QQ Number
static void searchByQQNumber(Contacts* ContactsPtr, int* x)
{
	char key[QQ_NUMBER_MAX] = { 0 };
	STDIN("请输入你要查找的QQ号:", key, "%s");
	int i = 0;
	for (i = 0; i < ContactsPtr->datacount; i++)
	{
		if (strstr(ContactsPtr->ptr[i].QQ_number, key) != NULL)
		{
			*x = i;
			break;
		}
	}
}

//以电话号码方式查找
//Search by Phone Number
static void searchByPhoneNumber(Contacts* ContactsPtr, int* x)
{
	char key[PHONE_MAX] = { 0 };
	STDIN("请输入你要查找的电话号码:", key, "%s");
	int i = 0;
	for (i = 0; i < ContactsPtr->datacount; i++)
	{
		if (strstr(ContactsPtr->ptr[i].phone, key) != NULL)
		{
			*x = i;
			break;
		}
	}
}

#define CASE(number,statement) case number: statement; break

//通讯录的查找
//Search in the contacts
int searchContacts(Contacts* ContactsPtr)
{
	assert(ContactsPtr);
	int i = 0;
	STDIN("本程序支持三种查找方式：1.姓名 2.QQ号 3.电话号码  请选择你想查找的方式，输入序列号即可：", &i, "%d");
	while (i != 1 && i != 2 && i != 3)
	{
		printf("你的输入有误，请重新输入\n");
		if (scanf("%d", &i) != 1)
		{
			printf("发生输入错误！请向管理员反馈该问题。\n");
		}
	}
	int j = -1;
	switch (i)
	{
		CASE(1, searchByName(ContactsPtr, &j));
		CASE(2, searchByQQNumber(ContactsPtr, &j));
		CASE(3, searchByPhoneNumber(ContactsPtr, &j));
	}
	return j;
}

#undef CASE

int PrintfAge(const Period* brith)
{
	//用来存储当前日期
	Period current;
	//time_t 用于描述系统时自1970年1月1日00:00:00 UTC以来的秒数
	time_t t = time(NULL);
	//struct tm 是一个结构体，用于表示时间和日期的各个组成部分，如年、月、日、小时、分钟、秒等
	//函数localtime参数是time_t*,返回指向struct tm的指针，所以要解引用
	struct tm tm = *localtime(&t);
	//tm.tm_year：表示自1900年以来的年份。例如，如果当前年份是2024年，tm.tm_year 的值将是124。因此，需要加上1900来得到当前的实际年份。
	current.year = tm.tm_year + 1900;
	//tm.tm_mon：表示月份，从0到11（0表示1月，11表示12月）。因此，需要加1来得到实际的月份。
	current.month = tm.tm_mon + 1;
	//tm.tm_mday：表示当前月份中的日期，从1开始，至于为什么不从0开始，可能是一种历史遗留问题亦或者和tm.tm_mon相区分
	current.day = tm.tm_mday;
	int ret = 0;
	ret = current.year - brith->year;
	if (current.month < brith->month || (current.month == brith->month && current.day < brith->day))
	{
		ret--;
	}
	return ret;
}

//单个通讯录的展示
//Display the contact
void displayContact(Contacts* ContactsPtr, int i)
{
	assert(ContactsPtr);
	printf("姓名 性别 年龄 QQ号 电话号码\n");
	printf("%s %s %d %s %s\n", ContactsPtr->ptr[i].name, ContactsPtr->ptr[i].sex, PrintfAge(&(ContactsPtr->ptr[i].brith)), ContactsPtr->ptr[i].QQ_number, ContactsPtr->ptr[i].phone);
}

//通讯录的展示
//Display the contacts
void displayContacts(Contacts* ContactsPtr)
{
	assert(ContactsPtr);
	printf("姓名 性别 年龄 QQ号 电话号码\n");
	int i = 0;
	for (i = 0; i < ContactsPtr->datacount; i++)
	{
		printf("%s %s %d %s %s\n", ContactsPtr->ptr[i].name, ContactsPtr->ptr[i].sex, PrintfAge(&(ContactsPtr->ptr[i].brith)), ContactsPtr->ptr[i].QQ_number, ContactsPtr->ptr[i].phone);
	}
}