#include <stdio.h>
#include <math.h>

const int INFINITE_ROOTS = 8888;
const double EPSILON = 0.0000001;
const int EXIT = 123123;

const int NO_ROOTS = 0;
const int ONE_ROOT = 1;
const int TWO_ROOTS = 2;


int input_coeffs(double* a, double* b, double* c);
int get_coeff(char name_coeff, double *coeff);
int solve_square(double a, double b, double c, double* x1, double* x2);
void print_roots(double x1, double x2, int n_roots);
double calculate_discriminant(double a, double b, double c);
int solve_linear(double b, double c, double* x1, double* x2);

bool equals_zero(double number);
bool not_equals_zero(double number);
bool less_zero(double number);
bool greater_zero(double number);

void clear(void);


int main(void)
{
    double a = 0.0, b = 0.0, c = 0.0;
    input_coeffs(&a, &b, &c);

    double x1 = 0.0, x2 = 0.0;
    int n_roots = solve_square(a, b, c, &x1, &x2);

    print_roots(x1, x2, n_roots);

    return 0;
}


int input_coeffs(double* a, double* b, double* c)
{
    printf("Введите коэффициенты\n");
    get_coeff('a', a);
    get_coeff('b', b);
    get_coeff('c', c);

    return 0;
}

int get_coeff(char name_coeff, double *coeff)
{
    double number;
    char buffer[100] = "";

    while (1) {
        printf("%c = ", name_coeff);
        fgets(buffer, sizeof(buffer), stdin);

        char *endptr;
        number = strtod(buffer, &endptr);

        if (endptr == buffer || *endptr != '\n')
        {
            printf("Ошибка ввода. Введите корректное число.\n");
        }
        else
        {
            break;
        }
    }

    *coeff = number;

    return 0;
}

int solve_square(double a, double b, double c,
                 double* x1, double* x2)
{
    if (equals_zero(a))
    {
        return solve_linear(b, c, x1, x2);
    }

    double d = calculate_discriminant(a, b, c);

    if (less_zero(d))
    {
        return NO_ROOTS;
    }
    else if (equals_zero(d))
    {
        *x1 = *x2 = -b / (2*a);
        return ONE_ROOT;
    }
    else
    {
        *x1 = (-b - sqrt(d)) / (2*a);
        *x2 = (-b + sqrt(d)) / (2*a);
        return TWO_ROOTS;
    }

    return 0;
}

void print_roots(double x1, double x2, int n_roots)
{
    switch(n_roots)
    {
    case NO_ROOTS:
        printf("Нет корней\n");
        break;
    case ONE_ROOT:
        printf("x = %g\n", x1);
        break;
    case TWO_ROOTS:
        printf("x1 = %g\n", x1);
        printf("x2 = %g\n", x2);
        break;
    case INFINITE_ROOTS:
        printf("Бесконечное количество корней\n");
        break;
    default:
        break;
    }
}

double calculate_discriminant(double a, double b, double c)
{
    return b*b - 4*a*c;
}

bool equals_zero(double number)
{
    return fabs(number) < EPSILON;
}

bool not_equals_zero(double number)
{
    return fabs(number) > EPSILON;
}

bool less_zero(double number)
{
    return number < -EPSILON;
}

bool greater_zero(double number)
{
    return number > EPSILON;
}

int solve_linear(double b, double c, double* x1, double* x2)
{
    if (equals_zero(b))
    {
        if (equals_zero(c))
        {
            return INFINITE_ROOTS;
        }
        else
        {
            return NO_ROOTS;
        }
    }
    else
    {
        if (equals_zero(c))
        {
            *x1 = *x2 = 0;
            return ONE_ROOT;
        }
        else
        {
            *x1 = *x2 = -c / b;
            return ONE_ROOT;
        }
    }
}

void clear(void)
{
    while (getchar() != '\n');
}

