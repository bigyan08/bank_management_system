#include <iostream>
#include <string>

using namespace std;

class Account {
public:
    Account() : name(""), accNumber(0), balance(0.0), active(false) {}

    void createAccount(string name, int accNumber, double balance) {
        this->name = name;
        this->accNumber = accNumber;
        this->balance = balance;
        this->active = true;
    }

    string getName() const { return name; }
    int getAccNumber() const { return accNumber; }
    double getBalance() const { return balance; }
    bool isActive() const { return active; }

    void deposit(double amount) {
        if (active) {
            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Account not active." << endl;
        }
    }

    void withdraw(double amount) {
        if (active) {
            if (amount > balance) {
                cout << "Insufficient balance!" << endl;
            } else {
                balance -= amount;
                cout << "Withdrawal successful. New balance: " << balance << endl;
            }
        } else {
            cout << "Account not active." << endl;
        }
    }

private:
    string name;
    int accNumber;
    double balance;
    bool active;
};

class Bank {
public:
    Bank() : accountCount(0) {}

    void createAccount(string name, double balance) {
        if (accountCount < MAX_ACCOUNTS) {
            accounts[accountCount].createAccount(name, accountCount + 1, balance);
            cout << "Account created successfully. Account Number: " << accountCount + 1 << endl;
            accountCount++;
        } else {
            cout << "Bank is full, cannot create more accounts." << endl;
        }
    }

    Account* getAccount(int accNumber) {
        if (accNumber > 0 && accNumber <= accountCount && accounts[accNumber - 1].isActive()) {
            return &accounts[accNumber - 1];
        } else {
            return nullptr;
        }
    }

private:
    static const int MAX_ACCOUNTS = 10;
    Account accounts[MAX_ACCOUNTS];
    int accountCount;
};

int main() {
    Bank bank;
    int choice;
    string name;
    int accNumber;
    double amount;

    while (true) {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter initial deposit: ";
            cin >> amount;
            bank.createAccount(name, amount);
            break;
        case 2:
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (Account* acc = bank.getAccount(accNumber)) {
                acc->deposit(amount);
            } else {
                cout << "Invalid account number." << endl;
            }
            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (Account* acc = bank.getAccount(accNumber)) {
                acc->withdraw(amount);
            } else {
                cout << "Invalid account number." << endl;
            }
            break;
        case 4:
            cout << "Enter account number: ";
            cin >> accNumber;
            if (Account* acc = bank.getAccount(accNumber)) {
                cout << "Account Balance: " << acc->getBalance() << endl;
            } else {
                cout << "Invalid account number." << endl;
            }
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
