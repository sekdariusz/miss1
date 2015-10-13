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
    
    int d = strtol(argv[1], NULL, 10);
    //printf("Żądana dokładność: %d\n", d);
    
    //aktualna liczba
    mpz_t num; 
    
    //suma wszystkich liczb
    mpz_t sum;  
    
    //ilość wszystkich liczb
    mpz_t amount;
    
    //wynik dzielenia
    mpz_t q;
    
    //reszta z dzielenia
    mpz_t r;
    
    //10
    mpz_t base;
    
    //do zad 2
    //suma kwadratów
    mpz_t pow_sum;
    
    //wynik odejmowania
    mpz_t sub;
    
    //pomocnicza do 3 zad
    mpz_t help;
    
    //licznik do 3 zad
    mpz_t counter;
    
    //inicjacja
    mpz_inits(num, sum, amount, q, r, base, sub, pow_sum, help, counter);
                  
    char str;
    while(scanf("%s", &str) == 1)
    {  
      mpz_set_str(num, &str, 10);
      mpz_add(sum, sum, num);
      
      mpz_pow_ui(num, num, 2);
      mpz_add(pow_sum, pow_sum, num);
      
      mpz_add_ui(amount, amount, 1);
    }
        
    char *result = (char *) malloc(1024);
    char *pom = (char *) malloc(1024);
    
    //przed kropką]
    mpz_fdiv_qr (q, r, sum, amount);
    mpz_get_str(result, 10, q);
    
    //po kropce
    mpz_set_ui(base, 10);
    
    mpz_pow_ui(base, base, d);
    mpz_mul(r, r, base);
    mpz_fdiv_qr (q, r, r, amount); 
    mpz_get_str(pom, 10, q);
    
    char *avg = (char *) malloc(2 + strlen(result)+ strlen(pom) );
    strcpy(avg, result);
    strcat(avg, ".");
    strcat(avg, pom);

    printf("Srednia: %s\n", avg);
    
    //zad 2
       
    mpz_mul(pow_sum, pow_sum, amount);
    mpz_pow_ui(sum, sum, 2);
    mpz_pow_ui(amount, amount, 2);
    
    //przed kropką
    mpz_sub(sub, pow_sum, sum);
    mpz_fdiv_qr (q, r, sub, amount);
    mpz_get_str(result, 10, q);
    
    mpz_mul(r, r, base);
    mpz_fdiv_qr (q, r, r, amount); 
    mpz_get_str(pom, 10, q);
    
    char *var = (char *) malloc(2 + strlen(result)+ strlen(pom) );
    strcpy(var, result);
    strcat(var, ".");
    strcat(var, pom);

    printf("Wariancja: %s\n", var);
    
    
    /*
    //zad 3
    rewind(file);

    fscanf (file, "%s", str);
    mpz_set_str(num, str, 10);
    
    while(!feof (file))
    {
     //zwiększam licznik o 1
     mpz_add_ui(counter, counter, 1);

     //pobieram kolejną liczbę z pliku
     fscanf (file, "%s", str);
     
     //zamieniam na typ gmp
     mpz_set_str(help, str, 10);
     
     //sprawdzam czy liczby są sobie równe, jeśli tak to kończę while
     if(mpz_cmp(num, help) == 0) {
         break;
     }
    }
    
    fclose (file);    
    
    gmp_printf ("Okres  %.Ff\n", counter, d);
    
    */
    //mpz_clears (num, sum, amount, q, r, var, help, counter);
    
    exit(EXIT_SUCCESS); 
} 



