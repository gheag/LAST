#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "modbus.h"
#include <string>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <bitset>
#include <mutex>

// ���������� /////////////////////////
int var;
int start_flag;
uint16_t global_work = 0;
uint16_t amount = 2;
bool is_start;
std::string str;
int flag_butt_start = 0;
bool is_shape;          // � ����� �� ������
bool can_input[25];     // ������� �� ������ (������ ������ ������������� ���������� ������)
int setpoint;           // �������
bool inshape;           // ������ � �����?


float time_Tmax = 0.0005;
float time_Tmin = 1;
bool first_timer_compl;
bool second_timer_compl;
bool timer_start;
bool timer_end=0;
bool faza_proizv_complite;
int Tmax_step_complite = 0;
bool last = 0;

bool flag_setpoint = 0;


int butt_setings[15][7]; // ������ � ����������� ������ (����� ������, ���������� �� x, ���������� �� y, ������, ������, ������� �� ������, )


std::string ip1, ip2, ip3, ip4, ip;

// �������
int setpoints[26] = {-999, -999, -70, 150, -999, -999, -999, -999, 4, 2, 10, 10, 7, 0, -0.3, 115, 155, 10, 10, 10, 10000, 1, 15,  15, 15 };

uint16_t normirovannaya_proizv, old_proizv = 0; // ���� ���������� ������������� ����������� ��� �������� (���� ������)

// state of button
bool isOver = false;
bool isPressedInside = false;

// state of mouse
bool isMousePressed = false;

const bool one = 1;
const bool zero = 0;

//////////////////////////////////////





