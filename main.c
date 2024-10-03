#define MCU_NAME STM8L152
#define USE_LSE

#include "stm8l15x.h"
#include "stm8l15x_clk.h"
#include "stm8l15x_lcd.h"
#include "stm8l15x_rtc.h"
#include "stm8l15x_pwr.h"
#include "stm8l15x_spi.h"
#include "stm8l15x_gpio.h"

// segment addressing for LCD high byte register, low byte bit mask
#define FourOuterBars   (256 *  0 +   2)
#define BarDownRight    (256 *  0 +   4)
#define BarUpLeft       (256 *  3 +  32)
#define BarDownLeft     (256 *  3 + 128)
#define BarUpRight      (256 * 10 +  32)
#define ModeThung       (256 *  0 +   8)
#define ModeWave        (256 *  4 +   4)
#define ModeDiamond     (256 *  7 +  64)
#define ModePlus        (256 * 11 +   4)
#define ModeLight       (256 * 11 +   8)
#define ModeTooth       (256 * 12 +   1)
#define Star1           (256 *  4 +   2)
#define Star2           (256 *  0 +  32)
#define Star3           (256 *  0 +  16)
#define Star4           (256 * 11 +   1)
#define Star5           (256 *  7 +  16)
#define Seg1O           (256 * 11 +  16)
#define Seg1OR          (256 *  7 + 128)
#define Seg1OL          (256 *  8 +   1)
#define Seg1M           (256 *  4 +   8)
#define Seg1UR          (256 *  0 +  64)
#define Seg1UL          (256 *  1 +   1)
#define Seg1U           (256 *  0 + 128)
#define Seg2O           (256 * 11 +  32)
#define Seg2OR          (256 *  8 +   2)
#define Seg2OL          (256 *  8 +   4)
#define Seg2M           (256 *  4 +  64)
#define Seg2UL          (256 *  1 +   4)
#define Seg2UR          (256 *  4 +  16)
#define Seg2UM          (256 *  4 +  32)
#define Seg2U           (256 *  1 +   2)
#define Seg3O           (256 * 11 + 128)
#define Seg3OR          (256 *  8 +   8)
#define Seg3OL          (256 *  8 +  16)
#define Seg3M           (256 *  5 +   1)
#define Seg3UL          (256 *  1 +  16)
#define Seg3UR          (256 *  4 + 128)
#define Seg3U           (256 *  1 +   8)
#define Seg4O           (256 * 12 +   2)
#define Seg4OR          (256 *  8 +  32)
#define Seg4OL          (256 *  9 +   4)
#define Seg4M           (256 *  5 +  64)
#define Seg4UL          (256 *  2 +   4)
#define Seg4UR          (256 *  5 +   2)
#define Seg4U           (256 *  1 +  32)
#define SegPP           (256 * 11 +  64)
#define EyeBrow         (256 *  7 +   2)
#define EyeRight        (256 *  7 +   4)
#define MouthSad        (256 *  7 +   8)
#define MouthEdge       (256 * 10 +  64)
#define MouthHappy      (256 * 10 + 128)
#define Twinkle         (256 *  3 +  64)
#define Batt            (256 *  7 +  32)
#define Timer           (256 * 12 +  64)

uint8_t ramRegisterList[13] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t ramRegisterListOld[13] = {0,0,0,0,0,0,0,0,0,0,0,0};

void delay_ms(uint16_t ms) {
    // Einfache Delay-Schleife
    for(uint16_t i = 0; i < ms; i++) {
        for(uint16_t j = 0; j < 160; j++); // Zeitlich abhängig von Taktfrequenz
    }
}

void LCD_Initx(void) {
    // LCD Clock einschalten
    
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);
    
    #ifdef USE_LSE
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
    #else
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
    #endif

    // LCD-Treiber initialisieren (1/4 duty, 1/3 bias, Frequenz, etc.)
    LCD_Init(LCD_Prescaler_2, LCD_Divider_31, LCD_Duty_1_4, LCD_Bias_1_3, LCD_VoltageSource_Internal);
    
    /* Mask register
    For declare the segements used.
    in the Discovery we use 0 to 16 segments. */
    LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);
    LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0x3F);
    LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0x4);
    
    
    /* To set contrast to mean value */
    LCD_ContrastConfig(LCD_Contrast_2V6);
    
    LCD_DeadTimeConfig(LCD_DeadTime_0);
    LCD_PulseOnDurationConfig(LCD_PulseOnDuration_4);
    // LCD-Treiber aktivieren
    LCD_Cmd(ENABLE);
    
}

void LCD_Clear(void) {
    uint8_t counter = 0;
  
    for (counter = LCD_RAMRegister_0; counter <= LCD_RAMRegister_12; counter++)
    {
        LCD->RAM[counter] = 0;
    }
}

void LCD_WriteSegment(uint8_t position) {
    // Alle Segmente ausschalten
    LCD_Clear();

    // An dieser Stelle wird ein LCD-Segment ein- oder ausgeschaltet
    // LCD_WriteRAM verwendet LCDRAM-Register, um bestimmte Segmente zu steuern.
    // Wir setzen ein Beispiel für Segmentsteuerung, je nach Position
    //LCD_WriteRAM(LCD_RAMRegister_1, position);
    //LCD_WriteRAM(LCD_RAMRegister_2, position);
    //LCD_WriteRAM(LCD_RAMRegister_3, position);
    //LCD_WriteRAM(LCD_RAMRegister_4, position);
    LCD_WriteRAM(LCD_RAMRegister_12, position);
    if(position == 1) {
        LCD_WriteRAM(LCD_RAMRegister_0, 2);
    }
    
    
    // RAM-Update-Request
    //LCD_UpdateDisplayRequest();
}

void setRamReg(int LCDdef) {
    uint8_t bitMask = LCDdef & 0xff;
    int ramRegister = LCDdef >> 8;
    ramRegisterList[ramRegister] |= bitMask;
}

void delRamReg(int LCDdef) {
    uint8_t bitMask = LCDdef & 0xff;
    int ramRegister = LCDdef >> 8;
    ramRegisterList[ramRegister] &= ~bitMask;
}

void syncRamReg(void) {
    for (int i = 0; i < 13; i++)
    {
        if (ramRegisterList[i] != ramRegisterListOld[i]) {
            ramRegisterListOld[i] = ramRegisterList[i];
            LCD_WriteRAM(i, ramRegisterList[i]);
        }
    }
}

void LCD_WriteDigit1(int value) {
    switch (value)
    {
    case 0:
        setRamReg(Seg1O);
        setRamReg(Seg1OL);
        setRamReg(Seg1OR);
        delRamReg(Seg1M);
        setRamReg(Seg1UL);
        setRamReg(Seg1UR);
        setRamReg(Seg1U);
        break;
    case 1:
        delRamReg(Seg1O);
        delRamReg(Seg1OL);
        setRamReg(Seg1OR);
        delRamReg(Seg1M);
        delRamReg(Seg1UL);
        setRamReg(Seg1UR);
        delRamReg(Seg1U);
        break;
    case 2:
        setRamReg(Seg1O);
        delRamReg(Seg1OL);
        setRamReg(Seg1OR);
        setRamReg(Seg1M);
        setRamReg(Seg1UL);
        delRamReg(Seg1UR);
        setRamReg(Seg1U);
        break;
    case 3:
        setRamReg(Seg1O);
        delRamReg(Seg1OL);
        setRamReg(Seg1OR);
        setRamReg(Seg1M);
        delRamReg(Seg1UL);
        setRamReg(Seg1UR);
        setRamReg(Seg1U);
        break;
    case 4:
        delRamReg(Seg1O);
        setRamReg(Seg1OL);
        setRamReg(Seg1OR);
        setRamReg(Seg1M);
        delRamReg(Seg1UL);
        setRamReg(Seg1UR);
        delRamReg(Seg1U);
        break;
    case 5:
        setRamReg(Seg1O);
        setRamReg(Seg1OL);
        delRamReg(Seg1OR);
        setRamReg(Seg1M);
        delRamReg(Seg1UL);
        setRamReg(Seg1UR);
        setRamReg(Seg1U);
        break;
    case 6:
        setRamReg(Seg1O);
        setRamReg(Seg1OL);
        delRamReg(Seg1OR);
        setRamReg(Seg1M);
        setRamReg(Seg1UL);
        setRamReg(Seg1UR);
        setRamReg(Seg1U);
        break;
    case 7:
        setRamReg(Seg1O);
        delRamReg(Seg1OL);
        setRamReg(Seg1OR);
        delRamReg(Seg1M);
        delRamReg(Seg1UL);
        setRamReg(Seg1UR);
        delRamReg(Seg1U);
        break;
    case 8:
        setRamReg(Seg1O);
        setRamReg(Seg1OL);
        setRamReg(Seg1OR);
        setRamReg(Seg1M);
        setRamReg(Seg1UL);
        setRamReg(Seg1UR);
        setRamReg(Seg1U);
        break;
    case 9:
        setRamReg(Seg1O);
        setRamReg(Seg1OL);
        setRamReg(Seg1OR);
        setRamReg(Seg1M);
        delRamReg(Seg1UL);
        setRamReg(Seg1UR);
        setRamReg(Seg1U);
        break;
    default:
        break;
    }
}

void LCD_WriteDigit2(int value) {
    switch (value)
    {
    case 0:
        setRamReg(Seg2O);
        setRamReg(Seg2OL);
        setRamReg(Seg2OR);
        delRamReg(Seg2M);
        setRamReg(Seg2UL);
        setRamReg(Seg2UR);
        setRamReg(Seg2U);
        break;
    case 1:
        delRamReg(Seg2O);
        delRamReg(Seg2OL);
        setRamReg(Seg2OR);
        delRamReg(Seg2M);
        delRamReg(Seg2UL);
        setRamReg(Seg2UR);
        delRamReg(Seg2U);
        break;
    case 2:
        setRamReg(Seg2O);
        delRamReg(Seg2OL);
        setRamReg(Seg2OR);
        setRamReg(Seg2M);
        setRamReg(Seg2UL);
        delRamReg(Seg2UR);
        setRamReg(Seg2U);
        break;
    case 3:
        setRamReg(Seg2O);
        delRamReg(Seg2OL);
        setRamReg(Seg2OR);
        setRamReg(Seg2M);
        delRamReg(Seg2UL);
        setRamReg(Seg2UR);
        setRamReg(Seg2U);
        break;
    case 4:
        delRamReg(Seg2O);
        setRamReg(Seg2OL);
        setRamReg(Seg2OR);
        setRamReg(Seg2M);
        delRamReg(Seg2UL);
        setRamReg(Seg2UR);
        delRamReg(Seg2U);
        break;
    case 5:
        setRamReg(Seg2O);
        setRamReg(Seg2OL);
        delRamReg(Seg2OR);
        setRamReg(Seg2M);
        delRamReg(Seg2UL);
        setRamReg(Seg2UR);
        setRamReg(Seg2U);
        break;
    case 6:
        setRamReg(Seg2O);
        setRamReg(Seg2OL);
        delRamReg(Seg2OR);
        setRamReg(Seg2M);
        setRamReg(Seg2UL);
        setRamReg(Seg2UR);
        setRamReg(Seg2U);
        break;
    case 7:
        setRamReg(Seg2O);
        delRamReg(Seg2OL);
        setRamReg(Seg2OR);
        delRamReg(Seg2M);
        delRamReg(Seg2UL);
        setRamReg(Seg2UR);
        delRamReg(Seg2U);
        break;
    case 8:
        setRamReg(Seg2O);
        setRamReg(Seg2OL);
        setRamReg(Seg2OR);
        setRamReg(Seg2M);
        setRamReg(Seg2UL);
        setRamReg(Seg2UR);
        setRamReg(Seg2U);
        break;
    case 9:
        setRamReg(Seg2O);
        setRamReg(Seg2OL);
        setRamReg(Seg2OR);
        setRamReg(Seg2M);
        delRamReg(Seg2UL);
        setRamReg(Seg2UR);
        setRamReg(Seg2U);
        break;
    default:
        break;
    }
}

void LCD_WriteDigit3(int value) {
    switch (value)
    {
    case 0:
        setRamReg(Seg3O);
        setRamReg(Seg3OL);
        setRamReg(Seg3OR);
        delRamReg(Seg3M);
        setRamReg(Seg3UL);
        setRamReg(Seg3UR);
        setRamReg(Seg3U);
        break;
    case 1:
        delRamReg(Seg3O);
        delRamReg(Seg3OL);
        setRamReg(Seg3OR);
        delRamReg(Seg3M);
        delRamReg(Seg3UL);
        setRamReg(Seg3UR);
        delRamReg(Seg3U);
        break;
    case 2:
        setRamReg(Seg3O);
        delRamReg(Seg3OL);
        setRamReg(Seg3OR);
        setRamReg(Seg3M);
        setRamReg(Seg3UL);
        delRamReg(Seg3UR);
        setRamReg(Seg3U);
        break;
    case 3:
        setRamReg(Seg3O);
        delRamReg(Seg3OL);
        setRamReg(Seg3OR);
        setRamReg(Seg3M);
        delRamReg(Seg3UL);
        setRamReg(Seg3UR);
        setRamReg(Seg3U);
        break;
    case 4:
        delRamReg(Seg3O);
        setRamReg(Seg3OL);
        setRamReg(Seg3OR);
        setRamReg(Seg3M);
        delRamReg(Seg3UL);
        setRamReg(Seg3UR);
        delRamReg(Seg3U);
        break;
    case 5:
        setRamReg(Seg3O);
        setRamReg(Seg3OL);
        delRamReg(Seg3OR);
        setRamReg(Seg3M);
        delRamReg(Seg3UL);
        setRamReg(Seg3UR);
        setRamReg(Seg3U);
        break;
    case 6:
        setRamReg(Seg3O);
        setRamReg(Seg3OL);
        delRamReg(Seg3OR);
        setRamReg(Seg3M);
        setRamReg(Seg3UL);
        setRamReg(Seg3UR);
        setRamReg(Seg3U);
        break;
    case 7:
        setRamReg(Seg3O);
        delRamReg(Seg3OL);
        setRamReg(Seg3OR);
        delRamReg(Seg3M);
        delRamReg(Seg3UL);
        setRamReg(Seg3UR);
        delRamReg(Seg3U);
        break;
    case 8:
        setRamReg(Seg3O);
        setRamReg(Seg3OL);
        setRamReg(Seg3OR);
        setRamReg(Seg3M);
        setRamReg(Seg3UL);
        setRamReg(Seg3UR);
        setRamReg(Seg3U);
        break;
    case 9:
        setRamReg(Seg3O);
        setRamReg(Seg3OL);
        setRamReg(Seg3OR);
        setRamReg(Seg3M);
        delRamReg(Seg3UL);
        setRamReg(Seg3UR);
        setRamReg(Seg3U);
        break;
    default:
        break;
    }
}

void LCD_WriteDigit4(int value) {
    switch (value)
    {
    case 0:
        setRamReg(Seg4O);
        setRamReg(Seg4OL);
        setRamReg(Seg4OR);
        delRamReg(Seg4M);
        setRamReg(Seg4UL);
        setRamReg(Seg4UR);
        setRamReg(Seg4U);
        break;
    case 1:
        delRamReg(Seg4O);
        delRamReg(Seg4OL);
        setRamReg(Seg4OR);
        delRamReg(Seg4M);
        delRamReg(Seg4UL);
        setRamReg(Seg4UR);
        delRamReg(Seg4U);
        break;
    case 2:
        setRamReg(Seg4O);
        delRamReg(Seg4OL);
        setRamReg(Seg4OR);
        setRamReg(Seg4M);
        setRamReg(Seg4UL);
        delRamReg(Seg4UR);
        setRamReg(Seg4U);
        break;
    case 3:
        setRamReg(Seg4O);
        delRamReg(Seg4OL);
        setRamReg(Seg4OR);
        setRamReg(Seg4M);
        delRamReg(Seg4UL);
        setRamReg(Seg4UR);
        setRamReg(Seg4U);
        break;
    case 4:
        delRamReg(Seg4O);
        setRamReg(Seg4OL);
        setRamReg(Seg4OR);
        setRamReg(Seg4M);
        delRamReg(Seg4UL);
        setRamReg(Seg4UR);
        delRamReg(Seg4U);
        break;
    case 5:
        setRamReg(Seg4O);
        setRamReg(Seg4OL);
        delRamReg(Seg4OR);
        setRamReg(Seg4M);
        delRamReg(Seg4UL);
        setRamReg(Seg4UR);
        setRamReg(Seg4U);
        break;
    case 6:
        setRamReg(Seg4O);
        setRamReg(Seg4OL);
        delRamReg(Seg4OR);
        setRamReg(Seg4M);
        setRamReg(Seg4UL);
        setRamReg(Seg4UR);
        setRamReg(Seg4U);
        break;
    case 7:
        setRamReg(Seg4O);
        delRamReg(Seg4OL);
        setRamReg(Seg4OR);
        delRamReg(Seg4M);
        delRamReg(Seg4UL);
        setRamReg(Seg4UR);
        delRamReg(Seg4U);
        break;
    case 8:
        setRamReg(Seg4O);
        setRamReg(Seg4OL);
        setRamReg(Seg4OR);
        setRamReg(Seg4M);
        setRamReg(Seg4UL);
        setRamReg(Seg4UR);
        setRamReg(Seg4U);
        break;
    case 9:
        setRamReg(Seg4O);
        setRamReg(Seg4OL);
        setRamReg(Seg4OR);
        setRamReg(Seg4M);
        delRamReg(Seg4UL);
        setRamReg(Seg4UR);
        setRamReg(Seg4U);
        break;
    default:
        break;
    }
}

void LCD_WriteDigit(int digitNumber, int value) {
    switch (digitNumber)
    {
    case 1:
        LCD_WriteDigit1(value);
        break;
    case 2:
        LCD_WriteDigit2(value);
        break;
    case 3:
        LCD_WriteDigit3(value);
        break;
    case 4:
        LCD_WriteDigit4(value);
        break;
    default:
        break;
    }
}

void RTC_InitConfig(void) {
    // Aktivieren der LSE (Low Speed External) für die RTC
    CLK_LSEConfig(CLK_LSE_ON);
    while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);  // Warten, bis LSE bereit ist

    // Aktivieren des RTC-Takts
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);

    // RTC Zugriff aktivieren
    //PWR_RTCAccessCmd(ENABLE);

    // Warten auf RTC Synchronisation
    RTC_WaitForSynchro();

    // RTC Konfiguration: 24-Stunden-Modus, Prescaler
    RTC_InitTypeDef RTC_InitStruct;
    RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
    RTC_InitStruct.RTC_AsynchPrediv = 127;  // Asynchroner Prescaler
    RTC_InitStruct.RTC_SynchPrediv = 255;   // Synchroner Prescaler
    RTC_Init(&RTC_InitStruct);
}

void RTC_SetTimeConfig(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_TimeTypeDef RTC_TimeStruct;

    // Zeit festlegen
    RTC_TimeStruct.RTC_Hours = hours;
    RTC_TimeStruct.RTC_Minutes = minutes;
    RTC_TimeStruct.RTC_Seconds = seconds;

    // Zeit in der RTC setzen
    RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
}

int main(void) {
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_In_PU_No_IT);
    uint8_t tasterSet = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7);
    GPIO_Init(GPIOE, GPIO_Pin_6, GPIO_Mode_In_PU_No_IT);
    uint8_t tasterHM = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);
    // LCD initialisieren
    LCD_Initx();
    // RTC Init
    RTC_InitConfig();
    RTC_SetTimeConfig(0,0,0);
    int tasterHMOld = 0;
    int tasterSetOld = 0;
    // Endlosschleife
    while (1) {
        RTC_TimeTypeDef RTC_TimeStruct;
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
        uint8_t lowMinutes = RTC_TimeStruct.RTC_Minutes % 10;
        uint8_t tenMinutes = (RTC_TimeStruct.RTC_Minutes - lowMinutes) / 10;
        uint8_t lowHours = RTC_TimeStruct.RTC_Hours % 10;
        uint8_t tenHours = (RTC_TimeStruct.RTC_Hours - lowHours) / 10;
        LCD_WriteDigit(1, lowMinutes);
        LCD_WriteDigit(2, tenMinutes);
        LCD_WriteDigit(3, lowHours);
        LCD_WriteDigit(4, tenHours);
        setRamReg(FourOuterBars);
        setRamReg(MouthHappy);
        setRamReg(EyeRight);
        setRamReg(Twinkle);
        setRamReg(Star1);
        setRamReg(Star2);
        setRamReg(Star3);
        setRamReg(Star4);
        tasterSet = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7);
        tasterHM = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);
        if (tasterSet == 0) {
            if (tasterSetOld == 0) {
                tasterSetOld = 1;
                // taster set erkannt (Minuten Einstellung) setzt Sekunden zu 0
                int minutes = RTC_TimeStruct.RTC_Minutes + 1;
                if (minutes > 59) {
                    minutes = 0;
                }
                RTC_SetTimeConfig(RTC_TimeStruct.RTC_Hours, minutes, 0);
            }
        } else {
            tasterSetOld = 0;
        }
        if (tasterHM == 0) {
            if (tasterHMOld == 0) {
                tasterHMOld = 1;
                // taster HM erkannt (Stunden Einstellung)
                int hours = RTC_TimeStruct.RTC_Hours + 1;
                if (hours > 23) {
                    hours = 0;
                }
                RTC_SetTimeConfig(hours, RTC_TimeStruct.RTC_Minutes, RTC_TimeStruct.RTC_Seconds);
            }
        } else {
            tasterHMOld = 0;
        }
        if ((RTC_TimeStruct.RTC_Seconds % 2) == 0) {
            setRamReg(SegPP);
        } else {
            delRamReg(SegPP);
        }
        syncRamReg();
        delay_ms(10); // weniger als 1 Sekunde Verzögerung
    }
}
