#pragma once

#include <cstdint>
#include <string>

// Linux 串口 RAII 封装 (基于 termios)
// 使用方式: open(设备路径, 波特率) → read/write → 析构自动关闭
class SerialPort {
public:
    SerialPort();
    ~SerialPort();

    // 禁止拷贝，防止 fd_ 被多次关闭
    SerialPort(const SerialPort &) = delete;
    SerialPort &operator=(const SerialPort &) = delete;

    // 打开串口设备，配置为 8N1 原始模式，返回是否成功
    bool open(const std::string &device, int baud_rate);
    // 关闭串口
    void close();
    bool isOpen() const;

    // 读取数据，返回实际读取字节数，出错返回 -1
    int read(uint8_t *buf, int max_len);
    // 写入数据，返回实际写入字节数
    int write(const uint8_t *buf, int len);
    // 清空收发缓冲区
    void flush();

private:
    int fd_ = -1;  // 串口文件描述符
    // 将整数波特率映射为 termios 波特率常量 (如 921600 → B921600)
    static int baudToConstant(int baud_rate);
};
