#include "Scenar.hpp"

using namespace std;


/**************************************************************************************************

Scenario
protected:
	unsigned int m;
	double S_Tau, L;

**************************************************************************************************/

Scenario::Scenario(unsigned int m, double S_Tau, double X_0, Modele * inner, Payoff * P)
	: m(m), S_Tau(S_Tau), L(0)
{
	inner->Mod_S_0(S_Tau);
	for(unsigned int i=0; i<m; i++)
		L += X_0 - (*P)(inner);
	L /= (double)m;
}

/*************************************************************************************************/

Scenario::Scenario(const Scenario & S)
{
	m = S.m;
	L = S.L;
	S_Tau = S.S_Tau;
}

/*************************************************************************************************/

void Scenario::Add_Simu(double X_0, Modele * M, Payoff * P)
{
	M->Mod_S_0(S_Tau);
	L = (L * m + X_0 - (*P)(M)) / (m+1.);
	m++;
}

/*************************************************************************************************/

double Scenario::Fiabilite(double c, Modele * M) const
{
	M->Mod_S_0(S_Tau);
	return m * abs(L - c) / M->StdDev();
}

/*************************************************************************************************/

bool Cmp_M(const Scenario & S1, const Scenario & S2)
	{return S1.m < S2.m;}

/*************************************************************************************************/

bool Cmp_Fiab::operator()(const Scenario & S1, const Scenario & S2) const
	{return S1.Fiabilite(c, M) < S2.Fiabilite(c, M);}

/**************************************************************************************************

Sample
protected:
	double X_0;
	vector<Scenario> Sc;
	Modele * outer;
	Modele * inner;
	Payoff * P;

**************************************************************************************************/

Sample::Sample(unsigned int n_0, unsigned int m_0, double X_0, Modele * outer, Modele * inner, Payoff * P)
	: X_0(X_0), outer(outer), inner(inner), P(P)
{
	for(unsigned int i=0; i<n_0; i++)
		Sc.push_back(Scenario(m_0, (*outer)(), X_0, inner, P));
}

/*************************************************************************************************/

Sample::Sample(const Sample & S)
{
	X_0 = S.X_0;
	Sc = S.Sc;
	outer = S.outer;
	inner = S.inner;
	P = S.P;
}

/*************************************************************************************************/

void Sample::Add_Scenar(unsigned int m, unsigned int n)
{
	for(unsigned int i=0; i<n; i++)
		Sc.push_back(Scenario(m, (*outer)(), X_0, inner, P));
}

/*************************************************************************************************/




