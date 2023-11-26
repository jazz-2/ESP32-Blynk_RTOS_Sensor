// https://github.com/jazz-2

#include "LED_display.h"

void DispAll()
{
    digitalWrite(A, low_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, low_);
    digitalWrite(E, low_);
    digitalWrite(F_, low_);
    digitalWrite(G, low_);
    digitalWrite(dot, low_);
}
void DispClear()
{
    digitalWrite(A, high_);
    digitalWrite(B, high_);
    digitalWrite(C, high_);
    digitalWrite(D, high_);
    digitalWrite(E, high_);
    digitalWrite(F_, high_);
    digitalWrite(G, high_);
    digitalWrite(dot, high_);
}
void DispDot()
{
    digitalWrite(A, high_);
    digitalWrite(B, high_);
    digitalWrite(C, high_);
    digitalWrite(D, high_);
    digitalWrite(E, high_);
    digitalWrite(F_, high_);
    digitalWrite(G, high_);
    digitalWrite(dot, low_);
}
void Disp0(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, low_);
    digitalWrite(E, low_);
    digitalWrite(F_, low_);
    digitalWrite(G, high_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp1(uint8_t dot2)
{
    digitalWrite(A, high_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, high_);
    digitalWrite(E, high_);
    digitalWrite(F_, high_);
    digitalWrite(G, high_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp2(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, low_);
    digitalWrite(C, high_);
    digitalWrite(D, low_);
    digitalWrite(E, low_);
    digitalWrite(F_, high_);
    digitalWrite(G, low_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp3(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, low_);
    digitalWrite(E, high_);
    digitalWrite(F_, high_);
    digitalWrite(G, low_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp4(uint8_t dot2)
{
    digitalWrite(A, high_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, high_);
    digitalWrite(E, high_);
    digitalWrite(F_, low_);
    digitalWrite(G, low_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp5(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, high_);
    digitalWrite(C, low_);
    digitalWrite(D, low_);
    digitalWrite(E, high_);
    digitalWrite(F_, low_);
    digitalWrite(G, low_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp6(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, high_);
    digitalWrite(C, low_);
    digitalWrite(D, low_);
    digitalWrite(E, low_);
    digitalWrite(F_, low_);
    digitalWrite(G, low_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp7(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, high_);
    digitalWrite(E, high_);
    digitalWrite(F_, high_);
    digitalWrite(G, high_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp8(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, low_);
    digitalWrite(E, low_);
    digitalWrite(F_, low_);
    digitalWrite(G, low_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void Disp9(uint8_t dot2)
{
    digitalWrite(A, low_);
    digitalWrite(B, low_);
    digitalWrite(C, low_);
    digitalWrite(D, low_);
    digitalWrite(E, high_);
    digitalWrite(F_, low_);
    digitalWrite(G, low_);
    if (dot2 == 0)
    {
        digitalWrite(dot, high_);
    }
    else
    {
        digitalWrite(dot, low_);
    }
}
void DispError()
{
    digitalWrite(A, low_);
    digitalWrite(B, high_);
    digitalWrite(C, high_);
    digitalWrite(D, low_);
    digitalWrite(E, high_);
    digitalWrite(F_, high_);
    digitalWrite(G, high_);
    digitalWrite(dot, high_);
}
void DispMinus()
{
    digitalWrite(A, high_);
    digitalWrite(B, high_);
    digitalWrite(C, high_);
    digitalWrite(D, high_);
    digitalWrite(E, high_);
    digitalWrite(F_, high_);
    digitalWrite(G, low_);
    digitalWrite(dot, high_);
}
void DispFirstDigit()
{
    digitalWrite(D1, low_);
    digitalWrite(D3, low_);
    digitalWrite(D4, high_);
}
void DispSecondDigit()
{
    digitalWrite(D1, low_);
    digitalWrite(D3, high_);
    digitalWrite(D4, low_);
}
void DispThirdDigit()
{
    digitalWrite(D1, high_);
    digitalWrite(D3, low_);
    digitalWrite(D4, low_);
}