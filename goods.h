#include <iostream>
using namespace std;

int findGood(Good arr[], int id, int size){
    int index;

    for (int i = 0; i < size; i++)
    {
        if(arr[i].id == id){
            index = i;
            break;
        }
    }
    return index;
}

bool doesExist(Good arr[], string name, int size){
    bool flag = false;

    for (int i = 0; i < size; i++)
    {
       if (name == arr[i].name){
            flag = true;
            break;
        }
    }

    return flag;
}

void viewGoods(Good arr[], int size){
    for (int i = 0; i < size; i++)
    {
        cout << arr[i].id << ": " << arr[i].name << "\n";
    }

    if((size) == 0){
        cout << "No goods found." << '\n';
    }
}

void addGood(Good arr[], int& id, int& totalItems, int size, Stack& undo){
    string name;
    int price, quantity;
    int index = totalItems;
    Good *g = &arr[index];
    goodWithAction actionGood;

    // Entry of good information
    cout << "Enter good name: " << "\n";
    cin >> name;
    cout << "Enter good price: " << "\n";
    cin >> price;
    cout << "Enter good quantity: " << "\n";
    cin >> quantity;

    if(totalItems >= size){
         cout << "You have reached the max amount of goods you can have, try deleting one or more or contacting your programmer to increase the limit." << '\n';
    }
    else if(!doesExist(arr, name, totalItems)){
        g->id = id;
        g->name = name;
        g->quantity = quantity;
        g->price = price;

        actionGood.good = *g;
        actionGood.action = ADD;

        undo.push(actionGood);

        id++;
        totalItems++;
        cout << "The item has been added successfully." << "\n";
    } else if(doesExist(arr, name, totalItems)) {
        cout << "The item already exists, please choose a different name." << "\n";
    }
};

void editGood(Good arr[], int id, int totalItems, Stack& undo){
    int editId;
    viewGoods(arr, totalItems);

    cout << "Enter id of good you want to edit: " << "\n";
    cin >> editId;

    int editIndex = findGood(arr, editId, totalItems);

    string name;
    int price, quantity;
    Good *g = &arr[editIndex];
    goodWithAction actionGood;

    // Entry of good information
    cout << "Enter good name: " << "\n";
    cin >> name;
    cout << "Enter good price: " << "\n";
    cin >> price;
    cout << "Enter good quantity: " << "\n";
    cin >> quantity;

    if(!doesExist(arr, name, totalItems)){
        actionGood.good = *g;
        actionGood.action = EDIT;
        undo.push(actionGood);

        g->name = name;
        g->quantity = quantity;
        g->price = price;

        cout << "The item has been edited successfully." << "\n";
    } else if(doesExist(arr, name, totalItems)) {
        cout << "The item already exists, please choose a different name." << "\n";
    }
}

void deleteGood(Good arr[], int id, int& totalItems, Stack& undo){
    int deleteId;
    viewGoods(arr, totalItems);

    cout << "Enter id of good you want to delete: " << "\n";
    cin >> deleteId;

    int deleteIndex = findGood(arr, deleteId, totalItems);
    int newIndex = 0;
    goodWithAction actionGood;

    actionGood.good = arr[deleteIndex];
    actionGood.action = DELETE;
    undo.push(actionGood);

    for (int i = 0; i < totalItems; i++) {
        if (i > deleteIndex || i < deleteIndex) {
            arr[newIndex] = arr[i];
            newIndex++;
        }
    }
    totalItems--;

    cout << "The item has been deleted successfully." << "\n";
}

void buyGood(Good arr[], int totalItems, Stack& undo){
    int buyId;
    viewGoods(arr, totalItems);

    cout << "Enter id of good you want to buy: " << "\n";
    cin >> buyId;

    int buyIndex = findGood(arr, buyId, totalItems);

    int quantity;
    Good *g = &arr[buyIndex];

    goodWithAction actionGood;
    actionGood.good = *g;
    actionGood.action = BUY;
    undo.push(actionGood);

    cout << "How many " << g->name << " would you like to buy?" << "\n";

    cin >> quantity;

    cout << "The price will be: " << (quantity * g->price) << "\n";
    g->quantity = g->quantity + quantity;
    cout << "The amout is now: " << (g->quantity) << "\n";
}

void sellGood(Good arr[], int totalItems, Stack& undo){
    int buyId;
    viewGoods(arr, totalItems);

    cout << "Enter id of good you want to buy: " << "\n";
    cin >> buyId;

    int buyIndex = findGood(arr, buyId, totalItems);

    int quantity;
    Good *g = &arr[buyIndex];

    goodWithAction actionGood;
    actionGood.good = *g;
    actionGood.action = SELL;
    undo.push(actionGood);

    cout << "Quantity: " << (g->quantity)  << "\n";
    cout << "How many " << g->name << " would you like to buy?" << "\n";
    cin >> quantity;

    if(quantity > g->quantity){
        cout << "The amount in stock is less than what's required." << "\n";
    } else {
        cout << "The price will be: " << (quantity * g->price) << "\n";
        g->quantity = g->quantity - quantity;
        cout << "The amout is now: " << (g->quantity) << "\n";
    }
}