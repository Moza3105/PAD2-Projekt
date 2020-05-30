#include <string.h>

typedef struct City
{
    char*  name;
    char* ascii;
    float lat;
    float lng;
    char* country;
    char* iso2;
    char* iso3;
    char* adminname;
    char* capital;
    int population;
    int id;
} city;


city makecity(char* name, char* ascii, float lat, float lng, char* country, char* iso2, char* iso3, char* adminname, char* capital, int population, int id)
{
    city tmp;
    tmp.name = name;
    tmp.ascii = ascii;
    tmp.lat = lat;
    tmp.lng = lng;
    tmp.country = country;
    tmp.iso2 = iso2;
    tmp.iso3 = iso3;
    tmp.adminname = adminname;
    tmp.capital = capital;
    tmp.population = population;
    tmp.id = id;
    return tmp;
}

city printcity(city tmp)
{
    printf("%s, %s, %.5f, %.5f, %s, %s, %s, %s, %s, %d, %d\n", tmp.name, tmp.ascii, tmp.lat, tmp.lng, tmp.country, tmp.iso2, tmp.iso3, tmp.adminname, tmp.capital, tmp.population, tmp.id);
    return tmp;
}

city* selectionsort(city* array, int length, char mode)
{


    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int min;
    city placeholdercity;
    int* value = malloc(length*sizeof(array[0]));
    char* tmp;

    if(mode=='n')
    {
        for(int i = 0; i<length; i++)
        {

            tmp = array[i].name;
            //printf("%c", tmp[0]);
            for(int j = 0; j < 26; j++)
            {

                if(tmp[0]==alphabet[j])
                {
                    //printf("%d  ", j);
                    value[i]=j;
                    break;
                }
                else if(j==25)
                {
                    //printf("%d  ", 27);
                    value[i]=27;
                }
            }

        }
        for(int j = 0; j<length; j++)
        {

            min=j;

            for(int i = j; i<length; i++)
            {
                if(value[i]<value[min])
                {
                    min = i;
                }
            }
            placeholdercity = array[j];
            array[j]=array[min];
            array[min]= placeholdercity;
            value[min]=value[j];

        }
        printf("Sorted using Selection-Sort! ;-)  --Alphabetical order\n");
    }
    else if(mode=='p')
    {
        for(int j = 0; j<length; j++)
        {

            min=j;

            for(int i = j; i<length; i++)
            {
                if(array[i].population>array[min].population)
                {
                    min = i;
                }
            }
            placeholdercity = array[j];
            array[j]=array[min];
            array[min]= placeholdercity;

        }
        printf("Sorted using Selection-Sort! ;-)  --max. Population to min.\n");
    }
    else
    {
        printf("Attempted Selection-Sort: Wrong mode selected! Array not sorted!\n");
    }





    return array;
}
//nicht benutzt aber vlt hilfreich
void makearray(FILE *myfile)
{
    city* unsorted = malloc(7);
    city Wien = makecity("Wien","ABCD",0,90,"Austria","2er","3er","adminland","Vienna",8000000,12345678);
    printcity(Wien);

    int j=0;
    int l=1;
    char c;
    char* str;
    str = malloc(sizeof(char));
    fseek(myfile, 3, SEEK_SET);


    while(1)
    {
        c = fgetc(myfile);

        if( feof(myfile) )
        {
            break ;
        }

        if(c=='\n')
        {
            printf("--< %d",l);
            str[j]='\0';
            j=0;



            int len = strlen(str);

            for(int i = 0; i < len; i++)
            {
                if(str[i] == '\"')
                {
                    for(int h = i; h < len; h++)
                    {
                        str[h] = str[h + 1];

                    }
                    len--;
                    i--;
                }
            }

            len = strlen(str);
            for(int i = 0; i < len; i++)
            {

                if(str[i] == ',')
                {
                    for(int h = i; h < len; h++)
                    {
                        str[h] = str[h + 1];
                    }
                    len--;
                    i--;

                }
                unsorted[l].name = str;
            }



            //printf("\n%s --ln:%d\n", str, l);
            printf("citysize*l:%d\n", l*sizeof(city));
            realloc(str, (1)*sizeof(char));

            unsorted = (city*) realloc(unsorted,l*sizeof(city));
            if (unsorted == NULL)
            {
                printf("NOOOOOO!!!");
                return -1;
            }

            //printf("unsorted: %d\n",(sizeof(unsorted[7000])));

            printf("check\n");
            l++;



        }

        str[j]=c;
        //printf("%c", c);
        str = (char *) realloc(str, (j+2)*sizeof(char));
        j++;

    }

    free(str);




    //return unsorted;
}
