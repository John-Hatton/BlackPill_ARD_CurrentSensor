#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>

// Create INA219 and LCD objects
Adafruit_INA219 ina219;
LiquidCrystal_I2C lcd(0x3B, 16, 2); // Adjust address if needed

// INA219 at port 0x40

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);
    while (!Serial) { delay(1); }

    // Initialize INA219
    if (!ina219.begin()) {
        Serial.println("Failed to find INA219 chip");
        while (1);
    }
    Serial.println("INA219 initialized!");

    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Starting...");
    delay(2000); // Pause for display
    lcd.clear();
}

//void loop() {
//    // Get readings from INA219
//    float busVoltage = ina219.getBusVoltage_V();
//    float shuntVoltage = ina219.getShuntVoltage_mV();
//    float current_mA = ina219.getCurrent_mA();
//    float power_mW = ina219.getPower_mW();
//
//    // ** Log to Serial Monitor (Verbose) **
//    Serial.println("=== INA219 Readings ===");
//    Serial.print("Bus Voltage   : "); Serial.print(busVoltage, 2); Serial.println(" V");
//    Serial.print("Shunt Voltage : "); Serial.print(shuntVoltage, 3); Serial.println(" mV");
//    Serial.print("Current       : "); Serial.print(current_mA, 1); Serial.println(" mA");
//    Serial.print("Power         : "); Serial.print(power_mW, 1); Serial.println(" mW");
//    Serial.println();
//
//    // ** Display on LCD (Concise) **
//    lcd.clear();
//    lcd.setCursor(0, 0); // First row
//    lcd.print("V:"); lcd.print(busVoltage, 2); lcd.print(" I:"); lcd.print(current_mA, 1);
//
//    lcd.setCursor(0, 1); // Second row
//    lcd.print("P:"); lcd.print(power_mW, 1); lcd.print("mW");
//    // Alternatively, you can display shunt voltage here if needed.
//
//    // Delay for readability
//    delay(1000); // 1-second update rate
//}

void loop(void)
{
    float shuntVoltage_mV = 0;
    float busVoltage_V = 0;
    float current_mA = 0;
    float loadVoltage_V = 0;
    float power_mW = 0;

    // Retrieve measurements
    shuntVoltage_mV = ina219.getShuntVoltage_mV();
    busVoltage_V = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    power_mW = ina219.getPower_mW();
    loadVoltage_V = busVoltage_V + (shuntVoltage_mV / 1000.0);

    // Display on Serial Monitor
    Serial.print("Bus Voltage:   "); Serial.print(busVoltage_V, 2); Serial.println(" V");
    Serial.print("Shunt Voltage: "); Serial.print(shuntVoltage_mV, 2); Serial.println(" mV");
    Serial.print("Load Voltage:  "); Serial.print(loadVoltage_V, 2); Serial.println(" V");
    Serial.print("Current:       "); Serial.print(current_mA, 2); Serial.println(" mA");
    Serial.print("Power:         "); Serial.print(power_mW, 2); Serial.println(" mW");
    Serial.println("");

    // Update LCD (if connected)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("V: "); lcd.print(loadVoltage_V, 2);
    lcd.print(" I: "); lcd.print(current_mA, 1);
    lcd.setCursor(0, 1);
    lcd.print("P: "); lcd.print(power_mW, 1); lcd.print("mW");

    delay(2000);
}
