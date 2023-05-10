#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

#define N       1000    //população total
#define time    1000
#define sample  10        

#define lambda   0.3     //probabilidade de infecção (parâmetro de ordem)
#define alpha    0.2     //probabilidade de cura
#define phi
#define gamma

#define So      0.95     //suscetivel inicial
#define Vo      0.0    


int main(){

   int state[N],state_sync[N];
   double S[time],I[time],V[time];
   
   int I_count,S_count,V_count;
   
   double S_ave,I_ave,V_ave;
   
   int i,j,s,t;
     
   int r;
   double rand;     
   unsigned int m,a;
   
   m=2147483647;
   a=16807;
   r=27;
     
   char arquivo[200];  
   FILE *fp;
   
   sprintf(arquivo,"N%i_time%i_S%.2lf_lambda%.2lf_alpha%.2lf_phi%.2lf_gamma%.2lf.txt",N,time,So,lambda,alpha,phi,gamma);
   fp=fopen(arquivo,"w");
   
   
   fprintf(fp,"#time\t\t\t\t#S\t\t\t\t#I\t\t\t\t#V\n");
   
   for(t=0;t<time;t++){
     S[t]=0.0;
     I[t]=0.0;
     V[t]=0.0;
   }
   
   for(s=1;s<=sample;s++){
      S_count=0;
      I_count=0;
      V_count=0;   
  
      for(i=0;i<N;i++){//define as condições iniciais de cada indivíduo            
           
         r=(r*a)%m; 
         rand=(double)r/m;
         if(rand<So){ 
            state[i]=0;
            state_sync[i]=0;
            S_count++;
         } 
         else{ 
            state[i]=-1;
            state_sync[i]=-1;
            I_count++;
         }
      } 
      V_count=Vo; 
      S[0]+=(double)S_count;
      I[0]+=(double)I_count;
      V[0]+=(double)V_count;
       
      for(t=1;t<time;t++){//Passos Monte Carlo
           
         //################################################
         /************  Dinâmica da epidemia *************/
         //################################################     
         for(i=0;i<N;i++){
              
            if(state[i]==0){// se indivíduo i é saudável(S)
      
               r=(r*a)%m;
               rand=(double)r/m;
               if(rand<=gamma){ //S→V
                  state_sync[i]=1;
               }
               else{//caso não se vacine    
                  
                  do{
                     r=(r*a)%m;
                     j=N*((double)r/m);
                  }while(j==i);
                     
                     if(state[j]==-1){//indívio j infectado(I) que entrará em contato com um saudável(S) i 
                        r=(r*a)%m;
                        rand=(double)r/m;
                        if( rand<=lambda ){//SI→II
                           state_sync[i]=-1;
                        }
                     }
                  }
               }
            if(state[i]==-1){//para um infectado "i"
               
               r=(r*a)%m;
               rand=(double)r/m;
               if(rand<=alpha){//chance de se tornar um saudável
                  state_sync[i]=0;
               }
            }
         }        
         for(i=0;i<N;i++) state[i]=state_sync[i]; //Atualização sincronizada ou paralela

         S_count=0;
         I_count=0;
         V_count=0;
           
         for(i=0;i<N;i++){  //conta os estados de cada indivíduo 
            if(state[i]==0)  S_count++;
            if(state[i]==-1) I_count++;
            if(state[i]==1)  V_count++;
         }
           
         S[t]+=(double)S_count;
         I[t]+=(double)I_count;
         V[t]+=(double)V_count;       
      }//tempo                           
  }//samples  
        
      for(t=0;t<time;t++){   
         S_ave=(double)S[t]/(N*sample);
         I_ave=(double)I[t]/(N*sample);
         V_ave=(double)V[t]/(N*sample);
         fprintf(fp,"%i\t\t\t\t%lf\t\t\t\t%lf\t\t\t\t%lf\n",t,S_ave,I_ave,V_ave);         
      }
      
      
     fclose(fp);
               
}
