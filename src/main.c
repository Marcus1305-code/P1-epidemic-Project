#include <stdio.h>
void input_parameters(int* susceptible, int* exposed, int* infected,
    int* recovered, int* beta, int* sigma, int* gamma, int* t);
int calculation_of_population_and_infection_rate(int susceptible, int exposed,
                                                 int infected, int recovered);
void differential_equations(double s, double e, double in, double r,
                            int N, int gamma, int beta, int sigma, int t);

int main() {
    int susceptible, exposed, infected, recovered, beta, sigma, gamma, t;

    input_parameters(&susceptible, &exposed, &infected,
        &recovered, &beta, &sigma, &gamma, &t);
    double s = (double)susceptible;
    double e = (double)exposed;
    double in = (double)infected;
    double r = (double)recovered;

    int N = calculation_of_population_and_infection_rate(susceptible,
        exposed, infected, recovered);

    differential_equations(susceptible, exposed, infected,
    recovered, N, gamma, beta, sigma, t);
    printf("total citizens: %d", N);
}
void input_parameters(int* susceptible, int* exposed, int* infected,
    int* recovered, int* beta, int* sigma, int* gamma, int* t) {
    printf("susceptible\n");
    scanf(" %d", susceptible);
    printf("exposed\n");
    scanf(" %d", exposed);
    printf("infected\n");
    scanf(" %d", infected);
    printf("recovered\n");
    scanf(" %d", recovered);
    printf("beta\n");
    scanf(" %d", beta);
    printf("sigma\n");
    scanf(" %d", sigma);
    printf("gamma\n");
    scanf(" %d", gamma);
    printf("chose time range\n");
    scanf(" %d", t);
}

int calculation_of_population_and_infection_rate(int susceptible, int exposed,
                            int infected, int recovered) {
    return susceptible + exposed + infected + recovered;
}

void differential_equations(double s, double e, double in, double r,
                            int N, int gamma, int beta, int sigma, int t) {

    FILE *file = fopen("seir_data.txt", "w");
    if (file == NULL) {
        printf("no file can be found\n");
        return;
    }

    float g, b, si;
    b = (float)beta / 10;
    g = (float)gamma / 10;
    si = (float)sigma / 10;

    fprintf(file, "0 %.2f %.2f %.2f %.2f\n", s, e, in, r);

    double differential_susceptible, differential_exposed,
        differential_infected, differential_recovered;

    double dt = 0.1;

    for (int i = 1; i <= t * 10; i++) {

        differential_susceptible = -(b * s * in)/N;
        //printf(" %lf", differential_susceptible);

        differential_exposed = -differential_susceptible - si * e;
        //printf(" %lf", differential_exposed);

        differential_infected = si * e - g * in;
        //printf(" %lf", differential_infected);

        differential_recovered = g * in;
        //printf(" %lf", differential_recovered);

        s += differential_susceptible * dt;
        e += differential_exposed * dt;
        in += differential_infected * dt;
        r += differential_recovered * dt;

        fprintf(file, "%lf %.2f %.2f %.2f %.2f\n",
                i * dt, s, e, in, r);
        //printf(" %lf\n", s + e + in + r);
    }

    fclose(file);
}