#include <stdlib.h>
#include <stdio.h>

// Function uses XOR to swap positions in string
void reverseBinaryString(char* str) {
    int len = 0;
    
    while(1) {
        len++; 
        if (str[len] == '\0') break;
    }
        
    for (int i = 0; i < len / 2; i++) {
        str[i] = str[i] ^ str[len - 1 - i];
        str[len- 1 - i] = str[len - 1 -i] ^ str[i]; 
        str[i] = str[i] ^ str[len - 1 - i];
    }
}

char* decimalToBinary(int decimal) {
    // Allocate memory to store a 32-bit binary string + \0
    char* binary = (char*)malloc(33);
    if (!binary) return NULL; 
    
    int i = 0;

    while(decimal) {
        // Check if the left-most bit is 1 or 0
        binary[i++] = '0' + (decimal & 1);
        // Divide by 2
        decimal >>= 1;
    }

    binary[i] = '\0';
    reverseBinaryString(binary); 
    return binary;
}

int main() {
    const int values[] = {14, 546, 312};

    for (int i = 0; i < 3; i++) {
        char* result = decimalToBinary(values[i]);
        if (result) {
            printf("%d = %s\n", values[i], result);
            free(result);
        }
        
    }    
    return 0;
}
