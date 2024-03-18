#include <Arduino.h>
#include "E220.h"

void E220::ResetBuff(byte* _payload){
    for (int i=0; i<199;i++){
        _payload[i]=0x00;
    }
}

void E220::ResetBuff(byte* _payload,int _length){
    for (int i=0; i<_length;i++){
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
    serial_e220.write(full_transmission_buffer, 200); 
}

void E220::TransmissionDataVariebleLength(byte* _tx_payload,int _length) {
    byte full_transmission_buffer[_length+1] = {0};
    full_transmission_buffer[0] = STARTLETTER;
    for (int i = 0; i < _length; i++) {
        full_transmission_buffer[i + 1] = _tx_payload[i];
    }
    serial_e220.write(full_transmission_buffer, _length+1); 
}

int E220::ReceiveData(byte* _rx_payload){
    bool isReceived=false;
    int receive_msg_length=0;
    if(serial_e220.available()>0){
        byte trash[400]={0};
        int nullcount=0;
        serial_e220.readBytesUntil(STARTLETTER,trash,400);
        serial_e220.readBytes(_rx_payload,199);
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
    if(serial_e220.available()>0){
        byte trash[400]={0};
        int nullcount=0;
        serial_e220.readBytesUntil(STARTLETTER,trash,400);
        serial_e220.readBytes(_rx_payload,199);
        delay(1);//wait for rssi culcuration at E220
        *rssi=-(256-serial_e220.read());
        // dBm=256-rssi;
        receive_msg_length=199;
    }else{
        receive_msg_length=0;
    }
    return receive_msg_length;
}

//When Variebale length data sended
int E220::ReceiveDataVariebleLength(byte* _rx_payload,int _length){
    bool isReceived=false;
    int receive_msg_length=0;
    if(serial_e220.available()>0){
        byte trash[400]={0};
        int nullcount=0;
        serial_e220.readBytesUntil(STARTLETTER,trash,400);
        serial_e220.readBytes(_rx_payload,_length+1);
        receive_msg_length=_length;
    }else{
        receive_msg_length=0;
    }
    return receive_msg_length;

}

int E220::ReceiveDataVariebleLength(byte* _rx_payload,int _length,int* rssi){
    bool isReceived=false;
    int receive_msg_length=0;
    if(serial_e220.available()>0){
        byte trash[400]={0};
        int nullcount=0;
        serial_e220.readBytesUntil(STARTLETTER,trash,400);
        serial_e220.readBytes(_rx_payload,_length+1);
        delay(1);//wait for rssi culcuration at E220
        *rssi=-(256-serial_e220.read());
        // dBm=256-rssi;
        receive_msg_length=_length;
    }else{
        receive_msg_length=0;
    }
    return receive_msg_length;
}
