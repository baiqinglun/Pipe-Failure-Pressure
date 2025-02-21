#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<variant>
#include<stdexcept>

#include "FailurePressure.h"
#include "CSVFileWriter.h"

int main()
{
    std::string name = "X52";
    Params X52_SMYS = { 6.3, 462.6, 6.0, 200.0, 435.5 };
    Params X52_UTS = { 6.3, 462.6, 6.0, 200.0, 530.0 };

    using RowParams = std::vector<std::variant<double, std::string>>;

    RowParams ASMEB31G2009_res_list = { "ASMEB31G2009" };
    RowParams RSTRENG085dL_res_list = { "RSTRENG085dL" };
    RowParams PCORRC_res_list = { "PCORRC" };
    RowParams DNV_RP_F101_res_list = { "DNV_RP_F101" };
    RowParams C_Fer_res_list = { "C_Fer" };
    RowParams Netto_res_list = { "Netto" };
    RowParams RAM_PIPE_REQUAL_res_list = { "RAM_PIPE_REQUAL" };

    std::vector<RowParams*> rows;
    rows.push_back(&ASMEB31G2009_res_list );
    rows.push_back(&RSTRENG085dL_res_list );
    rows.push_back(&PCORRC_res_list );
    rows.push_back(&DNV_RP_F101_res_list);
    rows.push_back(&C_Fer_res_list );
    rows.push_back(&Netto_res_list );
    rows.push_back(&RAM_PIPE_REQUAL_res_list );

    std::vector<double> t = { 1, 2, 3, 4, 5, 6 };
    for (size_t i = 0; i < t.size(); i++)
    {
        X52_SMYS[2] = t[i];
        X52_UTS[2] = t[i];

        // 创建上下文，初始采用FIFO策略
        FailurePressureContext context(make_unique<ASMEB31G2009>());
        ASMEB31G2009_res_list.push_back( context.executeStrategy(X52_SMYS)  );

        context.setStrategy(make_unique<RSTRENG085dL>());
        RSTRENG085dL_res_list.push_back(context.executeStrategy(X52_SMYS));

        context.setStrategy(make_unique<PCORRC>());
        PCORRC_res_list.push_back(context.executeStrategy(X52_UTS) );

        context.setStrategy(make_unique<DNV_RP_F101>());
        DNV_RP_F101_res_list.push_back(context.executeStrategy(X52_UTS) );

        context.setStrategy(make_unique<C_Fer>());
        C_Fer_res_list.push_back(context.executeStrategy(X52_SMYS) );

        context.setStrategy(make_unique<Netto>());
        Netto_res_list.push_back(context.executeStrategy(X52_SMYS) );

        context.setStrategy(make_unique<RAM_PIPE_REQUAL>());
        RAM_PIPE_REQUAL_res_list.push_back(context.executeStrategy(X52_UTS));
    }
    

    try {
        // 创建 CSVFileWriter 对象
        CSVFileWriter csvWriter(name + ".csv");

        RowParams header = { "method"};
        header.insert(header.end(), t.begin(), t.end());

        // 写入表头
        csvWriter.writeHeader(header);

        // 写入多行数据
        for (const auto& entry : rows)
        {
            csvWriter.writeRow(*entry);
        }

        std::cout << "数据已成功写入 " << name << ".csv" << std::endl;
        std::cout << "大功告成 " << name << ".csv" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1; // 返回错误代码
    }

	return 0;
}