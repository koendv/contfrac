/*
 * Continued fractions algorithm.
 * Convert a decimal number to a fraction.
 * Koen De Vleeschauwer, 2013. GPL license.
 *
 * The continued fractions algorithm can be traced back to Euclid (approx. 300 BC). 
 */

#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>

using namespace std;

void printfraction(long int n, long int d, long int x, long int y);

int main()
{

  char ch;
  
  do {
    /*
     * read positive floating point number as fraction x/y
     */
  
    long int x = 0;
    long int y = 1;
    long int max_denom;
    int precision = 1;
  
    cout << "enter ratio: ";
    /* skip whitespace */
    while (!('0' <= cin.peek()) && (cin.peek() <= '9') && (cin.peek() != '.'))
      cin.ignore(1);
    /* read integer part */
    while (('0' <= cin.peek()) && (cin.peek() <= '9')) {
      char digit;
      cin >> digit;
      x = x * 10 + (digit - '0');
      precision++;
      }
    if (cin.peek() == '.') {
      cin.ignore(1, '.'); // skip decimal point
      /* read fractional part */
      while (('0' <= cin.peek()) && (cin.peek() <= '9')) {
        char digit;
        cin >> digit;
        x = x * 10 + (digit - '0');
        y = y * 10;
        precision++;
        }
      } 

    /* use as many digits in the output as in the input */
    cout.precision(precision);

    /*
     * end condition
     */ 
    cout << "enter maximum value for nominator and denominator (0 for no max.): ";
    cin >> max_denom;
    if (max_denom <= 0) max_denom = std::numeric_limits<long int>::max();

    /* 
     * See "Continued Fraction" in Wolfram Mathworld.
     * cn = pn/qn are the convergents
     * rn = xn/yn are the remainders
     * x/y is the original decimal number.
     */

    long int x0 = x;
    long int y0 = y;
    long int p0 = 0;
    long int q0 = 1;
    long int p1 = 1;
    long int q1 = 0;

    bool notfirst = false;

    do {
      /* calculate next convergent */
      long int a = x0 / y0; /* integer division */
      long int p2 = a * p1 + p0;
      long int q2 = a * q1 + q0;

      /* calculate next remainder r = 1/(r-a) = y0/(x0-a*y0) */
      long int x1 = y0;
      long int y1 = x0 - a * y0;

      /* print best rational approximations */
      if (notfirst) 
        for (long int n = a/2; n < a; ++n) {
          long int pr = n * p1 + p0;
          long int qr = n * q1 + q0; 
          if ((pr > max_denom) || (qr > max_denom)) break;
          /* check pr/qr is an improvement over p1/q1 */
          if (labs(qr * q1 * x - y * q1 * pr) < labs(qr * q1 * x - y * qr * p1)) {
            printfraction(pr, qr, x, y);
            }
          }

      /* print convergent */
      if ((p2 > max_denom) || (q2 > max_denom)) break;
      printfraction(p2, q2, x, y);

      /* advance */
      p0 = p1;
      p1 = p2;
      q0 = q1;
      q1 = q2;
      x0 = x1;
      y0 = y1;
      notfirst = true;

      } while (y0 > 0);

    cout << "Another (y/n)?";
    for (ch = ' '; (ch != 'y') && (ch != 'n'); cin >> ch);
  } 
  while (ch == 'y');
}

/*
 * print the fraction. 
 * As a sanity check, floating point math is used to calculate the difference between the 
 * rational approximation and the original floating point number.
 */
void printfraction(long int n, long int d, long int x, long int y) {
  long double decnum = (long double) x/(long double) y;
  long double f = (long double) n/(long double) d;
  long double delta = fabs(decnum - f);
  cout << n << "/" << d << " = " << f << " (delta = " << delta <<  ")" << endl;
  return;
}

/* not truncated */
