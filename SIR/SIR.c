#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

<<<<<<< HEAD
#define N       1000    //total population
#define time    1000    //simulation time
#define sample  10      //number of samples

#define lambda   0.3    //infection probability (order parameter)
#define gamma    0.2    //probability of becoming recovered

#define So       0.95   //initial susceptible

int main()
{
   // arrays to store the state of individuals
   int state[N], state_sync[N];     
   // arrays to store the number of individuals in each state
   double S[time], I[time], R[time];
   // variables to count the number of individuals in each state
   int I_count, S_count, R_count; 
   // variables to store the average number of individuals in each state
   double S_ave, I_ave, R_ave; 

   int i, j, s, t; // loop variables

   int r;
   double rand;
   unsigned int m, a;

   m = 2147483647; // maximum value for the random number generator
   a = 16807;      // multiplier for the random number generator
   r = 27;         // initial seed for the random number generator

   char arquivo[200];
   FILE *fp;

   sprintf(arquivo, "N%i_time%i_S%.2lf_lambda%.2lf_gamma%.2lf.txt", N, time, So, lambda, gamma);
   fp = fopen(arquivo, "w");

   fprintf(fp, "#time\t\t\t\t#S\t\t\t\t#I\t\t\t\t#R\n");

   // initialize arrays
   for (t = 0; t < time; t++)
   {
      S[t] = 0.0;
      I[t] = 0.0;
      R[t] = 0.0;
   }

   for (s = 1; s <= sample; s++)
   {
      S_count = 0;
      I_count = 0;
      R_count = 0;

      // initialize the state of each individual
      for (i = 0; i < N; i++)
      {
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
      R[0] += (double)R_count;

      // Monte Carlo steps
      for (t = 1; t < time; t++)
      {

         // ################################################
         /************  Epidemic dynamics  *************/
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
                  { // S→I
                     state_sync[i] = 1;
                  }
               }
            }
            if(state[i]==-1){// if individual "i" is infected (I)
