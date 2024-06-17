//Leave Application System
//ANDREW ONG YONG KHANG
//SENG CHEE QUAN
//TEO JING AN
//SAMUEL FUNG WEN KAI

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <functional>

using namespace std;

const int TABLE_SIZE = 100;

struct Balrecord{
	
	int B_id,B_balance;
	string B_name;
	int eid,eduration;
	string ename,estart_day,eend_day,ereason;
	Balrecord* next;
};

struct Employee {
    int employee_id;
    string employee_name;
    string employee_pass;
    string employee_address;
    string employee_contact;
    Employee* next;
};

struct LeaveRecord {
    int eid;
    string B_name;
    string estart_day;
    string eend_day;
    int eduration;
    string ereason;
    LeaveRecord* next;
};

struct BalanceRecord {
    int B_id;
    string B_name;
    int B_balance;
    BalanceRecord* next;
};

struct LeaveRequest {
    int id;
    string name;
    string start_date;
    string end_date;
    int duration;
    string reason;
    string line;
    LeaveRequest* next;
};

//Employee Management-----register
class EmployeeList {
	
public:
    Employee* head;
    LeaveRecord *leaveHead;

    EmployeeList() {
        head = nullptr;
    }
	void e_usermanage();
    void sortById();
	LeaveRecord * binarySearchById(int id);
	void e_displayemp();
    void searchbyid();
	void sortEmployeesByID();
	void searchEmployeeByID(int id);
	void e_displaySubMenu();
	void e_displayOriginalEmpData();
	void e_displayleave();
    void sortbyduration();
    int findMaxDuration();
	
    void e_regis();

    void saveToFile() {
        ofstream fw_user("EMPLOYEE.txt",ios::app);
        Employee* temp = head;
		
        while (temp!= nullptr) {
            fw_user<<endl<< temp->employee_id << " " << temp->employee_pass << " " << temp->employee_name << " " << temp->employee_address << " " << temp->employee_contact << endl;
            temp = temp->next;
        }

        fw_user.close();
    }//end of savefile
    void e_del();
	};//END OF CLASS EMPLOYEE & edited implement linked list
class employee{
	private:
		int employee_id;
		string employee_name,employee_pass,employee_contact,employee_address;
	public:
		
		Employee* head;
    LeaveRecord *leaveHead;

    employee() {
        head = nullptr;
    }
		void emp_log();
		void emp_menu();
		void e_verify();
		void e_manage_menu();
		void e_usermanage();
		void e_display();
		void e_displayemp();
		void e_displayleave();
		void e_displayOverBalance();
		void ViewBalance(int id);
		
		friend class Applyleave;
		friend class Modifyleave;
};

class admin{

	private:
	int admin_id;
	string admin_name,admin_password;
	
	public:
		void admin_main();
		void admin_verify();
		void admin_menu();
		admin(){//default constructor
		
		admin_id=001;
		admin_name="LeaveApplicationSystem";
		admin_password="12345";
		
		ofstream fw_admin;
		fw_admin.open("ADMIN.txt");
		
		fw_admin<< admin_id<<"\t"<<admin_password<<"\t"<<admin_name<<endl;
		
		fw_admin.close();
		}
		~admin(){//destructor
	 	
	 	cout<<"\n\n\n\n\n\n\n\n"<<endl;
	 	cout<<"Admin: ANDREW ONG YONG KHANG 1211209054\n";
	 	cout<<"Admin: SENG CHEE QUAN 1211208130\n";
	 	cout<<"Admin: TEO JING AN 1211208694 \n";
	 	cout<<"Admin: SAMUEL FUNG WEN KAI 1211110578";
		 }
};

//apply
class Applyleave{
	private:
		char back;
		
	protected:
	int leave_start_mo,leave_end_mo,leave_end_day,leave_start_day,start_daysinmonth,end_daysinmonth;
	int duration;
	int optreason;
	string reason;
	
	public:
		void apply(int id);		
		bool isValidDate(int month, int day); 
		int getDaysInMonth(int month); 		
		int getDuration();
		string getReason(int optreason);	
		
		friend class employee;

};

class Modifyleave:protected Applyleave{
		private:
		char back;
		
		public:
		//delete
		void delfile(int id); 
		
		//search
		void search(); 
		
		//viewleave
		void viewleave(int id);
		
		//edit
		void editleave(int id);
};

class Approveleave:protected Applyleave{
	private:
		string line; char reenter,back;
		int id;
	public:
		void approve();
		void balance(int , int, string);
		
};
//global declaration
admin ad;
employee emp;
Applyleave Alea;
Modifyleave Mlea;
Approveleave appr;
Balrecord BR;
void EmployeeList::e_regis(){
        admin ad;
        char sure, reenter;
        int id, storedId;
        string line;

        system("CLS");
        
        
        ifstream testFile("EMPLOYEE.txt");
	if (!testFile.is_open()) {
    ofstream createFile("EMPLOYEE.txt");
    createFile.close();
	}
	testFile.close();
		cout << "\n\n\t\t===========  R E G I S T E R   N E W   E M P L O Y E E  ===========\n\n" << endl;
        cout << "\t\t  Enter new employee ID to check if the ID exists or not: ";
        cin >> id;
         
        
         ifstream fread("EMPLOYEE.txt");
    bool idFound = false;

    while (fread >> storedId) {
        getline(fread, line); // Read the rest of the line

        if (storedId == id) {
            idFound = true;
            break;
        }
    }

    fread.close();

        Employee* temp = head;
      

        while (temp!= nullptr) {
            if (temp->employee_id == id) {
                idFound = true;
                break;
            }
            temp = temp->next;
        }
    
        if (idFound) {
            cout << "\nThe ID already exists." << endl;

            cout << "\n\n\n\n\nDo you want to reenter? [Y/N]";
            cin >> reenter;

            if (reenter == 'Y' || reenter == 'y') {
                e_regis();
            } else {
                //emp.e_manage_menu();
            }
        } else {
            // Continue with the registration process
            Employee* newNode = new Employee;
            newNode->next = nullptr;

            do {
                system("CLS");
                cout << "This ID has not been used yet. Please enter the following information to register an account.\n" << endl;

                system("Color B0");
                cout << "Enter Employee Name\t\t: ";
                cin.ignore();
                getline(cin, newNode->employee_name);
                cout << "Create Employee Password\t: ";
                cin >> newNode->employee_pass;
                cout << "Enter Employee Gmail Address\t: ";
                cin.ignore();
                getline(cin, newNode->employee_address);
                cout << "Enter Employee Contact Number\t: ";
                getline(cin, newNode->employee_contact);

                cout << "\n\n	Please comfirm your information" << endl;
                cout << "\n 	----This is your information---- \n" << endl;
                cout << "\n Name 			: " << newNode->employee_name << endl;
                cout << " ID 			: " << id << endl;
                cout << " Password 		: " << newNode->employee_pass << endl;
                cout << " Address 		: " << newNode->employee_address << endl;
                cout << " Contact number		: " << newNode->employee_contact << endl;

                cout << "\n\nEnter Y to confirm [Y/N] : ";
                cin >> sure;
            } while (sure!= 'y' && sure!= 'Y');

            newNode->employee_id = id;

            if (head == nullptr) {
                head = newNode;
            } else {
                Employee* temp = head;
                while (temp->next!= nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
			
			// Write the new employee information to the file
        ofstream fout("EMPLOYEE.txt", ios::app); // Open file in append mode
        if (fout.is_open()) {
            fout <<endl<< newNode->employee_id << " "
                 << newNode->employee_pass << " "
                 << newNode->employee_name << " "
                 << newNode->employee_address << " "
                 << newNode->employee_contact;
            fout.close();
        } else {
            cout << "Error opening file for writing." << endl;
        }
            ad.admin_menu();
        }
}//end of employee register function

void EmployeeList::e_del(){
	    char back;
	    system("CLS");
	    int id;
	    char ans;
	    bool idFound = false;
	    
	    ifstream fr_user;
    	fr_user.open("EMPLOYEE.txt");
    	ofstream tempfile;
    	tempfile.open("temp.txt");
		loop:
		
	    
	    e_displayOriginalEmpData();
	    cout << "  \t   --- D E L E T E   E M P L O Y E E ---\n\n" << endl;
	    cout << "Enter the Employee ID to delete Employee Information: ";
	    cin >> 	id;
		fr_user.clear(); // clear any flags
        fr_user.seekg(0, ios::beg);
		Employee *head = NULL;
    	Employee *prev = NULL;
    	Employee *temp = head;
		while (!fr_user.eof()) {
		    Employee *temp = new Employee;
		    fr_user >> temp->employee_id;
		    fr_user >> temp->employee_pass;
		    fr_user >> temp->employee_name;
		    fr_user >> temp->employee_address;
		    fr_user >> temp->employee_contact;
		    temp->next = NULL; 
		    
		    
		    if (head == NULL) {
		        
		        head = temp;
		    } else {
		        
		        Employee *current = head;
		        while (current->next != NULL) {
		            current = current->next;
		        }
		        current->next = temp;
		    }
		}

	    temp = head;
        while((temp!=NULL)&&(temp->employee_id != id)){
			prev=temp;
			temp=temp->next;
			cout<<" "<<temp->employee_name;
		}
		if (temp != NULL) {
		    if (temp == head) {
		       
		        head = temp->next;
		    } else {
		        
		        prev->next = temp->next;
		    }
		    cout << "\nThis is the details of employee you want to delete..." << endl;
		    std::cout << std::left
              << "================================================================================================\n"
              << std::setw(8) << "ID"
              << std::setw(15) << "Password"
              << std::setw(20) << "NAME"
              << std::setw(30) << "Gmail Address"
              << "Contact Number\n"
              << "================================================================================================\n";
              std::cout << std::setw(8) << temp->employee_id
                  << std::setw(15) << temp->employee_pass
                  << std::setw(20) << temp->employee_name
                  << std::setw(30) << temp->employee_address
                  << temp->employee_contact << "\n";
		    delete temp;
		    idFound = true; 
		}
		temp=head;
		while (temp != NULL) {
        if (temp->employee_id != 0) { // Check if the node is not null
            tempfile << temp->employee_id << " " << temp->employee_pass << " " << temp->employee_name << " " << temp->employee_address << " " << temp->employee_contact << endl;
        }
        temp = temp->next;
    }

	    if (idFound) {
			fr_user.close();
    		tempfile.close();
    		remove("EMPLOYEE.txt");
    		rename("temp.txt", "EMPLOYEE.txt");
	        cout << "\n\nDeletion Employee Information successful." << endl;
	        cout << "\n\n\n\n\nDo you want to go back to menu page? [Y/N]: ";
	        cin >> back;
	        if (back == 'Y' || back == 'y') {
	            ad.admin_menu();
	        } else {
	            exit(0);
	        }
	    } else {
	        cout << "\nEmployee ID not found" << endl;
	        cout << "Do you want to re-enter Employee id? [Y/N] :";
	        cin >> ans;
	        if (ans == 'Y' || ans == 'y') {
	            goto loop;
	        } else {
				fr_user.close();
    			tempfile.close();
    			remove("EMPLOYEE.txt");
    			rename("temp.txt", "EMPLOYEE.txt");
				cout<<"done";
	            //ad.admin_menu();
	        }
	    }
		}//end of function delete employee
//main page	
void main_page(){
system("CLS");
	system("Color 80");
	int choose;
    cout<<""<<endl;	

cout<<" #                                         #                                                               "<<endl;
cout<<" #       ######   ##   #    # ######      # #   #####  #####  #      #  ####    ##   ##### #  ####  #    # "<<endl;
cout<<" #       #       #  #  #    # #          #   #  #    # #    # #      # #    #  #  #    #   # #    # ##   # "<<endl;
cout<<" #       #####  #    # #    # #####     #     # #    # #    # #      # #      #    #   #   # #    # # #  # "<<endl;
cout<<" #       #      ###### #    # #         ####### #####  #####  #      # #      ######   #   # #    # #  # # "<<endl;
cout<<" #       #      #    #  #  #  #         #     # #      #      #      # #    # #    #   #   # #    # #   ## "<<endl;
cout<<" ####### ###### #    #   ##   ######    #     # #      #      ###### #  ####  #    #   #   #  ####  #    # "<<endl;
                                                                                                           

    cout<<""<<endl;
	cout<<"	\t\t==  L E A V E   A P P L I C A T I O N  S Y S T E M  ==\n\n" <<endl;
	cout<<"	\t\t	=======  M A I N   M E N U  =======	\n\n"<<endl;
	cout<<"\t\t\t\t\t1. Admin Page "<<endl;
	cout<<"\t\t\t\t\t2. Employee Page "<<endl;
	cout<<"	\n\t\tChoose Your Selection : ";
	cin>>choose;
	switch(choose){
		case 1: 	ad.admin_main();break;
		case 2: 	emp.emp_log();break;
		default : 	cout<<"You entered an invalid selection."<<endl;
					exit(0);
	}
}

//ADMIN
//admin login page
void admin::admin_main(){
	system("CLS");
	system("Color 0B");
	cout<<"		=======  A D M I N   L O G I N  =======	\n\n"<<endl;
	cout<<"Enter your admin ID : ";
	cin>>admin_id;
	cout<<"Enter your password : ";
	cin>>admin_password;
	
	
	admin_verify();
}

//admin verify
void admin::admin_verify(){
    int verify_id;
    string verify_name, verify_password;
    char reenter;
    bool found = false; 

    ifstream fr_admin("ADMIN.txt");

    if (!fr_admin) {
        cout << "File doesn't exist." << endl;
        return;
    }

    while (fr_admin >> verify_id >> verify_password >>  verify_name) {
        if (admin_id == verify_id && admin_password == verify_password) {
            found = true;
            fr_admin >> verify_id >> verify_password >>  verify_name;
            break;  // Add this line to exit the loop once a match is found
        }
    }

    fr_admin.close();

    if (found) {
        cout << "\nAdmin verification successful!" << endl;
        admin_menu();
    } else {
        cout << "\nAdmin verification failed. Invalid credentials." << endl;
        cout << "Do you want to reenter? [Y/N]: ";
        cin >> reenter;

        if (reenter == 'Y' || reenter == 'y') {
            admin_main();
        } else {
            exit(0);
        }
    }
}

//admin menu
void admin::admin_menu(){
	int ad_choose;
	system("CLS");
	system("Color 0D");
	cout<<"		=======  A D M I N   M E N U  =======	\n\n"<<endl;
	cout<<"\t\t\t1. Approve leave "<<endl;
	cout<<"\t\t\t2. Search leave "<<endl;
	cout<<"\t\t\t3. View report"<<endl;
	cout<<"\t\t\t4. Employee Management "<<endl;
	cout<<"\t\t\t5. Home "<<endl;
	cout<<"\t\t\t0. Exit"<<endl;
	cout<<"	\nChoose Your Opinion : ";
	cin>>ad_choose;
	

	switch(ad_choose){
		case 1: 	appr.approve();break;
		case 2: 	Mlea.search();break;
		case 3: 	emp.e_display();break;
		case 4: 	emp.e_manage_menu();break;
		case 5: 	main_page();break;
		case 0:     exit(0);
		default : 	admin_menu();break;
		}
}
//admin-----Employee Management
void employee::e_manage_menu(){
	int ans;
	EmployeeList empList;

	system("CLS");
	system("Color DE");
	cout<<"		=======  A D M I N   M A N A G E M E N T   M E N U  =======	\n\n"<<endl;
	cout<<"\t\t\t1. Register New Employee "<<endl;
	cout<<"\t\t\t2. Delete Employee Information "<<endl;
	cout<<"\t\t\t3. Edit Employee Information "<<endl;
	
	cout<<"	\nChoose Your Opinion : ";
	cin>>ans;
	
	switch(ans){
		case 1:     empList.e_regis();empList.saveToFile();break;
		case 2: 	empList.e_del();break;//delete employee
		case 3: 	empList.e_usermanage();break;
		
}
}

//Employee Management-----edit
void EmployeeList::e_usermanage(){
	system("CLS");
	int id;
    string line; char reenter,back;
    bool idFound = false;

    ifstream fin;
    fin.open("EMPLOYEE.txt");
    ofstream tempfile;
    tempfile.open("temp.txt");

	e_displayOriginalEmpData();
    cout << "   \t  --- E D I T   E M P L O Y E E ---\n" << endl;
    cout << "Enter the Employee ID to edit Employee Information: ";
    cin >> id;

	fin.clear(); // clear any flags
    fin.seekg(0, ios::beg);
	Employee *head = NULL;
	Employee *prev = NULL;
	Employee *temp = head;
	while (!fin.eof()) {
	    Employee *temp = new Employee;
	    fin >> temp->employee_id;
	    fin >> temp->employee_pass;
	    fin >> temp->employee_name;
	    fin >> temp->employee_address;
	    fin >> temp->employee_contact;
		
	    temp->next = NULL; 
	    if (head == NULL) {
	        
	        head = temp;
	    } else {
	      
	        Employee *current = head;
	        while (current->next != NULL) {
	            current = current->next;
	        }
	        current->next = temp;
	    }
	}
	temp=head;

	while((temp!=NULL)&&(temp->employee_id != id)){
			prev=temp;
			temp=temp->next;
		}
		if (temp != NULL) {
		    if (temp == head) {
		     
		        head = temp->next;
		    } else {
		        
		        prev->next = temp->next;
		    }
		    cout<<"\n\nCurrent details of leave record with ID: \n"<<endl;
		    std::cout << "==================================================================================================================" << std::endl;
           std::cout << std::left;
    std::cout << std::setw(15) << "ID" 
              << std::setw(20) << "Password" 
              << std::setw(20) << "NAME" 
              << std::setw(35) << "Employee Gmail Address" 
              << std::setw(25) << "Employee Contact Number" 
              << std::endl;
    std::cout << "==================================================================================================================" << std::endl;
    std::cout << std::setw(15) << temp->employee_id
                  << std::setw(20) << temp->employee_pass
                  << std::setw(20) << temp->employee_name
                  << std::setw(35) << temp->employee_address
                  << std::setw(25) << temp->employee_contact 
                  << std::endl;
			cout<<"\n\nPlease enter new details..\n" <<endl;
			temp->employee_id=id;
			cin.ignore();
			cout<<"ENTER YOUR NAME\t\t\t: ";
			getline(cin,temp->employee_name);
			cout<<"ENTER Employee Password\t\t: ";
			cin>>temp->employee_pass;
			cout<<"ENTER Employee Gmail Address\t: ";
			cin>>temp->employee_address;
			cout<<"ENTER Employee Contact Number\t: ";
			cin>>temp->employee_contact;
			
			cout << "\n\nThis is the edited employee details" << endl;
            cout << "-----------------------------------\n" << endl;
            cout << "Employee NAME           : " << temp->employee_name << endl;
            cout << "Employee ID             : " << id << endl;
            cout << "Employee Password\t: " << temp->employee_pass << endl;
            cout << "Employee Gmail Address\t: " << temp->employee_address << endl;
            cout << "Employee Contact Number\t: " <<temp->employee_contact << endl;
            
            
	        tempfile << temp->employee_id << " " << temp->employee_pass << " " << temp->employee_name << " " << temp->employee_address << " " << temp->employee_contact << endl;
		    idFound = true;
		}
		temp=head;
		while (temp != NULL) {
        if (temp->employee_id != 0) { // Check if the node is not null
            tempfile << temp->employee_id << " " << temp->employee_pass << " " << temp->employee_name << " " << temp->employee_address << " " << temp->employee_contact << endl;
        }
        temp = temp->next;
    }

	if (idFound) {
			fin.close();
    		tempfile.close();
    		remove("EMPLOYEE.txt");
    		rename("temp.txt", "EMPLOYEE.txt");
			
			
			cout << "\nChange successful for Employee ID: " << id << endl;
        cout<<"\n\n\n\n\nDo you want to go back to menu page? [Y/N]";
		cin>>back;
		if(back=='Y'||back=='y'){
				ad.admin_menu();
			}
			else{
				exit(0);
			}
			
			
	    } else {
			char ans;
	        cout << "\nEmployee ID not found" << endl;
	        cout << "Do you want to re-enter Employee id? [Y/N] :";
	        cin >> ans;
	        if (ans == 'Y' || ans == 'y') {
	            
	        } else {
				fin.close();
    			tempfile.close();
    			remove("EMPLOYEE.txt");
    			rename("temp.txt", "EMPLOYEE.txt");
				cout<<"done";
	            ad.admin_menu();
	        }
	    }
}

//EMPLOYEE
//employee login page 
void employee::emp_log(){
	
	system("CLS");
	system("Color 0B");
	cout<<"		=======  E M P L O Y E E   L O G I N  =======	\n\n"<<endl;
	cout<<"Enter your ID : ";
	cin>>employee_id;
	cout<<"Enter your password : ";
	cin>>employee_pass;
	
	
	e_verify();
	
}
//employee verify
void employee::e_verify() {
    int verify_id;
    string verify_name, verify_password, verify_address, verify_contact,line;
    char reenter;
    bool found = false;

    ifstream fr_emp("EMPLOYEE.txt");

    if (!fr_emp) {
        cout << "File doesn't exist." << endl;
        return;
    }

    while (getline(fr_emp,line))
	{
	istringstream iss(line);
    iss >> verify_id >> verify_password >> verify_name >> verify_address >> verify_contact;
        if (employee_id == verify_id && employee_pass == verify_password) {
            found = true;
            break; // Exit the loop once a match is found
        }
    }

    fr_emp.close();

    if (found) {
        cout << "Employee verification successful!" << endl;
        emp_menu();
    } else {
        cout << "\nEmployee verification failed. Invalid credentials." << endl;
        cout << "Do you want to reenter? [Y/N]: ";
        cin >> reenter;

        if (reenter == 'Y' || reenter == 'y') {
            emp_log();
        } else {
            exit(0);
        }
    }
}
//D


void employee::e_display()
{
	EmployeeList empList;
	int i=1, ans1;
	char ans;
								
	system("Color 80");
	system("CLS");
	cout<<"\n\n		=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======	\n\n"<<endl;
	cout<<"\t\t 1. Display Employee Information "<<endl;
	cout<<"\t\t 2. Display Approved Leave Record "<<endl;
	cout<<"\t\t 3. Display Leave Requests Exceed the Limit "<<endl;
	cout<<"\n\t Enter Your Answer : ";
	cin>>ans1;
	
	switch(ans1)
	{
		case 1:
			empList.e_displaySubMenu();
			break;
		case 2:
			empList.e_displayleave();
			break;
			
		case 3:
			emp.e_displayOverBalance();
			break;
		default:
			e_display();
			break;
	}
	
}
void EmployeeList::e_displaySubMenu(){
	EmployeeList empList;
	e_displayOriginalEmpData();
	int choice;
	int searchID;
	do{
		cout<<"=================================================================================================="<<endl;
		cout<<"\n\t\t What would you like to do?"<<endl;
		cout<<"\n\t\t[1]SORT EMPLOYEE INFORMATION BASED ON ID"<<endl;
		cout<<"\t\t[2]SEARCH EMPLOYEE BASED ON ID"<<endl;
		cout<<"================================================================================================="<<endl;
		cout<<"ENTER YOUR CHOICE:";
		cin>>choice;
		if(choice == 1){
			empList.e_displayemp();
		}else if(choice == 2){
			system("CLS");
			cout << "\n\n\t\t=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======\n\n" << endl;
		cout << "\t\t\t\t\tSEARCH EMPLOYEE BASED ON ID" << endl;
    		cout <<endl<<"Enter Employee ID to search: ";
    		cin >> searchID;
    		searchEmployeeByID(searchID);
 		}else{
 			cout << "INVALID CHOICE PLEASE REENTER "<<endl;
 		
		}
	}while(choice > 3);
}
//display employee info
void EmployeeList::e_displayemp()
{
 system("CLS");
 		e_displayOriginalEmpData();
        cout << "\n\n\t\t=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======\n\n" << endl;
		cout << "\t\t\t\t\tEMPLOYEE SORTED BY ID" << endl;
		std::cout << std::left
              << "==============================================================================================================\n"
              << std::setw(15) << "Employee ID"
              << std::setw(25) << "Employee Name"
              << std::setw(25) << "Employee Password"
              << std::setw(30) << "Employee Email Address"
              << "Employee Contact\n"
              << "==============================================================================================================\n";
        
		sortEmployeesByID();
        if (head == nullptr) {
            cout << "No employee data available." << endl;
            return;
        }

        Employee* temp = head;
        int i = 1;
        while (temp != nullptr) {
            std::cout << std::setw(15) << temp->employee_id
                  << std::setw(25) << temp->employee_name
                  << std::setw(25) << temp->employee_pass
                  << std::setw(30) << temp->employee_address
                  << temp->employee_contact << "\n";
            temp = temp->next;
            i++;
        }
		
        char ans;
        cout << "\nClick [Y/y] to continue : ";
        cin >> ans;

        if (ans == 'y' || ans == 'Y') {
            e_displaySubMenu(); // Assuming this function exists
        }
    }

void EmployeeList::sortEmployeesByID() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    bool swapped;
    Employee* current;
    Employee* lastPtr = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->next != lastPtr) {
            if (current->employee_id > current->next->employee_id) {
                // Swap the data
                swap(current->employee_id, current->next->employee_id);
                swap(current->employee_pass, current->next->employee_pass);
                swap(current->employee_name, current->next->employee_name);
                swap(current->employee_address, current->next->employee_address);
                swap(current->employee_contact, current->next->employee_contact);
                swapped = true;
            }
            current = current->next;
        }
        lastPtr = current;
    } while (swapped);
}   
void EmployeeList::e_displayOriginalEmpData(){
	system("CLS");
    cout << "\n\n\t\t=======  O R I G I N A L  E M P L O Y E E   I N F O R M A T I O N  =======\n\n" << endl;
    std::cout << std::left
              << std::setw(12) << "Employee ID"
              << std::setw(20) << "Employee Name"
              << std::setw(20) << "Employee Password"
              << std::setw(28) << "Employee Email Address"
              << std::setw(20) << "Employee Contact" << std::endl;
    std::cout << "==================================================================================================================" << std::endl;

	ifstream fin("EMPLOYEE.txt");
        if (!fin) {
            cout << "File does not exist." << endl;
            exit(1);
        }

        while (fin) {
            Employee* newEmployee = new Employee;
            if (fin >> newEmployee->employee_id >> newEmployee->employee_pass >> newEmployee->employee_name >> newEmployee->employee_address >> newEmployee->employee_contact) {
                newEmployee->next = nullptr;

                if (head == nullptr) {
                    head = newEmployee;
                } else {
                    Employee* current = head;
                    while (current->next != nullptr) {
                        current = current->next;
                    }
                    current->next = newEmployee;
                }
            } else {
                delete newEmployee;
            }
        }
        
        fin.close();
        if (head == nullptr) {
            cout << "No employee data available." << endl;
            return;
        }

        Employee* temp = head;
        int i = 1;
        while (temp != nullptr) {
            std::cout << std::setw(12) << temp->employee_id
                  << std::setw(20) << temp->employee_name
                  << std::setw(20) << temp->employee_pass
                  << std::setw(28) << temp->employee_address
                  << std::setw(20) << temp->employee_contact << std::endl;
            temp = temp->next;
            i++;
        }
}
void EmployeeList::searchEmployeeByID(int id){
	EmployeeList empList;
	employee ep;
	bool found = false ;
	char back;
	
		ifstream fin("EMPLOYEE.txt");
        if (!fin) {
            cout << "File does not exist." << endl;
            exit(1);
        }

        while (fin) {
            Employee* newEmployee = new Employee;
            if (fin >> newEmployee->employee_id >> newEmployee->employee_pass >> newEmployee->employee_name >> newEmployee->employee_address >> newEmployee->employee_contact) {
                newEmployee->next = nullptr;

                if (head == nullptr) {
                    head = newEmployee;
                } else {
                    Employee* current = head;
                    while (current->next != nullptr) {
                        current = current->next;
                    }
                    current->next = newEmployee;
                }
            } else {
                delete newEmployee;
            }
        }
        
        fin.close();
        do {
        if (head == nullptr) {
            cout << "No employee data available." << endl;
            return;
        }

        Employee* temp = head;
        while (temp != nullptr) {
            if (temp->employee_id == id) {
            	cout << "-----------------------------------------------------------" << endl;
				cout <<"\t\tEmployee Information Found !!!"<<endl;
                cout << "-----------------------------------------------------------" << endl;
                cout << "Employee Information: " << "\nEmployee ID\t\t: " << temp->employee_id << "\nEmployee Name\t\t: " << temp->employee_name << "\nEmployee Password\t: " << temp->employee_pass << "\nEmployee Email Address\t: " << temp->employee_address << "\nEmployee Contact\t: " << temp->employee_contact << endl << endl;
                found = true;
                
                
                cout << endl<<"Do you want do to menu page? [Y/N]: ";
    		cin >> back;

    		if (back == 'Y' || back == 'y') {
        		ad.admin_menu();
    		}
    		else
    		{
    			exit(0);
			}
            }
            
            temp = temp->next;
            
            
        }

        if (!found) {
            cout << "Employee with ID " << id << " not found." << endl;
            cout << "Do you want to enter another ID? (Y/N): ";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                cout << "Enter Employee ID to search: ";
                cin >> id;
            } else if(choice == 'N' || choice == 'n'){
            	ep.e_display();
            }
        }
    } while (!found);
    
}
void EmployeeList::sortbyduration() {
    // Step 1: Find the maximum eduration
    int maxDuration = findMaxDuration();
    if (maxDuration == -1) {
        return; // Handle case where list is empty
    }

    // Step 2: Create a count array and initialize to 0
    int* count = new int[maxDuration + 1](); // Use dynamic array initialization
    
    // Step 3: Count frequencies of each eduration
    LeaveRecord* current = leaveHead;
    while (current != nullptr) {
        count[current->eduration]++;
        current = current->next;
    }

    // Step 4: Reconstruct sorted list based on count array
    current = leaveHead;
    int index = 0;
    while (current != nullptr) {
        while (count[index] == 0) {
            index++; // Skip over indices with count 0
        }
        current->eduration = index;
        count[index]--;
        current = current->next;
    }

    // Clean up dynamic array
    delete[] count;
}

int EmployeeList::findMaxDuration() {
    if (leaveHead == nullptr) {
        return -1; // Return -1 if list is empty
    }

    LeaveRecord* current = leaveHead;
    int maxDuration = current->eduration;
    while (current != nullptr) {
        if (current->eduration > maxDuration) {
            maxDuration = current->eduration;
        }
        current = current->next;
    }
    return maxDuration;
}

// Binary search function to find LeaveRecord by Employee ID (eid)
LeaveRecord* EmployeeList::binarySearchById(int id) {
    LeaveRecord* temp = leaveHead;

    while (temp != nullptr) {
        if (temp->eid == id) {
            return temp; // Found the LeaveRecord with the matching id
        } else if (temp->eid < id) {
            temp = temp->next;
        } else {
            return nullptr; // If B_id exceeds id, exit the cycle
        }
    }
    return nullptr; // If no record is found
}

void EmployeeList::sortById() {
    bool swapped = true;
    LeaveRecord *temp;
    LeaveRecord *lastptr = nullptr;
    do {
        swapped = false;
        temp = leaveHead;
        LeaveRecord *prev = nullptr;
        LeaveRecord *current = temp->next; // Initialize current pointer
        
        while (current != lastptr) {
            if (temp->eid > current->eid) {
                // Perform node swap
                if (prev == nullptr) {
                    leaveHead = current;
                } else {
                    prev->next = current;
                }
                temp->next = current->next;
                current->next = temp;
                swapped = true;
                
                // Reset temp and current pointers after swap
                temp = current;
            } else {
                // Move to next nodes
                prev = temp;
                temp = current;
            }
            current = temp->next;
        }
        lastptr = temp;
    } while (swapped);
}


void EmployeeList::searchbyid(){
    sortById();
    int searchId;
    cout << "\nEnter Employee ID to search for leave record: ";
    cin >> searchId;
    
     system("CLS");
     
      cout << "\n\n\t\t=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======\n\n" << endl;
		cout << "\t\t\t\t\tEMPLOYEE SEARCH BY ID" << endl;

    // Perform binary search to find the record with specified eid
    LeaveRecord* foundRecord = binarySearchById(searchId);
    if (foundRecord != nullptr) {
        // Display the found leave record
        cout << "\n\t\t-----------------------------------------------------------" << endl;
        cout << " \t\t\t   Leave Approved for Employee ID " << searchId << " :" << endl;
        cout << "\t\t-----------------------------------------------------------" << endl;
        cout << "\n\t\tEmployee ID\t\t: " << foundRecord->eid << "\n\t\tEmployee Name\t\t: " << foundRecord->B_name << "\n\t\tLeave Start Day\t\t: " << foundRecord->estart_day << "\n\t\tLeave End Day\t\t: " << foundRecord->eend_day << "\n\t\tDuration\t\t: " << foundRecord->eduration << "\n\t\tReason\t\t\t: " << foundRecord->ereason << endl << endl;
    } else {
        cout << "\nLeave record for Employee ID " << searchId << " not found." << endl;
    }
}

//display approved leave
void EmployeeList::e_displayleave(){
	system("CLS");
        cout << "\n\n\t\t\t=======  DISPLAY APPROVED LEAVE RECORD  =======\n\n" << endl;

        // Read leave data from file
        ifstream fin_app("LEAVEAPPROVE.txt");
        if (!fin_app) {
            cout << "File does not exist." << endl;
            return;
        }

        string line;
    leaveHead = nullptr;
        while (getline(fin_app, line)) {
            istringstream iss(line);
            LeaveRecord* newRecord = new LeaveRecord;
            iss >> newRecord->eid >> newRecord->B_name >> newRecord->estart_day >> newRecord->eend_day >> newRecord->eduration >> newRecord->ereason;
            newRecord->next = nullptr;

            if (leaveHead == nullptr) {
                leaveHead = newRecord;
            } else {
                LeaveRecord* current = leaveHead;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newRecord;
            }
        }
        fin_app.close();

        if (leaveHead == nullptr) {
            cout << "No leave records available." << endl;
            return;
        }

    LeaveRecord* temp = leaveHead;
    int i = 1;
    cout<<"=================================================================================================="<<endl;
	
        cout << "\t\t\t\t\tLeave Approved "<< endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    cout << std::left
    
         << std::setw(10) << "ID"
         << std::setw(15) << "NAME"
         << std::setw(15) << "START DATE"
         << std::setw(15) << "END DATE"
         << std::setw(15) << "DURATION"
         << std::setw(20) << "REASON" << endl;
	cout<<"=================================================================================================="<<endl;
		cout<<"\t\tWhat would you like to do?"<<endl;
    

    while (temp != nullptr) {
        cout << std::setw(10) << temp->eid
             << std::setw(15) << temp->B_name
             << std::setw(15) << temp->estart_day
             << std::setw(15) << temp->eend_day
             << std::setw(15) << temp->eduration
             << std::setw(20) << temp->ereason << endl;
        temp = temp->next;
        i++;
    }
    int choice;
    cout<<"=================================================================================================="<<endl;
		cout<<"\t\tWhat would you like to do?"<<endl;
		cout<<"\n\t\t[1]Sort by duration"<<endl;
		cout<<"\t\t[2]Sort by Id"<<endl;
		cout<<"\t\t[3]Search by ID"<<endl;
		cout<<"================================================================================================="<<endl;
		cout<<"ENTER YOUR CHOICE:";
    cin>>choice;
    switch(choice){
        case 1:
            sortbyduration();
            cout<<"----------------"<<endl;
            temp = leaveHead;
            i = 1;
            
            system("CLS");
            cout << "\n\n\t\t=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======\n" << endl;
		cout << "\t\t     ====E M P L O Y E E   S O R T E D   B Y   D U R A T I O N====" << endl;
            
            cout<<"=================================================================================================="<<endl;
		cout << std::left
    
         << std::setw(10) << "ID"
         << std::setw(15) << "NAME"
         << std::setw(15) << "START DATE"
         << std::setw(15) << "END DATE"
         << std::setw(15) << "DURATION"
         << std::setw(20) << "REASON" << endl;
	cout<<"=================================================================================================="<<endl;
            while (temp != nullptr) {
               
                cout << std::setw(10) << temp->eid
             << std::setw(15) << temp->B_name
             << std::setw(15) << temp->estart_day
             << std::setw(15) << temp->eend_day
             << std::setw(15) << temp->eduration
             << std::setw(20) << temp->ereason << endl;
                temp = temp->next;
                i++;
            }
            break;
        case 2:
            sortById();
			cout<<"-------------"<<endl;
            temp = leaveHead;
            i = 1;
            
            system("CLS");
            cout << "\n\n\t\t=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======" << endl;
            cout<<"\n\t\t=======  L E A V E   R E Q U E S T S   E X C E E D   T H E   L I M IT  ======="<<endl;
		cout << "\n\t\t\t====E M P L O Y E E   S O R T E D   B Y  I D====\n\n" << endl;
			
		
		cout<<"=================================================================================================="<<endl;
		cout << std::left
    
         << std::setw(10) << "ID"
         << std::setw(15) << "NAME"
         << std::setw(15) << "START DATE"
         << std::setw(15) << "END DATE"
         << std::setw(15) << "DURATION"
         << std::setw(20) << "REASON" << endl;
	cout<<"=================================================================================================="<<endl;
		
             
            while (temp != nullptr) {
                
               	cout << std::setw(10) << temp->eid
             << std::setw(15) << temp->B_name
             << std::setw(15) << temp->estart_day
             << std::setw(15) << temp->eend_day
             << std::setw(15) << temp->eduration
             << std::setw(20) << temp->ereason << endl;
             temp = temp->next;
                i++;
            }
            break;
        case 3:
            searchbyid();
            break;
        default:
            cout<<"error"<<endl;
        
    };
    char ans;
    cout << "\nClick [Y/y] to continue : ";
    cin >> ans;

    if (ans == 'y' || ans == 'Y') {
        ad.admin_menu(); // Assuming this function exists
    }
}

BalanceRecord* balanceHashTable[TABLE_SIZE] = {nullptr};

void insertIntoHashTable(BalanceRecord* record) {
    int index = record->B_id % TABLE_SIZE;
    record->next = balanceHashTable[index];
    balanceHashTable[index] = record;
}

BalanceRecord* searchInHashTable(int id) {
    int index = id % TABLE_SIZE;
    BalanceRecord* current = balanceHashTable[index];
    while (current) {
        if (current->B_id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Not found
}

BalanceRecord* merge(BalanceRecord* left, BalanceRecord* right, function<bool(BalanceRecord*, BalanceRecord*)> cmp) {
    BalanceRecord* result = nullptr;
    if (!left) return right;
    if (!right) return left;

    if (cmp(left, right)) {
        result = left;
        result->next = merge(left->next, right, cmp);
    } else {
        result = right;
        result->next = merge(left, right->next, cmp);
    }
    return result;
}

void split(BalanceRecord* source, BalanceRecord** frontRef, BalanceRecord** backRef) {
    BalanceRecord* fast;
    BalanceRecord* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

void mergeSort(BalanceRecord** headRef, function<bool(BalanceRecord*, BalanceRecord*)> cmp) {
    BalanceRecord* head = *headRef;
    BalanceRecord* left;
    BalanceRecord* right;

    if (!head || !head->next) {
        return;
    }

    split(head, &left, &right);
    mergeSort(&left, cmp);
    mergeSort(&right, cmp);
    *headRef = merge(left, right, cmp);
}

void clearLinkedList(BalanceRecord*& head) {
    BalanceRecord* current = head;
    while (current) {
        BalanceRecord* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void clearHashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        balanceHashTable[i] = nullptr;
    }
}

// Display leave requests that exceed the limit
void employee::e_displayOverBalance() {
    BalanceRecord* balanceHead = nullptr;
    clearHashTable(); // Clear hash table before new data is loaded

    system("CLS");
    cout << "\n\n=======  LEAVE REQUESTS EXCEED THE LIMIT  =======\n\n" << endl;

    ifstream fin_bal("BALANCE.txt");
    if (!fin_bal) {
        cout << "File does not exist." << endl;
        return;
    }

    string line;
    while (getline(fin_bal, line)) {
        istringstream iss(line);
        BalanceRecord* newRecord = new BalanceRecord;
        iss >> newRecord->B_id >> newRecord->B_name >> newRecord->B_balance;
        newRecord->next = nullptr;

        if (balanceHead == nullptr) {
            balanceHead = newRecord;
        } else {
            BalanceRecord* current = balanceHead;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newRecord;
        }

        insertIntoHashTable(newRecord);
    }
    fin_bal.close();

    if (balanceHead == nullptr) {
        cout << "No balance records available." << endl;
        return;
    }

    // Display records
    BalanceRecord* temp = balanceHead;
    int i = 1;
    cout<<"=================================================================================================="<<endl;
		cout << std::left
    
         << std::setw(10) << "ID"
         << std::setw(15) << "NAME"
         << std::setw(15) << "DURATION"<<endl;
	cout<<"=================================================================================================="<<endl;
    while (temp != nullptr) {
        if (temp->B_balance >= 30) {
            
	
	cout << std::setw(10) << temp->B_id
             << std::setw(15) << temp->B_name
             << std::setw(15) << temp->B_balance<<endl;
             
            i++;
        }
        temp = temp->next;
    }

    int choice;
    cout << "==================================================================================================" << endl;
    cout << "\t\tWhat would you like to do?" << endl;
    cout << "\n\t\t[1] Sort by duration" << endl;
    cout << "\t\t[2] Search by ID" << endl;
    cout << "=================================================================================================" << endl;
    cout << "ENTER YOUR CHOICE: ";
    cin >> choice;
    cin.ignore();

    switch(choice) {
        case 1:
            mergeSort(&balanceHead, [](BalanceRecord* a, BalanceRecord* b) {
                return a->B_balance < b->B_balance;
            });
            cout << "----------------" << endl;
            temp = balanceHead;
            i = 1;

            system("CLS");
            cout << "\n\n\t\t=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======\n\n" << endl;
            cout<<"\n\n\t\t=======  L E A V E   R E Q U E S T S   E X C E E D   T H E   L I M IT  ======="<<endl;
            cout << "\t\t\t====E M P L O Y E E   S O R T E D   B Y   D U R A T I O N====" << endl;


			cout<<"=================================================================================================="<<endl;
			cout <<"\t\t"<<std::left
    
        	 << std::setw(10) << "ID"
       	 	<< std::setw(15) << "NAME"
        	<< std::setw(15) << "DURATION"<<endl;
			cout<<"=================================================================================================="<<endl;
            while (temp != nullptr) {
                if (temp->B_balance >= 30) {
                    
                    cout <<"\t\t"<<std::setw(10) << temp->B_id
             << std::setw(15) << temp->B_name
             << std::setw(15) << temp->B_balance<<endl;
                    i++;
                }
                temp = temp->next;
            }
            break;
        case 2:
            int id;
           system("CLS");
            cout << "\n\n\t\t=======  E M P L O Y E E   I N F O R M A T I O N   D I S P L A Y  =======" <<endl<< endl;
            cout << "\t\t\t====E M P L O Y E E   S E A R C H   B Y   ID====" << endl<<endl;
            cout << "Enter ID to search: ";
            cin >> id;
            cin.ignore(); 
            {
                BalanceRecord* found = searchInHashTable(id);
                if (found) {
                    cout << "\nEmployee ID\t: " << found->B_id << "\nEmployee Name\t: " << found->B_name << "\nDuration\t: " << found->B_balance << endl;
                } else {
                    cout << "Record not found." << endl;
                }
            }
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }

    char ans;
    cout << "\nClick [Y/y] to continue : ";
    cin >> ans;
    cin.ignore();

    if (ans == 'y' || ans == 'Y') {
        clearLinkedList(balanceHead); // Clear linked list before exiting
        ad.admin_menu(); 
    }
}


//employee view balance
void employee::ViewBalance(int id){
	
	char ans,reenter;
	bool found=false;
	string line;
	system("CLS");
	cout<<"\n\n		=======  E M P L O Y E E   B A L A N C E   D I S P L A Y  =======	\n\n"<<endl;
	ifstream fr_bal;
	fr_bal.open("BALANCE.txt");
    fr_bal.clear(); // clear any flags
    fr_bal.seekg(0, ios::beg);
    BalanceRecord *head = NULL;
    BalanceRecord *prev = NULL;
	BalanceRecord *temp = head;
	if(!fr_bal)//failure connection
	{
		cout<<"File does not exist."<<endl;
		exit(0);	
	}//end of if
	else
	{
	    
	    while(!fr_bal.eof()){
            BalanceRecord *temp = new BalanceRecord;
            fr_bal>>temp->B_id>>temp->B_name>>temp->B_balance;
            temp->next=NULL;
            if (head == NULL) {
		        
		        head = temp;
		    } else {
		       
		        BalanceRecord *current = head;
		        while (current->next != NULL) {
		            current = current->next;
		        }
		        current->next = temp;
		    }
        }
    fr_bal.close();
    temp = head;
    while((temp!=NULL)&&(temp->B_id != id)){
		prev=temp;
		temp=temp->next;
	}
    if(temp!=NULL){
        if (temp == head) {
		        
		        head = temp->next;
		    } else {
		        
		        prev->next = temp->next;
		    }
        cout<<"Employee ID\t: "<<temp->B_id<<"\nEmployee Name\t: "<<temp->B_name<<"\nDuration\t: "<<temp->B_balance<<endl;
        if(temp->B_balance>=30){
            cout<<"\nYou have exceeded your leave limit!!"<<endl;
        }else{
            cout<<"\nThere are "<<30-temp->B_balance<<" days left in your limit."<<endl;
        }
        found = true;
    }
		if(!found){
			cout<<"\n\nInvalid Employee ID."<<endl;
			cout<< "\nDo you want to re-enter your id? [Y/N]: ";
        	cin>>reenter;
       		if(reenter=='Y'||reenter=='y'){
				ViewBalance(id);
			}
			else{
				emp.emp_menu();
			}
	}
	fr_bal.close();
	}
	cout<<"\nClick [Y/y] to continue : ";
	cin>>ans;
	
	if(ans=='y' || ans=='Y') 
	{
		emp.emp_menu();
	}
	 while(ans!= 'y' && ans != 'Y')
        {
        	cout<<"Error selected please select again.";
        	cout << "\nClick [Y/y] to continue : ";
      		cin >> ans;
		}
		emp.emp_menu();
    }

//employee menu
void employee::emp_menu(){
	int empchoose;
	system("CLS");
	cout<<"		=======  E M P L O Y E E   M E N U  =======	\n\n"<<endl;
	cout<<"\t\t\t1. Apply leave "<<endl;
	cout<<"\t\t\t2. View leave "<<endl;
	cout<<"\t\t\t3. Edit leave "<<endl;
	cout<<"\t\t\t4. Delete leave "<<endl;
	cout<<"\t\t\t5. View Balance"<<endl;
	cout<<"\t\t\t6. Home "<<endl;
	cout<<"\t\t\t7. Exit "<<endl;
	cout<<"	\nChoose Your Opinion : ";
	cin>>empchoose;
	
	switch(empchoose){
		case 1: 	Alea.apply(employee_id);break;
		case 2: 	Mlea.viewleave(employee_id);break;
		case 3: 	Mlea.editleave(employee_id);break;
		case 4: 	Mlea.delfile(employee_id);break;
		case 5: 	emp.ViewBalance(employee_id);break;
		case 6: 	main_page();break;
		case 7: 	exit(0);break;
		default : 	emp_menu();break;
	}
}

//APPLY LEAVE
void Applyleave::apply(int id){
    char reenter;
	int storedId;
	string line;
	system("CLS");
   	cout<<"		=======  A P P L Y  L E A V E  =======	\n\n"<<endl;
    ifstream fread("LEAVEAPPLY.txt");
    bool idFound = false;
    fread.clear(); // clear any flags
    fread.seekg(0, ios::beg);
    LeaveRequest *head =NULL;
    LeaveRequest *prev=NULL;
    LeaveRequest *temp =head;
    if(fread.peek() == ifstream::traits_type::eof()){
        system("CLS");
        temp = new LeaveRequest;
        temp->next = NULL;
        temp->id = id;
    	cout<<"		=======  A P P L Y  L E A V E  =======	\n\n"<<endl;
    	cout<<"You do not have any leave you are applying for. Please fill in the following information."<<endl;
        cout<<"\nENTER YOUR NAME : ";
		cin.ignore();
		getline(cin,temp->name);
		cout<<"ENTER YOUR START DATE [mm dd]: ";
		cin>>leave_start_mo>>leave_start_day;
		cout<<"ENTER YOUR END DATE [mm dd]: ";
		cin>>leave_end_mo>>leave_end_day;
		cout<<"Select your reason: "<<endl;
		cout<<"{[1] Health-related issues [2] Maternity leave [3] Family emergency [4] Personal reasons}: ";
		cin>>optreason;
		temp->duration=getDuration();
		temp->reason = getReason(optreason);
		if (!isValidDate(leave_start_mo, leave_start_day) || !isValidDate(leave_end_mo, leave_end_day)||leave_start_mo > leave_end_mo || (leave_start_mo == leave_end_mo && leave_start_day > leave_end_day)) {
		    cout << "|-INVALID DATE-|" << endl;
		    cout << "Do you want to re-enter your application form? [Y/N]: ";
		    cin >> reenter;
		    if (reenter == 'Y' || reenter == 'y') {
    	    	apply(id);
		    } else {
	            emp.emp_menu();
		    }
	    }
	    cout << "\n\nThis is your leave details" << endl;
		cout << "-----------------------------------\n" << endl;
		cout << "You are applying leave from " << leave_start_mo << " / " << leave_start_day << " until " << leave_end_mo << " / " << leave_end_day << endl;
		cout << "The reason: " << temp->reason << endl;
		cout << "The duration of your leave is " << temp->duration << " days\n";
		ofstream fwrite;
		fwrite.open("LEAVEAPPLY.txt",ios::app);
		if(!fwrite){
			cout<<"File not exist."<<endl;
		}
		fwrite<<temp->id<<" "<<temp->name<<" "<<leave_start_mo<<"/"<<leave_start_day<<" "<<leave_end_mo<<"/"<<leave_end_day<<" "<<temp->duration<<" "<<temp->reason<<endl;
		cout<<"Your application already saved...."<<endl;
		fwrite.close();
		cout<<"\n\n\n\n\nDo you want to go back to menu page? [Y/N]: ";
		cin>>back;
		if(back=='Y'||back=='y'){
			emp.emp_menu();
		}
		else{
			exit(0);
		}
    }
    while(!fread.eof()){
        temp = new LeaveRequest;
        fread>>temp->id>>temp->name>>temp->start_date>>temp->end_date>>temp->duration>>temp->reason;
        temp->next =NULL;
        if (head == NULL) {
		        
		        head = temp;
		    } else {
		        
		        LeaveRequest *current = head;
		        while (current->next != NULL) {
		            current = current->next;
		        }
		        current->next = temp;
		    }
    }
    temp = head;
    while (temp!= nullptr) {
        if (temp->id == id) {
            idFound = true;
            break;
        }
        temp = temp->next;
    }
    fread.close();
    if(idFound){
        cout << "\nYou already have a leave that is being applied for, and you cannot submit another application." << endl;
        cout << "\n\n\n\n\nDo you want to go back to the menu page? [Y/N]: ";
        cin >> back;
        if (back == 'Y' || back == 'y') {
            emp.emp_menu();
        } else {
            exit(0);
        }}else{
        	system("CLS");
            temp = new LeaveRequest;
            temp->next = NULL;
            temp->id = id;
        	cout<<"		=======  A P P L Y  L E A V E  =======	\n\n"<<endl;
        	cout<<"You do not have any leave you are applying for. Please fill in the following information."<<endl;
            cout<<"\nENTER YOUR NAME : ";
			cin.ignore();
			getline(cin,temp->name);
			cout<<"ENTER YOUR START DATE [mm dd]: ";
			cin>>leave_start_mo>>leave_start_day;
			cout<<"ENTER YOUR END DATE [mm dd]: ";
			cin>>leave_end_mo>>leave_end_day;
			cout<<"Select your reason: "<<endl;
			cout<<"{[1] Health-related issues [2] Maternity leave [3] Family emergency [4] Personal reasons}: ";
			cin>>optreason;
			temp->duration=getDuration();
			temp->reason = getReason(optreason);
			
			
			if (!isValidDate(leave_start_mo, leave_start_day) || !isValidDate(leave_end_mo, leave_end_day)||leave_start_mo > leave_end_mo || (leave_start_mo == leave_end_mo && leave_start_day > leave_end_day)) {
    		cout << "|-INVALID DATE-|" << endl;
    		cout << "Do you want to re-enter your application form? [Y/N]: ";
    		cin >> reenter;

    		if (reenter == 'Y' || reenter == 'y') {
        		apply(id);
    		} else {
    	        emp.emp_menu();
    		}
		}
		cout << "\n\nThis is your leave details" << endl;
		cout << "-----------------------------------\n" << endl;
		cout << "You are applying leave from " << leave_start_mo << " / " << leave_start_day << " until " << leave_end_mo << " / " << leave_end_day << endl;
		cout << "The reason: " << temp->reason << endl;
		cout << "The duration of your leave is " << temp->duration << " days\n";
		ofstream fwrite;
		fwrite.open("LEAVEAPPLY.txt",ios::app);
		if(!fwrite){
			cout<<"File not exist."<<endl;
		}
		fwrite<<temp->id<<" "<<temp->name<<" "<<leave_start_mo<<"/"<<leave_start_day<<" "<<leave_end_mo<<"/"<<leave_end_day<<" "<<temp->duration<<" "<<temp->reason<<endl;
		cout<<"Your application already saved...."<<endl;
		fwrite.close();
		cout<<"\n\n\n\n\nDo you want to go back to menu page? [Y/N]: ";
		cin>>back;
		if(back=='Y'||back=='y'){
			emp.emp_menu();
		}
		else{
			exit(0);
		}
			
    }

}
    	
bool Applyleave::isValidDate(int month, int day){
        return (month > 0 && month <= 12 && day > 0 && day <= getDaysInMonth(month));
    }
    
int Applyleave::getDaysInMonth(int month){
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        } else if (month == 2) {
            return 28;
        } else {
            return 31;
        }
    }
    
int Applyleave::getDuration(){
    	{
        int total_days_start = leave_start_day;
        int total_days_end = leave_end_day;

        for (int month = 1; month < leave_start_mo; ++month) {
            total_days_start += getDaysInMonth(month);
        }

        for (int month = 1; month < leave_end_mo; ++month) {
            total_days_end += getDaysInMonth(month);
        }

        return total_days_end - total_days_start;
    }
	}
	
string Applyleave::getReason(int optreason) {
			char reenter;
			Employee e;
			int id=e.employee_id;
			switch(optreason) { 
			
				case 1: return "Health-related-issues";
						break;
				case 2: return "Maternity-leave";
						break;	 
				case 3: return "Family-emergency";
						break;
				case 4: return "Personal-reasons";
						break;
				default:  
				cout<<"|-INVALID REASON-|"<<endl;
				cout<<"Do you want to re-enter your application form? [Y/N]: ";
				cin>>reenter;
				
				
				if(reenter=='Y'||reenter=='y'){
					apply(id);
				}
				
				else{
					main_page();
				}
				 
				 
			}
		
	}

//DELETE LEAVE
//DELETE LEAVE
void Modifyleave::delfile(int id){
	system("CLS");
    char reenter;
    bool idFound = false;

    ifstream fin;
    fin.open("LEAVEAPPLY.txt");
    ofstream tempfile;
    tempfile.open("temp.txt");

    cout << "		======= D E L E T E   L E A V E =======	\n\n" << endl;
    fin.clear(); // clear any flags
    fin.seekg(0, ios::beg);
    LeaveRequest *head = NULL;
    LeaveRequest *prev = NULL;
    LeaveRequest *temp = head;
    while (!fin.eof()){
	    LeaveRequest *temp = new LeaveRequest;
	    fin>>temp->id;
        fin>>temp->name;
        fin>>temp->start_date;
        fin>>temp->end_date;
        fin>>temp->duration;
        fin>>temp->reason;
        
	    temp->next = NULL;
	    if (head == NULL) {
	        
	        head = temp;
	    } else {
	        
	       LeaveRequest *current = head;
	        while (current->next != NULL) {
	            current = current->next;
	        }
	        current->next = temp;
	    }
	}

    temp=head;
    while((temp!=NULL)&&(temp->id != id)){
			prev=temp;
			temp=temp->next;
		}
		if (temp != NULL) {
		    if (temp == head) {
		       
		        head = temp->next;
		    } else {
		        
		        prev->next = temp->next;
		    }
		    cout<<"\n\nThis is the details of the leave you want to delete: \n"<<endl;
		    std::cout << "=============================================================================================" << std::endl;
            std::cout << std::left;
    std::cout << std::setw(10) << "ID"
              << std::setw(20) << "NAME"
              << std::setw(15) << "START DATE"
              << std::setw(15) << "END DATE"
              << std::setw(15) << "DURATION"
              << std::setw(25) << "REASON"
              << std::endl;
    std::cout << "=============================================================================================" << std::endl;
    std::cout << std::setw(10) << temp->id
                  << std::setw(20) << temp->name
                  << std::setw(15) << temp->start_date
                  << std::setw(15) << temp->end_date
                  << std::setw(15) << temp->duration
                  << std::setw(25) << temp->reason
                  << std::endl;
		    delete temp;
		    idFound = true; 
	}

    temp=head;
	while (temp != NULL) {
        tempfile<<temp->id<<" "<<temp->name<<" "<<temp->start_date<<" "<<temp->end_date<<" "<<temp->duration<<" "<<temp->reason<<endl;
        temp = temp->next;
    }

    if (idFound)
    {
        fin.close();
    	tempfile.close();
    	remove("LEAVEAPPLY.txt");
    	rename("temp.txt", "LEAVEAPPLY.txt");
        cout << "\nDeletion successful for Employee ID: " << id << endl;
        cout<<"\n\n\n\n\nDo you want to go back to menu page? [Y/N]: ";
		cin>>back;
		if(back=='Y'||back=='y'){
				emp.emp_menu();
			}
			else{
				exit(0);
			}
    }
    else
    {
        cout << "\nEmployee ID not found. No any leave apply from this ID." << endl;
        cout<< "Click [Y / y] to continue: ";
        cin>>reenter;
        if(reenter=='Y'||reenter=='y'){
                emp.emp_menu();
			}
			else{
               emp.emp_menu();
			}
		
    }
}

// Hash table for managing Leave Records
class LeaveHashTable {
private:
    LeaveRecord* table[TABLE_SIZE];

    int hashFunction(int eid) {
        return eid % TABLE_SIZE;
    }

public:
    LeaveHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    void insert(const LeaveRecord& record) {
        int index = hashFunction(record.eid);
        LeaveRecord* newNode = new LeaveRecord(record);
        newNode->next = table[index];
        table[index] = newNode;
    }

    LeaveRecord* search(int eid) {
        int index = hashFunction(eid);
        LeaveRecord* current = table[index];
        while (current) {
            if (current->eid == eid) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

//SEARCH LEAVE
void Modifyleave::search() {
    system("CLS");
    system("Color 80");
    int appid, aprid, choose;
    string line;
    char reenter;

    LeaveHashTable leaveApplications;
    LeaveHashTable leaveApprovals;

    // Load leave applications
    ifstream fin_app("LEAVEAPPLY.txt");
    while (getline(fin_app, line)) {
        istringstream iss(line);
        LeaveRecord record;
        iss >> record.eid >> record.B_name >> record.estart_day >> record.eend_day >> record.eduration >> record.ereason;
        leaveApplications.insert(record);
    }
    fin_app.close();

    // Load leave approvals
    ifstream fin_apr("LEAVEAPPROVE.txt");
    while (getline(fin_apr, line)) {
        istringstream iss(line);
        LeaveRecord record;
        iss >> record.eid >> record.B_name >> record.estart_day >> record.eend_day >> record.eduration >> record.ereason;
        leaveApprovals.insert(record);
    }
    fin_apr.close();
	
    cout << "\n\t\t\t\t    ======= S E A R C H  L E A V E =======\n" << endl;
   	cout<<"\t\t=================================================================================="<<endl;
    cout << "\t\t\tSelect the application status of the leave you want to search for? \n\t\t\t\t [1] Applying\n\t\t\t\t [2] Approved " << endl;
    cout<<"\t\t=================================================================================="<<endl;
    cout << "\n\t\t\tEnter your option [1 / 2]: ";
    cin >> choose;

    if (choose == 1) {
    	
    	
    	
    	system("CLS");
    cout << "\n\n\t\t======= A P P L Y I N G  L E A V E  E M P L O Y E E   I N F O R M A T I O N =======\n\n" << endl;
    
        cout << "Enter the Employee ID to search: ";
        cin >> appid;

        LeaveRecord* record = leaveApplications.search(appid);
        if (record) {
            cout << "\n\nThis is the details of the leave: \n" << endl;
            cout<<"=============================================================================================="<<endl;
		cout << std::left
		     << std::setw(10) << "ID"
		     << std::setw(15) << "NAME"
		     << std::setw(15) << "START DATE"
		     << std::setw(15) << "END DATE"
		     << std::setw(15) << "DURATION"
		     << std::setw(20) << "REASON" << endl;
		
		cout << std::setw(10) << record->eid
		     << std::setw(15) << record->B_name
		     << std::setw(15) << record->estart_day
		     << std::setw(15) << record->eend_day
		     << std::setw(15) << record->eduration
		     << std::setw(20) << record->ereason << endl;
        cout<<"=============================================================================================="<<endl;
        cout<<endl<<"Do you want back to menu ? [Y/N]:";
        cin>>reenter;
        if(reenter == 'Y' || reenter == 'y')
        {
        	ad.admin_menu();
		}
		else{
			exit(0);
		}
		
		} else {
            cout << "\nEmployee ID not found." << endl;
            cout <<endl<<"Do you want to re-enter your ID? [Y/N]: ";
            cin >> reenter;
            if (reenter == 'Y' || reenter == 'y') {
                search();
            } else {
                 ad.admin_menu();
            }
        }
        
    } else if (choose == 2) {
    	
    	system("CLS");
    cout << "\n\n\t\t======= A P P R O V E D  L E A V E  E M P L O Y E E   I N F O R M A T I O N =======\n\n" << endl;
    
        cout << "Enter the Employee ID to search: ";
        cin >> aprid;

        LeaveRecord* record = leaveApprovals.search(aprid);
        if (record) {
            std::cout << "\n\nThis is the details of the leave: \n" << std::endl;
            cout<<"=============================================================================================="<<endl;
    std::cout << std::left
              << std::setw(10) << "ID"
              << std::setw(15) << "NAME"
              << std::setw(15) << "START DATE"
              << std::setw(15) << "END DATE"
              << std::setw(15) << "DURATION"
              << std::setw(20) << "REASON" << std::endl;

    std::cout << std::setw(10) << record->eid
              << std::setw(15) << record->B_name
              << std::setw(15) << record->estart_day
              << std::setw(15) << record->eend_day
              << std::setw(15) << record->eduration
              << std::setw(20) << record->ereason << std::endl;
			cout<<"=============================================================================================="<<endl;
        cout<<endl<<"Do you want back to menu ? [Y/N]:";
        cin>>reenter;
        if(reenter == 'Y' || reenter == 'y')
        {
        	ad.admin_menu();
		}
		else{
			exit(0);
		}
		} else {
            cout << "\nNo matching records found for Employee ID: " << aprid << endl;
            cout << "Do you want to re-enter your ID? [Y/N]: ";
            cin >> reenter;
            if (reenter == 'Y' || reenter == 'y') {
                search();
            } else {
                 ad.admin_menu();
            }
        }
    } else {
        cout << "\nInvalid Selection." << endl;
        cout <<"Do you want to re-enter your selection? [Y/N]: ";
        cin >> reenter;
        if (reenter == 'Y' || reenter == 'y') {
            search();
        } else {
             emp.emp_menu();
        }
    }
}

void Modifyleave::viewleave(int id) {
    system("CLS");
    int appid, aprid, choose;
    string line;
    char reenter;

    LeaveHashTable leaveApplications;
    LeaveHashTable leaveApprovals;

    // Load leave applications
    ifstream fin_app("LEAVEAPPLY.txt");
    while (getline(fin_app, line)) {
        istringstream iss(line);
        LeaveRecord record;
        iss >> record.eid >> record.B_name >> record.estart_day >> record.eend_day >> record.eduration >> record.ereason;
        leaveApplications.insert(record);
    }
    fin_app.close();

    // Load leave approvals
    ifstream fin_apr("LEAVEAPPROVE.txt");
    while (getline(fin_apr, line)) {
        istringstream iss(line);
        LeaveRecord record;
        iss >> record.eid >> record.B_name >> record.estart_day >> record.eend_day >> record.eduration >> record.ereason;
        leaveApprovals.insert(record);
    }
    fin_apr.close();

    cout << "======= S E A R C H  L E A V E =======\n\n" << endl;
    cout << "Select the application status of the leave you want to search for? \n [1] Applying [2] Approved " << endl;
    cout << "\nEnter your option (1 / 2): ";
    cin >> choose;

    if (choose == 1) {
        appid = id;

        LeaveRecord* record = leaveApplications.search(appid);
        if (record) {
            cout << "\n\nThis is the details of the leave: \n" << endl;
            cout<<"=============================================================================================="<<endl;
            cout << left; // Set alignment to left
    cout << setw(10) << "ID" 
         << setw(20) << "NAME" 
         << setw(15) << "START DATE" 
         << setw(15) << "END DATE" 
         << setw(10) << "DURATION" 
         << setw(20) << "REASON" << endl;
         cout<<"=============================================================================================="<<endl;

    cout << setw(10) << record->eid 
         << setw(20) << record->B_name 
         << setw(15) << record->estart_day 
         << setw(15) << record->eend_day 
         << setw(10) << record->eduration 
         << setw(20) << record->ereason << endl;
        
        cout<<endl<<"Do you want back to menu ? [Y/N]:";
        cin>>reenter;
        if(reenter == 'Y' || reenter == 'y')
        {
        	emp.emp_menu();
		}
		else{
			exit(0);
		}
		
		} else {
            cout << "\nEmployee ID not found." << endl;
            cout <<endl<<"Do you want to re-enter your ID? [Y/N]: ";
            cin >> reenter;
            if (reenter == 'Y' || reenter == 'y') {
                search();
            } else {
                 emp.emp_menu();
            }
        }
        
    } else if (choose == 2) {
        aprid = id;

        LeaveRecord* record = leaveApprovals.search(aprid);
        if (record) {
            cout << "\n\nThis is the details of the leave: \n" << endl;
            cout << "ID\tNAME\t\tSTART DATE\tEND DATE\tDURATION\tREASON" << endl;
            cout << record->eid << "\t" << record->B_name << "\t" << record->estart_day << "\t" << record->eend_day << "\t" << record->eduration << "\t" << record->ereason << endl;
        cout<<endl<<"Do you want back to menu ? [Y/N]:";
        cin>>reenter;
        if(reenter == 'Y' || reenter == 'y')
        {
        	emp.emp_menu();
		}
		else{
			exit(0);
		}
		} else {
            cout << "\nNo records found for Employee ID: " << aprid << endl<<endl;
            cout << "Do you want back to menu? [Y/N]: ";
            cin >> reenter;
            if (reenter == 'Y' || reenter == 'y') {
                emp.emp_menu();
            } else {
                 exit(0);
            }
        }
    } else {
        cout << "\nInvalid Selection." << endl;
        cout <<"Do you want to re-enter your selection? [Y/N]: ";
        cin >> reenter;
        if (reenter == 'Y' || reenter == 'y') {
            search();
        } else {
             emp.emp_menu();
        }
    }
}

//EDIT LEAVE
void Modifyleave::editleave(int id){
	system("CLS");
     char reenter;
    bool idFound = false;

    ifstream fin;
    fin.open("LEAVEAPPLY.txt");
    ofstream tempfile;
    tempfile.open("temp.txt");
    fin.clear(); // clear any flags
    fin.seekg(0, ios::beg);
    cout << "		======= E D I T   L E A V E =======	\n\n" << endl;
  
    LeaveRequest* head =NULL;
    LeaveRequest* prev = NULL;
    LeaveRequest* temp = head;
    while(!fin.eof()){
        temp = new LeaveRequest;
        fin>>temp->id;
        fin>>temp->name;
        fin>>temp->start_date;
        fin>>temp->end_date;
        fin>>temp->duration;
        fin>>temp->reason;
        
        temp->next=NULL;
        if (head == NULL) {
	        
	        head = temp;
	    } else {
	        
	        LeaveRequest *current = head;
	        while (current->next != NULL) {
	            current = current->next;
	        }
	        current->next = temp;
	    }
    }
    temp=head;
    while((temp!=NULL)&&(temp->id != id)){
		prev=temp;
		temp=temp->next;
	}
    if (temp != NULL) {
	    if (temp == head) {
	        
	        head = temp->next;
	    } else {
	       
	        prev->next = temp->next;
	    }
        cout<<"\n\nCurrent details of leave record with ID: \n"<<endl;
        std::cout << "=================================================================================================" << std::endl;
        std::cout << std::left;
    std::cout << std::setw(10) << "ID" 
              << std::setw(20) << "NAME" 
              << std::setw(15) << "START DATE" 
              << std::setw(15) << "END DATE" 
              << std::setw(15) << "DURATION" 
              << std::setw(25) << "REASON" 
              << std::endl;
    std::cout << "=================================================================================================" << std::endl;
    std::cout << std::setw(10) << temp->id
                  << std::setw(20) << temp->name
                  << std::setw(15) << temp->start_date
                  << std::setw(15) << temp->end_date
                  << std::setw(15) << temp->duration
                  << std::setw(25) << temp->reason 
                  << std::endl;
		cout<<"\n\nPlease enter new details..\n" <<endl;
        cout<<"ENTER YOUR NAME : ";
		cin.ignore();
		getline(cin,temp->name);
		cout<<"ENTER YOUR START DATE [mm dd]: ";
		cin>>leave_start_mo>>leave_start_day;
		cout<<"ENTER YOUR END DATE [mm dd]: ";
		cin>>leave_end_mo>>leave_end_day;
		cout<<"Select your reason: "<<endl;
		cout<<"{[1] Health-related issues [2] Maternity leave [3] Family emergency [4] Personal reasons}: ";
		cin>>optreason;
		temp->duration=getDuration();
		temp->reason = getReason(optreason);
		if (!isValidDate(leave_start_mo, leave_start_day) || !isValidDate(leave_end_mo, leave_end_day)||leave_start_mo > leave_end_mo || (leave_start_mo == leave_end_mo && leave_start_day > leave_end_day)) {
    	cout << "|-INVALID DATE-|" << endl;
    	cout << "Do you want to try again? [Y/N]: ";
    	cin >> reenter;
    	if (reenter == 'Y' || reenter == 'y') {
        	editleave(id);
    	} else {

    	    main_page();
    	}
    }		
    		cout << "\n\nThis is your edit leave details" << endl;
    		cout << "-----------------------------------\n" << endl;
    		cout << "You are applying leave from \t:" << leave_start_mo << " / " << leave_start_day << " until " << leave_end_mo << " / " << leave_end_day << endl;
    		cout << "The reason\t\t\t: " << temp->reason << endl;
    		cout << "The duration of your leave is\t: " << getDuration() << " days\n";
    		tempfile<<temp->id<<" "<<temp->name<<" "<<leave_start_mo<<"/"<<leave_start_day<<" "<<leave_end_mo<<"/"<<leave_end_day<<" "<<temp->duration<<" "<<temp->reason<<endl;
		    idFound = true;
    }
    temp=head;
    while (temp != NULL) {
        tempfile<<temp->id<<" "<<temp->name<<" "<<temp->start_date<<" "<<temp->end_date<<" "<<temp->duration<<" "<<temp->reason<<endl;
        temp = temp->next;
    }

    if (idFound)
    {
        tempfile.close();
        fin.close();
        remove("LEAVEAPPLY.txt");
        rename("temp.txt", "LEAVEAPPLY.txt");
        cout << "\nChange successful for Employee ID: " << id << endl;
        cout<<"\n\n\n\n\nDo you want to go back to menu page? [Y/N]: ";
		cin>>back;
		if(back=='Y'||back=='y'){
				emp.emp_menu();
			}
			while(back!= 'y' && back != 'Y')
        {
        	cout<<"Error selected please select again.";
        	cout << "\nClick [Y/y] to continue : ";
      		cin >> back;
		}
		emp.emp_menu();
    }
    else
    {
        cout << "\nEmployee ID not found." << endl;
        cout<< "Do you want to re-enter your id? [Y/N]: ";
        cin>>reenter;
        if(reenter=='Y'||reenter=='y'){
				editleave(id);
			}
			else{
                tempfile.close();
                fin.close();
                remove("LEAVEAPPLY.txt");
                rename("temp.txt", "LEAVEAPPLY.txt");
				emp.emp_menu();
			}
		
    }

}

//APPROVED LEAVE
void Approveleave::approve() {
	
	 LeaveRequest* head = nullptr;

    system("CLS");
    int num,id;
    char back;
    bool idFound = false;

    cout << "     \t======= A P P R O V E  L E A V E =======\n" << endl;

    // Read leave requests from file
    ifstream fin("LEAVEAPPLY.txt");
    if (!fin) {
        cout << "File does not exist." << endl;
        return;
    }

    while (getline(fin, line)) {
        istringstream iss(line);
        LeaveRequest* newRequest = new LeaveRequest;
        iss >> newRequest->id >> newRequest->name >> newRequest->start_date >> newRequest->end_date >> newRequest->duration >> newRequest->reason;
        newRequest->next = nullptr;

        if (head == nullptr) {
            head = newRequest;
        } else {
            LeaveRequest* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newRequest;
        }
    }
    fin.close();

    // Display leave requests
    cout << "\nLeaves awaiting approval: \n" << endl;
    cout << std::left
         << std::setw(10) << "ID"
         << std::setw(15) << "NAME"
         << std::setw(15) << "START DATE"
         << std::setw(15) << "END DATE"
         << std::setw(15) << "DURATION"
         << std::setw(20) << "REASON" << endl;

    LeaveRequest* current = head;
    while (current != nullptr) {
        cout << std::setw(10) << current->id
             << std::setw(15) << current->name
             << std::setw(15) << current->start_date
             << std::setw(15) << current->end_date
             << std::setw(15) << current->duration
             << std::setw(20) << current->reason << endl;
        current = current->next;
    }

    cout << "\n\nEnter the number of the leave(s) you want to approve: ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << "\n\nEnter the ID of the employee you want to approve: ";
        cin >> id;

        // Find leave request by ID
        LeaveRequest* temp = head;
        LeaveRequest* prev = nullptr;
        LeaveRequest* request = nullptr;
        while (temp != nullptr) {
            if (temp->id == id) {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                request = temp;
                break;
            }
            prev = temp;
            temp = temp->next;
        }

        if (request != nullptr) {
            idFound = true;
            ofstream appro("LEAVEAPPROVE.txt", ios::app);
            appro << request->id << " " << request->name << " " << request->start_date << " " << request->end_date << " " << request->duration << " " << request->reason << endl;
            appro.close();
            // Assuming `balance` function updates the balance of leave for the employee.
            // Replace the line below with the actual function call if different.
            // appr.balance(id, request->duration, request->name);
            appr.balance(request->id, request->duration, request->name);
            cout << "\nSuccessfully approved leave for employee ID: " << id << endl;
            delete request; // Free the memory allocated for the approved request
        } else {
            cout << "Leave request not found for ID: " << id << endl;
        }
    }

    // Save remaining leave requests to file
    ofstream fout("LEAVEAPPLY.txt");
    current = head;
    while (current != nullptr) {
        fout << current->id << " " << current->name << " " << current->start_date << " " << current->end_date << " " << current->duration << " " << current->reason << endl;
        LeaveRequest* temp = current;
        current = current->next;
        delete temp;
    }
    fout.close();

    cout << "\n\n\n\n\nDo you want to go back to the menu page? [Y/N]: ";
    cin >> back;
    if (back == 'Y' || back == 'y') {
        // Assuming `ad.admin_menu()` exists and is a function to go back to the admin menu.
        ad.admin_menu();
    } else {
        exit(0);
    }

    // Free the memory allocated for the remaining leave requests
    while (head != nullptr) {
        LeaveRequest* temp = head;
        head = head->next;
        delete temp;
    }
}
//Cal Balance

void Approveleave::balance(int id, int duration,string name) {

	int balance_id;
    string balance_name;
    int currentduration, balance_duration;
    string balance_line;
    ifstream fr_balance;
    fr_balance.open("BALANCE.txt");
    ofstream temp_balance;
    temp_balance.open("temp_balance.txt", ios::app);
    bool idFound = false;

    while (getline(fr_balance, balance_line)) {
        istringstream iss(balance_line);
        iss >> balance_id >> balance_name >> balance_duration;

        if (id == balance_id) {
            // Update the balance for the specific ID
            currentduration = balance_duration + duration;
            temp_balance << id << "\t" << name << "\t" << currentduration << endl;
            idFound = true;
        } else {
            // Write the existing line to the temp file
            temp_balance << balance_id << "\t" << balance_name << "\t" << balance_duration << endl;
        }
    }

    // If the ID was not found, add a new entry to the balance file
    if (!idFound) {
        temp_balance << id << "\t" << name << "\t" << duration << endl;
    }

    temp_balance.close();
    fr_balance.close();

    // Rename the temp file to overwrite the original balance file
    remove("BALANCE.txt");
    rename("temp_balance.txt", "BALANCE.txt");
}
//int main
int main(){
	admin ad;
	main_page();
	return 0;
}	
