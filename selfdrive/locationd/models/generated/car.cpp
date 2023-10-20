#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3699073491920453798) {
   out_3699073491920453798[0] = delta_x[0] + nom_x[0];
   out_3699073491920453798[1] = delta_x[1] + nom_x[1];
   out_3699073491920453798[2] = delta_x[2] + nom_x[2];
   out_3699073491920453798[3] = delta_x[3] + nom_x[3];
   out_3699073491920453798[4] = delta_x[4] + nom_x[4];
   out_3699073491920453798[5] = delta_x[5] + nom_x[5];
   out_3699073491920453798[6] = delta_x[6] + nom_x[6];
   out_3699073491920453798[7] = delta_x[7] + nom_x[7];
   out_3699073491920453798[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5512259151403388105) {
   out_5512259151403388105[0] = -nom_x[0] + true_x[0];
   out_5512259151403388105[1] = -nom_x[1] + true_x[1];
   out_5512259151403388105[2] = -nom_x[2] + true_x[2];
   out_5512259151403388105[3] = -nom_x[3] + true_x[3];
   out_5512259151403388105[4] = -nom_x[4] + true_x[4];
   out_5512259151403388105[5] = -nom_x[5] + true_x[5];
   out_5512259151403388105[6] = -nom_x[6] + true_x[6];
   out_5512259151403388105[7] = -nom_x[7] + true_x[7];
   out_5512259151403388105[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6004474647322099520) {
   out_6004474647322099520[0] = 1.0;
   out_6004474647322099520[1] = 0;
   out_6004474647322099520[2] = 0;
   out_6004474647322099520[3] = 0;
   out_6004474647322099520[4] = 0;
   out_6004474647322099520[5] = 0;
   out_6004474647322099520[6] = 0;
   out_6004474647322099520[7] = 0;
   out_6004474647322099520[8] = 0;
   out_6004474647322099520[9] = 0;
   out_6004474647322099520[10] = 1.0;
   out_6004474647322099520[11] = 0;
   out_6004474647322099520[12] = 0;
   out_6004474647322099520[13] = 0;
   out_6004474647322099520[14] = 0;
   out_6004474647322099520[15] = 0;
   out_6004474647322099520[16] = 0;
   out_6004474647322099520[17] = 0;
   out_6004474647322099520[18] = 0;
   out_6004474647322099520[19] = 0;
   out_6004474647322099520[20] = 1.0;
   out_6004474647322099520[21] = 0;
   out_6004474647322099520[22] = 0;
   out_6004474647322099520[23] = 0;
   out_6004474647322099520[24] = 0;
   out_6004474647322099520[25] = 0;
   out_6004474647322099520[26] = 0;
   out_6004474647322099520[27] = 0;
   out_6004474647322099520[28] = 0;
   out_6004474647322099520[29] = 0;
   out_6004474647322099520[30] = 1.0;
   out_6004474647322099520[31] = 0;
   out_6004474647322099520[32] = 0;
   out_6004474647322099520[33] = 0;
   out_6004474647322099520[34] = 0;
   out_6004474647322099520[35] = 0;
   out_6004474647322099520[36] = 0;
   out_6004474647322099520[37] = 0;
   out_6004474647322099520[38] = 0;
   out_6004474647322099520[39] = 0;
   out_6004474647322099520[40] = 1.0;
   out_6004474647322099520[41] = 0;
   out_6004474647322099520[42] = 0;
   out_6004474647322099520[43] = 0;
   out_6004474647322099520[44] = 0;
   out_6004474647322099520[45] = 0;
   out_6004474647322099520[46] = 0;
   out_6004474647322099520[47] = 0;
   out_6004474647322099520[48] = 0;
   out_6004474647322099520[49] = 0;
   out_6004474647322099520[50] = 1.0;
   out_6004474647322099520[51] = 0;
   out_6004474647322099520[52] = 0;
   out_6004474647322099520[53] = 0;
   out_6004474647322099520[54] = 0;
   out_6004474647322099520[55] = 0;
   out_6004474647322099520[56] = 0;
   out_6004474647322099520[57] = 0;
   out_6004474647322099520[58] = 0;
   out_6004474647322099520[59] = 0;
   out_6004474647322099520[60] = 1.0;
   out_6004474647322099520[61] = 0;
   out_6004474647322099520[62] = 0;
   out_6004474647322099520[63] = 0;
   out_6004474647322099520[64] = 0;
   out_6004474647322099520[65] = 0;
   out_6004474647322099520[66] = 0;
   out_6004474647322099520[67] = 0;
   out_6004474647322099520[68] = 0;
   out_6004474647322099520[69] = 0;
   out_6004474647322099520[70] = 1.0;
   out_6004474647322099520[71] = 0;
   out_6004474647322099520[72] = 0;
   out_6004474647322099520[73] = 0;
   out_6004474647322099520[74] = 0;
   out_6004474647322099520[75] = 0;
   out_6004474647322099520[76] = 0;
   out_6004474647322099520[77] = 0;
   out_6004474647322099520[78] = 0;
   out_6004474647322099520[79] = 0;
   out_6004474647322099520[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5290008103764663250) {
   out_5290008103764663250[0] = state[0];
   out_5290008103764663250[1] = state[1];
   out_5290008103764663250[2] = state[2];
   out_5290008103764663250[3] = state[3];
   out_5290008103764663250[4] = state[4];
   out_5290008103764663250[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5290008103764663250[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5290008103764663250[7] = state[7];
   out_5290008103764663250[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2929614667293202327) {
   out_2929614667293202327[0] = 1;
   out_2929614667293202327[1] = 0;
   out_2929614667293202327[2] = 0;
   out_2929614667293202327[3] = 0;
   out_2929614667293202327[4] = 0;
   out_2929614667293202327[5] = 0;
   out_2929614667293202327[6] = 0;
   out_2929614667293202327[7] = 0;
   out_2929614667293202327[8] = 0;
   out_2929614667293202327[9] = 0;
   out_2929614667293202327[10] = 1;
   out_2929614667293202327[11] = 0;
   out_2929614667293202327[12] = 0;
   out_2929614667293202327[13] = 0;
   out_2929614667293202327[14] = 0;
   out_2929614667293202327[15] = 0;
   out_2929614667293202327[16] = 0;
   out_2929614667293202327[17] = 0;
   out_2929614667293202327[18] = 0;
   out_2929614667293202327[19] = 0;
   out_2929614667293202327[20] = 1;
   out_2929614667293202327[21] = 0;
   out_2929614667293202327[22] = 0;
   out_2929614667293202327[23] = 0;
   out_2929614667293202327[24] = 0;
   out_2929614667293202327[25] = 0;
   out_2929614667293202327[26] = 0;
   out_2929614667293202327[27] = 0;
   out_2929614667293202327[28] = 0;
   out_2929614667293202327[29] = 0;
   out_2929614667293202327[30] = 1;
   out_2929614667293202327[31] = 0;
   out_2929614667293202327[32] = 0;
   out_2929614667293202327[33] = 0;
   out_2929614667293202327[34] = 0;
   out_2929614667293202327[35] = 0;
   out_2929614667293202327[36] = 0;
   out_2929614667293202327[37] = 0;
   out_2929614667293202327[38] = 0;
   out_2929614667293202327[39] = 0;
   out_2929614667293202327[40] = 1;
   out_2929614667293202327[41] = 0;
   out_2929614667293202327[42] = 0;
   out_2929614667293202327[43] = 0;
   out_2929614667293202327[44] = 0;
   out_2929614667293202327[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2929614667293202327[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2929614667293202327[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2929614667293202327[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2929614667293202327[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2929614667293202327[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2929614667293202327[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2929614667293202327[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2929614667293202327[53] = -9.8000000000000007*dt;
   out_2929614667293202327[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2929614667293202327[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2929614667293202327[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2929614667293202327[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2929614667293202327[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2929614667293202327[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2929614667293202327[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2929614667293202327[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2929614667293202327[62] = 0;
   out_2929614667293202327[63] = 0;
   out_2929614667293202327[64] = 0;
   out_2929614667293202327[65] = 0;
   out_2929614667293202327[66] = 0;
   out_2929614667293202327[67] = 0;
   out_2929614667293202327[68] = 0;
   out_2929614667293202327[69] = 0;
   out_2929614667293202327[70] = 1;
   out_2929614667293202327[71] = 0;
   out_2929614667293202327[72] = 0;
   out_2929614667293202327[73] = 0;
   out_2929614667293202327[74] = 0;
   out_2929614667293202327[75] = 0;
   out_2929614667293202327[76] = 0;
   out_2929614667293202327[77] = 0;
   out_2929614667293202327[78] = 0;
   out_2929614667293202327[79] = 0;
   out_2929614667293202327[80] = 1;
}
void h_25(double *state, double *unused, double *out_2763657023161734409) {
   out_2763657023161734409[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5353771594371325908) {
   out_5353771594371325908[0] = 0;
   out_5353771594371325908[1] = 0;
   out_5353771594371325908[2] = 0;
   out_5353771594371325908[3] = 0;
   out_5353771594371325908[4] = 0;
   out_5353771594371325908[5] = 0;
   out_5353771594371325908[6] = 1;
   out_5353771594371325908[7] = 0;
   out_5353771594371325908[8] = 0;
}
void h_24(double *state, double *unused, double *out_732815993837596622) {
   out_732815993837596622[0] = state[4];
   out_732815993837596622[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7526421193376825474) {
   out_7526421193376825474[0] = 0;
   out_7526421193376825474[1] = 0;
   out_7526421193376825474[2] = 0;
   out_7526421193376825474[3] = 0;
   out_7526421193376825474[4] = 1;
   out_7526421193376825474[5] = 0;
   out_7526421193376825474[6] = 0;
   out_7526421193376825474[7] = 0;
   out_7526421193376825474[8] = 0;
   out_7526421193376825474[9] = 0;
   out_7526421193376825474[10] = 0;
   out_7526421193376825474[11] = 0;
   out_7526421193376825474[12] = 0;
   out_7526421193376825474[13] = 0;
   out_7526421193376825474[14] = 1;
   out_7526421193376825474[15] = 0;
   out_7526421193376825474[16] = 0;
   out_7526421193376825474[17] = 0;
}
void h_30(double *state, double *unused, double *out_3038851085446240298) {
   out_3038851085446240298[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2835438635864077281) {
   out_2835438635864077281[0] = 0;
   out_2835438635864077281[1] = 0;
   out_2835438635864077281[2] = 0;
   out_2835438635864077281[3] = 0;
   out_2835438635864077281[4] = 1;
   out_2835438635864077281[5] = 0;
   out_2835438635864077281[6] = 0;
   out_2835438635864077281[7] = 0;
   out_2835438635864077281[8] = 0;
}
void h_26(double *state, double *unused, double *out_3982360938347902733) {
   out_3982360938347902733[0] = state[7];
}
void H_26(double *state, double *unused, double *out_9095274913245382132) {
   out_9095274913245382132[0] = 0;
   out_9095274913245382132[1] = 0;
   out_9095274913245382132[2] = 0;
   out_9095274913245382132[3] = 0;
   out_9095274913245382132[4] = 0;
   out_9095274913245382132[5] = 0;
   out_9095274913245382132[6] = 0;
   out_9095274913245382132[7] = 1;
   out_9095274913245382132[8] = 0;
}
void h_27(double *state, double *unused, double *out_7765330290822580054) {
   out_7765330290822580054[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5010201947664502192) {
   out_5010201947664502192[0] = 0;
   out_5010201947664502192[1] = 0;
   out_5010201947664502192[2] = 0;
   out_5010201947664502192[3] = 1;
   out_5010201947664502192[4] = 0;
   out_5010201947664502192[5] = 0;
   out_5010201947664502192[6] = 0;
   out_5010201947664502192[7] = 0;
   out_5010201947664502192[8] = 0;
}
void h_29(double *state, double *unused, double *out_2065034001907613) {
   out_2065034001907613[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2325207291549685097) {
   out_2325207291549685097[0] = 0;
   out_2325207291549685097[1] = 1;
   out_2325207291549685097[2] = 0;
   out_2325207291549685097[3] = 0;
   out_2325207291549685097[4] = 0;
   out_2325207291549685097[5] = 0;
   out_2325207291549685097[6] = 0;
   out_2325207291549685097[7] = 0;
   out_2325207291549685097[8] = 0;
}
void h_28(double *state, double *unused, double *out_762567587029514275) {
   out_762567587029514275[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7407606308619215671) {
   out_7407606308619215671[0] = 1;
   out_7407606308619215671[1] = 0;
   out_7407606308619215671[2] = 0;
   out_7407606308619215671[3] = 0;
   out_7407606308619215671[4] = 0;
   out_7407606308619215671[5] = 0;
   out_7407606308619215671[6] = 0;
   out_7407606308619215671[7] = 0;
   out_7407606308619215671[8] = 0;
}
void h_31(double *state, double *unused, double *out_6861960321441106273) {
   out_6861960321441106273[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8725261058230818008) {
   out_8725261058230818008[0] = 0;
   out_8725261058230818008[1] = 0;
   out_8725261058230818008[2] = 0;
   out_8725261058230818008[3] = 0;
   out_8725261058230818008[4] = 0;
   out_8725261058230818008[5] = 0;
   out_8725261058230818008[6] = 0;
   out_8725261058230818008[7] = 0;
   out_8725261058230818008[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3699073491920453798) {
  err_fun(nom_x, delta_x, out_3699073491920453798);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5512259151403388105) {
  inv_err_fun(nom_x, true_x, out_5512259151403388105);
}
void car_H_mod_fun(double *state, double *out_6004474647322099520) {
  H_mod_fun(state, out_6004474647322099520);
}
void car_f_fun(double *state, double dt, double *out_5290008103764663250) {
  f_fun(state,  dt, out_5290008103764663250);
}
void car_F_fun(double *state, double dt, double *out_2929614667293202327) {
  F_fun(state,  dt, out_2929614667293202327);
}
void car_h_25(double *state, double *unused, double *out_2763657023161734409) {
  h_25(state, unused, out_2763657023161734409);
}
void car_H_25(double *state, double *unused, double *out_5353771594371325908) {
  H_25(state, unused, out_5353771594371325908);
}
void car_h_24(double *state, double *unused, double *out_732815993837596622) {
  h_24(state, unused, out_732815993837596622);
}
void car_H_24(double *state, double *unused, double *out_7526421193376825474) {
  H_24(state, unused, out_7526421193376825474);
}
void car_h_30(double *state, double *unused, double *out_3038851085446240298) {
  h_30(state, unused, out_3038851085446240298);
}
void car_H_30(double *state, double *unused, double *out_2835438635864077281) {
  H_30(state, unused, out_2835438635864077281);
}
void car_h_26(double *state, double *unused, double *out_3982360938347902733) {
  h_26(state, unused, out_3982360938347902733);
}
void car_H_26(double *state, double *unused, double *out_9095274913245382132) {
  H_26(state, unused, out_9095274913245382132);
}
void car_h_27(double *state, double *unused, double *out_7765330290822580054) {
  h_27(state, unused, out_7765330290822580054);
}
void car_H_27(double *state, double *unused, double *out_5010201947664502192) {
  H_27(state, unused, out_5010201947664502192);
}
void car_h_29(double *state, double *unused, double *out_2065034001907613) {
  h_29(state, unused, out_2065034001907613);
}
void car_H_29(double *state, double *unused, double *out_2325207291549685097) {
  H_29(state, unused, out_2325207291549685097);
}
void car_h_28(double *state, double *unused, double *out_762567587029514275) {
  h_28(state, unused, out_762567587029514275);
}
void car_H_28(double *state, double *unused, double *out_7407606308619215671) {
  H_28(state, unused, out_7407606308619215671);
}
void car_h_31(double *state, double *unused, double *out_6861960321441106273) {
  h_31(state, unused, out_6861960321441106273);
}
void car_H_31(double *state, double *unused, double *out_8725261058230818008) {
  H_31(state, unused, out_8725261058230818008);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
