#include <cmath>
#include <cstdio>
#include <iostream>

#include "formule2.cpp"

void calc()
{
    double RG{50};
    double RW{3293};
    double LW{47.2E-3};
    double RLW{120};

    double RM{3287};
    double LM{46.9E-3};
    double CM{4.76E-9};
    double RLM{120.7};

    double RT{3295};
    double CT{4.76E-9};

    // parametri: RW, RLW, RT, LW, CT
    double A = CT * CT * RT * RT * LW * LW;
    double B = CT * CT * RT * RT * (RLW * RLW + 2 * RLW * RW);
    double C = -RW * RW;

    // discriminante
    double discr = B * B + 4 * A * (-C); // 4*A*R_w^2

    // soluzione per x = omega^2
    double x = (-B + std::sqrt(discr)) / (2 * A);

    // omega_c e f_c
    double omega_c = std::sqrt(x);
    double fc = omega_c / (2 * M_PI);

    std::cout << "Frequenza di crossover (woofer-tweeter) = " << fc << " Hz " << std::endl;
    double fr = 1.0 / (2 * M_PI * sqrt(LM * CM));
    std::cout << "Frequenza di risonanza approssimata (midrange) = " << fr << " Hz" << std::endl;

    auto func_m = new TF1("Tensione Mid", V_m, 1E3, 3E4, 11);
    func_m->SetParameters(5., RW, RM, RT, RLW, RLM, RG, LW, LM, CM, CT);

    double res_freq = func_m->GetMaximumX(1E3, 3E4);
    std::cout << "Frequenza di risonanza = " << res_freq << std::endl;
}