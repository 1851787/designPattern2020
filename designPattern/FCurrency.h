#pragma once
#include <string>
#include <iostream>
#include "BaseClasses.h"
using namespace std;

class FCurrency : public DPObject
{
public:
	virtual void exchange(float num) = 0;
};

class Dollar :public FCurrency
{
public:
	virtual void exchange(float num)
	{
		cout << "�һ���ɣ�" << num << " ��Ԫ�Ѷһ�Ϊ " << 6.576*num << " �����" << endl;
	}
};

class Pound :public FCurrency
{
public:
	virtual void exchange(float num)
	{
		cout << "�һ���ɣ�" << num << " Ӣ���Ѷһ�Ϊ " << 8.6685*num << " �����" << endl;
	}
};

class Yen :public FCurrency
{
public:
	virtual void exchange(float num)
	{
		cout << "�һ���ɣ�" << num << " ��Ԫ�Ѷһ�Ϊ " << 0.0635*num << " �����" << endl;
	}
};