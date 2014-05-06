/*******************************************************************************
 *
 *                     HEADER INFORMATION            
 *
 * Filename      : Poly.cpp
 * Header File(s): Poly.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <valarray>
#include "Poly.hpp"


/************************************
 * Namespaces 
 ************************************/
using namespace std;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Constructor  : 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Poly::Poly ( void ) { ; }
/*******************************************************************************
* Constructor  : 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Poly::Poly ( vector<int> a ) { coeff = a; }
/*******************************************************************************
* Deconstructor: 
* Description  : 
* Arguments    : 
* Remarks      : 
********************************************************************************/
Poly::~Poly ( void ) { coeff.clear(); }
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
Poly& Poly::operator=( const Poly& obj ) 
{
    if ( this != &obj ) // prevent self-assignment
    {
        vector<int> tmp = obj.get_coeffs();
        coeff.swap(tmp);
    }
    return *this;
}
/*******************************************************************************
* Constructor  : (Operator)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : Recursive FFT
********************************************************************************/
Poly& Poly::operator*( const Poly& obj ) 
{
    Poly * r = new Poly();
    int size = coeff.size();
    vector< complex<double> > y1(size*2), y2(size*2), y3(size*2);
    vector<int> a = coeff, b = obj.get_coeffs();

    for( int i = 0; i < size; i++ )
    {
        y1[i] = complex<double>(a[i]);
        y2[i] = complex<double>(b[i]);
    }
    
    /* convert from coeff to point */
    y1 = recurrsive_fft(y1,false);
    y2 = recurrsive_fft(y2,false);
    
    /* multi */
    for( int i = 0; i < y1.size(); i++ )
    {
        y3[i] = y1[i]*y2[i];
    }
    
    /* convert from point to coeff */
    y3 = recurrsive_fft(y3,true);
     
    a.resize(size*2);
    
    for ( int i = 0; i < a.size(); i++ )
    {
        a[i] = int(round(real((y3[i]/complex<double>(y3.size())))));
    }   

    r->set_coeffs(a);
    
    return *r;
}
/*******************************************************************************
* Constructor  : (Operator)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : Brute force multiply
********************************************************************************/
Poly& Poly::operator+( const Poly& obj ) 
{
    int i,j,k,size=coeff.size();
    Poly * r = new Poly();
    
    for( int i = 0; i < size; i++ )
    {
        coeff.push_back(0); // padd
    }
    
    vector<int> b = obj.get_coeffs();
    b.resize(size*2,0);

    vector<int> c( size*2 );

    for(j = 0; j < c.size(); j++ )
    {
        for( k = 0; k < j+1; k++ )
        {
            c[j] += coeff[k]*b[j-k];
        }
    }
    
    for(i=0;i<size;i++)
    {
        coeff.pop_back(); // remove padd
    }
    
    c.resize(size*2);
    
    r->set_coeffs(c);
    
    return *r;
}
/*******************************************************************************
* Constructor  : (Operator)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : Iterative FFT
********************************************************************************/
Poly& Poly::operator-( const Poly& obj ) 
{
    Poly * r = new Poly();
    int size = coeff.size();
    vector< complex<double> > y1(size*2), y2(size*2), y3(size*2);
    vector<int> a = coeff, b = obj.get_coeffs();

    for( int i = 0; i < size; i++ )
    {
        y1[i] = complex<double>(a[i]);
        y2[i] = complex<double>(b[i]);
    }
    
    /* convert from coeff to point */
    y1 = iterative_fft(y1,false);    
    y2 = iterative_fft(y2,false);
    
    /* multi */
    for( int i = 0; i < y1.size(); i++ )
    {
        y3[i] = y1[i]*y2[i];
    }
    /* convert from point to coeff */
    y3 = iterative_fft(y3, true);

    a.resize(size*2);
    
    for ( int i = 0; i < a.size(); i++ )
    {
        a[i] = int(round(real((y3[i]/complex<double>(y3.size())))));
    }   

    r->set_coeffs(a);
    
    return *r;
}
/*******************************************************************************
* Constructor  : (Operator)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : (Compact) Recursive FFT
********************************************************************************/
Poly& Poly::operator/( const Poly& obj ) 
{
    Poly * r = new Poly();
    int size = coeff.size();
    valarray< complex<double> >  y1(size*2), y2(size*2), y3(size*2);
    vector<int> a = coeff, b = obj.get_coeffs();
    
    for( int i = 0; i < size; i++ )
    {
        y1[i] = complex<double>(a[i]);
        y2[i] = complex<double>(b[i]);
    }
    
    compact_recurisve_fft(y1);
    compact_recurisve_fft(y2); 
    
    for( int i = 0; i < y3.size(); i++ )
    {
        y3[i] = y1[i]*y2[i];
    }    
    
    compact_recurrsive_fft_inverse(y3);
    
    a.resize(size*2);
    
    for( int i = 0; i < a.size(); i++ )
    {
        a[i] = y3[i].real();
    }
    
    r->set_coeffs(a);
    
    return *r;
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
const int Poly::operator[]( size_t idx ) 
{
    if ( idx >= coeff.size() )
        return 0;

    return coeff[idx];
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
string Poly::display ( void )
{
    ostringstream s;
    int i;
    
    for ( i = 0; i < coeff.size()-1; i++ )
        s << coeff[i] <<",";
    s << coeff[i];
    
    return s.str();
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
vector<int> Poly::get_coeffs ( void ) const
{
    return coeff;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Poly::set_coeff_at ( unsigned int idx, int value )
{
    if ( idx >= coeff.size() )
        return;
    
    coeff[idx] = value;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Poly::set_coeffs ( vector<int> value )
{
    coeff = value;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
vector< complex<double> > Poly::recurrsive_fft ( vector< complex<double> > a, 
                                                 bool inverse )
{
    vector< complex<double> > y;
    int n = a.size();
    
    if ( n == 1 )
    {
        return a;
    }
    
    vector< complex<double> > y0,y1;
    
    complex<double> omega_n(cos(2*M_PI/n),(inverse?-1.0:1.0)*sin(2*M_PI/n));
    complex<double> omega(1);
    
    vector< complex<double> > a0;
    for ( int i = 0; i < a.size(); i+=2 )
        a0.push_back(a[i]);
    
    vector< complex<double> > a1;
    for ( int i = 0; i < a.size(); i+=2 )
        a1.push_back(a[i+1]);

    y0 = recurrsive_fft(a0,inverse);
    y1 = recurrsive_fft(a1,inverse);
    
    y.resize(n);
    
    for ( int k = 0; k < n/2; k++ )
    {
        y[k]     = y0[k] + omega*y1[k];
        y[k+n/2] = y0[k] - omega*y1[k];
        omega    = omega*omega_n;
    }
    
    return y;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
vector< complex<double> > Poly::iterative_fft ( vector< complex<double> > a, 
                                                bool inverse )
{
    int n = a.size();
    vector< complex<double> > A = bit_reverse_copy(a,a.size()/2-1);
    
    for ( int s = 1; s <= log2(n); s++ )
    {
        int m = pow(2,s);
        complex<double> omega_m(cos(2*M_PI/m),(inverse?-1.0:1.0)*sin(2*M_PI/m));
        for ( int k = 0; k < n-1; k += m )
        {
            complex<double> omega(1);
            for ( int j = 0; j < m/2; j++ )
            {
                complex<double> t (omega*A[k+j+m/2]), u(A[k+j]);
                A[k+j]     = u + t;
                A[k+j+m/2] = u - t;
                omega      = omega*omega_m;
            }
        }
    }
    
    return A;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
vector< complex<double> > Poly::bit_reverse_copy ( vector< complex<double> > a, 
                                                   int bits )
{
    vector< complex<double> > y(a.size());
    for ( unsigned short k = 0; k < a.size(); k++ )
    {
        y[bit_reverse(k,bits)] = a[k];
    }
    return y;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
unsigned int Poly::bit_reverse ( unsigned int n, unsigned int bits )
{
    unsigned int nrev  = n,
                 N     = 1 << bits, 
                 count = bits-1;
    
    for ( n>>=1; n; n>>=1 )
    {
        nrev <<= 1;
        nrev |= n & 1;
        count--;
    }

    nrev <<= count;
    nrev &= N - 1;

    return nrev;
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : http://rosettacode.org/wiki/Fast_Fourier_transform
********************************************************************************/
void Poly::compact_recurisve_fft ( valarray< complex<double> >& x )
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    valarray< complex<double> > even = x[slice(0, N/2, 2)];
    valarray< complex<double> >  odd = x[slice(1, N/2, 2)];

    // conquer
    compact_recurisve_fft(even);
    compact_recurisve_fft(odd);
    
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        complex<double> t = polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : http://rosettacode.org/wiki/Fast_Fourier_transform
********************************************************************************/
void Poly::compact_recurrsive_fft_inverse ( valarray< complex<double> >& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    compact_recurisve_fft( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}
