# Epidemiological Models

# SIS Model

The Susceptible-Infected-Susceptible (SIS) model, along with its various adaptations (e.g., accounting for mortality rates, population density changes, birth rates, and vaccination-based immunization), serves as a framework for describing scenarios in which susceptible individuals become infected and then self-immunize after a certain period, reverting back to a susceptible state. For more information on different SIS model variations, refer to relevant resources.

This model considers a uniform and homogeneous population where individuals are randomly distributed and classified as either Susceptible $(S)$ or Infected $(I)$. It assumes that any disease affecting the population follows the same dynamics:

1. $S+I=1$: The total population $N$ remains constant, allowing for the assumption that mortality and birth rates fluctuate in a manner that maintains this constancy. In this context, the epidemic can be observed over a brief period. Here, $S=n_s/N$ and $I=n_i/N$, where $n_s$ and $n_i$ represent the number of susceptible and infected individuals, respectively, and $N=n_i+n_s$. This approach focuses solely on population densities.

2. $S\overset{\lambda}{\Longrightarrow}I$: Susceptible individuals transition to the infected state with a probability of $\lambda$ per unit of time following contact with another infected individual. The rate $\lambda$ reflects a population's predisposition to an epidemic.

- For this process to unfold, a susceptible individual (probability $S$), an infected individual (probability $I$), and successful contagion (probability per unit of time $\lambda$) must be present. Therefore, the probability of a susceptible individual becoming infected after contact is given by $P_{S\to I}=\lambda SI$.

3. $I\overset{\alpha}{\Longrightarrow}S$: Infected individuals spontaneously revert to the susceptible state with a probability of $\alpha$ at each point in time. The factor $\alpha$ can be interpreted as an intrinsic recovery mechanism within the population.

- This process requires the presence of an infected individual (probability $I$) and their successful recovery (probability per unit of time $\alpha$). The probability of an infected individual spontaneously transitioning back to a susceptible state is thus $P_{S\to I}=\alpha I$.

Considering these rules, the dynamics of the SIS model can be expressed using a set of coupled ordinary differential equations (ODEs), which represent the rates of change of susceptible and infected populations over time:

$$
\begin{align}
{\frac{dS}{dt}}&=-{\lambda}SI+{\alpha}I ,\\
{\frac{dI}{dt}}&={\lambda}SI-{\alpha}I 
\end{align}
$$

These equations provide a physical understanding of the system's behavior:

- The rate of change of the susceptible population over time, $\frac{dS}{dt}$, depends on two competing processes:

- Susceptible individuals becoming infected, which decreases the susceptible population. This is represented by the term $-{\lambda}SI$.
Infected individuals recovering and reverting to a susceptible state, which increases the susceptible population. This is represented by the term ${\alpha}I$.
The rate of change of the infected population over time, $\frac{dI}{dt}$, is also governed by two competing processes:

- Susceptible individuals becoming infected, which increases the infected population. This is represented by the term ${\lambda}SI$.
Infected individuals recovering and reverting to a susceptible state, which decreases the infected population. This is represented by the term $-{\alpha}I$.
These coupled ODEs capture the continuous interplay between the susceptible and infected populations within the SIS model, providing a mathematical representation of the epidemic's progression.

To ilustrate this model, consider the following diagram:

<img src = "Images/SIS/SIS">


## Results




# SISV Model

