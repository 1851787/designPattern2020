#include<iostream>
#include"BaseClasses.h"
#include<map>
#include<string>
using namespace std;
/**
 * �������Ԫ��
 * ������Ԫ�����
 */
class Flyweight : public DPObject
{
	/**
	 * ������Ԫ��Ĳ���
	 * @param i Flyweight���
	 * @return void
	 */
public:
	virtual void Operation(int i) = 0;
};

/**
 * ����Ĺ��������
 * ���干����Ԫ�����
 */
class ConcreteFlyWeight :public Flyweight
{
public:
	/**
	 * ���干������Ĳ���
	 * @param i Flyweight���
	 * @return void
	 */
	void Operation(int i)
	{
		std::cout << "�����FlyWeight:" << i << std::endl;
	}
};
/**
 * ����Ĳ����������
 * ���岻������Ԫ�����
 */
class UnsharedConcreteFlyweight :public Flyweight//�����������
{
	/**
	 * ���岻��������Ĳ���
	 * @param i Flyweight���
	 * @return void
	 */
	void Operation(int i)
	{
		std::cout << "�������FlyWeight:" << i << std::endl;
	}
};
/**
 * ��Ԫ������
 * ����������Flyweight����
 */
class FlyweightFactory//
{
private:
	map<string, Flyweight*>flyweights;//ģ�����б�
public:
	FlyweightFactory()//��ʼ����ģ���б�
	{
		//flyweights["W"] = new ConcreteFlyWeight();//������Ҫ�öѣ���Ϊ���Ǹ��ͻ����򷵻صģ�������öѣ���᷵�ؾֲ����������
		//flyweights["C"] = new ConcreteFlyWeight();
		//flyweights["P"] = new ConcreteFlyWeight();//���е�����Ϊ��P����ģ�鶼ֻ��Ӧ���һ��ʵ������������Ԫģʽ�ľ�������ѽ
	}
	/**
	 * ���岻��������Ĳ���
	 * @param key Flyweight����
	 * @return flyweights[key] ������Ԫ����
	 */
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
FlyweightFactory Fac;//��������ֵ����һ������
