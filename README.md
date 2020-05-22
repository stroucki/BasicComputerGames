# Basic Computer Games

Games included in David Ahl's books "Basic Computer Games" ported to C.

## Intro

The second volume was one of my first type-ins books, but the Basic
code used in the book was already archaic, and required porting to run
on the Amstrad CPC 464.

The first volume recently came into my hands, so depending on
available time, I plan to port the games to C.

## Methodology

The original code was written in 1970s era Micro$oft Basic, for
apparently the lowest common denominator platform of the day.
I have chosen to port the programs to appear similar to how I imagine
the originals looked, but to use the availability of lower case
characters in code and data.

Perhaps out of design, the original code tends to be very unstructured,
with goto's transferring execution to far away locations. I will
restructure the code to give explanatory names to game functions.

If I notice that the game could be improved with altered parameters,
I will do so, but include comments with the old values.

## Compiling

Instructions to compile are given in the source.

## Issues

There is currently no one true way of obtaining random numbers, so the 
parts of the programs using random seeders and readers may have to be 
adapted. Currently uses arc4random_uniform(3) to obtain random numbers,
on Linux this requires linking in libbsd.

## Licence

GPLv3
