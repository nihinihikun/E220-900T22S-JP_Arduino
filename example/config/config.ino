#include <string.h>
#include <config_E220.h>
#define M0 0
#define M1 1

const int module_addr=0x01;
byte responcedata[11]={0};

byte set_data_buff[11]={0x00};

config_E220 e220conf(M0,M1);

void setup(){
    Serial.begin(9600);
    Serial1.begin(9600);
    delay(1000);
    e220conf.ReadResister(0x00,0x0B,responcedata);
}

void loop(){
    String serial_input;
    if(Serial.available() > 0){   
        serial_input = Serial.readStringUntil('\n');
        serial_input.trim(); 
    }
    
    if(serial_input.length() > 0){
        Serial.print("->");
        Serial.println(serial_input);
    }
    //show command
    if(serial_input.equals("show")>0){
        e220conf.Show();
    }
    //address command
    if(serial_input.startsWith("address ")){
        int spaceIndex = serial_input.indexOf(' ');
        String addressStr = serial_input.substring(spaceIndex + 1);
        int address = addressStr.toInt();
        e220conf.SetAddress(address, set_data_buff);
        byte w_data_buff[2];
        w_data_buff[0]=set_data_buff[0];
        w_data_buff[1]=set_data_buff[1];
        e220conf.WriteResister(0x00, 0x02,w_data_buff);
    }
    //bandrate command
    if(serial_input.startsWith("baudrate ")){
        int spaceIndex = serial_input.indexOf(' ');
        String baudrateStr = serial_input.substring(spaceIndex + 1);
        int baudrate = baudrateStr.toInt();
        e220conf.SetUartBaudrate(baudrate, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[2];
        e220conf.WriteResister(0x02, 0x01,w_data_buff);
    }
    //sf command
    if(serial_input.startsWith("sf ")){
        int spaceIndex = serial_input.indexOf(' ');
        String sfStr = serial_input.substring(spaceIndex + 1);
        int sf = sfStr.toInt();
        e220conf.SetSF(sf, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[2];
        e220conf.WriteResister(0x02, 0x01,w_data_buff);
    }
    //bw command
    if(serial_input.startsWith("bw ")){
        int spaceIndex = serial_input.indexOf(' ');
        String bwStr = serial_input.substring(spaceIndex + 1);
        int bw = bwStr.toInt();
        e220conf.SetBW(bw, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[2];
        e220conf.WriteResister(0x02, 0x01,w_data_buff);
    }
    //subpacketlength command
    if(serial_input.startsWith("subpacket ")){
        int spaceIndex = serial_input.indexOf(' ');
        String subpacketlengthStr = serial_input.substring(spaceIndex + 1);
        int subpacketlength = subpacketlengthStr.toInt();
        e220conf.SetSubpacketLength(subpacketlength, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[3];
        e220conf.WriteResister(0x03, 0x01,w_data_buff);
    }
    //power command
    if(serial_input.startsWith("power ")){
        int spaceIndex = serial_input.indexOf(' ');
        String powerStr = serial_input.substring(spaceIndex + 1);
        int power = powerStr.toInt();
        e220conf.SetTxPower(power, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[3];
        e220conf.WriteResister(0x03, 0x01,w_data_buff);
    }
    //channel command
    if(serial_input.startsWith("channel ")){
        int spaceIndex = serial_input.indexOf(' ');
        String channelStr = serial_input.substring(spaceIndex + 1);
        int channel = channelStr.toInt();
        e220conf.SetChannel(channel, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[4];
        e220conf.WriteResister(0x04, 0x01,w_data_buff);
    }
    //worcycle command
    if(serial_input.startsWith("worcycle ")){
        int spaceIndex = serial_input.indexOf(' ');
        String worcycleStr = serial_input.substring(spaceIndex + 1);
        int worcycle = worcycleStr.toInt();
        e220conf.SetWorCycle(worcycle, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[5];
        e220conf.WriteResister(0x05, 0x01,w_data_buff);
    }
    //rssi_noise command
    if(serial_input.startsWith("rssi_noise ")){
        int spaceIndex = serial_input.indexOf(' ');
        String rssi_noiseStr = serial_input.substring(spaceIndex + 1);
        int rssi_noise = rssi_noiseStr.toInt();
        e220conf.SetRssiNoiseAvailable(rssi_noise, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[3];
        e220conf.WriteResister(0x03, 0x01,w_data_buff);
    }
    //rssi_byte command
    if(serial_input.startsWith("rssi_byte ")){
        int spaceIndex = serial_input.indexOf(' ');
        String rssi_byteStr = serial_input.substring(spaceIndex + 1);
        int rssi_byte = rssi_byteStr.toInt();
        e220conf.SetRssiByteAvailable(rssi_byte, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[5];
        e220conf.WriteResister(0x05, 0x01,w_data_buff);
    }
    //tx_method command
    if(serial_input.startsWith("tx_method ")){
        int spaceIndex = serial_input.indexOf(' ');
        String tx_methodStr = serial_input.substring(spaceIndex + 1);
        int tx_method = tx_methodStr.toInt();
        e220conf.SetTxMethod(tx_method, set_data_buff);
        byte w_data_buff[1];
        w_data_buff[0]=set_data_buff[5];
        e220conf.WriteResister(0x05, 0x01,w_data_buff);
    }
    //default command
    if(serial_input.equals("default")>0){
        e220conf.SetDefault();
    }
    
    delay(1000);
}
