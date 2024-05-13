#include "Scenar.hpp"

using namespace std;


/**************************************************************************************************

Fonctions utiles

**************************************************************************************************/

/*	Densite d une normale centree reduite	*/
double Phi(double);

/*	Cherche le nombre de simulations a atteindre dans l algorithme Adaptive	*/
unsigned int Target(const Sample & S, double c, unsigned int N_Actu, unsigned int N_Simu, unsigned int Tau_e);

/*	Ajoute une simulation au premier element d un echantillon trie dont les fiabilites sont stockees dans Fiab,
	et le remet a sa place dans le vecteur (entre S[0] et S[n])	*/
void Add_Simu_Sort_Fiab(Sample & S, double * Fiab, unsigned int n, double c, double x_0, Modele * inner, Payoff * P);

/*	Ajoute une simulation au dernier element d un echantillon inversement trie par nombre de simulations interne,
	et le remet a sa place dans le vecteur (entre S[n_0] et S[n])	*/
bool Add_Simu_RSort_M(Sample & S, unsigned int n_0, unsigned int n, unsigned int m_0, double c, double x_0, Modele * inner, Payoff * P);

/*	Calcul l estimation de alpha pour un echantillon et un seuil donnes	*/
double Alpha(const Sample & S, double c);

/*	Calcul l estimation de alpha_bar pour un echantillon et un seuil donnes	*/
double Alpha_Bar(const Sample & S, double c);

/**************************************************************************************************

Dans nos algorithmes, nous aurons toujours besoin des parametres suivants qui definissent le modele:
	c		seuil de perte
	x_0		Valeur initiale du "tradeable" detenu
	outer	Modele suivi par le sous-jacent entre 0 et Tau
	inner	Modele suivi par le sous-jacent entre Tau et T
	P		Payoff du "tradeable" en T

**************************************************************************************************/

/**************************************************************************************************

Algorithme Uniforme:
	m		nombre de simulations internes par scenario
	n		nombre de scenarios

**************************************************************************************************/

double Uniform(unsigned int m, unsigned int n, double c, double x_0, Modele * outer, Modele * inner, Payoff * P);

/**************************************************************************************************

Algorithme Sequential:
	m_0		nombre initial de simulations internes par scenario
	m_bar	nombre moyen de simulations internes par scenario souhaite a la fin de l algorithme
	n		nombre de scenarios

**************************************************************************************************/

double Sequential(unsigned int m_0, unsigned int m_bar, unsigned int n, double c, double x_0, Modele * outer, Modele * inner, Payoff * P);

/**************************************************************************************************

Algorithme Threshold:
	gamma	seuil de fiabilite minimum souhaite par scenario
	n		nombre de scenarios

**************************************************************************************************/

double Threshold(double gamma, unsigned int n, double c, double x_0, Modele * outer, Modele * inner, Payoff * P);

/**************************************************************************************************

Algorithme Adaptive:
	m_0		nombre initial de simulations internes par scenario
	n_0		nombre initial de scenarios
	Tau_e	nombre de simulations ajoutees par etape
	k		nombre total de simulations internes souhaitees a la fin de l algorithme

**************************************************************************************************/

double Adaptive(unsigned int m_0, unsigned int n_0, unsigned int Tau_e, unsigned int k, double c, double x_0, Modele * outer, Modele * inner, Payoff * P);





