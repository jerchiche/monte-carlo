#include "Estimateurs.hpp"
#include <ctime>
#include <fstream>

using namespace std;


int main()
{
	srand(time(NULL));
	rand();
	
	/************************************************************************************************/
    
	double X_0 = 0;
	double sigma_outer = 1;
	double sigma_in = 5;
	double c = 1.282;   // 10% :  1.282, 1% : 2.326, 0.1% : 3.090;
	
    /************************************************************************************************/
    
	unsigned int m_0 = 2;
	unsigned int m_bar = 400;
	unsigned int n = 5000;
    
	unsigned int Nb_It = 100;
	
	/************************************************************************************************/
	
	time_t tBegin, tIte;
	ofstream Ecrire;
	Gauss outer(X_0, sigma_outer);
	Gauss inner(0, sigma_in);
	Action A_Simple;
    
	/************************************************************************************************/
    
	tBegin = time(NULL);
	cout << "Calcul avec l'algo Sequential : " << endl;
	Ecrire.open("GaussSeq.txt");
	for(unsigned int i=1; i<Nb_It+1; i++)
	{
		tIte = time(NULL);
		Ecrire << Sequential(m_0, m_bar, n, c, X_0, &outer, &inner, &A_Simple) << endl;
		cout << "Iteration " << i << ": " << difftime(time(NULL), tIte) << " secondes" << endl;
	}
	Ecrire.close();
	cout << "Temps de calcul : " << difftime(time(NULL), tBegin) << " secondes" << endl << endl;
	
	/************************************************************************************************/
	
	return 0;
}
