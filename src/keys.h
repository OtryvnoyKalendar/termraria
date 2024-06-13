#pragma once

// перед закрытием игры
void BeforeCloseProgram();

// одновременное нажатие клавиш

#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <linux/kernel.h>

// Методы для начала работы с библиотекой и завершением работы
void OpenKeysMode();

void CloseKeysMode();

// Получаем состояние клавиатуры
void RefreshKeyboardStatus();

int GetKeyState(int Key);
