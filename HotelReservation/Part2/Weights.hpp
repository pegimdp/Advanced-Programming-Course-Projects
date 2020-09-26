#ifndef __WEIGHTS_H__
#define __WEIGHTS_H__

#include "Macros.hpp"
#include "User.hpp"
#include "Hotel.hpp"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>

typedef std::vector<float> weights_t;

class Hotel;
class Weights
{
public:
  Weights();
  bool manual_weights_activated;
  weights_t manual_weights;
  weights_t estimated_weights;
  weights_t derivative_of_weights;
  void print_manual_weights(void);
  bool is_in_manual_weight_interval(float given_weight);
  void set_manual_weights(const weights_t& given_weights);
  float sum_of_manual_weights(void);
  float calc_weighted_average_of_rating(Rating* given_rating, const weights_t& given_weights);
  void estimate_weights_by_gradient_descent(Hotel* given_hotel, User* given_user, int num_of_steps);
private:
  void initialise_estimated_weights(void);
  void initialise_derivatives(void);
  void calculate_derivatives(User* given_user);
  float calc_weight_partial_derivative(int rating_index, int weight_index, User* given_user);
  float error_function(Rating* given_rating, const weights_t& given_weights, float overall_rating);
  float sum_of_weights(const weights_t& given_weights);
  int clamp(const float& given_number, int min, int max);

};

#endif
