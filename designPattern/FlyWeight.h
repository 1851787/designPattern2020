#pragma once
#include<iostream>
#include"BaseClasses.h"
#include<map>
#include<string>
using namespace std;

class Flyweight : public DPObject//�������Ԫ��
{
public:
	virtual void Operation(int i) = 0;
};
class ConcreteFlyWeight :public Flyweight//���������
{
public:
	void Operation(int i)
	{
		std::cout << "�����FlyWeight:" << i << std::endl;
	}
};
class UnsharedConcreteFlyweight :public Flyweight//�����������
{
	void Operation(int i)
	{
		std::cout << "�������FlyWeight:" << i << std::endl;
	}
};
class FlyweightFactory : public DPObject//��Ԫ����
{
private:
	map<string, Flyweight*>flyweights;//ģ�����б�
public:
	FlyweightFactory()//��ʼ����ģ���б�
	{
		flyweights["W"] = new ConcreteFlyWeight();//������Ҫ�öѣ���Ϊ���Ǹ��ͻ����򷵻صģ�������öѣ���᷵�ؾֲ����������
		flyweights["C"] = new ConcreteFlyWeight();
		flyweights["P"] = new ConcreteFlyWeight();//���е�����Ϊ��P����ģ�鶼ֻ��Ӧ���һ��ʵ������������Ԫģʽ�ľ�������ѽ
	}

	Flyweight* GetFlyWeight(string key)//����������Ԫ���󣬶���Щ��������Զ������һ���ù�����ģ�����б���
	{
		if (!flyweights.count(key))//�ȼ�����Ƿ����б��У�����������½����б���
		{
			flyweights[key] = new ConcreteFlyWeight();//����ֻ�ܷ��ضѿռ�
		}
		return flyweights[key];
	}
	map<string, Flyweight*>::size_type countN()//���ص�ǰ�ж��ٸ��ɹ������ģ��
	{
		return flyweights.size();
	}
};
