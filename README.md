![logo](https://raw.githubusercontent.com/fareanor3/Weather-station/main/openweatherlogo.png?token=AOSHXRSVGDLCJ5XTU3JND2DAW2WC4)

# Weather-station

Project of the Innovation course of ESME SUDRIA PARIS of SUP en 2020 for the OuiAreMaker competition ( https://ouiaremakers.com/ ). The mission of the project is to retrieve via an api the weather and the temperature and to display it in transparent on a plexiglass plate by LEDs. we put a point of honour on the simplicity and the minimalism.

## importations:

Vous devrez importer des bibliotèques exterieurs dont:

```arduino

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>

// strip led import

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
```
> si elle sont correctment installer elles s'afficheront en couleurs.

Dans arduino allez dans preference ( crl + , ) puis dans url de gestion de carte supplementaires collez : "http://arduino.esp8266.com/stable/package_esp8266com_index.json" et valider.

|`case` | *Sun* | *cloud* | *rain* | *snow* |  *total weather id* |
| ------------- |:-------------:| :-----:|:-------------:|:-------------:|:-----:|
| `1`  |  X  |       |      |      |       800         |
| `2`  |  X  |   X   |      |      |       801         |
| `3`  |     |   X   |      |      |      802-4        |
| `4`  |     |   X   |  X   |      |  200-321 520-31   |
| `5`  |     |   X   |      |  X   |      600-22       |
|  `6`  |  X  |   X   |  X   |      |       500-4       |


___

** API

Voici comment fontionnne l'ardino grace a l'API :

![API](https://raw.githubusercontent.com/fareanor3/Weather-station/main/API.png?token=AOSHXRXU3LUCZYRCQ4C774LAW2XQU)

Gernerer votre clef API sur [OpenWeatherMap](https://openweathermap.org/api) et coller la à la place de APIKey

![APIKey](https://raw.githubusercontent.com/fareanor3/Weather-station/main/APIKey.png?token=AOSHXRXO52TQWQKM5ERKPJ3AW2XRG)

enfin réliser ce montage : ⚠ Bien faire correpondre le pin de sortie avec le code !

![montage](https://raw.githubusercontent.com/fareanor3/Weather-station/main/montage.png?token=AOSHXRXGS5VNF2MFYWUX7MLAW2XSU)

