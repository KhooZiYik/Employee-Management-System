#pragma once
#include<iostream>
#include<stdlib.h> 
#include<string>
#include<fstream>
#define FILENAME "employeefile.txt"
using namespace std;

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

class WorkerManager{
	public:
		
		WorkerManager();
			
		void ShowMenu();
		
		void ExitSystem();
		
		void Add_Emp();
		
		void Save();
		
		int get_EmpNum();
		
		void init_Emp();
		
		void ShowEmp();
		
		void Del_Emp();
		
		int Emp_IsExist(int num);
		
		void Update_Emp();
		
		void Find_Emp();
		
		void SortEmp();
		
		void ClearFile();
			
		~WorkerManager();
		
		//variable
		int EmployeeNum;
			
		Worker ** EmployeeArray;
		
		bool FileisEmplty;
};

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//first case the file doesnot exist
	if(!ifs.is_open())
	{
		this->EmployeeNum = 0;
		this->EmployeeArray = NULL;
		this->FileisEmplty = true;
		ifs.close();
		return;
	}
	
	//case 2 file exist but no data
	char ch;
	ifs >> ch;
	if(ifs.eof())
	{
		this->EmployeeNum = 0;
		this->EmployeeArray = NULL;
		this->FileisEmplty = true;
		ifs.close();
		return;
	}
	
	//case 3 file exist contain data
	int num = this->get_EmpNum();
	this->EmployeeNum = num;
	
	this->EmployeeArray = new Worker * [this->EmployeeNum];
	this->init_Emp();
	ifs.close();
}

void WorkerManager::ShowMenu()
{
	cout << "****************************************************************************************" << endl;
	cout << "*****************		0. EXIT THE SYSEM				*********************************" << endl;
	cout << "*****************		1. ADD EMPLOYEE					*********************************" << endl;
	cout << "*****************		2. DISPLAY ALL INFORMATION		*********************************" << endl;
	cout << "*****************		3. DELETE EMPLOYEE				*********************************" << endl;
	cout << "*****************		4. UPDATE EMPLOYEE INFORMATION	*********************************" << endl;
	cout << "*****************		5. SEARCH FOR EMPLOYEE			*********************************" << endl;
	cout << "*****************		6. ARRANGE EMPLOYEE				*********************************" << endl;
	cout << "*****************		7. CLEAR ALL DATA				*********************************" << endl;
	cout << "****************************************************************************************" << endl;
}

void WorkerManager:: ExitSystem()
{
	cout << "THANK YOU DOR USING OUR SYSTEM" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "ENTER THE NUMBER OF EMPLOYEE: ";
	int addNum;
	cin >> addNum;
	
	if(addNum > 0)
	{
		//adding employee code
		int NewSize = this->EmployeeNum + addNum;
		
		Worker ** NewSpace = new Worker * [NewSize];
		
		if(this->EmployeeArray != NULL)
		{
			//create a array copy all the old data to new array
			for(int i = 0; i < this->EmployeeNum; i++)
			{
				NewSpace[i] = this->EmployeeArray[i];
			}
		}
		
		//adding new employee
		for(int i=0; i<addNum;i++)
		{
			int id,d_id;
			string name;
			
			cout <<"PLEASE ENTER NO " <<i+1<< "EMPLOYEE ID: ";
			cin >> id;
			fflush(stdin);
			cout <<"PLEASE ENTER NO " <<i+1<< "EMPLOYEE NAME: ";
			getline(cin, name);
			
			cout <<"PLEASE ENTER NO " <<i+1<< "EMPLOYEE DEPARTMENT (1 for employee 2 for manager 3 for boss): ";
			cin >> d_id;
			
			Worker * worker = NULL;
			switch(d_id)
			{
				case 1:
					//employee
					worker = new Employee(id, name, 1);
					break;
				case 2:
					//manager
					worker = new Manager(id, name, 2);
					break;
				case 3:
					//boss
					worker = new Boss(id, name, 3);
					break;
			}
			//save the worker pointer into the new array
			NewSpace [i + this->EmployeeNum] = worker;
			
		}
		delete [] this->EmployeeArray;
		this->EmployeeArray = NewSpace;
		this->EmployeeNum = NewSize;
		
		cout << "ADDED SUCCESSFULLY << endl";
		this->FileisEmplty = false;
		this->Save();
	}
	else{
		cout << "INVALID INPUT "<< endl;
	}
	
	system("pause");
	system("cls");
}

void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	
	for(int i = 0;i<this->EmployeeNum;i++)
	{
		ofs << this->EmployeeArray[i]->Id << " " << this->EmployeeArray[i]->Name << " " << this->EmployeeArray[i]->D_Id << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	int num = 0;
	int id, d_id;
	string name;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	while(ifs >> id && ifs >> name && ifs >> d_id)
	{
		num ++;
	}
	ifs.close();
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id,d_id;
	string name;
	
	int index = 0;
	while(ifs >> id && ifs >> name && ifs >>d_id)
	{
		Worker * worker = NULL;
		
		if(d_id == 1)//employee
		{
			worker = new Employee(id, name, d_id);
		}
		else if(d_id ==2)//manager
		{
			worker = new Manager(id, name, d_id);
		}
		else{//boss
			worker = new Boss(id, name, d_id);
		}
		this->EmployeeArray[index] = worker;
		index ++;
	}
	ifs.close();
}

void WorkerManager::ShowEmp(){
	if(this->FileisEmplty)
	{
		cout << "THE FILE IS EMPTY" << endl;
		system("pause");
		system("cls");
		return;
	}
	else{
		for(int i = 0; i < this->EmployeeNum;i++)
		{
			this->EmployeeArray[i]->DisplayInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp()
{
	if(this->FileisEmplty)
	{
		cout << "THE RECORD IS EMPTY" << endl;
	}
	else
	{
		cout <<"ENTER THE ID TO DELETE: " << endl;
		int id = 0;
		cin >> id;
		int index = this->Emp_IsExist(id);
		
		if(index != -1)
		{
			//delete
			for(int i = index; i<this->EmployeeNum-1;i++)
			{
				this->EmployeeArray[i] = this->EmployeeArray[i+1];
			}
			this->EmployeeNum--;
			//update data in file
			this->Save();
			cout << "DELETE SUCCESSFULLY" << endl;
		}
		else
		{
			cout <<"ID NOT EXIST" << endl;
		}
	}
	system("pause");
	system("cls");
}
		
int WorkerManager::Emp_IsExist(int num)
{
	int result = -1;
	
	for(int i = 0;i < this->EmployeeNum;i++)
	{
		if(this->EmployeeArray[i]->Id == num)
		{
			result = i;
			break;
		}
	}
	return result;
}

void WorkerManager::Update_Emp()
{
	if(this->FileisEmplty)
	{
		cout << "THE FILE IS EMPTY " << endl;
	}
	else
	{
		int id = 0;
		cout << "ENTER THE ID TO UPDATE: ";
		cin >> id;
		
		int index = this->Emp_IsExist(id);
		
		if(index !=-1 )
		{
			delete this->EmployeeArray[index];
			Worker * worker = NULL;
			int ID, D_ID;
			string NAME;
			
			cout << "ID " << id << "WAS FOUND\n" << endl;
			cout << "ENTER NEW ID: " ;
			cin >>ID;
			
			fflush(stdin);
			cout <<"ENTER NEW NAME: ";
			getline(cin, NAME);
			
			cout << "SELECT NEW DEPARTMENT (1. EMPLOYEE 2. MANAGER 3. BOSS): ";
			cin >>  D_ID;
			
			switch(D_ID)
			{
				case 1:
					worker = new Employee(ID, NAME, D_ID);
					break;
				case 2:
					worker = new Manager(ID, NAME, D_ID);
					break;
				case 3:
					worker = new Boss(ID, NAME, D_ID);
					break;
				default:
					cout << "INVALID INPUT" << endl;
			}
			this->EmployeeArray[index] = worker;
			
			this->Save();
			cout << "UPDATE SUCCESSFULLY " << endl;
		}
		else
		{
			cout << "ID NOT FOUND" << endl;
		}			
	}

	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if(this->FileisEmplty)
	{
		cout << "FILE IS EMPTY "<< endl;
	}
	else
	{
		int method = 0;
		cout << "PLEASE THE SEARCH METHOD (1. SEARCH BY ID 2. SEARCH BY NAME: ): ";
		cin >> method;
		
		if(method == 1)
		{
			//search by id
			int id = 0;
			cout << "PLEASE ENTER THE ID: ";
			cin >> id;
			
			int index = this->Emp_IsExist(id);
			if(index != -1)
			{
				cout << "THE EMPLOYEE INFO IS SHOWN BELOW: " << endl;
				this->EmployeeArray[index]->DisplayInfo();
			}
			else
			{
				cout << "THE ID NOT EXSIT" << endl;
			}
		}
		else if(method == 2)
		{
			//search by name
			string name;
			bool flag = false;
			fflush(stdin);
			cout << "ENTER THE NAME TO SEARCH: ";
			getline(cin, name);
			
			for(int i = 0;i<this->EmployeeNum;i++)
			{
				if(this->EmployeeArray[i]->Name == name)
				{
					cout << "THE RESULT IS SHOWN BELOW: "<< endl;
					this->EmployeeArray[i]->DisplayInfo();
					flag = true;
				}
			}
			if(flag == false)
			{
				cout << "RESULT NOT FOUND" << endl;
			}
		}
		else
		{
			cout << "INVALID INPUT" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::SortEmp()
{
	if(this->FileisEmplty)
	{
		cout << "THE FILE IS EMPTY" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		int sort = 0;
		cout << "1 FOR ACESDING SORT\n2 FOR DESCENDING SORT\nENTER YOUR CHOICE: ";
		cin >> sort;
		
		for(int i = 0 ;i<this->EmployeeNum;i++)
		{
			int minormax = i;
			for(int j = i+1;j<this->EmployeeNum;j++)
			{
				if(sort == 1)
				{
					if(this->EmployeeArray[i]->Id > this->EmployeeArray[j]->Id)
					{
						minormax = j;
					}
				}
				else
				{
					if(this->EmployeeArray[i]->Id < this->EmployeeArray[j]->Id)
					{
						minormax = j;
					}
				}	
			}
			if(i!=minormax)
			{
				Worker * temp = this->EmployeeArray[i];
				this->EmployeeArray[i] = this->EmployeeArray[minormax];
				this->EmployeeArray[minormax] = temp;
			}
		}
		cout << "ARRANGED SUCCESSFULLY" << endl;
		this->Save();
		this->ShowEmp();
	}
	system("pause");
	system("cls");
}

void WorkerManager:: ClearFile()
{
	if(this->FileisEmplty)
	{
		cout << "THE FILE IS EMPTY" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		int clear;
		cout << "ARE YOU SURE TO CLEAN ALL THE DATA? (1. YES 2. NO)";
		cin >> clear;
		
		if(clear == 1)
		{
			ofstream ofs(FILENAME, ios::trunc);
			ofs.close();
			
			if(this->EmployeeArray != NULL)
			{
				for(int i = 0;i<this->EmployeeNum;i++)
				{
					if(this->EmployeeArray[i]!=NULL)
					{
						delete this->EmployeeArray[i];
						this->EmployeeArray[i] = NULL;
					}
				}
				delete[] this->EmployeeArray;
				this->EmployeeArray = NULL;
				this->EmployeeNum =0;
				this->FileisEmplty = true;
			}
			cout << "ALL THE DATA IN THE FILE IS CLEAR"<< endl;
		}
		else if(clear == 2)
		{
			return;
		}
		else
		{
			cout << "INVALID INPUT "<< endl;
		}
		system("pause");
		system("cls");
	}
}

WorkerManager::~WorkerManager()
{
	if(this->EmployeeArray != NULL)
	{
		for(int i =0;i<this->EmployeeNum;i++)
		{
			if(this->EmployeeArray[i] != NULL)
			{
				delete this->EmployeeArray[i];				
			}
		}
		delete [] this->EmployeeArray;
		this->EmployeeArray =NULL;
		this->EmployeeNum = 0;
	}
}
