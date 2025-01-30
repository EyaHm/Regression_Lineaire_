#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct data {
    float x;
    float y;
}data;

//fonction affine
double f(double x, double a, double b) {
    return a * x + b;
}

//fonction descente de gradient
void descente_gradient(double *mse,data *p,int nb, double *a, double *b, double alpha, int max_iter, double eps) {
    if(p!=NULL) {
        double  grad_a, grad_b;
        int iter = 0;
        do {
            //calcul de l'erreur quadratique moyenne et des gradients
            grad_a = 0;
            grad_b = 0;
            *mse = 0;
            for (int i = 0; i < nb; i++) {
                double x = (p+i)->x;
                double y_reel = (p+i)->y;
                double y_pred = f(x, *a, *b);

                double erreur = y_reel - y_pred;

                *mse += erreur * erreur;
                grad_a += -2 * x * erreur;
                grad_b += -2 * erreur;

            }
            *mse /= nb; 
            grad_a /= nb;
            grad_b /= nb;

    
            *a -= alpha * grad_a;
            *b -= alpha * grad_b;

            iter++;
        } while (*mse > eps && iter < max_iter);
        printf("Iterations: %d\n", iter-1);
    }else {
        printf("Error\n");
        exit(1);
    }
}
//affichage du tableau
void afficher(data *p,int nb) {
    if (p!=NULL) {
        for(int i=0;i<nb;i++) {
            printf("X=%f  Y=%f\n",(p+i)->x,(p+i)->y);
        }
    } else {
        printf("Erreur\n");
        exit(1);
    }
}

void ajout(data **p,int *nb) {
    printf("Introduire el numero de points:");
    scanf("%d",nb);
    *p=(data *)malloc(*nb*sizeof(data));
    if(*p!=NULL) {
        for(int i=0;i<*nb;i++) {
            printf("X=");
            scanf("%f",&(*p+i)->x);
            printf("Y=");
            scanf("%f",&(*p+i)->y);
        }
    }else {
        printf("Erreur\n");
        exit(1);
    }
    }

int main(void) {
    data *p=NULL;
    int nb;
    ajout(&p,&nb);
    afficher(p,nb);

    //initialisation de a et b
    srand((unsigned int)time(NULL));
    double a = ((float)rand() / RAND_MAX) * 10;
    double b = ((float)rand() / RAND_MAX) * 10;
    printf("f(X)= %f X+ %f\n", a, b);

    //intialisation des parametres
    double eps=1e-5;
    double alpha=0.01;
    int max_iter=10000;
    double mse=0;

    //execution de descente de gradient
    descente_gradient(&mse,p,nb, &a, &b, alpha, max_iter, eps);
    printf("fonction finale f(X)= %f X+ %f\n", a, b);
    printf("Erreur quadratique moyenne finale : %f\n", mse);
    free(p);
    return 0;
}
