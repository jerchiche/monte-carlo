CC = g++
CFLAGS = -Wall -O3

gauss: Gauss.exe
	
gaussf: GaussF.exe
	
put: Put.exe
	
putf: PutF.exe
	

clean:
	rm -rf *.o *.exe
	

Modeles.o: Modeles.cpp Modeles.hpp
	$(CC) $(CFLAGS) -c Modeles.cpp
	
Payoff.o: Payoff.cpp Payoff.hpp Modeles.hpp
	$(CC) $(CFLAGS) -c Payoff.cpp
	
Scenar.o: Scenar.cpp Scenar.hpp Modeles.hpp Payoff.hpp
	$(CC) $(CFLAGS) -c Scenar.cpp
	
Estimateurs.o: Estimateurs.cpp Estimateurs.hpp Modeles.hpp Payoff.hpp Scenar.hpp
	$(CC) $(CFLAGS) -c Estimateurs.cpp
	

Gauss.exe: Modeles.o Payoff.o Scenar.o Estimateurs.o Gaussian.cpp
	$(CC) $(CFLAGS) Modeles.o Payoff.o Scenar.o Estimateurs.o Gaussian.cpp -o Gauss.exe
	
GaussF.exe: Modeles.o Payoff.o Scenar.o Estimateurs.o GaussFile.cpp
	$(CC) $(CFLAGS) Modeles.o Payoff.o Scenar.o Estimateurs.o GaussFile.cpp -o GaussF.exe
	
Put.exe: Modeles.o Payoff.o Scenar.o Estimateurs.o Put.cpp
	$(CC) $(CFLAGS) Modeles.o Payoff.o Scenar.o Estimateurs.o Put.cpp -o Put.exe
	
PutF.exe: Modeles.o Payoff.o Scenar.o Estimateurs.o PutFile.cpp
	$(CC) $(CFLAGS) Modeles.o Payoff.o Scenar.o Estimateurs.o PutFile.cpp -o PutF.exe