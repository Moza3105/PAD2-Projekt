#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 50


float matrix[MAX][MAX];

typedef struct City
{
    char  name[100];
    char ascii[100];
    float lat;
    float lng;
    char country[100];
    char iso2[5];
    char iso3[6];
    char adminname[100];
    char capital[100];
    int population;
    int id;
} city;


float distance(city uno, city dos)
{
    float distance;
    float x1 = uno.lng/57.29578;
    float y1 = uno.lat/57.29578;
    float x2 = dos.lng/57.29578;
    float y2 = dos.lat/57.29578;

    float deltax = x1-x2;

    float deltay = y1-y2;

    float a = sin(deltay/2)*sin(deltay/2) + cos(y1)*cos(y2)*sin(deltax/2)*sin(deltax/2);

    float c = 2*atan2(sqrt(a),sqrt(1-a));

    distance = 6371*c;
    return distance;
}

city makecity(char* name, char* ascii, float lat, float lng, char* country, char* iso2, char* iso3, char* adminname, char* capital, int population, int id)
{

    city tmp;
    strcpy(tmp.name,name);
    strcpy(tmp.ascii,ascii);
    tmp.lat = lat;
    tmp.lng = lng;
    strcpy(tmp.country,country);
    strcpy(tmp.iso2,iso2);
    strcpy(tmp.iso3,iso3);
    strcpy(tmp.adminname,adminname);
    strcpy(tmp.capital,capital);

    tmp.population = population;
    tmp.id = id;
    return tmp;
}

void slice_str(const char * str, char * buffer, size_t start, size_t end)
{
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i )
    {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

city printcity(city tmp)
{
    printf("%s, %s, %.5f, %.5f, %s, %s, %s, %s, %s, %d, %d\n", tmp.name, tmp.ascii, tmp.lat, tmp.lng, tmp.country, tmp.iso2, tmp.iso3, tmp.adminname, tmp.capital, tmp.population, tmp.id);
    return tmp;
}

city search(FILE* myfile)
{
    city foundcities;

    city tight[1000];

    char anfang[100];
    int selection;
    while(1)
    {

        scanf("%s", anfang);
        anfang[0]=toupper(anfang[0]);
        int length;
        length = strlen(anfang);
        for(int i = 1; i<length; i++)
        {

            anfang[i]=tolower(anfang[i]);

        }


        int good=1;
        int j=0;
        int l=1;
        char c;
        char* str;
        str = malloc(sizeof(char));
        fseek(myfile, 3, SEEK_SET);


        int citynumber = 0;


        while(1)
        {
            c = fgetc(myfile);

            if( feof(myfile) )
            {
                break ;
            }

            if(c=='\n')
            {


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
                for(int i = 0; i<length; i++)
                {

                    if(anfang[i]==str[i+1])
                    {
                        good = 1;



                    }
                    else
                    {
                        good = 0;
                        break;
                    }
                }

                if(good==1)
                {



                    size_t len = strlen(str);
                    char buffer[len + 1];

                    size_t start = 1;
                    size_t end = 0;
                    for (int comma = 0; comma < 10; comma++)
                    {
                        for(int i = (end+1); i < len; i++)
                        {

                            if(str[i] == ',')
                            {

                                end = i-1;
                                str[i]='0';
                                break;


                            }

                        }
                        slice_str(str, buffer, start, end);
                        start = end+2;


                        switch(comma)
                        {

                        case 0:
                            strcpy(tight[citynumber].name,buffer);

                            break;

                        case 1:
                            strcpy(tight[citynumber].ascii,buffer);
                            break;

                        case 2:
                            tight[citynumber].lat = atof(buffer);
                            break;

                        case 3:
                            tight[citynumber].lng = atof(buffer);
                            break;

                        case 4:
                            strcpy(tight[citynumber].country,buffer);
                            break;

                        case 5:
                            strcpy(tight[citynumber].iso2,buffer);
                            break;

                        case 6:
                            strcpy(tight[citynumber].iso3,buffer);
                            break;

                        case 7:
                            strcpy(tight[citynumber].adminname,buffer);
                            break;

                        case 8:
                            strcpy(tight[citynumber].capital,buffer);
                            break;

                        case 9:
                            tight[citynumber].population = atoll(buffer);
                            break;

                        default:

                            break;


                        }

                    }
                    slice_str(str, buffer, start, len);

                    tight[citynumber].id = atoll(buffer);
                    printf("%d:\t",citynumber+1);
                    printcity(tight[citynumber]);


                    citynumber++;

                    good = 0;
                }

                l++;

            }

            str[j]=c;
            //printf("%c", c);
            str = (char *) realloc(str, (j+2)*sizeof(char));
            j++;

        }
        if(citynumber==0)
        {
            printf("\n\nKeine Stadt gefunden! Versuchen Sie es nochmal.\n");

        }
        else
        {
            break;
        }
    }
    printf("\n\nWaehlen Sie ihre Stadt aus. (tippen Sie die Zahl ein)\n");
    scanf("%d",&selection);
    foundcities=tight[selection-1];





    return foundcities;
}

city* selectionsort(city* array, int length, char mode)
{


    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int min;
    city placeholdercity;
    int* value = malloc(length*sizeof(int));
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
        printf("\nSorted using Selection-Sort! ;-)  --Alphabetical order\n");
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
        printf("\nSorted using Selection-Sort! ;-)  --max. Population to min.\n");
    }
    else
    {
        printf("\nAttempted Selection-Sort: Wrong mode selected! Array not sorted!\n");
    }





    return array;
}

city* bubblesort(city* array, int length, char mode)
{

    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int tmpval;
    city placeholdercity;
    int* value = malloc(length*sizeof(int));
    char* tmp;

    if(mode=='n')
    {
        for(int i = 0; i<length; i++)
        {

            tmp = array[i].name;
            for(int j = 0; j < 26; j++)
            {

                if(tmp[0]==alphabet[j])
                {
                    value[i]=j;
                    break;
                }
                else if(j==25)
                {
                    value[i]=27;
                }
            }

        }
        for(int j = 0; j<length; j++)
        {

            for(int i = 0; (i+1)<length; i++)
            {
                if(value[i]>value[i+1])
                {
                    tmpval=value[i];
                    value[i]=value[i+1];
                    value[i+1]=tmpval;
                    placeholdercity = array[i];
                    array[i]=array[i+1];
                    array[i+1]= placeholdercity;
                }
            }




        }
        printf("\nSorted using Bubblesort! ;-)  --Alphabetical order\n");
    }

    else if(mode=='p')
    {
        for(int j = 0; j<length; j++)
        {

            for(int i = 0; (i+1)<length; i++)
            {
                if(array[i].population<array[i+1].population)
                {

                    placeholdercity = array[i];
                    array[i]=array[i+1];
                    array[i+1]= placeholdercity;
                }
            }




        }
        printf("\nSorted using Bubblesort! ;-)  --max. Population to min.\n");
    }
    else
    {
        printf("\nAttempted Bubblesort: Wrong mode selected! Array not sorted!\n");
    }

    return array;
}

void CreateCostMatrix(city* array,int n)
{

    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            matrix[i][j]=distance(array[i],array[j]);

        }

    }




}

void minimum_cost(city* array, int number)
{
    int visited[MAX]= {0};
    int place = 0;
    int lastplace = 0;

    float sum = 0;
    float min;




    int h;
    for(int j = 0; j<(number-1); j++)
    {
        h=place;
        matrix[h][0]=0;

        for(int g = 0; g<number; g++)
        {
            if(matrix[h][g]!=0)
            {
                min = matrix[h][g];
                place = g;

                break;
            }
        }
        for(int i = 0; i<number; i++)
        {

            if((matrix[h][i]!=0)&&(visited[i]!=1))
            {
                if(matrix[h][i]<min)
                {
                    min = matrix[h][i];

                    place = i;

                }
            }


        }
        visited[place]=1;
        matrix[place][h]=0;
        matrix[h][place]=0;
        printf("Von: %s\tNach:%s\tkm:%f  \n",array[lastplace].name,array[place].name,min);
        lastplace = place;
        sum +=min;

    }
    printf("Von: %s\tNach:%s\tkm:%f  \n\n",array[lastplace].name,array[0].name,matrix[lastplace][0]);
    printf("Insgesamt gefahrene Kilometer: %f\n",sum);

}

void getfirstcity(city* array, int number)
{
    int selection;
    city tmp;
    printf("Wo soll die Fahrt losgehen?  (tippen Sie die Zahl ein)\n\n");
    for(int i = 0; i<number; i++)
    {
        printf("%d:\t",i+1);
        printcity(array[i]);
    }
    scanf("%d", &selection);
    if(selection>0&&selection<=number)
    {
        tmp = array[0];
        array[0]=array[selection-1];
        array[selection-1] = tmp;
    }
}
