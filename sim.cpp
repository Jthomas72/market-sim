#include <iostream>
#include <stdlib.h>
#include "pqueue.h"
#include <fstream>

using namespace std;


bool is_legal(char* str);

int main(int argc, char* argv[]){

    if(argc != 5){
        cerr << "Error: invalid number of command line arguments." << endl;
        return 1;
    }

    
    struct Checker{
        Cust* cust;
        int cash;
        int time_done;
        int on_break;
    };
    int numb_checkers = atoi(argv[1]);
    int break_time = atoi(argv[2]);
    int number;
    int checkers_avalible = numb_checkers;
    Checker checkers[numb_checkers];
    for(int i = 0; i < numb_checkers; i++){
        checkers[i].cust = NULL;
        checkers[i].cash = 100;
        checkers[i].on_break = 0;
    }

    string name;
    string type;
    int tyme;
    int items;
    int klock = 1;
    Cust* cust_ptr;
    int in_line = 0;
    int stole;

    Pqueue arrival_q;
    Pqueue shop_q;
    Pqueue check_q;

    ofstream ofile(argv[4]);
    ifstream ifile(argv[3]);


    if(!ifile){
        cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
        return 1;
    }

    if(!ofile){
        cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
        return 1;
    }

    if(numb_checkers < 1 || !is_legal(argv[1])){
        cerr << "Error: invalid number of checkers specified." << endl;
        return 1;
    }

    if(break_time < 0 || !is_legal(argv[2])){
        cerr << "Error: invalid checker break duration specified." << endl;
        return 1;
    }


    while(ifile >> name){
        ifile >> type >> tyme >> items;
        arrival_q.enqueue(new Cust(name, type, tyme, items), tyme);
    }

    while(!arrival_q.empty() || !shop_q.empty() || !check_q.empty() || in_line){
        //Customers enter the store
        while(!arrival_q.empty() && arrival_q.get_prio() == klock){
            cust_ptr = arrival_q.dequeue();
            cust_ptr->print_enter(ofile, klock);
            shop_q.enqueue(cust_ptr, cust_ptr->get_items()*3 + klock);
        }
        //Customers finish getting their items
        while(!shop_q.empty() && shop_q.get_prio() == klock){
            cust_ptr = shop_q.dequeue();
            cust_ptr->print_dshop(ofile, klock);
            check_q.enqueue(cust_ptr, 0);
        }
        //Removes customers from a checker when correct time has passed, sets money and break time if cust was a robber
        for(int i = 0; i < numb_checkers; i++){
            if(checkers[i].cust && checkers[i].time_done == klock){
                if(checkers[i].cust->is_rob()){
                    checkers[i].on_break = break_time + 1;
                    stole = checkers[i].cash;            
                    checkers[i].cash = 0;
                }
                in_line--;
                checkers[i].cust->print_fcheck(ofile, klock, i, stole);
                delete checkers[i].cust;
                checkers[i].cust = NULL;
            }
        }        


        //Decrements the time a checker is taking a break
        checkers_avalible = 0;
        for(int i = 0; i < numb_checkers; i++){
            if(checkers[i].on_break > 0){
                checkers[i].on_break -= 1;
            }
            if(!checkers[i].on_break)
                checkers_avalible++;
        }

        while(!check_q.empty() && in_line < checkers_avalible){
            for(int i = 0; i < numb_checkers; i++){
                //Places a cust into the first checker without a cust and not on a break
                if(checkers[i].cust == NULL && checkers[i].on_break == 0){
                    cust_ptr = check_q.dequeue();
                    cust_ptr->print_scheck(ofile, klock, i);
                    checkers[i].cust = cust_ptr;
                    //Checks for robber or customer, sets time and money as needed
                    if(cust_ptr->is_rob()){
                        checkers[i].time_done = klock + 7;
                        in_line++;
                        break;   
                    }
                    else{
                        checkers[i].time_done = cust_ptr->get_items()*2 + klock;
                        checkers[i].cash += cust_ptr->get_items();
                        in_line++;
                        break;
                    }
                }
            }
        }
        klock++;
    }

    for(int i = 0; i < numb_checkers; i++){
        ofile << "registers[" << i << "] = $" << checkers[i].cash*5 << endl;
    }

    ofile << "time = " << klock << endl;
    return 0;
}

bool is_legal(char* str){
    while(*str){
        if(!isdigit(*str))
            return false;
        else str++;
    }
    return true;
}
