#ifndef EOS_HEADER_H
#define EOS_HEADER_H

static constexpr bool use_rootfinder                      = true;
static constexpr bool skip_failed_EoS                     = true;
static constexpr bool zero_unsolvable_charge_densities    = false;

static constexpr int VERBOSE = 3;
static constexpr double TINY = 1e-25;
static constexpr double TBQS_INFINITY = 1e10;  // indefinitely large limits for EoS

#endif
