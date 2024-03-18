#include <E220.h>
#include<SoftwareSerial.h>
#define M0 4
#define M1 5
#define RX_PIN D2
#define TX_PIN D3

int count=0;//for test message
uint32_t pre_send_time=0;

byte tx_payload[199]={0};
byte rx_payload[199]={0};

SoftwareSerial Serial_E220(RX_PIN, TX_PIN); // RX, TX
E220 e220(Serial_E220,0xFF,0xFF,0x0A);//TARGETADRESS=0xFFFF,CHANNEL=0x00

void setup(){
    Serial.begin(9600);
    Serial_E220.begin(9600);
    pinMode(M0, OUTPUT);
    pinMode(M1, OUTPUT);
    digitalWrite(M0, LOW);
    digitalWrite(M1, LOW);
}

void loop() {
    if (count > 10) {
        count = 0;
    }
    count++;
    int Rxlength=0;
    e220.GenerateTestMsg_2(tx_payload, count,199);
    if(millis()-pre_send_time>=1500){
    e220.TransmissionData(tx_payload);
    pre_send_time=millis();
    }
    Rxlength=e220.ReceiveData(rx_payload);
    Serial.write(rx_payload,Rxlength);
    Serial.println();
    delay(10);
    e220.ResetBuff(rx_payload);
    e220.ResetBuff(tx_payload);
}
