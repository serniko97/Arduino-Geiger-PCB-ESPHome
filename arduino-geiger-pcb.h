#include "esphome.h"
#define MAX_BUFFER_LENGHT 16

using namespace esphome::uart;

class ArduinoGeigerPCB : public Component, public UARTDevice, public Sensor {
    public:
    ArduinoGeigerPCB(UARTComponent *parent) : UARTDevice(parent) {}
    
    char buffer[MAX_BUFFER_LENGHT], c;
    int i, j;
    bool waitNewLine;
    
    void setup() override {
        buffer['\0','\0','\0','\0','\0','\0','\0','\0',
               '\0','\0','\0','\0','\0','\0','\0','\0'];
        i = 0;
        j = 0;
        c = '\0';
        waitNewLine = false;
    }
    
    void loop() override {
        while(available()) {
            c = read(); // reading one character at the time from serial interface
            
            if((c >= '0') && (c <= '9') && (i < MAX_BUFFER_LENGHT) && !waitNewLine)
            {
                buffer[i] = c;
                i++;
            } else if((i > 0) && ((c == '\n') || (c == '\r')) && !waitNewLine) {
                publish_state(atoi(buffer)); // updating the sensor value
                
                for(j = 0; (j < i) && (j < MAX_BUFFER_LENGHT); j++) {
                    buffer[j] = '\0';
                }
                i = 0;
            } else {
                if((c == '\n') || (c == '\r'))
                    waitNewLine = false;
                else
                    waitNewLine = true; // wait a new line if the serial comunication gets currupted
                
                for(j = 0; (j < i) && (j < MAX_BUFFER_LENGHT); j++) {
                    buffer[j] = '\0';
                }
                i = 0;
            }
        }
    }
};
