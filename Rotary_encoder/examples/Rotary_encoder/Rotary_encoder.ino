#include <Rotary_Encoder.h>

Rotary_Encoder encoder(2, 3); //This line can be further improve. do improve the library as well on the algrithms and the portmanipulation

int count = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  count += encoder.ticks();
  Serial.print(F("count: "));
  Serial.println(count);

}
