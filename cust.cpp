#include "cust.h"


Cust::Cust(string name, string robber, int atime, int items){
    m_name = name;
    if(robber == "robber")
        m_is_rob = true;
    else
        m_is_rob = false;
    m_arrival = atime;
    m_items = items;
}

void Cust::print_enter(ostream& ofile, int tyme){
    ofile << tyme << ": " << m_name << " entered store" << endl;
}

void Cust::print_dshop(ostream& ofile, int tyme){
    ofile << tyme << ": "<< m_name << " done shopping" << endl;
}

void Cust::print_scheck(ostream& ofile, int tyme, int lane){
    ofile << tyme << ": " << m_name << " started checkout with checker " << lane << endl;
}

void Cust::print_fcheck(ostream& ofile, int tyme, int lane, int stole){
    ofile << tyme << ": " << m_name;
    if(m_is_rob){
        ofile << " stole $" << stole*5 << " and " << m_items << " item";
        if(m_items > 1)
            ofile << "s";
        ofile << " from checker " << lane << endl;
    }

    else{
        ofile << " paid $" << m_items*5 << " for " << m_items << " item";
        if(m_items > 1)
            ofile << "s";
        ofile << " to checker " << lane << endl;
    }

}
