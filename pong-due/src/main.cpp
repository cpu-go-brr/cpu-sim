#include <Arduino.h>
#include <Wire.h>
#include "Intel4004.hpp"
#include <FastLED.h>

#define LEFT_UP_PIN 2
#define LEFT_DOWN_PIN 3
#define RIGHT_UP_PIN 4
#define RIGHT_DOWN_PIN 5

#define DATA_PIN 6
#define NUM_LEDS 256
#define BRIGHTNESS 16
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define C CRGB::DarkGoldenrod
#define B CRGB::Black

// Define the array of leds
Intel4004 cpu{};
CRGB leds[NUM_LEDS];
CRGB colors[3] = {B, CRGB::Red, CRGB::Green};

bool pong[16][6] = {{1, 1, 1, 1, 0, 0}, {1, 0, 1, 0, 0, 0}, {1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0}, {0, 1, 0, 1, 0, 0}, {0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0}, {0, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0}, {0, 1, 0, 1, 0, 1}, {0, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0}};

#define UPDATES_PER_SECOND 100

int getPos(int x, int y)
{
    return (16 * y) + ((y % 2 == 0) ? x : 15 - x);
}

void setup()
{

    Serial.begin(9600);

    for (int i = 0; i < 16; i++)
    {
        leds[getPos(i, 0)] = CRGB::DarkMagenta;
        leds[getPos(i, 9)] = CRGB::DarkMagenta;
    }

    for (int x = 16; x-- > 0;)
        for (int y = 6; y-- > 0;)
            leds[getPos(x, 15 - y)] = pong[x][y] ? C : B;

    pinMode(DATA_PIN, OUTPUT);

    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    


    pinMode(LEFT_UP_PIN, INPUT_PULLUP);
    pinMode(LEFT_DOWN_PIN, INPUT_PULLUP);
    pinMode(RIGHT_UP_PIN, INPUT_PULLUP);
    pinMode(RIGHT_DOWN_PIN, INPUT_PULLUP);

    bitset prog[] = {0x50, 0x13, 0x50, 0x0E, 0x50, 0x91, 0x50, 0x62, 0x50, 0x32, 0x40, 0x02, 0x40, 0x2E, 0x26, 0xFF, 0x26, 0x00, 0xC0, 0x2C, 0x37, 0x2E, 0x11, 0x2A, 0x54, 0x20, 0x00, 0xF0, 0x2D, 0xD1, 0xE0, 0xAA, 0xB0, 0x21, 0xD2, 0xE0, 0xAB, 0xB0, 0xDF, 0xB1, 0x21, 0xD2, 0xE0, 0x20, 0x00, 0xC0, 0x50, 0x0E, 0x40, 0x2E, 0x20, 0x00, 0x21, 0xEA, 0xF6, 0x1A, 0x4C, 0xF1, 0xD7, 0x9B, 0x14, 0x4C, 0xAB, 0xB0, 0xDF, 0xB1, 0x21, 0xD0, 0xE0, 0x6B, 0xAB, 0xB0, 0x21, 0xD2, 0xE0, 0xC0, 0xF6, 0x1A, 0x61, 0xF1, 0xAB, 0x14, 0x61, 0xB0, 0xDF, 0xB1, 0x21, 0xD0, 0xE0, 0xAB, 0xF8, 0xBB, 0xAB, 0xB0, 0x21, 0xD2, 0xE0, 0xC0, 0x20, 0x00, 0x21, 0xEA, 0xF5, 0x1A, 0x7B, 0xF1, 0xAA, 0x14, 0x7B, 0xB0, 0xD0, 0xB1, 0x21, 0xD0, 0xE0, 0xAA, 0xF8, 0xBA, 0xAA, 0xB0, 0x21, 0xD2, 0xE0, 0xF5, 0x1A, 0x90, 0xF1, 0xD7, 0x9A, 0x14, 0x90, 0xAA, 0xB0, 0xD0, 0xB1, 0x21, 0xD0, 0xE0, 0x6A, 0xAA, 0xB0, 0x21, 0xD2, 0xE0, 0xC0, 0xAC, 0xB0, 0xAD, 0xB1, 0xAD, 0xF2, 0xF4, 0x1C, 0xA2, 0xF1, 0xAB, 0x90, 0x1C, 0xA2, 0xF0, 0x9E, 0xBE, 0xAD, 0xF8, 0x1C, 0xAE, 0xF1, 0xAA, 0x90, 0x1C, 0xAE, 0xF0, 0x9E, 0xBE, 0xAC, 0x1C, 0xB4, 0xF0, 0x9F, 0xBF, 0xD7, 0xF1, 0x9C, 0x1C, 0xBC, 0xF0, 0x9F, 0xBF, 0xAD, 0xF1, 0x8E, 0xBD, 0xAC, 0xF1, 0x8F, 0xBC, 0x21, 0xD0, 0xE0, 0x2D, 0xD1, 0xE0, 0xAD, 0x14, 0x2E, 0xF4, 0x14, 0x2E, 0xC0};
    cpu.flash_rom(prog, sizeof(prog) / sizeof(bitset));
}

void draw()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            leds[getPos(x, y + 1)] = colors[cpu.ram_mem[x + 16 * y].val()];
        }
    }
}

void setControl(bool left_up, bool left_down, bool right_up, bool right_down)
{
    int data = 0b1000 * left_up + 0b0100 * left_down + 0b0010 * right_up + 0b0001 * right_down;
    printf("%d\n", data);
    cpu.set(data, cpu.rom_port(0));
}

unsigned char led_pos = 0;

uint8_t i = 0;
void loop()
{
    setControl(!digitalRead(LEFT_UP_PIN),!digitalRead(LEFT_DOWN_PIN),!digitalRead(RIGHT_UP_PIN),!digitalRead(RIGHT_DOWN_PIN));


    while (cpu.get(R6).val() == 0)
        cpu.simulate();

    cpu.simulate();



    for(int j = 10; j --> 0;)
    {
        FastLED.show();
        for (int x = 16; x-- > 0;)
        {
            CHSV hsv;
            hsv.h = i + 4*x;
            hsv.s = 255;
            hsv.v = 128;
            CHSV hsv2;
            hsv2.h = i + 4*x + 128;
            hsv2.s = 255;
            hsv2.v = 128;

            CHSV hsv3 = rgb2hsv_approximate(CRGB::DarkMagenta);
            hsv3.v = 100 + 4*x + i;

            if(hsv3.v < 100) hsv3.v = 100;
            // if(hsv.v > 200) hsv.v = 200;

            CRGB color;
            CRGB color2;
            CRGB color3;
            hsv2rgb_rainbow(hsv, color);
            hsv2rgb_rainbow(hsv2, color2);
            hsv2rgb_rainbow(hsv3, color3);

            leds[getPos(x, 0)] = color3;
            leds[getPos(x, 9)] = color3;

            for(int y_cord = 8; y_cord --> 0;)
            {
                if(cpu.ram_mem[x + 16 * y_cord].val() != 1)
                    continue;

                    colors[1] = color;
            }

            for (int i = 0; i < 16; i++)
            for (int y = 6; y-- > 0;)
                leds[getPos(x, 15 - y)] = pong[x][y] ? color : B;
        }
        delay(8);

        i--;
    }
    draw();

    



    // while (!Serial.available())
    //     ;

    // while (Serial.available())
    //     Serial.read();
}
