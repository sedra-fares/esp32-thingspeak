# ESP32 → ThingSpeak: Live Temperature & Humidity

**Name:** Sidra Faris
**University ID:** 12325061

## Project Description

An ESP32 reads temperature and humidity from a DHT22 sensor and sends the
readings to ThingSpeak over Wi-Fi every 20 seconds using an HTTP GET request.
ThingSpeak's built-in charts display both values live on a public channel.
The project runs in the Wokwi simulator (no physical hardware required), and
every serial log line includes my University ID.

## Links

- **ThingSpeak public channel:** https://thingspeak.mathworks.com/channels/3551501
- **Wokwi project:** https://wokwi.com/projects/478948894410472449

Channel name: `Sidra_Faris_12325061`

## ThingSpeak Channel

| Field   | Meaning          |
|---------|------------------|
| Field 1 | Temperature (°C) |
| Field 2 | Humidity (%)     |

The channel's sharing is set to **public**.

## Wiring (Wokwi)

| DHT22 pin   | ESP32 pin |
|-------------|-----------|
| VCC (+)     | 3V3       |
| SDA (DATA)  | GPIO 15   |
| GND (-)     | GND       |


## How It Works

1. Connects to the `Wokwi-GUEST` Wi-Fi network.
2. Reads temperature and humidity from the DHT22 on GPIO 15.
3. Sends them to ThingSpeak:
   `http://api.thingspeak.com/update?api_key=<KEY>&field1=<temp>&field2=<hum>`
4. Prints a log line containing the University ID, readings, HTTP status and entry number.

Example serial output:

```
[ID: 12325061] Temp: 24.0 C | Hum: 40.0 % | HTTP: 200 | Entry: 1
```
