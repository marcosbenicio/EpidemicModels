#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

#define N        10000      // Total population
#define time     1000       // Simulation time
#define sample   100        // Number of samples

#define lambda   0.9       // Probability of infection (order parameter)
#define alpha    0.3       // Probability of recovery

#define So       0.95      // Initial susceptible fraction

int main()
{
   // arrays to hold the state of each individual
   int state[N], state_sync[N];
   // arrays to store the number of individuals in each state
   double S[time], I[time];
   // variables to count the number of individuals in each state
   int I_count, S_count;
   // variables to store the average number of individuals in each state
   double S_ave, I_ave;

   int i, j, s, t;

   int r;
   double rand;
   unsigned int m, a;         

   m = 2147483647;      // maximum value for the random number generator
   a = 16807;           // multiplier for the random number generator
   r = 27;          // initial seed for the random number generator

   char arquivo[200];
   FILE *fp;

   sprintf(arquivo, "N%i_time%i_S%.2lf_lambda%.2lf_alpha%.2lf_sample%i.txt", N, time, So, lambda, alpha, sample);
   fp = fopen(arquivo, "w");

   fprintf(fp, "#time\t\t\t\t#S\t\t\t\t#I\n");

   for (t = 0; t < time; t++)
   {  // Initialize the S and I arrays to 0
      S[t] = 0.0;
      I[t] = 0.0;
   }
   // Run the simulation for multiple samples
   for (s = 1; s <= sample; s++)
   {// loop over samples 
      S_count = 0;
      I_count = 0;
       // Initialize the state array for each individual
      for (i = 0; i < N; i++)
      { // define as condições iniciais de cada indivíduo

         r = (r * a) % m;
         rand = (double)r / m;
         if (rand < So)
         {
            state[i] = 0;
            state_sync[i] = 0;
            S_count++;
         }
         else
         {
            state[i] = -1;
            state_sync[i] = -1;
            I_count++;
         }
      }

      S[0] += (double)S_count;
      I[0] += (double)I_count;


      for (t = 1; t < time; t++)
      { // loop over the simulation time

         // ################################################
            /************  Epidemic dynamics*************/
         // ################################################
         for (i = 0; i < N; i++)
         {

            if (state[i] == 0)
            { // if individual i is susceptible(S)
               do
               {
                  r = (r * a) % m;
                  j = N * ((double)r / m);
               } while (j == i);

               if (state[j] == -1)
               { // if individual j is infected(I) and will come into contact with individual i

                  r = (r * a) % m;
                  rand = (double)r / m;
                  if (rand <= lambda)
                  { //  S→I 
                     state_sync[i] = -1;
                  }
               }
            }
            if (state[i] == -1)
            { // if individual i is infected(I)

               r = (r * a) % m;
               rand = (double)r / m;
               if (rand <= alpha)
               { // I→S
                  state_sync[i] = 0;
               }
            }
         }
         for (i = 0; i < N; i++)
            state[i] = state_sync[i]; // Synchronous update
         // Count the number of healthy (S_count), infected (I_count)
         S_count = 0;
         I_count = 0;

         for (i = 0; i < N; i++)
         {// Count the states of each individual
            if (state[i] == 0)
               S_count++;
            if (state[i] == -1)
               I_count++;
         }
         // Add the number of healthy (S_count), infected (I_count) to the corresponding arrays (S, I)
         S[t] += (double)S_count;
         I[t] += (double)I_count;
      } // finish time loop
   }    // finish samples loop

   // Calculate the average number of healthy and infected individuals for each time step across all simulation runs
   for (t = 0; t < time; t++)
   {
      S_ave = (double)S[t] / (N * sample);
      I_ave = (double)I[t] / (N * sample);

      fprintf(fp, "%i\t\t\t\t%lf\t\t\t\t%lf\n", t, S_ave, I_ave);
   }

   fclose(fp);
}
