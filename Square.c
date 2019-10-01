#include <stdio.h>
#include <math.h>
#include <assert.h>

#define INF 100\
//const double  INF = 1000 ;
const double  EPS = 1e-17 ;


int Comp(double a, double b);//опыт1 experiment2

void SolveLine(double a, double b, double *ptr_x, int *ptr_k);

void SolveSquare(double a, double b, double c, double *ptr_x1, double *ptr_x2, int *ptr_k);

void InputCoeff(double *ptr_a, double *ptr_b, double *ptr_c);

int main () {
    int k = NAN;
    double x1 = NAN , x2 = NAN ;
    double a = NAN, b = NAN, c = NAN;
    InputCoeff(&a, &b, &c);// assert 
    assert (isnan(a) == 0 && isnan(b) == 0 && isnan(c) == 0) ;
    SolveSquare(a, b, c, &x1, &x2, &k);
    switch(k) {
        case 0 :
            printf("There are no solutions") ;
            break ;
        case 1 :
            printf("x=%lg", x1) ;
            break ;
        case 2 :
            printf("x1=%lg x2=%lg", x1, x2);
            break ;
        case INF : printf("There are infinity of solution");
    }
    return 0;
}

void InputCoeff(double *(ptr_a), double *(ptr_b), double *(ptr_c)){//a_ptr  
    printf("%s %c", "Input a, b, c", '\n');
    scanf("%lg %lg %lg", ptr_a, ptr_b, ptr_c);//assert check pointers
    assert (isnan(*ptr_a) == 0 && isnan(*ptr_b) == 0 && isnan(*ptr_c) == 0) ;
}

int Comp(double a, double b)
{
    if (fabs(a - b) < EPS) return 1 ;
    else return 0 ;
}

void SolveLine(double a, double b, double *ptr_x, int *ptr_k){//
    assert (isnan(a) == 0 && isnan(b) == 0) ;
    if (Comp(a, 0) && !Comp(b, 0)) *ptr_k = 0 ;
    else if (Comp(a, 0) && Comp(b, 0)) *ptr_k = INF ;
    else {
    *ptr_x = (-b) / a ;
    *ptr_k = 1 ;
    assert(isnan(*ptr_x) == 0);
    }
}

void SolveSquare(double a, double b, double c, double *ptr_x1, double *ptr_x2, int *ptr_k){//void
    //double x1 = NAN , x2 = NAN ;
    assert (isnan(a) == 0 && isnan(b) == 0 && isnan(c) == 0) ;
    if(Comp(a, 0) && Comp(b, 0) && Comp(c, 0)) *ptr_k = INF ; //printf("There are infinity of solution") 
    else if(Comp(a, 0) && Comp(b, 0) && !Comp(c, 0)) ptr_k = 0 ; //printf("There are no solutions");
    else if(Comp(a, 0) && !Comp(b, 0)) {
        SolveLine(b, c, ptr_x1, ptr_k);
        //*ptr_k = 1 ; printf("%lg", x1);
    }
    else if(!Comp(a, 0) && !Comp(b, 0) && Comp(c, 0)) {
        *ptr_x1 = 0 ;
        SolveLine(a, b, ptr_x2, ptr_k);
        *ptr_k = 2 ;//printf("x1=%lg x2=%lg", x1, x2);
    }
    else if(!Comp(a, 0) && Comp(c, 0) && Comp(c, 0)) {
        *ptr_x1 = 0 ;
        *ptr_k = 1 ;
    }
    else if(!Comp(a, 0) && !Comp(c, 0) && !Comp(c, 0)) {
        double D = NAN;
        D = b * b - 4 * a * c;
        if( D < (-EPS) ) *ptr_k = 0 ; //printf("There are no solutions") ;
        else if (fabs(D) < EPS){
            *ptr_x1 = (-b) / 2 / a ;
            *ptr_k = 1 ;//printf("x=%lg", x1);
        }
        else if(!Comp(D, 0)){
            double sqrtD = sqrt(D);
            *ptr_x1 = ((-b)-sqrtD)/ (2 * a) ;
            *ptr_x2 = ((-b)+sqrtD)/ (2 * a) ;
            *ptr_k = 2 ;//printf("x1=%lg x2=%lg", x1, x2) ;
        }
    }
}
