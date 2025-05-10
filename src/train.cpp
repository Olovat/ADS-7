// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}
Train::~Train() {
  if (!first) return;
  Car* current = first->next;
  while (current != first) {
    Car* next = current->next;
    delete current;
    current = next;
  }
  delete first;
  first = nullptr;
}
void Train::addCar(bool light) {
  if (first == nullptr) {
    first = new Car{light, nullptr, nullptr};
    return;
  }
  if (first->next == nullptr) {
    Car* obj = new Car{light, nullptr, nullptr};
    first->next = obj;
    first->prev = obj;
    obj->prev = first;
    obj->next = first;
    return;
  }
  Car* obj = new Car{light, nullptr, nullptr};
  first->prev->next = obj;
  obj->prev = first->prev;
  first->prev = obj;
  obj->next = first;
  first = obj;
}
int Train::getOpCount() {
  return countOp;
}
int Train::getLength() {
  countOp = 0;
  Car* tempObj;
  while (true) {
    tempObj = first;
    unsigned int countCar = 1;
    if (!tempObj->light) {
      tempObj->light = true;
    }
    tempObj = tempObj->next;
    countOp += 2;
    while (!tempObj->light) {
      tempObj = tempObj->next;
      countOp += 2;
      countCar++;
    }
    tempObj->light = false;
    if (!first->light) {
      return countCar;
    }
  }
}
