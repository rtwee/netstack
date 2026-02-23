
#ifndef NETSTACK_LOG_H
#define NETSTACK_LOG_H

#include <stdint.h>
#include <stddef.h>

// 日志级别
typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

/**
* @brief 设置日志级别
* @param level 日志级别
* @return 无
**/
void log_set_level(log_level_t level);

/**
* @brief 获取当前日志级别
* @return 当前日志级别
**/
log_level_t log_get_level();

/**
* @brief 记录一条日志消息
* @param level 日志级别
* @param component 组件名称（如 "TCP", "UDP", "IP" 等）
* @param format 格式字符串（类似于 printf 的格式）
* @param ... 可变参数列表，根据格式字符串提供的格式传递参数
* @return 无
**/
void log_message(log_level_t level, const char *component,const char* format, ...);

/** 
* @brief 以十六进制格式记录数据包内容
* @component 组件名称（如 "TCP", "UDP", "IP" 等）
* @data 数据包内容的指针
* @len 数据包内容的长度
**/
void log_packet_dump(const char *component, const void *data, size_t length);

#define LOG_DEBUG(component, format, ...) log_message(LOG_DEBUG, component, format,##__VA_ARGS__)
#define LOG_INFO(component, format, ...) log_message(LOG_INFO, component, format, ##__VA_ARGS__)
#define LOG_WARN(component, format, ...) log_message(LOG_WARN, component, format, ##__VA_ARGS__)
#define LOG_ERROR(component, format, ...) log_message(LOG_ERROR, component, format, ##__VA_ARGS__)

#endif