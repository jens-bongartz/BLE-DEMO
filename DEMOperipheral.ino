#include <ArduinoBLE.h>

#define BLE_UUID_DEMO_SERVICE              "1101"
#define BLE_UUID_COUNTER_CHAR              "2101"

int counter = 0;

#define BLE_DEVICE_NAME                           "DEMOperi"
#define BLE_LOCAL_NAME                            "demoperi"

BLEService DEMOService(BLE_UUID_DEMO_SERVICE);
// Characteristic --> UUID, BLERead / BLENotify, Datenpaket
BLECharacteristic counterCharacteristic(BLE_UUID_COUNTER_CHAR, BLERead | BLENotify, sizeof counter);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  //
  BLE.begin();
  BLE.setDeviceName(BLE_DEVICE_NAME);
  BLE.setLocalName(BLE_LOCAL_NAME);
  BLE.setAdvertisedService(DEMOService);
  DEMOService.addCharacteristic(counterCharacteristic);
  BLE.addService(DEMOService);
  counterCharacteristic.writeValue(&counter, sizeof counter);
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  BLE.advertise();
}

void loop() {  
  BLE.poll(); 
  counter = counter + 1;
  counterCharacteristic.writeValue(&counter, sizeof counter);
  delay(5);
}

void blePeripheralConnectHandler(BLEDevice central) {
  digitalWrite(LED_BUILTIN, HIGH);
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  digitalWrite(LED_BUILTIN, LOW);
}