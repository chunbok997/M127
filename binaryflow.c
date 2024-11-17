// Author: Chunbok Kim and Copilot
// Date: 2024-11-08
// Version: 0.1
// Purpose: Binary flow program

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define CATEGORY_INPUT_BASE_NUMBER 2
#define CATEGORY_PRINT_NO 0
#define CATEGORY_PRINT_YES 2
#define CATEGORY_PRINT_RANGE_NUMBER 3
#define CATEGORY_PRINT_RANGE_NUMBER_TOTAL 4
#define CATEGORY_PRINT_DATA 5
#define CATEGORY_PRINT_DATA_TOTAL 6
#define CATEGORY_SAVE_NO 0
#define CATEGORY_SAVE_YES 3
#define CATEGORY_SAVE_RANGE_NUMBER 7
#define CATEGORY_SAVE_RANGE_NUMBER_ONLY_PRIME 8
#define CATEGORY_SAVE_DATA 9
#define CATEGORY_SAVE_DATA_ONLY_PRIME 10
#define CATEGORY_LOAD_NO 0
#define CATEGORY_LOAD_YES 4
#define CATEGORY_LOAD_RANGE_NUMBER 11
#define CATEGORY_LOAD_RANGE_NUMBER_ONLY_PRIME 12
#define CATEGORY_LOAD_DATA 13
#define CATEGORY_LOAD_DATA_ONLY_PRIME 14
#define CATEGORY_SEARCH_NO 0
#define CATEGORY_SEARCH_YES 5
#define CATEGORY_SEARCH_HORIZONTAL 15
#define CATEGORY_SEARCH_VERTICAL 16
#define CATEGORY_SEARCH_HORIZONTAL_AGAIN 17
#define CATEGORY_SEARCH_VERTICAL_AGAIN 18
#define CATEGORY_LIST_NO 0
#define CATEGORY_LIST_YES 1

// Define function prototypes
// View menu
void view_menu();

// Get input from user
char *get_input(char *prompt);
// Get input from user as string
char *get_input_string(char *prompt);

// Find prime numbers
bool isPrime(int n);
// Find prime numbers using GMP
int isPrimeGMP(mpz_t n);

// Calculate the maximum exponent
int exp_max(mpfr_t n, mpfr_t base_n);
// Print the loop through the number and find the maximum exponent
int exp_sequence(mpfr_t n, mpfr_t base_n);
// Return the result of the exponential sequence
int exp_sequence_to_result(mpfr_t n, mpfr_t base_n, mpfr_t *result);
// Save the result of the exponential sequence to a file
int exp_sequence_to_file(mpfr_t n, mpfr_t base_n, FILE *fp);
// Count result of the exponential sequence
int exp_sequence_total(mpfr_t n, mpfr_t base_n);
// Print the loop through the number and find the maximum exponent
int exp_sequence_base_n(mpfr_t n, mpfr_t base_n);
// Return the result of the exponential sequence
int exp_sequence_base_n_to_result(mpfr_t n, mpfr_t base_n, mpfr_t *result);
// Save the result of the exponential sequence to a file
int exp_sequence_base_n_to_file(mpfr_t n, mpfr_t base_n, FILE *fp);
// Count result of the exponential sequence
int exp_sequence_base_n_total(mpfr_t n, mpfr_t base_n);

// Old functions
int decimal_to_binary(mpfr_t n, char *binary, int size);
// Old functions
int base_to_decimal(mpfr_t n, char *binary, int size);
// Old functions
int base_to_decimal_file(mpfr_t n, char *binary, int size, FILE *fp);
// Old functions
int bast_to_decimal_no_print(mpfr_t n, char *binary, int size);
// Old functions
int change_exp_length(mpfr_t n, int size);

// Print exponential sequence
long print_base(char *range1, char *range2, int size);
// Print none timer exponential sequence
long print_base_line(char *range1, char *range2, int size);
// Print exponential sequence of total
long print_base_line_total(char *range1, char *range2, int size);
// Save exponential sequence to a file
long print_base_line_save(char *range1, char *range2, int size, char *filename);
long print_list(int base);
long print_list_total(int base);

// Save the first number, last number
int save(char *filename, char *range1, char *range2, int size);
// Save only prime numbers
int save_prime(char *filename, char *range1, char *range2);
// Load the first number, last number and only prime numbers
long load(char *filename);
//int load_prime(char *filename);
// Load the first number, last number and only prime numbers in the list
int load_list(char *filename);
//int load_list_prime(char *filename);

int save_prime_list(char *filename);
int save_prime_list_sequence(char *filename);

// Search number of all columns
int search_horizontal(int value);
// Search number of all columns again
int search_horizontal_again(int value);
// Search columns for each row
int search_vertical(int *value, int in_max);
// Search columns for each row again
int search_vertical_again(int *value, int in_max);

char *global_str1;
char *global_str2;
int global_base;
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
mpfr_t *global_list;

// main function
// argc: number of arguments
// argv: array of arguments
int main(int argc, char *argv[])
{
    char *filename;
    int choice;
    int value;
    int value_index;
    int *value_array;

    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpz_t count;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;
    mpfr_t *result;

    global_str1 = (char *)malloc(1000 * sizeof(char));
    global_str2 = (char *)malloc(1000 * sizeof(char));
    memset(global_str1, 0, 1000);
    memset(global_str2, 0, 1000);
    global_base = 2;
    category_menu = CATEGORY_MENU_NO;
    category_status = CATEGORY_STATUS_NO;
    category_type = 0;
    category_content = 0;
    category_list = CATEGORY_LIST_NO;
    category_last_type = 0;
    category_last_content = 0;
    category_last_list = 0;
    for (int i = 0; i < 16; i++)
    {
        category[i] = 0;
    }
    global_list_line = 0;
    mpfr_init2(global_first, 1024);
    mpfr_init2(global_last, 1024);
    global_list = (mpfr_t *)malloc(1000 * sizeof(mpfr_t));
    for (int i = 0; i < 1000; i++)
    {
        mpfr_init2(global_list[i], 1024);
    }
    mpfr_set_ui(global_first, 0, MPFR_RNDN);
    mpfr_set_ui(global_last, 0, MPFR_RNDN);
    
    filename = (char *)malloc(256 * sizeof(char));
    if (filename == NULL)
    {
        printf("Error: Unable to allocate memory\n");
        return 1;
    }
    memset(filename, 0, 256);
    choice = 0;
    value = 0;
    value_index = 0;
    value_array = (int *)malloc(1000 * sizeof(int));
    memset(value_array, 0, 1000);
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpz_init(count);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    result = (mpfr_t *)malloc(1000 * sizeof(mpfr_t));
    for (int i = 0; i < 1000; i++)
    {
        mpfr_init2(result[i], 1024);
    }
    // Set n1 and n2 to 0
    mpz_set_str(n1, "0", 10);
    mpz_set_str(n2, "0", 10);
    mpz_set_str(count, "0", 10);
    mpfr_set_ui(base_n, global_base, MPFR_RNDN);

    char *input;
    int *numbers;
    char *token;

    input = (char *)malloc(1000 * sizeof(char));
    numbers = (int *)malloc(1000 * sizeof(int));
    token = (char *)malloc(1000 * sizeof(char));
    do
    { 
        view_menu();
        choice= atoi(get_input("Enter your choice: "));
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
                printf("Enter the first number, last number: ");
                scanf("%s %s", global_str1, global_str2);
                mpfr_set_str(global_first, global_str1, 10, MPFR_RNDN);
                mpfr_set_str(global_last, global_str2, 10, MPFR_RNDN);
                // choice is 0.
                getchar();
                break;
            case 2:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_INPUT_YES;
                category_content = CATEGORY_INPUT_BASE_NUMBER;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[2] = category_type;
                category[3] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                if (global_base < 2)
                {
                    global_base = 2;
                }
                printf("Enter base number to convert: ");
                scanf("%d", &global_base);
                getchar();
                printf("Base number to convert: %d\n", global_base);
                break;
            case 3:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_RANGE_NUMBER;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Converting base %d to decimal\n", global_base);
                print_base(global_str1, global_str2, global_base);
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                // getchar();
                global_list_line_backup = global_list_line;
                break;
            case 4:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_RANGE_NUMBER_TOTAL;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Converting base %d to decimal\n", global_base);
                print_base_line_total(global_str1, global_str2, global_base);
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_list_line_backup = global_list_line;
                break;
            case 5:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_HORIZONTAL;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Enter search value: ");
                scanf("%d", &value);
                getchar();
                printf("Searching horizontal prime numbers\n");
                search_horizontal(value);
                printf("Horizontal prime numbers searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 6:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_VERTICAL;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                value_index = 0;
                input = get_input("Enter search value: ");
                value_index = 0;
                token = strtok(input, " ");
                while (token != NULL)
                {
                    numbers[value_index] = atoi(token);
                    value_index++;
                    token = strtok(NULL, " ");
                }
                for (int i = 0; i < value_index; i++)
                {
                    value_array[i] = numbers[i];
                }
                printf("Searching vertical prime numbers\n");
                search_vertical(value_array, value_index);
                printf("Vertical prime numbers searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 7:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_RANGE_NUMBER;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Input the filename to save the output: ");
                scanf("%s", filename);
                getchar();
                printf("Converting base %d to decimal\n", global_base);
                save(filename, global_str1, global_str2, global_base);
                printf("Output saved to %s\n", filename);
                break;
            case 8:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_RANGE_NUMBER_ONLY_PRIME;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Input the filename to save the prime numbers: ");
                scanf("%s", filename);
                getchar();
                printf("Converting base %d to decimal\n", global_base);
                save_prime(filename, global_str1, global_str2);
                printf("Prime numbers saved to %s\n", filename);
                break;
            case 9:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_LOAD_YES;
                category_content = CATEGORY_LOAD_RANGE_NUMBER;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[9] = category_type;
                category[10] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Input the filename to load the output: ");
                scanf("%s", filename);
                getchar();
                printf("Loading the output from %s\n", filename);
                load(filename);
                printf("Output loaded from %s\n", filename);
                global_list_line_backup = global_list_line;
                break;
            case 10:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_DATA;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Printing number of all columns\n");
                print_list(global_base);
                printf("Prime numbers printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_list_line_backup = global_list_line;
                break;
            case 11:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_PRINT_YES;
                category_content = CATEGORY_PRINT_DATA_TOTAL;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[4] = category_type;
                category[5] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Printing number of all columns statistics\n");
                print_list_total(global_base);
                printf("Prime numbers printed\n");
                // Wait for the user to press enter
                printf("Press enter to continue\n");
                while (getchar() != '\n' && getchar() != EOF);
                //getchar();
                global_list_line_backup = global_list_line;
                break;
            case 12:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_HORIZONTAL_AGAIN;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Enter search value: ");
                scanf("%d", &value);
                getchar();
                printf("Searching horizontal prime numbers\n");
                search_horizontal_again(value);
                printf("Horizontal prime numbers searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 13:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SEARCH_YES;
                category_content = CATEGORY_SEARCH_VERTICAL_AGAIN;
                category_list = CATEGORY_LIST_YES;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;

                // erase the buffer
                //while (getchar() != '\n' && getchar() != EOF);
                value_index = 0;
                input = get_input_string("Enter search value: ");
                value_index = 0;
                token = strtok(input, " ");
                while (token != NULL)
                {
                    numbers[value_index] = atoi(token);
                    value_index++;
                    token = strtok(NULL, " ");
                }
                for (int i = 0; i < value_index; i++)
                {
                    value_array[i] = numbers[i];
                }
                printf("Searching vertical prime numbers\n");
                search_vertical_again(value_array, value_index);
                printf("Vertical prime numbers searched\n");
                global_list_line_backup = global_list_line;
                break;
            case 14:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_DATA;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Input the filename to save the prime numbers: ");
                scanf("%s", filename);
                getchar();
                printf("Saving only the prime numbers to %s\n", filename);
                save_prime_list_sequence(filename);
                printf("Prime numbers saved to %s\n", filename);
                global_list_line_backup = global_list_line;
                break;
            case 15:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_SAVE_YES;
                category_content = CATEGORY_SAVE_DATA_ONLY_PRIME;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[7] = category_type;
                category[8] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Input the filename to save the prime numbers: ");
                scanf("%s", filename);
                getchar();
                printf("Saving only the prime numbers to %s\n", filename);
                save_prime_list(filename);
                printf("Prime numbers saved to %s\n", filename);
                global_list_line_backup = global_list_line;
                break;
            case 16:
                category_status = CATEGORY_STATUS_YES;
                category_type = CATEGORY_LOAD_YES;
                category_content = CATEGORY_LOAD_DATA;
                category_list = CATEGORY_LIST_NO;
                category[1] = category_status;
                category[9] = category_type;
                category[10] = category_content;
                category[6] = category_list;
                category_last_type = category_type;
                category_last_content = category_content;
                category_last_list = category_list;
                printf("Input the filename to load the output: ");
                scanf("%s", filename);
                getchar();
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

        /*for (int i = 0; i < 16; i++)
        {
            printf("%d ", category[i]);
        }
        printf("\n");

        printf("category_last_type: %d category_last_content: %d category_last_list: %d\n", category_last_type, category_last_content, category_last_list);
        */
       
        if (category[2] == CATEGORY_INPUT_YES)
        {
            global_list_line = 0;
        }

        if (category[4] == CATEGORY_PRINT_YES || category[7] == CATEGORY_SEARCH_YES)
        {
            category[2] = CATEGORY_INPUT_NO;

            global_list_line = global_list_line_backup;
        }
        
        category_status = CATEGORY_STATUS_NO;
    } while (choice != 0);
    category_menu = CATEGORY_MENU_NO;

    free(global_str1);
    free(global_str2);
    mpfr_clear(global_first);
    mpfr_clear(global_last);
    for (int i = 0; i < 1000; i++)
    {
        mpfr_clear(global_list[i]);
    }
    free(global_list);
    free(filename);
    free(value_array);
    mpz_clear(n1);
    mpz_clear(n2);
    mpz_clear(count);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    for (int i = 0; i < 1000; i++)
    {
        mpfr_clear(result[i]);
    }
    free(result);
    free(input);
    free(numbers);
    free(token);

    return 0;
}

// View menu
void view_menu()
{
    // Welcome message
    printf("************************************************\n");
    printf("*     Welcome to the Mersenne Prime Number     *\n");
    printf("************************************************\n");
    printf("*                                              *\n");
    printf("*           BINARY-FLOW Version 0.1            *\n");
    printf("*                                              *\n"); 
    printf("***********************************************************************************************\n");
    printf("*  1. Input the first number, last number      *         Save to list and recalculate         *\n");
    printf("*  2. Input base number                        *   ( Search results are saved in the list )   *\n");
    printf("***********************************************************************************************\n");
    printf("*  3. Print the first number, last number      * 10. Print numbers in the list                *\n");
    printf("*  4. Print statistics of numbers              * 11. Print statistics of numbers in the list  *\n");
    printf("*  5. Search number of all columns             * 12. Search number of all columns in the list *\n");
    printf("*  6. Search columns for each row              * 13. Search columns for each row in the list  *\n");
    printf("*   ( Search results are saved in the list )   ************************************************\n");
    printf("************************************************ 14. Save numbers in the list                 *\n");
    printf("*  7. Save the first number, last number       * 15. Save only prime numbers in the list      *\n");
    printf("*  8. Save only prime numbers                  * 16. Load list data from the file             *\n");
    printf("*  9. Load range data from the file            ************************************************\n");
    printf("************************************************\n");
    printf("* 0. Exit                                      *\n");
    printf("************************************************\n");

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

// Calculate the maximum exponent
int exp_max(mpfr_t n, mpfr_t base_n)
{
    int index;
    mpz_t num;
    mpz_t base;
    mpz_t max;
    
    index = 0;
    mpz_init(num);
    mpz_init(base);
    mpz_init(max);
    mpz_set_ui(num, 0);
    mpz_set_ui(base, 0);
    mpz_set_ui(max, 0);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);

    while (mpfr_cmp_ui(n, 0) > 0)
    {
        mpz_pow_ui(max, base, index);
        if (mpz_cmp(max, num) > 0)
        {
            break;
        }
        index = index + 1;
        continue;
    }

    mpz_clear(num);
    mpz_clear(base);
    mpz_clear(max);

    return index;
}

// Print the loop through the number and find the maximum exponent
int exp_sequence(mpfr_t n, mpfr_t base_n)
{
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    exp_count = 0;
    count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);

    gmp_printf("%Zd ", num);
    count++;
    do
    {  
        exp_count = exp_max(n_temp, base_n);
        printf("%d ", exp_count - 1);
        count++;
        mpz_pow_ui(max, base, exp_count - 1);
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    printf("\n");

    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);
    mpfr_clear(n_temp);

    return count;
}

// Return the result of the exponential sequence
int exp_sequence_to_result(mpfr_t n, mpfr_t base_n, mpfr_t *result)
{
    int index;
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    index = 1;
    exp_count = 0;
    count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);
    mpfr_set(result[0], n, MPFR_RNDN);

    count++;
    do
    {  
        exp_count = exp_max(n_temp, base_n);
        mpfr_set_ui(result[index++], exp_count - 1, MPFR_RNDN);
        count++;
        mpz_pow_ui(max, base, exp_count - 1);
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    mpfr_set_si(result[index], -1, MPFR_RNDN);

    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);

    return count;
}

// Save the result of the exponential sequence to a file
int exp_sequence_to_file(mpfr_t n, mpfr_t base_n, FILE *fp)
{
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    exp_count = 0;
    count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);

    gmp_fprintf(fp, "%Zd ", num);
    count++;
    do
    {  
        exp_count = exp_max(n_temp, base_n);
        mpfr_fprintf(fp, "%d ", exp_count - 1);
        count++;
        mpz_pow_ui(max, base, exp_count - 1);
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    fprintf(fp, "\n");
    count++;

    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);

    return count;
}

// Count result of the exponential sequence
int exp_sequence_total(mpfr_t n, mpfr_t base_n)
{
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    count = 0;
    exp_count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);

    gmp_printf("%Zd ", num);
    do
    {  
        exp_count = exp_max(n_temp, base_n);
        printf("%d ", exp_count - 1);
        count++;
        mpz_pow_ui(max, base, exp_count - 1);
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    printf("(%d)\n", count);
 
    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);
    mpfr_clear(n_temp);

    return count;
}

// Print the loop through the number and find the maximum exponent
int exp_sequence_base_n(mpfr_t n, mpfr_t base_n)
{
    int index;
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    index = 0;
    exp_count = 0;
    count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);

    gmp_printf("%Zd ", num);
    count++;
    exp_count = exp_max(n_temp, base_n);
    exp_count = exp_count - 1;
    printf("%d ", exp_count);
    count++;
    do
    {
        mpz_pow_ui(max, base, exp_count);
        exp_count = exp_count - 1;
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            index = exp_max(n_temp, base_n);
            index = index - 1;
            printf("%d ", index);
            count++;
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    printf("\n");

    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);

    return count;
}

// Return the result of the exponential sequence
int exp_sequence_base_n_to_result(mpfr_t n, mpfr_t base_n, mpfr_t *result)
{
    int index;
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    index = 2;
    exp_count = 0;
    count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);

    mpfr_set(result[count], n, MPFR_RNDN);
    count++;
    exp_count = exp_max(n_temp, base_n);
    exp_count = exp_count - 1;
    mpfr_set_ui(result[count], exp_count, MPFR_RNDN);
    count++;
    do
    {
        mpz_pow_ui(max, base, exp_count);
        exp_count = exp_count - 1;
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            index = exp_max(n_temp, base_n);
            index = index - 1;
            mpfr_set_ui(result[count], index, MPFR_RNDN);
            count++;
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    mpfr_set_si(result[count], -1, MPFR_RNDN);
    count++;

    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);

    return count;
}

// Save the result of the exponential sequence to a file
int exp_sequence_base_n_to_file(mpfr_t n, mpfr_t base_n, FILE *fp)
{
    int index;
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    index = 0;
    exp_count = 0;
    count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);

    mpfr_fprintf(fp, "%Zd ", num);
    count++;
    exp_count = exp_max(n_temp, base_n);
    exp_count = exp_count - 1;
    mpfr_fprintf(fp, "%d ", exp_count);
    count++;
    do
    {
        mpz_pow_ui(max, base, exp_count);
        exp_count = exp_count - 1;
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            index = exp_max(n_temp, base_n);
            index = index - 1;
            mpfr_fprintf(fp, "%d ", index);
            count++;            
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    fprintf(fp, "\n");
    count++;

    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);

    return count;
}

// Count result of the exponential sequence
int exp_sequence_base_n_total(mpfr_t n, mpfr_t base_n)
{
    int index;
    int exp_count;
    int count;
    mpz_t num;
    mpz_t max;
    mpz_t base;
    mpfr_t n_temp;

    index = 0;
    exp_count = 0;
    count = 0;
    mpz_init(num);
    mpz_init(max);
    mpz_init(base);
    mpfr_init2(n_temp, 1024);
    mpfr_get_z(num, n, MPFR_RNDN);
    mpfr_get_z(base, base_n, MPFR_RNDN);
    mpfr_set(n_temp, n, MPFR_RNDN);

    gmp_printf("%Zd ", num);
    exp_count = exp_max(n_temp, base_n);
    exp_count = exp_count - 1;
    printf("%d ", exp_count);
    count++;
    do
    {
        mpz_pow_ui(max, base, exp_count);
        exp_count = exp_count - 1;
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n_temp, num, MPFR_RNDN);
            index = exp_max(n_temp, base_n);
            index = index - 1;
            printf("%d ", index);
            count++;
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    printf("(%d)\n", count);
 
    mpz_clear(num);
    mpz_clear(max);
    mpz_clear(base);

    return count;
}

// Old function
int decimal_to_binary(mpfr_t n, char *binary, int size)
{
    int index;
    mpz_t num;
    mpz_init(num);

    mpfr_get_z(num, n, MPFR_RNDN);

    // Convert the number to binary
    index = 0;

    while (mpz_cmp_ui(num, 0) > 0)
    {
        binary[index] = mpz_get_ui(num) % size + '0';
    
        mpz_fdiv_q_ui(num, num, size);
        index = index + 1;
    }
    binary[index] = '\0';

    // Reverse the binary number
    /*for (int i = 0; i < index / 2; i++)
    {
        char temp = binary[i];
        binary[i] = binary[index - i - 1];
        binary[index - i - 1] = temp;
    }*/

    mpz_clear(num);

    return index;
}

// Old function
int base_to_decimal(mpfr_t n, char *binary, int size)
{
    char *bin;
    int index;
    int total;
    int exp_count;
    mpz_t num;
    mpz_t exp;
    mpz_t max;

    bin = (char *)malloc(1000 * sizeof(char));
    memset(bin, 0, 1000);
    index = 0;
    total = 0;
    exp_count = decimal_to_binary(n, bin, size);
    mpz_init(num);
    mpz_init(exp);
    mpz_init(max);
    mpz_set_ui(num, 0);
    mpz_set_ui(exp, size);
    mpz_set_ui(max, 0);

    exp_count = exp_count - 1;
    printf("%d ", exp_count);
    mpfr_get_z(num, n, MPFR_RNDN);
    do
    {    
        mpz_pow_ui(max, exp, exp_count);
        exp_count = exp_count - 1;
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n, num, MPFR_RNDN);
            index = change_exp_length(n, size);
            printf("%d ", index);
            total = total + 1;
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    printf("(%d)\n", total + 1);
    printf("\n");

    free(bin);
    mpz_clear(num);
    mpz_clear(exp);
    mpz_clear(max);

    return total;
}

// Old function
int base_to_decimal_file(mpfr_t n, char *binary, int size, FILE *fp)
{
    char *bin;
    int index;
    int total;
    int exp_count;
    mpz_t num;
    mpz_t exp;
    mpz_t max;

    bin = (char *)malloc(1000 * sizeof(char));
    memset(bin, 0, 1000);
    index = 0;
    total = 0;
    exp_count = decimal_to_binary(n, bin, size);
    mpz_init(num);
    mpz_init(exp);
    mpz_init(max);
    mpz_set_ui(num, 0);
    mpz_set_ui(exp, size);
    mpz_set_ui(max, 0);

    exp_count = exp_count - 1;
    printf("%d ", exp_count);
    fprintf(fp, "%d ", exp_count);
    mpfr_get_z(num, n, MPFR_RNDN);
    do
    {    
        mpz_pow_ui(max, exp, exp_count);
        exp_count = exp_count - 1;
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n, num, MPFR_RNDN);
            index = change_exp_length(n, size);
            printf("%d ", index);
            fprintf(fp, "%d ", index);
            total = total + 1;
            continue;
        }
    } while (mpz_cmp(num, max) < 0);
    //printf("(%d)\n", total + 1);
    printf("\n");
    fprintf(fp, "\n");

    free(bin);
    mpz_clear(num);
    mpz_clear(exp);
    mpz_clear(max);

    return total;
}

// Old function
int base_to_decimal_no_print(mpfr_t n, char *binary, int size)
{
    char *bin;
    int total;
    int exp_count;
    mpz_t num;
    mpz_t exp;
    mpz_t max;

    bin = (char *)malloc(1000 * sizeof(char));
    memset(bin, 0, 1000);
    total = 0;
    exp_count = decimal_to_binary(n, bin, size);
    mpz_init(num);
    mpz_init(exp);
    mpz_init(max);
    mpz_set_ui(num, 0);
    mpz_set_ui(exp, size);
    mpz_set_ui(max, 0);

    exp_count = exp_count - 1;
    do
    {    
        mpz_pow_ui(max, exp, exp_count);
        exp_count = exp_count - 1;
        while (mpz_cmp(max, num) < 0)
        {
            mpz_sub(num, num, max);
            mpfr_set_z(n, num, MPFR_RNDN);
            total = total + 1;
            continue;
        }
    } while (mpz_cmp(num, max) < 0);

    free(bin);
    mpz_clear(num);
    mpz_clear(exp);
    mpz_clear(max);

    return total;
}

// Old function
int change_exp_length(mpfr_t n, int size)
{
    int index;
    mpz_t num;

    mpz_init(num);
    mpfr_get_z(num, n, MPFR_RNDN);

    // Convert the number to length
    index = 0;
    while (mpz_cmp_ui(num, 0) > 0)
    {
        mpz_fdiv_q_ui(num, num, size);
        index = index + 1;
    }
    index--;

    mpz_clear(num);

    return index;
}

// Print exponential sequence
long print_base(char *range1, char *range2, int size)
{
    char *binary;
    long line;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;

    binary = (char *)malloc(1000 * sizeof(char));
    line = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    mpz_set_str(n1, range1, 10);
    mpz_set_str(n2, range2, 10);
    mpfr_set_ui(base_n, size, MPFR_RNDN);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        if (isPrimeGMP(n1) != 0)
        {
            switch (size)
            {
                case 2:
                    exp_sequence(var1, base_n);
                    break;
                case 3:
                    exp_sequence_base_n(var1, base_n);
                    break;
                default:
                    exp_sequence_base_n(var1, base_n);
                    break;
            }
            line++;
        }
    }
    global_list_line = line;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(binary);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    
    return line;
}

// Print none timer exponential sequence
long print_base_line(char *range1, char *range2, int size)
{
    char *binary;
    long line;
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base;

    binary = (char *)malloc(1000 * sizeof(char));
    line = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base, 1024);
    mpz_set_str(n1, range1, 10);
    mpz_set_str(n2, range2, 10);
    mpfr_set_ui(base, size, MPFR_RNDN);

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        if (isPrimeGMP(n1) != 0)
        {
            switch (size)
            {
                case 2:
                    exp_sequence(var1, base);
                    break;
                case 3:
                    exp_sequence_base_n(var1, base);
                    break;
                default:
                     exp_sequence_base_n(var1, base);
                    break;
            }
            line++;
        }
    }

    free(binary);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base);
    
    return line;
}

// Print exponential sequence of the total
long print_base_line_total(char *range1, char *range2, int size)
{
    int cnt;
    int cnt_array[100];
    long line;
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base;
    
    cnt = 0;
    for (int i = 0; i < 100; i++)
    {
        cnt_array[i] = 0;
    }
    line = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpz_set_str(n1, range1, 10);
    mpz_set_str(n2, range2, 10);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base, 1024);
    mpfr_set_ui(base, size, MPFR_RNDN);

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        if (isPrimeGMP(n1) != 0)
        {
            switch (size)
            {
                case 2:
                    cnt = exp_sequence_total(var1, base);
                    cnt_array[cnt]++;
                    break;
                case 3:
                    cnt = exp_sequence_base_n_total(var1, base);
                    cnt_array[cnt]++;
                    break;
                default:
                    cnt = exp_sequence_base_n_total(var1, base);
                    cnt_array[cnt]++;
                    break;
            }
            line++;
        }
    }
    global_list_line = line;
    for (int i = 0; i < 100; i++)
    {
        if (cnt_array[i] > 0)
        {
            printf("(%d): %d\n", i, cnt_array[i]);
        }
    }

    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base);
    
    return line;
}

// Save exponential sequence to a file
long print_base_line_save(char *range1, char *range2, int size, char *filename)
{
    char *binary;
    int length;
    long line;
    FILE *fptr;
    mpz_t n1;
    mpz_t n2;
    mpz_t count;
    mpfr_t var1;
    mpfr_t var2;

    binary = (char *)malloc(1000 * sizeof(char));
    line = 0;   
    fptr = fopen(filename, "a");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpz_init(count);
    mpz_set_str(n1, range1, 10);
    mpz_set_str(n2, range2, 10);
    mpz_set_str(count, "0", 10);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        if (isPrimeGMP(n1) != 0)
        {
            gmp_printf("%Zd ", n1);
            mpfr_fprintf(fptr, "%.0Rf ", var1);
            switch (size)
            {
                case 2:
                    length = decimal_to_binary(var1, binary, size);
                    break;
                case 3:
                    length = base_to_decimal_file(var1, binary, 3, fptr);
                    break;
                default:
                    length = base_to_decimal_file(var1, binary, size, fptr);
                    break;
            }
            while (length > 0)
            { 
                length--;

                if (size == 2)
                {
                    if (binary[length] == '1')
                    {
                        gmp_printf("%d ", length);
                        mpfr_fprintf(fptr, "%d ", length);
                        mpz_add_ui(count, count, 1);
                    }
                }
            }
            if (size == 2)
            {
                gmp_printf("\n", count);
                mpfr_fprintf(fptr, "\n", count);
            }
            line++;
        }
        mpz_set_ui(count, 0);
    }

    free(binary);
    fclose(fptr);
    mpz_clear(n1);
    mpz_clear(n2);
    mpz_clear(count);
    mpfr_clear(var1);
    mpfr_clear(var2);
    
    return line;
}

// Save exponential sequence to a file
int save(char *filename, char *range1, char *range2, int size)
{
    char *binary;
    FILE *fp;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpz_t count;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t *result;
    mpfr_t g_size;

    binary = (char *)malloc(1000 * sizeof(char));
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpz_init(count);
    mpz_set_str(n1, range1, 10);
    mpz_set_str(n2, range2, 10);
    mpz_set_str(count, "0", 10);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    result = (mpfr_t *)malloc(1000 * sizeof(mpfr_t));
    for (int i = 0; i < 1000; i++)
    {
        mpfr_init2(result[i], 1024);
    }
    mpfr_init2(g_size, 1024);
    mpfr_set_ui(g_size, size, MPFR_RNDN);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        if (isPrimeGMP(n1) != 0)
        {
            exp_sequence_base_n_to_file(var1, g_size, fp);
        }
        mpz_set_ui(count, 0);
    }

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(binary);
    fclose(fp);
    mpz_clear(n1);
    mpz_clear(n2);
    mpz_clear(count);
    mpfr_clear(var1);
    mpfr_clear(var2);
    
    return 0;
}

// Save only the prime numbers to a file
int save_prime(char *filename, char *range1, char *range2)
{
    char *str1;
    char *str2;
    FILE *fp;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;

    str1 = (char *)malloc(1000 * sizeof(char));
    str2 = (char *)malloc(1000 * sizeof(char));
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }   
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpz_set_str(n1, range1, 10);
    mpz_set_str(n2, range2, 10);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        if (isPrimeGMP(n1) != 0)
        {
            gmp_fprintf(fp, "%Zd\n", n1);
        }
    }

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str1);
    free(str2);
    fclose(fp);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    
    return 0;
}

// Load the first and last number and only the prime numbers
long load(char *filename)
{
    int check;
    long count;
    FILE *fptr;
    mpz_t only_prime;

    check = 0;
    count = 0;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpz_init(only_prime);

    fseek(fptr, 0, SEEK_SET);
    while (gmp_fscanf(fptr, "%Zd", only_prime) != EOF)
    {
        if (check == 0)
        {
            mpz_get_str(global_str1, 10, only_prime);
            check = 1;
            count++;
        }
        else
        {
            mpz_get_str(global_str2, 10, only_prime);
            count++;
        }
        while(fgetc(fptr) != '\n');
    }

    global_list_line = count;

    fclose(fptr);
    mpz_clear(only_prime);

    return count;
}

// Load first and last number and all the prime numbers to a list
int load_list(char *filename)
{
    int count;
    FILE *fptr;
    mpz_t only_prime;

    count = 0;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpz_init(only_prime);

    count = 0;
    while (gmp_fscanf(fptr, "%Zd", only_prime) != EOF)
    {
        count++;
        while(fgetc(fptr) != '\n');
    }
    // The count is from 1
    global_list_line = count;   

    if (count > 1000)
    {
        global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
        if (global_list == NULL)
        {
            printf("realloc failed\n");
            exit(1);
        }
        for (int i = 1000; i < global_list_line; i++)
        {
            mpfr_init2(global_list[i], 1024);
        }
    }

    count = 0;
    fseek(fptr, 0, SEEK_SET);
    while (gmp_fscanf(fptr, "%Zd", only_prime) != EOF)
    {
        mpfr_set_z(global_list[count], only_prime, MPFR_RNDN);
        while(fgetc(fptr) != '\n');
        count++;
    }

    fclose(fptr);
    mpz_clear(only_prime);

    return 0;
}

long print_list(int base)
{
    char *str;
    long total;
    long count;
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;

    if (global_list_line == 0)
    {
        printf("No prime numbers to print\n");
        return 0;
    }

    str = (char *)malloc(1000 * sizeof(char));
    total = 0;
    count = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    mpfr_set_ui(base_n, base, MPFR_RNDN);

    // Find the prime numbers between n1 and n2
    while (total < global_list_line)
    {
        mpfr_sprintf(str, "%.0Rf", global_list[total]);
        mpfr_set_str(var1, str, 10, MPFR_RNDN);
        mpz_set_str(n1, str, 10);
        if (isPrimeGMP(n1) != 0)
        {
            switch (base)
            {
                case 2:
                    exp_sequence(var1, base_n);
                    break;
                case 3:
                    exp_sequence_base_n(var1, base_n);
                    break;
                default:
                    exp_sequence_base_n(var1, base_n);
                    break;
            }
            mpfr_sprintf(str, "%.0Rf", global_list[count]);
            mpz_set_str(n1, str, 10);
            count++;
        }
        total++;
    }
    global_list_line = total;

    free(str);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    
    return total;
}

long print_list_total(int base)
{
    char *str;
    long cnt;
    long cnt_array[1000];
    long total;
    long count;
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;

    if (global_list_line == 0)
    {
        printf("No prime numbers to print\n");
        return 0;
    }

    str = (char *)malloc(1000 * sizeof(char));
    for (int i = 0; i < 1000; i++)
    {
        cnt_array[i] = 0;
    }
    total = 0;
    count = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    mpfr_set_ui(base_n, base, MPFR_RNDN);

    // Find the prime numbers between n1 and n2
    while (total < global_list_line)
    {
        mpfr_sprintf(str, "%.0Rf", global_list[total]);
        mpfr_set_str(var1, str, 10, MPFR_RNDN);
        mpz_set_str(n1, str, 10);
        if (isPrimeGMP(n1) != 0)
        {
            switch (base)
            {
                case 2:
                    cnt = exp_sequence(var1, base_n);
                    cnt_array[cnt - 1]++;
                    break;
                case 3:
                    cnt = exp_sequence_base_n(var1, base_n);
                    cnt_array[cnt - 1]++;
                    break;
                default:
                    cnt = exp_sequence_base_n(var1, base_n);
                    cnt_array[cnt - 1]++;
                    break;
            }
            mpfr_sprintf(str, "%.0Rf", global_list[count]);
            mpz_set_str(n1, str, 10);
            count++;
        }
        total++;
    }
    global_list_line = total;

    for (int i = 0; i < 1000; i++)
    {
        if (cnt_array[i] > 0)
        {
            printf("(%d): %ld\n", i, cnt_array[i]);
        }
    }

    free(str);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    
    return total;
}

int save_prime_list_sequence(char *filename)
{
    char *binary;
    int index;
    long count;
    FILE *fptr;
    mpfr_t base_n;
    mpfr_t *result;

    binary = (char *)malloc(1000 * sizeof(char));
    index = 0;
    count = 0;
    fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    mpfr_init2(base_n, 1024);
    mpfr_set_ui(base_n, global_base, MPFR_RNDN);
    result = (mpfr_t *)malloc(1000 * sizeof(mpfr_t));
    for (int i = 0; i < 1000; i++)
    {
        mpfr_init2(result[i], 1024);
    }

    if (global_list_line == 0)
    {
        printf("No prime numbers to save\n");
    }
    else
    {
        for (int i = 0; i < global_list_line; i++)
        {
            index = 0;
            switch (global_base)
            {
                case 2:
                    exp_sequence_base_n_to_result(global_list[i], base_n, result);
                    while (mpfr_cmp_si(result[index], -1) != 0)
                    {
                        mpfr_fprintf(fptr, "%.0Rf ", result[index]);
                        index++;
                    }
                    break;
                case 3:
                    exp_sequence_base_n_to_result(global_list[i], base_n, result);
                    while (mpfr_cmp_si(result[index], -1) != 0)
                    {
                        mpfr_fprintf(fptr, "%.0Rf ", result[index]);
                        index++;
                    }
                    break;
                default:
                    exp_sequence_base_n_to_result(global_list[i], base_n, result);
                    while (mpfr_cmp_si(result[index], -1) != 0)
                    {
                        mpfr_fprintf(fptr, "%.0Rf ", result[index]);
                        index++;
                    }
                    break;
            }
            fprintf(fptr, "\n");
            count++;
        }
    }

    global_list_line = count;

    fclose(fptr);
    free(binary);
    mpfr_clear(base_n);
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_clear(result[i]);
    }
    free(result);
    return 0;
}

int save_prime_list(char *filename)
{
    long count;
    FILE *fptr;

    count = 0;
    fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    if (global_list_line == 0)
    {
        printf("No prime numbers to save\n");
    }
    else
    {
        printf("Saving %ld prime numbers\n", global_list_line);
        for (int i = 0; i < global_list_line - 1; i++)
        {
            mpfr_fprintf(fptr, "%.0Rf\n", global_list[i]);
            count++;
        }
    }

    fclose(fptr);

    return 0;
}

// Search number of all columns
int search_horizontal(int value)
{
    char *str;
    int size;
    long count;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;
    mpfr_t *result;
   
    if (global_list_line == 0)
    {
        printf("No prime numbers to search\n");
        return 0;
    }

    global_list_line = 1000;
    str = (char *)malloc(1000 * sizeof(char));
    size = global_base;
    count = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    mpfr_set_ui(base_n, global_base, MPFR_RNDN);
    result = (mpfr_t *)malloc(global_list_line * sizeof(mpfr_t));
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_init2(result[i], 1024);
    }

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    mpz_set_str(n1, global_str1, 10);
    mpz_set_str(n2, global_str2, 10);
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_sprintf(str, "%Zd", n1);
        mpfr_set_str(var1, str, 10, MPFR_RNDN);
        if (count > global_list_line - 1)
        {
            global_list_line = global_list_line + 1000;
            result = (mpfr_t *)realloc(result, global_list_line * sizeof(mpfr_t));
            if (result == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(result[i], 1024);
            }
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
            if (global_list == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(global_list[i], 1024);
            }
        }

        if (isPrimeGMP(n1) != 0)
        {
            int i = 0;
            switch (size)
            {
                case 2:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < 1000; i++)
                    {
                        if (mpfr_cmp_si(result[i], -1) == 0)
                        {
                            break;
                        }
                    }
                    if (i == value + 1)
                    {
                        for (int j = 0; j < 1000; j++)
                        {
                            if (mpfr_cmp_si(result[j], -1) == 0)
                            {
                                break;
                            }
                            //mpfr_printf("%.0Rf ", result[j]);
                            if (j == 0)
                            {
                                mpfr_set(global_list[count], result[j], MPFR_RNDN);
                            }
                            
                        }
                        //printf("\n");
                        count = count + 1;
                    }
                    break;
                default:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < 1000; i++)
                    {
                        if (mpfr_cmp_si(result[i], -1) == 0)
                        {
                            break;
                        }
                    }
                    if (i == value + 1)
                    {
                        for (int j = 0; j < 1000; j++)
                        {
                            if (mpfr_cmp_si(result[j], -1) == 0)
                            {
                                break;
                            }
                            //mpfr_printf("%.0Rf ", result[j]);
                            if (j == 0)
                            {
                                mpfr_set(global_list[count], result[j], MPFR_RNDN);
                            }
                        }
                        //printf("\n");
                        count = count + 1;
                    }
                    break;
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
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_clear(result[i]);
    }

    return 0;
}

// Search number of all columns again
int search_horizontal_again(int value)
{
    char *binary;
    int size;
    long count;
    long total;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;
    mpfr_t *result;

    if (global_list_line == 0)
    {
        printf("No prime numbers to search\n");
        return 0;
    }

    //global_list_line = 1000;
    binary = (char *)malloc(1000 * sizeof(char));
    size = global_base;
    count = 0;
    total = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    mpfr_set_ui(base_n, global_base, MPFR_RNDN);
    result = (mpfr_t *)malloc(global_list_line * sizeof(mpfr_t));
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_init2(result[i], 1024);
    }

    mpfr_sprintf(global_str1, "%.0Rf", global_list[0]);
    mpfr_sprintf(global_str2, "%.0Rf", global_list[global_list_line - 1]);
    mpz_set_str(n1, global_str1, 10);
    mpz_set_str(n2, global_str2, 10);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); total < global_list_line; mpz_add_ui(n1, n1, 1))
    {
        mpfr_sprintf(global_str1, "%.0Rf", global_list[total]);
        mpz_set_str(n1, global_str1, 10);
        mpfr_sprintf(global_str2, "%.0Rf", global_list[global_list_line - 1]);
        mpz_set_str(n2, global_str2, 10);
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        
        if (count > global_list_line)
        {
            global_list_line = global_list_line + 1000;
            result = (mpfr_t *)realloc(result, global_list_line * sizeof(mpfr_t));
            if (result == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(result[i], 1024);
            }
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
            if (global_list == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(global_list[i], 1024);
            }
        }

        if (isPrimeGMP(n1) != 0)
        {
            int i = 0;
            switch (size)
            {
                case 2:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < 1000; i++)
                    {
                        if (mpfr_cmp_si(result[i], -1) == 0)
                        {
                            break;
                        }
                    }
                    if (i == value + 1)
                    {
                        for (int j = 0; j < 1000; j++)
                        {
                            if (mpfr_cmp_si(result[j], -1) == 0)
                            {
                                break;
                            }
                            //mpfr_printf("%.0Rf ", result[j]);
                            if (j == 0)
                            {
                                mpfr_set(global_list[count], result[j], MPFR_RNDN);
                            }
                            
                        }
                        //printf("\n");
                        count = count + 1;
                    }
                    break;
                default:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < 1000; i++)
                    {
                        if (mpfr_cmp_si(result[i], -1) == 0)
                        {
                            break;
                        }
                    }
                    if (i == value + 1)
                    {
                        for (int j = 0; j < 1000; j++)
                        {
                            if (mpfr_cmp_si(result[j], -1) == 0)
                            {
                                break;
                            }
                            //mpfr_printf("%.0Rf ", result[j]);
                            if (j == 0)
                            {
                                mpfr_set(global_list[count], result[j], MPFR_RNDN);
                            }
                        }
                        //printf("\n");
                        count = count + 1;
                    }
                    break;
            }
            total++;
        }
    }

    mpfr_set_ui(global_list[global_list_line], 0, MPFR_RNDN);

    global_list_line = count;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(binary);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_clear(result[i]);
    }
    
    return 0;
}

// Search columns for each row
int search_vertical(int *value, int in_max)
{
    char *str;
    int size;
    long count;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;
    mpfr_t *result;

    if (global_list_line == 0)
    {
        printf("No prime numbers to search\n");
        return 0;
    }

    global_list_line = 1000;
    str = (char *)malloc(1000 * sizeof(char));
    size = global_base;
    count = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    mpfr_set_ui(base_n, global_base, MPFR_RNDN);
    result = (mpfr_t *)malloc(global_list_line * sizeof(mpfr_t));
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_init2(result[i], 1024);
    }

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    mpz_set_str(n1, global_str1, 10);
    mpz_set_str(n2, global_str2, 10);
    for (mpz_set(n1, n1); mpz_cmp(n1, n2) <= 0; mpz_add_ui(n1, n1, 1))
    {
        mpfr_sprintf(str, "%Zd", n1);
        mpfr_set_str(var1, str, 10, MPFR_RNDN);
        int check_prime = 0;
        if (count > global_list_line - 1)
        {
            global_list_line = global_list_line + 1000;
            result = (mpfr_t *)realloc(result, global_list_line * sizeof(mpfr_t));
            if (result == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(result[i], 1024);
            }
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
            if (global_list == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(global_list[i], 1024);
            }
        }

        if (isPrimeGMP(n1) != 0)
        {
            int i = 0;
            switch (size)
            {
                case 2:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < in_max; i++)
                    {
                        if (mpfr_cmp_si(result[i + 1], value[check_prime]) == 0)
                        {
                            check_prime++;
                        }
                        
                        if (check_prime == in_max)
                        {
                            for (int j = 0; j < 1000; j++)
                            {
                                if (mpfr_cmp_si(result[j], -1) == 0)
                                {
                                    break;
                                }
                                //mpfr_printf("%.0Rf ", result[j]);
                                if (j == 0)
                                {
                                    mpfr_set(global_list[count], result[j], MPFR_RNDN);
                                }
                            }
                            //printf("\n");
                            count = count + 1;
                        }
                    }
                    break;
                default:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < in_max; i++)
                    {
                        if (mpfr_cmp_si(result[i + 1], value[check_prime]) == 0)
                        {
                            check_prime++;
                        }
                        if (check_prime == in_max)
                        {
                            for (int j = 0; j < 1000; j++)
                            {
                                if (mpfr_cmp_si(result[j], -1) == 0)
                                {
                                    break;
                                }
                                //mpfr_printf("%.0Rf ", result[j]);
                                if (j == 0)
                                {
                                    mpfr_set(global_list[count], result[j], MPFR_RNDN);
                                }
                            }
                            //printf("\n");
                            count = count + 1;
                        }
                    }
                    break;
            }
        }        
        check_prime = 0;
    }

    global_list_line = count;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(str);
    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_clear(result[i]);
    }
    
    return 0;
}

// Search columns for each row again
int search_vertical_again(int *value, int in_max)
{
    char *binary;
    int size;
    long count;
    long total;
    // from n1 to n2
    mpz_t n1;
    mpz_t n2;
    mpfr_t var1;
    mpfr_t var2;
    mpfr_t base_n;
    mpfr_t *result;

    if (global_list_line == 0)
    {
        printf("No prime numbers to search\n");
        return 0;
    }

    binary = (char *)malloc(1000 * sizeof(char));
    memset(binary, 0, 1000);
    size = global_base;
    count = 0;
    total = 0;
    // Initialize n1 and n2
    mpz_init(n1);
    mpz_init(n2);    
    mpfr_init2(var1, 1024);
    mpfr_init2(var2, 1024);
    mpfr_init2(base_n, 1024);
    mpfr_set_ui(base_n, global_base, MPFR_RNDN);
    result = (mpfr_t *)malloc(global_list_line * sizeof(mpfr_t));
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_init2(result[i], 1024);
    }

    mpfr_sprintf(global_str1, "%.0Rf", global_list[0]);
    mpz_set_str(n1, global_str1, 10);
    mpfr_sprintf(global_str2, "%.0Rf", global_list[global_list_line - 1]);
    mpz_set_str(n2, global_str2, 10);

    // Start the timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Find the prime numbers between n1 and n2
    for (mpz_set(n1, n1); total < global_list_line; mpz_add_ui(n1, n1, 1))
    {
        mpfr_sprintf(global_str1, "%.0Rf", global_list[total]);
        mpz_set_str(n1, global_str1, 10);
        mpfr_sprintf(global_str2, "%.0Rf", global_list[global_list_line - 1]);
        mpz_set_str(n2, global_str2, 10);
        mpfr_set_z(var1, n1, MPFR_RNDN);
        mpfr_set_z(var2, n2, MPFR_RNDN);
        int check_prime = 0;

        if (count > global_list_line)
        {
            global_list_line = global_list_line + 1000;
            result = (mpfr_t *)realloc(result, global_list_line * sizeof(mpfr_t));
            if (result == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(result[i], 1024);
            }
            global_list = (mpfr_t *)realloc(global_list, global_list_line * sizeof(mpfr_t));
            if (global_list == NULL)
            {
                printf("realloc failed\n");
                exit(1);
            }
            for (int i = count; i < global_list_line; i++)
            {
                mpfr_init2(global_list[i], 1024);
            }
        }

        if (isPrimeGMP(n1) != 0)
        {
            int i = 0;
            switch (size)
            {
                case 2:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < in_max; i++)
                    {
                        if (mpfr_cmp_si(result[i + 1], value[i]) == 0)
                        {
                            check_prime++;
                        }
                        if (check_prime == in_max)
                        {
                            for (int j = 0; j < 1000; j++)
                            {
                                if (mpfr_cmp_si(result[j], -1) == 0)
                                {
                                    break;
                                }
                                //mpfr_printf("%.0Rf ", result[j]);
                                if (j == 0)
                                {
                                    mpfr_set(global_list[count], result[j], MPFR_RNDN);
                                }
                            }
                            //printf("\n");
                            count = count + 1;
                        }
                    }
                    break;
                default:
                    exp_sequence_base_n_to_result(var1, base_n, result);
                    for (i = 0; i < in_max; i++)
                    {
                        if (mpfr_cmp_si(result[i + 1], value[i]) == 0)
                        {
                            check_prime++;
                        }
                        if (check_prime == in_max)
                        {
                            for (int j = 0; j < 1000; j++)
                            {
                                if (mpfr_cmp_si(result[j], -1) == 0)
                                {
                                    break;
                                }
                                //mpfr_printf("%.0Rf ", result[j]);
                                if (j == 0)
                                {
                                    mpfr_set(global_list[count], result[j], MPFR_RNDN);
                                }
                            }
                            //printf("\n");
                            count = count + 1;
                        }
                    }
                    break;
            }
            total++;
        }
        
        check_prime = 0;
    }

    global_list_line = count;

    // Stop the timer
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the time taken to find the prime numbers
    printf("Time taken: %f seconds\n", cpu_time_used);

    mpz_clear(n1);
    mpz_clear(n2);
    mpfr_clear(var1);
    mpfr_clear(var2);
    mpfr_clear(base_n);
    for (int i = 0; i < global_list_line; i++)
    {
        mpfr_clear(result[i]);
    }

    return 0;
}