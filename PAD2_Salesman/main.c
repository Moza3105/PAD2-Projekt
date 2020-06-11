#include <stdio.h>
#include <stdlib.h>
#include "libsalesman.h"

int main()
{
    FILE *worldcities = fopen("worldcities.csv", "r");

    if (NULL == worldcities)
    {
        printf("could not open file");
        exit(-1);
    }


    printf("\nHallo! Sie befinden sich im Testprogramm!\n\n");
    //Sleep(2000);
    printf("Hier koennen Sie alle sich in der Library befindlichen Funktionen nach belieben austesten!\n\n");
    //Sleep(3000);
    printf("Wir wuenschen einen angenehmen Aufenthalt! ;-)\n\n");
    //Sleep(3000);

    printf("Lassen Sie uns zuerst einige Staedte aus unserer Liste suchen, fuer die wir eine Route benoetigen:\n\n");
    //Sleep(3000);

    //Sleep(1000);


    //vars

    city cities[MAX];
    city* sortedcities;
    char selection;
    int nummer = 0;


    //Ablauf
    for(nummer; nummer<=MAX; nummer++)
    {
        printf("Geben Sie hierfuer die ersten paar Buchstaben ihrer gesuchten Stadt ein. \nWaehlen Sie dann Ihre gewuenschte Stadt aus der Liste. \nDies koennen Sie beliebig oft machen, um neue Staedte hinzuzufuegen.\n\n");
        cities[nummer] = search(worldcities);
        printf("Ihre Auswahle:\t");
        printcity(cities[nummer]);
        printf("\n");
        printf("Wollen Sie eine weiter Stadt ausweahlen?\nJa (j),  Nein (n)\n");
        scanf(" %c", &selection);
        if(selection=='n')
        {
            break;
        }

    }
    nummer++;
    //Sleep(1000);
    printf("Wunderbar! Hier ist ein Ueberblick ueber die ausgewaehlten Stadte:\n\n");


    printf("\n-------------------------------------------------------------------------------\n");
    for(int i = 0; i<nummer; i++)
    {
        printcity(cities[i]);
    }
    printf("-------------------------------------------------------------------------------\n");
    //Sleep(2000);

    printf("\nDas sieht noch etwas unordentlich aus... Bringen wir Ordnung rein!\n");
    while(1)
    {
        printf("\nWelchen Sortieralgorithmus wollen Sie anwenden?\nSelectionsort (s)\nBubblesort (b)\n");
        scanf(" %c", &selection);

        if(selection=='s')
        {
            printf("\nSoll nach den Namen oder der Einwohnerzahl sortiert werden?\nNames (n)\nPopulation (p)\n");
            scanf(" %c", &selection);
            //nummer = 19;
            sortedcities = selectionsort(cities,nummer,selection);
            printf("\n-------------------------------------------------------------------------------\n");
            for(int i = 0; i<nummer; i++)
            {
                printcity(cities[i]);
            }
            printf("-------------------------------------------------------------------------------\n");
        }

        else if(selection=='b')
        {
            printf("\nSoll nach den Namen oder der Einwohnerzahl sortiert werden?\nNames (n)\nPopulation (p)\n");
            scanf(" %c", &selection);
            sortedcities = bubblesort(cities,nummer,selection);
            printf("\n-------------------------------------------------------------------------------\n");
            for(int i = 0; i<nummer; i++)
            {
                printcity(cities[i]);
            }
            printf("-------------------------------------------------------------------------------\n");

        }
        else
        {
            printf("\nIhre Eingabe war ungueltig! Versuchen Sie es nocheinmal.\n\n");
            continue;
        }
        printf("\nWollen Sie nochmal eine andere Sortierkonfiguration testen?\nJa (j),  Nein (n)\n");
        scanf(" %c", &selection);
        if(selection!='j')
        {
            break;
        }

    }



    getfirstcity(cities,nummer);
    CreateCostMatrix(cities,nummer);
    printf("\n\nAlles klar. So sieht ihr schnellster Weg aus:\n\n");
    minimum_cost(cities,nummer);


    if(worldcities!=NULL)
    {
        fclose(worldcities);
    }

    return 0;

}
