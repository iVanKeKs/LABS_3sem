//
// Created by iVan on 07.10.2019.
//


//Проверка на выпуклость многноугольника


#include "Tasks.h"

//Уравнение прямой
int StraightLineEquation1(double x1, double y1,
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


void lab13_2(int n, ...)
{
    //Треугольник всегда выпуклый
    if(n == 3)
    {
        printf("Выпуклый");
        return;
    }

    double massOfPoints1[n][2];

    va_list argc1;
    va_start(argc1, n);

    //Запись точек многоугольника в массив
    for(int i = 0; i<n; ++i)
    {
        for(int j = 0; j<2; ++j)
        {
            massOfPoints1[i][j] = va_arg(argc1, double);
        }
    }
    va_end(argc1);

    //Прохождение по массиву точек и составление уравнения прямой
    for(int i = 0; i<n; ++i)
    {
        //Проход по точкам не входящем в прямую
        for(int j = 0; j<n; ++j)
        {
            //Если не точки исследуемой прямой
            if(j != i && j != (i+1)%n)
            {                            //Первая точка прямой
                if(StraightLineEquation1(massOfPoints1[i][0], massOfPoints1[i][1],
                                         //Вторая точка прямой
                                         massOfPoints1[(i + 1) % n][0], massOfPoints1[(i + 1) % n][1],
                                         //Точка лежащая вне прямой сверху/снизу
                                         massOfPoints1[j][0], massOfPoints1[j][1]) == 0)

                //Точка оказалась с другой стороны прямой
                {
                    printf("Невыпуклый\n");
                    return;
                }
            }
        }
    }

    printf("Выпуклый");
}