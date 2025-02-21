#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <variant>

class CSVFileWriter {
private:
    std::ofstream file;    // �ļ������

public:
    // ���캯���������ļ���
    CSVFileWriter(const std::string& filename);

    // ����������ȷ���ر��ļ�
    ~CSVFileWriter();

    // д�������
    template<typename T>
    void writeHeader(const std::vector<T>& headers);
    //void writeHeader(const std::vector<std::string>& headers);

    // д��һ������
    template<typename T>
    void writeRow(const std::vector<T>& row); // ����ģ�庯������ʵ�ַ���ͷ�ļ���

    // ����ļ��Ƿ��
    bool isOpen() const;
};

// ģ�庯��ʵ��
template<typename T>
void  CSVFileWriter::writeRow(const std::vector<T>& row) {
    for (size_t i = 0; i < row.size(); ++i) {
        // ��ȡ�����ֵ��д��
        std::visit([this, i, size = row.size()](const auto& arg) {
            file << arg << (i < size - 1 ? "," : "");
            }, row[i]);
    }
    file << "\n"; // ����
}

// д�������
template<typename T>
void CSVFileWriter::writeHeader(const std::vector<T>& headers) {
    writeRow(headers);
}