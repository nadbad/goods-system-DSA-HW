// my files
#include "types.h"
#include "stack.h"
#include "goods.h"

// packages
#include <iostream>
#include <cstdlib>
using namespace std;

void undoAction(Stack& undo, Good goods[], int& totalItems, Stack& redo){ 
    if(!undo.isEmpty()){
        goodWithAction actionGood = undo.topItem();
        goodWithAction actionGoodRedo;
        int goodIndex = findGood(goods, actionGood.good.id, totalItems);

         if(actionGood.action == ADD){
            int newIndex = 0;

            actionGoodRedo.good = actionGood.good;
            actionGoodRedo.action = ADD;

            for (int i = 0; i < totalItems; i++) {
                 if (i > goodIndex || i < goodIndex) {
                    goods[newIndex] = goods[i];
                    newIndex++;
                }
            }
            totalItems--;

            cout << "The item has been unadded successfully." << "\n";
        } else if(actionGood.action == EDIT){
            Good *g = &goods[goodIndex];

            actionGoodRedo.good = *g;
            actionGoodRedo.action = EDIT;

            g->name = actionGood.good.name;
            g->quantity = actionGood.good.quantity;
            g->price = actionGood.good.price;

            cout << "The item has been unedited successfully." << "\n";
        } else if(actionGood.action == DELETE){
            Good *g = &goods[++totalItems];

            actionGoodRedo.good = actionGood.good;
            actionGoodRedo.action = DELETE;

            g->id = actionGood.good.id;
            g->name = actionGood.good.name;
            g->quantity = actionGood.good.quantity;
            g->price = actionGood.good.price;

            cout << "The item has been undeleted successfully." << "\n";
        } else if(actionGood.action == BUY){
            Good *g = &goods[goodIndex];

            actionGoodRedo.good = *g;
            actionGoodRedo.action = BUY;

            g->quantity = actionGood.good.quantity;

            cout << "The item has been unbought successfully." << "\n";
        } else if(actionGood.action == SELL){
            Good *g = &goods[goodIndex];

            actionGoodRedo.good = *g;
            actionGoodRedo.action = SELL;

            g->quantity = actionGood.good.quantity;

            cout << "The item has been unsold successfully." << "\n";
        }

        redo.push(actionGoodRedo);
        undo.pop();
    } else{
        cout << "No previous actions found." << endl;
    }
}

void redoAction(Stack& undo, Good goods[], int& totalItems, Stack& redo){
    if(!redo.isEmpty()){
        goodWithAction actionGood = redo.topItem();
        goodWithAction actionGoodUndo;
        int goodIndex = findGood(goods, actionGood.good.id, totalItems);

        if(actionGood.action == ADD){
            Good *g = &goods[++totalItems];

            actionGoodUndo.good = actionGood.good;
            actionGoodUndo.action = ADD;

            g->id = actionGood.good.id;
            g->name = actionGood.good.name;
            g->quantity = actionGood.good.quantity;
            g->price = actionGood.good.price;

            cout << "The item has been re-added successfully." << "\n";
        } else if(actionGood.action == EDIT){
            Good *g = &goods[goodIndex];

            actionGoodUndo.good = *g;
            actionGoodUndo.action = EDIT;

            g->name = actionGood.good.name;
            g->quantity = actionGood.good.quantity;
            g->price = actionGood.good.price;

            cout << "The item has been re-edited successfully." << "\n";
        } else if(actionGood.action == DELETE){
            int newIndex = 0;

            actionGoodUndo.good = actionGood.good;
            actionGoodUndo.action = DELETE;

            for (int i = 0; i < totalItems; i++) {
                 if (i > goodIndex || i < goodIndex) {
                    goods[newIndex] = goods[i];
                    newIndex++;
                }
            }
            totalItems--;

            cout << "The item has been re-deleted successfully." << "\n";
        } else if(actionGood.action == BUY){
            Good *g = &goods[goodIndex];

            actionGoodUndo.good = *g;
            actionGoodUndo.action = BUY;

            g->quantity = actionGood.good.quantity;

            cout << "The item has been re-bought successfully." << "\n";
        } else if(actionGood.action == SELL){
            Good *g = &goods[goodIndex];

            actionGoodUndo.good = *g;
            actionGoodUndo.action = SELL;

            g->quantity = actionGood.good.quantity;

            cout << "The item has been unsold successfully." << "\n";
        }
        
        undo.push(actionGoodUndo);
        redo.pop();
    } else {
        cout << "No previous actions found." << endl;
    }
}

int main()
{
    int size = 10;
    int flag = false;
    int id = 1;
    int totalItems = 0;
    Good goods[size];
    Stack undo;
    Stack redo;

    cout << "Welcome user" << "\n";

    do
    {
        // actions list
        cout << "What would you like to do?" << "\n";
        cout << "To exit, press: 0" << "\n";
        cout << "To view all goods, enter: 1" << "\n";
        cout << "To add a good, enter: 2" << "\n";
        cout << "To edit a good, enter: 3" << "\n";
        cout << "To delete a good, enter: 4" << "\n";
        cout << "To buy a good, enter: 5" << "\n";
        cout << "To sell a good, enter: 6" << "\n";
        cout << "To undo an action, enter: 7" << "\n";
        cout << "To redo an action, enter: 8" << "\n";

        int action;
        cin >> action;

        if (action == 0){
            flag = true;
        } else if (action == 1){
            viewGoods(goods, totalItems);
        } else if (action == 2){
            addGood(goods, id, totalItems, size, undo);
        } else if (action == 3){
            editGood(goods, id, totalItems, undo);
        } else if (action == 4){
            deleteGood(goods, id, totalItems, undo);
        } else if (action == 5){
            buyGood(goods, totalItems, undo);
        } else if (action == 6){
            sellGood(goods, totalItems, undo);
        } else if (action == 7){
            undoAction(undo, goods, totalItems, redo);
        } else if (action == 8){
            redoAction(undo, goods, totalItems, redo);
        } else {
            cout << "Enter valid action" << "\n";
        }
    } while(!flag);

    return 0;
}