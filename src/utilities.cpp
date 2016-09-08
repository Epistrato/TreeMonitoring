#include "utilities.h"

/* flashLED(){
   Flash the LED for visual feedback
*/

void flashLed(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(70);
    digitalWrite(LED_PIN, LOW);
    delay(70);
  }
}
