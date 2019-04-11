/*
 * UART    : TF Mini LiDAR
 * I2C     : LCD
 * D18/D19 : Touch (used as interrupt pin)
 * A2/A3   : Potentiometer
 */

#include <Arduino.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

const int pinButton     = PIN_D19;
const int potentiometer = A3;

unsigned char g_r = 128;
unsigned char g_g = 128;
unsigned char g_b = 128;
int           g_meter;

int toggleMenu = 0;

void pushed()
{
  toggleMenu++;
  toggleMenu %= 4;
}

void setup()
{
  Serial.begin(115200);

  // LiDAR
  Serial2.begin(115200);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Touch sensor
  pinMode(pinButton, INPUT);
  attachInterrupt(pinButton, pushed, FALLING);
}

void getTFminiData(int* distance, int* strength)
{
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  if(Serial2.available()) {
    rx[i] = Serial2.read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
      }
      i = 0;
    } else {
      i++;
    }
  }
}

void showMenu(int menu)
{
  char title[16];
  static int nowMenu = -1;
  unsigned char *target;
  int i;

  if (nowMenu != menu) {
    nowMenu = menu;

    lcd.clear();

    switch (menu) {
    case 0:
      snprintf(title, 16, "Distance: ");
      lcd.setCursor(0, 0);
      lcd.print(title);

      snprintf(title, 16, "Strength: ");
      lcd.setCursor(0, 1);
      lcd.print(title);
      break;
    case 1 ... 3:
      switch (menu) {
      case 1:
        snprintf(title, 16, "Display(R): ");
        target = &g_r;
        break;
      case 2:
        snprintf(title, 16, "Display(G): ");
        target = &g_g;
        break;
      case 3:
        snprintf(title, 16, "Display(B): ");
        target = &g_b;
        break;
      }
      lcd.setCursor(0, 0);
      lcd.print(title);

      lcd.setCursor(0, 1);
      for (i = 0; i < *target / 16; i++) {
        lcd.write(0xff);
      }
      g_meter = analogRead(potentiometer);
      break;
    default:
      break;
    }
  }
}

void showResult(int menu)
{
  switch (menu) {
  case 0: // LiDAR
    {
      char str[7];
      int distance = 0;
      int strength = 0;
      getTFminiData(&distance, &strength);
      if (distance) {
        getTFminiData(&distance, &strength);
        if (distance) {
          printf("Distance: %4d Strength: %4d\n",
                 distance, strength);

          snprintf(str, sizeof(str), "%4d  ", distance);
          lcd.setCursor(10, 0);
          lcd.print(str);

          snprintf(str, sizeof(str), "%4d  ", strength);
          lcd.setCursor(10, 1);
          lcd.print(str);
        }
      }
    }
    break;

  case 1 ... 3: // LCD color setting
    {
      int i;
      int value = analogRead(potentiometer);
      int diff = g_meter - value;
      unsigned char *target;

      if (abs(diff) < 50) { // noise filter
        break;
      }

      g_meter = value;

      switch (menu) {
      case 1:
        target = &g_r;
        break;
      case 2:
        target = &g_g;
        break;
      case 3:
        target = &g_b;
        break;
      }

      *target += diff / 3;

      printf("(r,g,b)=(%d,%d,%d) diff=%d level=%d\n",
             g_r, g_g, g_b, diff, *target/16);

      lcd.setCursor(0, 1);
      for (i = 0; i < 16; i++) {
        if (i < *target / 16) {
          lcd.write(0xff);
        } else {
          lcd.write(0xfe);
        }
      }
      lcd.setRGB(g_r, g_g, g_b);
    }
    break;
  }
}

void loop()
{
  showMenu(toggleMenu);
  showResult(toggleMenu);
}

