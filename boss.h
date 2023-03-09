#pragma once
#include<iostream>
#include<stdlib.h> 
#include<string>

using namespace std;

#include "worker.h"

class Boss: public Worker{
	public:
		Boss(int id, string name, int d_id);
		
		void DisplayInfo();
		
		string SetDep();
		
		~Boss();
};

Boss::Boss(int id, string name, int d_id)
{
	this->Id = id;
	this->Name = name;
	this->D_Id = d_id;
}

void Boss::DisplayInfo()
{
	cout << "ID: " << this->Id <<"\t" << "NAME: " << this->Name << "\t" << "DEPARTMENT: " << this->SetDep() << endl;
}

string Boss::SetDep()
{
	return string("BOSS");
}

Boss::~Boss()
{
}
