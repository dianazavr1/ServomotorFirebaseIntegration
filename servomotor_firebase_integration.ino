// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <Servo.h>

// const char* ssid = "azima";  
// const char* password = "11111111";  
// const char* firebaseHost = "arduino-63e63-default-rtdb.asia-southeast1.firebasedatabase.app";  
// const char* firebaseAuth = "AIzaSyBbbDxqr7BVFG9zAEKse0dwhrnEXTWyXkE";  

// Servo myServo;  
// int servoPin = D5;  

// void setup() {
//     Serial.begin(115200);
//     WiFi.begin(ssid, password);
//     myServo.attach(servoPin);  

//     Serial.print("Подключение к WiFi");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }
//     Serial.println("\nWiFi подключен!");
// }

// void loop() {
//     int angle1 = getServoAngleFromFirebase("servo");   
//     int angle2 = getServoAngleFromFirebase("servo2");  

//     if (angle1 >= 0 && angle1 <= 180 && angle2 >= 0 && angle2 <= 180) {
//         myServo.write(angle1);
//         delay(1000);
//         Serial.print("Установлен угол: ");
//         Serial.println(angle1);
//         delay(5000);  

//         myServo.write(angle2);
//         delay(1000);
//         Serial.print("Установлен угол: ");
//         Serial.println(angle2);
//         delay(5000);  
//     }
// }

// int getServoAngleFromFirebase(String servoName) {
//     if (WiFi.status() != WL_CONNECTED) {
//         Serial.println("WiFi не подключен!");
//         return -1;
//     }

//     WiFiClientSecure client;  
//     client.setInsecure();  

//     HTTPClient http;
//     String url = "https://" + String(firebaseHost) + "/" + servoName + ".json?auth=" + firebaseAuth;

//     Serial.print("Отправляем GET-запрос на: ");
//     Serial.println(url);  

//     http.begin(client, url);
//     int httpResponseCode = http.GET();

//     Serial.print("Код ответа сервера: ");
//     Serial.println(httpResponseCode);

//     if (httpResponseCode == 200) {
//         String response = http.getString();
//         Serial.print("Ответ Firebase (" + servoName + "): ");
//         Serial.println(response);  

//         http.end();
//         return response.toInt();
//     } else {
//         Serial.println("Ошибка запроса, проверь URL и токен!");
//     }
//     http.end();
//     return -1;
// }



#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>

const char* ssid = "azima";  
const char* password = "11111111";  
const char* firebaseHost = "arduino-63e63-default-rtdb.asia-southeast1.firebasedatabase.app";  
const char* firebaseAuth = "AIzaSyBbbDxqr7BVFG9zAEKse0dwhrnEXTWyXkE";  

Servo myServo;  
int servoPin = D5;  

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    myServo.attach(servoPin);  

    Serial.print("Подключение к WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi подключен!");
}

void loop() {
    int angle = getServoAngleFromFirebase();  
    if (angle >= 0 && angle <= 180) {  
        myServo.write(angle);
        Serial.print("Установлен угол: ");
        Serial.println(angle);
    }
    delay(5000);  
}

int getServoAngleFromFirebase() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi не подключен!");
        return -1;
    }

    WiFiClientSecure client;  
    client.setInsecure();  // Игнорируем SSL сертификаты

    HTTPClient http;
    String url = "https://" + String(firebaseHost) + "/servo.json?auth=" + firebaseAuth;

    Serial.print("Отправляем GET-запрос на: ");
    Serial.println(url);  

    http.begin(client, url);
    int httpResponseCode = http.GET();

    Serial.print("Код ответа сервера: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode == 200) {
        String response = http.getString();
        Serial.print("Ответ Firebase: ");
        Serial.println(response);  

        http.end();
        return response.toInt();
    } else {
        Serial.println("Ошибка запроса, проверь URL и токен!");
    }
    http.end();
    return -1;
}
