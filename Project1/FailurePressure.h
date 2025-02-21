#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<variant>
#include<stdexcept>

using namespace std;

// ����t�ǹܱں�ȣ�D�ǹܵ�ֱ����
// d��ȱ����ȣ�l��ȱ�ݳ���
// SMYS����������
// UTS��ǿ�ȼ���


// ����һ���ɱ�������ͣ�ʹ�� std::variant ��֧�ֶ�������
using Params = std::vector<std::variant<float, double, int>>;

class FailurePressureAbstract {
public:
    virtual double calucate(const Params& params) = 0;
    virtual ~FailurePressureAbstract() = default; // ����������
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

// ��������
class FailurePressureContext {
private:
    std::unique_ptr<FailurePressureAbstract> strategy; // ʹ��unique_ptr��������Ե���������
public:
    explicit FailurePressureContext(std::unique_ptr<FailurePressureAbstract> newStrategy)
        : strategy(move(newStrategy)) {
    }

    void setStrategy(std::unique_ptr<FailurePressureAbstract> newStrategy);

    double executeStrategy(const Params& params);
};