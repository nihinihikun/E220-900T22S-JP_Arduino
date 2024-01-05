#include <Arduino.h>
#include "config_E220.h"
//costructors
config_E220::config_E220(){
}

config_E220::config_E220(int M0pin,int M1pin){
    pinMode(M0pin,OUTPUT);
    pinMode(M1pin,OUTPUT);
    digitalWrite(M0pin,HIGH);
    digitalWrite(M1pin,HIGH);
}

config_E220::config_E220(int M0pin,int M1pin,int AUXpin){
    pinMode(M0pin,OUTPUT);
    pinMode(M1pin,OUTPUT);
    pinMode(AUXpin,INPUT);
    digitalWrite(M0pin,HIGH);
    digitalWrite(M1pin,HIGH);
}

//control resisters
int config_E220::ReadResister(byte starting_addr,byte _length,byte* _responcedata){
    byte set_data[3]={0};
    byte trash[100]={0};
    set_data[0]=0xc1;
    set_data[1]=starting_addr;
    set_data[2]=_length;
    _length=Serial1.write(set_data, 3);
    delay(500);

    if(Serial1.available()){
        int starting_addr_res=0;
        int length_res=0;
        Serial1.readBytesUntil(0xc1,trash,100);
        starting_addr_res=(int)Serial1.read();
        length_res=(int)Serial1.read();
        Serial1.readBytes(_responcedata,length_res);
        // Serial.write(_responcedata,length_res);
        return length_res;
    }else{
        Serial.println("Serial1 no response");
        return 0;
    }
}

int config_E220::WriteResister(byte starting_addr,byte _length,byte* _data){
    byte set_data[100]={0};
    byte trash[100]={0};

    set_data[0]=0xc0;
    set_data[1]=starting_addr;
    set_data[2]=_length;
    for(int i=0;i<(int)_length;i++){
        set_data[i+3]=_data[i];
    }
    Serial1.write(set_data, _length+3);   
    
    delay(500);
    int responce_length=0;
    if(Serial1.available()){
        Serial1.readBytesUntil(0xC1,trash,100);
        responce_length=Serial1.read();
        Serial1.readBytes(responcedata,responce_length);
        // Serial.write(responcedata,length);
        return responce_length;
    }else{
        // Serial.println("no response");
        return 0;
    }
}

int config_E220::SetTemporaryResister(byte starting_addr,byte _length,byte* _data){
    byte set_data[100]={0};
    byte trash[100]={0};

    set_data[0]=0xC2;
    set_data[1]=starting_addr;
    set_data[2]=_length;
    for(int i=0;i<_length;i++){
        set_data[i+3]=_data[i];
    }
    Serial1.write(set_data, _length+3);   
    
    delay(500);
    int responce_length=0;
    if(Serial1.available()){
        Serial1.readBytesUntil(0xc1,trash,100);
        responce_length=Serial1.read();
        Serial1.readBytes(responcedata,responce_length);
        return responce_length;
    }else{
        // Serial.println("no response");
        return 0;
    }
}

//commands
void config_E220::SetDefault(){
    Serial1.write(default_config_data, 11);
}

void config_E220::Show(){
    byte responcedata[11]={0};
    ReadResister(0x00,11,responcedata);
    Serial.println("------configuration------");
    Serial.print("Address:");
    Serial.print(responcedata[0],HEX);
    Serial.println(responcedata[1],HEX);


    Serial.print("UARTBaudrate:");
    Serial.print(uart_baudrate[(int)((responcedata[2]&0b11100000)>>5)]);
    Serial.println("bps");

    Serial.print("SF:");
    Serial.print(sf[(int)((responcedata[2]&0b00011100)>>2)]);
    Serial.println("");

    Serial.print("BW:");
    Serial.print(bw[(int)((responcedata[2]&0b00000011))]);
    Serial.println("kHz");

    Serial.print("SubpacketLength:");
    Serial.print(subpacket_length[(int)((responcedata[3]&0b11000000)>>6)]);
    Serial.println("bytes");

    Serial.print("RSSINoise:");
    if(((responcedata[3]&0b00100000)>>5)==0x00){
        Serial.println("Not Available");
    }else{
        Serial.println("Available");
    }

    Serial.print("TxPower:");
    Serial.print(tx_power[(int)((responcedata[3]&0b00000011))]);
    Serial.println("dBm");

    Serial.print("Channel:");
    Serial.print(responcedata[4]);
    Serial.println("");

    Serial.print("RSSIByte:");
    if(((responcedata[5]&0b10000000)>>7)==0x00){
        Serial.println("Not Available");
    }else{
        Serial.println("Available");
    }

    Serial.print("TxMethod:");
    if(((responcedata[5]&0b01000000)>>6)>0){
        Serial.println("Fixed length transmission mode");
    }else{
        Serial.println("Transparent mode");
    }

    Serial.print("WORCycle:");
    Serial.print(wor_cycle[(int)((responcedata[5]&0b00000111))]);
    Serial.println("ms");

    Serial.println("-------------------------");
}

//Address=0x00,0x01
void config_E220::SetAddress(int _addr,byte* _set_data_buff){
    if(_addr<0){
        // Serial.print("error:address<0");
    }else if(_addr<256){
        _set_data_buff[0]=_addr;
    }else if(_addr<65536){
        _set_data_buff[0]=_addr/256;
        _set_data_buff[1]=_addr%256;
    }else{
        // Serial.print("error:address>65535");
    }
}

//Address=0x02
void config_E220::SetUartBaudrate(int baudrate,byte* _set_data_buff){
    switch (baudrate)
    {
    case 1200:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b00000000;
        break;
    case 2400:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b00100000;
        break;
    case 4800:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b01000000;
        break;
    case 9600:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b01100000;
        break;
    case 19200:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b10000000;
        break;
    case 38400:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b10100000;
        break;
    case 57600:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b11000000;
        break;
    case 115200:
        _set_data_buff[2]=_set_data_buff[2]&0b00011111;
        _set_data_buff[2]=_set_data_buff[2]|0b11100000;
        break;
    default:
        break;
    }
}
//0x02
void config_E220::SetSF(int sf,byte* _set_data_buff){
    switch(sf)
    {
        case 5:
            _set_data_buff[2]=_set_data_buff[2]&0b11100011;
            _set_data_buff[2]=_set_data_buff[2]|0b00000000;
            break;
        case 6:
            _set_data_buff[2]=_set_data_buff[2]&0b11100011;
            _set_data_buff[2]=_set_data_buff[2]|0b00000100;
            break;
        case 7:
            _set_data_buff[2]=_set_data_buff[2]&0b11100011;
            _set_data_buff[2]=_set_data_buff[2]|0b00001000;
            break;
        case 8:
            _set_data_buff[2]=_set_data_buff[2]&0b11100011;
            _set_data_buff[2]=_set_data_buff[2]|0b00001100;
            break;
        case 9:
            _set_data_buff[2]=_set_data_buff[2]&0b11100011;
            _set_data_buff[2]=_set_data_buff[2]|0b00010000;
            break;
        case 10:
            _set_data_buff[2]=_set_data_buff[2]&0b11100011;
            _set_data_buff[2]=_set_data_buff[2]|0b00010100;
            break;
        case 11:
            _set_data_buff[2]=_set_data_buff[2]&0b11100011;
            _set_data_buff[2]=_set_data_buff[2]|0b00011000;
            break;
        default:
            break;
    }
}
// void SetAirDataRate(){
    
// }
void config_E220::SetBW(int bw,byte* _set_data_buff){
    switch(bw)
    {
        case 125:
            _set_data_buff[2]=_set_data_buff[2]&0b11111100;
            _set_data_buff[2]=_set_data_buff[2]|0b00000000;
            break;
        case 250:
            _set_data_buff[2]=_set_data_buff[2]&0b11111100;
            _set_data_buff[2]=_set_data_buff[2]|0b00000001;
            break;
        case 500:
            _set_data_buff[2]=_set_data_buff[2]&0b11111100;
            _set_data_buff[2]=_set_data_buff[2]|0b00000010;
            break;
        default:
            break;
    }
    
}
//0x03
void config_E220::SetSubpacketLength(int _sub_length,byte* _set_data_buff){
    switch (_sub_length)
    {
    case 200:
        _set_data_buff[3]=_set_data_buff[3]&0b00111111;
        _set_data_buff[3]=_set_data_buff[3]|0b00000000;
        
    case 128:
        _set_data_buff[3]=_set_data_buff[3]&0b00111111;
        _set_data_buff[3]=_set_data_buff[3]|0b01000000;
    case 64:
        _set_data_buff[3]=_set_data_buff[3]&0b00111111;
        _set_data_buff[3]=_set_data_buff[3]|0b10000000;
    case 32:
        _set_data_buff[3]=_set_data_buff[3]&0b00111111;
        _set_data_buff[3]=_set_data_buff[3]|0b11000000;
    default:
        break;
    }
}

void config_E220::SetRssiNoiseAvailable(bool _rssi_available,byte* _set_data_buff){
    if(_rssi_available){
        _set_data_buff[3]=_set_data_buff[3]&0b11011111;
    }else{
        _set_data_buff[3]=_set_data_buff[3]&0b11011111;
        _set_data_buff[3]=_set_data_buff[3]|0b00100000; 
    }
}

void config_E220::SetTxPower(int _power,byte* _set_data_buff){
    switch(_power){
        case 13:
            _set_data_buff[3]=_set_data_buff[3]&0b11111100;
            _set_data_buff[3]=_set_data_buff[3]|0b00000001;
        case 7:
            _set_data_buff[3]=_set_data_buff[3]&0b11111100;
            _set_data_buff[3]=_set_data_buff[3]|0b00000010;
        case 0:
            _set_data_buff[3]=_set_data_buff[3]&0b11111100;
            _set_data_buff[3]=_set_data_buff[3]|0b00000011;
        default:
            break;
    }
}
//0x04
void config_E220::SetChannel(int _channel,byte* _set_data_buff){
    if(_channel<0){
        Serial.print("error:channel<0");
    }else if(_channel<31){//toDo BWを監視するpgm+条件分岐
        _set_data_buff[4]=_channel;//Todo HEXに変換
    }
}
//0x05
void config_E220::SetRssiByteAvailable(bool _rssi_byte_available,byte* _set_data_buff){
    if(!_rssi_byte_available){
        _set_data_buff[5]=_set_data_buff[5]&0b01111111;
        _set_data_buff[5]=_set_data_buff[5]|0b00000000;
    }else{
        _set_data_buff[5]=_set_data_buff[5]&0b01111111;
        _set_data_buff[5]=_set_data_buff[5]|0b10000000;
    }
}

void config_E220::SetTxMethod(bool _fixed,byte* _set_data_buff){
    if(_fixed){//Transeparent mode
        _set_data_buff[5]=_set_data_buff[5]&0b10111111;
        _set_data_buff[5]=_set_data_buff[5]|0b00000000;
    }else{//fixed mode
        _set_data_buff[5]=_set_data_buff[5]&0b10111111;
        _set_data_buff[5]=_set_data_buff[5]|0b01000000;
    }

}

void config_E220::SetWorCycle(int _cycle,byte* _set_data_buff){
    switch (_cycle)
    {
    case 500:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000000;
        break;
    case 1000:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000001;
        break;
    case 1500:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000010;
        break;
    case 2000:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000011;
        break;
    case 2500:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000100;
        break;
    case 3000:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000101;
        break;
    case 3500:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000110;
        break;
    case 4000:
        _set_data_buff[5]=_set_data_buff[5]&0b11111000;
        _set_data_buff[5]=_set_data_buff[5]|0b00000111;
        break;
    default:
        break;
    }
}

//0x06
//0x07
//0x08(read only)
