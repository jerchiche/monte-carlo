#include "Modeles.hpp"

using namespace std;


/**************************************************************************************************

Gauss

**************************************************************************************************/

Gauss::Gauss(const Gauss & G)
{
	Mu = G.Mu;
	Sigma = G.Sigma;
}
/*************************************************************************************************/
double Gauss::operator()()
{
	static bool test = true;
	static double u;
	static double theta;
	double g;
	if(test)
	{
		u = rand() / (double) RAND_MAX;
        u = sqrt(-2 * log(u));
		theta = 2 * M_PI *rand() / (double) RAND_MAX;
		g = u * cos(theta);
		test = false;
	}	// Simulation de nouvelles uniformes et utilisation de la gaussienne par cosinus
	else
	{
		g = u * sin(theta);
		test = true;
	}	// Utilisation de la gaussienne par sinus
	return Mu + Sigma * g;
}

/**************************************************************************************************

B_S

**************************************************************************************************/

Param_BS::Param_BS(const Param_BS & P_BS)
{
	Mu = P_BS.Mu;
	Vol = P_BS.Vol;
	Temps = P_BS.Temps;
}

/*************************************************************************************************/

B_S::B_S(const Param_BS params, double X)
	: S_0(X)
{
	P = &params;
	double M = (P->Mu - P->Vol * P->Vol / 2) * P->Temps;
	double V = P->Vol * sqrt(P->Temps);
	G = Gauss(M, V);
}
/*************************************************************************************************/
B_S::B_S(const B_S & M)
{
	S_0 = M.S_0;
	P = M.P;
	G = M.G;
}
/*************************************************************************************************/
double B_S::StdDev() const
{
	double sigma_2 = G.StdDev() * G.StdDev();
	double Var = (exp(sigma_2) - 1) * exp(2 * G.E_Init() + sigma_2);
	return S_0 * sqrt(Var);
}




