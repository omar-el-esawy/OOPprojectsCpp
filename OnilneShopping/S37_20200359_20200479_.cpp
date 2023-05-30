#include <bits/stdc++.h>

using namespace std;
//intialze class Item

class Item {
    //intialze private members
    string name;
    int ID;
    double quantity, price;
    static int generatedID;
public:
    //function to know the same id
    void isTheSame() {
        generatedID--;
    }
    //costructor

    Item(string name, double quantity, double price) {
        this->name = name;
        this->quantity = quantity;
        this->price = price;
        this->ID = generatedID;
        generatedID++;
    }
//default costructor
    Item() {
        this->ID = generatedID;
        generatedID++;
    }
//copy costructor

    Item(const Item &other) {
        this->ID = other.ID;
        this->name = other.name;
        this->quantity = other.quantity;
        this->price = other.price;
    }
//seters and getter
    void setname(string name) {
        this->name = name;
    }

    void setQuan(double quantity) {
        this->quantity = quantity;
    }

    void setPrice(double price) {
        this->price = price;
    }

    int getID() const {
        return ID;
    }

    string getname() const {
        return name;
    }

    double getQuan() const {
        return quantity;
    }

    double getPrice() const {
        return price;
    }
//operators
    bool operator==(const Item &other) {
        return (this->name == other.name);
    }

    void operator+=(int x) {
        quantity += x;
    }

    void operator-=(int x) {
        quantity -= x;
    }

    friend istream &operator>>(istream &In, Item &item) {
        In >> item.name >> item.quantity >> item.price;
        return In;
    }

    friend ostream &operator<<(ostream &Out, Item &item) {
        Out << "Item ID : " << item.ID << endl
            << "Item name :  " << item.name << endl <<
            "Item price :  " << item.price << endl
            << "Item quantity : " << item.quantity << endl;
        return Out;
    }
};
//intialze class Seller
class Seller {
    //intialze private members
    string name, email;
    int maxItems;
    Item **item;
    int counter = 0;
public:
    //costructor
    Seller(string name = " ", string email = " ", int maxItems = 0) {
        this->name = name;
        this->email = email;
        this->maxItems = maxItems;
        item = new Item *[maxItems];
    }

//function to add items
    bool add(Item &newitem) {
        bool flag = 1;
        for (int i = 0; i < counter; i++) {
            if ((*item[i]) == newitem) {
                (*item[i]) += (newitem.getQuan());
                item[i]->isTheSame();
                flag = 0;
            }
        }
        if (flag) {
            //bool flag to know the capacity of the storage
            if (counter > maxItems) {
                cout << "the storage is full\n";
                return 0;
            }
            item[counter] = &newitem;
            counter++;
        }
        return 1;
    }
    //function to subtract the new quantity from the current quantity

    bool sell(string itemname, double quantity) {
        for (int i = 0; i < counter; i++) {
            if (item[i]->getname() == itemname) {
                if (quantity <= item[i]->getQuan())
                    (*item[i]) -= quantity;
                else {
                    cout << "there is no enough " << item[i]->getname() << endl;
                    return 0;
                }
            }
        }
        return 1;
    }
//operator
    friend ostream &operator<<(ostream &Out, Seller &seller) {
        Out << "seller name : " << seller.name << endl;
        Out << "seller email : " << seller.email << endl;
        Out << "seller maxitems : " << seller.maxItems << endl;
        return Out;
    }
//find an item by id
    Item *findID(int ID) {
        for (int i = 0; i < counter; i++) {
            if (item[i]->getID() == ID)
                return item[i];
        }
    }
//function to print items
    void printItems() {
        cout << "------Seller info --------" << endl;
        cout << (*this) << endl;
        for (int i = 0; i < counter; i++) {
            cout << "------Item num " << item[i]->getID() << "--------" << endl;
            cout << (*item[i]) << endl;
        }
    }
    //distructor

    ~Seller() {
        for (int i = 0; i < counter; i++) {
            delete item[i];
            item[i] = NULL;
        }
        delete item;
        item = NULL;
    }
};

int Item::generatedID = 1;

int main() {
    string name, email;
    int maxItems;
    cout << "intput your details: (name, email)" << endl;
    cin >> name >> email;
    cout << "input your store capacity :" << endl;
    cin >> maxItems;
    Seller seller(name, email, maxItems);

    while (1) {
        cout <<
             "------------------\n"
             "options:\n"
             "1. Print My Info. \n"
             "2. Add An Item.\n"
             "3. Sell An Item.\n"
             "4. Print Items.\n"
             "5. Find an Item by ID\n"
             "6. Exit\n"
             "------------------\n";
        int x;
        cin >> x;
        if (x == 1) {
            cout << seller;
        } else if (x == 2) {
            cout << "enter your details : (product name, quantity, price )" << endl;

            Item *x;
            x = new Item;
            cin >> *x;
            seller.add(*x);


        } else if (x == 3) {
            cout << "enter your details : (product name, quantity )" << endl;
            string productname;
            int quantity;
            cin >> productname >> quantity;
            seller.sell(productname, quantity);
        } else if (x == 4) {
            seller.printItems();
        } else if (x == 5) {
            cout << "find the item by ID : " << endl;
            int ID;
            cin >> ID;
            cout << (*seller.findID(ID));
        } else if (x == 6) {
            cout << "----------------------------------\n"
                 << "| The program closed, thank you! |\n"
                 << "----------------------------------\n";
            break;
        }
    }
}
