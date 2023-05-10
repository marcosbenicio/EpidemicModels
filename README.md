# Epidemiological Models

# SIS Model

The Susceptible-Infected-Susceptible (SIS) model, along with its various adaptations (e.g., accounting for mortality rates, population density changes, birth rates, and vaccination-based immunization), serves as a framework for describing scenarios in which susceptible individuals become infected and then self-immunize after a certain period, reverting back to a susceptible state. For more information on different SIS model variations, refer to relevant resources.

This model considers a uniform and homogeneous population where individuals are randomly distributed and classified as either Susceptible $(S)$ or Infected $(I)$. It assumes that any disease affecting the population follows the same dynamics:

1. $S+I=1$: The total population $N$ remains constant, allowing for the assumption that mortality and birth rates fluctuate in a manner that maintains this constancy. In this context, the epidemic can be observed over a brief period. Here, $S=n_s/N$ and $I=n_i/N$, where $n_s$ and $n_i$ represent the number of susceptible and infected individuals, respectively, and $N=n_i+n_s$. This approach focuses solely on population densities.

2. $S\overset{\lambda}{\Longrightarrow}I$: Susceptible individuals transition to the infected state with a probability of $\lambda$ per unit of time following contact with another infected individual. The rate $\lambda$ reflects a population's predisposition to an epidemic.

- For this process to unfold, a susceptible individual (probability $S$), an infected individual (probability $I$), and successful contagion (probability per unit of time $\lambda$) must be present. Therefore, the probability of a susceptible individual becoming infected after contact is given by $P_{S\to I}=\lambda SI$.

3. $I\overset{\alpha}{\Longrightarrow}S$: Infected individuals spontaneously revert to the susceptible state with a probability of $\alpha$ at each point in time. The factor $\alpha$ can be interpreted as an intrinsic recovery mechanism within the population.

- This process requires the presence of an infected individual (probability $I$) and their successful recovery (probability per unit of time $\alpha$). The probability of an infected individual spontaneously transitioning back to a susceptible state is thus $P_{S\to I}=\alpha I$.

To ilustrate this model, consider the following diagram:

<p align="center">
<img src = "Images/SIS/SIS.png" width="400">
</p>

The dynamics of the SIS model can be expressed using a set of coupled ordinary differential equations (ODEs), which represent the rates of change of susceptible and infected populations over time:

$$
\begin{align}
{\frac{dS}{dt}}&=-{\lambda}SI+{\alpha}I ,\\
{\frac{dI}{dt}}&={\lambda}SI-{\alpha}I 
\end{align}
$$

These equations provide a physical understanding of the system's behavior:

1. The rate of change of the susceptible population over time, $\frac{dS}{dt}$, depends on two competing processes:

- Susceptible individuals becoming infected, which decreases the susceptible population. This is represented by the term $-{\lambda}SI$.

- Infected individuals recovering and reverting to a susceptible state, which increases the susceptible population. This is represented by the term ${\alpha}I$.

2. The rate of change of the infected population over time, $\frac{dI}{dt}$, is also governed by two competing processes:

- Susceptible individuals becoming infected, which increases the infected population. This is represented by the term ${\lambda}SI$.

- Infected individuals recovering and reverting to a susceptible state, which decreases the infected population. This is represented by the term $-{\alpha}I$.

These coupled ODEs capture the continuous interplay between the susceptible and infected populations within the SIS model, providing a mathematical representation of the epidemic's progression.

## Results

<p align="center">
<img src = "Images/SIS/sis_tempo_lambda025.png" width="400">
  <img src = "Images/SIS/sis_tempo_lambda05.png" width="400">
  <img src = "Images/SIS/sis_tempo_lambda09.png" width="400">
</p>

Temporal evolution of infected and susceptible agent densities for the parameters $\lambda=0.25$, $\lambda=0.50$, and $\lambda=0.90$ with $\alpha=0.30$ fixed, showing an absorbing phase ($\lambda < \alpha$) at $\lambda=0.25$ and an active phase ($\lambda > \alpha$) at $\lambda=0.50$ and $\lambda=0.90$. Here, $N=10^4$, $I_0=5%$, and averages were taken over 100 simulations. The points represent the simulation results, and the lines represent the numerical solutions.

<p align="center">
<img src = "Images/SIS/Sis_lambda_inf.png" width="400">
</p>

This diagram provides a comprehensive view of the active and absorbing phases. As the fixed parameter $\alpha$ increases, the absorbing phase ($I_\infty=0$) becomes larger, and the active phase ($I_\infty \neq 0$) becomes smaller. Consequently, as the absorbing phases increase, the densities of infected individuals reached in the active phase will be lower for the $\lambda$ values.

<p align="center">
  <img src = "Images/SIS/Sis_lambda_inf_alfa03.png" width="400">
  <img src = "Images/SIS/Sis_lambda_inf_alfa0.5.png" width="400">
</p>

In this diagram, we can more clearly see each of the phases and where exactly the critical point ($\lambda=\alpha$) is; highlighted by the vertical red line. Near the critical point, we have the behavior described by the order parameter shown in the equation.

Here we consider the stationary density of infected individuals $I_\infty$ against the transmissivity rate $\lambda$ with $\alpha=0.3$ and $\alpha=0.5$. The total population is $N=10^4$ with $I_0=5%$. Averages were taken over 100 simulations.

# SISV Model

The introduction of a compartment for vaccinated individuals will change the dynamics subsequently observed in the SIS model. As a result, an individual can be considered in the susceptible (S), infected (I), or vaccinated (V) state. The implemented rules are exemplified below:

1. $S+I+V=1$: The total population $N$ is constant. I considered $S=n_s/N$, $I=n_i/N$, and $V=n_v/N$ where $n_s$, $n_i$, and $n_v$ are the numbers of susceptible, infected, and vaccinated individuals, respectively, and $N=n_i+n_s+n_v$; since we will be dealing exclusively with population densities.

2. $S\overset{\gamma}{\Longrightarrow}V$: A susceptible individual has a probability of $\gamma$ per unit of time to get vaccinated.

- The process occurs when we find a susceptible individual (with probability S) and with probability $\gamma$, this individual gets vaccinated. The probability of a susceptible individual becoming vaccinated will be $P_{S\to V}=\gamma S$.

3. $S\overset{(1-\gamma)\lambda}{\Longrightarrow}I$: A susceptible individual will be transferred to the infected state with a probability of $(1-\gamma)\lambda$ per unit of time after coming into contact with a second infected individual. Here, the predisposition rate for a given population to face an epidemic will be $(1-\gamma)\lambda$.

- The process occurs similarly to the SIS model \eqref{StoI}. The probability of a susceptible individual becoming infected after contact will be $P_{S\to I}=(1-\gamma)\lambda SI$.

4. $I\overset{\alpha}{\Longrightarrow}S$: Here, again, it will occur as already discussed for the SIS model \eqref{ItoS}.

- The probability of an infected individual spontaneously transforming into a susceptible individual is $P_{I\to S}=\alpha I$.

5. $V\overset{\phi}{\Longrightarrow}S$ A vaccinated individual can become susceptible again with a probability of $\phi$. We can interpret $\phi$ as a rate of loss of immunity for the individual who was vaccinated.

- For this process to occur, it is necessary to find a vaccinated individual (with probability V), and for that individual to lose the immunity provided by the vaccine (with probability $\phi$). The probability of a vaccinated individual becoming susceptible is $P_{V\to S}= \phi V$.

To ilustrate this model, consider the following diagram:

<p align="center">
<img src = "Images/SIS/SISV.png" width="400">
</p>

In the context of the SISV (Susceptible-Infected-Susceptible-Vaccinated) model, the following set of coupled ordinary differential equations (ODEs) describe the dynamics of the population:

$$
\begin{align}
{\frac{dS}{dt}}&=-{ {\gamma}S - {(1-\gamma)\lambda}SI + {\alpha}I +{\phi}V } \\
{\frac{dI}{dt}}&={ {(1-\gamma)\lambda}SI -{\alpha}I }, \\
{\frac{dV}{dt}}&={{\gamma}S- {\phi}V }.
\end{align}
$$

1. The rate of change of the susceptible population over time, $\frac{dS}{dt}$, depends on four competing processes:
Susceptible individuals becoming infected, which decreases the susceptible population. This is represented by the term $-{(1-\gamma)\lambda}SI$.

- Susceptible individuals getting vaccinated, which also decreases the susceptible population. This is represented by the term $-{\gamma}S$.

- Infected individuals recovering and reverting to a susceptible state, which increases the susceptible population. This is represented by the term ${\alpha}I$.

- Vaccinated individuals losing immunity and reverting to a susceptible state, which increases the susceptible population. This is represented by the term ${\phi}V$.

2. The rate of change of the infected population over time, $\frac{dI}{dt}$, is governed by two competing processes:

- Susceptible individuals becoming infected, which increases the infected population. This is represented by the term ${(1-\gamma)\lambda}SI$.

- Infected individuals recovering and reverting to a susceptible state, which decreases the infected population. This is represented by the term $-{\alpha}I$.

3. The rate of change of the vaccinated population over time, $\frac{dV}{dt}$, depends on two competing processes:

- Susceptible individuals getting vaccinated, which increases the vaccinated population. This is represented by the term ${\gamma}S$.

- Vaccinated individuals losing immunity and reverting to a susceptible state, which decreases the vaccinated population. This is represented by the term $-{\phi}V$.

# Results



