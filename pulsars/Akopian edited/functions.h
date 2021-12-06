#ifndef AKOPIAN_EDITED_FUNCTIONS_H
#define AKOPIAN_EDITED_FUNCTIONS_H

const double Rs = 1.2; // R_star in 10 km

//constants
const double pi = 3.14159265;
const double c = 30000.0 / Rs; // c in Rs/sec
const double omegaB = 1.17 * 1.76 * pow(10.0, 19); // e*Bo/(m*c)

//pulsar constants
const double P = 1.382449; // period in sec

const double Omega = 2.0 * pi / P; // 2 pi / P (same time z-component of Omega)
const double Rlc = c / Omega; // R_lc (light cylinder)
const double Rpc = Rs * sqrt(Rs / Rlc); // R_pc (polar cap)

//model parameters
const double lambda = 30000.0;
//#define f0 (0.5)
//#define A (0.1)
const double f0 = 1.0;
const double A = 5.0;
const double Rm = 50.0 * Rs;

const double omega = 2 * pi * 0.327 * pow(10.0, 9); // 10^9 Hz = 1 GHz
const double gamma = 100.0; // gamma factor

const double chi = 48.0 * (pi / 180); // chi in rad
const double beta = 0.4 * (pi / 180); // beta in rad

const int mode = 1; // 0: X-mode, 1: O-mode

//functions
double r(double x, double y, double z); // r
double nr(double x, double y, double z, int a); // n_a
double CosPsim(double x, double y, double z, double mx, double my, double mz); // Cos(psi_m) = (m , n)
double rPerp(double x, double y, double z, double mx, double my, double mz); // r_perp
double g1(double x, double y, double z, double mx, double my, double mz); // (f_0 R_0 / r_perp)^5
double g2(double x, double y, double z, double mx, double my, double mz); // (R_0 / r_perp)^2
double gamma_a(double x, double y, double z, double mx, double my, double mz);  // g / x

double Ba(double x, double y, double z, double mx, double my, double mz, int a); // B_a
double B(double x, double y, double z, double mx, double my, double mz); // B
double ba(double x, double y, double z, double mx, double my, double mz, int a); // b

double g(double x, double y, double z, double mx, double my, double mz); // g(r_perp)
double theta(double x, double y, double z, double mx, double my, double mz, double kx, double ky, double kz); // theta
double Theta(double x, double y, double z, double mx, double my, double mz); // Theta
double n(double x, double y, double z, double mx, double my, double mz, double kx, double ky, double kz); // n

double Lambda(double x, double y, double z, double mx, double my, double mz); // Lambda

int Kdelta(int a, int i); // Kronecker Delta
//derivatives
// r_i derivatives
double dnadri(double x, double y, double z, int a, int i); // dn_a / dr_i
double mdndri(double x, double y, double z, double mx, double my, double mz, int i); // (m , dn / dr_i)
double dBadri(double x, double y, double z, double mx, double my, double mz, int a, int i); // dB_a / dr_i
double dbadri(double x, double y, double z, double mx, double my, double mz, int a, int i); // db_a / dr_i
double dthdri(double x, double y, double z, double mx, double my,
              double mz, double kx, double ky, double kz, int i); // dth / dr_i
double drpdri(double x, double y, double z, double mx, double my, double mz, int i); // dr_perp / dr_i
double dg1dri(double x, double y, double z, double mx, double my, double mz, int i); // dg_1 / dr_i
double dg2dri(double x, double y, double z, double mx, double my, double mz, int i); // dg_2 / dr_i
double dgdri(double x, double y, double z, double mx, double my, double mz, int i); // dg / dr_i
double dThdri(double x, double y, double z, double mx, double my, double mz, int i); // dTh / dr_i

double dkndri(double x, double y, double z, double mx,
              double my, double mz, double kx, double ky, double kz, int i); // d(k/n)/dr_i

// k_i derivatives
double dkadki(double kx, double ky, double kz, int a, int i); // d(k_a/k)/dk_i
double dkndki(double x, double y, double z, double mx, double my, double mz,
              double kx, double ky, double kz, int i); // d(k/n)/dk_i

#endif //AKOPIAN_EDITED_FUNCTIONS_H
