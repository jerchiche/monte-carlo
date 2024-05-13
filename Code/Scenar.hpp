#include <vector>
#include "Payoff.hpp"

using namespace std;


/**************************************************************************************************

Scenario:	Stock une simulation externe (valeur S_Tau du sous jacent en Tau), le nombre de
			simulations internes, ainsi que la perte moyennes sur les simulations internes

Cmp_Fiab:	Objet fonctionnel pour comparer deux scenarios en fonction de leurs fiabilit¨¦s

**************************************************************************************************/

class Scenario
{
protected:
	unsigned int m;
	double S_Tau, L;
	
public:
	// Constructeurs
	Scenario()
		: m(0), S_Tau(0), L(0) {}
	Scenario(unsigned int m, double S_Tau, double X_0, Modele * inner, Payoff * P);
	Scenario(const Scenario &);

	// Destructeurs
	~Scenario() {}
	
	// Accesseurs et Mutateurs
	unsigned int Lire_M() const
		{return m;}
	double Loss() const
		{return L;}
	
	// Autres fonctions
	void Add_Simu(double X_0, Modele * M, Payoff * P);	// Ajoute une simulation interne au scenario
	double Fiabilite(double, Modele *) const;	// Calcul la fiabilite du scenario (signee, sans valabs)
	friend bool Cmp_M(const Scenario &, const Scenario &);	//Compare deux scenarios par rapport a leur m
};

/*************************************************************************************************/

struct Cmp_Fiab
{
private:
	double c;
	Modele * M;
public:
	Cmp_Fiab(double c, Modele * M)
		: c(c), M(M) {}

	// Destructeurs
	~Cmp_Fiab() {}
	
	bool operator()(const Scenario &, const Scenario &) const;
};

/**************************************************************************************************

Sample: Echantillon de scenarios avec
	X_0: 	Valeur initial du portefeuille (en general, = prix d un echangeable)
	Sc: 	Vecteur de Scenarios
	outer: 	Modele suivi par le sous jacent avant Tau (ne doit pas changer)
	inner: 	Modele suivi par le sous jacent entre Tau et T (on le change en fonction de la valeur
			initial du Scenario sur lequel on travaille)
	P: 		Payoff en T

**************************************************************************************************/

class Sample
{
protected:
	double X_0;
	vector<Scenario> Sc;
	Modele * outer;
	Modele * inner;
	Payoff * P;
	
public:
	// Constructeurs
	Sample()
		: X_0(), Sc(vector<Scenario>()), outer(NULL), inner(NULL), P(NULL) {}
	Sample(unsigned int n_0, unsigned int m_0, double X_0, Modele * outer, Modele * inner, Payoff * P);
	Sample(const Sample &);

	// Destructeurs
	~Sample() {}
	
	// Accesseurs et Mutateurs
	vector<Scenario> Lire_Sc() const
		{return Sc;}
	Modele * Lire_In() const
		{return inner;}
	Scenario operator[](unsigned int k) const
		{return Sc[k];}
	Scenario & operator[](unsigned int k)
		{return Sc[k];}
	
	// Autres fonctions
	void Add_Scenar(unsigned int m, unsigned int n=1);	// Ajoute n scenarios avec pour chacun, m simulations internes
};


