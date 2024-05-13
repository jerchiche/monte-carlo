#include "Payoff.hpp"

using namespace std;


/**************************************************************************************************

Put

**************************************************************************************************/

double Put::operator()(Modele * M)
{
	double S_T = (*M)();
	double Payoff = (S_T < K) ? (K - S_T) : 0;
	return M->Actualisation() * Payoff;
}

/**************************************************************************************************

Call

**************************************************************************************************/

double Call::operator()(Modele * M)
{
	double S_T = (*M)();
	double Payoff = (S_T > K) ? 0 : (S_T - K);
	return M->Actualisation() * Payoff;
}

/**************************************************************************************************

Autres types de Payoffs possibles

**************************************************************************************************/

double Digitale::operator()(Modele * M)
{
	double S_T = (*M)();
	double Payoff = (S_T < K) ? 0 : 1;
	return M->Actualisation() * Payoff;
}






