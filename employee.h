#pragma once
#include<iostream>
#include<stdlib.h> 
#include<string>

using namespace std;

#include "worker.h"

class Employee: public Worker{
	public:
		Employee(int id, string name, int d_id);
		
		void DisplayInfo();
		
		string SetDep();
		
		~Employee();
};

Employee::Employee(int id, string name, int d_id)
{
	this->Id = id;
	this->Name = name;
	this->D_Id = d_id;
}

void Employee::DisplayInfo()
{
	cout << "ID: " << this->Id <<"\t" << "NAME: " << this->Name << "\t" << "DEPARTMENT: " << this->SetDep() << endl;
}

string Employee::SetDep()
{
	return string("EMPLOYEE");
}

Employee::~Employee()
{
}
