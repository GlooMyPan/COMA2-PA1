#include <iostream>
#include <iomanip>			// f¨¹r setprecision()
#include <cstdlib>			// f¨¹r atoi()
#include <cmath>			// f¨¹r sqrt()
#include "Stoppuhr.h"


/***  berechne Primzahlentabelle  ***/

// berechne die Anzahl Teiler von n
// naive Version
size_t anzahlTeilerNaiv ( size_t n )
{
    size_t anzahl = 0;
	for (size_t k = 1; k <= n; ++k)
	    if (n % k == 0)
	        ++anzahl;
    return anzahl;

}


// berechne die Anzahl Teiler von n
// verbesserte Version
size_t anzahlTeilerBesser ( size_t n )
{
	size_t wurzel = sqrt(n), anzahl = 0;
	for (size_t k = 1; k <= wurzel; ++k)
	    if (n % k == 0)
	        anzahl += 2;

    if (wurzel * wurzel == n)
        --anzahl;

    return anzahl;
}


// berechne die Anzahl Teiler von n
// Version mit Division von n
size_t anzahlTeilerDiv ( size_t n )
{
    size_t anzahl = 1, p = 2;
    size_t k;
    while (n > 1)
    {
        k = 1;
        while (n % p == 0)
        {
            n /= p;
            ++k;
        }
        p > 2 ? p += 2 : ++p;
        anzahl *= k;
    }
    return anzahl;
}  // anzahlTeilerDiv()


/***  Hauptprogramm  *************************************************/

int main ( int narg, char* argv[] )
{
	if ( narg < 3 )
	{
		cout << "Usage: " << argv[ 0 ] << "  v  n"		 << endl ;
		cout << "       v: Kennzahl des Verfahrens"		 << endl ;
		cout << "       n: natuerliche Zahl"			 << endl ;
		cout << "Sucht eine nat. Zahl <= n mit den meisten Teilern" << endl ;
		cout << "unter Verwendung des Verfahrens Nr. v." << endl ;
		cout << "v = 1: naive Teilerberechnung"		     << endl ;
		cout << "    2: verbesserte Teilerberechnung"    << endl ;
		cout << "    3: Teilerberechnung mit Division"   << endl ;

		return 0 ;
	}

/***  setze Parameter  ***/

	size_t verf = atoi( argv[ 1 ] ) ;
	size_t nMax = atoi( argv[ 2 ] ) ;

	if ( verf < 1  ||  verf > 3 )
	{
		cout << "Es gibt keine Verfahrensnummer " << verf << endl ;
		return 0 ;
	}

	// init. Zeiger auf die gew¨¹schte Funktion
	auto anzahlTeiler = anzahlTeilerNaiv ;
	if ( verf == 2 )
		anzahlTeiler = anzahlTeilerBesser ;
	if ( verf == 3 )
		anzahlTeiler = anzahlTeilerDiv ;

/***  bearbeite Aufgabe  ***/

	size_t const NITER = 3 ;
	size_t maxTeiler = 0 ;
	size_t maxZahl   = 0 ;

    Stoppuhr uhr;
    for(size_t i = 0; i < NITER; ++i)
    {
        for ( size_t n = 1 ;  n <= nMax ;  ++n )
        {
            size_t anzTeiler = anzahlTeiler( n ) ;

            if ( maxTeiler < anzTeiler )
            {
                maxTeiler = anzTeiler ;
                maxZahl   = n ;
            }
        }
    }
    double laufzeit =  uhr.stopp() / NITER;

	cout << maxZahl << " hat " << maxTeiler << " Teiler" << endl ;
    cout << "Laufzeit: " << laufzeit << endl;

	return 0 ;

}  // main()

