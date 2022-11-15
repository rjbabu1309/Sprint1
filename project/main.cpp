#include <bits/stdc++.h>
#include "headers.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************* STRING OPERATIONS ********************************************/
int str_len(char c[])
{
	int length=0;
	while(c[length]!='\0')
	{
		length++;
	}
	return length;
}
string conv_to_str(char* a,int size)
{
	int i;
	string s = "";
	for(i=0;i<size;i++)
	{
		s = s + a[i];
	}
	return s;
}
int isSubstring(string s1, string s2) 
{ 
    int M = s1.length(); 
    int N = s2.length(); 
    for (int i = 0; i <= N - M; i++) { // A loop to slide pat[] one by one
        int j; 
        for (j = 0; j < M; j++) //For current index i, check for pattern match
            if (s2[i + j] != s1[j]) 
                break; 
        if (j == M) 
            return i; 
    } 
    return -1;
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************CAR CLASS FUNCTIONS****************************************************/
void Cars::getdata()
{
	cout<<"Enter name of car: ";
	scanf(" %[^\n]s",name);
	while(1)
	{
		cout<<"Enter ID of the car: ";
		cin>>ID;
		if(ID/10000 == 0 && ID/1000!=0)
			break;
		else
			cout<<"4 Digit please"<<endl;
	}
	while(1)
	{
		cout<<"Booked status(1 for yes/0 for no): ";
		cin>>booked;
		if(booked==1||booked==0)
			break;
		else
			cout<<"Enter (1 for yes/0 for no)"<<endl;
	}
}
void Cars::putdata()
{
	if(booked==1)
		cout<<"\t"<<"|"<<setw(20)<<name<<" |"<<setw(5)<<ID<<" |"<<setw(4)<<"Yes"<<" |"<<endl;
	else
		cout<<"\t"<<"|"<<setw(20)<<name<<" |"<<setw(5)<<ID<<" |"<<setw(4)<<"No"<<" |"<<endl;
}
void Cars::modify() //function to modify the records
{
	int ch;
	cout<<"Current details are"<<endl;
	putdata();
	cout<<"Modify:\n 1.Name\n 2.ID\n 3.Booking\n 4.All\n Your choie: ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			cout<<"Enter new name of the Car: ";
			cin>>name;
			break;
		case 2:
			cout<<"Enter new ID: ";
			cin>>ID;
			break;
		case 3:
			cout<<"Booking status?(1 for yes/0 for no): ";
			cin>>booked;
			break;
		case 4:
			getdata();
			break;
		default:
			cout<<"Wrong option selected, refer menu"<<endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************LOGIN ADMIN CODES****************************************************/
void Login_admin::login_admin(char user_n[], char pass[])
{
	string name;
	int ch = 0,round = 0;
	ifstream fin("admin_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No admin Data Available!"<<endl;
		fin.close();
		return;
	}
	else{
		while(fin>>username>>password)
		{
			if(strcmp(user_n,username)==0 && strcmp(pass,password)==0)
			{
				name = conv_to_str(user_n,str_len(user_n));
				size_t found = name.find("@cadmin.ac.in"); 
				cout<<"Hello "<<name.substr(0,found)<<endl;
				round = 1;
				do_work();
			}
			else if(strcmp(user_n,username)==0)
			{
				cout<<"Entered password is incorrect"<<endl;
				round = 1;
			}
		}
		fin.close();
		if(round==0)
		{
			cout<<"This User does not exist!"<<endl;
		}
	}
}
void Login_admin::Read_user_data()
{
	ifstream fin("login_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No User Data Available!"<<endl;
		fin.close();
		return;
	}
	while(fin>>username>>password)
	{
		cout<<"|"<<setw(20)<<username<<"|"<<setw(10)<<password<<"|"<<endl;
	}
	fin.close();
}

void Login_admin::add_car(string car_type){
	char ch='y';
	ofstream fout(car_type,ios::out|ios::app);
	while(ch=='y'|ch=='Y')
	{
		c.getdata();
		fout.write((char*)&c,sizeof(c));
		cout<<"\nDo you wish to add more(y/n): ";
		cin>>ch;
	}
	cout<<"\nData added to file\n"<<endl;
	fout.close();
}
void Login_admin::display_car(string car_type)
{
	ifstream fin(car_type,ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No Data Available!"<<endl;
		fin.close();
		return;
	}
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		c.putdata();
		cout<<endl; 
	}
	fin.close();
}
void Login_admin::search_car()
{
    vector<string> car_type_names={"HATCHBACK.txt","SEDAN.txt"};
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be searched: ";
	cin>>entered_id;
	for(auto type_name:car_type_names){
	    ifstream fin1(type_name,ios::in);
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			c.putdata();
			found = 'y';
		}
	}
	fin1.close();
	if(found =='y'){return;}
	}
	if(found =='n'){cout<<"\nCar of ID "<<entered_id<<" is not in the Records.\n";}
	return;
}
void Login_admin::modify_car() //fuction to modify the records of file
{
    
    vector<string> all_file_names={"HATCHBACK.txt","SEDAN.txt"};
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the Car ID to be modified: ";
	cin>>entered_id;
	
	for(auto file_name:all_file_names)
	{
	    fstream fio1(file_name,ios::in|ios::out);
	fio1.seekg(0);
	while(!fio1.eof())
	{
		int loc = fio1.tellg(); //storing the current location in loc
		fio1.read((char*)&c,sizeof(c));
		if(c.get_ID()==entered_id)
		{
			c.modify();
			found = 'y';
			fio1.seekg(loc); //moving the pointer to current location
			fio1.write((char*)&c,sizeof(c));
			cout<<"\nYour record of ID "<<entered_id<<" has been updated"<<endl;
			break;
		}
	}
	fio1.close();
	if(found =='y'){return;}
	}
	if(found =='n'){cout<<"\nCar of ID "<<entered_id<<"is not in the file.\n";}
	return;
}
void Login_admin::delete_c() //function to delete the records of file
{	
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be deleted: ";
	cin>>entered_id;
	ifstream fin1("HATCHBACK.txt",ios::in);
	ofstream fout1("temp1.txt",ios::out|ios::app);
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			found = 'y';
		}
		else{
			fout1.write((char*)&c,sizeof(c)); //writing to temp file
		}
	}
	fin1.close();
	fout1.close();
	remove("HATCHBACK.txt");
	rename("temp1.txt","HATCHBACK.txt");
	if(found=='y'){
		cout<<"Record successfully deleted"<<endl;
		return;
	}
	ifstream fin2("SEDAN.txt",ios::in);
	ofstream fout2("temp2.txt",ios::out|ios::app);
	while(fin2.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			found = 'y';
		}
		else{
			fout2.write((char*)&c,sizeof(c)); //writing to temp file
		}
	}	
	fin2.close();
	fout2.close();
	remove("SEDAN.txt");
	rename("temp2.txt","SEDAN.txt");
	if(found=='y'){
		cout<<"Record successfully deleted"<<endl;
		return;
	}
	else{
	    cout<<"Sorry,Car Id not found"<<endl;
	}
}
void Login_admin::do_work()
{
	int ch,op;
	int choose;
	do{
		cout<<"\nChoose option \n 1.Add Data \n 2.Display Data \n 3.Search Data \n 4.Modify Data \n 5.Delete Data\n 6.To see all the users\n 7.Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"Add Car Data\n";
				cout<<"Enter\n 1.Hatchback\n 2.Sedan\n Your choice: ";
				cin>>choose;
				switch(choose)
				{
					case 1:
						add_car("HATCHBACK.txt");
						break;
					case 2:
						add_car("SEDAN.txt");
						break;
					default:
						cout<<"Wrong option selected"<<endl;
				}
				break;
			case 2:
				choose = 0;
				cout<<"Display Record\n";
				cout<<"Enter\n 1.Hatchback\n 2.Sedan\n 3.All\n Your choice: ";
				cin>>choose;
				switch(choose)
				{
					case 1:
						display_car("HATCHBACK.txt");
						break;
					case 2:
						display_car("SEDAN.txt");
						break;
					case 3:
						display_car("HATCHBACK.txt");
						display_car("SEDAN.txt");
						break;
					default:
						cout<<"Wrong option selected"<<endl;
				}
				break;
			case 3:
				cout<<"Search Record\n";
				search_car();
				break;
			case 4:
				cout<<"Modify Record\n";
				modify_car();
				break;
			case 5:
				cout<<"Delete Record\n";
				delete_c();
				break;
			case 6:
				cout<<"User Data"<<endl;
				Read_user_data();
				break;
			case 7:
				break;
			default:
				cout<<"Wrong choice\n";
		}
	}while(ch!=7);
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************** LOGIN USER CODES **************************************************/
int Login_user::check_user_existence(char uname[] )
{
	int flag = 0;
	ifstream fin("login_data.txt",ios::in);
	while(fin>>username>>password)
	{
		if(strcmp(uname,username)==0){
			flag = 1;
		}
	}
	fin.close();
	if(flag==1)
	{
		return 1;
	}
	return 0;
}
void Login_user :: Register()
{
	char new_name[100];
	char pass[50];
	int val;
	ofstream fout("login_data.txt",ios::app);
	do{
		cout<<"Enter username(mail): ";
		cin>>new_name;
		//check username exists or not
		val = check_user_existence(new_name);
		if(val==1){cout<<"Username already exists use another one "<<endl;}
	}while(val==1);
	cout<<"Enter your preferred password: ";
	cin>>pass;
	fout<<new_name<<" "<<pass<<endl;
	fout.close();
}
int Login_user :: show(string car_type)
{
	ifstream fin(car_type,ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No Data Available!"<<endl;
		fin.close();
		return 1;
	}
	cout<<"\tFORMAT"<<endl;
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |"<<endl;
	cout<<"\n\tAvailable cars are\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0){
			c.putdata();
		}
	}
	fin.close();
	fin.open(car_type,ios::in);
	cout<<"\n\tUnvailable cars are\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==1){
			c.putdata();
		}
	}
	fin.close();
	return 0;
}
void Login_user :: book(string car_type)
{
	int car_to_book;
	char* car_name;
	int check=0;
	do{
		cout<<"Enter the ID of car to book: ";
		cin>>car_to_book;
	fstream fio(car_type,ios::in|ios::out);
	//check valid id
	fio.seekg(0);
	while(!fio.eof())
	{
		int loc = fio.tellg(); 
		fio.read((char*)&c,sizeof(c));
		if(c.get_ID() == car_to_book && c.booked_status() == 0){
		    check=1;
		    car_name=c.get_name();
			c.bookit();
			fio.seekg(loc);
			fio.write((char*)&c,sizeof(c));
			bill(car_to_book,car_name,car_type);
			break;
		}
		else if(c.get_ID() == car_to_book && c.booked_status() == 1)
		{
			 throw(Exception("Sorry its Already booked"));
		}
	}
	fio.close();
	if(check == 0){
			cout<<"ID is wrong :( refer menu"<<endl;
		}
	}while(check==0);
}
void Login_user::unbook()
{
    vector<string> all_file_names={"HATCHBACK.txt","SEDAN.txt"};
	char* name_of_car;
	int id_car;
	do{
	cout<<"Enter the ID of car you want to submit: ";
	cin>>id_car;
	if(id_car/10000!=0 && id_car/1000==0){
	    cout<<"ID is of 4 digit please check your bill"<<endl;}
	}while(id_car/10000!=0 && id_car/1000==0);
	char found = 'n';
	for(auto file_name:all_file_names){
	fstream fio1(file_name,ios::in|ios::out);
	fio1.seekg(0);
	while(!fio1.eof())
	{
		int loc = fio1.tellg(); 
		fio1.read((char*)&c,sizeof(c));
		if(c.get_ID() == id_car && c.booked_status()==0){
			name_of_car = c.get_name();
			cout<<"This ID is of "<<name_of_car<<"\nPlease enter the correct ID of Your car"<<endl;
			found = 'j';
		}
		else if(c.get_ID() == id_car && c.booked_status()==1){
			c.unbookit();
			found = 'y';
			name_of_car = c.get_name();
			fio1.seekg(loc);
			fio1.write((char*)&c,sizeof(c));
		}
	}
	fio1.close();
	if(found == 'j'){return;}
	if(found == 'y'){
		cout<<"Hope You liked Our Car - "<<name_of_car<<" :)"<<endl;
		cout<<"Thank You for using our services!!"<<endl;
		return;
	}
	}
	throw(Exception("OOPS! The Car you are submitting does not belong to us!!"));
}
void Login_user::bill(int carid,char* car_name,string car_type)  //(float rate,int carid,char* name_of_car)
{
	int see_car,rate;
	string namethecar;
	int choice,n,bill_id;
	float pay,min_pay,penalty_rate;
	if(car_type=="HATCHBACK.txt")
	    rate=50;
	else if(car_type=="SEDAN.txt")
	    rate=75;
	namethecar=car_name;
	cout<<"Thank You for Booking! Please enter following info"<<endl;
	cout<<"Enter Time for which you want the car for rent"<<endl;
    cout<<" (1)Less than a day\n (2)Min 1 whole day\n Your choice: ";
    cin>>choice;
    int random=rand();
    bill_id=random/100000;
	switch(choice)
	{
		case 1:
			cout<<"Enter number of hours for which u want to get car on rent: ";
            cin>>n;
			pay = n * rate;
			min_pay = 0.3 * pay;
			penalty_rate = 0.1 * rate + rate;
			cout<<endl;
			cout<<"************************ BILL ********************************"<<endl;
			cout<<"|"<<setw(30)<<"Invoice Number"<<"|"<<setw(30)<<bill_id<<endl;
			cout<<"|"<<setw(30)<<"Customer Name"<<"|"<<setw(30)<<username<<endl;
			cout<<"|"<<setw(30)<<"Car Name"<<"|"<<setw(30)<<namethecar<<endl;
			cout<<"|"<<setw(30)<<"Car ID"<<"|"<<setw(30)<<carid<<endl;
			cout<<"|"<<setw(30)<<"Numbers of Hours"<<"|"<<setw(30)<<n<<endl;
			cout<<"|"<<setw(30)<<"Total Pay"<<"|"<<setw(30)<<pay<<endl;
			cout<<"|"<<setw(30)<<"Advance Pay "<<"|"<<setw(30)<<min_pay<<endl;
			cout<<"|"<<setw(30)<<"After use Pay"<<"|"<<setw(30)<<pay-min_pay<<endl;
			cout<<"|"<<setw(30)<<"Penalty per hour"<<"|"<<setw(30)<<penalty_rate<<endl;
			cout<<"***************************************************************"<<endl;
			break;
		case 2:
				cout<<"Enter number of days for which u want to get car on rent: ";
           		cin>>n;
			pay = n * rate * 18; //18 = hours driven per day
			min_pay = 0.3 * pay;
			penalty_rate = 0.1 * rate + rate;
			cout<<endl;
			cout<<"************************** BILL ******************************"<<endl;
			cout<<"|"<<setw(30)<<"Invoice Number"<<"|"<<setw(30)<<bill_id<<endl;
			cout<<"|"<<setw(30)<<"Customer Name"<<"|"<<setw(30)<<username<<endl;
			cout<<"|"<<setw(30)<<"Car Name"<<"|"<<setw(30)<<namethecar<<endl;
			cout<<"|"<<setw(30)<<"Car ID"<<"|"<<setw(30)<<carid<<endl;
			cout<<"|"<<setw(30)<<"Numbers of Days"<<"|"<<setw(30)<<n<<endl;
			cout<<"|"<<setw(30)<<"Total Pay"<<"|"<<setw(30)<<pay<<endl;
			cout<<"|"<<setw(30)<<"Advance Pay "<<"|"<<setw(30)<<min_pay<<endl;
			cout<<"|"<<setw(30)<<"After use Pay"<<"|"<<setw(30)<<pay-min_pay<<endl;
			cout<<"|"<<setw(30)<<"Penalty per hour"<<"|"<<setw(30)<<penalty_rate<<endl;
			cout<<"**************************************************************"<<endl;
			break;
		default:
			cout<<"Wrong option selected"<<endl;
	}
}

void Login_user::display(string car_type)
{
	ifstream fin(car_type,ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No Data Available!"<<endl;
		fin.close();
		return;
	}
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		c.putdata();
		cout<<endl; 
	}
	fin.close();
}
void Login_user :: do_user_work()
{
	int choice;
	cout<<"Menu\n 1.Book a car\n 2.Submit the car\n 3.Display Data \nYour choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			int ch;
			int collect;
			cout<<setw(30)<<"QUICK INFO"<<endl;
			cout<<"|"<<setw(10)<<"TYPE"<<" |"<<setw(15)<<"RATE(per hr)"<<" |"<<setw(20)<<"PENALTY RATE(per hr)"<<" |"<<endl;
			cout<<"|"<<setw(10)<<"HATCHBACK"<<" |"<<setw(15)<<50<<" |"<<setw(20)<<50*(0.1) + 50<<" |"<<endl;
			cout<<"|"<<setw(10)<<"SEDAN"<<" |"<<setw(15)<<75<<" |"<<setw(20)<<75*(0.1) + 75<<" |"<<endl;

			cout<<"\nBooking Point\n 1.Hatchback\n 2.Sedan\n Your Choice: ";
			cin>>ch;
			switch(ch)
			{
				case 1:
					collect = show("HATCHBACK.txt");
					if(collect == 0)
						book("HATCHBACK.txt");	
					break;
				case 2:
					collect = show("SEDAN.txt");
					if(collect == 0)
						book("SEDAN.txt");
					break;
				default:
					cout<<"Seems You selected wrong option"<<endl;
			}
			break;
		case 2:
			unbook();
			break;
		case 3:
		    int select;
		    cout<<"1.HATCHBACK \n2.SEDAN \n3.All \nEnter Your Choice: "<<endl;
		    cin>>select;
		    switch(select)
		    {
		        case 1:
		            display("HATCHBACK.txt");
		            break;
		        case 2:
		            display("SEDAN.txt");
		            break;
		        case 3:
		            display("HATCHBACK.txt");
		            display("SEDAN.txt");
		            break;
		        default:
					cout<<"Seems You selected wrong option"<<endl;
		    }
	}
	
}
void Login_user :: login(char user_n[], char pass[])
{
	string name;
	int round = 0;
	ifstream fin("login_data.txt",ios::in);
	while(fin>>username>>password)
	{
		if(strcmp(user_n,this->username)==0 && strcmp(pass,this->password)==0)
		{
			name = conv_to_str(user_n,str_len(user_n));
			size_t found = name.find("@");
			cout<<"Welcome back "<<name.substr(0,found)<<endl;
			round = 1;
			do_user_work();
		}
		else if(strcmp(user_n,this->username)==0)
		{
			cout<<"Entered Password is incorret"<<endl;
			round =1;
		}
	}
	fin.close();
	if(round == 0)
	{
		char ans;
		cout<<"You might want to consider registering(y/n): ";
			cin>>ans;
			if(ans=='y'||ans=='Y'){
				this->Register();
			}
			else{
				cout<<"Allright see ya!"<<endl;
			}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
/******************************** MAIN PROGRAM ***********************************************/
int main()
{
	Login_user l;
	Login_admin la;
	char username[100],password[50];
	int choosing;
	string user;
	string line;
	try{
	do{
		cout<<"\n\t\t\tEnter:\n \t\t\t[1]Login\n \t\t\t[2]User Registeration\n \t\t\t[3]Exit Program\n \t\t\tYour Choice: ";
		cin>>choosing;
		switch(choosing)
	{
		case 1: //login function will seperate the user and admin.
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"\t\t\tLogin"<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"\n\tUsername - ";
			cin>>username;
			cout<<"\tPassword - ";
			cin>>password;
			user = conv_to_str(username,str_len(username));
			if(isSubstring("@cadmin.ac.in",user)!=-1)
			{
				la.login_admin(username,password);
				choosing = 3;
			}
			else{
				l.login(username,password);
				choosing = 3;
			}
			break;
		case 2: //user registeration
			l.Register();
			cout<<"Thank You For Registering, We won't let you down!"<<endl;
			break;
		case 3:
			break;
		default:
			cout<<"Wrong option selected please refer menu"<<endl;
	    }
	}while(choosing!=3);
	}
	catch(Exception& e){
	    cout<<e.getMessage() ;
	}
	return 0;
}
