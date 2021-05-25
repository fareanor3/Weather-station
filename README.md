![logo](https://raw.githubusercontent.com/fareanor3/Weather-station/main/openweatherlogo.png?token=AOSHXRSVGDLCJ5XTU3JND2DAW2WC4)

# Weather-station

Project of the Innovation course of ESME SUDRIA PARIS of SUP en 2020 for the OuiAreMaker competition ( https://ouiaremakers.com/ ). The mission of the project is to retrieve via an api the weather and the temperature and to display it in transparent on a plexiglass plate by LEDs. we put a point of honour on the simplicity and the minimalism.
Documentation : https://www.youtube.com/watch?v=McwarmDpQXo

## importations:

Vous devrez importer des bibliotèques exterieurs dont:

>Arduino_JSON 

Dans arduino allez dans preference ( crl + , ) puis dans url de gestion de carte supplementaires collez : "http://arduino.esp8266.com/stable/package_esp8266com_index.json" et valider.

|`case` | *Sun* | *cloud* | *rain* | *snow* |  *total weather id* |
| ------------- |:-------------:| :-----:|:-------------:|:-------------:|:-----:|
| `1`  |  X  |       |      |      |       800         |
| `2`  |  X  |   X   |      |      |       801         |
| `3`  |     |   X   |      |      |      802-4        |
| `4`  |     |   X   |  X   |      |  200-321 520-31   |
| `5`  |     |   X   |      |  X   |      600-22       |
|  `6`  |  X  |   X   |  X   |      |       500-4       |
