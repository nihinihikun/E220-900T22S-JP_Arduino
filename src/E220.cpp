#include <Arduino.h>
#include "E220.h"
E220::E220(uint8_t _target_adress1, uint8_t _target_adress2, uint8_t _channel) {
    uint8_t target_address_1;
    uint8_t  target_address_2;
    uint8_t  channel;
}

void E220::ResetBuff(byte* _payload){
    for (int i=0; i<199;i++){
        _payload[i]=0x00;
    }
}

void E220::GenerateTestMsg(byte* _payload, int count) {
    for (int i = 0; i < 199; i++) {
        _payload[i] = 0x43 + count;
    }
}
void E220::GenerateTestMsg_2(byte* _payload, int count,int _length) {
    for (int i = 0; i < _length; i++) {
        if(i<(int)(_length/2)){
            _payload[i] = 0x44 + count;
        }else{
            _payload[i] = 0x43;
        }
    }
}

void E220::TransmissionData(byte* _tx_payload) {
    byte full_transmission_buffer[200] = {0};
    full_transmission_buffer[0] = STARTLETTER;
    for (int i = 0; i < 199; i++) {
        full_transmission_buffer[i + 1] = _tx_payload[i];
    }
    Serial1.write(full_transmission_buffer, 200); 
}

int E220::ReceiveData(byte* _rx_payload){
    bool isReceived=false;
    int receive_msg_length=0;
    if(Serial1.available()>0){
        byte trash[400]={0};
        int nullcount=0;
        Serial1.readBytesUntil(STARTLETTER,trash,400);
        Serial1.readBytes(_rx_payload,199);
        receive_msg_length=199;
    }else{
        receive_msg_length=0;
    }
    return receive_msg_length;
}

//When rssi available
int E220::ReceiveData(byte* _rx_payload,int* rssi){
    bool isReceived=false;
    int receive_msg_length=0;
    if(Serial1.available()>0){
        byte trash[400]={0};
        int nullcount=0;
        Serial1.readBytesUntil(STARTLETTER,trash,400);
        Serial1.readBytes(_rx_payload,199);
        delay(1);//wait for rssi culcuration at E220
        *rssi=-(256-Serial1.read());
        // dBm=256-rssi;
        receive_msg_length=199;
    }else{
        receive_msg_length=0;
    }
    return receive_msg_length;
}
