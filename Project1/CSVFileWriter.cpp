#include "CSVFileWriter.h"

// 构造函数
CSVFileWriter::CSVFileWriter(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filename);
    }
}

// 析构函数
CSVFileWriter::~CSVFileWriter() {
    if (file.is_open()) {
        file.close();
    }
}



// 检查文件是否打开
bool CSVFileWriter::isOpen() const {
    return file.is_open();
}
