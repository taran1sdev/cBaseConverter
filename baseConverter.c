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
void reverseString(char* str) {
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
    reverseString(binary); 
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
        total += (decimal * pos);
        pos *= 16;
    } 
    
    // Use existing decimal to binary to convert the hex total to binary 
    return decimalToBinary(total);
}

char* binaryToHex(char* binary) {
    const char* hexDigits = "0123456789ABCDEF";
    
    // convert the binary to decimal format
    int decimal = binaryToDecimal(binary);
    
    // allocate memory to store a 32-bit hex number  
    char* result = (char*)malloc(9);
    if (!result) return NULL;

    int i = 0;
    while(decimal) {
        result[i++] = hexDigits[decimal % 16];
        decimal /= 16;
    }
    
    result[i] = '\0';
    reverseString(result);
    return result;
}

int parseDecimalString(char* str) {
    int len = stringLen(str);
    int pos = 1;
    int total = 0;

    for (int i = len - 1; i >= 0; i--) {
        int decimal = str[i] - '0';
        total += (decimal * pos);
        pos *= 10;
    }

    return total;
}

int main() {
    int option;

    while(1) {        
        printf("\nNumber base converter\n");
        printf("---- Menu ----\n");
        printf("1] Decimal to Binary\n");
        printf("2] Binary to Decimal\n");
        printf("3] Hex to Binary\n");
        printf("4] Binary to Hex\n");
        printf("5] Exit\n");
       
        scanf("%d", &option);

        if (option == 5) {
           printf("Goodbye.\n");
           break; 
        }

        char input[40];
        switch (option) {
            case 1: 
                printf("Enter a decimal number: ");
                scanf("%s", &input);
                int decimal = parseDecimalString(input);
                char* result = decimalToBinary(decimal);
                printf("%s\n", result);
                free(result);
                break;
            case 2: 
                printf("Enter a binary number (32-bit max): ");
                scanf("%s", &input);
                int len = stringLen(input);
                if (len > 33) {
                    printf("Too long.\n");
                    break;
                }
                int decResult = binaryToDecimal(input);
                printf("%d\n", decResult);
                break;
            case 3:
                printf("Enter a Hexadecimal number: ");
                scanf("%s", &input);
                result = hexToBinary(input);
                printf("%s\n", result);
                free(result);
                break;
            case 4:
                printf("Enter a Binary number (32-bit max): ");
                scanf("%s", &input);
                len = stringLen(input);
                if (len > 33) {
                    printf("Too long.\n");
                    break;
                }
                result = binaryToHex(input);
                printf("%s", result);
                free(result);
                break;
            default:
                printf("Invalid input, please try again..\n");
        }
    } 

           
    return 0;
}
