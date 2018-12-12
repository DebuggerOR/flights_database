#include "interface.h"
#include "MyImplementation.h"

#include <iostream>
#include <fstream>

int session_number = 0;
const char* test_file = "testing.txt";

#ifndef TEST
#define TEST
const int titles_count = 5;
const Jobs titles_array[] = { MANAGER, PILOT, FLY_ATTENDANT, NAVIGATOR, OTHER };

#endif

const int classes_count = 2;
const Classes classes_array[] = { SECOND_CLASS, FIRST_CLASS };

int model1 = 1234;
int model2 = 4321;

int crew_map_1[] = { 1, 0, 0, 1, 0 };
int crew_map_2[] = { 4, 1, 2, 0, 2 };
int crew_map_3[] = { 7, 1, 1, 1, 2 };

int classes_map_1[] = { 200, 20 };
int classes_map_2[] = { 3, 1 };

void success(int counter) {
    printf("Session %d, test %d passed\n", session_number, counter);
}
void failure(int counter, const char* ext = "")
{
    printf("Session %d, test %d failed %s\n", session_number, counter, ext);
}


map<Jobs, int> createCrewMap(int *arr)
{
    map<Jobs, int> mp;
    for (int i = 0; i < titles_count; ++i)
    {
        mp.insert(pair<Jobs, int>(titles_array[i], arr[i]));
    }

    return mp;
}

map<Classes, int> createClassesMap(int *arr)
{
    map<Classes, int> mp;
    for (int i = 0; i < classes_count; ++i) {
        mp.insert(pair<Classes, int>(classes_array[i], arr[i]));
    }
    return mp;
}

void empFactory(Ex2 *ex2, Jobs title, int num)
{
    for (int i = 0; i < num; ++i)
    {
        ex2->addEmployee(5, 1950, "", title);
    }
}

void empFactory(Ex2* ex2, map<Jobs, int> titles)
{
    for (int i = 0; i < titles_count; ++i) {
        empFactory(ex2, titles_array[i], titles[titles_array[i]]);
    }
}

void resFactory(Ex2* ex2, Classes cls, string flight_id, string cust_id, int num) {
    for (int i = 0; i < num; ++i) {
        ex2->addResevation(cust_id, flight_id, cls, 2);
    }

}

template<class T>
void* should_succeed(Ex2* ex2, T func, int test_number) {
    void* result = NULL;
    try
    {
        result = func(ex2);
        success(test_number);
    }
    catch (...)
    {
        failure(test_number);
    }
    return result;
}

template<class T>
void should_succeed_bool(Ex2* ex2, T func, int test_num)
{
    try
    {
        if (func(ex2)) {
            success(test_num);
        }
        return;
    }
    catch (...)
    {
        failure(test_num, " - WRONG EXCEPTION");
    }
    failure(test_num, " - WRONG TEST");
}

template<class T>
void should_fail(Ex2* ex2, T func, int test_number) {
    try
    {
        func(ex2);
        failure(test_number);
    }
    catch (...)
    {
        success(test_number);
    }
}


void simple_test1(Ex2* ex2)
{
    int counter = 0;
    // invalid priority
    should_fail(ex2, [](Ex2* ex2) {ex2->addCustomer("John Hayha", 7); }, counter++);
    should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addCustomer("John Hayha", 4); }, counter++);
    // add employee - no employer
    Employee* emp = (Employee*)should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addEmployee(4, 6, "", titles_array[0]); }, counter++);
    ofstream file(test_file, ios_base::trunc);
    file << emp->getID() << endl;
    file.close();
    // add plane
    should_succeed(ex2, [](Ex2* ex2) {return (void *)ex2->addPlane(model1, createCrewMap(crew_map_1), createClassesMap(classes_map_1)); }, counter++);
}

void simple_test2(Ex2* ex2)
{
    string id;
    ifstream file(test_file, ios_base::in);
    file >> id;
    file.close();

    int counter = 0;
    Employee* emp = (Employee*)should_succeed(ex2, [id](Ex2* ex2) {return (void*)ex2->addEmployee(4, 6, id, titles_array[3]); }, counter++);
    should_succeed_bool(ex2, [id, emp](Ex2* ex2) {return emp->getEmployer()->getID() == id; }, counter++);

}

void test3(Ex2* ex2)
{
    int counter = 0;
    Flight* flight = (Flight*)should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
    ofstream file(test_file, ios_base::out | ios_base::trunc);
    file << flight->getID() << endl;
    int verifier = 0;
    auto assigned_c = flight->getAssignedCrew();
    for (auto it = assigned_c.begin(); it != assigned_c.end(); ++it, ++verifier) {
        if (verifier > 2) {
            failure(counter++);
        }
        file << (*it)->getID() << endl;
    }

    file.close();
}

void test4(Ex2* ex2)
{
    int counter = 0;
    string ids[3];
    ifstream file(test_file, ios_base::in);
    for (int i = 0; i < 3; ++i) file >> ids[i];
    file.close();

    Flight* flight = (Flight*) should_succeed(ex2, [ids](Ex2* ex2) {return (void*)ex2->getFlight(ids[0]); }, counter++);
    list<Employee*> crew = flight->getAssignedCrew();
    if (crew.size() != 2)	{
        failure(counter++);
    }
    else
    {
        string ids2[2];
        auto itr = crew.begin();
        ids2[0] = (*itr++)->getID();
        ids2[1] = (*itr)->getID();

        bool check1 = (ids2[0] == ids[1]) && (ids2[1] == ids[2]);
        bool check2 = (ids2[0] == ids[2]) && (ids2[1] == ids[1]);
        if (check1 || check2) {
            success(counter++);
        }
        else {
            failure(counter++);
        }

    }

    should_fail(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
    should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-11"), "ARL", "VAN"); }, counter++);
}

void test5(Ex2* ex2)
{
    int counter = 0;
    should_succeed(ex2, [](Ex2* ex2) {empFactory(ex2, createCrewMap(crew_map_1)); return nullptr;  }, counter++);
    should_fail(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
    // NOTE THAT I SENT model1+1, so the plane is of wrong model!!
    should_succeed(ex2, [](Ex2* ex2) {return (void *)ex2->addPlane(model1+1, createCrewMap(crew_map_1), createClassesMap(classes_map_1)); }, counter++);
    should_fail(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);

    should_succeed(ex2, [](Ex2* ex2) {return (void *)ex2->addPlane(model1, createCrewMap(crew_map_1), createClassesMap(classes_map_1)); }, counter++);
    should_succeed(ex2, [](Ex2* ex2) {return (void*)ex2->addFlight(model1, Date("2019-10-10"), "ARL", "VAN"); }, counter++);
}



void(*tests[])(Ex2*) = { simple_test1, simple_test2, test3, test4, test5};
const int tests_number = 5;

class Tester {
    int session_number;
public:
    void operator()(int session_number)
    {
        Ex2* ex2 = new MyImplementation();
        tests[session_number](ex2);
        ex2->exit();
        delete ex2;
    }
};


int main(int argc, char* argv[])
{
    Date date1("2018-12-01");
    Date date2("2018-12-02");
    Date date3("2018-12-03");
    Date date4("9999-09-01");

    if(!(date1>date2)){cout<<"GOOD"<<endl;}
    else{cout<<"BAD"<<endl;}
    if(date4>date3){cout<<"GOOD"<<endl;}
    else{cout<<"BAD"<<endl;}
    if(date4>date3){cout<<"GOOD"<<endl;}
    else{cout<<"BAD"<<endl;}
    if(date2<date3){cout<<"GOOD"<<endl;}
    else{cout<<"BAD"<<endl;}
    if(date2==date2){cout<<"GOOD"<<endl;}
    else{cout<<"BAD"<<endl;}
    if(!(date1==date2)){cout<<"GOOD"<<endl;}
    else{cout<<"BAD"<<endl;}
    if(!(date4<date2)){cout<<"GOOD"<<endl;}
    else{cout<<"BAD"<<endl;}
#ifdef DELETE_FIRST
    // Make sure to delete all of your database files before
    // you start my tests! You don't want old data to interfere
#endif
    Tester t;
    for (int i = 0; i < tests_number; ++i) {
        session_number = i;
        t(i);
    }
    Ex2 *my = new MyImplementation();  // This line must work!

    Employee* e1 = my->addEmployee(2, 1994, "", MANAGER);
    Employee* e2 = my->addEmployee(2, 1914, "", MANAGER);
    Employee* e3 = my->addEmployee(2, 1094, "", MANAGER);
    Employee* e4 = my->addEmployee(2, 1900, "", MANAGER);
    Employee* e5 = my->addEmployee(3, 1994, e4->getID(), MANAGER);
    Employee* e6 = my->addEmployee(4, 1974, e4->getID(), PILOT);
    Employee* e7 = my->addEmployee(5, 1850, e4->getID(), FLY_ATTENDANT);
    Employee* e8 = my->addEmployee(7, 1950, e3->getID(), PILOT);
    Employee* e9 = my->addEmployee(1, 1840, e3->getID(), FLY_ATTENDANT);
    Employee* e10 = my->addEmployee(0, 1999, e7->getID(), NAVIGATOR);
    Employee* e11 = my->addEmployee(19, 2019, e8->getID(), NAVIGATOR);

    map<Jobs, int> crew;
    crew.insert(std::pair<Jobs, int>(MANAGER, 1));
    crew.insert(std::pair<Jobs, int>(NAVIGATOR, 1));
    crew.insert(std::pair<Jobs, int>(PILOT, 1));
    map<Classes, int> classSeats;
    classSeats.insert(std::pair<Classes, int>(FIRST_CLASS, 20));
    classSeats.insert(std::pair<Classes, int>(SECOND_CLASS, 20));
    Plane* p1 = my->addPlane(123, crew, classSeats);
    Plane* p2 = my->addPlane(153, crew, classSeats);
    Plane* p3 = my->addPlane(3333, crew, classSeats);
    Plane* p4 = my->addPlane(993, crew, classSeats);
    Plane* p5 = my->addPlane(3363, crew, classSeats);
    Plane* p6 = my->addPlane(1113, crew, classSeats);

    Customer* c1 = my->addCustomer("ori kopel", 3);
    Customer* c2 = my->addCustomer("shlomo f", 5);
    Customer* c3 = my->addCustomer("moshe f", 3);
    Customer* c4 = my->addCustomer("dowi f", 1);
    Customer* c5 = my->addCustomer("renana f", 3);
    Customer* c6 = my->addCustomer("nushnushit e", 3);

    Flight* f1 = my->addFlight(123, Date("2018-11-25"), "israel", "los angeles");
    Flight* f2 = my->addFlight(153, Date("2019-01-25"), "Poland", "greece");
    Flight* f3 = my->addFlight(3333, Date("2019-01-26"), "USA", "greece");
    Flight* f4 = my->addFlight(153, Date("2019-02-02"), "london", "israel");
    Flight* f5 = my->addFlight(993, Date("2019-01-13"), "Poland", "berlin");
    Flight* f6 = my->addFlight(1113, Date("2019-01-13"), "Poland", "berlin");
    Reservation* r1 = my->addResevation(c1->getID(), f1->getID(), FIRST_CLASS, 2);
    Reservation* r2 = my->addResevation(c1->getID(), f1->getID(), FIRST_CLASS, 2);
    Reservation* r3 = my->addResevation(c1->getID(), f1->getID(), SECOND_CLASS, 2);
    Reservation* r4 = my->addResevation(c3->getID(), f1->getID(), FIRST_CLASS, 2);

    my->exit();
    delete my;

    Ex2 *my2 = new MyImplementation();
    Customer* c = my2->addCustomer("kok f", 3);
    Employee* e = my2->addEmployee(5, 2020, "", PILOT);
    Plane* p = my2->addPlane(23, crew, classSeats);
    Flight* f = my2->addFlight(3333, Date("2014-05-08"), "givaat shmuel A", "ze good yaaad");
    Reservation* r = my2->addResevation(c->getID(), f->getID(), SECOND_CLASS, 1);

    my2->exit();
    delete my2;

    return 0;
}