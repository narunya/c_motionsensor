#pragma once
#include "hardware/i2c.h"

#define LCD_CHARACTER 1
#define LCD_COMMAND 0

// LCD command and flag definitions
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET 0x20
#define LCD_SETDDRAMADDR 0x80

#define LCD_ENTRYLEFT 0x02
#define LCD_DISPLAYON 0x04
#define LCD_2LINE 0x08

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE_BIT 0x04

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);
void lcd_char(char value);
void lcd_send_command(uint8_t value);
void lcd_data(uint8_t data);

void lcd_search(char* buffer);
void lcd_warning(char* buffer);
void lcd_alarm(char* buffer);
