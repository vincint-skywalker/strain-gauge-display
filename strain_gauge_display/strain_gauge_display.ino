// Strain Gage
//   created by Huang Lihao

#include <U8g2lib.h>
#include <U8x8lib.h>

#include <sstream>
#include <iomanip>

#define G1	A0
#define G2	A1
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

const char *s;
std::stringstream ss;
int g1, g2;
float V1, V2, Va, V0;
float strain;

#define Vref 3.3
#define E Vref
#define K 1.78
#define ModuleAmp 250



void setup() {
  // Set Serial to debug
  Serial.begin(9600);

  // u8x8
  u8x8.begin();

  // u8x8 start up page
  u8x8.setFont(u8x8_font_inr21_2x4_f);
  u8x8.drawString(0,0,"Strain");
  u8x8.drawString(7,4,"Gauge");
  delay(2000);
  u8x8.clear();

  u8x8.setFont(u8x8_font_artossans8_r);
  u8x8.drawString(0,1,"created by");
  u8x8.setFont(u8x8_font_7x14B_1x2_f);
  u8x8.drawString(3,4,"Huang Lihao");
  delay(2000);
  u8x8.clear();

  V0 = Vref * 0.5;
  std::showpos(ss);
  std::internal(ss);
}

void loop() {
  g1 = analogRead(G1);
  g2 = analogRead(G2);
  V1 = g1 / 1023.0 * Vref;
  V2 = g2 / 1023.0 * Vref;
  Va = (V1 + V2) * 0.5;
  strain = 4.0 * (Va- V0) / (ModuleAmp * K * E);

  Serial.print("strain = "); Serial.print(String(strain)); Serial.print(", ");
  Serial.print("V1 = "); Serial.print(String(V1)); Serial.print(", ");
  Serial.print("V2 = "); Serial.print(String(V2)); Serial.print("\n");


  ss.str("");
  ss << std::setiosflags(std::ios::fixed) << std::setprecision(3) << strain *100;
  s = ss.str().data();
  u8x8.setFont(u8x8_font_inb21_2x4_n);
  u8x8.drawString(0,0,s);
  
  ss.str("");
  ss << std::setiosflags(std::ios::fixed) << std::setprecision(3) << strain * 200000;
  s = ss.str().data();
  u8x8.setFont(u8x8_font_inb21_2x4_n);
  u8x8.drawString(0,4,s);
  
  u8x8.setFont(u8x8_font_inb21_2x4_f);
  u8x8.drawString(13,0,"%");
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.drawString(13,6,"kN");
  delay(1000);
}

