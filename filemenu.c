// Author: Chunbok Kim and Copilot
// Date: 2024-11-05
// Version: 0.1
// Purpose: File menu program

// Include header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gmp.h>
#include <mpfr.h>

// Define constants
#define LIST_OF_MERSENNE_PRIME_NUMBERS 52

// Define functions
// View menu
void view_menu();
// Get input from user
char *get_input(char *prompt);
// Load the list from the file
long load_file(char *filename);
// Save the list to the file
int save_file(char *filename);
// Print the list
void print_list(void);
// Insert a new data in the list
void insert_data(long line);
// Edit a data in the list
void edit_data(long line);
// Delete a data in the list
void delete_data(long line);
// Search a data in the list
int search_data(char *data);
// Create mersenne-prime-numbers.txt
int create_mersenne_prime_numbers(char *filename);
// Create mersenne-prime-numbers-digits.txt
int create_digits(char *filename); 
// Create mersenne-prime-numbers-mpn-digits.txt
int create_mpn_digits(char *filename);
// Create mersenne-prime-numbers-digits-mpn.txt
int create_digits_mpn(char *filename);
// Create mersenne-prime-numbers-log10-2.txt
int create_log10_2(char *filename);
// Create merseene-prime-numbers-1-log10-2.txt
int create_1_log10_2(char *filename);

// Define global variables
long global_line;
mpfr_t *global_list;
mpfr_t *global_store;

// Main function
int main(int argc, char *argv[])
{
    char *filename;
    int choice;
    long i;
    long line;
    
    filename = (char *)malloc(1000 * sizeof(char));
    choice = 0;
    i = 0;
    line = 0;
    
    global_list = (mpfr_t *)malloc(1000 * sizeof(mpfr_t));
    for (i = 0; i < 1000; i++)
    {
        mpfr_init2(global_list[i], 1024);
    }

    global_store = (mpfr_t *)malloc(LIST_OF_MERSENNE_PRIME_NUMBERS * sizeof(mpfr_t));
    for (i = 0; i < LIST_OF_MERSENNE_PRIME_NUMBERS; i++)
    {
        mpfr_init2(global_store[i], 1024);
    }

    mpfr_set_str(global_store[0], "2", 10, MPFR_RNDN);
    mpfr_set_str(global_store[1], "3", 10, MPFR_RNDN);
    mpfr_set_str(global_store[2], "5", 10, MPFR_RNDN);
    mpfr_set_str(global_store[3], "7", 10, MPFR_RNDN);
    mpfr_set_str(global_store[4], "13", 10, MPFR_RNDN);
    mpfr_set_str(global_store[5], "17", 10, MPFR_RNDN);
    mpfr_set_str(global_store[6], "19", 10, MPFR_RNDN);
    mpfr_set_str(global_store[7], "31", 10, MPFR_RNDN);
    mpfr_set_str(global_store[8], "61", 10, MPFR_RNDN);
    mpfr_set_str(global_store[9], "89", 10, MPFR_RNDN);
    mpfr_set_str(global_store[10], "107", 10, MPFR_RNDN);
    mpfr_set_str(global_store[11], "127", 10, MPFR_RNDN);
    mpfr_set_str(global_store[12], "521", 10, MPFR_RNDN);
    mpfr_set_str(global_store[13], "607", 10, MPFR_RNDN);
    mpfr_set_str(global_store[14], "1279", 10, MPFR_RNDN);
    mpfr_set_str(global_store[15], "2203", 10, MPFR_RNDN);
    mpfr_set_str(global_store[16], "2281", 10, MPFR_RNDN);
    mpfr_set_str(global_store[17], "3217", 10, MPFR_RNDN);
    mpfr_set_str(global_store[18], "4253", 10, MPFR_RNDN);
    mpfr_set_str(global_store[19], "4423", 10, MPFR_RNDN);
    mpfr_set_str(global_store[20], "9689", 10, MPFR_RNDN);
    mpfr_set_str(global_store[21], "9941", 10, MPFR_RNDN);
    mpfr_set_str(global_store[22], "11213", 10, MPFR_RNDN);
    mpfr_set_str(global_store[23], "19937", 10, MPFR_RNDN);
    mpfr_set_str(global_store[24], "21701", 10, MPFR_RNDN);
    mpfr_set_str(global_store[25], "23209", 10, MPFR_RNDN);
    mpfr_set_str(global_store[26], "44497", 10, MPFR_RNDN);
    mpfr_set_str(global_store[27], "86243", 10, MPFR_RNDN);
    mpfr_set_str(global_store[28], "110503", 10, MPFR_RNDN);
    mpfr_set_str(global_store[29], "132049", 10, MPFR_RNDN);
    mpfr_set_str(global_store[30], "216091", 10, MPFR_RNDN);
    mpfr_set_str(global_store[31], "756839", 10, MPFR_RNDN);
    mpfr_set_str(global_store[32], "859433", 10, MPFR_RNDN);
    mpfr_set_str(global_store[33], "1257787", 10, MPFR_RNDN);
    mpfr_set_str(global_store[34], "1398269", 10, MPFR_RNDN);
    mpfr_set_str(global_store[35], "2976221", 10, MPFR_RNDN);
    mpfr_set_str(global_store[36], "3021377", 10, MPFR_RNDN);
    mpfr_set_str(global_store[37], "6972593", 10, MPFR_RNDN);
    mpfr_set_str(global_store[38], "13466917", 10, MPFR_RNDN);
    mpfr_set_str(global_store[39], "20996011", 10, MPFR_RNDN);
    mpfr_set_str(global_store[40], "24036583", 10, MPFR_RNDN);
    mpfr_set_str(global_store[41], "25964951", 10, MPFR_RNDN);
    mpfr_set_str(global_store[42], "30402457", 10, MPFR_RNDN);
    mpfr_set_str(global_store[43], "32582657", 10, MPFR_RNDN);
    mpfr_set_str(global_store[44], "37156667", 10, MPFR_RNDN);
    mpfr_set_str(global_store[45], "42643801", 10, MPFR_RNDN);
    mpfr_set_str(global_store[46], "43112609", 10, MPFR_RNDN);
    mpfr_set_str(global_store[47], "57885161", 10, MPFR_RNDN);
    mpfr_set_str(global_store[48], "74207281", 10, MPFR_RNDN);
    mpfr_set_str(global_store[49], "77232917", 10, MPFR_RNDN);
    mpfr_set_str(global_store[50], "82589933", 10, MPFR_RNDN);
    mpfr_set_str(global_store[51], "136279841", 10, MPFR_RNDN);

    for (i = 0; i < LIST_OF_MERSENNE_PRIME_NUMBERS; i++)
    {
        mpfr_set(global_list[i], global_store[i], MPFR_RNDN);
    }

    global_line = LIST_OF_MERSENNE_PRIME_NUMBERS;

    do
    {
        view_menu();
        choice = atol(get_input("Enter your choice: "));
        switch (choice)
        {
            case 1:
                printf("You chose to load the list from the file\n");
                filename = get_input("Enter filename: ");
                global_line = load_file(filename);
                break;
            case 2:
                printf("You chose to print the list\n");
                print_list();
                break;
            case 3:
                printf("You chose to insert a new data in the list\n");
                line = atol(get_input("Enter line number: "));
                insert_data(line);
                break;
            case 4:
                printf("You chose to edit a data in the list\n");
                line = atol(get_input("Enter line number: "));
                edit_data(line);
                break;
            case 5:
                printf("You chose to delete a data in the list\n");
                line = atol(get_input("Enter line number: "));
                delete_data(line);
                break;
            case 6:
                printf("You chose to search a data in the list\n");
                search_data(get_input("Enter search term: "));
                break;
            case 7:
                printf("You chose to save the list to the file\n");
                filename = get_input("Enter filename: ");
                save_file(filename);
                break;
            case 8:
                printf("You chose to create Mersenne Prime Numbers file\n");
                create_mersenne_prime_numbers("mersenne-prime-numbers.txt");
                break;
            case 9:
                printf("You chose to create digits file\n");
                create_digits("mersenne-prime-numbers-digits.txt");
                break;
            case 10:
                printf("You chose to create MPN / digits file\n");
                create_mpn_digits("mersenne-prime-numbers-mpn-digits.txt");
                break;
            case 11:
                printf("You chose to create digits / MPN file\n");
                create_digits_mpn("mersenne-prime-numbers-digits-mpn.txt");
                break;
            case 12:
                printf("You chose to create log(2), 1 / log(2) file\n");
                create_log10_2("mersenne-prime-numbers-log10-2.txt");
                create_1_log10_2("mersenne-prime-numbers-1-log10-2.txt");
                break;
            case 0:
                printf("You chose to exit\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    for (i = 0; i < 1000; i++)
    {
        mpfr_clear(global_list[i]);
    }

    for (i = 0; i < LIST_OF_MERSENNE_PRIME_NUMBERS; i++)
    {
        mpfr_clear(global_store[i]);
    }

    free(global_list);
    free(global_store);
    free(filename);

   return 0;
}

// View menu
void view_menu()
{        
    // Welcome message
    printf("********************************************\n");
    printf("*   Welcome to the Mersenne Prime Number   *\n");
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*          FILE-MENU Version 0.1           *\n");
    printf("*                                          *\n"); 
    printf("********************************************\n");
    printf("*  1. Load the list from the file          *\n");
    printf("*  2. Print the list                       *\n");
    printf("*  3. Insert a new data in the list        *\n");
    printf("*  4. Edit a data in the list              *\n");
    printf("*  5. Delete a data in the list            *\n");
    printf("*  6. Search a data in the list            *\n");
    printf("*  7. Save the list to the file            *\n");
    printf("********************************************\n");
    printf("*  8. Create Mersenne Prime Numbers file   *\n");
    printf("*  9. Create digits file                   *\n");
    printf("* 10. Create MPN / digits file             *\n");
    printf("* 11. Create digits / MPN file             *\n");
    printf("* 12. Create log(2), 1 / log(2) file       *\n");
    printf("********************************************\n");
    printf("*  0. Exit                                 *\n");
    printf("********************************************\n");
    printf(" ! MPN = Mersenne Prime Numbers\n");
    printf(" ! digits = Mersenne Prime Numbers digits\n");
    printf(" ! MPN * log(2) + 1 = digits\n");
    printf(" ! digits / log(2) += MPN\n");
    printf(" ! log(2)     = 0.3010299956639811952137388\n");
    printf(" ! 1 / log(2) = 3.3219280948873623478703194\n");
    printf("********************************************\n");
    
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

// Load the list from the file
long load_file(char *filename)
{
    FILE *file;
    char buffer[1000];
    long line = 0;

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 0;
    }

    while (fgets(buffer, 1000, file) != NULL)
    {
        mpfr_set_str(global_list[line], buffer, 10, MPFR_RNDN);
        line++;
    }

    fclose(file);

    return line;
}

// Save the list to the file
int save_file(char *filename)
{
    FILE *file;
    long i;

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    for (i = 0; i < global_line; i++)
    {
        mpfr_fprintf(file, "%.0Rf\n", global_list[i]);
    }

    fclose(file);

    return 0;
}

// Print the list
void print_list(void)
{
    if (global_line == 0)
    {
        printf("No data\n");
        return;
    }

    for (long i = 0; i < global_line; i++)
    {
        mpfr_printf("%3d: %.0Rf\n", i + 1, global_list[i]);
    }

    return;
}

// Insert a new data in the list
void insert_data(long line)
{
    char *buffer;
    long index;

    if (global_line == 0)
    {
        printf("No data\n");
        return;
    }

    if (line < 0 || line > global_line)
    {
        printf("Error: Invalid line number\n");
        return;
    }

    line = line - 1;

    mpfr_printf("Current data: %.0Rf\n", global_list[line]);

    buffer = get_input("Enter new data: ");
    
    for (index = global_line; index > line; index--)
    {
        mpfr_set(global_list[index], global_list[index - 1], MPFR_RNDN);
    }

    mpfr_set_str(global_list[line], buffer, 10, MPFR_RNDN);

    global_line++;

    return ;
}

// Edit a data in the list
void edit_data(long line)
{
    char buffer[1000];

    if (global_line == 0)
    {
        printf("No data\n");
        return;
    }

    if (line < 0 || line > global_line)
    {
        printf("Error: Invalid line number\n");
        return;
    }

    line = line - 1;

    mpfr_printf("Current data: %.0Rf\n", global_list[line]);

    // scanf() function is returrn '\n' from input buffer
    // remove '\n' from buffer
    printf("Enter new data: ");
    scanf("%s", buffer);
    getchar();

    mpfr_set_str(global_list[line], buffer, 10, MPFR_RNDN);

    return ;
}

// Delete a data in the list
void delete_data(long line)
{
    long i;

    if (global_line == 0)
    {
        printf("No data\n");
        return;
    }

    if (line < 0 || line > global_line)
    {
        printf("Error: Invalid line number\n");
        return;
    }

    line = line - 1;

    for (i = line; i < global_line - 1; i++)
    {
        mpfr_set(global_list[i], global_list[i + 1], MPFR_RNDN);
    }

    global_line--;

    return ;
}

// Search a data in the list
int search_data(char *data)
{
    long i;
    mpfr_t temp;

    mpfr_init2(temp, 1024);

    for (i = 0; i < global_line; i++)
    {
        mpfr_set_str(temp, data, 10, MPFR_RNDN);
        if (mpfr_cmp(global_list[i], temp) == 0)
        {
            mpfr_printf("Found at line %d: %.0Rf\n", i + 1, global_list[i]);
            return 0;
        }
    }

    printf("Not found\n");

    mpfr_clear(temp);

    return 0;
}

int create_mersenne_prime_numbers(char *filename)
{
    FILE *file;
    
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    for (int i = 0; i < global_line; i++)
    {
        mpfr_fprintf(file, "%.0Rf\n", global_list[i]);
    }

    fclose(file);

    return 0;
}

// Create mersenne-prime-numbers-digits.txt
int create_digits(char *filename)
{
    char *buffer;
    long i;
    FILE *file;
    mpfr_t one;
    mpfr_t two;
    mpfr_t log10_2;
    mpfr_t result;
    
    buffer = (char *)malloc(1000 * sizeof(char));

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    mpfr_init2(one, 1024);
    mpfr_init2(two, 1024);
    mpfr_init2(log10_2, 1024);
    mpfr_init2(result, 1024);

    mpfr_set_str(one, "1.0", 10, MPFR_RNDN);
    mpfr_set_str(two, "2.0", 10, MPFR_RNDN);
    mpfr_set_str(log10_2, "0.0", 10, MPFR_RNDN);
    mpfr_set_str(result, "0.0", 10, MPFR_RNDN);

    mpfr_log10(log10_2, two, MPFR_RNDN);
    for (i = 0; i < global_line; i++)
    {
        mpfr_mul(result, global_list[i], log10_2, MPFR_RNDN);
        mpfr_add(result, result, one, MPFR_RNDN);
        mpfr_sprintf(buffer, "%.30Rf", result);
        buffer = strtok(buffer, ".");
        mpfr_fprintf(file, "%s\n", buffer);
    }

    free(buffer);
    fclose(file);
    mpfr_clear(one);
    mpfr_clear(two);
    mpfr_clear(log10_2);
    mpfr_clear(result);

    return 0;
}

// create_mersenne_prime_numbers_mpn_digits.txt
int create_mpn_digits(char *filename)
{
    char *buffer;
    long i;
    FILE *file;
    mpfr_t one;
    mpfr_t two;
    mpfr_t log10_2;
    mpfr_t result;
    mpfr_t digits;

    buffer = (char *)malloc(1000 * sizeof(char));

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    mpfr_init2(one, 1024);
    mpfr_init2(two, 1024);
    mpfr_init2(log10_2, 1024);
    mpfr_init2(result, 1024);
    mpfr_init2(digits, 1024);

    mpfr_set_str(one, "1.0", 10, MPFR_RNDN);
    mpfr_set_str(two, "2.0", 10, MPFR_RNDN);
    mpfr_set_str(log10_2, "0.0", 10, MPFR_RNDN);
    mpfr_set_str(result, "0.0", 10, MPFR_RNDN);
    mpfr_set_str(digits, "0.0", 10, MPFR_RNDN);

    mpfr_log10(log10_2, two, MPFR_RNDN);
    for (i = 0; i < global_line; i++)
    {
        mpfr_mul(result, global_list[i], log10_2, MPFR_RNDN);
        mpfr_add(result, result, one, MPFR_RNDN);
        mpfr_sprintf(buffer, "%.30Rf", result);
        buffer = strtok(buffer, ".");
        mpfr_set_str(digits, buffer, 10, MPFR_RNDN);
        mpfr_div(result, global_list[i], digits, MPFR_RNDN);
        mpfr_fprintf(file, "%.30Rf\n", result);
    }

    free(buffer);
    fclose(file);
    mpfr_clear(one);
    mpfr_clear(two);
    mpfr_clear(log10_2);
    mpfr_clear(result);
    mpfr_clear(digits);

    return 0;
}

// Create mersenne-prime-numbers-digits-mpn.txt
int create_digits_mpn(char *filename)
{
    char *buffer;
    long i;
    FILE *file;
    mpfr_t one;
    mpfr_t two;
    mpfr_t log10_2;
    mpfr_t result;
    mpfr_t digits;

    buffer = (char *)malloc(1000 * sizeof(char));

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    mpfr_init2(one, 1024);
    mpfr_init2(two, 1024);
    mpfr_init2(log10_2, 1024);
    mpfr_init2(result, 1024);
    mpfr_init2(digits, 1024);

    mpfr_set_str(one, "1.0", 10, MPFR_RNDN);
    mpfr_set_str(two, "2.0", 10, MPFR_RNDN);
    mpfr_set_str(log10_2, "0.0", 10, MPFR_RNDN);
    mpfr_set_str(result, "0.0", 10, MPFR_RNDN);
    mpfr_set_str(digits, "0.0", 10, MPFR_RNDN);

    mpfr_log10(log10_2, two, MPFR_RNDN);
    for (i = 0; i < global_line; i++)
    {
        mpfr_mul(result, global_list[i], log10_2, MPFR_RNDN);
        mpfr_add(result, result, one, MPFR_RNDN);
        mpfr_sprintf(buffer, "%.30Rf", result);
        buffer = strtok(buffer, ".");
        mpfr_set_str(digits, buffer, 10, MPFR_RNDN);
        mpfr_div(result, digits, global_list[i], MPFR_RNDN);
        mpfr_fprintf(file, "%.30Rf\n", result);
    }

    free(buffer);
    fclose(file);
    mpfr_clear(one);
    mpfr_clear(two);
    mpfr_clear(log10_2);
    mpfr_clear(result);
    mpfr_clear(digits);

    return 0;
}

// Create mersenne-prime-numbers-log10-2.txt
int create_log10_2(char *filename)
{
    FILE *file;
    mpfr_t two;
    mpfr_t log2;

    mpfr_init2(two, 1024);
    mpfr_init2(log2, 1024);

    mpfr_set_str(two, "2.0", 10, MPFR_RNDN);
    mpfr_set_str(log2, "0.0", 10, MPFR_RNDN);

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    mpfr_log10(log2, two, MPFR_RNDN);
    mpfr_fprintf(file, "%.30Rf\n", log2);

    fclose(file);
    mpfr_clear(two);
    mpfr_clear(log2);

    return 0;
}

// Create merseene-prime-numbers-1-log10-2.txt
int create_1_log10_2(char *filename)
{
    FILE *file;
    mpfr_t one;
    mpfr_t two;
    mpfr_t log10_2;
    mpfr_t result;

    mpfr_init2(one, 1024);
    mpfr_init2(two, 1024);
    mpfr_init2(log10_2, 1024);
    mpfr_init2(result, 1024);

    mpfr_set_str(one, "1.0", 10, MPFR_RNDN);
    mpfr_set_str(two, "2.0", 10, MPFR_RNDN);
    mpfr_set_str(log10_2, "0.0", 10, MPFR_RNDN);
    mpfr_set_str(result, "0.0", 10, MPFR_RNDN);

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    mpfr_log10(log10_2, two, MPFR_RNDN);
    mpfr_div(result, one, log10_2, MPFR_RNDN);
    mpfr_fprintf(file, "%.30Rf\n", result);

    fclose(file);
    mpfr_clear(one);
    mpfr_clear(two);
    mpfr_clear(log10_2);
    mpfr_clear(result);

    return 0;
}
