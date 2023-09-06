#include<iostream>
#include<fstream>
#include<ostream>
#include<istream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<map>
#include "headerfiles/admin.h"
#include "headerfiles/faculty.h"
using namespace std;

int main()
{
    int ch;
    admin a;
    faculty f;
    cout<<""<<endl;
    cout<<""<<endl;
    cout<<"\t\t\t\t "<<"********* WELCOME TO HOME PAGE **********"<<endl;
    cout<<""<<endl;
    cout<<"\t\t\t\t 1:ADMIN"<<endl;
    cout<<"\t\t\t\t 2:FACULTY"<<endl;
    cout<<"\t\t\t\t 3:Quit"<<endl;
    cout<<""<<endl;
    cout<<"\t\t\t\t"; cin>>ch;
    switch (ch)
    {
        case 1:
                            
                cout<<"\t\t\t\t ************ WELCOME TO ADMIN LOGIN PAGE ************"<<endl;
                
                a.admin_login(); //admin login function
                
           break;
        case 2:
            
            int c;
                cout<<"\t\t\t\t ************ WELCOME TO FACULTY SIGNUP/LOGIN PAGE ************"<<endl;
                cout<<""<<endl;
                cout<<"\t\t\t\t 1:Sign up"<<endl;
                cout<<"\t\t\t\t 2:Log in"<<endl;
                cout<<"\t\t\t\t"; cin>>c;
                
                switch (c)
                {
                case 1:
                 
                    f.faculty_reg();//faculty signup function 
                    break;
                
                case 2:
                f.faculty_login(); //faculty login function
                    break;
                
                default:
                    break;
                }
            
        break;
         case 3:
                break;
        default:
            cout<<"\t\t\t\t Invalid Choice !!!!!!"<<endl;
            main();
            break;
    }
}


