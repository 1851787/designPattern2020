#pragma once
#include "FCurrency.h"

class Adapter : public DPObject
{
public:

	Adapter()
	{
		dollar = new Dollar;
		pound = new Pound;
		yen = new Yen;
	}
	~Adapter()
	{
		delete dollar;
		delete pound;
		delete yen;
	}
public:
	void exchange(string type, float num) {
		if (type == "dollar" || type == "��Ԫ")
		{
			dollar->exchange(num);
		}
		else if (type == "pound" || type == "Ӣ��")
		{
			pound->exchange(num);
		}
		else if (type == "yen" || type == "��Ԫ")
		{
			yen->exchange(num);
		}
	}
	void start() {
		string type;	//�������
		float num;		//�������
		while (cin >> type) {
			if (type == "quit") {
				getline(cin, type);
				break;
			}
			cin >> num;
			exchange(type, num);
		}
	}

private:
	FCurrency *dollar;
	FCurrency *pound;
	FCurrency *yen;
};