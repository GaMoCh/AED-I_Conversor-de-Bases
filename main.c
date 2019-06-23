#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

void printSuccess() {
    printf("\nResultado: ");
}

void printError() {
    printf("\nEntrada inválida");
}

double _pow(double base, int exponent) {
    if (exponent > 0) {
        return (base * pow(base, exponent - 1));
    } else if (exponent < 0) {
        return (1 / pow(base, -exponent));
    } else {
        return 1;
    }
}

unsigned int convertCharValueToNumberValue(char charValue) {
    if (charValue >= '0' && charValue <= '9') {
        return (int)charValue - '0';
    } else if (charValue >= 'A' && charValue <= 'F') {
        return (int)charValue - 'A' + 10;
    } else if (charValue >= 'a' && charValue <= 'f') {
        return (int)charValue - 'a' + 10;
    }
}

void convertBaseToDec(char number[32], unsigned int base) {
    double fractionalPart = 0.0;
    unsigned long long integerPart = 0;
    unsigned int digits = strlen(number);
    unsigned int commaPosition = strlen(number);
    int isNegative = 0;
    int expoent = 0;

    for (int counter = digits - 1; counter >= 0; counter--) {
        if ((number[counter] == '0' || number[counter] == '1') || base > 2 ||
            number[counter] == '-' && counter == 0 || number[counter] == ',') {
            if ((number[counter] >= '0' && number[counter] <= '7') || base > 8 ||
                number[counter] == '-' && counter == 0 || number[counter] == ',') {
                if (number[counter] >= '0' && number[counter] <= '9' ||
                    number[counter] >= 'A' && number[counter] <= 'F' ||
                    number[counter] >= 'a' && number[counter] <= 'f' ||
                    number[counter] == '-' && counter == 0 || number[counter] == ',') {
                    if (number[counter] == ',') {
                        if (commaPosition < digits) {
                            printError();
                            return;
                        }
                        commaPosition = counter;
                    }
                } else {
                    printError();
                    return;
                }
            } else {
                printError();
                return;
            }
        } else {
            printError();
            return;
        }
    }

    if (number[0] == '-') {
        if (digits == 1) {
            printError();
            return;
        }
        isNegative = 1;
    }

    for (int counter = commaPosition - 1; counter >= isNegative; counter--) {
        unsigned int digit = convertCharValueToNumberValue(number[counter]);
        integerPart += digit * pow(base, expoent);
        expoent++;
    }

    if (commaPosition < digits) {
        expoent = -1;
        for (int counter = commaPosition + 1; counter < digits; counter++) {
            unsigned int digit = convertCharValueToNumberValue(number[counter]);
            fractionalPart += digit * pow(base, expoent);
            expoent--;
        }
    }

    printSuccess();

    if (isNegative == 1) {
        printf("-");
    }

    printf("%lf", integerPart + fractionalPart);
}

void convertDecToBase_printValue(int number) {
    if (number >= 10) {
        printf("%c", number + 'A' - 10);
    } else {
        printf("%d", number);
    }
}

void convertDecToBase_integerPart(unsigned long long number, unsigned int base) {
    unsigned long long remainder = 0;

    if (number == 0) {
        return;
    } else {
        remainder = number % base;
        convertDecToBase_integerPart(number / base, base);
    }

    convertDecToBase_printValue(remainder);
}

void convertDecToBase_fractionalPart(double number, unsigned int base, unsigned int fractionalPrecision) {
    int integerPart = 0;

    while (fractionalPrecision != 0) {
        number *= base;
        integerPart = (int) number;
        convertDecToBase_printValue(integerPart);
        number -= integerPart;
        fractionalPrecision--;
    }
}

void convertDecToBase(char number[32], unsigned int base) {
    double fractionalPart = 0.0;
    unsigned long long integerPart = 0;
    unsigned int digits = strlen(number);
    unsigned int commaPosition = strlen(number);
    unsigned int fractionalPrecision = 0;
    int isNegative = 0;
    int expoent = 0;

    for (int counter = digits - 1; counter >= 0; counter--) {
        if (number[counter] >= '0' && number[counter] <= '9' ||
        number[counter] == '-' && counter == 0 || number[counter] == ',') {
            if (number[counter] == ',') {
                if (commaPosition < digits) {
                    printError();
                    return;
                }
                commaPosition = counter;
            }
        } else {
            printError();
            return;
        }
    }

    if (number[0] == '-') {
        if (digits == 1) {
            printError();
            return;
        }
        isNegative = 1;
    }

    for (int counter = commaPosition - 1; counter >= isNegative; counter--) {
        unsigned int digit = convertCharValueToNumberValue(number[counter]);
        integerPart += digit * _pow(10, expoent);
        expoent++;
    }

    if (commaPosition < digits) {
        expoent = -1;
        for (int counter = commaPosition + 1; counter < digits; counter++) {
            unsigned int digit = convertCharValueToNumberValue(number[counter]);
            fractionalPart += digit * _pow(10, expoent);
            expoent--;
        }
    }

    if (fractionalPart != 0) {
        printf("\nPrecisão dos números fracionários: ");
        scanf("%u", &fractionalPrecision);
    }

    printSuccess();

    if (integerPart == 0) {
        printf("0");
    } else {
        convertDecToBase_integerPart(integerPart, base);
    }

    if (fractionalPart != 0) {
        printf(",");
        convertDecToBase_fractionalPart(fractionalPart, base, fractionalPrecision);
    }
}

int main() {
    unsigned int choice = 0;
    unsigned int base = 0;
    char number[32];

    setlocale(LC_ALL, "portuguese");

    do {
        system("cls");

        printf("- CONVERSOR DE BASES -\n\n");

        printf("Selecione uma opção: \n\n");

        printf("0 - Sair \n");
        printf("1 - Decimal para binário \n");
        printf("2 - Decimal para octal \n");
        printf("3 - Decimal para hexadecimal \n");
        printf("4 - Binário para decimal \n");
        printf("5 - Octal para decimal \n");
        printf("6 - Hexadecimal para decimal \n");

        printf("\nInsira a opção: ");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                break;
            case 1:
                base = 2;
                break;
            case 2:
                base = 8;
                break;
            case 3:
                base = 16;
                break;
            case 4:
                base = 2;
                break;
            case 5:
                base = 8;
                break;
            case 6:
                base = 16;
                break;
            default:
                printf("\nOpção inválida\n\n");
                system("pause");
                continue;
        }

        system("cls");

        if (choice != 0) {
            printf("Insira o número: ");
            scanf("%s", &number);

            if (choice >= 1 && choice <= 3) {
                convertDecToBase(number, base);
            } else if (choice >= 4 && choice <= 6) {
                convertBaseToDec(number, base);
            }

            printf("\n\n");
            system("pause");
        }
    } while (choice != 0);
    return 0;
}
