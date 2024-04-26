#include <iostream>

int main()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int *first = array;

    // first: index = 0 // forth: index = 3
    std::cout << *(first + 3) << std::endl;

    return 0;
}