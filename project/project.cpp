// project.cpp The Parking lot Management System
//

//#include "stdafx.h"
//#include "Kesong_RFID_PORT.h"
//#pragma comment(lib, "Kesong_RFID_PORT.lib")
#include "stdlib.h"
#include "stdio.h"
#include "string"
#include "time.h"  
#include "iostream"
#define ZERO "00000000000000000000000000000000"
using namespace std;

void welcome();
void menu();
void searcher_menu();
void over();
int close();
void check();
void reg();
void search();
void error();
void logout();
void back();
int bind(string p, string t);
char databuffer[1025];

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
 	//int read_2;
 	//int init = rfid_reader_init(0);
 	int init = 1;
 	//int num;
 	//printf("you can select the function 1-read 2-write 3-rewite\n");
 	//scanf("%d",num);
 		
 	if(init==1){
 		printf("***System Initialization Completed***\n");
		system("pause");
		welcome();
		menu();
		searcher_menu();
	 }
	else{
		printf("!!!System Initialization Failed!!!\n");
		return 0;
	}
		
	// switch(num){
	// case 1:
	//{
//	int read_1 = rfid_reader_readTag(0,databuffer,0,1,3);
//	if(read_1==1){
//		printf("***读取成功***\n");
//		printf("%s\n",databuffer);
//    }
//	else
//		printf("读取失败\n");
//	//}
//	// case 2:
//	//{
//	int write = rfid_reader_writeTag(0,DATA,0,1,3,"00000000");	
// 	if(write==1)
//		printf("***写入成功***\n");
// 	else
//		printf("!!!写入失败!!!\n");
//
//	//}
//	// case 3:
//	//{ 
//		read_2 = rfid_reader_readTag(0,databuffer,0,1,3);
//		if(read_2==1)
//		{
//			printf("在读一次--->");
//			printf("%s\n",databuffer);
//		}else
//			printf("读取失败");
// 	//}
//	//break;}
//	system ("pause");
//
//	return 0;
}

//Print Welcome Information
void welcome()
{
    printf("\n\n\n\n\n");
	printf("                   ********************************************\n");
	printf("                   ********************************************\n");
	printf("                   **                                        **\n");
    printf("                   **                Welcome!                **\n");
	printf("                   **                                        **\n");
	printf("                   **                                        **\n");
	printf("                   **      Parking Lot Management System     **\n");
	printf("                   **                                        **\n");
	printf("                   ********************************************\n");
	printf("                   ********************************************\n");
	system("pause");
}

//Print Welcome menu 
void menu()                         
{
	system("cls");
	printf("                       MAIN MENU                          \n");
	printf("-------------ENTER IN THE NUMBER YOU CHOOSE---------------\n");
	printf("----------------------------------------------------------\n");
    printf("               1-----Check Unloading Lot                  \n");
    printf("               2-----Register Cars                        \n");
    printf("               3-----Search Cars                          \n");
    printf("               4-----Logout Cars                         \n");
    printf("               0-----Exit                                 \n");

}

//Receive the input number 
void searcher_menu()
{
	int a;
	 
	printf("Please type in the number： ");
	scanf("%d",&a);
	if(a==1)
	{
		system("cls");
	    check();
	}
	else if(a==2)
	{
		system("cls");
		reg();
	} 
	else if(a==3)
	{
		system("cls");
		search();
	}
	else if(a==4)
	{
		system("cls");
		logout();
	}
	else if(a==0) 
	{
		close();
	}
	else
	{
		error();
	}
}

//Print Exit interface
void over()
{
    system("cls");
	printf("                   ********************************************\n");
	printf("                   ********************************************\n");
    printf("                   **                                        **\n");
	printf("                   **                 Goodbye!               **\n");
	printf("                   **                                        **\n");
	printf("                   **       Parking Lot Management System    **\n");
	printf("                   **                                        **\n");
	printf("                   ********************************************\n");
	printf("                   ********************************************\n");
	system("pause");
}

//Close the management system
int close(){
//	int a = rfid_reader_deinit(0);
	int a = 1;
	if(a == 1){
		printf("The RFID Reader was closed!");
		system("pause");
		over();
		return 0;
	}
	else{
		error();
		return 0;
	}
}

//Check if the space is avaiable or not
void check()
{
//	int read_1 = rfid_reader_readTag(0,databuffer,0,1,3);
	int read_1 = 1;
	if(read_1==1){
		printf("The space is occupied.\n");
		back();
    }
	else
		printf("The space is free.\n");
}

//Register the car into the system
void reg()
{
	string p;
	printf("Please enter in the plate number:");
	cin>>p;
	
	time_t timep;  
    time(&timep);  
    string t = ctime(&timep);
    
	int a = bind(p,t);
	if(a=1)
	{
		printf("Registration Completed!");
		back();
	}
	else
	{
		error();
	}
}

//Bind the car number to speicfic RFID card
int bind(string p, string t)
{
//	int a = rfid_reader_writeTag(0,p,0,2,3,"00000000");	
//	int b = rfid_reader_writeTag(0,t,2,4,3,"00000000");	
	int a = 1; int b = 1;
	if(a==b & a==1)
		return 1;
	else
		return 0;
}

//Search specific car with its number
void search()
{
	char p[1025];
	printf("Please enter in the plate number:");
	scanf("%s", &p);
	
//	int a = rfid_reader_readTag(0,databuffer,0,2,3);
	int a = 1;
	if(a==1){
//		for(int i=0; i<6; i++){
//			if(p[i] == databuffer[i])
//				continue;
//			else
//				printf("Please check other space.");
//				break;
//		}
		printf("The car with number %s is in space 0.", p);
		back();
	}
	else{
		error();
	}
}

//Print error information
void error(){
	printf("Error! Press any button back to main menu.");
	system("pause");
	menu();
	searcher_menu();
}

//Logout cars from the system
void logout(){
	char p[1025];
	printf("Please enter in the plate number:");
	scanf("%s", &p);
	
	time_t timep;  
    time(&timep);  
    string t = ctime(&timep);
    
//	int a = rfid_reader_readTag(0,databuffer,2,4,3);
	int a = 1;
	if(a == 1){
		printf("The car with number %s enter the parking lot at:\n", p);
		string t1 = ctime(&timep);
		cout<<t1<<endl;
//		printf("%s\n", databuffer);
		printf("And leave at:\n");
		cout<<t<<endl;
	}
	else{
		error();
	}
	
//	int b = rfid_reader_writeTag(0,ZERO,0,6,3,"00000000");
	int b = 1;
	if(b == 1){
		printf("Logout Finished!");
		back();
	}
	else{
		printf("Failed to logout!");
		error();
	}
}

void back(){
	printf("\n\nPress any button back to main menu.");
	system("pause");
	menu();
	searcher_menu();
}
