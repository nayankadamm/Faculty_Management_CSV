#include<iostream>
#include<fstream>
#include<ostream>
#include<istream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<map>
#include "headerfiles/faculty.h"
using namespace std;
//this is the method  to check the username already exists or not in the database while doing signup
bool isUsernameExist(string username) {
    ifstream file("./Database/FacultyData.csv");
    
    string line;

    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            return true;
        }
    }

    return false;
}


   
    string faculty_unique_id; //this is private unique for each faculty
    
   
bool faculty:: faculty_reg() {
    
    string username, password, technology;
    int randomNumber;

    // check if a username already exists in the CSV file
    bool (*isUsernameExist)(string) = &::isUsernameExist;

    while (true) {
        // get user input for username, password, and technology
        cout << "Enter your username: ";
       cin>>username;

        // check if the username already exists in the CSV file
        if (isUsernameExist(username)) {
            cout << "Username already exists. Please enter a different username." << endl;
        } else {
            break;
        }
    }

    cout << "Enter your password: ";
   cin>>password;

    cout << "Enter your technology: ";
    cin>>technology;

    // generate a random number for the each faculty while signup 
    srand(time(0));
   randomNumber= rand() % 9000 + 1000;
   

    // open the CSV file in append mode
    ofstream file("./Database/FacultyData.csv", ios::app);

    // add the user data to the CSV file
    file << username << "," << password << "," << technology << "," << randomNumber << endl;

    // close the file
    file.close();

    cout << "User created successfully!" << endl;
    faculty_login();

    return true;
}
    void faculty:: faculty_login()
    {
        //faculty login
    string username, password, line;
    ifstream file("./Database/FacultyData.csv");
    bool found = false;
    cout << "\t\t\t\t Enter your username: ";
    cin >> username;
    cout << "\t\t\t\t Enter your password: ";
    cin >> password;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp_username, temp_password,tech,id;
        getline(ss, temp_username, ',');
        getline(ss, temp_password, ',');
         getline(ss, tech, ',');
          getline(ss, id, ',');
        if (temp_username == username && temp_password == password) 
        {
            found = true;
             faculty_unique_id=id; 
            break;
        }
    }
    if (found) {
        cout << "\t\t\t\t Login successful!" << endl;
       
        faculty_work();
    } else {
        cout << "\t\t\t\t Invalid username or password." << endl;
        faculty_login();
    }
    };
    void faculty:: faculty_work()
    {
        //faculty work
        int ch;
        cout<<"\t\t\t\t Enter Choice"<<endl;
        cout<<"\t\t\t\t 1:Get Schedule"<<endl;
        cout<<"\t\t\t\t 2:Accept/Cancel Schedule"<<endl;
        cout<<"\t\t\t\t 3:Quit"<<endl;
        cout<<"\t\t\t\t"; cin>>ch;
        switch (ch)
        {
        case 1:
                cout<<"\t\t\t\t 1:Get Schedule"<<endl;
                get_shedule();

            break;
        case 2:
                cout<<"\t\t\t\t 2:Accept/Cancel Schedule"<<endl;
                cancle_shedule();
            break;
        case 3:
                cout<<"\t\t\t\t 3:Quit"<<endl;

            break;    
        
        default:
            break;
        }
    }  
    void faculty:: get_shedule()
{
    //get shedule of the faculty
  vector<string>record;
  ifstream file;
  file.open("./Database/AdminAllocatedShedule.csv");
  bool found_record = false;
  string f_name;
  string l_name;
  string number;
  cout<<""<<endl;
  
  while(getline(file,f_name, ','))
  {
      getline(file,l_name);
      if(f_name==faculty_unique_id)
      {
        found_record=true;
        record.push_back(f_name);
        record.push_back(l_name);
      }
  }
  cout<<""<<endl;
  for(int i=0;i<record.size();i+=2)
  {
    
    cout<<"\t\t\t\t"<<record[i]<<" "<<record[i+1]<<endl;
  }
    cout<<""<<endl;
    faculty_work();
            }
int faculty:: cancle_shedule()
{           
    //accept and cancle shedule
  vector<string>record;
  ifstream file;
  file.open("./Database/AdminAllocatedShedule.csv");
  bool found_record = false;
  string f_name;
  string l_name;
  string number;
  cout<<""<<endl;

  while(getline(file,f_name, ','))
  {
      getline(file,l_name);
      if(f_name==faculty_unique_id)
      {
        found_record=true;
        record.push_back(f_name);
        record.push_back(l_name);
      }
  }
  cout<<""<<endl;
  for(int i=0;i<record.size();i+=2)
  {
   
    cout<<"\t\t\t\t"<<record[i]<<" "<<record[i+1]<<endl;
  }
    cout<<""<<endl;
    string filename = "./Database/AdminAllocatedShedule.csv";
    ifstream fin(filename.c_str());
    if (!fin) {
        cout << "File not found!" << endl;
        return 1;
    }
    vector<vector<string> > data;
    string line;
    while (getline(fin, line))
     {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) 
        {
            row.push_back(cell);
        }
        data.push_back(row);
    }
     string str1;
     int n;
      string search_value;
    cout<<"\t\t\t\t Enter the batch id"<<endl;
     cout<<"\t\t\t\t"; cin>>search_value;
    
    cout<<"\t\t\t\t Enter the choice::"<<endl;
    cout<<"\t\t\t\t 1:Accept the schedule"<<endl;
    cout<<"\t\t\t\t 2:Reject the schedule"<<endl;
    cout<<"\t\t\t\t";cin>>n;   
switch (n)
{
case 1:
cout<<endl;
    cout<<"\t\t\t\tSchedule Accepted "<<endl;
    cout<<endl;
    str1="Accepted";
    break;
case 2:
cout<<endl;
    cout<<"\t\t\t\tSchedule Rejected"<<endl;
    cout<<endl;
    str1 ="Rejected";
default:
    break;
}
   int flag=0;
    for (vector<vector<string> >::size_type i = 0; i < data.size(); i++) 
    {
        if (data[i][1] == search_value) 
        { 
           flag=1;
            data[i][9] = str1;
            ofstream fout(filename.c_str());
            for (vector<vector<string> >::size_type j = 0; j < data.size(); j++) 
            {
                for (vector<string>::size_type k = 0; k < data[j].size(); k++)
                 {
                    fout << data[j][k];
                    if (k != data[j].size() - 1) 
                    {
                        fout << ",";
                    }
                }
                fout << endl;
            }
            fout.close();
            break; 
        }
    }
    if(flag==0)
    {
        cout<<"\t\t\t\tEntered wrong batch id"<<endl;
    }                          
faculty_work();
            }       
