#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <list>
using namespace std;

void display_content1()
{
    cout<<endl<<"\t\t\t<<<<<<<<<<<<<<<<<<<<< ATM MANAGEMENT SYSTEM >>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    cout<<"\t\t\t_________________________________________________________________________"<<endl;
}

void display_content2()
{

    cout<<endl<<"******************************************************************************************************"<<endl;
}
class BankAccount
{
private:
    string AccountId, name;
    double balance;
    int pin;

protected:
    BankAccount(string aId, string n, double b, int p)
        : AccountId(aId), name(n), balance(b), pin(p) {}

    void deposit(double amt)
    {
        balance += amt;
    }

    void withdraw(double amt)
    {
        if (amt > balance)
            throw runtime_error(">>>>>Insufficient amount...!!");
        else if (amt == 0.0)
            throw runtime_error(">>>>>>Invalid amount....!!");

        balance -= amt;
    }

    string getAccountId() const
    {
        return AccountId;
    }

    double getBalance() const
    {
        return balance;
    }

    int getPin() const
    {
        return pin;
    }

    virtual void Instruction() = 0; // Pure virtual function

    friend class ATM;
};

class Transactions
{
private:
    string accountId, Type;
    double tamt;

public:
    Transactions(string a, double t, string ty)
        : accountId(a), tamt(t), Type(ty) {}

    void display_Transactions() const
    {
        cout<<endl<<"ACCOUNT_Id|TYPE|TRANSACTION AMOUNT|"<<endl;
        cout <<endl<< accountId << "\t" << Type << "\t" << tamt << endl;
    }

    friend class ATM;
};

class SavingsAccount : public BankAccount
{
private:
    double minbal;

public:
    SavingsAccount(string aId, string n, double b, int p, double m)
        : BankAccount(aId, n, b, p), minbal(m)
    {
        if (b < minbal)
            throw invalid_argument(">>>>Insufficient balance");
    }

    void Instruction() override
    {
        cout << ">>>>>>This is a savings account ." << endl;
    }

    friend class ATM;
};

class CheckingAccount : public BankAccount
{
private:
    double daily_limit_amt;

public:
    CheckingAccount(const string aId, string n, double b, int p, double d)
        : BankAccount(aId, n, b, p), daily_limit_amt(d) {}

    void Instruction() override
    {
        cout << ">>>>This is a checking account ." << endl;
    }

    friend class ATM;
};

class ATM
{
public:
    int choice, upin;
    double amount;
    list<Transactions>T;

    void displaymenu()
    {
        display_content2();

        cout <<endl<< "1.Check balance" << endl;
        cout << "2. Deposit amount" << endl;
        cout << "3. Withdraw amount" << endl;
        cout << "4. Bank statement" << endl;
        cout << "5. Exit>>>>>>" << endl;
    }

    void useATM(BankAccount &a)
    {
        while (true)
        {
            cout <<endl<< "<<<<<<<<<Please insert your card.....!!" ;
            cout <<endl<< "<<<<<<<<<Please enter your pin.!!"<<endl ;
            cin >> upin;

            if (upin == a.getPin())
            {
                displaymenu();
                cout << ">>>>>>>>>>>>>>>Please press the choice:-" <<endl;
                cin >> choice;

                switch (choice)
                {
                case 1:a.Instruction();
                    cout <<endl<< "Your current Balance:- " << a.getBalance() << endl;
                    break;

                case 2:a.Instruction();
                    cout <<endl<< "Please insert the amount:-" << endl;
                    cin >> amount;
                    a.deposit(amount);
                    T.push_back(Transactions(a.getAccountId(), amount, "deposit"));
                    break;

                case 3:a.Instruction();
                    cout << "Please enter the amount to be withdrawn:-"<< endl;
                    cin >> amount;
                    try
                    {
                        a.withdraw(amount);
                        T.push_back(Transactions(a.getAccountId(), amount, "withdraw"));
                    }
                    catch (const runtime_error &e)
                    {
                        cout << e.what() << endl;
                    }
                    break;

                case 4:a.Instruction();
                    cout <<endl<< "\t\t\t<<<<<<<<<<<Bank statement>>>>>>>>>" << endl;
                    for (const auto &transaction : T)
                    {
                        transaction.display_Transactions();
                    }
                    break;

                case 5:
                    return;

                default:
                    cout << ">>>>>>>>>>>>>>Invalid choice...!!" << endl;
                    break;
                }
            }
            else
            {
                cout << "Incorrect pin...!" << endl;
            }
        }
    }
};

int main()
{
    vector<SavingsAccount> s;
    vector<CheckingAccount> c;
    ATM f;

    int choice;
    display_content1();


    try
    {   cout<<"1.Savings"<<endl<<"2.Checking account"<<endl;
        cout<<endl<<"Please enter your type of account:-"<<endl;
        cin>>choice;

        if(choice==1)
        {s.push_back(SavingsAccount("SBI@1548000048", "Mary", 10000.00, 1234, 1000.00)); // creating savings account
        f.useATM(s[0]);
        }
        else if(choice==2)
        {c.push_back(CheckingAccount("SBI@1548000049", "Jeson", 11000.00, 4567, 40000.00)); // creating current account
        f.useATM(c[0]);
        }
        else
        {
            throw invalid_argument("Invalid account choice");
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
