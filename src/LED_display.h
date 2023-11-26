// https://github.com/jazz-2
#ifndef SOFTWARE_PWM
#define SOFTWARE_PWM
#include <Arduino.h>

#define D1 14
#define D3 33
#define D4 32

#define E 21
#define D 22
#define dot 23
#define C 19
#define G 18
#define B 5

#define F_ 17
#define A 16

#define LED_DISPLAY_COMMON_ANODE 1
#if LED_DISPLAY_COMMON_ANODE == 1
#define low_ 0
#define high_ 1
#else
#define high_ 0
#define low_ 1
#endif


void DispAll();
void DispClear();
void DispDot();
void Disp0(uint8_t dot2 = 0);
void Disp1(uint8_t dot2 = 0);
void Disp2(uint8_t dot2 = 0);
void Disp3(uint8_t dot2 = 0);
void Disp4(uint8_t dot2 = 0);
void Disp5(uint8_t dot2 = 0);
void Disp6(uint8_t dot2 = 0);
void Disp7(uint8_t dot2 = 0);
void Disp8(uint8_t dot2 = 0);
void Disp9(uint8_t dot2 = 0);
void DispError();
void DispMinus();
void DispFirstDigit();
void DispSecondDigit();
void DispThirdDigit();

#endif