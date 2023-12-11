#include <ArduinoBLE.h>

#define BLE_UUID_DEMO_SERVICE              "1101"
#define BLE_UUID_COUNTER_CHAR              "2101"

int counter;

void setup() {
  Serial.begin(115200);
  BLE.begin(); 
}

void loop()
{
  BLEDevice peripheral;
  do
  {
    Serial.println("scanning for service");
    // start scanning for peripherals
    BLE.scanForUuid(BLE_UUID_DEMO_SERVICE); 
    peripheral = BLE.available();
    delay(3);
  } while (!peripheral);

  if (peripheral)
  {
    Serial.print("Found  ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();
    // stop scanning
    BLE.stopScan();
  }
  peripheral.connect();
  peripheral.discoverAttributes();

  BLECharacteristic counterCharacteristic = peripheral.characteristic(BLE_UUID_COUNTER_CHAR);

  if (!counterCharacteristic) {
    //Serial.println("no gesture characteristic found!");
    peripheral.disconnect();
    return;
  } else if (!counterCharacteristic.canSubscribe()) {
    //Serial.println("gesture characteristic is not subscribable!");
    peripheral.disconnect();
    return;
  } else if (!counterCharacteristic.subscribe()) {
    //Serial.println("subscription failed!");
    peripheral.disconnect();
    return;
  } else {
    Serial.println("Subscribed to counter");
  }
  while (peripheral.connected()) {
    if (counterCharacteristic.valueUpdated()) {
      counterCharacteristic.readValue(&counter, sizeof counter);
      Serial.println(counter);
    }
  }
}