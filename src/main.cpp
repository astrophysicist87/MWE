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
#include "../include/eos_conformal_diagonal.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main (int argc, char *argv[])
{
  EquationOfState eos;
  
  // default: use particle's current location as initial guess
  // (pass in corresponding EoS as well!)
  eos.tbqs( 1000.0/197.3, -50.0, 50.0, 0.0, "conformal_diagonal" );

  bool solution_found = false;
  double sVal = eos.s_out( 0.862529, -0.308373, 0.0, 0.308373, solution_found );
  //double sVal = eos.s_out( 0.862529, -0.000308373, 0.0, 0.000308373, solution_found );
  //double sVal = eos.s_out( 0.862529, 0.0, 0.0, 0.0, solution_found );
  
  if ( solution_found )
	{
	  cout << "found solution!" << endl;
	  cout << "T = " << eos.T() << endl;
	  cout << "muB = " << eos.muB() << endl;
	  cout << "muS = " << eos.muS() << endl;
	  cout << "muQ = " << eos.muQ() << endl;
	  	  
		if (eos.cs2()<0)
		{
		  cout << __LINE__ << "cs2 was negative!" << endl;
		  exit(8);
		}
		
		// exact solution
		{
      // try conformal diagonal seed
      auto conformal_diagonal_EoS = std::dynamic_pointer_cast<EoS_conformal_diagonal>
                                        ( eos.chosen_EOS_map["conformal_diagonal"] );

      vector<double> result = conformal_diagonal_EoS->get_tbqs_seed_from_eBSQ( 0.862529, -0.308373, 0.0, 0.308373 );

			cout << "Exact: " << result[0] << "   " << result[1] << "   " << result[2] << "   " << result[3] << endl;
    }

	}

  return 0;
}
