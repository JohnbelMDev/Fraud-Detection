#include <iostream>
#include <bitset>

int main() {
    unsigned int a = 5;  // Binary: 0000 0101
    unsigned int b = 9;  // Binary: 0000 1001

    // Bitwise AND
    unsigned int andResult = a & b;  // Binary: 0000 0001
    std::cout << "AND Result: " << andResult << " (" << std::bitset<8>(andResult) << ")\n";

    // Bitwise OR
    unsigned int orResult = a | b;   // Binary: 0000 1101
    std::cout << "OR Result: " << orResult << " (" << std::bitset<8>(orResult) << ")\n";

    // Bitwise XOR
    unsigned int xorResult = a ^ b;  // Binary: 0000 1100
    std::cout << "XOR Result: " << xorResult << " (" << std::bitset<8>(xorResult) << ")\n";

    // Bitwise NOT
    unsigned int notResult = ~a;     // Binary: 1111 1010
    std::cout << "NOT Result: " << notResult << " (" << std::bitset<8>(notResult) << ")\n";

    // Left Shift
    unsigned int leftShift = a << 1; // Binary: 0000 1010
    std::cout << "Left Shift Result: " << leftShift << " (" << std::bitset<8>(leftShift) << ")\n";

    // Right Shift
    unsigned int rightShift = b >> 1; // Binary: 0000 0100
    std::cout << "Right Shift Result: " << rightShift << " (" << std::bitset<8>(rightShift) << ")\n";

    return 0;
}
