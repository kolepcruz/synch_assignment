#include <iostream>

int *seila() {
    int *a;
    return a;
}

int main() {
    int *a;
    int k = 5;
    a = &k;
    a = seila();
    std::cout << a << std::endl;
    std::cout << "Hello World!" << std::endl;
    return 0;
}