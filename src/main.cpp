#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/eos.h"
#include "../include/constants.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main (int argc, char *argv[])
{
  EquationOfState eos;
  
  // default: use particle's current location as initial guess
  // (pass in corresponding EoS as well!)
  eos.tbqs( 1000.0, 0.0, 0.0, 0.0, "conformal_diagonal" );

  bool solution_found = false;
  //double sVal = eos.s_out( 0.862529, -0.308373, 0.0, 0.308373, solution_found );
  double sVal = eos.s_out( 0.862529, 0.0, 0.0, 0.0, solution_found );

  if ( solution_found )
	{
	  cout << "found solution!" << endl;
		if (eos.cs2()<0)
		{
		  cout << __LINE__ << "cs2 was negative!" << endl;
		  exit(8);
		}
	}

  return 0;
}
