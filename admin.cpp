#include<iostream>
#include<fstream>
#include<ostream>
#include<istream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<map>
#include<regex>
#include "headerfiles/admin.h"
using namespace std;
struct Node {
    //struct for the linked list used in allocat_shedule function to get the data
    //from the admincreatedData 
    int id;
    string tech,d1,d,d2,location,f;
    Node* next;
};

    void admin:: admin_login()
    {   
        int exist;
        string user,pass,u,p;
        cout<<"\t\t\t\t Enter Username::"; //admin username
        cin>>user;
        
        cout<<"\t\t\t\t Enter Password::"; //admin password
        cin>>pass;
        ifstream input("./Database/AdminCreds.csv");
        //checking if entered creds does match or not from the database
        while(input>>u>>p)
        {
            if(u==user&&p==pass)
            {
                exist=1;
            }
            
        }
        input.close();
        //if creds match then it will go to admin_work panel
        if(exist==1)
        {
            cout<<"\t\t\t\t Logged in Successfully"<<endl;
            admin_work();
        }
        //if not then it will ask to login again
        else
        {
            cout<<"\t\t\t\t Invalid Username or Password"<<endl;
            admin_login();
        }
    };
   void admin:: admin_work()
   {
    //admin work panel
    //each case have different function calling in it according to user input
        int ch;
        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"\t\t\t\t Enter the choice"<<endl;
        cout<<""<<endl;
        cout<<"\t\t\t\t 1:Create a new training Schedule"<<endl;
        cout<<"\t\t\t\t 2:Update the schedule"<<endl;
        cout<<"\t\t\t\t 3:Allocate schedule to a specific trainer"<<endl;
        cout<<"\t\t\t\t 4:Generate the report"<<endl;
        cout<<"\t\t\t\t 5:Quit Application"<<endl;
        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"\t\t\t\t"; cin>>ch;
        switch (ch)
        {
        case 1:
            cout<<"\t\t\t\t create a new training schedule "<<endl;
            create_schedule();
            break;
        case 2:
            cout<<"\t\t\t\t Update the schedule"<<endl;
            update_schedule();
            break;
        case 3:
            cout<<"\t\t\t\t Allocate schedule to a specific trainer"<<endl;
            allocate_schedule();
            break;
        case 4:
        cout<<endl;
            cout<<"\t\t\t\t *********** REPORT ***********"<<endl;
            cout<<endl;
            cout<<"\t\t\t\t Technology       Month       Batches"<<endl;
            generate_report();
            break;
        case 5:

            cout<<"\t\t\t\t Quit Application"<<endl;
            break;
        default:
                cout<<"\t\t\t\t Invalid choice"<<endl;
                admin_work();
            break;
        }

   }
   void admin:: create_schedule() {
    string technology, f_details, date1, date2, venue_details, month;
    int batch_id, days;
//creating the schedule in the and updating it in the csv file
    try {
        cout << "\t\t\t\tEnter batch id" << endl;
        cout << "\t\t\t\t";
        cin >> batch_id;
        cout << "\t\t\t\tEnter technology" << endl;
        cout << "\t\t\t\t";
        cin >> technology;
    //validations for the start date 
       while(true){
            cout<<"\t\t\t\t Enter start Date: ";
            cin>>date1;
            if(!regex_match(date1, regex("\\d{2}-\\d{2}-\\d{4}"))){
                cout<<"\t\t\t\t Invalid input. Date must be in the format 'DD-MM-YYYY'.\n";
            }
            else{
                break;
            }
        }

         cout << "\t\t\t\tEnter Number of Days" << endl;
        cout << "\t\t\t\t";
        cin >> days;
//validations for the end date
        while(true){
            cout<<"\t\t\t\t Enter End Date: ";
            cin>>date2;
            if(!regex_match(date2, regex("\\d{2}-\\d{2}-\\d{4}"))){
                cout<<"\t\t\t\t Invalid input. Date must be in the format 'DD-MM-YYYY'.\n";
            }
            else{
                break;
            }
        }

       
    

        cout << "\t\t\t\tEnter venue" << endl;
        cout << "\t\t\t\t";
        cin >> venue_details;
        cout << "\t\t\t\tEnter month" << endl;
        cout << "\t\t\t\t";
        cin >> month;
//writing the admin input data in csv file
//if succesfully write the data it will go again to admin_work panel
        ofstream file("./Database/AdminCreatedData.csv", ios::app | ios::app);
        file << batch_id << ',' << technology << ',' << date1 << ',' << days << ',' << date2 << ',' << venue_details << ',' << month << endl;
        cout << "" << endl;
        cout << "\t\t\t\tSchedule Created successfully" << endl;
        file.close();
        admin_work();
    } catch (const exception &e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}

   int admin:: update_schedule() {
    string filename = "./Database/AdminAllocatedShedule.csv";

    //first to update the schedule we need to check which data we need to update so
    //first we will print the whole data on the screen and will update it by row and column wise
    try {
        ifstream file(filename);
        if (!file) {
            throw "File not found!";
        }

        
        vector<vector<string> > d;
        string l;
        while (getline(file, l)) {
            vector<string> row;
            stringstream ss(l);
            string cell;
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            d.push_back(row);
        }

        for (size_t i = 0; i < d.size(); i++) {
            cout << "\t\t\t\t";
            for (size_t j = 0; j < d[i].size(); j++) {
                cout << d[i][j] << "\t";
            }
            cout << endl;
        }

        ifstream fin(filename.c_str());
        if (!fin) {
            throw "File not found!";
        }

        //adding the whole csv data to vector array to update it
        vector<vector<string> > data;
        string line;
        while (getline(fin, line)) {
            vector<string> row;
            stringstream ss(line);
            string cell;
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            data.push_back(row);
        }
        
    //updating the data 
        int row, col;
        string value;
        cout << "\t\t\t\t Enter the row number you want to update: " << endl;
        cout << "\t\t\t\t"; cin >> row;
        cout << "\t\t\t\t Enter the column number you want to update: " << endl;
        cout << "\t\t\t\t"; cin >> col;
        cout << "\t\t\t\t Enter the new value: ";
        cin.ignore();
        getline(cin, value);

        data[row - 1][col - 1] = value;

        ofstream fout(filename.c_str());
        for (vector<vector<string> >::size_type i = 0; i < data.size(); i++) {
            for (vector<string>::size_type j = 0; j < data[i].size(); j++) {
                fout << data[i][j];
                if (j != data[i].size() - 1) fout << ",";
            }
            fout << endl;
        }

        cout << "\t\t\t\t CSV file updated!" << endl;
        int n;
        cout << "\t\t\t\t 1:Admin dashboard" << endl;
        cout << "\t\t\t\t 2:Update more" << endl;
        cout << "\t\t\t\t"; cin >> n;
        if (n == 1) {
            admin_work();
        }
        else if (n == 2) {
            update_schedule();
        }
        else {
            cout << "\t\t\t\t Invalid choice";
        }
    }
    catch (const char* msg) {
        cerr << "\t\t\t\t Exception: " << msg << endl;
        return 1;
    }

    return 0;
}

void admin:: allocate_schedule(){
    //now to allocate the data first we need to check the shedules admin have created
    //so to print the data on the screen singley linked list is used for it
    string fileName = "./Database/AdminCreatedData.csv";
      Node* head = nullptr;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int id;
        string tech,d1,d,d2,location,f;
       
      
       
        getline(ss, token, ',');
          id = stoi(token);
         getline(ss, tech, ',');
          getline(ss, d1, ',');
           getline(ss, d, ',');
            getline(ss, d2, ',');
             getline(ss, location, ',');
         getline(ss, f, ',');
        
         
        

        Node* newNode = new Node;
       
        newNode->id = id;
        newNode->tech = tech;
        newNode->d1 = d1;
        newNode->d = d;
        newNode->d2 = d2;
        newNode->location = location;
        newNode->f = f;
       

        
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    file.close();

    // print the contents of the linked list
    Node* current = head;
    while (current != nullptr) {
        cout << current->id << ", " << current->tech <<", " << current->d1 <<", " << current->d <<", " << current->d2 <<", " 
        << current->location <<", " << current->f << endl;
        current = current->next;
       
    
    }

    // free the memory used by the linked list
    current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
  
//allocating the schedule to specific trainer
    string technology, f_details, date1, date2, venue_details, month, status;
    int batch_id, uniqueId,days;

    try{
        cout<<"\t\t\t\t Enter Unique Id of the Faculty: ";
        cin>>uniqueId;

        if(cin.fail()){
            throw runtime_error("Invalid input. Please enter a valid integer value.");
        }

        cout<<"\t\t\t\t Enter batch id: ";
        cin>>batch_id;

        if(cin.fail()){
            throw runtime_error("Invalid input. Please enter a valid integer value.");
        }

        cout<<"\t\t\t\t Enter technology: ";
        cin>>technology;

        while(true){
            cout<<"\t\t\t\t Enter start Date: ";
            cin>>date1;
            if(!regex_match(date1, regex("\\d{2}-\\d{2}-\\d{4}"))){
                cout<<"\t\t\t\t Invalid input. Date must be in the format 'DD-MM-YYYY'.\n";
            }
            else{
                break;
            }
        }
           cout<<"\t\t\t\t Enter days: ";
        cin>>days;
        while(true){
            cout<<"\t\t\t\t Enter End Date: ";
            cin>>date2;
            if(!regex_match(date2, regex("\\d{2}-\\d{2}-\\d{4}"))){
                cout<<"\t\t\t\t Invalid input. Date must be in the format 'DD-MM-YYYY'.\n";
            }
            else{
                break;
            }
        }

        cout<<"\t\t\t\t Enter venue: ";
        cin>>venue_details;

        cout<<"\t\t\t\t Enter faculty details: ";
        cin>>f_details;

        cout<<"\t\t\t\t Enter Month:";
        cin>>month;

        cout<<"\t\t\t\t Enter status: ";
        cin>>status;

        ofstream reg("./Database/AdminAllocatedShedule.csv", ios::app);
        reg<<uniqueId<<','<<batch_id<<','<<technology<<','<<date1<<','<<days<<','<<date2<<','<<venue_details<<','<<f_details<<','<<month<<','<<status<<endl;
        cout<<"\t\t\t\t Schedule created successfully"<<endl;
        admin_work();
    }
    catch(exception& ex){
        cerr<<ex.what()<<endl;
    }
}

   void admin:: generate_report() {
    //here we are generating report on the  basis of montht and technology
    try {
        vector<vector<string> > v;
        ifstream file("./Database/AdminCreatedData.csv");
        if (!file) {
            throw runtime_error("Error opening file");
        }
         string id;
            string technology;
            string startdate;
            string endDate;
            string venue;
            string month;
            string days;
            string status;
   
    int i=0;
    // adding the technology and month from each row of the csv file vector array
    while(file.good())
    {  
            getline(file,id,','); 
            getline(file,technology,',');
            getline(file,startdate,',');
            getline(file,days,',');
            getline(file,endDate,',');
            getline(file,venue,',');
            getline(file,month ,'\n');
            
     	

            v.push_back(vector<string>());
            for(int j=0;j<1;j++)
            {  	
                
                
                v[i].push_back(technology);
                
                v[i].push_back(month);
            }	
            i++;
    }

// printing the technology and month with count of similarity 

   map<vector<string>, int> freq;
    for (vector<string> a : v) {
        freq[a]++;
    }
    for (pair<vector<string>, int> p : freq)
    {
        cout<<"\t\t\t\t";
        for (string x : p.first) {
            cout<< x << "\t\t";
        }
        cout<< p.second << endl;
    }
 admin_work();
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}  
