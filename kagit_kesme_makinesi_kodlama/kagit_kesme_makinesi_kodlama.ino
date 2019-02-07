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
**                                               KAGIT KESME MAKINESI PROTOTIP YAZILIMI                                             **
**                                                                                                                                  **
**   Not: bu kodda ACS712 Akim sensörü ile DC akim olcumu yaparak serial monitorde deger akisini gormekteyiz.                       **
**   eger ACS712 modulunu AC akim olcmek icin kullanicaksaniz https://github.com/tahayrdkl/Arduino vermis oldugum linkten           **
**   AC akim olcmek icin kullanilacak olan kodu temin edebilirsiniz.                                                                **
**                                                                                                                                  **
**************************************************************************************************************************************
*/
int role1 = 5;
int role2 = 6;
int startbuton = 4;

void setup()
{

  Serial.begin(9600);
  pinMode(role1 ,OUTPUT); 
  pinMode(role2 ,OUTPUT);
  // motor yonunu degistirmek icin motor kutuplarini degistirecek standart 5v 2way role kullaniyoruz.
  pinMode(startbuton ,INPUT);
  digitalWrite(role1,HIGH); 
  digitalWrite(role2,HIGH);
  /* 
  guc verilmesi gerekiyor cunku benim kullandığım roleler ters calısıyor
  "digitalWrite(role1,HIGH); , digitalWrite(role2,HIGH);" 
  bu kismi kendi rolelerinizin calısma mantıgına bakarak düzeltebilirsiniz.
  kod devamindada; (role1 ve role2) icin HIGH komutunu LOW yapmayi veya LOW komutunu HIGH yapmayi unutmayin.
  
  */
}


void loop()
 {
  if(digitalRead(startbuton) == HIGH)
  /* ON/OFF anahtar kullandim. anahtar acik oldugunda dongu donecek. 
   ayrica acil durdurma butonu, ON/OFF butonunun herhangi bir girisine baglanilacak ve acil durumda,
   butun gucu kesecek(butun gucu kesmemin sebebi herhangi bir yazilim bug inda butun sistemi durdurmak.
  */
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

  if(ortalama >= 0,1) // eger motorlarda zorlanma olursa. 
  /*
    Not: "0,1" olarak verilen deger tamamen rastgele secilmistir. 
   "0,1" degerini serial monitore bakarak projenizin normal durumdayken
   cektigi akima gore hesapliyarak degistirebilirsiniz.
   */
  {
   digitalWrite(role1,LOW);  
   digitalWrite(role2,LOW);
   //motor guc kablolari rolelerin tetiksiz halindeki kisadevre yapan cikislarina baglanilacaktir
   delay(3000); // 3 saniye boyunca motorlar ters donecekler
   digitalWrite(role1,HIGH);// 3 saniye sonunda motorlar normal donuslerine devam edecekler
   digitalWrite(role2,HIGH);
   
   }
   else // eger motorlarda zorlanma olmazsa
   {
    digitalWrite(role1,HIGH);// normal donus yapacaklar
    digitalWrite(role2,HIGH);
   }
   
   
}
 }
