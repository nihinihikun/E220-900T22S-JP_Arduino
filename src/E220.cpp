#include <Arduino.h>
#include "E220.h"
E220::E220(uint8_t _target_adress1, uint8_t _target_adress2, uint8_t _channel) {
    uint8_t target_address_1;
    uint8_t  target_address_2;
    uint8_t  channel;
}

void E220::ResetBuff(byte* _payload){
    for (int i=0; i<48;i++){
        _payload[i]=0x00;
    }
}

void E220::GenerateTestMsg(byte* _payload, int count) {
    for (int i = 0; i < 49; i++) {
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
    byte full_transmission_buffer[54] = {0};
    full_transmission_buffer[0] = target_address_1;
    full_transmission_buffer[1] = target_address_2;
    full_transmission_buffer[2] = channel;
    full_transmission_buffer[3] = STARTLETTER;
    for (int i = 0; i < 49; i++) {
        full_transmission_buffer[i + 4] = _tx_payload[i];
    }
    Serial1.write(full_transmission_buffer, 53); 
}

int E220::ReceiveData(byte* _rx_payload){
    bool isReceived=false;
    int receive_msg_length=0;
    if(Serial1.available()>0){
        byte trash[100]={0};
        int nullcount=0;
        Serial1.readBytesUntil(STARTLETTER,trash,100);
        Serial1.readBytes(_rx_payload,49);
        receive_msg_length=49;
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
        byte trash[100]={0};
        int nullcount=0;
        Serial1.readBytesUntil(STARTLETTER,trash,100);
        Serial1.readBytes(_rx_payload,49);
        *rssi=-(256-Serial1.read());
        // dBm=256-rssi;
        receive_msg_length=49;
    }else{
        receive_msg_length=0;
    }
    return receive_msg_length;
}

void E220::ChangeChannel(uint8_t _channel){
    channel=_channel;
}

void E220::ChangeTargetAddress(uint8_t _target_adress1, uint8_t _target_adress2){
    target_address_1=_target_adress1;
    target_address_2=_target_adress2;
}

