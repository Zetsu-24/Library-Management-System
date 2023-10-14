/*#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream> // file handling
#include <cstring>
#include <sstream>
#include <ctime>
#include <string.h>
#include <cstdio>
#include <iomanip>
#include <bits/stdc++.h>
#include <regex>

using namespace std;

#define N 200

int i = 0;
int j = 0;
int k1, k2, k3;
int k = 0;

string users[N];
string passed[N];

int studn[N];

string cho;

string lineu, linep, lines, temp, temp1;

class login // studdent login
{
private:
    string user;
    string pass;

public:
    int check();
    string regist();
    void dispr();
    void change_password();
    void exit();
    void append();
    int initial();
};

class book
{
private:
    int num;

public:
    void due_details();
    void check_in();
    void check_out();
    void date_enroll();
    void reset_enroll();
};

class student
{
private:
    string student_name;
    int student_id;

public:
    void add_student();
    int edit_student();
    void view_details(int w);
    void list_ofall();
    int initial();
};

// Add student to database for able to issue books

void student::add_student()
{
    cout << "-----------------" << endl;
    cout << "Enter the name of student to add: ";
    cin >> student_name;
    cout << "Enter the student ID: ";
    cin >> student_id;
    cout << "-----------------" << endl;
    fstream studentfile("student.txt", ios::app);
    studentfile << student_name << " ";
    studentfile << student_id << endl;

    studn[k] = student_id;
    studentfile.close();
    k++;
}

// view the details of a particular student

void student::view_details(int w)
{
    time_t tt;

    struct tm *ti;

    time(&tt);
    ti = localtime(&tt);
    time_t now = time(0);
    struct tm *ltm = localtime(&now);

    fstream studentfile("stu.txt", ios::in);

    cout << endl;

    int y = 0;

    while (y < k)
    {
        if (studn[y] == w)
        {
            break;
        }

        y++;
    }

    y++;

    if (y == k + 1)
    {
        cout << "-----------------" << endl;
        cout << "Not Found" << endl;
        cout << "-----------------" << endl;
    }
    else
    {
        cout << "-----------------" << endl;
        cout << "The entered ID is in line no.: " << y << endl;
        fstream studentfile("stu.txt", ios::in);
        int lineno = 0;
        do
        {
            if (lineno == y)
            {
                cout << "Student name and ID:" << lines << endl;
                cout << "-----------------" << endl;
                break;
            }

            lineno++;

        } while (getline(studentfile, lines));

        fstream file("book.txt", ios::in);
        string s;
        cout << "The list of checked out books under ID: " << w << endl;

        while (getline(file, s))
        {
            smatch matches;
            regex reg2("([0-9]+)");
            regex_search(str, matches, reg2);
            if (matches.s(1) == to_string(w))
            {
                regex reg("[0-9] + (.*)");
                sregex_iterator currentmatch(s.begin(), s.end(), reg);
                sregex_iterator lastmatch;

                while (lastmatch != currentmatch)
                {
                    smatch match = *currentmatch;
                    cout << matches.str(1) << ": " << match.str() << endl;

                    smatch mat;
                    regex rew("[0-9A-Za-z .]*([0-9][0-9]/[0-9][0-9]/[0-9][0-9][0-9][0-9])");
                    regex_search(s, mat, rew);

                    if (regex_search(s, mat, rew))
                    {
                        string z;
                        z = mat.str(1);

                        // checking for fine starts here//

                        int date1, month1, year1;
                        smatch date2;
                        smatch month2;
                        smatch year2;
                        regex reg1("([0-9][0-9])/[0-9][0-9]/[0-9][0-9][0-9][0-9]");
                        regex reg2("[0-9][0-9]/([0-9][0-9])/[0-9][0-9][0-9][0-9]");
                        regex reg3("[0-9][0-9]/[0-9][0-9]/([0-9][0-9][0-9][0-9])");
                        regex_search(z, date2, reg1);
                        regex_search(z, month2, reg2);
                        regex_search(z, year2, reg3);
                        int temp_date, temp_month, temp_year;
                        smatch matches;
                        regex reg("([0-9][0-9]/[0-9][0-9]/[0-9][0-9][0-9][0-9])");
                        regex_search(z, matches, reg);

                        if (regex_search(z, matches, reg))
                        {
                            if (stoi(year2[1]) < 1900 + ltm->tm_year)
                            {
                                cout << "---> Passed by year. Huge Fine has to be paid for this book" << endl;
                            }
                            else if (stoi(year2[1]) > 1900 + ltm->tm_year)
                            {
                                cout << "---> The check in date will come soon. No need to worry" << endl;
                            }
                            else
                            {
                                if (stoi(month2[1]) < 1 + ltm->tm_mon)
                                {
                                    cout << "---> Passed by month. Huge Fine has to be paid for this book" << endl;
                                }
                                else if (stoi(month2[1]) > 1 + ltm->tm_mon)
                                {
                                    cout << "---> The check in date will come soon. No need to worry" << endl;
                                }
                                else
                                {
                                    if (stoi(date2[1]) < ltm->tm_mday)
                                    {
                                        cout << "---> Passed by date. Fine has to be paid for the this book" << endl;
                                    }
                                    else if (stoi(date2[1]) > ltm->tm_mday)
                                    {
                                        cout << "---> The check in date will come soon. No need to worry" << endl;
                                    }
                                    else
                                    {
                                        cout << "---> The book has been issued today !!" << endl;
                                    }
                                }
                            }
                        }

                        // checking fine ends here
                    }

                    currentmatch++;
                }
            }
        }
    }

    cout << "----------------------" << endl;
    cout << endl;
    file.close();
}

// edit details of a particular student(issue or return)

int student::edit_student()
{
    cout << endl;
    int temp_id;
    cout << "----------------------" << endl;
    cout << "Enter Student ID: ";
    cin >> temp_id;
    int i = 0;

    while (i < N)
    {
        if (temp_id == studn[i])
        {
            k3 = temp_id;
            cout << "----------------------" << endl;
            cout << "1:Issue(check out) a book\n2: Return(check in) a book" << endl;
            book b;

            int choice2;
            cin >> choice2;

            switch (choice2)
            {
            case 1:
            {
                b.check_out();
                break;
            }
            case 2:
            {
                b.check_in();
                break;
            }

            default:
            {
                cout << "----------------------" << endl;
                cout << "Incorrect Entry" << endl;
                cout << "----------------------" << endl;
                break;
            }
            }

            break;
        }
        else
        {
            i++;
        }

        if (i == N)
        {
            cout << "----------------------" << endl;
            cout << "No Student Found" << endl;
            cout << "----------------------" << endl;
        }
    }

    return k3;
}

// check out of book

void book ::check_out()
{
    string book;
}*/

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <conio.h>
using namespace std;
#define el "\n"
#define sp " "

int res_book(int, int); // To check whether any book a given book no. exists or not
/*Class of books*/
class book
{
protected:
    int bno, quant; // book no
    char bname[50]; // book name
    char aname[50]; // book author's name
    char pname[50]; // publication name
public:
    void createb();
    void showb();
    void showlist();
    void assignbno(int x) // bno assigned on the basis of no
    {                     // no. of objects in file
        bno = 10001;
        bno += x - 1;
    start1:
        bno += 1;
        if (res_book(bno, 0))
            goto start1;
    }
    void set_q()
    {
        quant -= 1;
    }
    int quantity()
    {
        return quant;
    }
    void reset_q()
    {
        quant += 1;
    }
    int retbno()
    {
        return bno;
    }
};
/*End of class book*/

void book::createb() // To enter data in data members of class book
{
    int i;
    cout << "\n\t\tEnter the details:-\n";
    cout << "\n\t\tEnter Book's Name: ";
    char n[50];
    cin.getline(n, 50);
    cin.getline(bname, 50);
    for (i = 0; bname[i] != '\0'; i++)
    {
        if (bname[i] >= 'a' && bname[i] <= 'z')
            bname[i] -= 32;
    }
    cout << "\n\t\tEnter Author's Name: ";
    cin.getline(aname, 50);
    cout << "\n\t\tEnter Publication Name: ";
    cin.getline(pname, 50);
    cout << "\n\t\tEnter Book's quantity: ";
    cin >> quant;
}

void book::showb() // To display the details of books
{
    cout << "\n\t\tBook No.: " << bno << el;
    cout << "\n\t\tBook Name: " << bname << el;
    cout << "\n\t\tBook's Author Name: " << aname << el;
    cout << "\n\t\tBook's Publication: " << pname << el;
    cout << "\n\t\tBook's Quantity: " << quant << el;
}

void book::showlist() // To display book details in list form
{
    cout << "\n\t" << bno << "\t\t" << bname << "\t\t" << aname << "\t\t" << quant;
}

/*Class of Students*/
class student
{
protected:
    char name[25]; // Student name
    int bno;       // Book no. of book issued
    int token;     // To veirfy book issued or not
public:
    void creates();
    void shows();
    void showlist();
    void settoken(int x) // To set token and assign bno a book no
    {
        bno = x;
        token = 1;
    }
    void resettoken() // To reset token
    {
        bno = 0;
        token = 0;
    }
    int retbno()
    {
        return bno;
    }
    int admno; // Admission No
};
/*End of class Students*/

bool res_student(int);  // To check whether the admission no. already exist or not
void student::creates() // To enter values to all data members of class student
{
    int i;
plane:
    system("CLS");
    cout << "\n\t\tEnter the details:-\n";
    cout << "\n\t\tEnter student's Admission no: ";
    cin >> admno;
    if (res_student(admno))
    {
        cout << "\n\t\tRecord already exist with this admission no.";
        cout << "\n\t\tEnter a different admission no.\n";
        system("PAUSE");
        goto plane;
    }
    cout << "\n\t\tEnter student's Name: ";
    char n[50];
    cin.getline(n, 50);
    cin.getline(name, 25);
    for (i = 0; name[i] != '\0'; i++)
    {
        if (name[i] >= 'a' && name[i] <= 'z')
            name[i] -= 32;
    }
    bno = 0;
    token = 0;
}

void student::shows() // Show details of Students
{
    cout << "\n\t\tStudent's Admission No.: " << admno << el;
    cout << "\n\t\tStudent's Name: " << name << el;
    if (token == 1)
    {
        cout << "\n\t\tBook Issued (Book no): " << bno;
    }
}

void student::showlist() // To display Student details in list form
{
    cout << "\n\t" << admno << "\t\t" << name << "\t\t" << bno;
}

/*To Write object of class book in file*/
void write_book()
{
    book bk;
    ofstream outf("book1.bin", ios::app | ios::binary);
    outf.seekp(0, ios::end);
    int x = outf.tellp() / sizeof(book);
    bk.assignbno(x);
    bk.createb();
    bk.showb();
    outf.write(reinterpret_cast<char *>(&bk), sizeof(book));
    cout << "\n\t\tRecord added successfully";
    outf.close();
}

/*To Write object of class student in file*/
void write_student()
{
    student st;
    ofstream outf("student.bin", ios::app | ios::binary);
    outf.seekp(0, ios::end);
    st.creates();
    st.shows();
    outf.write(reinterpret_cast<char *>(&st), sizeof(student));
    cout << "\n\t\tRecord added successfully";
    outf.close();
}

/*To display Student records in list form*/
void list_student()
{
    system("CLS");
    student st;
    ifstream intf("student.bin", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        cout << "\n\t*****Students Details*****\n\n";
        cout << "\n\tAdmission No:\tName: \tBook Issued:";
        while (intf.read(reinterpret_cast<char *>(&st), sizeof(student)))
            st.showlist();
    }
    intf.close();
}

/*To display book records in list form*/
void list_book()
{
    book bk;
    ifstream intf("book1.bin", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        cout << "\n\t*****Books Details*****\n\n";
        cout << "\n\tBook No:\t\tName: \t\tAuthor's Name: \t\tQuantity: ";
        while (intf.read(reinterpret_cast<char *>(&bk), sizeof(book)))
            bk.showlist();
    }
    intf.close();
}

/*To search for a specific student*/
void search_student(int x)
{
    student st;
    int cnt = 0;
    ifstream intf("student.bin", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        while (intf.read(reinterpret_cast<char *>(&st), sizeof(student)))
        {
            if (st.admno == x)
            {
                cnt++;
                cout << "\n\t\tFILE FOUND!!!!";
                st.shows();
                break;
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists";
    }
    intf.close();
}

/*To search for a specific book*/
void search_book(int x)
{
    book bk;
    int cnt = 0;
    ifstream intf("book1.bin", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        while (intf.read(reinterpret_cast<char *>(&bk), sizeof(book)))
        {
            if (bk.retbno() == x)
            {
                cnt++;
                cout << "\n\t\tFILE FOUND!!!!";
                bk.showb();
                break;
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists";
    }
    intf.close();
}

/*To modify the book records*/
void modify_book(int x)
{
    book bk;
    int cnt = 0;
    fstream intf("book1.bin", ios::in | ios::out | ios::ate | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        while (intf.read(reinterpret_cast<char *>(&bk), sizeof(book)))
        {
            if (bk.retbno() == x)
            {
                cnt++;
                bk.createb();
                bk.showb();
                intf.seekp(intf.tellp() - sizeof(book));
                intf.write(reinterpret_cast<char *>(&bk), sizeof(book));
                cout << "\n\t\tRecord Updated";
                break;
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists";
    }
    intf.close();
}

/*To modify the student records*/
void modify_student(int x)
{
    student st;
    int cnt = 0;
    fstream intf("student.bin", ios::in | ios::out | ios::ate | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        while (intf.read(reinterpret_cast<char *>(&st), sizeof(student)))
        {
            if (st.admno == x)
            {
                cnt++;
                st.creates();
                st.shows();
                intf.seekp(intf.tellp() - sizeof(student));
                intf.write(reinterpret_cast<char *>(&st), sizeof(student));
                cout << "\n\t\tRecord Updated";
                break;
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists";
    }
    intf.close();
}

/*To delete a specific student record*/
void delete_student(int x)
{
    student st;
    int cnt = 0;
    ifstream intf("student.bin", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("temp.bin", ios::app | ios::binary);
        while (intf.read(reinterpret_cast<char *>(&st), sizeof(student)))
        {
            if (st.admno == x)
                cnt++;
            else
                outf.write(reinterpret_cast<char *>(&st), sizeof(student));
        }
        intf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("temp.bin");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("student.bin");
            rename("temp.bin", "student.bin");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
}

/*To delete a specific book record*/
void delete_book(int x)
{
    book bk;
    int cnt = 0;
    ifstream intf("book1.bin", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        cout << "\n\t\tFile not found";
    else
    {
        ofstream outf("temp1.bin", ios::app | ios::binary);
        while (intf.read(reinterpret_cast<char *>(&bk), sizeof(book)))
        {
            if (bk.retbno() == x)
                cnt++;
            else
                outf.write(reinterpret_cast<char *>(&bk), sizeof(book));
        }
        intf.close();
        outf.close();
        if (cnt == 0)
        {
            remove("temp1.bin");
            cout << "\n\t\tNo such record exists";
        }
        else
        {
            remove("book.bin");
            rename("temp1.bin", "book.bin");
            cout << "\n\t\tRecord deleted successfully";
        }
    }
}

// To search whether a specific student record exists or not
bool res_student(int x)
{
    student st;
    int cnt = 0, f = 0;
    ifstream intf("student.bin", ios::in | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        f = 1;
    else
    {
        while (intf.read(reinterpret_cast<char *>(&st), sizeof(student)))
        {
            if (st.admno == x)
            {
                cnt++;
                break;
            }
        }
        if (cnt == 0)
            f = 1;
    }
    intf.close();
    if (f)
        return 0;
    else
        return 1;
}

/*To search a specific book and return true or false*/
int res_book(int x, int z)
{
    book bk;
    int cnt = 0, f = 1;
    fstream intf("book1.bin", ios::in | ios::out | ios::ate | ios::binary);
    intf.seekg(0, ios::beg);
    if (!intf)
        f = 0;
    else
    {
        while (intf.read(reinterpret_cast<char *>(&bk), sizeof(book)))
        {
            if (bk.retbno() == x)
            {
                cnt++;
                if (z == 1)
                {
                    bk.showb();
                    if (bk.quantity() > 0)
                    {
                        bk.set_q();
                        intf.seekp(intf.tellp() - sizeof(book));
                        intf.write(reinterpret_cast<char *>(&bk), sizeof(book));
                    }
                    else
                        f = 2;
                }
                else if (z == 2)
                {
                    bk.showb();
                    bk.reset_q();
                    intf.seekp(intf.tellp() - sizeof(book));
                    intf.write(reinterpret_cast<char *>(&bk), sizeof(book));
                }
                break;
            }
        }
        if (cnt == 0)
            f = 0;
    }
    intf.close();
    return f;
}

/*To issue books*/
void book_issue()
{
    int sn, bn;
    system("CLS");
    cout << "\n\n\t\t*****BOOK ISSUE******";
    cout << "\n\n\t\tEnter the student's admission no: ";
    cin >> sn;
    int cnt = 0;
    student st;
    fstream outf("student.bin", ios::in | ios::out | ios::ate | ios::binary);
    outf.seekg(0, ios::beg);
    if (!outf)
        cout << "\n\t\tFile not found\n";
    else
    {
        while (outf.read(reinterpret_cast<char *>(&st), sizeof(student)))
        {
            if (st.admno == sn)
            {
                cnt++;
                list_book();
                cout << "\n\n\t\tEnter the book no.:";
                cin >> bn;
                cout << "\n";
                int flag = res_book(bn, 1);
                if (flag == 1)
                {
                    st.settoken(bn);
                    outf.seekp(outf.tellp() - sizeof(student));
                    outf.write(reinterpret_cast<char *>(&st), sizeof(student));
                    cout << "\n\t\tBook Issued";
                    cout << "\n\t\tNote: Write the current date in backside of the book";
                    cout << "\n\t\t      Should be submitted within 15 days to avoid fine";
                    cout << "\n\t\t      The fine is Rs. 1 for each day after 15 days period\n";
                    break;
                }
                else if (flag == 2)
                {
                    cout << "\n\t\tTHE BOOK IS OUT OF STOCK!!!";
                    break;
                }
                else
                {
                    cout << "\n\t\tNo such record exists\n";
                    break;
                }
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists\n";
    }
    outf.close();
}

/*To deposit books*/
void book_deposit()
{
    int sn, bn;
    system("CLS");
    cout << "\n\n\t\t*****BOOK DEPOSIT******";
    cout << "\n\n\t\tEnter the student's admission no: ";
    cin >> sn;
    int cnt = 0;
    student st;
    fstream outf("student.bin", ios::in | ios::out | ios::ate | ios::binary);
    outf.seekg(0, ios::beg);
    if (!outf)
        cout << "\n\t\tFile not found\n";
    else
    {
        while (outf.read(reinterpret_cast<char *>(&st), sizeof(student)))
        {
            if (st.admno == sn)
            {
                cnt++;
                bn = st.retbno();
                bool flag = res_book(bn, 2);
                if (flag)
                {
                    st.resettoken();
                    outf.seekp(outf.tellp() - sizeof(student));
                    outf.write(reinterpret_cast<char *>(&st), sizeof(student));
                    int days;
                    cout << "\n\t\tBook deposited in no. of days:";
                    cin >> days;
                    if (days > 15)
                    {
                        int fine = (days - 15) * 1;
                        cout << "\n\n\t\tFine: " << fine << el;
                    }
                    cout << "\n\t\tBook Deposited Successfully\n";
                    break;
                }
                else
                {
                    cout << "\n\t\tNo such record exists\n";
                    break;
                }
            }
        }
        if (cnt == 0)
            cout << "\n\t\tNo such record exists\n";
    }
    outf.close();
}

/*Function that has features of Admin Menu*/
void admin_menu()
{
fine:
    system("PAUSE");
    system("CLS");
    int opt;
    cout << "\n\n\n\t\t\t******ADMINISTRATOR MENU******";
    cout << "\n\n\t1.\tCREATE STUDENT RECORD";
    cout << "\n\n\t2.\tDISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3.\tDISPLAY SPECIFIC STUDENT RECORD ";
    cout << "\n\n\t4.\tMODIFY STUDENT RECORD";
    cout << "\n\n\t5.\tDELETE STUDENT RECORD";
    cout << "\n\n\t6.\tCREATE BOOK ";
    cout << "\n\n\t7.\tDISPLAY ALL BOOKS ";
    cout << "\n\n\t8.\tDISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t9.\tMODIFY BOOK ";
    cout << "\n\n\t10.\tDELETE BOOK ";
    cout << "\n\n\t11.\tBACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-11) ";
    cin >> opt;
    if (opt == 1)
    {
        system("CLS");
        write_student();
        cout << el;
        goto fine;
    }
    else if (opt == 2)
    {
        system("CLS");
        list_student();
        cout << el;
        goto fine;
    }
    else if (opt == 3)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the admission no. of the student";
        cin >> ad;
        search_student(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 4)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the admission no. of the student";
        cin >> ad;
        modify_student(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 5)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the admission no. of the student";
        cin >> ad;
        delete_student(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 6)
    {
        system("CLS");
        write_book();
        cout << el;
        goto fine;
    }
    else if (opt == 7)
    {
        system("CLS");
        list_book();
        cout << el;
        goto fine;
    }
    else if (opt == 8)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the book no. of the book";
        cin >> ad;
        search_book(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 9)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the book no. of the book";
        cin >> ad;
        modify_book(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 10)
    {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the book no. of the book";
        cin >> ad;
        delete_book(ad);
        cout << el;
        goto fine;
    }
    else if (opt == 11)
        return;
    else
    {
        cout << "\n\t\tEnter correct option";
        cout << el;
        goto fine;
    }
}

/*Checks for correct password*/
// The password if predefined and has to be changed through the source code
// of application
bool passwords()
{
    int i = 0;
    char ch, st[21], ch1[21] = {"0000"};
    cout << "\n\n\t\tEnter Password : ";
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            st[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            cout << "\b \b";
        }
        else
        {
            cout << "*";
            st[i] = ch;
            i++;
        }
    }
    for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++)
        ;
    if (st[i] == '\0' && ch1[i] == '\0')
        return 1;
    else
        return 0;
}

// Main function
int main()
{
    cout << "\n\n\t\t\t*******************************************";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t*******************************************";
    bool a = passwords();
    if (!a)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "\nWrong password";
            cout << "\nYou have " << 2 - i << "attempts left";
            if (passwords())
                goto last;
            if (i == 1)
            {
                cout << "\n\n\n\t\t\t All attempts failed........";
                cout << "\n\n\t\t\t Sorry, but you can't login";
                exit(0);
            }
        }
    }
last:
    cout << "\n\n";
start:
    system("PAUSE");
    system("CLS");
    int opt;
    cout << "\n\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\n\t\t\tWhat do you want to do?";
    cout << "\n\t\t\t1.\tBOOK ISSUE";
    cout << "\n\t\t\t2.\tBOOK DEPOSIT";
    cout << "\n\t\t\t3.\tADMINISTRATOR MENU";
    cout << "\n\t\t\t4.\tExit";
    cout << "\n\n Choose your option: ";
    cin >> opt;
    if (opt == 1)
    {
        system("CLS");
        book_issue();
        goto start;
    }
    else if (opt == 2)
    {
        system("CLS");
        book_deposit();
        goto start;
    }
    else if (opt == 3)
    {
        admin_menu();
        goto start;
    }
    else if (opt == 4)
        exit(0);
    else
    {
        cout << "\n\t\tEnter correct option";
        goto start;
    }
}