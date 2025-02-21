#include "FailurePressure.h"

// 上下文类
void FailurePressureContext::setStrategy(std::unique_ptr<FailurePressureAbstract> newStrategy) {
    strategy = move(newStrategy);
}

double FailurePressureContext::executeStrategy(const Params& params) {
    if (strategy) {
        return strategy.get()->calucate(params);
    }
}


double ASMEB31G2009::calucate(const Params& params) {
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double SMYS = std::get<double>(params[4]);

    double S_flow = SMYS * 1.1;
    double z = pow(l, 2) / (D * t);

    double M = 0.0;
    if (z > 50) {
        M = 0.032 * z + 3.3;
    }
    else {
        M = pow(1 + 0.6275 * z - 0.003375 * pow(z, 2), 0.5);
    }

    double failure_pressure = S_flow * 2 * t / D * (1 - 0.85 * d / t) / (1 - 0.85 * d / t / M);
    std::cout << "调用 ASMEB31G2009 成功" << failure_pressure << std::endl;
    return failure_pressure;
};

double RSTRENG085dL::calucate(const Params& params) {
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double SMYS = std::get<double>(params[4]);

    double S_flow = SMYS + 68.95;
    double z = pow(l, 2) / (D * t);

    double M = 0.0;
    if (z > 50) {
        M = 0.032 * z + 3.3;
    }
    else {
        M = pow(1 + 0.6275 * z - 0.003375 * pow(z, 2), 0.5);
    }

    double failure_pressure = S_flow * 2 * t / D * (1 - 0.85 * d / t) / (1 - 0.85 * d / t / M);
    std::cout << "调用 RSTRENG085dL 成功" << failure_pressure << std::endl;
    return failure_pressure;
}

double PCORRC::calucate(const Params& params) {
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double UTS = std::get<double>(params[4]);

    double M = 1 - exp((-0.157 * l) / (pow(D / 2, 0.5) * (t - d)));

    double failure_pressure = 2 * t * UTS / D * (1 - d * M / t);
    cout << "调用 PCORRC 成功" << failure_pressure << endl;
    return failure_pressure;
}

double DNV_RP_F101::calucate(const Params& params)
{
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double UTS = std::get<double>(params[4]);

    double M = pow(1 + 0.31 * pow(l, 2) / (D * t), 0.5);

    double failure_pressure = 2 * t * UTS / (D - t) * ((1 - d / t) / (1 - d / t / M));
    cout << "调用 DNV_RP_F101 成功" << failure_pressure << endl;
    return failure_pressure;
}

double C_Fer::calucate(const Params& params)
{
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double SMYS = std::get<double>(params[4]);

    double z = pow(l, 2) / (D * t);
    double S_flow = SMYS * 0.9;

    double M = 0.0;
    if (z > 50) {
        M = 0.032 * z + 3.3;
    }
    else {
        M = pow(1 + 0.6275 * z - 0.003375 * pow(z, 2), 0.5);
    }

    double A0 = l * t;
    double A = l * d;

    double failure_pressure = 2 * t * S_flow / D * (1 - A/A0) / (1- A / A0 / M);
    cout << "调用 C_Fer 成功" << failure_pressure << endl;
    return failure_pressure;
}

double AGANG18::calucate(const Params& params)
{
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double SMYS = std::get<double>(params[4]);

    return 0.0;
}

double Netto::calucate(const Params& params)
{
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double SMYS = std::get<double>(params[4]);

    double failure_pressure = 1.1 * SMYS * 2 * t / D * (1 - 0.9435 * pow(d / t, 1.6) * pow(l / D, 0.4));
    cout << "调用 Netto 成功" << failure_pressure << endl;
    return failure_pressure;
}

double RAM_PIPE_REQUAL::calucate(const Params& params)
{
    double t = std::get<double>(params[0]);
    double D = std::get<double>(params[1]);
    double d = std::get<double>(params[2]);
    double l = std::get<double>(params[3]);
    double UTS = std::get<double>(params[4]);

    double SCF = 1 + 2 * pow(2 * d / D, 0.5);
    double failure_pressure = 2.2 * (t - d) * UTS / (D - t) / SCF;
    cout << "调用 RAM_PIPE_REQUAL 成功" << failure_pressure << endl;
    return failure_pressure;
}
