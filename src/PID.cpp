#include <iostream>
#include "PID.h"

using namespace std;

PID::PID() = default;

PID::~PID() = default;

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  p_error = i_error = d_error = 0.0;
  prev_cte = int_cte = 0.0;
}

void PID::UpdateError(double cte) {
  int_cte += cte;

  p_error = -Kp*cte;
  i_error = -Ki*int_cte;
  d_error = -Kd*(cte-prev_cte);

  prev_cte = cte;
}

double PID::TotalError() {
  // DEBUG
  // cout << "P Error: " << p_error << " I Error: " << i_error << " D Error: " << d_error << endl;
  return p_error + i_error + d_error;
}

