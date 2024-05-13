#include "Estimateurs.hpp"

using namespace std;


/**************************************************************************************************

Fonctions Utiles

**************************************************************************************************/

double Phi(double x)
	{return exp(-x * x / 2) / sqrt(2 * M_PI);}

/*************************************************************************************************/

unsigned int Target(const Sample & S, double c, unsigned int N_Actu, unsigned int Nb_Simu, unsigned int Tau_e)
{
	double Alpha_B, Biais, Variance, Val;
	Alpha_B = Alpha_Bar(S,c);
	Biais = Alpha(S, c) - Alpha_B;
	Variance = Alpha_B * (1 - Alpha_B) / (double)N_Actu;
	
	Val = max(1., pow(Variance * pow((Nb_Simu + Tau_e), 4) / (4 * Biais * Biais * pow(Nb_Simu, 4)), 0.2));
	
	Val = (N_Actu * Val < N_Actu + Tau_e) ? N_Actu * Val : N_Actu + Tau_e;
	return Val / 1;
}

/*************************************************************************************************/

double Alpha(const Sample & S, double c)
{
	unsigned long n = S.Lire_Sc().size(), alpha = 0;
	for(unsigned int i=0; i<n; i++)
		alpha += (S[i].Loss()>c) ? 1 : 0;
	return alpha / (double)n;
}

/*************************************************************************************************/

double Alpha_Bar(const Sample & S, double c)
{
	unsigned long n = S.Lire_Sc().size();
	double alpha = 0;
	for(unsigned int i=0; i<n; i++)
		alpha += Phi(S[i].Fiabilite(c, S.Lire_In()));
	return alpha / (double)n;
}

/*************************************************************************************************/

void Add_Simu_Sort_Fiab(Sample & S, double * Fiab, unsigned int n, double c, double x_0, Modele * inner, Payoff * P)
{
	unsigned int j = 0;
	S[0].Add_Simu(x_0, inner, P);
	Fiab[0] = S[0].Fiabilite(c, inner);
	while((Fiab[j] > Fiab[j+1]) && (j<n-1))
	{
		swap(Fiab[j], Fiab[j+1]);
		swap(S[j], S[j+1]);
		j++;
	}
}

/*************************************************************************************************/

bool Add_Simu_RSort_M(Sample & S, unsigned int N_Fiab, unsigned int N_Actu, unsigned int m_0, double c, double x_0, Modele * inner, Payoff * P)
{
	unsigned int j = N_Actu-1, M = S[j].Lire_M()+1;
	S[j].Add_Simu(x_0, inner, P);
	
	while((M > S[j-1].Lire_M()) && (j>N_Fiab))
	{
		swap(S[j-1], S[j]);
		j--;
	}
	if(M == m_0)
		{return true;}
	return false;
}

/**************************************************************************************************

Uniform

**************************************************************************************************/

double Uniform(unsigned int m, unsigned int n, double c, double x_0, Modele * outer, Modele * inner, Payoff * P)
{
	double alpha = 0;
	Scenario Sc;
	for(unsigned int i=0; i<n; i++)
	{
		Sc = Scenario(m, (*outer)(), x_0, inner, P);
		alpha += (Sc.Loss() < c) ? 0 : 1;
	}
	return alpha / (double)n;
}

/**************************************************************************************************

Sequential

**************************************************************************************************/

double Sequential(unsigned int m_0, unsigned int m_bar, unsigned int n, double c, double x_0, Modele * outer, Modele * inner, Payoff * P)
{
	unsigned int i, To_Add = (m_bar - m_0) * n;
	
	double Fiab[n];
	
	Sample S(n, m_0, x_0, outer, inner, P);
	
	Cmp_Fiab Cmp(c, inner);
	sort(&S[0], &S[n], Cmp);
	
	for(i=0; i<n; i++)
		Fiab[i] = S[i].Fiabilite(c, inner);
	
	for(i=0; i<To_Add; i++)
		Add_Simu_Sort_Fiab(S, Fiab, n, c, x_0, inner, P);
	return Alpha(S, c);
}

/**************************************************************************************************

Threshold

**************************************************************************************************/

double Threshold(double gamma, unsigned int n, double c, double x_0, Modele * outer, Modele * inner, Payoff * P)
{
	double alpha = 0;
	Scenario Sc;
	for(unsigned int i=0; i<n; i++)
	{
		Sc = Scenario(1, (*outer)(), x_0, inner, P);
		while(Sc.Fiabilite(c, inner) < gamma)
			Sc.Add_Simu(x_0, inner, P);
		alpha += (Sc.Loss() < c) ? 0 : 1;
	}
	return alpha / (double)n;
}

/**************************************************************************************************

Adaptive

**************************************************************************************************/

double Adaptive(unsigned int m_0, unsigned int n_0, unsigned int Tau_e, unsigned int k, double c, double x_0, Modele * outer, Modele * inner, Payoff * P)
{
	unsigned int i, l, New_N;
	unsigned int N_Actu = n_0, N_Fiab = n_0;
	unsigned int Nb_Simu = m_0 * n_0;
	double Fiab[k/m_0];	// Creer un tableau de taille le maximum de scenarios possible
	
	Sample S(n_0, m_0, x_0, outer, inner, P);
	
	Cmp_Fiab Cmp(c, inner);
	sort(&S[0], &S[n_0], Cmp);
	
	for(i=0; i<n_0; i++)
		Fiab[i] = S[i].Fiabilite(c, inner);
	
	for(l=1; l<k/Tau_e; l++)
	{
		New_N = Target(S, c, N_Actu, Nb_Simu, Tau_e);
		S.Add_Scenar(1, New_N - N_Actu);
		Nb_Simu += New_N - N_Actu;
		N_Actu = New_N;
		
		while(Nb_Simu < l * Tau_e)
		{
			if(N_Fiab < N_Actu)
			{
				if(Add_Simu_RSort_M(S, N_Fiab, N_Actu, m_0, c, x_0, inner, P))
				{
					Fiab[N_Fiab] = S[N_Fiab].Fiabilite(c, inner);
					N_Fiab++;
					i = N_Fiab-1;
					while((Fiab[i-1] > Fiab[i]) && (i>1))
					{
						swap(Fiab[i-1], Fiab[i]);
						swap(S[i-1], S[i]);
						i--;
					}
				}
				Nb_Simu++;
			}	// Ceci ajoute un scenario au plus petit m s il y en a inferieur a m_0, et le met du cote des scen tries par fiab si m=m_0 apres ajout
			else
			{
				Add_Simu_Sort_Fiab(S, Fiab, N_Fiab, c, x_0, inner, P);
				Nb_Simu++;
			}
		}
	}
	return Alpha(S, c);
}




