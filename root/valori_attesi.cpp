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

    auto amp_m = new TF1("Tensione Mid", V_m, 1E3, 3E4, 11);
    amp_m->SetParameters(5., RW, RM, RT, RLW, RLM, RG, LW, LM, CM, CT);

    double res_freq = amp_m->GetMaximumX(1E3, 3E4);
    std::cout << "Frequenza di risonanza = " << res_freq << std::endl;

    // calcola differenza di fase twetter e woofer al crossover
    auto phase_w = new TF1("Fase woofer", p_w, 1E3, 3E4, 11);
    phase_w->SetParameters(5., RW, RM, RT, RLW, RLM, RG, LW, LM, CM, CT);
    double phase_w_val = phase_w->Eval(fc);
    std::cout << "Fase woofer al crossover = " << phase_w_val << std::endl;
    auto phase_t = new TF1("Fase tweeter", p_t, 1E3, 3E4, 11);
    phase_t->SetParameters(5., RW, RM, RT, RLW, RLM, RG, LW, LM, CM, CT);
    double phase_t_val = phase_t->Eval(fc);
    std::cout << "Fase tweeter al crossover = " << phase_t_val << std::endl;
    double phase_diff = -phase_w_val + phase_t_val;
    std::cout << "Differenza di fase woofer-tweeter al crossover = " << phase_diff << std::endl;
}