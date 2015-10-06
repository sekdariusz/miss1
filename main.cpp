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
    
    //wariancja
    mpf_t var;
    
    //pomocnicza do 3 zad
    mpf_t help;
    
    //liczik do 3 zad
    mpf_t counter;
    
    //inicjacja
    mpf_inits(num, sum, amount, avg, var, help, counter);
    
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
      //pobieram kolejna liczbę z pliku
      fscanf (file, "%s", str);
      
      //zamieniam na tym gmp
      mpf_set_str(num, str, 10);
      
      //dodaje liczbe do sumy
      mpf_add(sum, sum, num);
      
      //zwiększam licznik liczb o 1
      mpf_add_ui(amount, amount, 1);
    }
    
    //dzielenie: suma_liczb/ilość_liczb = wartość średnia
    mpf_div(avg, sum, amount);
    
    //wyświetlanie
    gmp_printf ("Ilosc liczb %.Ff\n", amount, 50);
    gmp_printf ("Suma liczb %.Ff\n", sum, 50);
    gmp_printf ("Wartosc srednia  %.Ff\n", avg, 50);
    
    //zad 2
    
    //średnia wyliczona wcześniej do kwadratu
    mpf_pow_ui(avg, avg, 2);
    
    //przewijam plik do początku
    rewind(file);
    while (!feof (file))
    {  
      //pobieram kolejna liczbę z pliku
      fscanf (file, "%s", str);
      
      //zamieniam na typ gmp
      mpf_set_str(num, str, 10);
      
      //podnoszę liczbę do drugiej potęgi
      mpf_pow_ui(num, num, 2);
      
      //odejmuję od kwadratu obecnej liczby kwadrat średniej
      mpf_sub(num, num, avg);
      
      //dodaję poprzedni wynik do sumy
      mpf_add(var, var, num);
    }
    
    //dzielenie: suma/ilość_liczb
    mpf_div(var, var, amount);
    gmp_printf ("Wariancja  %.Ff\n", var, 50);

    //zad 3
    rewind(file);

    fscanf (file, "%s", str);
    mpf_set_str(num, str, 10);
    
    while(!feof (file))
    {
     //zwiększam licznik o 1
     mpf_add_ui(counter, counter, 1);

     //pobieram kolejną liczbę z pliku
     fscanf (file, "%s", str);
     
     //zamieniam na typ gmp
     mpf_set_str(help, str, 10);
     
     //sprawdzam czy liczby są sobie równe, jeśli tak to kończę while
     if(mpf_cmp(num, help) == 0) {
         break;
     }
    }
    
    fclose (file);    
    
    gmp_printf ("Okres  %.Ff\n", counter, 50);
    
    //mpf_clears (amount, sum, num, avg);
    
    exit(EXIT_SUCCESS); 
}

