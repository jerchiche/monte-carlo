#include "Estimateurs.hpp"
#include <ctime>
#include <fstream>

using namespace std;


int main()
{
	srand(time(NULL));
	rand();
	
	/************************************************************************************************/
    
	double X_0 = 1.669;
	double S_0 = 100;
	double volatilite = 0.2;
	double Taux_SR = 0.03;
	double Taux_Risque = 0.08;
	double Strike = 95;
	double Maturity = 0.25;
	double Tau = 1 / (double)52;
    
	double c = 0.859;	// 10% : 0.859; 1% : 1.221; 0.1% : 1.390;
	
	/************************************************************************************************/
	
	unsigned int m_0 = 50;
	unsigned int n_0 = 50;
	unsigned int Tau_e = 100000;
	unsigned int k = 4000000;
    
	unsigned int Nb_It = 100;
	
	/************************************************************************************************/
	
	time_t tBegin, tIte;
	ofstream Ecrire;
    
    Param_BS P_Outer(Taux_Risque, volatilite, Tau);
	Param_BS P_Inner(Taux_SR, volatilite, Maturity - Tau);
	
	B_S outer(P_Outer, S_0);
	B_S inner(P_Inner, 0);
	
	Put P_Off = Put(Strike);
    
	/************************************************************************************************/
    
	tBegin = time(NULL);
	cout << "Calcul avec l'algo Adaptive : " << endl;
	Ecrire.open("PutAdap.txt");
	for(unsigned int i=1; i<Nb_It+1; i++)
	{
		tIte = time(NULL);
		Ecrire << Adaptive(m_0, n_0, Tau_e, k, c, X_0, &outer, &inner, &P_Off) << endl;
		cout << "Iteration " << i << ": " << difftime(time(NULL), tIte) << " secondes" << endl;
	}
	Ecrire.close();
	cout << "Temps de calcul : " << difftime(time(NULL), tBegin) << " secondes" << endl << endl;
	
	/************************************************************************************************/
	
	return 0;
}


