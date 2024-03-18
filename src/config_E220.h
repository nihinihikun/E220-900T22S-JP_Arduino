#ifndef config_E220_H 
#define config_E220_H 

class config_E220{
    public:
        Stream& serial_e220;
        config_E220(Stream& serial_e220);
        config_E220(Stream& serial_e220,int M0pin,int M1pin);
        config_E220(Stream& serial_e220,int M0pin,int M1pin,int AUXpin);

        void GetConfigAll();

        int ReadResister(byte starting_addr,byte _length,byte* _responcedata);
        int WriteResister(byte starting_addr,byte _length,byte* _writedata);
        int SetTemporaryResister(byte starting_addr,byte _length,byte* _data);

        void SetDefault();
        void Show();

        void SetAddress(int _addr,byte* _set_data_buff);
        void SetUartBaudrate(int baudrate,byte* _set_data_buff);
        void SetSF(int sf,byte* _set_data_buff);
        void SetBW(int bw,byte* _set_data_buff);
        void SetSubpacketLength(int _sub_length,byte* _set_data_buff);
        void SetRssiNoiseAvailable(bool _rssi_available,byte* _set_data_buff);
        void SetTxPower(int _power,byte* _set_data_buff);
        void SetChannel(int _channel,byte* _set_data_buff);
        void SetRssiByteAvailable(bool _rssi_byte_available,byte* _set_data_buff);
        void SetTxMethod(bool _fixed,byte* _set_data_buff);
        void SetWorCycle(int _cycle,byte* _set_data_buff);
    private:
        const byte default_config_data[11]={0xC0,0x00,0x08,0x00,0x00,0x62,0x00,0x0F,0x03,0x00,0x00};
        byte set_data[11]={0};
        byte responcedata[11]={0};
        //selections
        uint32_t uart_baudrate[8]={1200,2400,4800,9600,19200,38400,57600,115200};
        uint32_t sf[8]={5,6,7,8,9,10,11,12};
        uint32_t bw[3]={125,250,500};
        uint32_t subpacket_length[4]={200,128,64,32};
        uint32_t tx_power[4]={NULL,13,7,0};
        uint32_t wor_cycle[8]={500,1000,1500,2000,2500,3000,3500,4000};

        
};

#endif