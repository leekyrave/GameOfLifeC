#include "GameOfLife.h";

int GetAbsoluteIndex(int size, int index) {
    index = (index >= size) ? index % size : (index < 0) ? size - (abs(index) % size) : index;
    return index;
}