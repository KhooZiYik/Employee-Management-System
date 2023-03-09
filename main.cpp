#include<iostream>
#include<stdlib.h> 
#include<string>

using namespace std;

#include "workermanager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main()
{
	
	WorkerManager wm;
	int choice;
	
	while(true){
		wm.ShowMenu();
		cout << "ENTER CHOICE: ";
		cin >>choice;
		
		switch(choice){
			case 0:
				//exit system function
				wm.ExitSystem();
				break;
			case 1:
				//add employee function
				wm.Add_Emp();
				break;
			case 2:
				//display all employee
				wm.ShowEmp();
				break;
			case 3:
				//delete function	
				wm.Del_Emp();
				break;
			case 4:
				//update function
				wm.Update_Emp();
				break;
			case 5:
				//search function
				wm.Find_Emp();
				break;
			case 6:
				//arrange function
				wm.SortEmp();
				break;
			case 7:
				wm.ClearFile();
				break;
			default:
				cout <<"INVALID INPUT "<< endl;
		}
	}
	
	return 0;
}

