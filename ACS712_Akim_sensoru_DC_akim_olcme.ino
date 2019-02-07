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
**   Not: bu kodda ACS712 Akim sensörü ile DC akim olcumu yaparak serial monitorde deger akisini gormekteyiz.                       **
**   eger ACS712 modulunu AC akim olcmek icin kullanicaksaniz https://github.com/tahayrdkl/Arduino vermis oldugum linkten           **
**   AC akim olcmek icin kullanilacak olan kodu temin edebilirsiniz.                                                                **
**                                                                                                                                  **
**************************************************************************************************************************************
*/

void setup()
{

  Serial.begin(9600);

}


void loop()
{
  float ortalama = 0;
  for (int i = 0; i < 1000 ; i++)
  {
    ortalama = ortalama + (.044 * analogRead(A0) - 3.78) / 1000;
    // "(.044 * analogRead(A0)" yazdiğim bu formul ACS712 30A Modeli icin gecerlidir.
    //  eger modulunuz ACS712 5A modeli ise "(.0264 * analogRead(A0) - 13.51)" bu formulu,
    //  ACS712 20A modeli ise "(.19 * analogRead(A0) -25)" bu formulu kullaniniz.

    delay(1);

  }

  Serial.println(ortalama);

}
