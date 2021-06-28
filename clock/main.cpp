/* Jay Zinzuwadia
 * CS210-T5409
 * May 18th, 2021
 * Completed June 6th, 2021*/


#include<iostream>
#include<ctime> //required to print current time for system
#include<iomanip> //required for setw and formatting
using namespace std;

//this class is needed for the output of current time. variables are inherited from this class.
class Time {
public:
    int hour;
    int minute;
    int seconds;
};
//class for the 12 hour clock that inherits variables from the main class
class hour_12_clock:public Time {
public:
    string meridian;
    hour_12_clock()
    {
        //this code cluster allowed me to print current system time. draws variables from the class TIme
        time_t now = time(0);
        tm *ltm = localtime(&now);
        hour=ltm->tm_hour;
        minute=ltm->tm_min;
        seconds=ltm->tm_sec;

        //sets meridian to AM and PM
        if(hour>=12)
        {
            meridian = "P M";
            hour-=12;
        }
        else
            meridian = "A M";

    }

    /* This function allows the user to add hour to the current displayed clock
     * it will also roll over the meridian to PM if the user enters equivalent hours to change to the next
     * meridian */
    void add_hour(int h)
    {
        hour+=h;
        if(hour>12){
            hour-=12;
        }
        else if(hour>=12){
            if(meridian == "A M"){
                meridian = "P M";
            }
            else if(meridian == "P M"){
                meridian = "A M";
            }
        }

    }
    //add minute function. If more than 60 are added, it rolls over to hours
    void add_minute(int min)
    {
        minute+=min;
        if(minute>=60){
            int h = minute/60;
            minute -= 60*h;
            add_hour(h);
        }
    }
    //function to add seconds. if more than 60 seconds are added it rolls over to minutes
    void add_seconds(int sec){
        seconds+=sec;
        if(seconds>=60){
            int m = seconds/60;
            seconds-=60*m;
            add_minute(m);
        }
    }
};

/*class for 24 hour clock that runs the same information except accounts that the clock runs 24 hours on the hour
side and not only 12. main difference will be in the add hour function*/
class hour_24_clock:public Time {
public:
    int hour;
    int minute;
    int seconds;
    hour_24_clock(){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        hour=ltm->tm_hour;
        minute=ltm->tm_min;
        seconds=ltm->tm_sec;
    }
    //add hour function for the 24 hour format
    void add_hour(int h){
        hour+=h;
        if(hour>=24){
            hour -= 24;
        }
    }
    //add minute function. If more than 60 are added, it rolls over to hours
    void add_minute(int min){
        minute+=min;
        if(minute>=60){
            int h = minute/60;
            minute -= 60*h;
            add_hour(h);
        }
    }

    //function to add seconds. If more than 60 seconds are added it rolls over to minutes
    void add_seconds(int sec){
        seconds+=sec;
        if(seconds>=60){
            int m = seconds/60;
            seconds-=60*m;
            add_minute(m);
        }
    }
};

/*function that displays both clocks with the correct format required by ChadaTech. */
void display(hour_12_clock c1,hour_24_clock c2){
    cout << endl;
    cout<<"\t\t*************************\t\t";
    cout<<"*************************"<< endl;
    cout<<"\t\t*\t12-Hour Clock\t\t*\t";

    cout<<"\t*\t 24-Hour Clock\t\t*" << endl;

    cout<<"\t\t*\t"<<setw(2) << setfill('0')<<c1.hour<<":"<<setw(2) << setfill('0')<<c1.minute<<":"<<setw(2) <<
    setfill('0')<<c1.seconds<<" "<<c1.meridian<<"\t\t*\t";

    cout<<"\t*\t   "<<setw(2) << setfill('0')<<c2.hour<<":"<<setw(2) << setfill('0')<<c2.minute<<":"<<setw(2) <<
    setfill('0')<<c2.seconds<<"\t\t\t*" << endl;
    cout<<"\t\t*************************\t\t";
    cout<<"*************************\n";
}

int main()
{
    //assigns the 2 clock classes to c1 and c2
    hour_12_clock c1;
    hour_24_clock c2;
    //displays both clocks on screen
    display(c1,c2);
    //displays the menu until 4 is hit which is exit program
    int choice = 0;
    while(choice!=4){
        cout<<"\n\n*************************" << endl;
        cout<<"* 1 - Add One Hour\t\t*" << endl;
        cout<<"* 2 - Add One Minute\t*" << endl;
        cout<<"* 3 - Add One Second\t*" << endl;
        cout<<"* 4 - Exit Program\t\t*" << endl;
        cout<<"*************************" << endl << endl;
        cin>>choice;

        //switch function to run through menu.
        switch (choice){
            case 1: c1.add_hour(1);
                c2.add_hour(1);
                break;
            case 2: c1.add_minute(1);
                c2.add_minute(1);
                break;
            case 3: c1.add_seconds(1);
                c2.add_seconds(1);
                break;
            case 4:
                exit(0);
            default:
                cout<<"INVALID CHOICE!2" << endl;
        }

        //after each menu selection, both updated clocks are displayed
        display(c1,c2);


    }
}