#include <E220.h>
#define M0 0
#define M1 1

int count=0;//for test message

byte tx_payload[199]={0};
byte rx_payload[199]={0};

E220 e220(0xFF,0xFF,0x00);//TARGETADRESS=0xFFFF,CHANNEL=0x00

void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
    pinMode(M0, OUTPUT);
    pinMode(M1, OUTPUT);
    digitalWrite(M0, LOW);
    digitalWrite(M1, LOW);
}

void loop() {
    static int rssi=0;
    if (count > 10) {
        count = 0;
    }
    count++;
    int Rxlength=0;
    e220.GenerateTestMsg_2(tx_payload, count,199);
    e220.TransmissionData(tx_payload);
    Rxlength=e220.ReceiveData(rx_payload,&rssi);
    Serial.write(rx_payload,Rxlength);
    Serial.println();
    Serial.print("RSSI[dBm]:");
    Serial.println(rssi);
    delay(10);
    e220.ResetBuff(rx_payload);
    e220.ResetBuff(tx_payload);
    delay(2000);
}
