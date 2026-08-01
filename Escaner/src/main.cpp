#include <Arduino.h>
#include <NimBLEDevice.h>
#include <map>
#include <math.h>

#define TIEMPO_EXPIRACION 15000 
#define TIEMPO_ESCANEO 2        

NimBLEScan* pBLEScan;

struct DispositivoBLE {
    int rssi;
    String info;
    unsigned long ultimoVisto;
};

std::map<String, DispositivoBLE> baseDatos;

// EL AJUSTE MAESTRO: Diferentes potencias para diferentes dispositivos
float calcularDistanciaMetros(int rssi, String info) {
    float txPower = -69.0;       // Referencia estándar para Apple/Wearables
    
    // Si es una MAC Rotativa o Android, asumimos que transmite con menos fuerza
    if (info == "MAC_Rotativa" || info == "Android" || info == "Genérico/Oculto") {
        txPower = -80.0; // Lo ajustamos para que si llega a -80dBm lo ponga a ~1 metro
    }

    float factorAmbiental = 2.5; // Ajuste para entornos interiores con gente
    if (rssi == 0) return -1.0;
    return pow(10.0, (txPower - rssi) / (10.0 * factorAmbiental));
}

String obtenerMarcaPorCID(uint16_t cid) {
    switch (cid) {
        case 0x004C: return "Apple";
        case 0x0075: return "Samsung";
        case 0x0006: return "Microsoft";
        case 0x00E0: return "Google";
        case 0x0118: return "Xiaomi"; 
        case 0x038F: return "Xiaomi"; 
        default: return "";
    }
}

class CallbacksDispositivos: public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
        String mac = String(advertisedDevice->getAddress().toString().c_str());
        mac.toUpperCase();
        int rssi = advertisedDevice->getRSSI();
        String perfil = "Genérico/Oculto";
        bool id = false;

        if (advertisedDevice->haveManufacturerData()) {
            std::string datos = advertisedDevice->getManufacturerData();
            if (datos.length() >= 2) {
                uint16_t cid = (datos[1] << 8) | (datos[0] & 0xFF);
                String marca = obtenerMarcaPorCID(cid);
                if (marca != "") { perfil = marca; id = true; }
            }
        } 
        if (!id && advertisedDevice->haveServiceUUID()) {
            NimBLEUUID uuid = advertisedDevice->getServiceUUID();
            String uuidStr = String(uuid.toString().c_str()).substring(4,8);
            uuidStr.toUpperCase();
            if (uuidStr == "FE2C" || uuidStr == "FEF3" || uuidStr == "FE9F") {
                perfil = "Android"; id = true;
            } else if (uuidStr == "FEED") {
                perfil = "Wearable"; id = true;
            }
        }
        if (!id && advertisedDevice->getAddress().getType() == 1) { 
            perfil = "MAC_Rotativa"; 
        }

        DispositivoBLE temp = {rssi, perfil, millis()};
        baseDatos[mac] = temp;
    }
};

void setup() {
    Serial.begin(115200);
    delay(2000); 
    NimBLEDevice::init("");
    pBLEScan = NimBLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new CallbacksDispositivos(), true);
    pBLEScan->setActiveScan(false); 
    pBLEScan->setInterval(100);     
    pBLEScan->setWindow(99);        
}

void loop() {
    pBLEScan->start(TIEMPO_ESCANEO, false);
    pBLEScan->clearResults(); 

    unsigned long ahora = millis();

    Serial.println("---START_JSON---");
    for (auto it = baseDatos.begin(); it != baseDatos.end(); ) {
        if (ahora - it->second.ultimoVisto > TIEMPO_EXPIRACION) {
            it = baseDatos.erase(it);
        } else {
            // Pasamos el tipo de dispositivo para calcular la distancia correcta
            float dist = calcularDistanciaMetros(it->second.rssi, it->second.info);
            
            Serial.printf("{\"mac\":\"%s\",\"rssi\":%d,\"dist\":%.1f,\"info\":\"%s\"}\n", 
                          it->first.c_str(), it->second.rssi, dist, it->second.info.c_str());
            ++it;
        }
    }
    Serial.println("---END_JSON---");
    delay(10);
}