#define N 1000 // total population
#define time 1000
#define sample 10

#define lambda 0.3 // infection probability (order parameter)
#define gamma 0.2  // probability of becoming recovered

#define So 0.95 // initial susceptible

int main()
{

   int state[N], state_sync[N];
   double S[time], I[time], R[time];

   int I_count, S_count, R_count;

   double S_ave, I_ave, R_ave;

   int i, j, s, t;

   int r;
   double rand;
   unsigned int m, a;

   m = 2147483647;
   a = 16807;
   r = 27;

   char arquivo[200];
   FILE *fp;

   sprintf(arquivo, "N%i_time%i_S%.2lf_lambda%.2lf_gamma%.2lf.txt", N, time, So, lambda, gamma);
   fp = fopen(arquivo, "w");

   fprintf(fp, "#time\t\t\t\t#S\t\t\t\t#I\t\t\t\t#R\n");

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

      for (i = 0; i < N; i++)
      { // define initial conditions for each individual

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

      for (t = 1; t < time; t++)
      { // Monte Carlo steps

         // ################################################
         /************  Epidemic dynamics *************/
         // ################################################
         for (i = 0; i < N; i++)
         {

            if (state[i] == 0)
            { // if individual i is healthy(S)
               do
               {
                  r = (r * a) % m;
                  j = N * ((double)r / m);
               } while (j == i);

               if (state[j] == -1)
               { // infected individual "j" will contact "i" healthy(S)

                  r = (r * a) % m;
                  rand = (double)r / m;
                  if (rand <= lambda)
                  { // S→I
                     state_sync[i] = -1;
                  }
               }
            }
            if (state[i] == -1)
            { // If individual "i" is infected(I)

               r = (r * a) % m;
               rand = (double)r / m;
               if (rand <= gamma)
               { // S→R
                  state_sync[i] = 1;
               }
            }
         }
         for (i = 0; i < N; i++)
            state[i] = state_sync[i]; // Synchronous update
         // Count the number of healthy (S_count), infected (I_count) AND Recovery (R_count) individuals in the population
         S_count = 0;
         I_count = 0;
         R_count = 0;

         for (i = 0; i < N; i++)
         { // Count the states of each individual
            if (state[i] == 0)
               S_count++;
            if (state[i] == -1)
               I_count++;
            if (state[i] == 1)
               R_count++;
         }
         // Add the number of healthy (S_count), infected (I_count) and Recovery (R_count) individuals to the corresponding arrays (S, I and R)
         S[t] += (double)S_count;
         I[t] += (double)I_count;
         R[t] += (double)R_count;

      } // finish time loop
   }    // finish samples loop

   // Calculate the average number of healthy and infected individuals for each time step across all simulation runs
   for (t = 0; t < time; t++)
   {
      S_ave = (double)S[t] / (N * sample);
      I_ave = (double)I[t] / (N * sample);
      R_ave = (double)R[t] / (N * sample);

      fprintf(fp, "%i\t\t\t\t%lf\t\t\t\t%lf\t\t\t\t%lf\n", t, S_ave, I_ave, R_ave);
   }

   fclose(fp);
}
