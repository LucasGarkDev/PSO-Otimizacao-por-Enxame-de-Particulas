#include "pso.h"




double custom_sqrt(double number) {
   double guess = number / 2.0;
   double epsilon = 0.00001;


   if (number < 0) return -1; // Retorna -1 para valores negativos (não suportado)
   while ((guess * guess - number) > epsilon || (number - guess * guess) > epsilon) {
       guess = (guess + number / guess) / 2.0;
   }
   return guess;
}


double custom_fabs(double number) {
   return number < 0 ? -number : number;
}


double custom_sin(double x) {
   // Aproximação por série de Taylor para x em radianos
   double term = x;
   double result = term;
   int n = 1;
   int sign = -1;


   while (custom_fabs(term) > 0.00001) {
       term *= x * x / ((2 * n) * (2 * n + 1));
       result += sign * term;
       sign *= -1;
       n++;
   }
   return result;
}




// Função objetivo (Eggholder function)
double eggholder(double x, double y) {
   return -(y + 47) * custom_sin(custom_sqrt(custom_fabs((x / 2) + y + 47))) - x * custom_sin(custom_sqrt(custom_fabs(x - (y + 47))));
}


// Inicializa o enxame
void initializeSwarm(Swarm *swarm, int numParticles, int dimensions, double minPos, double maxPos, double maxVel) {
   swarm->particles = (Particle *)malloc(numParticles * sizeof(Particle));
   swarm->globalBestPosition = (double *)malloc(dimensions * sizeof(double));
   swarm->globalBestFitness = INFINITY;
   swarm->numParticles = numParticles;
   swarm->dimensions = dimensions;


   for (int i = 0; i < numParticles; i++) {
       Particle *p = &swarm->particles[i];
       p->position = (double *)malloc(dimensions * sizeof(double));
       p->velocity = (double *)malloc(dimensions * sizeof(double));
       p->bestPosition = (double *)malloc(dimensions * sizeof(double));
       p->fitness = INFINITY;
       p->bestFitness = INFINITY;


       for (int d = 0; d < dimensions; d++) {
           p->position[d] = minPos + (maxPos - minPos) * ((double)rand() / RAND_MAX);
           p->velocity[d] = -maxVel + 2 * maxVel * ((double)rand() / RAND_MAX);
           p->bestPosition[d] = p->position[d];
       }
   }
}


// Avalia a aptidão de uma partícula
double evaluateFitness(double *position) {
   return eggholder(position[0], position[1]);
}


// Atualiza a velocidade
void updateVelocity(Particle *particle, double *globalBestPosition, int dimensions, double w, double c1, double c2) {
   for (int d = 0; d < dimensions; d++) {
       double r1 = (double)rand() / RAND_MAX;
       double r2 = (double)rand() / RAND_MAX;


       particle->velocity[d] = w * particle->velocity[d]
           + c1 * r1 * (particle->bestPosition[d] - particle->position[d])
           + c2 * r2 * (globalBestPosition[d] - particle->position[d]);
   }
}


// Atualiza a posição
void updatePosition(Particle *particle, double minPos, double maxPos, int dimensions) {
   for (int d = 0; d < dimensions; d++) {
       particle->position[d] += particle->velocity[d];


       if (particle->position[d] < minPos) {
           particle->position[d] = minPos;
           particle->velocity[d] = 0;
       } else if (particle->position[d] > maxPos) {
           particle->position[d] = maxPos;
           particle->velocity[d] = 0;
       }
   }
}


// Atualiza as melhores posições
void updateBestPositions(Swarm *swarm) {
   for (int i = 0; i < swarm->numParticles; i++) {
       Particle *p = &swarm->particles[i];
       p->fitness = evaluateFitness(p->position);


       if (p->fitness < p->bestFitness) {
           p->bestFitness = p->fitness;
           for (int d = 0; d < swarm->dimensions; d++) {
               p->bestPosition[d] = p->position[d];
           }
       }


       if (p->fitness < swarm->globalBestFitness) {
           swarm->globalBestFitness = p->fitness;
           for (int d = 0; d < swarm->dimensions; d++) {
               swarm->globalBestPosition[d] = p->position[d];
           }
       }
   }
}


// Executa o PSO
void runPSO(Swarm *swarm, int iterations, double w, double c1, double c2, double minPos, double maxPos) {
   for (int iter = 0; iter < iterations; iter++) {
       for (int i = 0; i < swarm->numParticles; i++) {
           Particle *p = &swarm->particles[i];
           updateVelocity(p, swarm->globalBestPosition, swarm->dimensions, w, c1, c2);
           updatePosition(p, minPos, maxPos, swarm->dimensions);
       }
       updateBestPositions(swarm);
       printf("Iteration %d: Best Fitness = %lf\n", iter, swarm->globalBestFitness);
   }
}


int main() {
   srand(time(NULL));


   int numParticles = 50;
   int dimensions = 2;
   double minPos = -512, maxPos = 512, maxVel = 77;
   double w = 0.5, c1 = 1.5, c2 = 1.5;
   int iterations = 100;


   Swarm swarm;
   initializeSwarm(&swarm, numParticles, dimensions, minPos, maxPos, maxVel);
   runPSO(&swarm, iterations, w, c1, c2, minPos, maxPos);


   // Liberar memória
   for (int i = 0; i < numParticles; i++) {
       free(swarm.particles[i].position);
       free(swarm.particles[i].velocity);
       free(swarm.particles[i].bestPosition);
   }
   free(swarm.particles);
   free(swarm.globalBestPosition);


   return 0;
}

