#pragma once
#include<iostream>
#include<stdlib.h> 
#include<string>

using namespace std;

#include "worker.h"

class Manager: public Worker{
	public:
		Manager(int id, string name, int d_id);
		
		void DisplayInfo();
		
		string SetDep();
		
		~Manager();
};

Manager::Manager(int id, string name, int d_id)
{
	this->Id = id;
	this->Name = name;
	this->D_Id = d_id;
}

void Manager::DisplayInfo()
{
	cout << "ID: " << this->Id <<"\t" << "NAME: " << this->Name << "\t" << "DEPARTMENT: " << this->SetDep() << endl;
}

string Manager::SetDep()
{
	return string("MANAGER");
}

Manager::~Manager()
{
}
