#include "netstack/log.h"

int main() {
    // 设置日志级别为 LOG_INFO
    log_set_level(LOG_INFO);

    // 记录不同级别的日志消息
    LOG_DEBUG("TCP", "This is a debug message."); // 不会被记录，因为当前级别是 LOG_INFO
    LOG_INFO("TCP", "This is an info message.");  // 会被记录
    LOG_WARN("TCP", "This is a warning message."); // 会被记录
    LOG_ERROR("TCP", "This is an error message."); // 会被记录

    // 记录一个数据包的十六进制内容
    uint8_t packet_data[] = {0x45, 0x00, 0x00, 0x54, 0x00, 0x00, 0x40, 0x00, 0x40, 0x01};
    log_packet_dump("IP", packet_data, sizeof(packet_data));

    return 0;
}