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
    byte payload[55]="AAAAA...AA";//(up to 199 letters)
    ```
    - define as byte
    - length must be up to 199bytes 
1. transmission
    ```
    e220.TransmissionDataVariebleLength(payload,55);
    ```


##### Recieve data
1. define datalist for recieve
    ```
    byte receive_data[55];
    ```
    - length must be up to 199bytes
1. call function
    ```
    int receive_msg_length;
    receive_msg_length=e220.ReceiveDataVariebleLength(receive_data,55);
    ```

    - this function return receive message length as int.

    If you set rssibyte available, use this function below.
    ```
    int receive_msg_length;
    int rssi;
    receive_msg_length=e220.ReceiveDataVariebleLength(receive_data,55,&rssi);
    ```
