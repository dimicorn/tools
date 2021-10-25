//
// Created by dmitr on 25-Oct-21.
//

#ifndef AKOPIAN_EDITED_FUNCTIONS_H
#define AKOPIAN_EDITED_FUNCTIONS_H
//functions
double r (double x, double y, double z); // r
double nr (double x, double y, double z, int a); // n_a
double CosPsim (double x, double y, double z, double mx, double my, double mz); // Cos(psi_m) = (m , n)
double rPerp (double x, double y, double z, double mx, double my, double mz); // r_perp
double g1 (double x, double y, double z, double mx, double my, double mz); // (f_0 R_0 / r_perp)^5
double g2 (double x, double y, double z, double mx, double my, double mz); // (R_0 / r_perp)^2
double gamma_a(double x, double y, double z, double mx, double my, double mz);  // g / x

double Ba (double x, double y, double z, double mx, double my, double mz, int a); // B_a
double B (double x, double y, double z, double mx, double my, double mz); // B
double ba (double x, double y, double z, double mx, double my, double mz, int a); // b

double g (double x, double y, double z, double mx, double my, double mz); // g(r_perp)
double theta (double x, double y, double z, double mx, double my, double mz, double kx, double ky, double kz); // theta
double Theta (double x, double y, double z, double mx, double my, double mz); // Theta
double n (double x, double y, double z, double mx, double my, double mz, double kx, double ky, double kz); // n

double Lambda (double x, double y, double z, double mx, double my, double mz); // Lambda

int Kdelta (int a, int i); // Kronecker Delta
//derivatives
// r_i derivatives
double dnadri (double x, double y, double z, int a, int i); // dn_a / dr_i
double mdndri (double x, double y, double z, double mx, double my, double mz, int i); // (m , dn / dr_i)
double dBadri (double x, double y, double z, double mx, double my, double mz, int a, int i); // dB_a / dr_i
double dbadri (double x, double y, double z, double mx, double my, double mz, int a, int i); // db_a / dr_i
double dthdri (double x, double y, double z, double mx, double my,
               double mz, double kx, double ky, double kz, int i); // dth / dr_i
double drpdri (double x, double y, double z, double mx, double my, double mz, int i); // dr_perp / dr_i
double dg1dri (double x, double y, double z, double mx, double my, double mz, int i); // dg_1 / dr_i
double dg2dri (double x, double y, double z, double mx, double my, double mz, int i); // dg_2 / dr_i
double dgdri (double x, double y, double z, double mx, double my, double mz, int i); // dg / dr_i
double dThdri (double x, double y, double z, double mx, double my, double mz, int i); // dTh / dr_i

double dkndri (double x, double y, double z, double mx,
               double my, double mz, double kx, double ky, double kz, int i); // d(k/n)/dr_i

// k_i derivatives
double dkadki (double kx, double ky, double kz, int a, int i); // d(k_a/k)/dk_i
double dkndki (double x, double y, double z, double mx, double my, double mz,
               double kx, double ky, double kz, int i); // d(k/n)/dk_i

#endif //AKOPIAN_EDITED_FUNCTIONS_H
