//
// Created by iVan on 07.10.2019.
//


//Проверка на выпуклость многноугольника


#include "Tasks.h"

//Уравнение прямой
int StraightLineEquation(double x1, double y1,
                          double x2, double y2,
                          double x3, double y3)
{
    //Уравнение прямой
    double res = (double)(x3-x1)*(y2-y1) - (double)(y3-y1)*(x2-x1);
    if(res > 0)
    {
        //Результат больше 0
        // Точка лежит выше прямой
        return 0;
    }
    else
    {
        //Результат больше 1
        // Точка лежит ниже прямой
        return 1;
    }
}

//Проверка знака всех точек не лежащих на текущей прямой
int TestPoints(int n, const int *mass)
{
    /*
    switch(mass[0])
    {
        //Проверяем все ли выше прямой
        case (0):
        {
            for(int i = 1; i<n; ++i)
            {
                if(mass[i] == 1)
                {
                    //Возвращает флаг 0 - наличие точки ниже прямой
                    return 0;
                }
            }
            break;
        }

        //Проверяем все ли выше прямой
        case (1):
        {
            for(int i = 1; i<n; ++i)
            {
                if(mass[i] == 0)
                {
                    //Возвращает флаг 0 - наличие точки выше прямой
                    return 0;
                }
            }
            break;
        }
    }
     */

    for(int i = 0; i<n; ++i)
    {
        if(mass[0] == 0)
        {
            return 0;
        }
    }

    //Не нулевой флаг - все точки сохраняют знак
    return 1;
}


void lab13_1(int n, ...)
{
    //Треугольник всегда выпуклый
    if(n == 3)
    {
        printf("Выпуклый");
        return;
    }

    double massOfPoints[n][2];

    va_list argc;
    va_start(argc, n);

    //Запись точек многоугольника в массив
    for(int i = 0; i<n; ++i)
    {
        for(int j = 0; j<2; ++j)
        {
            massOfPoints[i][j] = va_arg(argc, double);
        }
    }
    va_end(argc);

    //Массив результатов уравнения прямой
    int massOfResults[BUFSIZ];
    int *pmass = massOfResults;

    //Прохождение по массиву точек и составление уравнения прямой
    for(int i = 0; i<n; ++i)
    {
        //Проход по точкам не входящем в прямую
        for(int j = 0; j<n; ++j)
        {
            //Если не точки исследуемой прямой
            if(j != i && j != (i+1)%n)
            {                                           //Первая точка прямой
                *pmass = StraightLineEquation(massOfPoints[i][0], massOfPoints[i][1],
                                              //Вторая точка прямой
                                              massOfPoints[(i + 1) % n][0], massOfPoints[(i + 1) % n][1],
                                              //Точка лежащая вне прямой сверху/снизу
                                              massOfPoints[j][0], massOfPoints[j][1]);
                printf("%d\n", *pmass);
                pmass++;
            }
        }
        printf("\n");

        //Выходим из метода если найдена хотябы одна точка не сохраняющая знак в ряду других
        if(TestPoints(n-2, massOfResults) == 0)
        {
            printf("Невыпуклый\n");
            return;
        }

    }

    printf("Выпуклый");
}