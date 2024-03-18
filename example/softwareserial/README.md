# Communication Usage(SoftwareSerial)

**Attension!**
- Set M0 and M1 pin to be LOW.(Nomal mode)
- need include SoftwareSerial.h
```
#include <E220.h>
#include <SoftwareSerial.h>
```
##### define object
```
SoftwareSerial mySerial(D3, D4); // RX, TX
E220 e220(mySerial,0xFF,0xFF,0x00);
```
- E220(&Stream,uint8_t tagetaddress1,uint8_t targetaddress2,uint8_t channel)
    - tagetaddress1,tagetaddress2
        - target-address
            - ex) target-address=0x00FF,tagetaddress1=0x00,tagetaddress2=0xFF
        - channel
            - ex) channel=0x01,channel=0x01

##### Send data
1. make payload-bytedata
    ```
    byte payload[199]="AAAAA...AA";//(199 letters)
    ```
    - define as byte
    - length must be 199bytes 
1. transmission
    ```
    e220.TransmissionData(payload);
    ```


##### Recieve data
1. define datalist for recieve
    ```
    byte receive_data[199];
    ```
    - length must be 199bytes
1. call function
    ```
    int receive_msg_length;
    receive_msg_length=e220.ReceiveData(receive_data);
    ```

    - this function return receive message length as int.

    If you set rssibyte available, use this function below.
    ```
    int receive_msg_length;
    int rssi;
    receive_msg_length=e220.ReceiveData(receive_data,&rssi);
    ```

#### Generate test messages
- generate test messages
```
void E220::GenerateTestMsg(byte* _payload, int count) {
    for (int i = 0; i < 199; i++) {
        _payload[i] = 0x43 + count;
    }
}
``` 


