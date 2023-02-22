//
//  main.cpp
//  goodcode
//
//  Created by Ben Schwartz on 10/30/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//

//basically, for this game, you start with 5 dice
//your goal is to roll five 5's, and you get three rolls to do so
//After each roll, if you get a 5, you can set it aside and roll the remaining non-5 die.
//Ex. if I rolled two 5's and three non-5's my first roll, I would only roll three die the next round
//you win if you achieve all 5's on any of the rounds
//you lose if you don't get all 5's in three rolls

//I wrote a simple recursive method to play the game, so I can simulate to find the probability of winning
//Either it's on my end or xcode's end, but this runs perfectly when i debug, but if i run without debugging
//i am getting no 'wins'. I'm not sure why this is.
//The accepted probabiluty that I calculated seperatly is between 1-3%, so I am trying to get this number

//the problem was seeding the random
//dont seed it
//im so fucking stupid

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <limits.h>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;
bool playGame(int numFives, int timesRolled)
{

    //cout << "num 5's : " << numFives << "\ttimes rolled : " << timesRolled << endl;
    //cout << "NEW" << endl;
    if(numFives == 5)
        return true;

    else if(timesRolled == 3)
        return false;


    else
    {

       //srand(21);
        int dice = 5-numFives;
        int numFivesRolled = 0;
        for(int i = 0; i < dice; i++){
            int roll = rand()%6+1;
            if(roll == 5){
               // cout<<"FIVE ROLLED"<<endl;
                numFivesRolled++;
            }
            else if(numFives == 4)
                numFivesRolled++;
//            else if(numFives == 4)
//            {
//                cout << "4 5's" << endl;
//                numFivesRolled++;
//            }
//            cout << "1. times rolled : " << timesRolled << "\t5tot : " << numFives << "\tcurrent5s : " << numFivesRolled << endl;
        }
//        cout << "2. times rolled : " << timesRolled << "\t5tot : " << numFives << "\tcurrent5s : " << numFivesRolled << endl << endl;
        return playGame(numFives+numFivesRolled, timesRolled+1);
    }
};

bool didIwin()
{
 //   bool a = playGame(0,0);
   // cout << boolalpha << "returned : " << a << endl;
   // return a;
    return playGame(0,0);
};
int main()
{
    int numRun = 3;
    int tries = 100000000;
    double pcts[numRun];
    int totWins = 0;
    for(int i = 0; i < numRun; i++)
    {


        int wins = 0;

        for(int i = 0; i < tries; i++)
        {
            bool a = didIwin();

            if(a){
                wins++; totWins++;}
            if(i % 100000 == 0){
                printf("%.1f", (i/1000000.0));
                cout <<  " mil" << endl;
            }
        }
        pcts[i] = (((double)wins) / tries);
        cout << "added" << endl;

    }

    cout << "\n\n\\*\t*\tREADY\n\n";
    cin.get();

    sleep_until(system_clock::now() + seconds(3));
    cout << "attempts : " << tries*numRun << endl;
    cout << "wins : " << totWins << endl;
    cout << "win% : " << (((double)totWins) / (tries*numRun)) << endl;
    double sum = 0;
    for(double d: pcts)
        sum += d;
    
    cout << "avg of avgs : " << (sum / numRun) << endl;
    return 0;
}


