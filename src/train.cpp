// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCar(bool light){
    Car* newCar = new Car{light, nullptr, nullptr};
    if (first == nullptr) {
        first = newCar;
        first->next=first;
        first->prev=first;
      }
    else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev= newCar;
    }
}
int Train::getOpCount(){
    return countOp;
}
int Train::getLength () {
    if (first == nullptr) return 0;
    Car* current = first;
    current->light = true;
    int step = 1;
    int allsteps = 0;
    do {
        for (int i = 0; i< step; i++) {
            current = current->next;
            countOp++;
        }
        allsteps+=step;
        if (current->light) break;
        step*=2;
    }
    while (true);

    int low = allsteps - step + 1;
    int high = allsteps;

    while ( low<high) {
     first->light= false;
     int mid = low + (high - low) / 2;
     current = first;
     for (int i = 0; i<mid; i++) {
        current = current->next;
        countOp++;
     }
     if (current->light) 
        high = mid;
     else 
        low = mid + 1;
     first->light = true;

    }
    return low;
}
