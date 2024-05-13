#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;


/**************************************************************************************************

Modeles:	Sert a simuler l evolution d un sous jacent S

**************************************************************************************************/

class Modele
{
public:
	virtual double operator()() = 0;		// Simule une trajectoire du sous-jacent
	
	virtual void Mod_S_0(double) = 0;		// Modifie la valeur initiale du sous-jacent
	virtual double E_Init() const = 0;		// Lit la valeur initiale du sous-jacent
	
	virtual double StdDev() const = 0;		// Calcul l ecart type
	virtual double Actualisation() const	// Renvoie l'actualisation qui vaut 1 par defaut
		{return 1;}

	// Destructeurs
	virtual ~Modele() {}
};

/**************************************************************************************************

Gauss(m, sigma):	La loi d un sous jacent suivant une loi Normale(m, sigma)

**************************************************************************************************/

class Gauss : public Modele
{
private:
	double Mu, Sigma;
	
public:
	// Constructeurs
	Gauss(double moyenne=0, double S=1)
		: Mu(moyenne), Sigma(S) {}
	Gauss(const Gauss &);
	
	// Destructeurs
	~Gauss() {}
	
	// Simulation
	double operator()();
	
	// Accesseurs / Mutateurs
	void Mod_S_0(double New_S_0)
		{Mu = New_S_0;}
	double E_Init() const
		{return Mu;}
	
	double StdDev() const
		{return Sigma;}
};

static Gauss G_Standard = Gauss();

/**************************************************************************************************

Param_BS:		L ensemble des parametre qui servent a definir un Modele de Black Scholes

B_S(S_0, P):	La loi d un sous jacent suivant un Modele de Black Scholes avec comme parametres
				ceux pointes par P

**************************************************************************************************/

struct Param_BS
{
private:
	double Mu, Vol, Temps;
	
public:
	Param_BS()
		: Mu(0), Vol(0), Temps(0) {}
	Param_BS(double mu, double vol, double temps)
		: Mu(mu), Vol(vol), Temps(temps) {}
	Param_BS(const Param_BS &);
	
	// Destructeurs
	~Param_BS() {}
	
	friend class B_S;
};

/*************************************************************************************************/

class B_S : public Modele
{
private:
	double S_0;
	const Param_BS * P;
	Gauss G;
	
public:
	// Constructeurs
	B_S()
		: S_0(0), P(NULL), G(Gauss()) {}
	B_S(const Param_BS, double);
	B_S(const B_S &);

	// Destructeurs
	~B_S() {}
	
	// Simulation
	double operator()()
		{return S_0 * exp(G());}
	
	// Mutateurs
	void Mod_S_0(double x)
		{S_0 = x;}
	double E_Init() const
		{return S_0;}
	
	double StdDev() const;
	double Actualisation() const
		{return exp(-P->Temps * P->Mu);}
};





