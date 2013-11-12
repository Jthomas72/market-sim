#ifndef CUST_H
#define CUST_H
#include <fstream>
#include <iostream>
using namespace std;
class Cust{
public:
    Cust(string name, string robber, int atime, int items);
    void print_enter(ostream& ofile, int tyme);
    void print_dshop(ostream& ofile, int tyme);
    void print_scheck(ostream& ofile, int tyme, int lane);
    void print_fcheck(ostream& ofile, int tyme, int lane, int stole);

    int get_items() {return m_items;}
    bool is_rob() {return m_is_rob;}

private:
    string m_name;
    bool m_is_rob;
    int m_arrival;
    int m_items;
};
#endif
