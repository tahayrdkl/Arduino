/*
**************************************************************************************************************************************
**                                                                                                                                  **
**                                                                                                                                  **
**      ____________   ________  ___    ___  ________             ___    ___  ________  _______     ___  __    ___                  **
**     |\_____   ____\|\   __  \|\  \  |\  \|\   __  \           |\  \  /  /||\   __  \|\   ___  \ |\  \|\  \ |\  \                 **
**     \|____|\  \___|\ \  \|\  \ \  \_\_\  \ \  \|\  \          \ \  \/  / |\ \  \|\  \ \  \__|\  \ \  \/  /|  \  \                **
**           \ \  \    \ \   __  \ \   ___   \ \   __  \          \ \    / /  \ \   _  _\ \  \  \\  | \   ___  \ \  \               **
**            \ \  \    \ \  \ \  \ \  \__|\  \ \  \ \  \   __     \ /  / /    \ \  \\  \\ \  \__/  /\ \  \\ \  \ \  \____          **
**             \ \__\    \ \__\ \__\ \__\ \ \__\ \__\ \__\ |\__\ __ /  / /      \ \__\\ _\\ \______/ |\ \__\\ \__\ \_______\        **
**              \|__|     \|__|\|__|\|__|  \|__|\|__|\|__| \|__||\____/ /        \|__|\|__|\|______|/  \|__| \|__|\|_______|        **
**                                                               \|___|/                                                            **
**                                                                                                                                  **
**                                                                                                                                  **
**                                                            TAHA YURDAKUL                                                         **
**                                                       tahayurdakul@icloud.com                                                    **
**                                                                                                                                  **
**                                                                                                                                  **
**                                                                                                                                  **
**   Not: bu kodda ACS712 Akim sensörü ile AC akim olcumu yaparak serial monitorde deger akisini gormekteyiz.                       **
**   eger ACS712 modulunu DC akim olcmek icin kullanicaksaniz https://github.com/tahayrdkl/Arduino vermis oldugum linkten           **
**   DC akim olcmek icin kullanilacak olan kodu temin edebilirsiniz.                                                                **
**                                                                                                                                  **
**************************************************************************************************************************************
*/

float genlik_akim;      
float efektif_deger;       

void setup()
{
    Serial.begin(9600);
  
}
void loop()
{
    int sensor_max;
    sensor_max = getMaxValue();
    Serial.print("sensor_max = ");
    Serial.println(sensor_max); 
     genlik_akim=(float)(sensor_max-512)/1024*5/185*1000000; 
    efektif_deger=genlik_akim/1.414;
    
    Serial.println("genlik akim");
    Serial.println(genlik_akim,1);
    Serial.println("efektif deger");
    Serial.println( efektif_deger,1);
}

int getMaxValue()
{
    int sensorValue;   
    int sensorMax = 0;
    uint32_t start_time = millis();
    while((millis()-start_time) < 1000) 
    {
        sensorValue = analogRead(A0);
        if (sensorValue > sensorMax)
        {
            
            sensorMax = sensorValue;
        }
    }
    return sensorMax;
}
