// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (first == nullptr) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getOpCount() {
  return countOp;
}

int Train::getLength() {
  if (first == nullptr) return 0;
  
  bool allLightsOn = true;
  Car* check = first;
  do {
    if (!check->light) {
      allLightsOn = false;
      break;
    }
    check = check->next;
    if (check != first) countOp++;
  } while (check != first);
  
  if (allLightsOn) {
    first->light = false;
    countOp = 0;
  }
  
  if (!allLightsOn && !first->light) {
    Car* current = first;
    current->light = true;
    
    int count = 1;
    current = current->next;
    countOp++;
    
    while (!current->light) {
      count++;
      current = current->next;
      countOp++;
    }
    
    return count;
  }
  
  bool originalState = first->light;
  first->light = !originalState;
  
  Car* current = first;
  int step = 1;
  int totalSteps = 0;
  
  do {
    for (int i = 0; i < step; i++) {
      current = current->next;
      countOp++;
    }
    totalSteps += step;
    
    if (current->light == !originalState && current != first) {
      break;
    }
    
    step *= 2;
  } while (true);
  
  int low = totalSteps - step + 1;
  int high = totalSteps;
  
  first->light = originalState;
  first->light = !originalState;
  
  while (low < high) {
    int mid = low + (high - low) / 2;
    current = first;
    
    for (int i = 0; i < mid; i++) {
      current = current->next;
      countOp++;
    }
    
    if (current->light == !originalState) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  
  first->light = originalState;
  
  return low;
}
