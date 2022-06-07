#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

#include "../include/constants.h"
#include "../include/eos.h"
#include "../include/eos_base.h"
#include "../include/eos_conformal_diagonal.h"
#include "../include/eos_header.h"
#include "../include/formatted_output.h"
#include "../include/rootfinder.h"

using namespace constants;

using std::vector;
using std::string;
using std::to_string;



////////////////////////////////////////////////////////////////////////////////
void EquationOfState::init()
{
	tbqsPosition.resize(4);

  //============================================================================
  // THIS IF-CHAIN INITIALIZES THE DEFAULT EOS TO USE
  //============================================================================
  // SET UP CONFORMAL EOS
  
  // SET UP CONFORMAL DIAGONAL EOS
  if ( settingsPtr->EoS_type == "conformal_diagonal" )
  {
    formatted_output::update("Setting diagonal conformal equation of state");

    const double Nc = 3.0, Nf = 2.5;  // u+d massless, s 'half massless'
    double c  = pi*pi*(2.0*(Nc*Nc-1.0)+(7.0/2.0)*Nc*Nf)/90.0;
    double T0 = 1.0, muB0 = 1.0, muQ0 = 1.0, muS0 = 1.0; // trivial scales

    // set minima and maxima for rootfinder (can be arbitrarily large)
    vector<double> tbqs_minima = { 0.0,          -TBQS_INFINITY, -TBQS_INFINITY, -TBQS_INFINITY };
    vector<double> tbqs_maxima = { TBQS_INFINITY, TBQS_INFINITY,  TBQS_INFINITY,  TBQS_INFINITY };


    formatted_output::detail("set up with following parameters:");
    formatted_output::detail( "c    = " + to_string(c) );
    formatted_output::detail( "T0   = " + to_string(T0) );
    formatted_output::detail( "muB0 = " + to_string(muB0) );
    formatted_output::detail( "muQ0 = " + to_string(muQ0) );
    formatted_output::detail( "muS0 = " + to_string(muS0) );

    // add matched conformal EoS to vector of EoSs
    chosen_EOSs.push_back( std::make_shared<EoS_conformal_diagonal>(
                            c, T0, muB0, muS0, muQ0,
                            tbqs_minima, tbqs_maxima, "conformal_diagonal" ) );

    default_eos_name = "conformal_diagonal";

  }

  //============================================================================
  // create a map to access all needed EoSs by name
  // (this step *MUST BE DONE AFTER* chosen EoSs have been set,
  //  and each EoS must have a *UNIQUE NAME*)
  //============================================================================
  formatted_output::update( "Check order of equations of state:" );
  for ( auto & chosen_eos : chosen_EOSs )
  {
    formatted_output::detail( chosen_eos->name );
    chosen_EOS_map.insert({{ chosen_eos->name, chosen_eos }});
  }


	return;
}



