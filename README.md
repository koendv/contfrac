# Contfrac

The program solves the following kind of problems:
* You have a gearbox. You know the gear ratio and the maximum number of teeth of a gear. You want tooth count. 
* You have a PLL phase-locked loop. You know the ratio between incoming and outgoing frequency and the size of multiplier and divider registers. You want to know multiplier and divider.
* You have a transformer. You know the ratio between incoming and outgoing voltages and the maximum number of windings. You need to know the number of windings of primary and secondary.

Mathematically speaking the problem is finding rational approximations to real numbers.

## Example 1
The design ratio of a gearbox is 1.41421356. Gears have between 10 and 100 teeth. Determine tooth count.

    $ ./contfrac
    enter ratio: 1.41421356
    enter maximum value for nominator and denominator (0 for no max.): 100
    1/1 = 1 (delta = 0.41421356)
    3/2 = 1.5 (delta = 0.08578644)
    4/3 = 1.333333333 (delta = 0.08088022667)
    7/5 = 1.4 (delta = 0.01421356)
    17/12 = 1.416666667 (delta = 0.002453106667)
    24/17 = 1.411764706 (delta = 0.002448854118)
    41/29 = 1.413793103 (delta = 0.0004204565517)
    99/70 = 1.414285714 (delta = 7.215428571e-05)
    Another (y/n)?n
    $

Four solutions fit the specifications: 17/12, 24/17, 41/29, 99/70. A possible choice is one gear with 41 teeth, and one with 29. The gears will wear out evenly, as the greatest common denominator of the teeth counts is 1.

## Example 2 

A PLL with an incoming frequency of 1 MHz and 8-bit registers for multiplier and divider is used in a radio. Which multiplier and divider settings need to be used to synthesize 1265 kHz?

    $ ./contfrac
    enter ratio: 1.265
    enter maximum value for nominator and denominator (0 for no max.): 256
    1/1 = 1 (delta = 0.265)
    3/2 = 1.5 (delta = 0.235)
    4/3 = 1.3333 (delta = 0.068333)
    5/4 = 1.25 (delta = 0.015)
    14/11 = 1.2727 (delta = 0.0077273)
    19/15 = 1.2667 (delta = 0.0016667)
    43/34 = 1.2647 (delta = 0.00029412)
    105/83 = 1.2651 (delta = 6.0241e-05)
    148/117 = 1.265 (delta = 4.2735e-05)
    253/200 = 1.265 (delta = 0)
    Another (y/n)?n
    $

To synthesize 1265 kHz from a 1 MHz base, set multiplier to 253, and divider to 200.

The program uses integer arithmetic. This avoids rounding errors; it also means the algorithm can be used in a microcontroller. The algorithm used is the continued fractions algorithm, which can be traced back to Euclid (approx. 300 BC).
