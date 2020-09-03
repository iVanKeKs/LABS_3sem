#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "List.h"

//   №1
//Кратные числа введеному
void Multiplicity()
{
    int number;
    scanf("%d", &number);



    for(int output = number; output < 100; output+=number)
    {
        printf("%d ", output);
    }
}


//   №2
//Состваное число или простое
void NumberTest()
{
    int number;

    scanf("%d", &number);

    while(number)
    {
        if(number == 1)
        {
            printf("Единица это единица");
            continue;
        }

        for(int i = number-1; i>1; --i)
        {
            if(number % i == 0)
            {
                printf("Число составное\n");
                number = -1;
                break;
            }
        }
        if(number != -1)
        {
            printf("Число простое\n");
        }

        scanf("%d", &number);
    }
}


//   №3
//Перезапись файла без цифр
void Rewriting()
{
    FILE *fin, *fout;
    char c;

    if( !((fin = fopen("C:\\Users\\iVan\\Documents\\0_0\\in.txt", "r")) && (fout = fopen("C:\\Users\\iVan\\Documents\\0_0\\out.txt", "w"))) )
    {
        printf("Не удалось открыть файлы\n");
        exit(-1);
    }

    c = fgetc(fin);
    while(!feof(fin))
    {
        if('0' > c || c > '9')
        {
            fprintf(fout, "%c", c);
        }
        c = fgetc(fin);
    }

    fclose(fin);
    fclose(fout);
}


//   №4
//Решение квадратного уравнения
void QuadraticEquation()
{
    int a, b, c;

    int e = scanf("%d %d %d", &a, &b, &c);

    if(a == 0)
    {
        printf("Коэффицент \"a\" не может бытья равен 0\n");
        exit(-1);
    }

    int D = b*b - 4*a*c;

    if(D < 0)
    {
        printf("Вещественных корнец нет\n");
    }

    if(D == 0)
    {
        printf("X = %f\n", (float)(-b)/2/a);
    }

    if(D > 0)
    {
        printf("X1 = %f\nX2 = %f\n", ((-b)+sqrtf(D))/2/a, ((-b)*sqrtf(D))/2/a);
    }
}


//   №5
//Определение кратность первого второму
void MultiTwo()
{
    int a, b;

    scanf("%d %d", &a, &b);

    if(a%b == 0)
    {
        printf("Число %d кратно число %d", a, b);
    }
    else
    {
        printf("Число %d НЕ кратно числу %d", a, b);
    }
}


//   №6
//Разделяет введенное число на цифры
void SplitNumber()
{
    char number[7];
    char *ptr = number;
    scanf("%s", number);

    while(*ptr != '\0')
    {
        printf("%c ", *ptr);
        ++ptr;
    }
}


//   №7
//Возведение чисел в степень
void NumberPow()
{
    int power;
    //При вводе больше 10 вызывает переполнение
    scanf("%d", &power);

    for(int number = 1; number < 11; ++number)
    {
        for(int i = 0; i<power; ++i)
        {
            printf("%d\n", (int)pow(number, i));
        }
    }
}


//   №8
//Могут ли введенные числа быть сторонами прямоугольного треугольника
void TriangleNumber()
{
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    if((a*a + b*b - c*c == 0) ||
       (b*b + c*c - a*a == 0) ||
       (a*a + c*c - b*b == 0))
    {
        printf("Введенные числа могут быть сторонами прямого треугольника");
    }
    else
    {
        printf("Введенные числа НЕ могут быть сторонами прямого треугольника");
    }
}


//   №9
//Суммирование алг последовательности
void SummSequence()
{
    int number;
    int summ = 0;

    scanf("%d", &number);

    printf("%d", ((1+number)/2*number));
}


//   №10
//Факториал
void Factorial()
{
    int number;
    int Fac = 1;

    scanf("%d", &number);

    for(int i = 1; i <= number; ++i)
    {
        Fac *= i;
    }
    printf("%d\n", Fac);
}


//   №11
//Подсчет колличества букв в строке
void CountOfLiters(char *fileIn)
{
    FILE *fin, *fout;

    if(!(fin = fopen(fileIn, "r")) ||
       !(fout = fopen("out2.txt", "w")))
    {
        printf("Не удалось открыть папку\n");
        exit(-1);
    }

    char litter;
    int numberOfLitter = 0;
    while(!feof(fin))
    {
	if((litter = fgetc(fin)) == '\n')
	{
	    fprintf(fout, "%d\n", numberOfLitter);
	    numberOfLitter = 0;
        continue;
	}

	if((litter >= 65 && litter <= 90) ||
	   (litter >= 97 && litter <= 122))
	{
	    numberOfLitter += 1;
	}

    }
    fclose(fin);
    fclose(fout);
}


//   №12
//Проверка на колличество не букв, цифр и пробела
void CountOfSymbols(char *fileIn)
{
    FILE *fin, *fout;
    if(!(fin = fopen(fileIn, "r")) ||
       !(fout = fopen("out3.txt", "w")))
    {
        printf("Не удалось ктрыть файл");
        exit(-1);
    }

    char litter;
    int numberOfLitter = 0;

    while(!feof(fin))
    {
        if((litter = fgetc(fin)) == '\n')
	    {
	        fprintf(fout, "%d\n", ++numberOfLitter);
	        numberOfLitter = 0;
            continue;
	    }

	    if(((litter < 48) ||
	        (litter > 57 && litter < 65) ||
	        (litter > 90 && litter < 97) ||
	        (litter > 122)) &&
	         litter != ' ')
	    {
	        numberOfLitter += 1;
	    }
    }

    fclose(fin);
    fclose(fout);
}

//   №13
//Перекручивание столбцов
void Stolbs()
{
    const int size = 80;
    char buff1[size], buff2[size], buff3[size];
    int i = 0;
    char *pbuff = buff1;

    char c, c_ = (char)NULL;

    FILE *fin, *fout;
    if(!(fin = fopen("C:\\Users\\iVan\\Documents\\0_0\\in.txt", "r")))
    {
        printf("Не удалось открыть файл для чтения");
        exit(-1);
    }

    if(!(fout = fopen("C:\\Users\\iVan\\Documents\\0_0\\out.txt", "w")))
    {
        printf("Не удалось открыть файл для записи");
        exit(-1);
    }

    while(!feof(fin))
    {
        c = fgetc(fin);

        //Слово закончилась
        if((c_ == ' ') || (c_ == '\n'))
        {
            i++;
            i %= 3;
            *pbuff = '\0';
            switch(i)
            {
                //Если текущий 3 столбец
                case 0:
                {
                    pbuff = buff1;
                    fprintf(fout, "%s %s %s\n", buff3, buff1, buff2);
                    break;
                }

                //Если текущий 1 столбец
                case 1:
                {
                    pbuff = buff2;
                    break;
                }

                //Если текущий 2 столбец
                case 2:
                {
                    pbuff = buff3;
                    break;
                }
            }

            //Пропуск ненужных пробелов
            while(c == ' ')
            {
                c = fgetc(fin);
            }
        }

        //Запись слова
        if (c != ' ' && c != '\n' && c != '\r')
        {
            *pbuff++ = c;
        }

        c_ = c;
    }
    fclose(fout);
    fclose(fin);
}


//   №14
//Замена не цифр АСКИИ кодом
void ChangerNonNumber(char *fileIn)
{
    FILE *fin, *fout;

    if(!(fin = fopen(fileIn, "r")) ||
       !(fout = fopen("out3.txt", "w")))
    {
        printf("Не удалось открыть файл");
        exit(-1);
    }

    char litter;
    while(!feof(fin))
    {
        litter = fgetc(fin);

        if(litter >= 48 && litter <= 57)
        {
            fprintf(fout, "%c", litter);
        }
        else
        {
            fprintf(fout, "%d", litter);
        }
    }

    fclose(fin);
    fclose(fout);

}


//   №15
//Скрещивание двух файлов в шахматном порядке
void lab15()
{
    FILE *fin1, *fin2, *fout;

    if(!(fin1 = fopen("in1.txt", "r")) ||
       !(fin2 = fopen("in2.txt", "r")) ||
       !(fout = fopen("out2.txt", "w")))
    {
        printf("Не удалось открыть файл");
        exit(-1);
    }

    char buff1,
         buff2;

    while(!(feof(fin1) || feof(fin2)))
    {
        // Чтение из первого файла
        buff1 = fgetc(fin1);
        while(!isspace(buff1) && !feof(fin1))
        {
            fprintf(fout, "%c", buff1);
            buff1 = fgetc(fin1);
        }
        fprintf(fout, " ");

        // Чтение из второго файла
        buff2 = fgetc(fin2);
        while(!isspace(buff2) && !feof(fin2))
        {
            fprintf(fout, "%c", buff2);
            buff2 = fgetc(fin2);
        }
        fprintf(fout, " ");
    }

    fclose(fin1);
    fclose(fin2);
    fclose(fout);
}

//   №17
//Схема Горнера
int Gorner(char *sourceNumber, int countSystem)
{
    char *b = sourceNumber;
    int result = 0;

    while(*b)
    {                                  /*Если число        АSCII-код 0 */
        result = result * countSystem + (isdigit(*b) ? (*b++ - '0') : (toupper(*b++) - 'A' + 10));
    }

    //printf("%s -> %d | cc %d", sourceNumber, result, countSystem);

    return result;
}

//   №17
// Обратная схема Горнера
void GornerReverce(int sourceNumber, int countSystem)
{
    const char size = 100;

    int buffNumber = sourceNumber,
        sizeOfResult = 0;
    char letterBuff;
    char outputBuf[size];
    char *b = outputBuf + size - 1;
    b--;

    outputBuf[size-1] = '\0';

    while(buffNumber)
    {
        if((letterBuff = buffNumber % countSystem) < 10)
        {//               ASCII код 0
            *b-- = letterBuff + '0';
        }
        else
        {//                    ASCII код А
            *b-- = letterBuff - 10 + 'A';
        }
        buffNumber /= countSystem;
        ++sizeOfResult;
    }

    printf("%s\n", ++b);
}

//   №19
// Скрещивание массивов
void lab19()
{
    int sizeFirstMass,
        sizeSecondMass;

    scanf("%d %d", &sizeFirstMass, &sizeSecondMass);

    if(sizeFirstMass == 0 || sizeSecondMass == 0)
    {
        printf("Одно из значений введено неправильно\n");
        return;
    }

    int *firstMass = (int *)malloc(sizeof(int)*sizeFirstMass),
        *secondMass = (int *)malloc(sizeof(int)*sizeSecondMass),
        *outMass = (int *)malloc(sizeof(int)*sizeFirstMass);

    srand(time(NULL));
    printf("Mass 1: ");
    for(int i = 0; i < sizeFirstMass; ++i)
    {
        firstMass[i] = rand() % 50;
        printf("%d ", firstMass[i]);
    }
    printf("\nMass 2: ");

    for(int i = 0; i < sizeSecondMass; ++i)
    {
        secondMass[i] = rand() % 50;
        printf("%d ", secondMass[i]);
    }
    printf("\nOut Mass: ");

    int *pMass = secondMass;
    for(int i = 0; i < sizeFirstMass; ++i)
    {
        outMass[i] = firstMass[i] + *pMass;
        printf("%d ", outMass[i]);
        if(i < sizeSecondMass-1)
        {
            ++pMass;
        }
    }

    free(firstMass);
    free(secondMass);
    free(outMass);
}

//   №20
// Максимальное введеное число в 9, 18, 27 и 36 СС
void lab20()
{
    int countSystem;
    scanf("%d", &countSystem);
    if(countSystem < 2 || countSystem > 36)
    {
        printf("Не верно введена система счисления");
        return;
    }

    char buff[BUFSIZ],
         *pbuff = buff,
         literBuff;

    // Максимально число в 10 системе счяисления
    int max = -1,
        numberBuff;

    // Запись чисел
    while((literBuff = getchar()) != EOF)
    {

        // Разделительный символ
        if(isspace(literBuff))
        {
            *pbuff = '\0';
            pbuff = buff;
            // Если слово STOP
            if(!(strncmp(buff, "Stop", 4)))
            {
                break;
            }

            numberBuff = Gorner(buff, countSystem);
            if(numberBuff > max)
            {
                max = numberBuff;
            }
            continue;
        }

        *pbuff = literBuff;
        ++pbuff;
    }

    // Перевод максимального числа
    printf("Максимальное число: %d\n", max);
    printf("В 9 системе счисления: ");
    GornerReverce(max, 9);
    printf("В 18 системе счисления: ");
    GornerReverce(max, 18);
    printf("В 27 системе счисления: ");
    GornerReverce(max, 27);
    printf("В 36 системе счисления: ");
    GornerReverce(max, 36);
}

int main(int argc, char **argv)
{
    lab19();
    return 0;
}
