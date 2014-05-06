/*******************************************************************************
 * Filename      : Poly.h
 * Source File(s): Poly.cpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified : 
 * Modifier(s)   : 
 *******************************************************************************/
#ifndef POLY_H
#define	POLY_H

/*******************************************************************************
*                                   INCLUDES
********************************************************************************/
#include <vector>
#include <string>
#include <complex>
#include <valarray>

/*******************************************************************************
*                                    DATATYPES
********************************************************************************/

/*******************************************************************************
*                                    EXTERNS
********************************************************************************/

/*******************************************************************************
*                                    DEFINES
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
using namespace std;

class Poly
{
    public: 
        /* constructors */
        Poly ( void ); /* default */
        Poly ( std::vector<int> );
        Poly& operator= ( const Poly& ); /* assign */
        Poly& operator* ( const Poly& );
        Poly& operator+ ( const Poly& );
        Poly& operator- ( const Poly& );
        Poly& operator/ ( const Poly& );

        const int operator[] ( std::size_t );
        ~Poly ( void );

        /* functions */
        std::string      display      ( void );
        std::vector<int> get_coeffs   ( void ) const;
        void             set_coeffs   ( std::vector<int> );
        void             set_coeff_at ( unsigned int, int );

        /* algorithm */
        vector< complex<double> > recurrsive_fft ( vector< complex<double> >, 
                                                   bool );            

        void compact_recurisve_fft ( valarray< complex<double> >& );
        void compact_recurrsive_fft_inverse ( valarray< complex<double> >& );

        vector< complex<double> > iterative_fft ( vector< complex<double> >, 
                                                  bool );
        vector< complex<double> > bit_reverse_copy ( vector< complex<double> >, 
                                                     int );
        unsigned int bit_reverse ( unsigned int, unsigned int );
        /* variables */

    private:
        std::vector<int> coeff;
            
            
};
#endif
