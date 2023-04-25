#include <iostream>
using namespace std;

struct Good {
    int id;
    string name;
    int quantity;
    int price;
};

enum actions {
    ADD,
    EDIT,
    DELETE,
    BUY,
    SELL,
    UNDO,
    REDO,
};

struct goodWithAction {
    Good good;
    actions action;
};