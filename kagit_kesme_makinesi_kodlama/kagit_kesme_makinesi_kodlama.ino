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

float motorun_calisma_amperi = 0 ; 
float zorlanmadaki_akim_farki =  0.1  ; // zorlanma aninda motorun geri donus yapabilmesi icin olmasi gereken amper farki
/*
    Not: "0,1" olarak verilen deger tamamen rastgele secilmistir. 
   "0,1" degerini serial monitore bakarak projenizin normal durumdayken
   cektigi akima gore hesapliyarak degistirebilirsiniz.
*/

void setup()
{

  Serial.begin(9600);
  pinMode(role1 ,OUTPUT); 
  pinMode(role2 ,OUTPUT);
  // motor yonunu degistirmek icin motor kutuplarini degistirecek standart 5v 2way role kullaniyoruz.
  
  digitalWrite(role1,HIGH); 
  digitalWrite(role2,HIGH);
  // roleleri tetetikte birakmamak icin sinyal verdim
  
  /* 
  guc verilmesi gerekiyor cunku benim kullandığım roleler ters calısıyor
  "digitalWrite(role1,HIGH); , digitalWrite(role2,HIGH);" 
  bu kismi kendi rolelerinizin calısma mantıgına bakarak düzeltebilirsiniz.
  kod devamindada; (role1 ve role2) icin HIGH komutunu LOW yapmayi veya LOW komutunu HIGH yapmayi unutmayin.
  
  */
  
  for (int i = 0; i < 1000 ; i++)
  {
    
    motorun_calisma_amperi = motorun_calisma_amperi + (.044 * analogRead(A0) - 3.78) / 1000;
    // "(.044 * analogRead(A0)" yazdiğim bu formul ACS712 30A Modeli icin gecerlidir.
    //  eger modulunuz ACS712 5A modeli ise "(.0264 * analogRead(A0) - 13.51)" bu formulu,
    //  ACS712 20A modeli ise "(.19 * analogRead(A0) -25)" bu formulu kullaniniz.
/*
motorun_calisma_amperi ===== motorun referans alacagi baslangic akimi.
 */
    delay(1);

  }

}


void loop()
 {
  

  float motor_calisirken = 0;
  for (int i = 0; i < 1000 ; i++)
  {
    
    motor_calisirken = motor_calisirken + (.044 * analogRead(A0) - 3.78) / 1000;
    // "(.044 * analogRead(A0)" yazdiğim bu formul ACS712 30A Modeli icin gecerlidir.
    //  eger modulunuz ACS712 5A modeli ise "(.0264 * analogRead(A0) - 13.51)" bu formulu,
    //  ACS712 20A modeli ise "(.19 * analogRead(A0) -25)" bu formulu kullaniniz.

    delay(1);

  }
/*
 motorun surekli olarak olcum yapmasini saglayan kisim
*/
  Serial.println("motorun_calisma_amperi:");
  Serial.println(motorun_calisma_amperi);
  Serial.println("*********************************************************************");
  Serial.println("su_anki_cektigi_akim:");
  Serial.println(motor_calisirken);
  Serial.println("*********************************************************************");
 
  
  if(motor_calisirken  >=  motorun_calisma_amperi  +  zorlanmadaki_akim_farki) // eger motorlarda zorlanma olursa. 
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
