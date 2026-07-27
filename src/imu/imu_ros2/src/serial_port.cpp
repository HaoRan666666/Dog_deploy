#include "serial_port.h"

#include <cerrno>
#include <cstring>

#include <fcntl.h>    // open, O_RDWR, O_NOCTTY
#include <termios.h>  // termios, tcgetattr, tcsetattr, cfsetospeed
#include <unistd.h>   // read, write, close

SerialPort::SerialPort() = default;

SerialPort::~SerialPort() {
    close();  // 析构时自动关闭串口
}

bool SerialPort::open(const std::string &device, int baud_rate) {
    close();  // 先关闭已打开的串口

    // 以读写方式打开，O_NOCTTY 防止成为控制终端
    fd_ = ::open(device.c_str(), O_RDWR | O_NOCTTY);
    if (fd_ < 0) {
        fprintf(stderr, "Failed to open %s: %s\n", device.c_str(), strerror(errno));
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // 获取当前串口配置
    if (tcgetattr(fd_, &tty) != 0) {
        fprintf(stderr, "tcgetattr failed: %s\n", strerror(errno));
        close();
        return false;
    }

    // 设置输入输出波特率
    int speed = baudToConstant(baud_rate);
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    // 控制标志：8N1 数据格式，无硬件流控，启用接收
    tty.c_cflag &= ~PARENB;      // 无校验位
    tty.c_cflag &= ~CSTOPB;      // 1 个停止位
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;          // 8 个数据位
    tty.c_cflag &= ~CRTSCTS;     // 关闭 RTS/CTS 硬件流控
    tty.c_cflag |= CREAD | CLOCAL;  // 启用接收，忽略调制解调器控制线

    // 本地标志：原始模式（关闭行缓冲、回显、信号字符处理）
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // 输出标志：原始模式（不做换行转换等）
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;

    // 输入标志：关闭软件流控，不做特殊字符处理
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    // 非阻塞读：VMIN=0 无需最小字节数，VTIME=1 超时 0.1 秒
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 1;

    // 立即应用配置
    if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
        fprintf(stderr, "tcsetattr failed: %s\n", strerror(errno));
        close();
        return false;
    }

    return true;
}

void SerialPort::close() {
    if (fd_ >= 0) {
        ::close(fd_);
        fd_ = -1;
    }
}

bool SerialPort::isOpen() const {
    return fd_ >= 0;
}

int SerialPort::read(uint8_t *buf, int max_len) {
    int n = ::read(fd_, buf, max_len);
    if (n < 0) {
        fprintf(stderr, "Serial read error: %s\n", strerror(errno));
        return -1;
    }
    return n;
}

int SerialPort::write(const uint8_t *buf, int len) {
    int n = ::write(fd_, buf, len);
    if (n < 0) {
        fprintf(stderr, "Serial write error: %s\n", strerror(errno));
        return -1;
    }
    return n;
}

void SerialPort::flush() {
    tcflush(fd_, TCIOFLUSH);  // 清空输入输出缓冲区
}

int SerialPort::baudToConstant(int baud_rate) {
    // 将整数波特率映射为 termios 的 Bxxxx 常量
    switch (baud_rate) {
        case 9600:     return B9600;
        case 19200:    return B19200;
        case 38400:    return B38400;
        case 57600:    return B57600;
        case 115200:   return B115200;
        case 230400:   return B230400;
        case 460800:   return B460800;
        case 500000:   return B500000;
        case 576000:   return B576000;
        case 921600:   return B921600;
        case 1000000:  return B1000000;
        case 1152000:  return B1152000;
        case 1500000:  return B1500000;
        case 2000000:  return B2000000;
        case 2500000:  return B2500000;
        case 3000000:  return B3000000;
        case 3500000:  return B3500000;
        case 4000000:  return B4000000;
        default:       return B921600;  // 未识别时默认 921600
    }
}
