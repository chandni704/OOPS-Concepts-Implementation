#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

void display_content1()
{
    cout<<endl<<"\t\t\t<<<<<<<<<<<<<<<<<<<<< PORTFOLIO MANAGEMENT SYSTEM >>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    cout<<"\t\t\t_________________________________________________________________________"<<endl;
}

void display_content2()
{

    cout<<endl<<"******************************************************************************************************"<<endl;
}

// Base class: Stock
class Stock {
public:
    virtual void show() const = 0; // pure virtual function
    virtual ~Stock() {}
};

// Derived class: Equity
class Equity : public Stock {
    string name;
    double price;
public:
    Equity(const string& n, double p) : name(n), price(p) {}
    void show() const override {

        cout<<endl << "Stock: " << name << ", Price: " << price << endl<<endl;;
    }
};

// Derived class: Bond
class Bond : public Stock {
    string issuer;
    double interestRate;
public:
    Bond(const string& i, double r) : issuer(i), interestRate(r) {}
    void show() const override {
        cout << "Bond: " << issuer << ", Interest Rate: " << interestRate << "%" << endl<<endl;;
    }
};

// Portfolio class that manages different stocks using smart pointers
class Portfolio {
    vector<shared_ptr<Stock>> stocks;
public:
    void addStock(const shared_ptr<Stock>& stock) {
        stocks.push_back(stock);
    }
    void showPortfolio() const {
        for (const auto& stock : stocks) {
            stock->show();
        }
    }
};

// Template function to create and add stocks to the portfolio
template <typename T, typename... Args>
void createAndAddStock(Portfolio& portfolio, Args&&... args) {
    portfolio.addStock(make_shared<T>(forward<Args>(args)...));
}

// Friend function to display portfolio details (not a member of Portfolio)
void showPortfolioDetails(const Portfolio& portfolio) {
    portfolio.showPortfolio();
}

// Exception class for invalid stock operation
class InvalidStockException : public runtime_error {
public:
    InvalidStockException(const string& message) : runtime_error(message) {}
};



int main() {
    try {
        Portfolio portfolio;
        char choice;

        display_content1();

        do {
                 display_content2();

            cout << ">>>>>>>Choose stock type to add (s: stock b: Bond): ";
            cin >> choice;

            if (choice == 's' || choice == 'S') {
                string name;
                double price;

                cout <<endl<< "Enter Stock name: ";
                cin >> name;
                cout<<endl << "Enter Stock price: ";
                cin >> price;

                createAndAddStock<Equity>(portfolio, name, price);

            } else if (choice == 'b' || choice == 'B') {
                string issuer;
                double interestRate;

                cout<<endl << ">>>>>>>Enter Bond issuer: ";
                cin >> issuer;
                cout <<endl<< ">>>>>>>Enter Bond interest rate: ";
                cin >> interestRate;

                createAndAddStock<Bond>(portfolio, issuer, interestRate);

            } else {
                cerr << ">>>>>>>Invalid choice, please try again." << endl;
                // Simulating an invalid operation to trigger an exception
                throw InvalidStockException("Invalid stock operation!");
            }

            cout <<endl<< ">>>>>>>Do you want to add another stock? (y/n): ";
            cin >> choice;

            cout<<endl;


              display_content2();

        } while (choice == 'y' || choice == 'Y');

        // Display the portfolio details using a friend function
         cout<<endl<<"\t\t\t\t <<<<<<<<<<<<<<<<YOUR HOLDINGS>>>>>>>>>>>>>>>>"<<endl;
         cout<<"\t\t ---------------------------------------------------------------------------"<<endl;
        showPortfolioDetails(portfolio);




    } catch (const InvalidStockException& ex) {
        cerr << "Exception: " << ex.what() << endl;
    }

    return 0;
}
