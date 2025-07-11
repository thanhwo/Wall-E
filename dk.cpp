#define BLYNK_TEMPLATE_ID "TMPL6BVtXInjE"
#define BLYNK_TEMPLATE_NAME "Robot"
#define BLYNK_AUTH_TOKEN "aB61_pNl0TEvaXPd7BoMGyj0SiauWbSl"

#include <Arduino.h>
#include <Wifi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Kul";
char pass[] = "244466666";

#define INA 26
#define INB 27
#define ENA 14

#define INC 32
#define IND 33
#define ENB 25


const int pwmChannelA = 0;
const int pwmChannelB = 1;

void setup(){
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    pinMode(INA, OUTPUT);
    pinMode(INB, OUTPUT);
    pinMode(INC, OUTPUT);
    pinMode(IND, OUTPUT);

    ledcSetup(pwmChannelA, 1000, 8);
    ledcSetup(pwmChannelB, 1000, 8);
    ledcAttachPin(ENA, pwmChannelA);
    ledcAttachPin(ENB, pwmChannelB);

}

int joystickX = 0;
int joystickY = 0;

BLYNK_WRITE(V0){
    joystickX = param.asInt();
}

BLYNK_WRITE(V1){
    joystickY = param.asInt();
}

void loop(){
    Blynk.run();

    int speed;

    if (joystickY > 50){
        speed = map(abs(joystickY), 0, 100, 0, 255);
        digitalWrite(INA, HIGH);
        digitalWrite(INB, LOW);
        digitalWrite(INC, HIGH);
        digitalWrite(IND, LOW);
    } else if (joystickY < -50){
        speed = map(abs(joystickY), 0, 100, 0, 255);
        digitalWrite(INA, LOW);
        digitalWrite(INB, HIGH);
        digitalWrite(INC, LOW);
        digitalWrite(IND, HIGH);
    } else if (joystickX > 50){
        speed = map(abs(joystickX), 0, 100, 0, 255);
        digitalWrite(INA, LOW);
        digitalWrite(INB, HIGH);
        digitalWrite(INC, HIGH);
        digitalWrite(IND, LOW);
    } else if (joystickX < -50){
        speed = map(abs(joystickX), 0, 100, 0, 255);
        digitalWrite(INA, HIGH);
        digitalWrite(INB, LOW);
        digitalWrite(INC, LOW);
        digitalWrite(IND, HIGH);
    } else {
        digitalWrite(INA, LOW);
        digitalWrite(INB, LOW);
        digitalWrite(INC, LOW);
        digitalWrite(IND, LOW);
        speed = 0;
    }
    ledcWrite(pwmChannelA, speed);
    ledcWrite(pwmChannelB, speed);
}
