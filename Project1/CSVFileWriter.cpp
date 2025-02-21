#include "CSVFileWriter.h"

// ���캯��
CSVFileWriter::CSVFileWriter(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("�޷����ļ�: " + filename);
    }
}

// ��������
CSVFileWriter::~CSVFileWriter() {
    if (file.is_open()) {
        file.close();
    }
}



// ����ļ��Ƿ��
bool CSVFileWriter::isOpen() const {
    return file.is_open();
}
