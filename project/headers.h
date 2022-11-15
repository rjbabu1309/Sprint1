#include <bits/stdc++.h>
#define max_car_name 30
#define max_username_len 100
#define max_password_len 50
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************* CLASSES ******************************************************/
class Exception {

public:
   Exception(const string& msg) : msg_(msg) {}
  ~Exception() {}

   string getMessage() const {return(msg_);}
private:
   string msg_;
};

class Cars
{
	protected:
		char name[max_car_name];
		int ID;  //format 4 digit
		int booked; // 1 or 0
	public:
		void getdata();
		void putdata();
		void modify();
		int booked_status(){
			return booked;
		}
		int get_ID(){
			return ID;
		}
		char* get_name(){
			return name;
		}
		void bookit(){
			this->booked = 1;
		}
		void unbookit(){
			this->booked = 0;			
		}
		~Cars(){}
}c;
class Login{
	protected:
		char username[max_username_len];
		char password[max_password_len];
};
class Login_user:public Login{
	public:
		void Register();
		int check_user_existence(char[]);
		void login(char user_n[], char pass[]);
		//display available cars
		int show(string);
		//book the available cars
		void book(string);
		//invoices
		void bill(int,char*,string);   //void bill(float,int,char*);
		//do work function
		void do_user_work();
		void unbook();
		//display versions
		void display(string);
		~Login_user(){}
};
class Login_admin:public Login{
	public:
		void login_admin(char user_n[],char pass[]);
		void Read_user_data();
		//this is file class in original code
		void search_car();
		void delete_c();
		void modify_car();
		void add_car(string car_type);
		//display versions
		void display_car(string car_type);
		//do work function
		void do_work();
		~Login_admin(){cout<<"Thanks for using :) , Have a Nice Day!\n\n";}
};
