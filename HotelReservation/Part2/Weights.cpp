#include "Weights.hpp"

Weights::Weights()
{
   manual_weights_activated = false;
   manual_weights = {};
   estimated_weights = {};
   srand(time(NULL));
};

bool Weights::is_in_manual_weight_interval(float given_weight)
{
  if(given_weight >= WEIGHTS_MIN && given_weight <= WEIGHTS_MAX)
    return true;
  throw InvalidRequest();
}

void Weights::set_manual_weights(const weights_t& given_weights)
{
  manual_weights = {};
  for(auto weight:given_weights)
    manual_weights.push_back(weight);
}

void Weights::initialise_estimated_weights(void)
{
  estimated_weights = {};
  for(int weight = 0; weight < NUM_OF_WEIGHTS; weight++)
    estimated_weights.push_back(rand() % 5 + 1);
}

void Weights::initialise_derivatives(void)
{
  derivative_of_weights = {};
  for(int weight = 0; weight < NUM_OF_WEIGHTS; weight++)
    derivative_of_weights.push_back(0);
}

void Weights::print_manual_weights(void)
{
  std::cout << ACTIVE << SPACE << TRUE_ << SPACE
            << std::fixed << std::setprecision(2) << LOCATION << SPACE <<  manual_weights[LOCATION_INDEX] << SPACE
            << std::fixed << std::setprecision(2) << CLEANLINESS << SPACE <<  manual_weights[CLEANLINESS_INDEX] << SPACE
            << std::fixed << std::setprecision(2) << STAFF << SPACE <<  manual_weights[STAFF_INDEX] << SPACE
            << std::fixed << std::setprecision(2) << FACILITIES << SPACE <<  manual_weights[FACILITIES_INDEX] << SPACE
            << std::fixed << std::setprecision(2) << VALUE_FOR_MONEY << SPACE <<  manual_weights[VALUE_FOR_MONEY_INDEX] << SPACE << std::endl;

}

float Weights::sum_of_manual_weights(void)
{
  return std::accumulate(manual_weights.begin(), manual_weights.end(), 0, [&](const int& acc, const float& data) { return acc + data; });
}

void Weights::estimate_weights_by_gradient_descent(Hotel* given_hotel, User* given_user, int num_of_steps)
{
  initialise_estimated_weights();
  for(int step = 0; step < num_of_steps; step++)
  {
    initialise_derivatives();
    calculate_derivatives(given_user);
  }
  for(int weight_index = 0; weight_index < estimated_weights.size(); weight_index++)
  {
    estimated_weights[weight_index] = estimated_weights[weight_index] - EPSILON * derivative_of_weights[weight_index];
    estimated_weights[weight_index] = clamp(estimated_weights[weight_index], 0, 5);
  }
}

void Weights::calculate_derivatives(User* given_user)
{
  for(int rating = 0; rating < given_user->given_ratings.size(); rating++)
  {
    for(int weight_index = 0; weight_index < NUM_OF_WEIGHTS; weight_index++)
      derivative_of_weights[weight_index] += calc_weight_partial_derivative(rating, weight_index, given_user);
  }
}

float Weights::calc_weight_partial_derivative(int rating_index, int weight_index, User* given_user)
{
  weights_t changed_weights = estimated_weights;
  changed_weights[weight_index] += EPSILON;
  return (error_function(given_user->given_ratings[rating_index], changed_weights, given_user->given_ratings[rating_index]->ratings[OVERALL_RATING_INDEX])
         -error_function(given_user->given_ratings[rating_index], estimated_weights, given_user->given_ratings[rating_index]->ratings[OVERALL_RATING_INDEX]))/EPSILON;
}

float Weights::error_function(Rating* given_rating, const weights_t& given_weights, float overall_rating)
{
  return pow(calc_weighted_average_of_rating(given_rating, given_weights)-overall_rating, 2);
}

float Weights::calc_weighted_average_of_rating(Rating* given_rating, const weights_t& given_weights)
{
  float dividend = 0;
  for(int weight_index = 0; weight_index < given_rating->ratings.size(); weight_index++)
    dividend += given_rating->ratings[weight_index] * given_weights[weight_index];
  return dividend/sum_of_weights(given_weights);
}

float Weights::sum_of_weights(const weights_t& given_weights)
{
  float sum = 0;
  for(auto weight:given_weights)
    sum += weight;
  return sum;
}

int Weights::clamp(const float& given_number, int min, int max)
{
  if(given_number <= min)
    return min;
  else if(given_number >= max)
    return max;
  else
    return given_number;
}
