/* 
 * File:   main.cpp
 * Author: daroslav
 *
 * Created on 5 października 2015, 23:52
 */

#include <cstdlib>
#include <stdio.h>
#include "gmp.h"
#include <string.h>

using namespace std;

int main(int argc, char** argv) {

    FILE * file;

    //aktualna liczba
    mpf_t num; 
    
    //suma wszystkich liczb
    mpf_t sum;  
    
    //ilość wszystkich liczb
    mpf_t amount;
    
    //srednia
    mpf_t avg;
    
    //srednia
    mpf_t var;
    
    //inicjacja
    mpf_inits(num, sum, amount, avg, var);
    
    //zad 1
    file = fopen("test1", "r");
    if (file == NULL) {
        printf("File is null");
        mpf_clears (amount, sum, num, avg);
        exit(EXIT_FAILURE);
    }
                      
    char str[1024];
    while (!feof (file))
    {  
      fscanf (file, "%s", str);
      mpf_set_str(num, str, 10);
      
      mpf_add(sum, sum, num);
      mpf_add_ui(amount, amount, 1);
    }
        
    mpf_div(avg, sum, amount);
    
    gmp_printf ("Ilosc liczb %.Ff\n", amount, 50);
    gmp_printf ("Suma liczb %.Ff\n", sum, 50);
    gmp_printf ("Wartosc srednia  %.Ff\n", avg, 50);
    
    //zad 2
    mpf_pow_ui(avg, avg, 2);
    
    rewind(file);
    while (!feof (file))
    {  
      fscanf (file, "%s", str);
      mpf_set_str(num, str, 10);
      mpf_pow_ui(num, num, 2);
      mpf_sub(num, num, avg);
      mpf_add(var, var, num);
    }
    mpf_div(var, var, amount);
    gmp_printf ("Wariancja  %.Ff\n", var, 50);

    //zad 3
    rewind(file);


    fclose (file);    
    
    //mpf_clears (amount, sum, num, avg);
    
    exit(EXIT_SUCCESS); 
}

