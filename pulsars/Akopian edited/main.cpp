#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "functions.h"


/*
void showVector(const char *msg, double x, double y, double z) {
    std::cout << msg << "x: " << x << " | "
              << msg << "y: " << y << " | "
              << msg << "z: " << z << "\n";
}
*/
int main() {
    std::ofstream par;
    //par.open ("data.dat");

    //geometry of observing surface
    double ox = sin(chi + beta);
    double oy = 0;
    double oz = cos(chi + beta);
    double p1x = cos(chi + beta);
    double p1y = 0;
    double p1z = -sin(chi + beta);
    double p2x = 0;
    double p2y = 1;
    double p2z = 0;

    // intensity
    double I;
    //double sumInt;

    // initial phase
    double fi0;

    // a-parameters
    double a1, a2;
    double a1min = -0.25;
    double a1max = 0.25; // this is the perpendicular to movement coordinate
    double a2min = -0.25;
    double a2max = 0.25; // this is along the movement
    double astep = 0.25;

    // fi-parameters
    double fi;
    double fimax = 15;
    double fistep = 0.5;

    double Rmax = 1000 * Rs;
    double Tmax = Rmax / c;
    double rx, ry, rz;
    double mx, my, mz = cos(chi);

    double kx, ky, kz;

    double t, dt = 0.00005; // normally 0.00005

    // counter
    double counter = 0;
    for (fi = -fimax; fi <= fimax; fi += fistep) {
        for (a1 = a1min; a1 <= a1max; a1 += astep) {
            for (a2 = a2min; a2 <= a2max; a2 += astep) {
                ++counter;
            }
        }
    }
    double cmax = counter;
    counter = 0;

    int run_count = 0;
    for (fi = -fimax; fi <= fimax; fi += fistep) {
        // cycle for fi
        std::string iter_str = std::to_string(run_count);
        int nzeros = 0;
        if (run_count < 10) {
            nzeros = 2;
        } else if (run_count < 100) {
            nzeros = 1;
        }
        ++run_count;
        iter_str = std::string(nzeros, '0').append(iter_str);
        std::string s_file = "Omode_";
        s_file += iter_str;//to_string(run_count);
        s_file +="_phi_";
        s_file += std::to_string(fi);
        s_file +=".dat";
        par.open(s_file);

        //sumInt = 0;
        // cout << fi << endl << endl; // counter
        fi0 = fi * pi / 180;
        std::cout << (int) (counter * 100 / cmax) << " %" << std::endl; // counter
        //int temppppp = 0;
        for (a1 = a1min; a1 <= a1max; a1 += astep) {
            // cycle for a1
            std::cout << (counter * 100 / cmax) << " %" << std::endl; // counter
            for (a2 = a2min; a2 <= a2max; a2 += astep) {//
                ++counter;
                I = 0;
                rx = Rmax * ox + a1 * p1x + a2 * p2x;
                ry = Rmax * oy + a1 * p1y + a2 * p2y;
                rz = Rmax * oz + a1 * p1z + a2 * p2z;
                kx = -ox;
                ky = -oy;
                kz = -oz;
                for (t = Tmax; t >= -Tmax / 10; t -= dt) {
                    if (r(rx, ry, rz) < 1.2 * Rs)
                        break;

                    mx = sin(chi) * cos(fi0 + Omega * t);
                    my = sin(chi) * sin(fi0 + Omega * t);

                    if (theta(rx, ry, rz, mx, my, mz, kx, ky, kz) > pi / 2.) {
                        break;
                    }

                    rx += c * dkndki(rx, ry, rz, mx, my, mz, kx, ky, kz, 1) * dt;
                    ry += c * dkndki(rx, ry, rz, mx, my, mz, kx, ky, kz, 2) * dt;
                    rz += c * dkndki(rx, ry, rz, mx, my, mz, kx, ky, kz, 3) * dt;

                    kx += -c * dkndri(rx, ry, rz, mx, my, mz, kx, ky, kz, 1) * dt;
                    ky += -c * dkndri(rx, ry, rz, mx, my, mz, kx, ky, kz, 2) * dt;
                    kz += -c * dkndri(rx, ry, rz, mx, my, mz, kx, ky, kz, 3) * dt;

                    mx = sin(chi) * cos(fi0 + Omega * (t - dt));
                    my = sin(chi) * sin(fi0 + Omega * (t - dt));

                    I += g(rx, ry, rz, mx, my, mz) * exp(-A * pow((r(rx, ry, rz) - Rm), 2) / (Rm * Rm))
                         * exp(-pow(theta(rx, ry, rz, mx, my, mz, kx, ky, kz) * gamma_a(rx, ry, rz, mx, my, mz), 2));
                }
                par << a1 << ", " << a2 << ", " << I << std::endl;
            }
        }
        par << std::endl;
        par.close();
    }
    //par.close();
    return 0;
}