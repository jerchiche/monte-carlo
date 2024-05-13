#include "Modeles.hpp"

using namespace std;


/**************************************************************************************************

Payoff:	Donne une simulation du payoff actualise d'un "tradable" (Action, Call,...) dont le
		sous-jacent est modelise par un Modele (On n enregistre pas le chemin du sous-jacent,
		donc on ne peut pas utiliser de Payoff path-dependent)

**************************************************************************************************/

class Payoff
{
public:
	virtual double operator()(Modele *) = 0;

	// Destructeurs
	virtual ~Payoff() {}
};

/**************************************************************************************************

Action:	Simule le Payoff d une simple action = S_T

**************************************************************************************************/

class Action : public Payoff
{
public:
	double operator()(Modele * M)
		{return (*M)();}

	// Destructeurs
	~Action() {}
};

/**************************************************************************************************

Put:	Simule Payoff d un Put = (K - S_T)+

**************************************************************************************************/

class Put : public Payoff
{
private:
	double K;
public:
	Put(double Strike)
		: K(Strike) {}
	double operator()(Modele *);

	// Destructeurs
	~Put() {}
};

/**************************************************************************************************

Call:	Simule le Payoff d un Call = (S_T - K)+

**************************************************************************************************/

class Call : public Payoff
{
private:
	double K;
public:
	Call(double Strike)
		: K(Strike) {}
	double operator()(Modele *);

	// Destructeurs
	~Call() {}
};

/**************************************************************************************************

Digitale: Simule le Payoff d une Digitale = Indicatrice(S_T > K)

**************************************************************************************************/

class Digitale : public Payoff
{
private:
	double K;
public:
	Digitale(double Strike)
		: K(Strike) {}
	double operator()(Modele *);

	// Destructeurs
	~Digitale() {}
};

/*************************************************************************************************/



