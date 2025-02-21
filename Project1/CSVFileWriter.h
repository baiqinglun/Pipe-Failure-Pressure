#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <variant>

class CSVFileWriter {
private:
    std::ofstream file;    // 文件输出流

public:
    // 构造函数，接受文件名
    CSVFileWriter(const std::string& filename);

    // 析构函数，确保关闭文件
    ~CSVFileWriter();

    // 写入标题行
    template<typename T>
    void writeHeader(const std::vector<T>& headers);
    //void writeHeader(const std::vector<std::string>& headers);

    // 写入一行数据
    template<typename T>
    void writeRow(const std::vector<T>& row); // 声明模板函数，但实现放在头文件中

    // 检查文件是否打开
    bool isOpen() const;
};

// 模板函数实现
template<typename T>
void  CSVFileWriter::writeRow(const std::vector<T>& row) {
    for (size_t i = 0; i < row.size(); ++i) {
        // 提取变体的值并写入
        std::visit([this, i, size = row.size()](const auto& arg) {
            file << arg << (i < size - 1 ? "," : "");
            }, row[i]);
    }
    file << "\n"; // 换行
}

// 写入标题行
template<typename T>
void CSVFileWriter::writeHeader(const std::vector<T>& headers) {
    writeRow(headers);
}