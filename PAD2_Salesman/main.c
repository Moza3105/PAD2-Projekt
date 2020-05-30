#include <stdio.h>
#include <stdlib.h>
#include "libsalesman.h"

int main()
{
    FILE *worldcities = fopen("worldcities.txt", "r");

    printf("Hallo! Das ist das Testprogramm!\n");
    if (NULL == worldcities)
    {
        printf("could not open file");
        exit(-1);
    }

    city cities[19];
    int number = sizeof(cities)/sizeof(cities[0]);
    city* sortedcities;

    // define 19 cities
    {

    cities[0] = makecity("Wien","ABCD",0,90,"Austria","2er","3er","adminland","Vienna",1200000,12345678);
    cities[1] = makecity("Tokyo","Tokyo",35.6850,139.7514,"Japan","JP","JPN","Tōkyō","primary",35676000,1392685764);
    cities[2] = makecity("New York","New York",40.6943,-73.9249,"United States","US","USA","New York","",19354922.0,1840034016);
    cities[3] = makecity("Mexico City","Mexico City",19.4424,-99.1310,"Mexico","MX","MEX","Ciudad de México","primary",19028000,1484247881);
    cities[4] = makecity("Mumbai","Mumbai",19.0170,72.8570,"India","IN","IND","Mahārāshtra","admin",18978000,1356226629);
    cities[5] = makecity("São Paulo","Sao Paulo",-23.5587,-46.6250,"Brazil","BR","BRA","São Paulo","admin",18845000,1076532519);
    cities[6] = makecity("Delhi","Delhi",28.6700,77.2300,"India","IN","IND","Delhi","admin",15926000,1356872604);
    cities[7] = makecity("Shanghai","Shanghai",31.2165,121.4365,"China","CN","CHN","Shanghai","admin",14987000,1156073548);
    cities[8] = makecity("Kolkata","Kolkata",22.4950,88.3247,"India","IN","IND","West Bengal","admin",14787000,1356060520);
    cities[9] = makecity("Los Angeles","Los Angeles",34.1139,-118.4068,"United States","US","USA","California","",12815475.0,1840020491);
    cities[10] = makecity("Dhaka","Dhaka",23.7231,90.4086,"Bangladesh","BD","BGD","Dhaka","primary",12797394,1050529279);
    cities[11] = makecity("Buenos Aires","Buenos Aires",-34.6025,-58.3975,"Argentina","AR","ARG","Buenos Aires, Ciudad Autónoma de","primary",12795000,1032717330);
    cities[12] = makecity("Karachi","Karachi",24.8700,66.9900,"Pakistan","PK","PAK","Sindh","admin",12130000,1586129469);
    cities[13] = makecity("Cairo","Cairo",30.0500,31.2500,"Egypt","EG","EGY","Al Qāhirah","primary",11893000,1818253931);
    cities[14] = makecity("Rio de Janeiro","Rio de Janeiro",-22.9250,-43.2250,"Brazil","BR","BRA","Rio de Janeiro","admin",11748000,1076887657);
    cities[15] = makecity("Ōsaka","Osaka",34.7500,135.4601,"Japan","JP","JPN","Ōsaka","admin",11294000,1392419823);
    cities[16] = makecity("Beijing","Beijing",39.9289,116.3883,"China","CN","CHN","Beijing","primary",11106000,1156228865);
    cities[17] = makecity("Manila","Manila",14.6042,120.9822,"Philippines","PH","PHL","Manila","primary",11100000,1608618140);
    cities[18] = makecity("Moscow","Moscow",55.7522,37.6155,"Russia","RU","RUS","Moskva","primary",10452000,1643318494);


    }

    for(int i = 0; i<19; i++)
    {
        printcity(cities[i]);
    }

    printf("\n--------\n");
    //cities: array of cities to be sorted
    //number: items in the array
    //'p','n' modes for population and name
     sortedcities = selectionsort(cities,number,'p');
     sortedcities = selectionsort(cities,number,'n');
     sortedcities = selectionsort(cities,number,'l');

    printf("--------\n\n");

    for(int i = 0; i<19; i++)
    {
        printcity(sortedcities[i]);
    }



    fclose(worldcities);
    return 0;
}
