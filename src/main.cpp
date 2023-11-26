// https://github.com/jazz-2
#include <Arduino.h>
#include "LED_display.h"
#include <math.h>

#define buzzer 27
#define buzzerPWMchannel 0

float c = 261.6256;
float d = 293.6648;
float e = 329.6276;
float f = 349.2282;
float g = 391.9954;
float a = 440.0000;
float h = 493.8833;
#define loudBuzzer 2000

float melody[] = {c, d, e, f, g, a, h};

#include "credentials.h" //or use code snippet below

// /* Fill-in information from Blynk Device Info here */
// #define BLYNK_TEMPLATE_ID ""
// #define BLYNK_TEMPLATE_NAME ""
// #define BLYNK_AUTH_TOKEN ""
// // Your WiFi credentials.
// // Set password to "" for open networks.
// char ssid[] = "";
// char pass[] = "";

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

//============================================================
#include <freertos/FreeRTOS.h>

static TaskHandle_t taskADC_read = NULL;
static TaskHandle_t taskDisplay = NULL;
static TaskHandle_t taskLED_info = NULL;
static TaskHandle_t taskBLynkStart = NULL;
static TaskHandle_t task_Sound = NULL;

#define ADC1_0 36
#define LED_internal LED_BUILTIN
static volatile uint16_t ADC_airQuality = 0;
static const uint16_t treshold = 1500;
static volatile uint8_t LED_of_truth = 0;

////===========================================================================
#define DispAvailableDigits 3
uint8_t DisplayDigitsAmount = 3;
const uint8_t numToDisp_size = 6;
char numToDisp[numToDisp_size + 1] = "000";

void setup_LED_Display()
{
    pinMode(D1, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    digitalWrite(D1, high_);
    digitalWrite(D3, high_);
    digitalWrite(D4, high_);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F_, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(dot, OUTPUT);
}

void resetValues(uint8_t *i, bool *dotPrinted, uint8_t *i_2)
{
    if (*i >= DisplayDigitsAmount)
    {
        *i = 0;
        *dotPrinted = false;
        *i_2 = 0;
    }
}
void DispDigits(void *params)
{

    while (1)
    {
        static uint8_t i = 0;

        static bool dotPrinted = false;
        bool dotFound = false;
        for (uint8_t n = 0; n < numToDisp_size; n++)
        {
            if (numToDisp[n] == '.')
            {
                dotFound = true;
            }
            if (numToDisp[n] == '\0')
            {
                DisplayDigitsAmount = n;
                break;
            }
        }
        if (dotFound == false && DisplayDigitsAmount > DispAvailableDigits)
        {
            DisplayDigitsAmount = DisplayDigitsAmount - 1;
        }

        static uint8_t i_2 = 0;
        if (i_2 == 0)
        {
            DispFirstDigit();
        }
        else if (i_2 == 1)
        {
            DispSecondDigit();
        }
        else if (i_2 == 2)
        {
            DispThirdDigit();
        }
        i_2++;

        if (numToDisp[i] == 'a')
        {
            DispAll();
        }
        else if (numToDisp[i] == 'b')
        {
            DispClear();
        }
        else if (numToDisp[i] == 'c')
        {
            DispError();
        }
        else if (numToDisp[i] == '-')
        {
            DispMinus();
        }
        else if (numToDisp[i] == '.')
        {
            DispDot();
        }
        else if (numToDisp[i + 1] == '.')
        {
            if (numToDisp[i] == '0')
            {
                Disp0(1);
            }
            else if (numToDisp[i] == '1')
            {
                Disp1(1);
            }
            else if (numToDisp[i] == '2')
            {
                Disp2(1);
            }
            else if (numToDisp[i] == '3')
            {
                Disp3(1);
            }
            else if (numToDisp[i] == '4')
            {
                Disp4(1);
            }
            else if (numToDisp[i] == '5')
            {
                Disp5(1);
            }
            else if (numToDisp[i] == '6')
            {
                Disp6(1);
            }
            else if (numToDisp[i] == '7')
            {
                Disp7(1);
            }
            else if (numToDisp[i] == '8')
            {
                Disp8(1);
            }
            else if (numToDisp[i] == '9')
            {
                Disp9(1);
            }
        }
        else if (numToDisp[i] == '0')
        {
            Disp0();
        }
        else if (numToDisp[i] == '1')
        {
            Disp1();
        }
        else if (numToDisp[i] == '2')
        {
            Disp2();
        }
        else if (numToDisp[i] == '3')
        {
            Disp3();
        }
        else if (numToDisp[i] == '4')
        {
            Disp4();
        }
        else if (numToDisp[i] == '5')
        {
            Disp5();
        }
        else if (numToDisp[i] == '6')
        {
            Disp6();
        }
        else if (numToDisp[i] == '7')
        {
            Disp7();
        }
        else if (numToDisp[i] == '8')
        {
            Disp8();
        }
        else if (numToDisp[i] == '9')
        {
            Disp9();
        }

        if (dotPrinted == false && numToDisp[i + 1] == '.')
        {
            dotPrinted = true;
            i = i + 2;
        }
        else
        {
            i++;
        }

        resetValues(&i, &dotPrinted, &i_2);

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void DispChange()
{
    memset(numToDisp, '\0', sizeof(numToDisp));
    itoa(ADC_airQuality, numToDisp, 10);
    for (int i = 0; i < numToDisp_size; i++)
    {
        Serial.print(numToDisp[i]);
    }
    Serial.println();
}

void LED_info(void *params)
{
    uint16_t LED_period = 0;
    while (1)
    {
        uint32_t currentTime = millis();
        static uint32_t lastTime;
        if (LED_of_truth == 1)
        {
            LED_period = 2000;
            if (currentTime - lastTime >= LED_period)
            {
                lastTime = currentTime;
            }
            if (currentTime - lastTime <= 100)
            {
                digitalWrite(LED_internal, HIGH);
            }
            else
            {
                digitalWrite(LED_internal, LOW);
            }
        }
        else if (LED_of_truth == 2)
        {
            LED_period = 500;
            if (currentTime - lastTime >= LED_period)
            {
                lastTime = currentTime;
            }
            if (currentTime - lastTime <= 100)
            {
                digitalWrite(LED_internal, HIGH);
            }
            else
            {
                digitalWrite(LED_internal, LOW);
            }
        }
        else if (LED_of_truth == 3)
        {
            LED_period = 150;
            if (currentTime - lastTime >= (LED_period + 1))
            {
                lastTime = currentTime;
            }
            if (currentTime - lastTime <= LED_period / 2)
            {
                digitalWrite(LED_internal, HIGH);
            }
            else
            {
                digitalWrite(LED_internal, LOW);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(75 - 10));
    }
}
const uint16_t medium_AirQuality = treshold - 500;
bool alarmCondition = false;
bool belowAlarm = true;
volatile bool stopSendingWhenSound = false;
void SendToCloud()
{
    static bool playOnlyOnce = false;

    Blynk.virtualWrite(V0, ADC_airQuality);

    Serial.println((String) "sent to the virtual pin: " + ADC_airQuality);

    if (belowAlarm)
    {
        playOnlyOnce = false;
    }

    if (alarmCondition)
    {
        String msg = "bad";
        Blynk.virtualWrite(V2, msg);

        if (playOnlyOnce == false)
        {
            playOnlyOnce = true;
            stopSendingWhenSound = true;
            vTaskResume(task_Sound);
        }
    }
    else if (ADC_airQuality < treshold && ADC_airQuality >= medium_AirQuality)
    {
        String msg = "medium";
        Blynk.virtualWrite(V2, msg);
    }
    else if (ADC_airQuality < medium_AirQuality)
    {
        String msg = "OK";
        Blynk.virtualWrite(V2, msg);
    }
}
static portMUX_TYPE my_spinlock = portMUX_INITIALIZER_UNLOCKED;
void ADC_read(void *params)
{
    bool bad_AirQuality_DetectedForEvent = false;
    bool bad_AirQuality_DetectedForEAutomations = false;
    uint16_t changeTreshold = 200;
    uint16_t samplesNumber = 75;
    uint32_t ADC_airQuality_SUM = 0;

    while (1)
    {

        ADC_airQuality_SUM = 0;
        for (uint16_t i = 0; i < samplesNumber; i++)
        {
            ADC_airQuality_SUM = ADC_airQuality_SUM + analogRead(ADC1_0);
        }

        taskENTER_CRITICAL(&my_spinlock);
        ADC_airQuality = ADC_airQuality_SUM / samplesNumber;

        alarmCondition = ADC_airQuality >= treshold;
        belowAlarm = ADC_airQuality < (treshold - changeTreshold);

        if (alarmCondition)
        {
            LED_of_truth = 3;
        }
        else if (ADC_airQuality < treshold && ADC_airQuality >= medium_AirQuality)
        {
            LED_of_truth = 2;
        }
        else if (ADC_airQuality < medium_AirQuality)
        {
            LED_of_truth = 1;
        }

        if (alarmCondition && bad_AirQuality_DetectedForEAutomations == false)
        {
            bad_AirQuality_DetectedForEAutomations = true;
        }
        else if (belowAlarm && bad_AirQuality_DetectedForEAutomations == true)
        {
            bad_AirQuality_DetectedForEAutomations = false;
        }
        if (bad_AirQuality_DetectedForEAutomations == true && ADC_airQuality < treshold)
        {
            ADC_airQuality = treshold;
        }
        taskEXIT_CRITICAL(&my_spinlock);

        DispChange();

        if (stopSendingWhenSound == false)
        {
            if (bad_AirQuality_DetectedForEvent == false && alarmCondition)
            {
                bad_AirQuality_DetectedForEvent = true;
                Blynk.logEvent("polluted_air");
                SendToCloud();
            }
            else if (bad_AirQuality_DetectedForEvent == true && belowAlarm)
            {
                bad_AirQuality_DetectedForEvent = false;
                Blynk.logEvent("air_is_clean");
                SendToCloud();
            }

            static TickType_t lastTickCount = 0;
            bool periodicUpdate = xTaskGetTickCount() - lastTickCount >= 4000;
            if (periodicUpdate)
            {
                lastTickCount = xTaskGetTickCount();
                SendToCloud();
            }
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void BLynkStart(void *params)
{
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    vTaskDelete(NULL);
}

void morse_S()
{
    for (int i = 0; i < 3; i++)
    {
        if (belowAlarm)
        {
            break;
        }
        ledcWriteTone(buzzerPWMchannel, loudBuzzer);
        vTaskDelay(pdTICKS_TO_MS(100));
        ledcWriteTone(buzzerPWMchannel, 0);
        vTaskDelay(pdTICKS_TO_MS(100));
    }
}
void morse_O()
{
    for (int i = 0; i < 3; i++)
    {
        if (belowAlarm)
        {
            break;
        }
        ledcWriteTone(buzzerPWMchannel, loudBuzzer);
        vTaskDelay(pdTICKS_TO_MS(200));
        ledcWriteTone(buzzerPWMchannel, 0);
        vTaskDelay(pdTICKS_TO_MS(200));
    }
}
void Sound(void *params)
{
    uint8_t sizeOfTArray = sizeof(melody) / sizeof(melody[0]);
    while (1)
    {

        morse_S();
        morse_O();
        morse_S();
        vTaskDelay(pdTICKS_TO_MS(200));

        for (uint8_t i = 0; i < sizeOfTArray; i++)
        {
            if (belowAlarm)
            {
                break;
            }

            ledcWriteTone(buzzerPWMchannel, (int)melody[i]);
            vTaskDelay(pdTICKS_TO_MS(200));
            ledcWriteTone(buzzerPWMchannel, 0);
            vTaskDelay(pdTICKS_TO_MS(30));
        }

        stopSendingWhenSound = false;
        vTaskSuspend(task_Sound);
    }
}

void setup()
{
    Serial.begin(115200);

    analogReadResolution(12);
    analogSetWidth(12);

    ledcSetup(buzzerPWMchannel, 500, 1);
    ledcAttachPin(buzzer, buzzerPWMchannel);

    pinMode(LED_internal, OUTPUT);
    setup_LED_Display();
    xTaskCreatePinnedToCore(LED_info,
                            "LED_info",
                            configMINIMAL_STACK_SIZE + 600,
                            NULL,
                            1,
                            &taskLED_info,
                            1);
    xTaskCreatePinnedToCore(DispDigits,
                            "LED display",
                            configMINIMAL_STACK_SIZE + 600,
                            NULL,
                            1,
                            &taskDisplay,
                            1);
    xTaskCreatePinnedToCore(BLynkStart,
                            "BLynkStart",
                            4000,
                            NULL,
                            1,
                            &taskBLynkStart,
                            1);
    xTaskCreatePinnedToCore(Sound,
                            "Sound",
                            configMINIMAL_STACK_SIZE + 1000,
                            NULL,
                            1,
                            &task_Sound,
                            1);
    vTaskSuspend(task_Sound);
    xTaskCreatePinnedToCore(ADC_read,
                            "sensor read",
                            4500,
                            NULL,
                            1,
                            &taskADC_read,
                            1);

    vTaskDelete(NULL);
}
void loop()
{
    ;
}