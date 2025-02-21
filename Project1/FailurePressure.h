#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<variant>
#include<stdexcept>

using namespace std;

// 其中t是管壁厚度，D是管道直径；
// d是缺陷深度，l是缺陷长度
// SMYS是屈服极限
// UTS是强度极限


// 声明一个可变参数类型，使用 std::variant 来支持多种类型
using Params = std::vector<std::variant<float, double, int>>;

class FailurePressureAbstract {
public:
    virtual double calucate(const Params& params) = 0;
    virtual ~FailurePressureAbstract() = default; // 虚析构函数
};

class ASMEB31G2009 : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

class RSTRENG085dL : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

class PCORRC : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

class DNV_RP_F101 : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

class C_Fer : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

class AGANG18 : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

class Netto : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

class RAM_PIPE_REQUAL : public FailurePressureAbstract {
public:
    double calucate(const Params& params) override;
};

// 上下文类
class FailurePressureContext {
private:
    std::unique_ptr<FailurePressureAbstract> strategy; // 使用unique_ptr来管理策略的生命周期
public:
    explicit FailurePressureContext(std::unique_ptr<FailurePressureAbstract> newStrategy)
        : strategy(move(newStrategy)) {
    }

    void setStrategy(std::unique_ptr<FailurePressureAbstract> newStrategy);

    double executeStrategy(const Params& params);
};