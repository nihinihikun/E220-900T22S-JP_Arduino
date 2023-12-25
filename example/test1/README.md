# Communication Usage

**Attension!**
- Set M0 and M1 pin to be LOW.(Nomal mode)

##### define object
```
E220 e220(0xFF,0xFF,0x00);
```
- E220(uint8_t tagetaddress1,uint8_t targetaddress2,uint8_t channel)
    - tagetaddress1,tagetaddress2
        - target-address
            - ex) target-address=0x00FF,tagetaddress1=0x00,tagetaddress2=0xFF
        - channel
            - ex) channel=0x01,channel=0x01

##### Send data
1. make payload-bytedata
    ```
    byte payload[48]="AAAAA...AA";//(48 letters)
    ```
    - define as byte
    - length must be 48bytes 
1. transmission
    ```
    e220.TransmissionData(payload);
    ```


##### Recieve data
1. define datalist for recieve
    ```
    byte receive_data[48];
    ```
    - length must be 48bytes
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


##### Change target-address/channel
- Change target-address
    ```
    ChangeTargetAddress(uint8_t _target_adress1, uint8_t _target_adress2);
    ```
    - tagetaddress1,tagetaddress2
        - target-address
            - ex) target-address=0x00FF,tagetaddress1=0x00,tagetaddress2=0xFF

- Change channel
    ```
    ChangeChannel(uint8_t _channel); 
    ```

#### Generate test messages
- generate test messages
```
void E220::GenerateTestMsg(byte* _payload, int count) {
    for (int i = 0; i < 49; i++) {
        _payload[i] = 0x43 + count;
    }
}
``` 


