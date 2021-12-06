//functions
#include <cmath>
#include <iostream>
#include "functions.h"

double r(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

double nr(double x, double y, double z, int a) {
    if (a == 1) {
        return x / r(x, y, z);
    }
    if (a == 2) {
        return y / r(x, y, z);
    } else {
        return z / r(x, y, z);
    }
}

double CosPsim(double x, double y, double z, double mx, double my, double mz) {
    double nx = nr(x, y, z, 1);
    double ny = nr(x, y, z, 2);
    double nz = nr(x, y, z, 3);
    return nx * mx + ny * my + nz * mz;
}

double rPerp(double x, double y, double z, double mx, double my, double mz) {
    double R = r(x, y, z);
    double cospsim = CosPsim(x, y, z, mx, my, mz);
    if (1 - pow(cospsim, 2) < 0) {
        std::cout << "ERROR!" << std::endl;
    }
    return sqrt(1 - pow(cospsim, 2)) * sqrt(Rs / R) * Rs;
}

double g1(double x, double y, double z, double mx, double my, double mz) {
    double rperp = rPerp(x, y, z, mx, my, mz);
    return pow(sqrt(f0) * Rpc / rperp, 2);
}

double g2(double x, double y, double z, double mx, double my, double mz) {
    double rperp = rPerp(x, y, z, mx, my, mz);
    return pow(Rpc / rperp, 2);
}

double Ba(double x, double y, double z, double mx, double my, double mz, int a) {
    double nx = nr(x, y, z, 1);
    double ny = nr(x, y, z, 2);
    double nz = nr(x, y, z, 3);
    double R3 = pow(r(x, y, z), 3);
    double nn[3] = {nx, ny, nz};
    double mm[3] = {mx, my, mz};
    return 3 * CosPsim(x, y, z, mx, my, mz) * nn[a - 1] / R3 - mm[a - 1] / R3;
}

double B(double x, double y, double z, double mx, double my, double mz) {
    double Bx = Ba(x, y, z, mx, my, mz, 1);
    double By = Ba(x, y, z, mx, my, mz, 2);
    double Bz = Ba(x, y, z, mx, my, mz, 3);
    return sqrt(Bx * Bx + By * By + Bz * Bz);
}

double ba(double x, double y, double z, double mx, double my, double mz, int a) {
    double Bx = Ba(x, y, z, mx, my, mz, 1);
    double By = Ba(x, y, z, mx, my, mz, 2);
    double Bz = Ba(x, y, z, mx, my, mz, 3);
    double BB = B(x, y, z, mx, my, mz);
    double Bb[3] = {Bx, By, Bz};
    return Bb[a - 1] / BB;
}

double g(double x, double y, double z, double mx, double my, double mz) {
    //double rperp = rPerp(x, y, z, mx, my, mz);
    double cospsim = CosPsim(x, y, z, mx, my, mz);
    double sinpsim = sqrt(1.0 - cospsim * cospsim);
    double rperp_over_R0 = sinpsim * sqrt(Rlc / r(x, y, z));
    //return exp(-pow(rperp_over_R0, 2)) / (1.0 + pow(f0 / rperp_over_R0, 5));
    //return exp(-pow(2*rperp_over_R0, 2)) / (1.0 + pow(f0 / rperp_over_R0, 2)); //andrey
    //return 1.25 * sqrt(sqrt(rperp_over_R0*rperp_over_R0) * 2.5) * exp(-pow(rperp_over_R0*2.5,2));//andrey
    //double K = 14.8;

    //return K * pow(rperp_over_R0, 3) * exp(-10 * pow(rperp_over_R0,4));//andrey
    //return 100.0/1.284 * pow(rperp_over_R0, 3) * exp(-10 * pow(rperp_over_R0,2));//andrey
    //return 130.0 * pow(rperp_over_R0,3) * exp(-10.0 * pow(rperp_over_R0,5)) * pow(1.0 - rperp_over_R0,2);

    return (37.5 * pow(rperp_over_R0, 3) * exp(-24.0 * pow(rperp_over_R0, 6)));
}

double gamma_a(double x, double y, double z, double mx, double my, double mz) {
    //double rperp = rPerp(x, y, z, mx, my, mz);
    double cospsim = CosPsim(x, y, z, mx, my, mz);
    double sinpsim = sqrt(1.0 - cospsim * cospsim);
    double rperp_over_R0 = sinpsim * sqrt(Rlc / r(x, y, z));
    if ((rperp_over_R0) < 1e-10) {
        rperp_over_R0 = 1e-10;
    }
    return gamma / rperp_over_R0;
}

double theta(double x, double y, double z, double mx, double my, double mz, double kx, double ky, double kz) {
    double bx = ba(x, y, z, mx, my, mz, 1);
    double by = ba(x, y, z, mx, my, mz, 2);
    double bz = ba(x, y, z, mx, my, mz, 3);
    double th = acos(-(bx * kx + by * ky + bz * kz) / sqrt(kx * kx + ky * ky + kz * kz));
    return th;
}

double Theta(double x, double y, double z, double mx, double my, double mz) {
    double G = g(x, y, z, mx, my, mz);
    double R = r(x, y, z);
    //double bz = ba(x, y, z, mx, my, mz, 3);
    double Lamb = Lambda(x, y, z, mx, my, mz);
    return fabs(Lamb * lambda * G / pow(R, 3));
}

double n(double x, double y, double z, double mx, double my, double mz, double kx, double ky, double kz) {
    double th = theta(x, y, z, mx, my, mz, kx, ky, kz);
    double Th = Theta(x, y, z, mx, my, mz);
    return 1 + th * th / 4 - sqrt(pow(th, 4) / 16 + Th);
}

double Lambda(double x, double y, double z, double mx, double my, double mz) {
    //double R = r(x, y, z);
    double bz = ba(x, y, z, mx, my, mz, 3);
    return 2 * omegaB * Omega * bz / (omega * omega * gamma_a(x, y, z, mx, my, mz) *
                                      gamma_a(x, y, z, mx, my, mz) * gamma_a(x, y, z, mx, my, mz));
}

int Kdelta(int a, int i) {
    if (a == i) {
        return 1;
    } else {
        return 0;
    }
}

//derivatives
// r_i derivatives
double dnadri(double x, double y, double z, int a, int i) {
    double R = r(x, y, z);
    //double rvec[3] = {x, y, z};
    return (Kdelta(a, i) - nr(x, y, z, a) * nr(x, y, z, i)) / R;
}

double mdndri(double x, double y, double z, double mx, double my, double mz, int i) {
    return mx * dnadri(x, y, z, 1, i) + my * dnadri(x, y, z, 2, i)
           + mz * dnadri(x, y, z, 3, i);
}

double dBadri(double x, double y, double z, double mx, double my, double mz, int a, int i) {
    double R = r(x, y, z);
    double Mn = CosPsim(x, y, z, mx, my, mz);
    double mDn = mdndri(x, y, z, mx, my, mz, i);
    double nvec[3] = {x / R, y / R, z / R};
    double Mvec[3] = {mx, my, mz};
    double rvec[3] = {x, y, z};

    return -3 * rvec[i - 1] * (3 * Mn * nvec[a - 1] - Mvec[a - 1]) / pow(R, 5) +
           (3 / pow(R, 3)) * dnadri(x, y, z, a, i) * Mn + (3 / pow(R, 3)) * nvec[a - 1] * mDn;
}

double dbadri(double x, double y, double z, double mx, double my, double mz, int a, int i) {
    double Bvec[3] = {Ba(x, y, z, mx, my, mz, 1), Ba(x, y, z, mx, my, mz, 2),
                      Ba(x, y, z, mx, my, mz, 3)};
    double dBvec[3] = {dBadri(x, y, z, mx, my, mz, 1, i), dBadri(x, y, z, mx, my, mz, 2, i),
                       dBadri(x, y, z, mx, my, mz, 3, i)};
    double BB = B(x, y, z, mx, my, mz);
    return (1 / BB) * dBvec[a - 1] - (Bvec[a - 1] / (BB * BB * BB)) *
                                     (Bvec[0] * dBvec[0] + Bvec[1] * dBvec[1] + Bvec[2] * dBvec[2]);
}

double drpdri(double x, double y, double z, double mx, double my, double mz, int i) {
    double cos = fabs(CosPsim(x, y, z, mx, my, mz)), sin = sqrt(1 - cos * cos);
    if (cos > 1) {
        std::cout << "ERROR!" << std::endl;
    }
    double R = r(x, y, z), rvec[3] = {x, y, z};
    double mdn = mdndri(x, y, z, mx, my, mz, i);
    return -Rs * sqrt(Rs) * (rvec[i - 1] * sin / (2 * R * R) + cos * mdn / sin) / sqrt(R);
}

double dg1dri(double x, double y, double z, double mx, double my, double mz, int i) {
    double drp = drpdri(x, y, z, mx, my, mz, i);
    double g01 = g1(x, y, z, mx, my, mz);
    double rp = rPerp(x, y, z, mx, my, mz);
    return -5 * g01 * drp / rp;
}

double dg2dri(double x, double y, double z, double mx, double my, double mz, int i) {
    double g02 = g2(x, y, z, mx, my, mz);
    double rp = rPerp(x, y, z, mx, my, mz);
    double drp = drpdri(x, y, z, mx, my, mz, i);
    return -2 * g02 * drp / rp;
}
/*
double andrey_dgdri(double x, double y, double z, double mx, double my, double mz, int i) {
//    double Dg1 = dg1dri (x,y,z,mx,my,mz,i);
//    double Dg2 = dg2dri (x,y,z,mx,my,mz,i);
//    double G = g (x,y,z,mx,my,mz);
//    double g01 = g1 (x,y,z,mx,my,mz);
//    double g02 = g2 (x,y,z,mx,my,mz);
//    double r_i = 1;
//    double A = 1;
//    double B = 1;
    return 1;//G*((1 + g01)*Dg2 - g02*g02*Dg1)/(g02*g02*(1 + g01));
}
*/
double dgdri(double x, double y, double z, double mx, double my, double mz, int i) {
    double Dg1 = dg1dri(x, y, z, mx, my, mz, i);
    double Dg2 = dg2dri(x, y, z, mx, my, mz, i);
    double G = g(x, y, z, mx, my, mz);
    double g01 = g1(x, y, z, mx, my, mz);
    double g02 = g2(x, y, z, mx, my, mz);
    return G * ((1 + g01) * Dg2 - g02 * g02 * Dg1) / (g02 * g02 * (1 + g01));
//    return andrey_dgdri (x,y,z,mx,my,mz);
}

double dThdri(double x, double y, double z, double mx, double my, double mz, int i) {
    double rvec[3] = {x, y, z};
    double G = g(x, y, z, mx, my, mz);
    double R = r(x, y, z);
    //double DgDri = dgdri(x, y, z, mx, my, mz, i);
    double Lamb = Lambda(x, y, z, mx, my, mz);
    return Lamb * lambda * pow(Rs, 3) * (1 / pow(R, 3)) *
           (dgdri(x, y, z, mx, my, mz, i) - (3 * rvec[i - 1] / (R * R)) * G);
}

double dkndri(double x, double y, double z, double mx, double my, double mz,
              double kx, double ky, double kz, int i) {
    /*
    if (mode == 0){
        return 0;
    }
    */
    double k = sqrt(kx * kx + ky * ky + kz * kz);
    double N = n(x, y, z, mx, my, mz, kx, ky, kz);
    double bk = kx * dbadri(x, y, z, mx, my, mz, 1, i) + ky * dbadri(x, y, z, mx, my, mz, 2, i) +
                kz * dbadri(x, y, z, mx, my, mz, 3, i);
    double th = theta(x, y, z, mx, my, mz, kx, ky, kz);
    double Th = Theta(x, y, z, mx, my, mz);
    double DThdri = dThdri(x, y, z, mx, my, mz, i);
    if (pow(th, 4) / 16 + Th < 0)
        std::cout << "ERROR!" << std::endl;
    return k * (bk - (pow(th, 2) * bk / 4 - DThdri) / sqrt(pow(th, 4) / 16 + Th)) / (2 * N * N);
}

// k_i derivatives
double dkadki(double kx, double ky, double kz, int a, int i) {
    double K = sqrt(kx * kx + ky * ky + kz * kz);
    double kvec[3] = {kx, ky, kz};
    return Kdelta(a, i) / K - kvec[a - 1] * kvec[i - 1] / pow(K, 3);
}

double dkndki(double x, double y, double z, double mx, double my, double mz,
              double kx, double ky, double kz, int i) {
    double kvec[3] = {kx, ky, kz};
    /*
    if (mode == 0){
        return kvec[i - 1];
    }
    */
    double dkvec[3] = {dkadki(kx, ky, kz, 1, i), dkadki(kx, ky, kz, 2, i),
                       dkadki(kx, ky, kz, 3, i)};
    double N = n(x, y, z, mx, my, mz, kx, ky, kz);
    double th = theta(x, y, z, mx, my, mz, kx, ky, kz);
    double Th = Theta(x, y, z, mx, my, mz);
    double bvec[3] = {ba(x, y, z, mx, my, mz, 1), ba(x, y, z, mx, my, mz, 2),
                      ba(x, y, z, mx, my, mz, 3)};
    double K = sqrt(kx * kx + ky * ky + kz * kz);
    return kvec[i - 1] / (N * K) + (K / (2 * N * N)) * (1 - (th * th / 4) / sqrt(pow(th, 4) / 16 + Th))
                                   * (bvec[0] * dkvec[0] + bvec[1] * dkvec[1] + bvec[2] * dkvec[2]);
}
