#pragma once
#include<iostream>
#include<stdlib.h> 
#include<string>

using namespace std;

class Worker{
	public:

		virtual void DisplayInfo() = 0;
		virtual string SetDep() = 0;
		
		int Id;
		string Name;
		int D_Id;
};
