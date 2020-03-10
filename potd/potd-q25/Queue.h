#pragma once

#include <cstddef>

class Queue {
    public:
        Queue();
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
    private:
        int length = 0;
        int* arr = new int[1];
};
