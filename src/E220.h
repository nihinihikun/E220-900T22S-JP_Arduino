#ifndef E220_h 
#define E220_h 
#define STARTLETTER 0x02

class E220{
    public:
        Stream& serial_e220;
        E220(Stream& serial_e220, uint8_t _target_adress1, uint8_t _target_adress2, uint8_t _channel): serial_e220(serial_e220), target_address_1(_target_adress1), target_address_2(_target_adress2), channel(_channel) {};

        void ResetBuff(byte* _payload);
        void ResetBuff(byte* _payload,int _length);
        void GenerateTestMsg(byte* _payload, int count);
        void GenerateTestMsg_2(byte* _payload, int count,int _length);
        void TransmissionData(byte* _tx_payload);
        void TransmissionDataVariebleLength(byte* _tx_payload,int _length);
        int ReceiveData(byte* _rx_payload);
        int ReceiveData(byte* _rx_payload,int* rssi);
        int ReceiveDataVariebleLength(byte* _rx_payload,int _length);
        int ReceiveDataVariebleLength(byte* _rx_payload,int _length,int* rssi);
    private:
        uint8_t target_address_1;
        uint8_t  target_address_2;
        uint8_t  channel;
};
#endif