/*******************************************************************************
 *
 *                     HEADER INFORMATION            
 *
 * Filename      : main.cpp
 * Header File(s): Poly.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
#include <iostream>
#include "Poly.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/time.h>

int main ( int argc, char * argv[] )
{
    srand(time(NULL));
    struct timespec start, stop;
    double avg_accum;;     
    vector<int> a, b;
    Poly A, B, C, D, E, F;
    ofstream myfile;
    
    for ( int i = 4; i < 65537; i *= 2 )
    {    
        myfile.open ("raw", fstream::out | fstream::app);       
        
        for ( int j = 0; j < i; j++ )
        {
            a.push_back((rand() % (j + 1)) + 1);
            b.push_back((rand() % (j + 1)) + 1);
        }
        A.set_coeffs(a);
        B.set_coeffs(b);

        avg_accum = 0;
        for ( int k = 0; k < 5; k++ )
        {
            clock_gettime( CLOCK_REALTIME, &start);
            C = A+B; // brute
            clock_gettime( CLOCK_REALTIME, &stop);
            avg_accum += ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)1000000000L;
        }
        myfile << fixed << setprecision(10) << avg_accum/5.0;  

        avg_accum = 0;
        for ( int k = 0; k < 5; k++ )
        {
            clock_gettime( CLOCK_REALTIME, &start);    
            D = A/B; // iterative
            clock_gettime( CLOCK_REALTIME, &stop);
            avg_accum += ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)1000000000L;
        }
        myfile << "," << fixed << setprecision(10) << avg_accum/5.0;
        
        avg_accum = 0;
        for ( int k = 0; k < 5; k++ )
        {
            clock_gettime( CLOCK_REALTIME, &start);    
            E = A/B; // recursive
            clock_gettime( CLOCK_REALTIME, &stop);
            avg_accum += ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)1000000000L;
        }
        myfile << "," << fixed << setprecision(10) << avg_accum/5.0;
        
        avg_accum = 0;
        for ( int k = 0; k < 5; k++ )
        {
            clock_gettime( CLOCK_REALTIME, &start);    
            F = A/B; // recursive (compact)
            clock_gettime( CLOCK_REALTIME, &stop);
            avg_accum += ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double)1000000000L;
        }
        myfile << "," << fixed << setprecision(10) << avg_accum/5.0;
        
        myfile << "," << i << endl;        
        
        myfile.close();
    }
    
    return 0;
}
