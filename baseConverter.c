#include <stdlib.h>
#include <stdio.h>


// Helper function to find the length of strings
int stringLen(char* str) {
    int len = 0;

    while(1) {
        len++;
        if (str[len] == '\0') break;
    }
    return len;
}

// Function uses XOR to swap positions in string
void reverseBinaryString(char* str) {
    int len = stringLen(str);

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

int binaryToDecimal(char* binary) {
    int decimal = 0;
    int len = stringLen(binary);
    
    for (int i = 0; i < len; i++ ) {
        decimal = decimal * 2 + (binary[i] - '0');
    }       
    
    return decimal;
}

char* hexToBinary(char* hex) {
    int len = stringLen(hex);
    // Track the position of the number (*16 each time)
    int pos = 1;
    int total = 0;

    // Loop backwards and convert hex to decimal before converting to binary
    for (int i = len - 1; i >= 0; i--) {
        int decimal;
        if ((int)hex[i] > 64) {
            // add 10*pos to the total and convert to digit
            decimal = hex[i] - 'A';
            total += (10 * pos);
        } else {
            decimal = hex[i] - '0';
        }
        printf("%d\n", total); 
        total += (decimal * pos);
        pos *= 16;
    } 
    
    // Use existing decimal to binary to convert the hex total to binary 
    return decimalToBinary(total);
}

char* binaryToHex(char* binary) {
    char* hexDigits = "0123456789ABCDEF";
    
    // convert the binary to decimal format
    int decimal = binaryToDecimal(binary);
    
    // allocate memory to store a 32-bit hex number  
    char* result = (char*)malloc(9);
    
    int i = 0;
    while(decimal) {
        result[i++] = hexDigits[decimal % 16];
        decimal /= 16;
    }
    
    result[i] = '\0';
    reverseBinaryString(result);
    return result;
}

int main() {
    const int values[] = {14, 546, 312};

    for (int i = 0; i < 3; i++) {
        char* result = decimalToBinary(values[i]);
        int decimal = binaryToDecimal(result);
        if (result) {
            printf("%d = %s\n", values[i], result);
            printf("%s = %d\n", result, decimal);
            free(result);
        }
        
    }   
    

    char* hex = "1F44";
    char* result = hexToBinary(hex);
    char* result2 = binaryToHex(result);

    printf("%s = %s\n", hex, result);
    printf("%s = %s\n", result, result2);

    free(result);
    free(result2); 


    return 0;
}
