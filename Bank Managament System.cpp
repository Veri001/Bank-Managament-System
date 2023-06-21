//=========== Header ===========//
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;
//=========== ===========//

//=========== Class Used ===========//
class account
{
    int acno;
    char name[50];
    int deposit;
    char type;
public:
    void create_account(); // Funksioni i cili merr te dhenat nga perdoruesi
    void show_account() const; // Funksioni qe shfaq te dhenat ne ekran
    void modify(); // Funksioni qe shton te dhenat e reja
    void dep(int); // Funksioni per te pranuar shumen dhe per ta shtuar ne balance
    void draw(int); // Funksioniper te pranuar shumen dhe per ta zbritur nga shuma e balances
    void report() const; // Funksioniper te shfaqur te dhenat ne format tabelare
    int retacno() const; // Funksioniper te kthyer numrin e llogarise
    int retdeposit() const; // Funksioni per te kthyer shumen e bilancit
    char rettype() const; // Funksioni per te kthyer llojin e llogarise
};
//=========== ===========//
void account::create_account()
{
    cout<<"\nVendosni Nr. e Llogarise: ";
    cin>>acno;
    cout<<"\n\nVendosni Emrin e Mbajtesit te Llogarise: ";
    cin.ignore();
    cin.getline(name, 50);
    cout<<"\nEnter Type of The Account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current): ";
    cin>>deposit;
    cout<<"\n\n\nLlogaria u Krijua...";
}

void account::show_account() const
{
    cout<<"\nNr. i Llogarise: "<<acno;
    cout<<"\nEmri i Perdoruesit te Llogarise: ";
    cout<<name;
    cout<<"\nType of Account: "<<type;
    cout<<"\nBalanca: "<<deposit;
}

void account::modify()
{
    cout<<"\nNr. i Llogarise: "<<acno;
    cout<<"\nNdryshoni Emrin e Perdoruesit te Llogarise: ";
    cin.ignore();
    cin.getline(name, 50);
    cout<<"\nModifiko Llogarin: ";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current): ";
    cin>>deposit;
}

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno() const
{
    return acno;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}
//=========== ===========//

//=========== Function Declaration ===========//
void write_account(); // Funksion per te shkruar rekord ne skedar binar
void display_sp(int); //  Funksion per te shfaqur detajet e llogarise te dhena nga perdoruesi
void modify_account(int); // Funksionper te modifikuar rekordin e skedarit
void delete_account(int); // Funksion per te fshire regjistrimin e skedarit
void display_all(); // Funksion per te shfaqur te gjitha detajet e llogarise
void deposit_whithdraw(int, int); // Funksion per te depozituar/terhequr shumen per llogarine e dhene
void intro(); // Funksion i ekranit prezantues
//=========== ===========//

//=========== Main Function Of Program ===========//
int main()
{
    char ch;
    int num;
    intro();
    do{
        system("cls");
        cout<<"\n\n\n\tMENU";
        cout<<"\n\n\t01. LLOGARI E RE";
        cout<<"\n\n\t02. DEPOSITO PARA";
        cout<<"\n\n\t03. TERHIQ PARA";
        cout<<"\n\n\t04. BALANCA";
        cout<<"\n\n\t05. LISTA E TE GJITHE PERDORUESVE";
        cout<<"\n\n\t06. MBYLL NJE LLOGARI";
        cout<<"\n\n\t07. MODIFIKO NJE LLOGARI";
        cout<<"\n\n\t08. DILNI";
        cout<<"\n\n\tZGJIDHNI NJE OPSION (1-8): ";
        cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\nVendosni Nr. e Llogarise: ";
                cin>>num;
                deposit_whithdraw(num, 1);
                break;
            case '3':
                cout<<"\n\nVendosni Nr. e Llogarise: ";
                cin>>num;
                deposit_whithdraw(num, 2);
                break;
            case '4':
                cout<<"\n\nVendosni Nr. e Llogarise: ";
                cin>>num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout<<"\n\nVendosni Nr. e Llogarise: ";
                cin>>num;
                delete_account(num);
                break;
            case '7':
                cout<<"\n\nVendosni Nr. e Llogarise: ";
                cin>>num;
                modify_account(num);
                break;
            case '8':
                cout<<"\n\nThanks for using bank managment system";
                break;
            default:
                cout<<"\nJu Lutem vendosni nje numer (1-8)";
                cout<<"\n\n          Faleminderit!";
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');

    return 0;
}
//=========== Function to Write in file ===========//
void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac),sizeof(account));
    outFile.close();
}
//=========== ===========//

//=========== Function to Read specific Record from file ===========//
void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open!! Press any Key...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if(flag == false){
        cout<<"\n\nLlogaria nuk Ekziston";
    }
}
//=========== ===========//

//=========== Function to Modify record of file ===========//
void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary | ios::in | ios::out);
    if(!File)
    {
        cout<<"File could not be open!! Press any Key...";
        return;
    }
    while(!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno() == n)
        {
            ac.show_account();
            cout<<"\n\nVendosni Detajet e reja per Llogarine"<<endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\n\t Llogaria u Perditesua";
            found = true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\n\n Record Not Found";
    }
}
//=========== ===========//

//=========== Function to Delete Record of File ===========//
void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open!! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0, ios::beg);
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char*>(&ac),sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tLlogaria u Mbyll...";
}
//=========== ===========//

//=========== Function to Display all Accounts Deposit List ===========//
void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open!! Press any Key...";
        return;
    }
    cout<<"\n\n\t\tLISTA E PERDORUESVE\n\n";
    cout<<"=============================================\n";
    cout<<"A/c Nr.      Emri        Type    Balanca\n";
    cout<<"=============================================\n";
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}
//=========== Function to Deposit and Withdraw Amounts ===========//
void deposit_whithdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary | ios::in | ios::out);
    if(!File)
    {
        cout<<"File could not be open!! Press any Key...";
        return;
    }
    while(!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno() == n)
        {
            ac.show_account();
            if(option == 1)
            {
                cout<<"\n\n\tDEPOZITO PARA";
                cout<<"\n\nVendosni Sasine Per te Depozituar";
                cin>>amt;
                ac.dep(amt);
            }
            if(option == 2)
            {
                cout<<"\n\n\tTERHIQ PARA";
                cout<<"\n\nVendosni Sasine per te Terhequr";
                cin>>amt;
                int bal = ac.retdeposit() - amt;
                if((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
                {
                    cout<<"Balanca e Pamjaftueshme";
                }else{
                    ac.draw(amt);
                }
            }
            int pos = (-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\n\t Llogaria u Perditesua";
            found = true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\n\n Record Not Found";
    }
}
//=========== ===========//

//=========== INTRODUCTION FUNCTION ===========//
void intro()
{
    cout<<"\n\n\t  BANK";
    cout<<"\n\n\t     MANAGMENT";
    cout<<"\n\n\t        SYSTEM";
    cout<<"\n\n    Press Enter to Continue";
    cin.get();
}
//=========== ===========//
