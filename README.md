![logo](https://github.com/fareanor3/Weather-station/blob/main/openweatherlogo.png?raw=true)

# Weather-station
___

>Project of the Innovation course of ESME SUDRIA PARIS of SUP en 2020 for the OuiAreMaker competition ( https://ouiaremakers.com/ ). 
>The mission of the project is to retrieve via an api the weather and the temperature and to display it in transparent on a plexiglass plate by LEDs. 
>We put a point of honour on the simplicity and the minimalism.
___

## Importations:

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
> Si elles sont correctement installer elles s'afficheront en couleurs.

>Dans arduino allez dans preference ( crl + , ) puis dans url de gestion de carte supplementaires collez : "http://arduino.esp8266.com/stable/package_esp8266com_index.json" et valider.

#### 💡Voici les cas que nous traitons dans ce code :

> Les "X" symbolisant l'alumage des led en fonction de chaque cas et faisant corespondre à la couleur sa temperature associée. 

|`case` | *Sun* | *cloud* | *rain* | *snow* |  *total weather id* |
| ------------- |:-------------:| :-----:|:-------------:|:-------------:|:-----:|
| `1`  |  X  |       |      |      |       800         |
| `2`  |  X  |   X   |      |      |       801         |
| `3`  |     |   X   |      |      |      802-4        |
| `4`  |     |   X   |  X   |      |  200-321 / 520-31   |
| `5`  |     |   X   |      |  X   |      600-22       |
|  `6`  |  X  |   X   |  X   |      |       500-4       |

___

## API

> Voici comment fontionnne l'ardino grace a l'API ( API est un acronyme anglais qui signifie « Application Programming Interface », que l'on traduit par interface de programmation d'application):

![API](https://user-images.githubusercontent.com/61111238/120857069-075e3680-c581-11eb-815b-11c71aa8e2ce.png)

> Gernerer votre clef API sur [OpenWeatherMap](https://openweathermap.org/api) et coller la à la place de APIKey

![APIKey](https://user-images.githubusercontent.com/61111238/120857157-1b099d00-c581-11eb-8638-647ab1ab3457.png)

> Enfin réliser ce montage : ⚠ Bien faire correpondre le pin de sortie avec le code !

![montage](https://user-images.githubusercontent.com/61111238/120857292-49877800-c581-11eb-8d5a-6f73a973c7c4.png)

#### hésitez pas ! laissez vos retours !

[<img src='https://cdn.jsdelivr.net/npm/simple-icons@3.0.1/icons/github.svg' alt='github' height='40'>](https://github.com/fareanor3)
![Profile views](https://gpvc.arturio.dev/fareanor3)
