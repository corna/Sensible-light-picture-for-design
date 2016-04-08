/*
 * Sensible light picture for design
 * Copyright (C) 2016 Nicola Corna <nicola@corna.info>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

const uint8_t pir_pin = 2;
const uint8_t led_pin = 3;

const uint8_t brightness_step_ms = 6;
const uint16_t light_timeout = 10000;

void quadratic(int pin, uint8_t value) {
  analogWrite(pin, map((uint16_t)(value) * value, 0, 65025, 0, 255));
}

void setup() {
  pinMode(pir_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  analogWrite(led_pin, 0);
}

void loop() {
  static unsigned long light_on_start = 0;
  static uint8_t brightness_target = 0;
  static uint8_t brightness_cur = 0;

  if (digitalRead(pir_pin) == HIGH) {
    light_on_start = millis();
    brightness_target = 255;
  }

  if (millis() - light_on_start >= light_timeout)
    brightness_target = 0;

  if (brightness_target > brightness_cur)
    quadratic(led_pin, ++brightness_cur);
  else if (brightness_target < brightness_cur)
    quadratic(led_pin, --brightness_cur);

  delay(brightness_step_ms);  
}
