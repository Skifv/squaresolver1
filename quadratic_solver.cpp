/* quadratic_solver.cpp -- calculates the real roots
of a quadratic equation of the form ax^2+bx+c = 0 */

/* quadratic_solver.cpp -- считает действительные корни
квадратного уравнения вида ax^2+bx+c = 0 */

#include <stdio.h>
#include <math.h>

#define DIFFERENCE 0.000000000001                                  // needed to compare a variable of double type with 0
#define EXIT 400                                                   // needed to check if the output was displayed before the discriminant scenarios

void greetings(int language);                                      // displays the welcome message
int what_the_accuracy_of_answers(int language);                    // determines how accurately the answers will be displayed
double coefficient_request(char variable_name, int language);      // assigns values to the coefficients

// functions of checking all cases when a == 0
// функции, которые проверяют все случаи, когда a == 0
int zero_zero_zero(double a, double b, double c, int language);
int zero_zero_NOTzero(double a, double b, double c, int language);
int zero_NOTzero_zero(double a, double b, double c, int language);
int zero_NOTzero_NOTzero(double a, double b, double c, int accuracy_of_answers, int language);

double calculate_discriminant(double a, double b, double c);

// different scenarios with discriminants
// различные сценарии с дискриминантом
int D_is_less_than_zero(double a, double b, double c, double D, int x1, int x2, int x3, int x4, int language);
int D_equals_zero(double a, double b, double c, double D, int accuracy_of_answers, int x1, int x2, int x3, int x4, int language);
int D_is_greater_than_zero(double a, double b, double c, double D, int accuracy_of_answers, int x1, int x2, int x3, int x4, int language);

int choose_language(void);                                         // language selection (выбор языка)

void clear(void);                                                  // clears the input buffer (очищает буфер ввода)

int main(void)
{
    double a = 0;                                                  // coefficients (коэффициенты)
    double b = 0;
    double c = 0;

    double D = 0;                                                  // discriminant (дискриминант)

    int accuracy_of_answers = 0;                                   // number of digits after the decimal point (количество знаков после запятой)

    // these variables are needed to check if the output was displayed before the discriminant scenarios
    // эти переменные нужны, чтобы проверить, был ли вывод ответа до начала сценариев с дискриминантом
    int x1 = 0;
    int x2 = 0;
    int x3 = 0;
    int x4 = 0;

    int language = choose_language();                              // language selection (выбор языка)

    greetings(language);

    accuracy_of_answers = what_the_accuracy_of_answers(language);  // user inputs the accuracy of the answers (ползователь вводит точность ответов)

    switch(language)
    {
    case 1:
        printf("Now enter the coefficients:\n");
        break;
    case 2:
        printf("Теперь введите коэффициенты:\n");
        break;
    default:
        printf("Выбран некорректный язык.\n");
        break;
    }

    while(1)
    {
        a = coefficient_request('a', language);                    // user enters coefficients a, b, c (пользователь вводит коэффициенты a, b, c)
        b = coefficient_request('b', language);
        c = coefficient_request('c', language);

        x1 = zero_zero_zero(a, b, c, language);                    // checking all cases when a == 0 (проверка всех случаев, когда a == 0)
        x2 = zero_zero_NOTzero(a, b, c, language);
        x3 = zero_NOTzero_zero(a, b, c, language);
        x4 = zero_NOTzero_NOTzero(a, b, c, accuracy_of_answers, language);

        D = calculate_discriminant(a, b, c);

        // different discriminant scenarios
        // разные сценарии с дискриминантом
        D_is_less_than_zero(a, b, c, D, x1, x2, x3, x4, language);
        D_equals_zero(a, b, c, D, accuracy_of_answers, x1, x2, x3, x4, language);
        D_is_greater_than_zero(a, b, c, D, accuracy_of_answers, x1, x2, x3, x4, language);

        switch(language)
        {
        case 1:
            printf("\n\nLet's get on with it! Enter the new coefficients (or press 'q' to exit):\n");
            break;
        case 2:
            printf("\n\nДавайте продолжим! Введите новые коэффициенты (или нажмите 'q', чтобы выйти):\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
    }

    return 0;
}

// function that displays the welcome message
// функция, которая выводит приветствие
void greetings(int language)
{
    switch(language)
    {
    case 1:
        printf("\n---- This program will calculate the real roots "
               "of a quadratic equation of the form 'ax^2+bx+c = 0' ----\n");
        printf("\nThe coefficients 'a', 'b', and 'c' are needed for the calculation.\n");
        printf("P.S: If the coefficients are not integers, "
               "write the integer and fractional parts through the dot.\n");
        printf("P.P.S: To close the program, enter 'q' "
               "(or any other character that is not a number).\n");
        printf("Let's start!\n\n");
        break;
    case 2:
        printf("\n---- Эта программа вычислит действительные корни "
               "квадратного уравнения вида 'ax^2+bx+c = 0' ----\n");
        printf("\nДля расчёта необходимы коэффициенты 'a', 'b' и 'c'.\n");
        printf("P.S: Если коэффициенты представляют собой десятичные дроби, "
               "введите целую и дробную части, разделяя их точкой (не запятой).\n");
        printf("P.P.S: Чтобы выйти, нажмите 'q' "
               "(или любой другой символ, не являющийся числом).\n");
        printf("Давайте начнем!\n\n");
        break;
    default:
        printf("Выбран некорректный язык.\n");
        break;
    }
}

// the accuracy with which the roots of the equation will be output
// точность, с которой будут выводиться корни уравнения
int what_the_accuracy_of_answers(int language)
{
    int accuracy_of_answers = 0;   // returned value (возвращаемое значение)
    int status = 0;                // variable to check if the input is correct (переменная для проверки правильности ввода)

    switch(language)
    {
    case 1:
        printf("With what accuracy would you like to receive answers?\n");
        printf("        (enter the number of decimal places)\n");
        break;
    case 2:
        printf("С какой точностью вы бы хотели получать ответы?\n");
        printf("  (введите количество знаков после запятой)\n");
        break;
    default:
        printf("Выбран некорректный язык.\n");
        break;
    }
    status = scanf("%d", &accuracy_of_answers);
    clear();
    if (status != 1)
    {
        switch(language)
        {
        case 1:
            printf("Goodbye, UwU <3\n");
            break;
        case 2:
            printf("Пока, котик UwU <3\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        exit(1);
    }
    return accuracy_of_answers;
}

// function that assigns values of type double to coefficients
// функция, присваивающая знаения типа double коэффициентам
double coefficient_request(char variable_name, int language)
{
    double variable_value = 0;     // returned value (возвращаемое значение)

    int status = 0;                // variable to check if the input is correct (переменная для проверки правильности ввода)

    printf("%c = ", variable_name);
    status = scanf("%lf", &variable_value);
    clear();
    if (status != 1)
    {
        switch(language)
        {
        case 1:
            printf("Goodbye, UwU <3\n");
            break;
        case 2:
            printf("Пока, котик UwU <3\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        exit(1);
    }

    return variable_value;
}

// if all coefficients are equal to 0
// если все коэффициенты равны нулю
int zero_zero_zero(double a, double b, double c, int language)
{
    if (fabs(a) < DIFFERENCE && fabs(b) < DIFFERENCE && fabs(c) < DIFFERENCE)
    {
        printf("---- %.1f*x^2 + %.1f*x + %.1f = 0 ----\n", a, b, c);
        switch(language)
        {
        case 1:
            printf("The root of the equation is any number!\n");
            break;
        case 2:
            printf("Корнем уравнения является любое число!\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        return EXIT;
    }
    return 0;
}

// if a == 0, b == 0, c != 0
int zero_zero_NOTzero(double a, double b, double c, int language)
{
    if (fabs(a) < DIFFERENCE && fabs(b) < DIFFERENCE && fabs(c) > DIFFERENCE)
    {
        printf("---- %.1f*x^2 + %.1f*x + %.1f = 0 ----\n", a, b, c);
        switch(language)
        {
        case 1:
            printf("The equation has no solutions.\n");
            break;
        case 2:
            printf("Уравнение не имеет решений.\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        return EXIT;
    }
    return 0;
}

// if a == 0, b != 0, c == 0
int zero_NOTzero_zero(double a, double b, double c, int language)
{
    if (fabs(a) < DIFFERENCE && fabs(b) > DIFFERENCE && fabs(c) < DIFFERENCE)
    {
        printf("---- %.1f*x^2 + %.1f*x + %.1f = 0 ----\n", a, b, c);
        switch(language)
        {
        case 1:
            printf("The equation has only one root!\n");
            break;
        case 2:
            printf("Уравнение имеет единственное решение!\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        printf("x = 0.\n");
        return EXIT;
    }
    return 0;
}

// if a == 0, b != 0, c != 0
int zero_NOTzero_NOTzero(double a, double b, double c, int accuracy_of_answers, int language)
{
    if (fabs(a) < DIFFERENCE && fabs(b) > DIFFERENCE && fabs(c) > DIFFERENCE)
    {
        double root = -c / b;
        printf("---- %.1f*x^2 + %.1f*x + %.1f = 0 ----\n", a, b, c);
        switch(language)
        case 1:
        {
            printf("The equation has only one root!\n");
            break;
        case 2:
            printf("Уравнение имеет единственное решение!\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        printf("x = %.*f.\n", accuracy_of_answers, root);
        return EXIT;
    }
    return 0;
}

// calculates the discriminant
// считает дискриминант
double calculate_discriminant(double a, double b, double c)
{
    return b*b - 4*a*c;
}

// no solutions when the discriminant is less than zero
// нет решений, когда дискриминант меньше нуля
int D_is_less_than_zero(double a, double b, double c, double D, int x1, int x2, int x3, int x4, int language)
{
    if (D < 0.0 && x1 != EXIT && x2 != EXIT && x3 != EXIT && x4 != EXIT)
    {
        printf("---- %.1f*x^2 + %.1f*x + %.1f = 0 ----\n", a, b, c);
        switch(language)
        {
        case 1:
            printf("The equation has no real solutions.\n");
            break;
        case 2:
            printf("Уравнение не имеет действительных решений.\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
    }
    return 0;
}

// discriminant equals 0
// дискриминант равен нулю
int D_equals_zero(double a, double b, double c, double D, int accuracy_of_answers, int x1, int x2, int x3, int x4, int language)
{
    if (fabs(D) < DIFFERENCE && x1 != EXIT && x2 != EXIT && x3 != EXIT && x4 != EXIT)
    {
        double root = 0;
        root = -b/(2*a);
        printf("---- %.1f*x^2 + %.1f*x + %.1f = 0 ----\n", a, b, c);
        switch(language)
        {
        case 1:
            printf("The equation has only one root!\n");
            break;
        case 2:
            printf("Уравнение имеет единственное решение!\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        printf("x = %.*f.\n", accuracy_of_answers, root);
    }
    return 0;
}

// discriminant is greater than 0
// дискриминант больше нуля
int D_is_greater_than_zero(double a, double b, double c, double D, int accuracy_of_answers, int x1, int x2, int x3, int x4, int language)
{
    if (D > 0.0 && x1 != EXIT && x2 != EXIT && x3 != EXIT && x4 != EXIT)
    {
        double first_root = (-b - sqrt(D)) / (2*a);
        double second_root = (-b + sqrt(D)) / (2*a);
        printf("---- %.1f*x^2 + %.1f*x + %.1f = 0 ----\n", a, b, c);
        switch(language)
        {
        case 1:
            printf("The equation has two roots!\n");
            break;
        case 2:
            printf("Уравнение имеет два решения!\n");
            break;
        default:
            printf("Выбран некорректный язык.\n");
            break;
        }
        printf("x1 = %.*f\nx2 = %.*f\n", accuracy_of_answers, first_root, accuracy_of_answers, second_root);
    }
    return 0;
}

// language selection
// выбор языка
int choose_language(void)
{
    int language = 0;          // returned value (возвращаемое значение)

    int status = 0;            // variable to check if the input is correct (переменная для проверки правильности ввода)

    printf("Select your preferred language (выберите продпочитаемый язык).\n");
    printf("1. English (английский).\n");
    printf("2. Russian (русский).\n");
    printf("Enter a number (введите номер):\n");
    status = scanf("%d", &language);
    clear();
    while ((language != 1 && language != 2) || status != 1)
    {
        printf("You've entered something wrong... Let's try again.\n");
        printf("(Вы ввели что-то не то... Давайте попробуем еще раз.)\n");
        printf("Enter a number (введите номер):\n");
        status = scanf("%d", &language);
        clear();
    }

    return language;
}

// function that clears the input buffer to avoid problems with infinite reading of the value
// функция, очищающая входной буфер, чтобы избежать проблем с бесконечным считыванием значения переменных
void clear(void)
{
    while (getchar() != '\n');
}
