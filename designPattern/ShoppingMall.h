#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <sstream>
#include "BaseClasses.h"
#include "TravelPlan.h"
#include "CIcecream.h"

struct Shopping : public DPObject {
public:
	Path* path;
	Description* description;
	Spot* spot;
	~Shopping() {
		if (path != nullptr) { delete path; }
		if (description != nullptr) { delete description; }
	}

};

//相应的买/租物品的价格

struct Price : public DPObject
{
	constexpr int static juicePrice = 10;//果汁的价格
	constexpr int static yogertPrice = 8;//酸奶的价格
	constexpr int static CandiesPrice = 2;//糖果的价格
	constexpr int static equipmentRentingPrice = 100;//租赁一套装备的价格
}Price;

/***************************************************************/
/***************买物品Factory and Abstruct Factory **************/
/***************************************************************/

class Abstract_goods : public DPObject
{
public:
	int price;//物品的价格
	virtual ~Abstract_goods() {};//析构
	virtual void typePrice() = 0;//显示相应的物品价格
	virtual std::string type() const = 0;//商品信息
};


//具体的商品类型类
class Juice : public Abstract_goods
{
public:
	int price = Price.juicePrice;
	void typePrice() override
	{
		std::cout << "The price is" << price << "RMB.";
		return;
	}

	std::string type() const override
	{
		std::string coutpart1 = "Juice ,and you should pay ";
		std::string value = std::to_string(price);
		std::string coutpart2 = " yuan ,thanks.";

		return coutpart1 + value + coutpart2;
	}

};

class Candies : public Abstract_goods
{
	int price = Price.CandiesPrice;
	void typePrice() override
	{
		std::cout << "The price is" << price << "RMB.";
		return;
	}

	std::string type() const override
	{
		std::string coutpart1 = "Candies,and you should pay ";
		std::string value = std::to_string(price);
		std::string coutpart2 = " yuan ,thanks.";

		return coutpart1 + value + coutpart2;
	}
};

class Yogert :public Abstract_goods
{
	int price = Price.yogertPrice;
	void typePrice() override
	{
		std::cout << "The price is" << price << "RMB.";
		return;
	}

	std::string type() const override
	{
		std::string coutpart1 = "Yogert ,and you should pay ";
		std::string value = std::to_string(price);
		std::string coutpart2 = " yuan ,thanks.";

		return coutpart1 + value + coutpart2;
	}
};


/********************抽象的口味类型类*****************/
class Abstract_flavor : public DPObject
{

public:
	virtual ~Abstract_flavor() {};
	virtual std::string selectflavor() const = 0;
	virtual std::string describeGoods(const Abstract_goods &goodsType) const = 0;
};

/**********************具体的口味类型类******************/
class Apple : public Abstract_flavor
{
public:
	std::string selectflavor() const override
	{
		return "The customer choose an apple one.";
	}
	std::string describeGoods(const Abstract_goods &goodsType) const override
	{
		const std::string result = goodsType.type();
		return "Here is your apple " + result + " ";
	}
};

class Orange : public Abstract_flavor
{
public:
	std::string selectflavor() const override
	{
		return "The customer choose an Orange one.";
	}

	std::string describeGoods(const Abstract_goods &goodsType) const override
	{
		const std::string result = goodsType.type();
		return "Here is your orange  " + result + " ";
	}
};


/*************************抽象实例****************************/
class Get_goods : public DPObject
{//抽象工厂 生产有两个属性的产品
public:
	Get_goods()
	{
		//Singleton
		_count++;
		if (_count > 1)
			std::exception();

	}
	virtual Abstract_goods *getGoodsType() const = 0;
	virtual Abstract_flavor *getGoodsflavor() const = 0;
	Get_goods(const Get_goods&) = delete;
	Get_goods& operator=(const Get_goods&) = delete;
private:
	static int _count;//for Singleton

};

int Get_goods::_count = 0;

/**************************6种实例***************************/
class  Get_apple_juice : public Get_goods
{
public:
	Abstract_goods *getGoodsType() const override
	{
		return new Juice();
	}
	Abstract_flavor *getGoodsflavor() const override
	{
		return new Apple();
	}
};

class Get_apple_candies : public Get_goods
{
public:
	Abstract_goods *getGoodsType() const override
	{

		return  new Candies();
	}
	Abstract_flavor *getGoodsflavor() const override
	{
		return new Apple();
	}
};

class Get_apple_yogert : public Get_goods
{
public:
	Abstract_goods *getGoodsType() const override
	{
		return  new Yogert();
	}
	Abstract_flavor *getGoodsflavor() const override
	{
		return new Apple();
	}
};

class Get_orange_candies : public Get_goods
{
public:
	Abstract_goods *getGoodsType() const override
	{
		return  new Candies();
	}
	Abstract_flavor *getGoodsflavor() const override
	{
		return new Orange();
	}
};

class Get_orange_juice : public Get_goods
{
public:
	Abstract_goods *getGoodsType() const override
	{
		return  new Juice();
	}
	Abstract_flavor *getGoodsflavor() const override
	{
		return new Orange();
	}
};

class Get_orange_yogert : public Get_goods
{
public:
	Abstract_goods *getGoodsType() const override
	{
		return  new Yogert();
	}
	Abstract_flavor *getGoodsflavor() const override
	{
		return new Orange();
	}
};



/******************************************************************/
/*********************bridge 租用成套的东西*************************/
/******************************************************************/

class Abstruct_equipment : public DPObject//实现部分
{
public:
	virtual ~Abstruct_equipment() {}
	virtual std::string renting() const = 0;
};


class Sticks : public Abstruct_equipment
{
public:
	std::string renting() const override
	{
		return "The board and sticks is a pair.Please take away them together!\n";
	}
};


class Board : public Abstruct_equipment
{
public:
	std::string renting() const override
	{
		return "The board and the sticks is a pair.Please take away them together!\n";
	}
};


class Suit : public DPObject //抽象
{

protected:
	Abstruct_equipment* equipment_;

public:
	int price = Price.equipmentRentingPrice;
	Suit(Abstruct_equipment* equipment) : equipment_(equipment) {}

	virtual ~Suit() {}

	virtual std::string getTogether() const
	{
		return this->equipment_->renting() + "It costs 100 yuan.\n";
	}
};


class Extend_suit : public Suit //扩展
{
public:

	Extend_suit(Abstruct_equipment* equipment) : Suit(equipment) {}

	std::string getTogether() const override
	{
		return  this->equipment_->renting() + "It costs 100 yuan.\n";
	}

};

void Client_equipment(const Suit& suit)
{
	std::cout << suit.getTogether();
}




void Client_goods(const Get_goods &factory)
{
	const Abstract_goods *product_a = factory.getGoodsType();
	const Abstract_flavor *product_b = factory.getGoodsflavor();
	std::cout << product_b->selectflavor() << "\n";
	std::cout << product_b->describeGoods(*product_a) << "\n";
	delete product_a;
	delete product_b;
}

/*void CreatObj()
{
  Get_orange_juice*objOrangeJuice =new Get_orange_juice();
  Get_apple_juice *objAppleJuice =new Get_apple_juice();
  Get_orange_yogert*objOrangeYogert =new Get_orange_yogert();
  Get_apple_yogert*objAppleYogert=new Get_apple_yogert();
  Get_orange_candies*objOrangeCandies=new Get_orange_candies();
  Get_apple_candies*objAppleCandies=new Get_apple_candies();
}*/

/*void ClientOption
  (std::string op,std::string obj,
  const  Get_apple_juice &objAppleJuice,
  const  Get_orange_juice &objOrangeJuice,
  const  Get_apple_yogert &objAppleYogert,
  const  Get_orange_yogert &objOrangeYogert,
  const  Get_apple_candies &objAppleCandies,
  const  Get_orange_candies&objOrangeCandies)*/
void ClientOption(std::string op, std::string obj)
{
	if (op == "buy")
	{
		if (obj == "AppleJuice")
		{
			Get_apple_juice *objAppleJuice = new Get_apple_juice();
			std::cout << "Client:I'd like some apple juice.\n";
			Client_goods(*objAppleJuice);
			delete objAppleJuice;
		}
		else if (obj == "OrangeJuice")
		{
			Get_orange_juice*objOrangeJuice = new Get_orange_juice();
			std::cout << "Client:I'd like some orange juice.\n";
			Client_goods(*objOrangeJuice);
			delete objOrangeJuice;
		}
		else if (obj == "AppleYogert")
		{
			Get_apple_yogert*objAppleYogert = new Get_apple_yogert();
			std::cout << "Client:I'd like some apple yougert.\n";
			Client_goods(*objAppleYogert);
			delete objAppleYogert;
		}
		else if (obj == "OrangeYogert")
		{
			Get_orange_yogert*objOrangeYogert = new Get_orange_yogert();
			std::cout << "Client:I'd like some orange yogert.\n";
			Client_goods(*objOrangeYogert);
			delete objOrangeYogert;
		}
		else if (obj == "AppleCandies")
		{
			Get_apple_candies*objAppleCandies = new Get_apple_candies();
			std::cout << "Client:I'd like some apple candies.\n";
			Client_goods(*objAppleCandies);
			delete objAppleCandies;
		}
		else if (obj == "OrangeCandies")
		{
			Get_orange_candies*objOrangeCandies = new Get_orange_candies();
			std::cout << "Client:I'd like some orange candies.\n";
			Client_goods(*objOrangeCandies);
			delete objOrangeCandies;
		}

		else
		{
			std::cout << "Wrong Input,Please input again!" << std::endl;
		}
	}

	else if (op == "rent")
	{
		if (obj == "sticks")
		{
			Abstruct_equipment*equipment = new Sticks;
			Suit* suit = new Suit(equipment);
			Client_equipment(*suit);
			delete equipment;
			delete suit;
		}
		else if (obj == "board")
		{
			Abstruct_equipment* equipment = new Board;
			Suit *suit = new Extend_suit(equipment);
			Client_equipment(*suit);
			delete equipment;
			delete suit;
		}
		else
		{
			std::cout << "Wrong Input,Please input again!" << std::endl;
		}
	}


}

/************************************************************************
*							ShoppingMall模块							*
*************************************************************************/

class ShoppingManager : public MacroCommandReceiver
{

private:
	ShoppingManager() : MacroCommandReceiver("shop") {
		this->addReciver(&(IcecreamManager::getInstance()));
	}
	std::vector<Shopping*> ShoppingList;

protected:
	bool executeCommand(std::string cmd) {
		std::string subCmd = sliceCommand(cmd);
		removeBlank(cmd);

		if (subCmd == "buy")
		{
			if (cmd == "AppleJuice")
			{
				ClientOption("buy", "AppleJuice");
				std::cout << std::endl;
				return true;
			}
			if (cmd == "OrangeJuice")
			{
				ClientOption("buy", "OrangeJuice");
				std::cout << std::endl;
				return true;
			}
			if (cmd == "AppleYogert")
			{
				ClientOption("buy", "AppleYogert");
				std::cout << std::endl;
				return true;
			}
			if (cmd == "OrangeYogert")
			{
				ClientOption("buy", "OrangeYogert");
				std::cout << std::endl;
				return true;
			}
			if (cmd == "AppleCandies")
			{
				ClientOption("buy", "AppleCandies");
				std::cout << std::endl;
				return true;
			}
			if (cmd == "OrangeCandies")
			{
				ClientOption("buy", "OrangeCandies");
				std::cout << std::endl;
				return true;
			}
			return false;
		}
		if (subCmd == "rent")
		{
			if (cmd == "sticks")
			{
				ClientOption("rent", "sticks");
				return true;
			}
			if (cmd == "board")
			{
				ClientOption("rent", "board");
				return true;
			}
		}



		return false;
	}
public:
	ShoppingManager(const ShoppingManager&) = delete;
	ShoppingManager& operator=(const ShoppingManager&) = delete;

	static ShoppingManager& getInstance()
	{
		static ShoppingManager reciver;
		return reciver;
	}

	virtual void printHelp(int level)
	{
		MacroCommandReceiver::printHelp(level);
		level++;
		std::string head(level * 3, '-');
		std::cout << head + "buy" << std::endl;
		std::cout << head + "---" + "AppleJuice" << std::endl;
		std::cout << head + "---" + "AppleYogert" << std::endl;
		std::cout << head + "---" + "AppleCandies" << std::endl;
		std::cout << head + "---" + "OrangeJuice" << std::endl;
		std::cout << head + "---" + "OrangeYogert" << std::endl;
		std::cout << head + "---" + "OrangeCandies" << std::endl;
		std::cout << head + "rent" << std::endl;
		std::cout << head + "---" + "sticks" << std::endl;
		std::cout << head + "---" + "board" << std::endl;
	}
	~ShoppingManager()
	{
		for (int i = 0; i < ShoppingList.size(); i++)
		{
			if (ShoppingList[i] != nullptr)
			{
				delete ShoppingList[i];
			}

		}
	}
};