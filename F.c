#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define VERSION "1.1.0"

void main(int argc, char **argv) {
    if(argc <= 1) {
        printf("%s [Number]\n", argv[0]);
        exit(0);
    } else if(argc > 2) {
        puts("Argument Redundancy");
        exit(0);
    } else if(strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("F - v%s\n", VERSION);
        exit(0);
    } else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        puts("-------------------------\n"\
             "F - Contraction of Factor\n"\
             "-------------------------\n"\
             "Finds factors (Not prime factors)\n"\
             "of a given number that abides\n"\
             "to the following:\n"\
             "* Must not be a zero\n"\
             "* Must not be negative\n"\
             "At once, only a single argument can\n"\
             "passed to F. The following are\n"\
             "arguments supported:\n"\
             "A number\n"\
             "-v --version - display the current version\n"\
             "-h --help - display this dialogue\n"
             "-------------------------\n"
             "F © 2020 Hathim Ali\n"\
             "F is distributed under GNU GPL v3");
             exit(0);
    }
    size_t i;
    mpz_t number;
    mpz_t theNumber;
    mpz_t placeValue;
    mpz_init(number);
    mpz_init(theNumber);
    mpz_init_set_si(placeValue, 1);
    char charNumber[strlen(argv[1])];
    char temporaryCharNumber;
    bool isNegative = false;

    strcpy(charNumber, argv[1]);
    for(i = strlen(charNumber); i > 0; i--) {
        temporaryCharNumber = charNumber[i - 1];
        if(temporaryCharNumber == '-') {
            puts("Negative Integer Fault");
            exit(0);
        }
        mpz_set_si(number, atoi(&temporaryCharNumber));
        //gmp_printf("Number: %Zd CharNumber: %c\n", number, temporaryCharNumber);
        //gmp_printf("Place Value: %Zd * Number: %Zd\n", placeValue, number);
        mpz_mul(number, number, placeValue);
        //gmp_printf("Number: %Zd + TheNumber: %Zd\n", number, theNumber);
        mpz_add(theNumber, theNumber, number);
        //gmp_printf("TheNumber: %Zd\n", theNumber);
        mpz_mul_ui(placeValue, placeValue, 10);
    }
    mpz_clear(placeValue);
    if(mpz_cmp_si(theNumber, 0) == 0) {
        puts("Zero Integer Fault");
        exit(0);
    }
    mpz_set_ui(number, 1);
    gmp_printf("%Zd => ( ", theNumber);
    while(true) {
        if(mpz_divisible_p(theNumber, number) != 0) gmp_printf("%Zd, ", number);
        mpz_add_ui(number, number, 1);
        if(mpz_cmp(theNumber, number) == 0) {
            gmp_printf("%Zd )\n", number);
            break;
        }
    }
    mpz_clear(number);
    mpz_clear(theNumber);
}