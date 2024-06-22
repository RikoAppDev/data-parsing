#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_data(long long id, int m_mod2, char m_mod1, char m_type1, char m_type2, double value, int time, int date)
{
    printf("ID cislo mer. osoby: %lld\n", id);
    printf("Mer. modul: %c%d\n", m_mod1, m_mod2);
    printf("Typ  mer.  veliciny: %c%c\n", m_type1, m_type2);
    printf("Hodnota: %f\n", value);
    printf("Cas merania: %04d\n", time);
    printf("Datum: %d\n\n", date);
}

void scan_data(FILE **fr)
{
    long long id;
    int time, date, m_mod2;
    double value;
    char m_mod1, m_type[2];

    while (fscanf(*fr, "%lld", &id) != EOF)
    {
        fscanf(*fr, "%lld\n", &id);
        fscanf(*fr, "%c%d\n", &m_mod1, &m_mod2);
        fscanf(*fr, "%c%c\n", &m_type[0], &m_type[1]);
        fscanf(*fr, "%lf\n", &value);
        fscanf(*fr, "%d\n", &time);
        fscanf(*fr, "%d\n\n", &date);
        print_data(id, m_mod2, m_mod1, m_type[0], m_type[1], value, time, date);
    }
    rewind(*fr);
}

void v_command(FILE **fr, int *v, int n, long long *id, int *m_mod2, char *m_mod1, char *m_type, double *value, int *time, int *date, int record_count)
{
    if (*v)
    {
        if (n)
        {
            for (int i = 0; i < record_count; i++)
            {
                print_data(*(id + i), *(m_mod2 + i), *(m_mod1 + i), *(m_type + i * 2), *(m_type + i * 2 + 1), *(value + i), *(time + i), *(date + i));
            }
        }
        else
        {
            scan_data(fr);
        }
    }
    else
    {
        if ((*fr = fopen("C:\\Users\\frede\\Desktop\\STU - FIIT\\Proceduralne programovanie\\Visual Studio Code\\Projekt 1\\dataloger.txt", "r")) == NULL)
        {
            printf("Neotvoreny subor.\n");
        }
        else
        {
            *v = 1;
            scan_data(fr);
        }
    }
}

void sort_value_by_date(double *sort_value, int *sort_date, int *sort_time, int counter)
{
    for (int i = 0; i < counter - 1; i++)
    {
        for (int j = 0; j < counter - i - 1; j++)
        {
            if (*(sort_date + j) > *(sort_date + j + 1))
            {
                double help2 = *(sort_value + j);
                *(sort_value + j) = *(sort_value + j + 1);
                *(sort_value + j + 1) = help2;

                int help3 = *(sort_date + j);
                *(sort_date + j) = *(sort_date + j + 1);
                *(sort_date + j + 1) = help3;

                int help4 = *(sort_time + j);
                *(sort_time + j) = *(sort_time + j + 1);
                *(sort_time + j + 1) = help4;
            }
        }
    }
}

void s_command(int n, int *m_mod2, char *m_mod1, char *m_type, double *value, int *time, int *date, int record_count)
{
    if (!n)
    {
        printf("Polia nie su vytvorene.\n");
    }
    else
    {
        int i_m_mod2;
        char i_m_mod1, i_m_type[2];
        scanf("%c%d %c%c", &i_m_mod1, &i_m_mod2, &i_m_type[0], &i_m_type[1]);
        getchar();

        double sort_value[record_count];
        int sort_date[record_count], sort_time[record_count], counter = 0, exist = 0;
        for (int i = 0; i < record_count; i++)
        {
            if (*(m_mod1 + i) == i_m_mod1 && *(m_mod2 + i) == i_m_mod2 && *(m_type + i * 2) == i_m_type[0] && *(m_type + i * 2 + 1) == i_m_type[1])
            {
                exist = 1;
                sort_value[counter] = *(value + i);
                sort_date[counter] = *(date + i);
                sort_time[counter] = *(time + i);
                counter++;
            }
        }

        sort_value_by_date(sort_value, sort_date, sort_time, counter);

        FILE *fw;
        fw = fopen("C:\\Users\\frede\\Desktop\\STU - FIIT\\Proceduralne programovanie\\Visual Studio Code\\Projekt 1\\vystup_S.txt", "w");

        for (int i = 0; i < counter; i++)
        {
            fprintf(fw, "%d%04d\t%f\n", *(sort_date + i), *(sort_time + i), *(sort_value + i));
        }
        fclose(fw);

        if (exist)
        {
            printf("Pre dany vstup je vytvoreny txt subor.\n");
        }
        else
        {
            printf("Pre dany vstup neexistuju zaznamy.\n");
        }
    }
}

void sort_values(double *value, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (*(value + j) > *(value + j + 1))
            {
                int help = *(value + j);
                *(value + j) = *(value + j + 1);
                *(value + j + 1) = help;
            }
        }
    }
}

void h_command(int n, char *m_type, double *value, int record_count)
{
    if (!n)
    {
        printf("Polia nie su vytvorene.\n");
    }
    else
    {
        double sorted_value[record_count];

        char i_m_type[2];
        scanf("%c%c", &i_m_type[0], &i_m_type[1]);
        getchar();

        int j = 0;
        for (int i = 0; i < record_count; i++)
        {
            if (*(m_type + i * 2) == i_m_type[0] && *(m_type + i * 2 + 1) == i_m_type[1])
            {
                sorted_value[j] = *(value + i);
                j++;
            }
        }

        sort_values(sorted_value, j);

        int counter = 0, int_start = 0, int_end = 5;

        printf("\tAx\t    pocetnost\n");

        int i = 0;
        while (i < j)
        {
            if (*(sorted_value + i) > int_start && *(sorted_value + i) <= int_end)
            {
                counter++;
                i++;
            }
            else
            {
                if (counter != 0)
                {
                    printf("(%3d.0 - %3d.0>\t\t%d\n", int_start, int_end, counter);
                }
                counter = 0;
                int_start += 5;
                int_end += 5;
            }
        }
        printf("(%3d.0 - %3d.0>\t\t%d\n", int_start, int_end, counter);
    }
}

void r_command(int n, int *time, int record_count)
{
    if (!n)
    {
        printf("Polia nie su vytvorene.\n");
    }
    else
    {
        int time_table[24][60] = {0};

        for (int i = 0; i < record_count; i++)
        {
            int s = *(time + i) % 100;
            int h = *(time + i) /= 100;

            time_table[h][s] = 1;
        }

        for (int i = 0; i < 24; i++)
        {
            int next = 0;
            for (int j = 0; j < 60; j++)
            {
                if (time_table[i][j] != 0)
                {
                    if (!next)
                    {
                        printf("%02d:", i);
                        printf("%02d", j);
                        next = 1;
                    }
                    else
                    {
                        printf(", %02d", j);
                    }
                }
            }
            if (next)
            {
                printf("\n");
            }
        }
    }
}

void n_command(FILE **fr, int *v, int *n, long long **id, int **m_mod2, char **m_mod1, char **m_type, double **value, int **time, int **date, int *record_count)
{
    if (!*v)
    {
        printf("Neotvoreny subor.\n");
    }
    else
    {
        if (*n)
        {
            for (int i = 0; i < *record_count; i++)
            {
                *(*id + i) = 0;
            }
            free(*id);
            *id = NULL;
            free(*m_mod2);
            *m_mod2 = NULL;
            free(*m_mod1);
            *m_mod1 = NULL;
            free(*m_type);
            *m_type = NULL;
            free(*value);
            *value = NULL;
            free(*time);
            *time = NULL;
            free(*date);
            *date = NULL;
            *record_count = 0;
        }

        *n = 1;
        char z;
        while ((z = getc(*fr)) != EOF)
        {
            if (z == '\n')
                (*record_count)++;
        }
        *record_count = ++(*record_count) / 7;
        rewind(*fr);

        *id = (long long *)malloc(*record_count * sizeof(long long));
        *time = (int *)malloc(*record_count * sizeof(int));
        *date = (int *)malloc(*record_count * sizeof(int));
        *m_mod2 = (int *)malloc(*record_count * sizeof(int));
        *value = (double *)malloc(*record_count * sizeof(double));
        *m_mod1 = (char *)malloc(*record_count * sizeof(char));
        *m_type = (char *)malloc(*record_count * 2 * sizeof(char));

        if (*id == NULL || *time == NULL || *date == NULL || *m_mod2 == NULL || *value == NULL || *m_mod1 == NULL || *m_type == NULL)
        {
            printf("Pole sa nepodarilo vytvorit.\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < *record_count; i++)
        {
            fscanf(*fr, "%lld\n", (*id + i));
            fscanf(*fr, "%c%d\n", (*m_mod1 + i), (*m_mod2 + i));
            fscanf(*fr, "%c%c\n", (*m_type + i * 2), (*m_type + i * 2 + 1));
            fscanf(*fr, "%lf\n", (*value + i));
            fscanf(*fr, "%d\n", (*time + i));
            fscanf(*fr, "%d\n\n", (*date + i));
        }
        rewind(*fr);
    }
}

int check_type(char type1, char type2)
{
    char type[9][2] = {"R1", "U1", "A1", "R2", "U2", "A2", "R4", "U4", "A4"};

    for (int i = 0; i < 9; i++)
    {
        if (type1 == type[i][0] && type2 == type[i][1])
        {
            return 1;
        }
    }
    return 0;
}

int check_time(int time)
{
    int min = time % 100;
    time /= 100;
    if (min > 59)
    {
        return 0;
    }
    if (time > 23)
    {
        return 0;
    }
    return 1;
}

int check_date(int date)
{
    if (date > 99999999 || date < 10000000)
    {
        return 0;
    }
    int day = date % 100;
    if (day > 31)
    {
        return 0;
    }
    date /= 100;
    int month = date % 100;
    if (month > 12)
    {
        return 0;
    }
    return 1;
}

void c_command(FILE **fr, int v)
{
    if (!v)
    {
        printf("Neotvoreny subor.\n");
    }
    else
    {
        long long id;
        int time, date, m_mod2;
        double value;
        char m_mod1, m_type[2];
        int correct = 1;

        while (fscanf(*fr, "%lld", &id) != EOF)
        {
            fscanf(*fr, "%lld\n", &id);
            fscanf(*fr, "%c%d\n", &m_mod1, &m_mod2);
            fscanf(*fr, "%c%c\n", &m_type[0], &m_type[1]);
            fscanf(*fr, "%lf\n", &value);
            fscanf(*fr, "%d\n", &time);
            fscanf(*fr, "%d\n\n", &date);

            if (id % 11 != 0)
            {
                printf("Nekorektne zadany vstup: ID cislo mer. osoby.\n");
                correct = 0;
            }
            else if (m_mod1 < 'A' || m_mod1 > 'Z' || m_mod2 < 0 || m_mod2 > 99)
            {
                printf("Nekorektne zadany vstup: Mer. modul.\n");
                correct = 0;
            }
            else if (check_type(m_type[0], m_type[1]) == 0)
            {
                printf("Nekorektne zadany vstup: Typ mer. veliciny.\n");
                correct = 0;
            }
            else if (check_time(time) == 0)
            {
                printf("Nekorektne zadany vstup: Cas merania.\n");
                correct = 0;
            }
            else if (check_date(date) == 0)
            {
                printf("Nekorektne zadany vstup: Datum.\n");
                correct = 0;
            }
        }
        rewind(*fr);
        if (correct)
        {
            printf("Data su korektne.\n");
        }
    }
}

void z_command(int n, long long **id, int **m_mod2, char **m_mod1, char **m_type, double **value, int **time, int **date, int *record_count)
{
    if (n)
    {
        long long i_id;
        scanf("%lld", &i_id);
        getchar();

        int new_count = 0;
        for (int i = 0; i < *record_count; i++)
        {
            if (*(*id + i) != i_id)
            {
                *(*id + new_count) = *(*id + i);
                *(*m_mod1 + new_count) = *(*m_mod1 + i);
                *(*m_mod2 + new_count) = *(*m_mod2 + i);
                *(*m_type + new_count * 2) = *(*m_type + i * 2);
                *(*m_type + new_count * 2 + 1) = *(*m_type + i * 2 + 1);
                *(*value + new_count) = *(*value + i);
                *(*time + new_count) = *(*time + i);
                *(*date + new_count) = *(*date + i);
                new_count++;
            }
        }

        *id = (long long *)realloc(*id, new_count * sizeof(long long));
        *time = (int *)realloc(*time, new_count * sizeof(int));
        *date = (int *)realloc(*date, new_count * sizeof(int));
        *m_mod2 = (int *)realloc(*m_mod2, new_count * sizeof(int));
        *value = (double *)realloc(*value, new_count * sizeof(double));
        *m_mod1 = (char *)realloc(*m_mod1, new_count * sizeof(char));
        *m_type = (char *)realloc(*m_type, new_count * 2 * sizeof(char));

        printf("Vymazalo sa: %d zaznamov!\n", *record_count - new_count);
        *record_count = new_count;
    }
    else
    {
        printf("Polia nie su vytvorene.\n");
    }
}

void o_command(FILE **fr, int v, int n, int *m_mod2, char *m_mod1, char *m_type, double *value, int *time, int *date, int *record_count)
{
    if (!v)
    {
        printf("Neotvoreny subor.\n");
    }
    else
    {
        int i_m_mod2;
        char i_m_mod1, i_m_type[2];
        scanf("%c%d %c%c", &i_m_mod1, &i_m_mod2, &i_m_type[0], &i_m_type[1]);
        getchar();

        if (n)
        {
            double sort_value[*record_count];
            int sort_date[*record_count], sort_time[*record_count], counter = 0;

            for (int i = 0; i < *record_count; i++)
            {
                if (*(m_mod1 + i) == i_m_mod1 && *(m_mod2 + i) == i_m_mod2 && *(m_type + i * 2) == i_m_type[0] && *(m_type + i * 2 + 1) == i_m_type[1])
                {
                    sort_value[counter] = *(value + i);
                    sort_date[counter] = *(date + i);
                    sort_time[counter] = *(time + i);
                    counter++;
                }
            }

            sort_value_by_date(sort_value, sort_date, sort_time, counter);

            for (int i = 0; i < counter; i++)
            {
                printf("%c%d\t%c%c\t%d\t%04d\t%f\n", i_m_mod1, i_m_mod2, i_m_type[0], i_m_type[1], *(sort_date + i), *(sort_time + i), *(sort_value + i));
            }
        }
        else
        {
            char z;
            while ((z = getc(*fr)) != EOF)
            {
                if (z == '\n')
                    (*record_count)++;
            }
            *record_count = ++(*record_count) / 7;
            rewind(*fr);

            double sort_value[*record_count];
            int sort_date[*record_count], sort_time[*record_count], counter = 0;

            long long h_id;
            int h_time, h_date, h_m_mod2;
            double h_value;
            char h_m_mod1, h_m_type[2];

            while (fscanf(*fr, "%lld", &h_id) != EOF)
            {
                fscanf(*fr, "%lld\n", &h_id);
                fscanf(*fr, "%c%d\n", &h_m_mod1, &h_m_mod2);
                fscanf(*fr, "%c%c\n", &h_m_type[0], &h_m_type[1]);
                fscanf(*fr, "%lf\n", &h_value);
                fscanf(*fr, "%d\n", &h_time);
                fscanf(*fr, "%d\n\n", &h_date);

                if (h_m_mod1 == i_m_mod1 && h_m_mod2 == i_m_mod2 && h_m_type[0] == i_m_type[0] && h_m_type[1] == i_m_type[1])
                {
                    sort_value[counter] = h_value;
                    sort_date[counter] = h_date;
                    sort_time[counter] = h_time;
                    counter++;
                }
            }
            rewind(*fr);

            sort_value_by_date(sort_value, sort_date, sort_time, counter);

            for (int i = 0; i < counter; i++)
            {
                printf("%c%d\t%c%c\t%d\t%04d\t%f\n", i_m_mod1, i_m_mod2, i_m_type[0], i_m_type[1], *(sort_date + i), *(sort_time + i), *(sort_value + i));
            }
        }
    }
}

int main()
{
    char command;
    int v = 0, n = 0, record_count = 0;
    FILE *fr;

    long long *id = NULL;
    int *time = NULL, *date = NULL, *m_mod2 = NULL;
    double *value = NULL;
    char *m_mod1 = NULL, *m_type = NULL;

    while (command != 'k')
    {
        printf("Input command: ");
        command = getchar();
        getchar();
        switch (command)
        {
        case 'v':
            v_command(&fr, &v, n, id, m_mod2, m_mod1, m_type, value, time, date, record_count);
            break;
        case 'o':
            o_command(&fr, v, n, m_mod2, m_mod1, m_type, value, time, date, &record_count);
            break;
        case 'n':
            n_command(&fr, &v, &n, &id, &m_mod2, &m_mod1, &m_type, &value, &time, &date, &record_count);
            break;
        case 'c':
            c_command(&fr, v);
            break;
        case 's':
            s_command(n, m_mod2, m_mod1, m_type, value, time, date, record_count);
            break;
        case 'h':
            h_command(n, m_type, value, record_count);
            break;
        case 'r':
            r_command(n, time, record_count);
            break;
        case 'z':
            z_command(n, &id, &m_mod2, &m_mod1, &m_type, &value, &time, &date, &record_count);
            break;
        case 'k':
            if (n)
            {
                for (int i = 0; i < record_count; i++)
                {
                    *(id + i) = 0;
                }
                free(id);
                id = NULL;
                free(m_mod2);
                m_mod2 = NULL;
                free(m_mod1);
                m_mod1 = NULL;
                free(m_type);
                m_type = NULL;
                free(value);
                value = NULL;
                free(time);
                time = NULL;
                free(date);
                date = NULL;
            }
            if (v)
            {
                fclose(fr);
            }
            break;
        default:
            break;
        }
    }

    return 0;
}