// Author: Chunbok Kim and Copilot
// Date:    2024.11.17
// Version: 0.1
// Purpose: Log flow program

// Include the necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <gmp.h>
#include <mpfr.h>

// Define constants
// Set the status code for category
#define CATEGORY_MENU_NO 0
#define CATEGORY_MENU_YES 1
#define CATEGORY_STATUS_NO 0
#define CATEGORY_STATUS_YES 1
#define CATEGORY_INPUT_NO 0
#define CATEGORY_INPUT_YES 1
#define CATEGORY_INPUT_RANGE_NUMBER 1
#define CATEGORY_INPUT_RANGE1_RANGE2 2
#define CATEGORY_INPUT_RANGE3_RANGE4 3
#define CATEGORY_PRINT_NO 0
#define CATEGORY_PRINT_YES 2
#define CATEGORY_PRINT_LOG_2 4
#define CATEGORY_PRINT_LOG_2_TOTAL 5
#define CATEGORY_PRINT_1_DIV_LOG_2 6
#define CATEGORY_PRINT_1_DIV_LOG_2_TOTAL 7
#define CATEGORY_PRINT_LOG_2_AND_1_DIV_LOG_2 8
#define CATEGORY_PRINT_LOG_2_AND_1_DIV_LOG_2_TOTAL 9
#define CATEGORY_PRINT_RANGE_NUMBER 10
#define CATEGORY_PRINT_RANGE_NUMBER_TOTAL 11
#define CATEGORY_SAVE_NO 0
#define CATEGORY_SAVE_YES 3
#define CATEGORY_SAVE_RANGE_NUMBER 12
#define CATEGORY_SAVE_RANGE_NUMBER_ONLY_PRIME 13
#define CATEGORY_SAVE_DATA 14
#define CATEGORY_SAVE_DATA_ONLY_PRIME 15
#define CATEGORY_LOAD_NO 0
#define CATEGORY_LOAD_YES 4
#define CATEGORY_LOAD_DATA 16
//#define CATEGORY_LOAD_DATA_ONLY_PRIME 14
#define CATEGORY_SEARCH_NO 0
#define CATEGORY_SEARCH_YES 5
#define CATEGORY_SEARCH_LOG_10_2 17
#define CATEGORY_SEARCH_LOG_10_DIV_1 18
#define CATEGORY_SEARCH_LOG_10_2_AGAIN 19
#define CATEGORY_SEARCH_LOG_10_DIV_1_AGAIN 20
#define CATEGORY_LIST_NO 0
#define CATEGORY_LIST_YES 1

// Function prototypes
void view_menu();
char *get_input(char *prompt);
char *get_input_string(char *prompt);
char **get_input_array(char *prompt, int size);

bool isPrime(int n);
int isPrimeGMP(mpz_t n);

void log10_2(char *res);
void log10_div_1(char *res);
void log10_2_digits(mpfr_t n, char *res);

void div_PN_digits(mpfr_t n, char *res);
void div_digits_PN(mpfr_t n, char *res); 

char *get_delete_string(char *str, int start, int end);
char *get_delete_first_string(char *str, int end);
char *get_delete_last_string(char *str, int start);
char *get_delete_middle_string(char *str, int start, int end);

void print_PN_digits(void);
void print_PN_digits_total(void);
void print_digits_PN(void);
void print_digits_PN_total(void);
void print_digits_PN_and_PN_digits(void);
void print_digits_PN_and_PN_digits_total(void);

int save(char *filename, char *range1, char *range2, int choice_save);
int save_prime(char *filename, char *range1, char *range2, int choice_save);
int load(char *filename);
int load_prime(char *filename);

void print_list(int choice_save);
void print_prime_list(int choice_save);
int save_list(char *filename, int choice_save);
int save_list_prime(char *filename, int choice_save);
int load_list(char *filename);

int search_log10_2(char **value_arr, int in_max);
int search_log10_2_div_1(char **value_arr, int in_max);
int search_log10_2_again(char **value_arr, int in_max);
int search_log10_2_div_1_again(char **value_arr, int in_max);

// global variables
char *global_str1;
char *global_str2;
char *global_first_str;
char *global_last_str;
char *global_range_str;
char *global_range1_str;
char *global_range2_str;
char *global_range3_str;
char *global_range4_str;
char **global_value_arr;
int global_choice_save;
int global_size;
int category_menu;
int category_status;
int category_type;
int category_content;
int category_list;
int category[16];
long global_list_line;
long global_list_line_backup;
long global_category;
int category_last_type;
int category_last_content;
int category_last_list;
mpfr_t global_first;
mpfr_t global_last;
mpfr_t global_range1;
mpfr_t global_range2;
mpfr_t global_range3;
mpfr_t global_range4;
mpfr_t *global_list;

// main function
// argc: number of arguments
// argv: array of arguments
int main(int argc, char *argv[])
{
    char *filename;
    char *str;
    char *input;
    char *token;
    char **input_array;
    char **input_str;
    int choice;
    int choice_save;
    int token_count;

    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpz_t count;
    mpfr_t n;
    mpfr_t res;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;
    mpfr_t *result;

    // Initialize the global variables
    global_first_str = (char *)malloc(1000 * sizeof(char));
    global_last_str = (char *)malloc(1000 * sizeof(char));
    global_range1_str = (char *)malloc(1000 * sizeof(char));
    global_range2_str = (char *)malloc(1000 * sizeof(char));
    global_range3_str = (char *)malloc(1000 * sizeof(char));
    global_range4_str = (char *)malloc(1000 * sizeof(char));
    global_value_arr = (char **)malloc(1000 * sizeof(char *));
    for (int i = 0; i < 1000; i++)
    {
        global_value_arr[i] = (char *)malloc(1000 * sizeof(char));
    }
    memset(global_first_str, 0, 1000);
    memset(global_last_str, 0, 1000);
    memset(global_range1_str, 0, 1000);
    memset(global_range2_str, 0, 1000);
    memset(global_range3_str, 0, 1000);
    memset(global_range4_str, 0, 1000);
    mpfr_init2(global_first, 1024);
    mpfr_init2(global_last, 1024);
    mpfr_init2(global_range1, 1024);
    mpfr_init2(global_range2, 1024);
    mpfr_init2(global_range3, 1024);
    mpfr_init2(global_range4, 1024);
    mpfr_init2(n, 1024);
    mpfr_init2(res, 1024);

    strcpy(global_first_str, "0.0");
    mpfr_set_str(global_first, global_first_str, 10, MPFR_RNDN);
    strcpy(global_last_str, "0.0");
    mpfr_set_str(global_last, global_last_str, 10, MPFR_RNDN);
    log10_2(global_range1_str);
    strcpy(global_range2_str, "0.5");
    mpfr_set_str(global_range1, global_range1_str, 10, MPFR_RNDN);
    mpfr_set_str(global_range2, global_range2_str, 10, MPFR_RNDN);
    strcpy(global_range3_str, "2.0");
    log10_div_1(global_range4_str);
    mpfr_set_str(global_range3, global_range3_str, 10, MPFR_RNDN);
    mpfr_set_str(global_range4, global_range4_str, 10, MPFR_RNDN);

    global_str1 = (char *)malloc(1000 * sizeof(char));
    global_str2 = (char *)malloc(1000 * sizeof(char));
    filename = (char *)malloc(256 * sizeof(char));
    memset(global_str1, 0, 1000);
    memset(global_str2, 0, 1000);
    memset(filename, 0, 256);
    global_choice_save = 0;
    global_size = 2;
    str = (char *)malloc(1000 * sizeof(char));
    input = (char *)malloc(1000 * sizeof(char));
    token = (char *)malloc(1000 * sizeof(char));
    input_array = (char **)malloc(1000 * sizeof(char *));
    for (int i = 0; i < 1000; i++)
    {
        input_array[i] = (char *)malloc(1000 * sizeof(char));
    }
    input_str = (char **)malloc(1000 * sizeof(char *));
    for (int i = 0; i < 1000; i++)
    {
        input_str[i] = (char *)malloc(1000 * sizeof(char));
    }
    choice = 0;
    choice_save = 1;
    token_count = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpz_init(count);
    // Set n1 and n2 to 0
    mpz_set_str(n1, "0", 10);
    mpz_set_str(n2, "0", 10);
    mpz_set_str(count, "0", 10);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    result = (mpfr_t *)malloc(1000 * sizeof(mpfr_t));
    for (int i = 0; i < 1000; i++)
    {
        mpfr_init2(result[i], 1024);
    }
    mpfr_set_ui(base_n, global_size, MPFR_RNDN);

    global_list = (mpfr_t *)malloc(1000 * sizeof(mpfr_t));
    for(int i = 0; i < 1000; i++)
    {
        mpfr_init2(global_list[i], 1024);
    }

    do
    { 
        view_menu();
        choice = atoi(get_input("Enter your choice: "));
        category_menu = CATEGORY_MENU_YES;
        category_type = category_menu;
        category[0] = category_type;

        switch(choice)
        {
            case 1:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_INPUT_YES;
                category_content = CATEGORY_INPUT_RANGE_NUMBER;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[2] = category_type;
                category[3] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                input_str = get_input_array("Enter the first number, last number: ", 2);
                strcpy(global_first_str, input_str[0]);
                strcpy(global_last_str, input_str[1]);
                mpfr_set_str(global_first, global_first_str, 10, MPFR_RNDN);
                mpfr_set_str(global_last, global_last_str, 10, MPFR_RNDN);
                break;
            case 2:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_INPUT_YES;
                category_content = CATEGORY_INPUT_RANGE1_RANGE2;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[2] = category_type;
                category[3] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("range1 = [ digits / PN, log(2) ]\n");
                mpfr_printf("range1 = %.30Rf\n", global_range1);
                printf("range2 = [ digits / PN, log(2) + x ]\n");
                mpfr_printf("range2 = %.30Rf\n", global_range2);
                printf("\n");
                log10_2(str);
                mpfr_printf("log(2) = %s\n", str);
                input_str = get_input_array("Enter the range1, range2: ", 2);
                strcpy(global_range1_str, input_str[0]);
                strcpy(global_range2_str, input_str[1]);
                mpfr_set_str(global_range1, global_range1_str, 10, MPFR_RNDN);
                mpfr_set_str(global_range2, global_range2_str, 10, MPFR_RNDN);
                break;
            case 3:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_INPUT_YES;
                category_content = CATEGORY_INPUT_RANGE3_RANGE4;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[2] = category_type;
                category[3] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("range1 = [ PN / digits, 1 / log(2) - x ]\n");
                mpfr_printf("range3 = %.30Rf\n", global_range3);
                printf("range2 = [ PN / digits, 1 / log(2) ]\n");
                mpfr_printf("range4 = %.30Rf\n", global_range4);
                printf("\n");
                log10_div_1(str);
                mpfr_printf("1 / log(2) = %s\n", str);
                global_range_str = get_input_string("Enter the range1, range2: ");
                sscanf(global_range_str, "%s %s", global_range3_str, global_range4_str);
                mpfr_set_str(global_range3, global_range3_str, 10, MPFR_RNDN);
                mpfr_set_str(global_range4, global_range4_str, 10, MPFR_RNDN);
                break;
            case 4:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_LOG_2;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("digits / PN is log(2)\n");
                printf("Printing log(2)\n");
                print_digits_PN();
                printf("log(2) printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_choice_save = 2;
                global_list_line_backup = global_list_line;
                break;
            case 5:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_LOG_2_TOTAL;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("digits / PN is log(2)\n");
                printf("Printing log(2)\n");
                print_digits_PN_total();
                printf("log(2) printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_choice_save = 2;
                global_list_line_backup = global_list_line;
                break;
            case 6:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_1_DIV_LOG_2;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("PN / digits is 1 / log(2)\n");
                printf("Printing 1 / log(2)\n");
                print_PN_digits();
                printf("1 / log(2) printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_choice_save = 3;
                global_list_line_backup = global_list_line;
                break;
            case 7:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_1_DIV_LOG_2_TOTAL;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("PN / digits is 1 / log(2)\n");
                printf("Printing 1 / log(2)\n");
                print_PN_digits_total();
                printf("1 / log(2) printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_choice_save = 3;
                global_list_line_backup = global_list_line;
                break;
            case 8:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_LOG_2_AND_1_DIV_LOG_2;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Printing log(2) and 1 / log(2)\n");
                print_digits_PN_and_PN_digits();
                printf("log(2) and 1 / log(2) printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_choice_save = 4;
                global_list_line_backup = global_list_line;
                break;
            case 9:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_LOG_2_AND_1_DIV_LOG_2_TOTAL;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Printing log(2) and 1 / log(2)\n");
                print_digits_PN_and_PN_digits_total();
                printf("log(2) and 1 / log(2) printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_choice_save = 4;
                global_list_line_backup = global_list_line;
                break;
            case 10:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_LOG_10_2;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                input = get_input_string("Enter search value: ");
                token = strtok(input, " ");
                token_count = 0;
                while (token != NULL)
                {
                    strcpy(input_array[token_count], token);
                    token_count++;
                    token = strtok(NULL, " ");
                }
                printf("Searching numbers in the range\n");
                search_log10_2(input_array, token_count);
                printf("Numbers in the range searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 11:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_LOG_10_DIV_1;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                input = get_input_string("Enter search value: ");
                token = strtok(input, " ");
                token_count = 0;
                while (token != NULL)
                {
                    strcpy(input_array[token_count], token);
                    token_count++;
                    token = strtok(NULL, " ");
                }
                printf("Searching numbers in the range\n");
                search_log10_2_div_1(input_array, token_count);
                printf("Numbers in the range searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 12:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_RANGE_NUMBER;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[9] = category_type;
                category[10] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("1. log(2)\n");
                printf("2. 1 / log(2)\n");
                printf("3. log(2) and 1 / log(2)\n");
                choice_save = atoi(get_input("Enter the choice: "));
                filename = get_input("Enter the filename to save the output: ");
                printf("Saving the output to %s\n", filename);
                save(filename, global_str1, global_str2, choice_save);
                printf("Output saved to %s\n", filename);
                global_list_line_backup = global_list_line;
                break;
            case 13:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_RANGE_NUMBER_ONLY_PRIME;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[9] = category_type;
                category[10] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("1. log(2)\n");
                printf("2. 1 / log(2)\n");
                printf("3. log(2) and 1 / log(2)\n");
                choice_save = atoi(get_input("Enter the choice: "));
                filename = get_input("Enter the filename to save the prime numbers: ");
                printf("Saving the prime numbers to %s\n", filename);
                save_prime(filename, global_str1, global_str2, choice_save);
                printf("Prime numbers saved to %s\n", filename);
                global_list_line_backup = global_list_line;
                break;
            case 14:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_LOAD_YES;
                category_content = CATEGORY_LOAD_DATA;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[11] = category_type;
                category[12] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                filename = get_input("Enter the filename to load the output: ");
                printf("Loading the output from %s\n", filename);
                load(filename);
                printf("Output loaded from %s\n", filename);
                global_list_line_backup = global_list_line;
                break;
            case 15:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_RANGE_NUMBER;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("1. log(2)\n");
                printf("2. 1 / log(2)\n");
                printf("3. log(2) and 1 / log(2)\n");
                printf("Enter the choice: ");
                scanf("%d", &choice_save);
                getchar();
                printf("Printing only the prime numbers\n");
                print_list(choice_save);
                printf("Prime numbers printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_list_line_backup = global_list_line;
                break;
            case 16:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_RANGE_NUMBER_TOTAL;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("1. log(2)\n");
                printf("2. 1 / log(2)\n");
                printf("3. log(2) and 1 / log(2)\n");
                printf("Enter the choice: ");
                scanf("%d", &choice_save);
                getchar();
                printf("Printing only the prime numbers\n");
                print_prime_list(choice_save);
                printf("Prime numbers printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_list_line_backup = global_list_line;
                break;
            case 17:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_LOG_10_2_AGAIN;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                input = get_input_string("Enter search value: ");
                token = strtok(input, " ");
                token_count = 0;
                while (token != NULL)
                {
                    strcpy(input_array[token_count], token);
                    token_count++;
                    token = strtok(NULL, " ");
                }
                printf("Searching numbers in the range\n");
                search_log10_2_again(input_array, token_count);
                printf("Numbers in the range searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 18:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_LOG_10_DIV_1_AGAIN;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                input = get_input_string("Enter search value: ");
                token = strtok(input, " ");
                token_count = 0;
                while (token != NULL)
                {
                    strcpy(input_array[token_count], token);
                    token_count++;
                    token = strtok(NULL, " ");
                }
                printf("Searching numbers in the range\n");
                search_log10_2_div_1_again(input_array, token_count);
                printf("Numbers in the range searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 19:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_DATA;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[9] = category_type;
                category[10] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("1. log(2)\n");
                printf("2. 1 / log(2)\n");
                printf("3. log(2) and 1 / log(2)\n");
                printf("Enter the choice: ");
                scanf("%d", &choice_save);
                getchar();
                printf("Input the filename to save the prime numbers: ");
                scanf("%s", filename);
                getchar();
                printf("Saving only the prime numbers to %s\n", filename);
                save_list(filename, choice_save);
                printf("Prime numbers saved to %s\n", filename);
                break;
            case 20:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_DATA_ONLY_PRIME;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[9] = category_type;
                category[10] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("1. log(2)\n");
                printf("2. 1 / log(2)\n");
                printf("3. log(2) and 1 / log(2)\n");
                printf("Enter the choice: ");
                scanf("%d", &choice_save);
                getchar();
                printf("Input the filename to save the prime numbers: ");
                scanf("%s", filename);
                getchar();
                printf("Saving only the prime numbers to %s\n", filename);
                save_list_prime(filename, choice_save);
                printf("Prime numbers saved to %s\n", filename);
                break;
            case 21:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_LOAD_YES;
                category_content = CATEGORY_LOAD_DATA;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[11] = category_type;
                category[12] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                filename = get_input("Enter the filename to load the output: ");
                printf("Loading the output from %s\n", filename);
                load_list(filename);
                printf("Output loaded from %s\n", filename);
                global_list_line_backup = global_list_line;
                break;
            case 0:
                printf("Exiting the program\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
        if (category[2] == CATEGORY_INPUT_YES)
        {
            global_list_line = 0;
        }

        if (category[4] == CATEGORY_PRINT_YES || category[7] == CATEGORY_SEARCH_YES)
        {
            category[2] = CATEGORY_INPUT_NO;

            global_list_line = global_list_line_backup;
        }

    } while (choice != 0);
    category_menu = CATEGORY_MENU_NO;

    free(global_str1);
    free(global_str2);
    free(filename);
    mpz_clear(n1);
    mpz_clear(n2);
    mpz_clear(count);
    mpfr_clear(var1);
    mpfr_clear(var2);

    return 0;
}

// View menu
void view_menu()
{
    // Welcome message
    printf("*************************************************\n");
    printf("*     Welcome to the Mersenne Prime Number      *\n");
    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("*             LOG-FLOW Version 0.1              *\n");
    printf("*                                               *\n"); 
    printf("*************************************************************************************************\n");
    printf("*  1. Input the first number, last number       *         Save to list and recalculate          *\n");
    printf("*  2. Input range1, range2 ( log(2) )           *   ( Search results are saved in the list )    *\n");
    printf("*  3. Input range1, range2 ( 1 / log(2) )       *************************************************\n");
    printf("************************************************* 15. Print numbers in the list                 *\n");
    printf("*  4. Print log(2)                              * 16. Print statistics of numbers in the list   *\n");
    printf("*  5. Print statistics of log(2)                * 17. Search log(2) in the list                 *\n");
    printf("*  6. Print 1 / log(2)                          * 18. Search 1 / log(2) in the list             *\n");
    printf("*  7. Print statistics of 1 / log(2)            *************************************************\n");
    printf("*  8. Print log(2) and 1 / log(2)               * 19. Save numbers in the list                  *\n");
    printf("*  9. Print statistics of log(2) and 1 / log(2) * 20. Save only prime numbers in the list       *\n");
    printf("* 10. Search log(2)                             * 21. Load list data from the file              *\n");
    printf("* 11. Search 1 / log(2)                         *************************************************\n");
    printf("*   ( Search results are saved in the list )    *                                               *\n");
    printf("*************************************************                                               *\n");
    printf("* 12. Save the first number, last number        *                                               *\n");
    printf("* 13. Save only prime numbers                   *                                               *\n");
    printf("* 14. Load range data from the file             *                                               *\n");
    printf("*************************************************                                               *\n");
    printf("* 0. Exit                                       *                                               *\n");
    printf("*************************************************************************************************\n");

    return;
}

// Get input from user
char *get_input(char *prompt)
{
    char *buffer = (char *)malloc(1000 * sizeof(char));

    printf("%s", prompt);
    while (fgets(buffer, 1000, stdin) != NULL)
    {
        if (strlen(buffer) == 1)
        {
            printf("Error: No input\n");
            printf("%s", prompt);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;
        break;
    }

    if (buffer == NULL)
    {
        printf("Error: Unable to get input\n");
        return NULL;
    }

    return buffer;
}

// Get input from user as string
char *get_input_string(char *prompt)
{
    char *buffer = (char *)malloc(1000 * sizeof(char));

    printf("%s", prompt);
    while (fgets(buffer, 1000, stdin) != NULL)
    {
        if (strlen(buffer) == 1)
        {
            printf("Error: No input\n");
            printf("%s", prompt);
            continue;
        }

        buffer[strlen(buffer)] = 0;
        break;
    }

    if (buffer == NULL)
    {
        printf("Error: Unable to get input\n");
        return NULL;
    }

    return buffer;
}

// Get input from user as array of strings
char **get_input_array(char *prompt, int size)
{
    char *buffer = (char *)malloc(1000 * sizeof(char));
    char **input_array = (char **)malloc(1000 * sizeof(char *));
    char *token;
    int token_count = 0;

    for (int i = 0; i < 1000; i++)
    {
        input_array[i] = (char *)malloc(1000 * sizeof(char));
    }

    printf("%s", prompt);
    while (fgets(buffer, 1000, stdin) != NULL)
    {
        if (strlen(buffer) == 1)
        {
            printf("Error: No input\n");
            printf("%s", prompt);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;
        token = strtok(buffer, " ");
        while (token != NULL)
        {
            strcpy(input_array[token_count], token);
            token_count++;
            if (token_count >= size)
            {
                break;
            }
            token = strtok(NULL, " ");
        }
        break;
    }

    if (buffer == NULL)
    {
        printf("Error: Unable to get input\n");
        return NULL;
    }

    return input_array;
}


// Function to check if a number is prime
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i = i + 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to check if a number is prime using GMP
int isPrimeGMP(mpz_t n)
{
    return mpz_probab_prime_p(n, 25);
}

void log10_2(char *res)
{
    mpfr_t temp;
    mpfr_init2(temp, 1024);

    mpfr_set_ui(temp, 2, MPFR_RNDN);
    
    mpfr_log10(temp, temp, MPFR_RNDN);
    mpfr_sprintf(res, "%.30Rf", temp);
    
    mpfr_clear(temp);

    return;
}

void log10_div_1(char *res)
{
    mpfr_t temp;
    mpfr_t one;
    mpfr_init2(temp, 1024);
    mpfr_init2(one, 1024);
    
    mpfr_set_ui(temp, 2, MPFR_RNDN);   
    mpfr_set_ui(one, 1, MPFR_RNDN);
    
    mpfr_log10(temp, temp, MPFR_RNDN);
    mpfr_div(temp, one, temp, MPFR_RNDN);
    mpfr_sprintf(res, "%.30Rf", temp);
    
    mpfr_clear(temp);
    mpfr_clear(one);

    return;
}

void log10_2_digits(mpfr_t n, char *res)
{
    char *str_log2_2;
    char *digits;
    char *token;
    mpfr_t temp;
    
    str_log2_2 = (char *)malloc(1000 * sizeof(char));
    digits = (char *)malloc(1000 * sizeof(char));
    token = (char *)malloc(1000 * sizeof(char));
    mpfr_init2(temp, 1024);
    
    log10_2(str_log2_2);
    mpfr_set_str(temp, str_log2_2, 10, MPFR_RNDN);
    mpfr_mul(temp, n, temp, MPFR_RNDN);
    mpfr_sprintf(token, "%.30Rf", temp);
    digits = strtok(token, ".");
    mpfr_set_str(temp, digits, 10, MPFR_RNDN);
    mpfr_add_ui(temp, temp, 1, MPFR_RNDN);
    mpfr_sprintf(res, "%.30Rf", temp);
    
    free(str_log2_2);
    //free(digits);
    free(token);
    mpfr_clear(temp);

    return;
}

void div_PN_digits(mpfr_t n, char *res)
{
    char *str_log2_2;
    char *digits;
    char *token;
    mpfr_t temp;
    
    str_log2_2 = (char *)malloc(1000 * sizeof(char));
    digits = (char *)malloc(1000 * sizeof(char));
    token = (char *)malloc(1000 * sizeof(char));
    mpfr_init2(temp, 1024);
    
    log10_2_digits(n, digits);
    mpfr_set_str(temp, digits, 10, MPFR_RNDN);
    mpfr_div(temp, n, temp, MPFR_RNDN);
    mpfr_sprintf(res, "%.30Rf", temp);

    free(str_log2_2);
    //free(digits);
    free(token);
    mpfr_clear(temp);

    return;
}

void div_digits_PN(mpfr_t n, char *res)
{
    char *digits;
    mpfr_t temp;

    digits = (char *)malloc(1000 * sizeof(char));
    mpfr_init2(temp, 1024);
    
    log10_2_digits(n, digits);
    mpfr_set_str(temp, digits, 10, MPFR_RNDN);
    mpfr_div(temp, temp, n, MPFR_RNDN);
    mpfr_sprintf(res, "%.30Rf", temp);

    free(digits);
    mpfr_clear(temp);

    return;
}

char * get_delete_string(char *str, int start, int end)
{
    char *new_str;
    int i;
    int j;

    new_str = (char *)malloc(1000 * sizeof(char));
    memset(new_str, 0, 1000);

    for (i = 0, j = 0; i < strlen(str); i++)
    {
        if (i >= start && i <= end)
        {
            continue;
        }
        new_str[j] = str[i];
        j++;
    }

    return new_str;
}

char *get_delete_first_string(char *str, int end)
{
    char *new_str;
    int i;
    int j;

    new_str = (char *)malloc(1000 * sizeof(char));
    memset(new_str, 0, 1000);

    for (i = 0, j = 0; i < strlen(str); i++)
    {
        if (i <= end)
        {
            continue;
        }
        new_str[j] = str[i];
        j++;
    }

    return new_str;
}

char *get_delete_last_string(char *str, int start)
{
    char *new_str;
    int i;
    int j;

    new_str = (char *)malloc(1000 * sizeof(char));
    memset(new_str, 0, 1000);

    for (i = 0, j = 0; i < strlen(str); i++)
    {
        if (i >= start)
        {
            continue;
        }
        new_str[j] = str[i];
        j++;
    }

    return new_str;
}

char *get_delete_middle_string(char *str, int start, int end)
{
    char *new_str;
    int i;
    int j;

    new_str = (char *)malloc(1000 * sizeof(char));
    memset(new_str, 0, 1000);

    for (i = 0, j = 0; i < strlen(str); i++)
    {
        if (i >= start && i <= end)
        {
            continue;
        }
        new_str[j] = str[i];
        j++;
    }

    return new_str;
}

void print_PN_digits(void)
{
    char *res;
    long line;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;

    res = (char *)malloc(1000 * sizeof(char));
    line = 0;
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);

    mpfr_set(n1, global_first, MPFR_RNDN);
    mpfr_set(n2, global_last, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        if (isPrimeGMP(prime) != 0)
        {
            div_PN_digits(n1, res);
            mpfr_set_str(range, res, 10, MPFR_RNDN);
            if (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0)
            {
                mpfr_printf("%.0Rf %s\n", n1, res);
                line++;
            }
        }
    }

    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return;
}

void print_PN_digits_total(void)
{
    char *res;
    char *res_length;
    char *res_value;
    char *res_temp;
    char *log10_div_1_str;
    int res_array[50][1000];
    int length;
    long line;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;

    res = (char *)malloc(1000 * sizeof(char));
    res_length = (char *)malloc(1000 * sizeof(char));
    res_value = (char *)malloc(1000 * sizeof(char));
    res_temp = (char *)malloc(1000 * sizeof(char));
    log10_div_1_str = (char *)malloc(1000 * sizeof(char));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            res_array[i][j] = 0;
        }
    }
    length = 0;
    line = 0;
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);

    mpfr_set(n1, global_first, MPFR_RNDN);
    mpfr_set(n2, global_last, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        length = strlen(res);
        if (isPrimeGMP(prime) != 0)
        {
            div_PN_digits(n1, res);
            res_length = get_delete_middle_string(res, 1, 1);
            //if (length == 1)
            //    res_length = get_delete_last_string(res_length, 2);
            //else if (length == 2)
            //    res_length = get_delete_last_string(res_length, 2);
            //else
            if (length < 8)
            { 
                res_length = get_delete_first_string(res_length, length - 3);
                res_length = get_delete_last_string(res_length, 2);
            }
            else
            {
                res_length = get_delete_first_string(res_length, length - 4);
                res_length = get_delete_last_string(res_length, 3);
            }
            log10_div_1(res_value);
            for (int i = 0; i < 1000; i++)
            {
                if (atoi(res_length) == i)
                {
                    res_array[length - 1][i]++;
                }
            }
        }
    }

    // Print the statistics to one line for each length
    for (int i = 0; i < 50; i++)
    {
        log10_div_1_str = get_delete_string(res_value, i, strlen(res_value) - 1);
        for (int j = 0; j < 1000; j++)
        {
            if (res_array[i][j] != 0)
            {
                printf("%d ", i + 1);
                if (i < 2)
                {
                    sprintf(log10_div_1_str, "%d", j);
                    printf("%c.", log10_div_1_str[0]);
                    for (int k = 1; k < strlen(log10_div_1_str); k++)
                    {
                        printf("%c", log10_div_1_str[k]);
                    }
                    printf(" %d\n", res_array[i][j]);
                }
                else if (i < 8)
                    printf("%s%d %d\n", log10_div_1_str, j, res_array[i][j]);
                else
                {
                    log10_div_1_str = get_delete_middle_string(log10_div_1_str, length - 2, length - 2);
                    printf("%s%d %d\n", log10_div_1_str, j, res_array[i][j]);
                }
                line++;
            }
        }
    }

    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    free(res_length);
    free(res_value);
    free(res_temp);
    free(log10_div_1_str);
    mpz_clear(prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return;
}

void print_digits_PN(void)
{
    char *res;
    long line;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;

    res = (char *)malloc(1000 * sizeof(char));
    line = 0;
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);

    mpfr_set(n1, global_first, MPFR_RNDN);
    mpfr_set(n2, global_last, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        if (isPrimeGMP(prime) != 0)
        {
            div_digits_PN(n1, res);
            mpfr_set_str(range, res, 10, MPFR_RNDN);
            if (mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0)
            {   
                mpfr_printf("%.0Rf %s\n", n1, res);
                line++;
            }
        }
    }

    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return;
}

void print_digits_PN_total(void)
{
    char *res;
    char *res_length;
    char *res_value;
    char *log10_2_str;
    int res_array[50][10];
    int length;
    long line;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;

    res = (char *)malloc(1000 * sizeof(char));
    res_length = (char *)malloc(1000 * sizeof(char));
    res_value = (char *)malloc(1000 * sizeof(char));
    log10_2_str = (char *)malloc(1000 * sizeof(char));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            res_array[i][j] = 0;
        }
    }
    length = 0;
    line = 0;
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);

    mpfr_set(n1, global_first, MPFR_RNDN);
    mpfr_set(n2, global_last, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        length = strlen(res);
        if (isPrimeGMP(prime) != 0)
        {
            div_digits_PN(n1, res);
            strncpy(res_length, res, length + 2);
            res_length[length + 2] = '\0';
            log10_2(res_value);
            res_length = get_delete_string(res_length, 0, 1 + length - 1);
            for (int i = 0; i < 10; i++)
            {
                if (atoi(res_length) == i)
                {
                    res_array[length - 1][i]++;
                    line++;
                }
            }
        }
    }

    // Print the statistics to one line for each length
    for (int i = 0; i < 50; i++)
    {
        log10_2_str = get_delete_string(res_value, 3 + i - 1, strlen(res_value) - 1);
        for (int j = 0; j < 10; j++)
        {
            if (res_array[i][j] != 0)
            {
                printf("%s%d %d\n", log10_2_str, j, res_array[i][j]);
            }
        }
    }

    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    free(res_length);
    free(res_value);
    free(log10_2_str);
    mpz_clear(prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return;
}

void print_digits_PN_and_PN_digits(void)
{
    char *res;
    char *res_temp1;
    char *res_temp2;
    long line;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range_temp1;
    mpfr_t range_temp2;

    res = (char *)malloc(1000 * sizeof(char));
    res_temp1 = (char *)malloc(1000 * sizeof(char));
    res_temp2 = (char *)malloc(1000 * sizeof(char));
    line = 0;
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range_temp1, 1024);
    mpfr_init2(range_temp2, 1024);

    mpfr_set(n1, global_first, MPFR_RNDN);
    mpfr_set(n2, global_last, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        if (isPrimeGMP(prime) != 0)
        {
            div_digits_PN(n1, res_temp1);
            div_PN_digits(n1, res_temp2);
            mpfr_set_str(range_temp1, res_temp1, 10, MPFR_RNDN);
            mpfr_set_str(range_temp2, res_temp2, 10, MPFR_RNDN);
            if (mpfr_cmp(range_temp1, global_range1) >= 0 && mpfr_cmp(range_temp1, global_range2) <= 0 && mpfr_cmp(range_temp2, global_range3) >= 0 && mpfr_cmp(range_temp2, global_range4) <= 0)
            {
                mpfr_printf("%.0Rf %s %s\n", n1, res_temp1, res_temp2);
                line++;
            }
        }
    }

    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    free(res_temp1);
    free(res_temp2);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range_temp1);
    mpfr_clear(range_temp2);

    return;
}

void print_digits_PN_and_PN_digits_total(void)
{
    char *res;
    char *res_temp1;
    char *res_temp2;
    long line;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range_temp1;
    mpfr_t range_temp2;

    char *res_1;
    char *res_length_1;
    char *res_value_1;
    char *log10_2_str_1;
    int res_array_1[50][10];
    int length_1;
    mpz_t prime_1;
    mpfr_t n1_1;
    mpfr_t n2_1;
    mpfr_t range_1;

    char *res_2;
    char *res_length_2;
    char *res_value_2;
    char *log10_div_1_str_2;
    int res_array_2[50][1000];
    int length_2;
    mpz_t prime_2;
    mpfr_t n1_2;
    mpfr_t n2_2;
    mpfr_t range_2;

    res = (char *)malloc(1000 * sizeof(char));
    res_temp1 = (char *)malloc(1000 * sizeof(char));
    res_temp2 = (char *)malloc(1000 * sizeof(char));
    line = 0;
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range_temp1, 1024);
    mpfr_init2(range_temp2, 1024);
    mpfr_set(n1, global_first, MPFR_RNDN);
    mpfr_set(n2, global_last, MPFR_RNDN);

    res_1 = (char *)malloc(1000 * sizeof(char));
    res_length_1 = (char *)malloc(1000 * sizeof(char));
    res_value_1 = (char *)malloc(1000 * sizeof(char));
    log10_2_str_1 = (char *)malloc(1000 * sizeof(char));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            res_array_1[i][j] = 0;
        }
    }
    length_1 = 0;
    mpz_init2(prime_1, 1024);
    mpfr_init2(n1_1, 1024);
    mpfr_init2(n2_1, 1024);
    mpfr_init2(range_1, 1024);
    mpfr_set(n1_1, global_first, MPFR_RNDN);
    mpfr_set(n2_1, global_last, MPFR_RNDN);

    res_2 = (char *)malloc(1000 * sizeof(char));
    res_length_2 = (char *)malloc(1000 * sizeof(char));
    res_value_2 = (char *)malloc(1000 * sizeof(char));
    log10_div_1_str_2 = (char *)malloc(1000 * sizeof(char));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            res_array_2[i][j] = 0;
        }
    }
    length_2 = 0;
    mpz_init2(prime_2, 1024);
    mpfr_init2(n1_2, 1024);
    mpfr_init2(n2_2, 1024);
    mpfr_init2(range_2, 1024);
    mpfr_set(n1_2, global_first, MPFR_RNDN);
    mpfr_set(n2_2, global_last, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        length_1 = strlen(res);
        length_2 = strlen(res);
        mpfr_set(n1_1, n1, MPFR_RNDN);
        mpfr_set(n2_1, n2, MPFR_RNDN);
        mpfr_set(n1_2, n1, MPFR_RNDN);
        mpfr_set(n2_2, n2, MPFR_RNDN);
        if (isPrimeGMP(prime) != 0)
        {
            div_digits_PN(n1_1, res_1);
            div_PN_digits(n1_2, res_2);
            
            div_digits_PN(n1, res_temp1);
            div_PN_digits(n1, res_temp2);
            mpfr_set_str(range_temp1, res_temp1, 10, MPFR_RNDN);
            mpfr_set_str(range_temp2, res_temp2, 10, MPFR_RNDN);
            if (mpfr_cmp(range_temp1, global_range1) >= 0 && mpfr_cmp(range_temp1, global_range2) <= 0 && mpfr_cmp(range_temp2, global_range3) >= 0 && mpfr_cmp(range_temp2, global_range4) <= 0)
            {
                strncpy(res_length_1, res_1, length_1 + 2);
                res_length_1[length_1 + 2] = '\0';
                log10_2(res_value_1);
                res_length_1 = get_delete_string(res_length_1, 0, 1 + length_1 - 1);
                for (int i = 0; i < 10; i++)
                {
                    if (atoi(res_length_1) == i)
                    {
                        res_array_1[length_1 - 1][i]++;
                    }
                }
                res_length_2 = get_delete_middle_string(res_2, 1, 1);
                if (length_2 < 8)
                {
                    res_length_2 = get_delete_first_string(res_length_2, length_2 - 3);
                    res_length_2 = get_delete_last_string(res_length_2, 2);
                }
                else
                {
                    res_length_2 = get_delete_first_string(res_length_2, length_2 - 4);
                    res_length_2 = get_delete_last_string(res_length_2, 3);
                }
                log10_div_1(res_value_2);
                for (int i = 0; i < 1000; i++)
                {
                    if (atoi(res_length_2) == i)
                    {
                        res_array_2[length_2 - 1][i]++;
                    }
                }
                line++;
            }
        }
    }

    // Print the statistics to one line for each length
    for (int i = 0; i < 50; i++)
    {
        log10_2_str_1 = get_delete_string(res_value_1, 3 + i - 1, strlen(res_value_1) - 1);
        log10_div_1_str_2 = get_delete_string(res_value_2, i, strlen(res_value_2) - 1);
        for (int j = 0; j < 10; j++)
        {
            if (res_array_1[i][j] != 0)
            {
                printf("[ %2d : ", i + 1);
                printf("%s%d", log10_2_str_1, j);
                //for (int k = 0; k < 20 - strlen(log10_2_str_1) - 1; k++)
                {
                //    printf(" ");
                }
                printf(": %9d ]", res_array_1[i][j]);
                printf("\n");
            }
        }
        for (int j = 0; j < 1000; j++)
        {
            if (res_array_2[i][j] != 0)
            {
                printf("( %2d : ", i + 1);
                if (i < 2)
                {
                    sprintf(log10_div_1_str_2, "%d", j);
                    printf("%c.", log10_div_1_str_2[0]);
                    for (int k = 1; k < strlen(log10_div_1_str_2); k++)
                    {
                        printf("%c", log10_div_1_str_2[k]);
                    }
                    printf(" : %9d )\n", res_array_2[i][j]);
                }
                else if (i < 8)
                    printf("%s%d : %9d )\n", log10_div_1_str_2, j, res_array_2[i][j]);
                else
                {
                    log10_div_1_str_2 = get_delete_middle_string(log10_div_1_str_2, length_2 - 2, length_2 - 2);
                    printf("%s%d : %9d )\n", log10_div_1_str_2, j, res_array_2[i][j]);
                }
            }
        }
    }

    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    free(res_temp1);
    free(res_temp2);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range_temp1);
    mpfr_clear(range_temp2);

    free(res_1);
    free(res_length_1);
    free(res_value_1);
    free(log10_2_str_1);
    mpz_clear(prime_1);
    mpfr_clear(n1_1);
    mpfr_clear(n2_1);
    mpfr_clear(range_1);

    free(res_2);
    free(res_length_2);
    free(res_value_2);
    free(log10_div_1_str_2);
    mpz_clear(prime_2);
    mpfr_clear(n1_2);
    mpfr_clear(n2_2);
    mpfr_clear(range_2);

    return;
}

int save(char *filename, char *range1, char *range2, int choice_save)
{
    char *res;
    char *res_temp1;
    char *res_temp2;
    FILE *fp;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;
    mpfr_t range_temp1;
    mpfr_t range_temp2;

    res = (char *)malloc(1000 * sizeof(char));
    res_temp1 = (char *)malloc(1000 * sizeof(char));
    res_temp2 = (char *)malloc(1000 * sizeof(char));
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range_temp1, 1024);
    mpfr_init2(range_temp2, 1024);

    mpfr_set_str(n1, global_first_str, 10, MPFR_RNDN);
    mpfr_set_str(n2, global_last_str, 10, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        if (isPrimeGMP(prime) != 0)
        {
            if (choice_save == 1)
            {
                div_digits_PN(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf %s\n", n1, res);
                }
            }
            else if (choice_save == 2)
            {
                div_PN_digits(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf %s\n", n1, res);
                }
            }
            else
            {
                div_digits_PN(n1, res_temp1);
                div_PN_digits(n1, res_temp2);
                mpfr_set_str(range_temp1, res_temp1, 10, MPFR_RNDN);
                mpfr_set_str(range_temp2, res_temp2, 10, MPFR_RNDN);
                if (mpfr_cmp(range_temp1, global_range1) >= 0 && mpfr_cmp(range_temp1, global_range2) <= 0 && mpfr_cmp(range_temp2, global_range3) >= 0 && mpfr_cmp(range_temp2, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf %s %s\n", n1, res_temp1, res_temp2);
                }
            }
        }
    }

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    fclose(fp);
    mpz_clear(prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return 0;
}

int save_prime(char *filename, char *range1, char *range2, int choice_save)
{
    char *res;
    char *res_temp1;
    char *res_temp2;
    FILE *fp;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;
    mpfr_t range_temp1;
    mpfr_t range_temp2;

    res = (char *)malloc(1000 * sizeof(char));
    res_temp1 = (char *)malloc(1000 * sizeof(char));
    res_temp2 = (char *)malloc(1000 * sizeof(char));
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range_temp1, 1024);
    mpfr_init2(range_temp2, 1024);

    mpfr_set_str(n1, global_first_str, 10, MPFR_RNDN);
    mpfr_set_str(n2, global_last_str, 10, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); mpfr_cmp(n1, n2) <= 0; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        if (isPrimeGMP(prime) != 0)
        {
            if (choice_save == 1)
            {
                div_PN_digits(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf\n", n1);
                }
            }
            else if (choice_save == 2)
            {
                div_digits_PN(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf\n", n1);
                }
            }
            else
            {
                div_digits_PN(n1, res_temp1);
                div_PN_digits(n1, res_temp2);
                mpfr_set_str(range_temp1, res_temp1, 10, MPFR_RNDN);
                mpfr_set_str(range_temp2, res_temp2, 10, MPFR_RNDN);
                if (mpfr_cmp(range_temp1, global_range1) >= 0 && mpfr_cmp(range_temp1, global_range2) <= 0 && mpfr_cmp(range_temp2, global_range3) >= 0 && mpfr_cmp(range_temp2, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf\n", n1);
                }
            }
        }
    }

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    fclose(fp);
    mpz_clear(prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return 0;
}

int load(char *filename)
{
    char *str;
    char *data1_str;
    char *data2_str;
    char *data3_str;
    char *token;
    char *token_temp;
    int choice_load;
    int token_count;
    int check;
    long line;
    FILE *fptr;
    mpfr_t data1;
    mpfr_t data2;
    mpfr_t data3;

    str = (char *)malloc(1000 * sizeof(char));
    data1_str = (char *)malloc(1000 * sizeof(char));
    data2_str = (char *)malloc(1000 * sizeof(char));
    data3_str = (char *)malloc(1000 * sizeof(char));
    token = (char *)malloc(1000 * sizeof(char));
    token_temp = (char *)malloc(1000 * sizeof(char));
    choice_load = 0;
    token_count = 0;
    check = 0;
    line = 0;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpfr_init2(data1, 1024);
    mpfr_init2(data2, 1024);
    mpfr_init2(data3, 1024);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // check the type of data
    while (fgets(data1_str, 1000, fptr) != NULL)
    {
        data2_str = strtok(data1_str, " ");
        while (data2_str != NULL)
        {
            token_count++;
            switch (token_count)
            {
                case 1:
                    for (int i = 0; i < strlen(data2_str); i++)
                    {
                        if (isdigit(data2_str[i]) == 0)
                        {
                            choice_load = 0;
                            break;
                        }
                        else
                        {
                            choice_load = 1;
                            break;
                        }
                    }
                    break;
                case 2:
                    if (data2_str[0] == '0' && data2_str[1] == '.') 
                    {
                        for (int i = 2; i < strlen(data2_str); i++)
                        {
                            if (isdigit(data2_str[i]) == 0)
                            {
                                choice_load = 0;
                                break;
                            }
                            else
                            {
                                choice_load = 2;
                                break;
                            }
                        }
                    }
                    else if ((data2_str[0] == '2' || data2_str[0] == '3') && data2_str[1] == '.')
                    {
                        for (int i = 2; i < strlen(data2_str); i++)
                        {
                            if (isdigit(data2_str[i]) == 0)
                            {
                                choice_load = 0;
                                break;
                            }
                            else
                            {
                                choice_load = 3;
                                break;
                            }
                        }
                    }
                    break;
                case 3:
                    if ((data2_str[0] == '2' || data2_str[0] == '3') && data2_str[1] == '.')
                    {
                        for (int i = 2; i < strlen(data2_str); i++)
                        {
                            if (isdigit(data2_str[i]) == 0)
                            {
                                choice_load = 0;
                                break;
                            }
                            else
                            {
                                choice_load = 4;
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;;
            }
            data2_str = strtok(NULL, " ");
        }
    }

    global_choice_save = choice_load;

    fseek(fptr, 0, SEEK_SET);
    // Use fgets to read the file line by line
    while (fgets(data1_str, 1000, fptr) != NULL)
    {

        data2_str = strtok(data1_str, " ");
        mpfr_set_str(data2, data2_str, 10, MPFR_RNDN);
        
        if (check == 0)
        {
            mpfr_set_str(global_first, data2_str, 10, MPFR_RNDN);
            check = 1;
        }
        else
        {
            mpfr_set_str(global_last, data2_str, 10, MPFR_RNDN);
        }
        line++;
    }
    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    free(data1_str);
    // free(data2_str);
    free(data3_str);
    free(token);
    free(token_temp);
    fclose(fptr);
    mpfr_clear(data1);
    mpfr_clear(data2);
    mpfr_clear(data3);

    return 0;
}

int load_prime(char *filename)
{

    char *str;
    char *data1_str;
    char *data2_str;
    char *data3_str;
    char *token;
    char *token_temp;
    int check;
    int count;
    FILE *fptr;
    mpfr_t data1;
    mpfr_t data2;
    mpfr_t data3;

    str = (char *)malloc(1000 * sizeof(char));
    data1_str = (char *)malloc(1000 * sizeof(char));
    data2_str = (char *)malloc(1000 * sizeof(char));
    data3_str = (char *)malloc(1000 * sizeof(char));
    token = (char *)malloc(1000 * sizeof(char));
    token_temp = (char *)malloc(1000 * sizeof(char));
    check = 0;
    count = 0;
    memset(str, 0, 1000);
    memset(data1_str, 0, 1000);
    memset(data2_str, 0, 1000);
    memset(data3_str, 0, 1000);
    memset(token, 0, 1000);
    memset(token_temp, 0, 1000);
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpfr_init2(data1, 1024);
    mpfr_init2(data2, 1024);
    mpfr_init2(data3, 1024);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    while (fscanf(fptr, "%s", data1_str) != EOF)
    {
        mpfr_set_str(data1, data1_str, 10, MPFR_RNDN);
        mpfr_printf("%.0Rf\n", data1);
        if (check == 0)
        {
            mpfr_set_str(global_first, data1_str, 10, MPFR_RNDN);
            mpfr_set_str(global_range1, data2_str, 10, MPFR_RNDN);
            mpfr_set_str(global_range3, data3_str, 10, MPFR_RNDN);
            check = 1;
            count++;
        }
        else
        {
            mpfr_set_str(global_last, data1_str, 10, MPFR_RNDN);
            mpfr_set_str(global_range2, data2_str, 10, MPFR_RNDN);
            mpfr_set_str(global_range4, data3_str, 10, MPFR_RNDN);
            count++;
        }
    }

    global_list_line = count;

    global_list = (mpfr_t *)malloc(count * sizeof(mpfr_t));

    for (int i = 0; i < count; i++)
    {
        mpfr_init2(global_list[i], 1024);
    }

    rewind(fptr);
    count = 0;

    while (fscanf(fptr, "%s", data1_str) != EOF)
    {
        mpfr_set_str(data1, data1_str, 10, MPFR_RNDN);
        mpfr_set(global_list[count], data1, MPFR_RNDN);
        while(fgetc(fptr) != '\n');
        count++;
    }

    global_list_line = count;
    
    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    free(data1_str);
    free(data2_str);
    free(data3_str);
    fclose(fptr);
    mpfr_clear(data1);
    mpfr_clear(data2);
    mpfr_clear(data3);

    return 0;
}

void print_list(int choice_save)
{
    char *res;
    long total;
    mpz_t only_prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;

    res = (char *)malloc(1000 * sizeof(char));
    total = 0;
    mpz_init(only_prime);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    if (global_list_line == 0)
    {
        printf("No prime numbers found\n");
        return;
    }

    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_get_z(only_prime, global_list[i], MPFR_RNDN);;

            mpfr_set_z(n1, only_prime, MPFR_RNDN);

                if (choice_save == 1)
                {
                    div_digits_PN(n1, res);
                    mpfr_set_str(range, res, 10, MPFR_RNDN);
                    if (mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0)
                    {
                        mpfr_printf("%.0Rf %s\n", n1, res);
                        total++;
                    }
                }
                else if (choice_save == 2)
                {
                    div_PN_digits(n1, res);
                    mpfr_set_str(range, res, 10, MPFR_RNDN);
                    if (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0)
                    {
                        mpfr_printf("%.0Rf %s\n", n1, res);
                        total++;
                    }
                }
                else if (choice_save == 3)
                {
                    div_digits_PN(n1, res);
                    mpfr_set_str(range, res, 10, MPFR_RNDN);
                    if (mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0)
                    {
                        mpfr_printf("%.0Rf %s\n", n1, res);
                    }
                    div_PN_digits(n1, res);
                    mpfr_set_str(range, res, 10, MPFR_RNDN);
                    if (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0)
                    {
                        mpfr_printf("%.0Rf %s\n", n1, res);
                    }
                    if ((mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0) || (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0))
                    {
                        total++;
                    }
                }
                else
                {
                    mpfr_printf("%.0Rf\n", n1);
                    total++;
                }
        
        }

    global_list_line = total;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    mpz_clear(only_prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);
}

void print_prime_list(int choice_save)
{
    char *str;
    char *res;
    char *res_length;
    char *res_value;
    char *log10_2_str;
    char *log10_div_1_str;
    char *only;
    int length;
    int length_prev;
    int in_max_count;
    int res_array[50][1000];
    long total;
    long total2;
    long count;
    long line;
    mpz_t prime;
    mpz_t only_prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;
    mpfr_t var1;
    mpfr_t var2;

    str = (char *)malloc(1000 * sizeof(char));
    res = (char *)malloc(1000 * sizeof(char));
    res_length = (char *)malloc(1000 * sizeof(char));
    res_value = (char *)malloc(1000 * sizeof(char));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            res_array[i][j] = 0;
        }
    }
    log10_2_str = (char *)malloc(1000 * sizeof(char));
    log10_div_1_str = (char *)malloc(1000 * sizeof(char));
    only = (char *)malloc(1000 * sizeof(char));
    length = 0;
    length_prev = 0;
    in_max_count = 0;
    total = 0;
    total2 = 0;
    count = 0;
    mpz_init(prime);
    mpz_init(only_prime);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    if (global_list_line == 0)
    {
        printf("No prime numbers found\n");
        return;
    }

    if (choice_save == 1)
    {
        for (int i = 0; i < global_list_line; i++)
        {
            mpfr_get_z(only_prime, global_list[i], MPFR_RNDN);;
            mpfr_set_z(n1, only_prime, MPFR_RNDN);
            mpfr_sprintf(res, "%.0Rf", n1);
            mpz_set_str(prime, res, 10);
            length = strlen(res);
            if (isPrimeGMP(prime) != 0)
            {
                div_digits_PN(n1, res);
                strncpy(res_length, res, length + 2);
                res_length[length + 2] = '\0';
                log10_2(res_value);
                res_length = get_delete_string(res_length, 0, 1 + length - 1);
                mpfr_printf("%.0Rf %s(%s)\n", n1, res, res_length);
                for (int i = 0; i < 10; i++)
                {
                    if (atoi(res_length) == i)
                    {
                        res_array[length - 1][i]++;
                        total++;
                    }
                }
            }        
        } 
        // Print the statistics to one line for each length
        for (int i = 0; i < 50; i++)
        {
            log10_2_str = get_delete_string(res_value, 3 + i - 1, strlen(res_value) - 1);
            for (int j = 0; j < 10; j++)
            {
                if (res_array[i][j] != 0)
                {
                    printf("%s%d %d\n", log10_2_str, j, res_array[i][j]);
                }
            }
        }
    } 
    else if (choice_save == 2)
    {
        for (int i = 0; i < global_list_line; i++)
        {
            mpfr_sprintf(str, "%.0Rf", global_list[i]);
            mpz_set_str(prime, str, 10);
            mpfr_set_str(n1, str, 10, MPFR_RNDN);
            mpfr_set(var1, n1, MPFR_RNDN);
            length = strlen(str);
            
            if (isPrimeGMP(prime) != 0)
            {
                div_PN_digits(var1, res);
                res_length = get_delete_middle_string(res, 1, 1);
                if (length < 3)
                    res_length = get_delete_last_string(res_length, 2);
                else
                {
                    if (length > 7)
                    {
                        res_length = get_delete_last_string(res_length, length);
                        res_length = get_delete_first_string(res_length, length - 4);
                    }
                    else
                    {
                        res_length = get_delete_last_string(res_length, length);
                        res_length = get_delete_first_string(res_length, length - 3);
                    }
                }
                log10_div_1(res_value);
                if (length_prev != length)
                {
                    in_max_count++;
                }
                for (int i = in_max_count - 1; i < in_max_count; i++)
                {                       
                    str = get_delete_middle_string(global_value_arr[i], 1, 1);
                    if (length < 2)
                    {
                        str = get_delete_last_string(str, 2);
                        if (strncmp(res_length, str, 2) == 0)
                        {
                            mpfr_sprintf(only, "%.0Rf", var1);
                            mpfr_set_str(global_list[count], only, 10, MPFR_RNDN);
                            res_array[length - 1][atoi(res_length)]++;
                            count++;
                        }
                    }
                    else
                    {
                        if (length > 7)
                        {
                            str = get_delete_last_string(str, length);
                            str = get_delete_first_string(str, length - 4);
                            if (strncmp(res_length, str, 3) == 0)
                            {
                                mpfr_sprintf(only, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only, 10, MPFR_RNDN);
                                res_array[length - 1][atoi(res_length)]++;
                                count++;
                            }
                        }
                        else
                        {
                            str = get_delete_last_string(str, length);
                            str = get_delete_first_string(str, length - 3);
                            if (strncmp(res_length, str, 2) == 0)
                            { 
                                mpfr_sprintf(only, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only, 10, MPFR_RNDN);
                                res_array[length - 1][atoi(res_length)]++;
                                count++;
                            }
                        }
                    }
                }
                length_prev = length;
            }
        }
        // Print the statistics to one line for each length
        for (int i = 0; i < 50; i++)
        {
            log10_div_1_str = get_delete_string(res_value, i, strlen(res_value) - 1);
            for (int j = 0; j < 1000; j++)
            {
                if (res_array[i][j] != 0)
                {
                    printf("%d ", i + 1);
                    if (i < 2)
                    {
                        sprintf(log10_div_1_str, "%d", j);
                        printf("%c.", log10_div_1_str[0]);
                        for (int k = 1; k < strlen(log10_div_1_str); k++)
                        {
                            printf("%c", log10_div_1_str[k]);
                        }
                        printf(" %d\n", res_array[i][j]);
                    }
                    else if (i < 8)
                        printf("%s%d %d\n", log10_div_1_str, j, res_array[i][j]);
                    else
                    {
                        log10_div_1_str = get_delete_middle_string(log10_div_1_str, length - 2, length - 2);
                        printf("%s%d %d\n", log10_div_1_str, j, res_array[i][j]);
                    }
                    line++;
                }
            }
        } 
    }
    else if (choice_save == 3)
    {
        for (int i = 0; i < global_list_line; i++)
        {
            mpfr_get_z(only_prime, global_list[i], MPFR_RNDN);;
            mpfr_set_z(n1, only_prime, MPFR_RNDN);
            mpfr_sprintf(res, "%.0Rf", n1);
            mpz_set_str(prime, res, 10);
            length = strlen(res);
            if (isPrimeGMP(prime) != 0)
            {
                div_digits_PN(n1, res);
                strncpy(res_length, res, length + 2);
                res_length[length + 2] = '\0';
                log10_2(res_value);
                res_length = get_delete_string(res_length, 0, 1 + length - 1);
                for (int i = 0; i < 10; i++)
                {
                    if (atoi(res_length) == i)
                    {
                        res_array[length - 1][i]++;
                        total++;
                    }
                }
            }        
        }
        // Print the statistics to one line for each length
        for (int i = 0; i < 50; i++)
        {
            log10_2_str = get_delete_string(res_value, 3 + i - 1, strlen(res_value) - 1);
            for (int j = 0; j < 10; j++)
            {
                if (res_array[i][j] != 0)
                {
                    printf("%s%d %d\n", log10_2_str, j, res_array[i][j]);
                }
            }
        }
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                res_array[i][j] = 0;
            }
        }
        for (int i = 0; i < global_list_line; i++)
        {
            mpfr_get_z(only_prime, global_list[i], MPFR_RNDN);;
            mpfr_set_z(n1, only_prime, MPFR_RNDN);
            mpfr_sprintf(res, "%.0Rf", n1);
            mpz_set_str(prime, res, 10);
            length = strlen(res);
            if (isPrimeGMP(prime) != 0)
            {
                div_PN_digits(n1, res);
                res_length = get_delete_middle_string(res, 1, 1);
                res_length = get_delete_first_string(res_length, length - 3);
                res_length = get_delete_last_string(res_length, 2);
                log10_div_1(res_value);
                for (int i = 0; i < 1000; i++)
                {
                    if (atoi(res_length) == i)
                    {
                        res_array[length - 1][i]++;
                        total2++;
                    }
                }
            }
        }
        // Print the statistics to one line for each length
        for (int i = 0; i < 50; i++)
        {
            log10_div_1_str = get_delete_string(res_value, i, strlen(res_value) - 1);
            for (int j = 0; j < 1000; j++)
            {
                if (res_array[i][j] != 0)
                {
                    printf("%d ", i + 1);
                    if (i < 2)
                    {
                        sprintf(log10_div_1_str, "%d", j);
                        printf("%c.", log10_div_1_str[0]);
                        for (int k = 1; k < strlen(log10_div_1_str); k++)
                        {
                            printf("%c", log10_div_1_str[k]);
                        }
                        printf(" %d\n", res_array[i][j]);
                    }
                    else
                        printf("%s%d %d\n", log10_div_1_str, j, res_array[i][j]);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < global_list_line; i++)
        {
            mpfr_get_z(only_prime, global_list[i], MPFR_RNDN);;
            mpfr_set_z(n1, only_prime, MPFR_RNDN);
            mpfr_sprintf(res, "%.0Rf", n1);
            mpz_set_str(prime, res, 10);
            length = strlen(res);
            if (isPrimeGMP(prime) != 0)
            {
                mpfr_printf("%.0Rf\n", n1);
                total++;
            }
        }
    }

    if (total > total2 && total2 != 0 && total != 0)
    {
        total = total2;
    }
    else
    {
        total = total;
    }

    global_list_line = total;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    free(res_length);
    free(res_value);
    free(log10_2_str);
    free(log10_div_1_str);
    mpz_clear(only_prime);
    mpz_clear(prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);
}

int search_log10_2(char **value_arr, int in_max)
{
    char *str;
    char *res;
    char *res_length;
    char *res_value;
    char *digits_str;
    char *only_prime;
    int length;
    long count;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t range;
    mpfr_t range2;

    str = (char *)malloc(1000 * sizeof(char));
    res = (char *)malloc(1000 * sizeof(char));
    res_length = (char *)malloc(1000 * sizeof(char));
    res_value = (char *)malloc(1000 * sizeof(char));
    digits_str = (char *)malloc(1000 * sizeof(char));
    only_prime = (char *)malloc(1000 * sizeof(char));
    length = 0;
    count = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range2, 1024);
    mpfr_sprintf(str, "%.0Rf", global_first);
    mpz_set_str(n1, str, 10);
    mpfr_sprintf(str, "%.0Rf", global_last);
    mpz_set_str(n2, str, 10);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    if (global_list_line == 0)
    {
        printf("No prime numbers to save\n");
    }
    else
    {
        if (global_list_line > 1000)
        {
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
            for (int i = 1000; i < global_list_line; i++)
            {
                mpfr_init2(global_list[i], 1024);
            }
        }

        for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
        {
            mpfr_set_z(var1, n1, MPFR_RNDN);
            mpfr_set_z(var2, n2, MPFR_RNDN);
            mpfr_sprintf(str, "%.0Rf", var1);
            length = strlen(str);
            if (isPrimeGMP(n1) != 0)
            {
                switch (global_choice_save)
                {
                    case 2:
                        div_digits_PN(var1, res);
                        strncpy(res_length, res, length + 2);
                        res_length[length + 2] = '\0';
                        log10_2(res_value);
                        res_length = get_delete_string(res_length, 0, 1 + length - 1);
                        for (int i = 0; i < in_max; i++)
                        {
                            str = get_delete_string(value_arr[i], 0, length);
                            if (strncmp(res_length, str, 1) == 0)
                            {       
                                mpfr_printf("%.0Rf %s\n", var1, res);
                                mpfr_sprintf(only_prime, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                count++;
                            }
                            if (i == length - 1)
                            {
                                break;
                            }
                        }
                        break;
                    case 4:
                        div_digits_PN(var1, res);
                        strncpy(res_length, res, length + 2);
                        res_length[length + 2] = '\0';
                        log10_2(res_value);
                        res_length = get_delete_string(res_length, 0, 1 + length - 1);
                        for (int i = 0; i < in_max; i++)
                        {
                            str = get_delete_string(value_arr[i], 0, length);
                            if (strncmp(res_length, str, 1) == 0)
                            {       
                                mpfr_printf("%.0Rf %s\n", var1, res);
                                mpfr_sprintf(only_prime, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                count++;
                            }
                            if (i == length - 1)
                            {
                                break;
                            }
                        }
                        break;
                }
            }
        }
    }

    global_list_line = count;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    free(res);
    free(digits_str);
    free(only_prime);
    free(res_length);
    free(res_value);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(range);
    mpfr_clear(range2);
    
    return 0;
}

int search_log10_2_div_1(char **value_arr, int in_max)
{
    char *str;
    char *res;
    char *res_length;
    char *res_value;
    char *digits_str;
    char *only_prime;
    int length;
    int in_max_count;
    int length_prev;
    long count;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t range;
    mpfr_t range2;

    str = (char *)malloc(1000 * sizeof(char));
    res = (char *)malloc(1000 * sizeof(char));
    res_length = (char *)malloc(1000 * sizeof(char));
    res_value = (char *)malloc(1000 * sizeof(char));
    digits_str = (char *)malloc(1000 * sizeof(char));
    only_prime = (char *)malloc(1000 * sizeof(char));
    length = 0;
    in_max_count = 0;
    length_prev = 0;
    count = 0;
    
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range2, 1024);
    mpfr_sprintf(str, "%.0Rf", global_first);
    mpz_set_str(n1, str, 10);
    mpfr_sprintf(str, "%.0Rf", global_last);
    mpz_set_str(n2, str, 10);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    if (global_list_line == 0)
    {
        printf("No prime numbers to save\n");
    }
    else
    {
        if (global_list_line > 1000)
        {
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
            for (int i = 1000; i < global_list_line; i++)
            {
                mpfr_init2(global_list[i], 1024);
            }
        }

        // Copy string from value_arr to global_value_arr
        for (int i = 0; i < in_max; i++)
        {
            strcpy(global_value_arr[i], value_arr[i]);
        }

        for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
        {
            mpfr_sprintf(str, "%.0Zd", global_list[count]);
            mpfr_set_z(var1, n1, MPFR_RNDN);
            mpfr_set_z(var2, n2, MPFR_RNDN);
            mpfr_sprintf(str, "%.0Rf", var1);
            length = strlen(str);
            if (isPrimeGMP(n1) != 0)
            {
                switch (global_choice_save)
                {
                    case 3:
                        div_PN_digits(var1, res);
                        res_length = get_delete_middle_string(res, 1, 1);
                        if (length < 3)
                            res_length = get_delete_last_string(res_length, 2);
                        else
                        {
                            if (length > 7)
                            {
                                res_length = get_delete_last_string(res_length, length);
                                res_length = get_delete_first_string(res_length, length - 4);
                            }
                            else
                            {
                                res_length = get_delete_last_string(res_length, length);
                                res_length = get_delete_first_string(res_length, length - 3);
                            }
                        }
                        log10_div_1(res_value);
                        if (length_prev != length)
                        {
                            in_max_count++;
                        }
                        for (int i = in_max_count - 1; i < in_max_count; i++)
                        {
                            
                            str = get_delete_middle_string(value_arr[i], 1, 1);
                            if (length < 2)
                            {
                                str = get_delete_last_string(str, 2);
                                if (strncmp(res_length, str, 2) == 0)
                                {       
                                    mpfr_sprintf(only_prime, "%.0Rf", var1);
                                    mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                    count++;
                                }
                            }
                            else
                            {
                                if (length > 7)
                                {
                                    str = get_delete_last_string(str, length);
                                    str = get_delete_first_string(str, length - 4);
                                    if (strncmp(res_length, str, 3) == 0)
                                    {       
                                        mpfr_sprintf(only_prime, "%.0Rf", var1);
                                        mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                        count++;
                                    }
                                }
                                else
                                {
                                    str = get_delete_last_string(str, length);
                                    str = get_delete_first_string(str, length - 3);
                                    //printf("(str: %s %s)\n", str, res_length);
                                    if (strncmp(res_length, str, 2) == 0)
                                    {       
                                        mpfr_sprintf(only_prime, "%.0Rf", var1);
                                        mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                        count++;
                                    }
                                }
                            }
                        }
                        break;
                    case 4:
                        div_PN_digits(var1, res);
                        res_length = get_delete_middle_string(res, 1, 1);
                        if (length < 3)
                            res_length = get_delete_last_string(res_length, 2);
                        else
                        {
                            if (length > 7)
                            {
                                res_length = get_delete_last_string(res_length, length);
                                res_length = get_delete_first_string(res_length, length - 4);
                            }
                            else
                            {
                                res_length = get_delete_last_string(res_length, length);
                                res_length = get_delete_first_string(res_length, length - 3);
                            }
                        }
                        log10_div_1(res_value);
                        if (length_prev != length)
                        {
                            in_max_count++;
                        }
                        for (int i = in_max_count - 1; i < in_max_count; i++)
                        {
                            
                            str = get_delete_middle_string(value_arr[i], 1, 1);
                            if (length < 2)
                            {
                                str = get_delete_last_string(str, 2);
                                if (strncmp(res_length, str, 2) == 0)
                                {       
                                    mpfr_sprintf(only_prime, "%.0Rf", var1);
                                    mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                    count++;
                                }
                            }
                            else
                            {
                                if (length > 7)
                                {
                                    str = get_delete_last_string(str, length);
                                    str = get_delete_first_string(str, length - 4);
                                    if (strncmp(res_length, str, 3) == 0)
                                    {       
                                        mpfr_sprintf(only_prime, "%.0Rf", var1);
                                        mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                        count++;
                                    }
                                }
                                else
                                {
                                    str = get_delete_last_string(str, length);
                                    str = get_delete_first_string(str, length - 3);
                                    //printf("(str: %s %s)\n", str, res_length);
                                    if (strncmp(res_length, str, 2) == 0)
                                    {       
                                        mpfr_sprintf(only_prime, "%.0Rf", var1);
                                        mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                        count++;
                                    }
                                }
                            }
                        }
                        break;
                }
                length_prev = length;
            }
        }
    }

    global_list_line = count;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    free(res);
    free(digits_str);
    free(only_prime);
    free(res_length);
    free(res_value);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(range);
    mpfr_clear(range2);
    
    return 0;
}

int save_list(char *filename, int choice_save)
{
    char *res;
    char *res_temp1;
    char *res_temp2;
    long total;
    FILE *fp;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;
    mpfr_t range_temp1;
    mpfr_t range_temp2;

    res = (char *)malloc(1000 * sizeof(char));
    res_temp1 = (char *)malloc(1000 * sizeof(char));
    res_temp2 = (char *)malloc(1000 * sizeof(char));
    total = 0;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range_temp1, 1024);
    mpfr_init2(range_temp2, 1024);

    mpfr_set_str(n1, global_first_str, 10, MPFR_RNDN);
    mpfr_set_str(n2, global_last_str, 10, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); total < global_list_line; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_set(n1, global_list[total], MPFR_RNDN);
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        if (isPrimeGMP(prime) != 0)
        {
            if (choice_save == 1)
            {
                div_digits_PN(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf %s\n", n1, res);
                    total++;
                }
            }
            else if (choice_save == 2)
            {
                div_PN_digits(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf %s\n", n1, res);
                    total++;
                }
            }
            else
            {
                div_digits_PN(n1, res_temp1);
                div_PN_digits(n1, res_temp2);
                mpfr_set_str(range_temp1, res_temp1, 10, MPFR_RNDN);
                mpfr_set_str(range_temp2, res_temp2, 10, MPFR_RNDN);
                if (mpfr_cmp(range_temp1, global_range1) >= 0 && mpfr_cmp(range_temp1, global_range2) <= 0 && mpfr_cmp(range_temp2, global_range3) >= 0 && mpfr_cmp(range_temp2, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf %s %s\n", n1, res_temp1, res_temp2);
                    total++;
                }
            }
        }
    }

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    fclose(fp);
    mpz_clear(prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return 0;
}

int save_list_prime(char *filename, int choice_save)
{
    char *res;
    char *res_temp1;
    char *res_temp2;
    long total;
    FILE *fp;
    mpz_t prime;
    mpfr_t n1;
    mpfr_t n2;
    mpfr_t range;
    mpfr_t range_temp1;
    mpfr_t range_temp2;

    res = (char *)malloc(1000 * sizeof(char));
    res_temp1 = (char *)malloc(1000 * sizeof(char));
    res_temp2 = (char *)malloc(1000 * sizeof(char));
    total = 0;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpz_init2(prime, 1024);
    mpfr_init2(n1, 1024);
    mpfr_init2(n2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range_temp1, 1024);
    mpfr_init2(range_temp2, 1024);

    mpfr_set_str(n1, global_first_str, 10, MPFR_RNDN);
    mpfr_set_str(n2, global_last_str, 10, MPFR_RNDN);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (mpfr_set(n1, n1, MPFR_RNDN); total < global_list_line; mpfr_add_ui(n1, n1, 1, MPFR_RNDN))
    {
        mpfr_set(n1, global_list[total], MPFR_RNDN);
        mpfr_sprintf(res, "%.0Rf", n1);
        mpz_set_str(prime, res, 10);
        if (isPrimeGMP(prime) != 0)
        {
            if (choice_save == 1)
            {
                div_PN_digits(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range3) >= 0 && mpfr_cmp(range, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf\n", n1);
                    total++;
                }
            }
            else if (choice_save == 2)
            {
                div_digits_PN(n1, res);
                mpfr_set_str(range, res, 10, MPFR_RNDN);
                if (mpfr_cmp(range, global_range1) >= 0 && mpfr_cmp(range, global_range2) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf\n", n1);
                    total++;
                }
            }
            else
            {
                div_digits_PN(n1, res_temp1);
                div_PN_digits(n1, res_temp2);
                mpfr_set_str(range_temp1, res_temp1, 10, MPFR_RNDN);
                mpfr_set_str(range_temp2, res_temp2, 10, MPFR_RNDN);
                if (mpfr_cmp(range_temp1, global_range1) >= 0 && mpfr_cmp(range_temp1, global_range2) <= 0 && mpfr_cmp(range_temp2, global_range3) >= 0 && mpfr_cmp(range_temp2, global_range4) <= 0)
                {
                    mpfr_fprintf(fp, "%.0Rf\n", n1);
                    total++;
                }
            }
        }
    }

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(res);
    fclose(fp);
    mpz_clear(prime);
    mpfr_clear(n1);
    mpfr_clear(n2);
    mpfr_clear(range);

    return 0;
}

int load_list(char *filename)
{
    char *str;
    char *data1_str;
    char *data2_str;
    char *data3_str;
    char *token;
    char *token_temp;
    int count;
    int choice_load;
    int token_count;
    long line;
    FILE *fptr;
    mpfr_t data1;
    mpfr_t data2;
    mpfr_t data3;

    str = (char *)malloc(1000 * sizeof(char));
    data1_str = (char *)malloc(1000 * sizeof(char));
    data2_str = (char *)malloc(1000 * sizeof(char));
    data3_str = (char *)malloc(1000 * sizeof(char));
    token = (char *)malloc(1000 * sizeof(char));
    token_temp = (char *)malloc(1000 * sizeof(char));
    count = 0;
    line = 0;
    memset(str, 0, 1000);
    memset(data1_str, 0, 1000);
    memset(data2_str, 0, 1000);
    memset(data3_str, 0, 1000);
    memset(token, 0, 1000);
    memset(token_temp, 0, 1000);
    choice_load = 0;
    token_count = 0;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpfr_init2(data1, 1024);
    mpfr_init2(data2, 1024);
    mpfr_init2(data3, 1024);

    // start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // check the type of data
    while (fgets(data1_str, 1000, fptr) != NULL)
    {
        data2_str = strtok(data1_str, " ");
        while (data2_str != NULL)
        {
            token_count++;
            switch (token_count)
            {
                case 1:
                    for (int i = 0; i < strlen(data2_str); i++)
                    {
                        if (isdigit(data2_str[i]) == 0)
                        {
                            choice_load = 0;
                            break;
                        }
                        else
                        {
                            choice_load = 1;
                            break;
                        }
                    }
                    break;
                case 2:
                    if (data2_str[0] == '0' && data2_str[1] == '.') 
                    {
                        for (int i = 2; i < strlen(data2_str); i++)
                        {
                            if (isdigit(data2_str[i]) == 0)
                            {
                                choice_load = 0;
                                break;
                            }
                            else
                            {
                                choice_load = 2;
                                break;
                            }
                        }
                    }
                    else if ((data2_str[0] == '2' || data2_str[0] == '3') && data2_str[1] == '.')
                    {
                        for (int i = 2; i < strlen(data2_str); i++)
                        {
                            if (isdigit(data2_str[i]) == 0)
                            {
                                choice_load = 0;
                                break;
                            }
                            else
                            {
                                choice_load = 3;
                                break;
                            }
                        }
                    }
                    break;
                case 3:
                    if ((data2_str[0] == '2' || data2_str[0] == '3') && data2_str[1] == '.')
                    {
                        for (int i = 2; i < strlen(data2_str); i++)
                        {
                            if (isdigit(data2_str[i]) == 0)
                            {
                                choice_load = 0;
                                break;
                            }
                            else
                            {
                                choice_load = 4;
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;;
            }
            data2_str = strtok(NULL, " ");
        }
    }

    global_choice_save = choice_load;

    if (choice_load == 0)
    {
        printf("Invalid data type\n");
        return 0;
    }

    // count the number of lines in the file
    rewind(fptr);
    while (fgets(str, 1000, fptr) != NULL)
    {
        line++;
    }

    if (line > 1000)
    {
        global_list = (mpfr_t *)realloc(global_list, line * sizeof(mpfr_t));

        for (int i = 1000; i < line; i++)
        {
            mpfr_init2(global_list[i], 1024);
        }
    }

    rewind(fptr);
    count = 0;
    while (fgets(str, 1000, fptr) != NULL)
    {
        sprintf(data1_str, "%s", str);
        mpfr_set_str(data1, data1_str, 10, MPFR_RNDN);
        mpfr_set(global_list[count], data1, MPFR_RNDN);
        mpfr_printf("%.0Rf\n", global_list[count]);
        count++;
    }

    global_list_line = line;

    // stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    free(data1_str);
    free(data2_str);
    free(data3_str);
    fclose(fptr);
    mpfr_clear(data1);
    mpfr_clear(data2);
    mpfr_clear(data3);

    return 0;
}

int search_log10_2_again(char **value_arr, int in_max)
{
    char *str;
    char *res;
    char *res_length;
    char *res_value;
    char *digits_str;
    char *only_prime;
    int length;
    long count;
    long total;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t range;
    mpfr_t range2;

    str = (char *)malloc(1000 * sizeof(char));
    res = (char *)malloc(1000 * sizeof(char));
    res_length = (char *)malloc(1000 * sizeof(char));
    res_value = (char *)malloc(1000 * sizeof(char));
    digits_str = (char *)malloc(1000 * sizeof(char));
    only_prime = (char *)malloc(1000 * sizeof(char));
    length = 0;
    count = 0;
    total = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range2, 1024);
    mpfr_sprintf(str, "%.0Rf", global_first);
    mpz_set_str(n1, str, 10);
    mpfr_sprintf(str, "%.0Rf", global_last);
    mpz_set_str(n2, str, 10);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    printf("global_list_line: %ld\n", global_list_line);
    printf("global_choice_save: %d\n", global_choice_save);

    // Find the prime numbers between n1 and n2
    if (global_list_line == 0)
    {
        printf("No prime numbers to save\n");
    }
    else
    {
        if (global_list_line > 1000)
        {
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
        }

        for (mpz_set(n1, n1); total < global_list_line; mpz_add_ui(n1, n1, 1))
        {
            mpfr_sprintf(only_prime, "%.0Rf", global_list[total]);
            mpz_set_str(n1, only_prime, 10);
            mpfr_set_z(var1, n1, MPFR_RNDN);
            mpfr_set_z(var2, n2, MPFR_RNDN);
            mpfr_sprintf(str, "%.0Rf", var1);
            length = strlen(str);
            if (isPrimeGMP(n1) != 0)
            {
                switch (global_choice_save)
                {
                    case 1:
                    case 2:
                        div_digits_PN(var1, res);
                        strncpy(res_length, res, length + 2);
                        res_length[length + 2] = '\0';
                        log10_2(res_value);
                        res_length = get_delete_string(res_length, 0, 1 + length - 1);
                        for (int i = 0; i < in_max; i++)
                        {
                            str = get_delete_string(value_arr[i], 0, length);
                            if (strncmp(res_length, str, 1) == 0)
                            {       
                                mpfr_printf("%.0Rf %s\n", var1, res);
                                mpfr_sprintf(only_prime, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                count++;
                            }
                            if (i == length - 1)
                            {
                                break;
                            }
                        }
                        break;
                    case 4:
                        div_digits_PN(var1, res);
                        strncpy(res_length, res, length + 2);
                        res_length[length + 2] = '\0';
                        log10_2(res_value);
                        res_length = get_delete_string(res_length, 0, 1 + length - 1);
                        for (int i = 0; i < in_max; i++)
                        {
                            str = get_delete_string(value_arr[i], 0, length);
                            if (strncmp(res_length, str, 1) == 0)
                            {       
                                mpfr_printf("%.0Rf %s\n", var1, res);
                                mpfr_sprintf(only_prime, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                count++;
                            }
                            if (i == length - 1)
                            {
                                break;
                            }
                        }
                        break;
                }
            }
            total++;
        }
    }

    global_list_line = count;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    free(res);
    free(digits_str);
    free(only_prime);
    free(res_length);
    free(res_value);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(range);
    mpfr_clear(range2);
    
    return 0;
}

int search_log10_2_div_1_again(char **value_arr, int in_max)
{
    char *str;
    char *res;
    char *res_length;
    char *res_value;
    char *digits_str;
    char *only_prime;
    int length;
    long count;
    long total;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t range;
    mpfr_t range2;

    str = (char *)malloc(1000 * sizeof(char));
    res = (char *)malloc(1000 * sizeof(char));
    res_length = (char *)malloc(1000 * sizeof(char));
    res_value = (char *)malloc(1000 * sizeof(char));
    digits_str = (char *)malloc(1000 * sizeof(char));
    only_prime = (char *)malloc(1000 * sizeof(char));
    length = 0;
    count = 0;
    total = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(range, 1024);
    mpfr_init2(range2, 1024);
    mpfr_sprintf(str, "%.0Rf", global_first);
    mpz_set_str(n1, str, 10);
    mpfr_sprintf(str, "%.0Rf", global_last);
    mpz_set_str(n2, str, 10);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    if (global_list_line == 0)
    {
        printf("No prime numbers to save\n");
    }
    else
    {
        if (global_list_line > 1000)
        {
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
        }

        for (mpz_set(n1, n1); total < global_list_line; mpz_add_ui(n1, n1, 1))
        {
            mpfr_sprintf(only_prime, "%.0Rf", global_list[total]);
            mpz_set_str(n1, only_prime, 10);
            mpfr_set_z(var1, n1, MPFR_RNDN);
            mpfr_set_z(var2, n2, MPFR_RNDN);
            mpfr_sprintf(str, "%.0Rf", var1);
            length = strlen(str);
            if (isPrimeGMP(n1) != 0)
            {
                switch (global_choice_save)
                {
                    case 1:
                    case 3:
                        div_PN_digits(var1, res);
                        res_length = get_delete_middle_string(res, 1, 1);
                        //res_length = get_delete_first_string(res_length, length - 3);
                        if (length < 3)
                            res_length = get_delete_last_string(res_length, 2);
                        else
                        {
                            res_length = get_delete_last_string(res_length, length);
                            res_length = get_delete_first_string(res_length, length - 3);
                        }
                        //printf("res_length: %s\n", res_length);
                        log10_div_1(res_value);
                        for (int i = length - 1; i < in_max; i++)
                        {
                            str = get_delete_middle_string(value_arr[i], 1, 1);
                            if (length > 2)
                            {
                                str = get_delete_last_string(str, length + 1);
                                str = get_delete_first_string(value_arr[i], length - 2);
                            }
                            //printf("(str: %s %s)\n", str, res_length);
                            if (strncmp(res_length, str, 2) == 0)
                            {       
                                mpfr_printf("%.0Rf %s\n", var1, res);
                                mpfr_sprintf(only_prime, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                count++;
                            }
                            if (i == length - 1)
                            {
                                break;
                            }
                        }
                        break;
                    case 4:
                        div_PN_digits(var1, res);
                        res_length = get_delete_middle_string(res, 1, 1);
                        //res_length = get_delete_first_string(res_length, length - 3);
                        if (length < 3)
                            res_length = get_delete_last_string(res_length, 2);
                        else
                        {
                            res_length = get_delete_last_string(res_length, length);
                            res_length = get_delete_first_string(res_length, length - 3);
                        }
                        //printf("res_length: %s\n", res_length);
                        log10_div_1(res_value);
                        for (int i = length - 1; i < in_max; i++)
                        {
                            str = get_delete_middle_string(value_arr[i], 1, 1);
                            if (length > 2)
                            {
                                str = get_delete_last_string(str, length + 1);
                                str = get_delete_first_string(value_arr[i], length - 2);
                            }
                            //printf("(str: %s %s)\n", str, res_length);
                            if (strncmp(res_length, str, 2) == 0)
                            {       
                                mpfr_printf("%.0Rf %s\n", var1, res);
                                mpfr_sprintf(only_prime, "%.0Rf", var1);
                                mpfr_set_str(global_list[count], only_prime, 10, MPFR_RNDN);
                                count++;
                            }
                            if (i == length - 1)
                            {
                                break;
                            }
                        }
                        break;
                }
            }
            total++;
        }
    }

    global_list_line = count;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    free(res);
    free(digits_str);
    free(only_prime);
    free(res_length);
    free(res_value);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(range);
    mpfr_clear(range2);
    
    return 0;
}