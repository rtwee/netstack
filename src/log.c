#include "netstack/log.h"

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

// 设置当前日志级别，默认为 LOG_DEBUG
static log_level_t current_log_level = LOG_DEBUG;

/* 日志级别数组，用于格式化输出 */
static const char* log_level_strings[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR"
};

void log_set_level(log_level_t level) {
    current_log_level = level;
}

log_level_t log_get_level() {
    return current_log_level;
}

/*
* @brief获取当前时间戳字符串
* @param buffer 存储时间戳的缓冲区
* @param size 缓冲区大小
*/
static void get_timestamp(char* buffer, size_t size) {
    // 获取当前时间戳，格式为 YYYY-MM-DD HH:MM:SS
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}


void log_message(log_level_t level, const char *component, const char* format, ...) {
    char timestamp[32];
    va_list args;
    
    if(level < current_log_level) {
        return; // 如果日志级别低于当前设置的级别，则不记录日志
    }

    get_timestamp(timestamp, sizeof(timestamp));

    //输出日志头部
    printf("[%s] [%s] [%s]: ", timestamp, log_level_strings[level], component);

    //处理可变参数
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n"); // 换行
    fflush(stdout); // 确保日志立即输出
}

void log_packet_dump(const char *component, const void *data, size_t length) {
    const uint8_t * bytes = (const uint8_t *)data;
    char timestamp[32];

    if(LOG_DEBUG < current_log_level) {
        return; // 仅在调试级别时记录数据包内容
    }

    get_timestamp(timestamp, sizeof(timestamp));
    //输出转储头部
    printf("[%s] [DEBUG] [%s]: Packet Dump (%zu bytes):\n", timestamp, component, length);

    // 按行输出十六进制转储（每行16字节）
    for(size_t i = 0; i < length; i += 16) {
        printf("%04zx: ", i); // 输出偏移地址
        for(size_t j = 0; j < 16 ; j++) {
            if(i + j < length) {
                printf("%02x ", bytes[i + j]); // 输出十六进制字节
            } else {
                printf("   "); // 填充空格
            }
        }
        printf(" "); // 分隔十六进制和ASCII部分
        for(size_t j = 0; j < 16 && i + j < length; j++) {
            unsigned char c = bytes[i + j];
            printf("%c", (c >= 32 && c < 127) ? c : '.');
        }
        printf("\n");
    }

    fflush(stdout); // 确保日志立即输出
}