#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

const byte radky = 4;
const byte sloupce = 4;
char keys[radky][sloupce] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'R','0','=','/'}
};
byte pinyRadku[radky] = {12, 11, 10, 9};
byte pinySloupcu[sloupce] = {8, 7, 6, 5};

Keypad klavesnice = Keypad( makeKeymap(keys), pinyRadku, pinySloupcu, radky, sloupce); 

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5,6,7,3,POSITIVE);

boolean prvni_cislo = false;
boolean akce_povolena = false;
boolean dalsi = false;
String cislo_1,cislo_2;
char operace;
float vysledek;

void setup() {
Serial.begin(9600);
lcd.begin(16,2);
lcd.clear();
lcd.print("Kalkulacka");
}

void loop() {
char klavesa = klavesnice.getKey();

if(klavesa != NO_KEY && (klavesa=='1'||klavesa=='2'||klavesa=='3'||klavesa=='4'||klavesa=='5'||klavesa=='6'||klavesa=='7'||klavesa=='8'||klavesa=='9'|klavesa=='0')){
  if(prvni_cislo == false){
    cislo_1 = cislo_1 + klavesa;
    lcd.clear();
    lcd.print(cislo_1);
  }
  else{
    cislo_2 = cislo_2 + klavesa;
    lcd.clear();
    lcd.print(cislo_2);
    akce_povolena = true;
    }
  }
else if(klavesa != NO_KEY &&(klavesa == '/' || klavesa == '*' || klavesa == '-' || klavesa == '+')){
  if(dalsi == false){
      prvni_cislo = true;
      dalsi = true;
      operace = klavesa;
      lcd.clear();
      lcd.print(operace); 
  }
}
else if(akce_povolena == true && klavesa != NO_KEY && klavesa == '='){
  if(operace == '+'){
    vysledek = (float)cislo_1.toInt() + (float)cislo_2.toInt();
    vypis_vysledku();
  }
  else if(operace == '-'){
    vysledek = (float)cislo_1.toInt() - (float)cislo_2.toInt();
    vypis_vysledku();
  }
  else if(operace == '*'){
    vysledek = (float)cislo_1.toInt() * (float)cislo_2.toInt();
    vypis_vysledku();
  }
  else if(operace == '/'){
    if (cislo_2.toInt()==0){
      lcd.clear();
      lcd.print("Error");
      lcd.setCursor(0,1);
      lcd.print("Delis 0,Press R");
    }
    else{
      vysledek = (float)cislo_1.toInt() / (float)cislo_2.toInt();
      vypis_vysledku();
    }
  }
  if(cislo_2.toInt()!=0){
    cislo_1 = vysledek;
    cislo_2 = "";
    dalsi = false;
    operace == ' ';
  }
  }
else if(klavesa != NO_KEY && klavesa == 'R'){
  lcd.clear();
  prvni_cislo = false;
  akce_povolena = false;
  dalsi = false;
  cislo_1 = "";
  cislo_2 = "";
  vysledek = 0;
  operace = ' ';
  lcd.print("Reset");
}
}


void vypis_vysledku(){
  lcd.clear();
  lcd.print(vysledek);
}
