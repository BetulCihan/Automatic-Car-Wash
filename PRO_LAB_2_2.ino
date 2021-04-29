int buton1 = 2;
int buton2 = 3;
int buton3 = 4;
int buton4 = 5;
int buton5 = 6;
int buton6 = 7;
int kirmiziLed = 8;
int yesilLed = 9;
int sayi,toplam=0,cikis=1,p,girilenPara=0,harcananPara=0;
int loopIsaret = 0;
int randomSayi;
int i1,i2,i3,i4;

struct Banknot{
    int banknotTip;
    int banknotSayi;
} kasa[5] = { {5,0},{10,0},{20,0},{50,0},{100,0}};

struct Hizmet{
    int hizmetID;
    char hizmetAdi[15];
    int hizmetHak;
    int hizmetFiyat;
} islem[4] = {{1,"kopukleme",30,15},{2,"yikama",50,10},
    {3,"kurulama",100,5},{4,"cilalama",20,50}};

struct Banknot banknot[5] ={{5,0},{10,0},{20,0},{50,0},{100,0}};
struct Banknot ust[5]={{5,0},{10,0},{20,0},{50,0},{100,0}};
struct Hizmet hizmet[4]={{1,"kopukleme",0,15},{2,"yikama",0,10},{3,"kurulama",0,5},{4,"cilalama",0,50}};

void setup()
{
  Serial.begin(9600);
  pinMode(buton1, INPUT);
  pinMode(buton2, INPUT);
  pinMode(buton3, INPUT);
  pinMode(buton4, INPUT);
  pinMode(buton5, INPUT);
  pinMode(buton6, INPUT);
  pinMode(kirmiziLed, OUTPUT);
  pinMode(yesilLed, OUTPUT);
}

void loop()
{
  girilenPara=0; harcananPara=0; toplam = 0;
  if(loopIsaret % 2 == 0){
    Serial.println("5 tl yuklemek icin 1. butona basin");
    Serial.println("10 tl yuklemek icin 2. butona basin");
    Serial.println("20 tl yuklemek icin 3. butona basin");
    Serial.println("50 tl yuklemek icin 4. butona basin");
    Serial.println("100 tl yuklemek icin 5. butona basin");
    Serial.println("Cikis icin 6. butona basin\n");
    loopIsaret++;
  }
  cikis=1;
  if(girilenPara == 0){
  while(cikis){
      if(digitalRead(buton1) == HIGH){
        banknot[0].banknotSayi += 1;
        kasa[0].banknotSayi += 1;
        Serial.println("5 tl yuklediniz");
        delay(1000);
    }
      if(digitalRead(buton2) == HIGH){
       banknot[1].banknotSayi += 1;
       kasa[1].banknotSayi += 1;
       Serial.println("10 tl yuklediniz");
       delay(1000);
      }
     if(digitalRead(buton3) == HIGH){
        banknot[2].banknotSayi += 1;
        kasa[2].banknotSayi += 1;
        Serial.println("20 tl yuklediniz");
        delay(1000);
      }
      if(digitalRead(buton4) == HIGH){
        banknot[3].banknotSayi += 1;
        kasa[3].banknotSayi += 1;
        Serial.println("50 tl yuklediniz");
        delay(1000);
      }
      if(digitalRead(buton5) == HIGH){
        banknot[4].banknotSayi += 1;
        kasa[4].banknotSayi += 1;
        Serial.println("100 tl yuklediniz");
        delay(1000);
      }
       if(digitalRead(buton6) == HIGH){
         cikis = 0;
     }        
  }
  } 
  if(loopIsaret % 2 == 1){ 
  cikis = 1;
    for(int k =0; k<5; k++){
        girilenPara += banknot[k].banknotSayi * banknot[k].banknotTip;
    }
    for(int j =0; j<5; j++){
        toplam += kasa[j].banknotSayi * kasa[j].banknotTip;
    }
    Serial.print("Girdiginiz para: ");   Serial.println(girilenPara);
    Serial.print("Kasadaki para: ");  Serial.println(toplam);
    hizmetIslemleri();
 	// randomSayi = millis() %4 +1;
    randomSayi =2;
  if(randomSayi == 2){
        digitalWrite(kirmiziLed,HIGH);
    	digitalWrite(yesilLed,LOW);
        Serial.println("\nPara sikisti");
        for(int a=0; a<5; a++){
            kasa[a].banknotSayi -= banknot[a].banknotSayi;
            toplam -= banknot[a].banknotSayi * banknot[a].banknotTip;
        }
        for(int g=0; g<4; g++){
            islem[g].hizmetHak += hizmet[g].hizmetHak;
        }
    Serial.println("Islemler iptal edildi.");
              for(int u=0; u<5; u++){
                if(banknot[u].banknotSayi != 0){
				  Serial.print(banknot[u].banknotSayi); Serial.print(" adet ");
                  Serial.print(banknot[u].banknotTip); Serial.println("TL iade edildi.");
             	}
          }
    Serial.print("Iade sonrasi kasadaki para: "); Serial.println(toplam);
    Serial.print("\nKalan kopukleme hakki: "); Serial.println(islem[0].hizmetHak);
    Serial.print("Kalan yikama hakki: ");    Serial.println(islem[1].hizmetHak);
    Serial.print("Kalan kurulama hakki: ");  Serial.println(islem[2].hizmetHak);
    Serial.print("Kalan cilalama hakki: ");  Serial.println(islem[3].hizmetHak);
    Serial.println("\n\n");  
  }
  else{
    HERE:
    Serial.println("\nDevam etmek istiyorsaniz 5.butona basin.");
    Serial.println("Yanlis secim yaptiysaniz 6.butona basin.\n");
    delay(2000);
    while(1){
    if(digitalRead(buton6) == HIGH){
      for(int b=0; b<4; b++){
            islem[b].hizmetHak += hizmet[b].hizmetHak;
            hizmet[b].hizmetHak = 0;
      }
    Serial.print("Resetleme sonrasi kasadaki para: ");  Serial.println(toplam);
    cikis = 1;  harcananPara=0;
    for(int k =0; k<5; k++)
    	girilenPara += banknot[k].banknotSayi * banknot[k].banknotTip;
     hizmetIslemleri();
      goto HERE;
    break;
    }
    else if(digitalRead(buton5) == HIGH){
     break; 
    }
 }
        digitalWrite(kirmiziLed,LOW);
    	digitalWrite(yesilLed,HIGH);
        girilenPara = 0;
        for(int k =0; k<5; k++)
            girilenPara += banknot[k].banknotSayi * banknot[k].banknotTip;
        int paraUstu = girilenPara - harcananPara;
        Serial.print("Para Ustu: ");  Serial.println(paraUstu);
        
    	if(paraUstu > toplam){
            printf("Kasada yeterli para yoktur.");
        }
        else{
            while(paraUstu){
               p=0;
              i1=0,i2=0,i3=0,i4=0;
                while(paraUstu >= kasa[p].banknotTip){
                    p++;
                }
              if(p==6) p=5;
                if(kasa[p-1].banknotSayi != 0){
                  if(p-1 >= 0){
                    ust[p-1].banknotSayi += 1;
                    paraUstu -= ust[p-1].banknotTip;
                  i1++;
                  }
                }
                else if(kasa[p-2].banknotSayi != 0){
                  if(p-2 >= 0){
                    ust[p-2].banknotSayi += 1;
                    paraUstu -= ust[p-2].banknotTip;
                  i2++;
                  }
                }
                else if(kasa[p-3].banknotSayi != 0){
                  if(p-3 >= 0){
                    ust[p-3].banknotSayi += 1;
                    paraUstu -= ust[p-3].banknotTip;
                  i3++;
                  }
                }
                else if(kasa[p-4].banknotSayi != 0){
                  if(p-4 >= 0){
                    ust[p-4].banknotSayi += 1;
                    paraUstu -= ust[p-4].banknotTip;
                  	i4++;
                  }
                }
              if((i1+i2+i3+i4) == 0)
                paraUstu = 0;
            }
          
          int ustToplam = 0;
          paraUstu = girilenPara - harcananPara;

          for(int j=0; j<5; j++){
			ustToplam += ust[j].banknotSayi*ust[j].banknotTip;
          }
          if(ustToplam == paraUstu){
            for(int z=0; z<5; z++){
                if(ust[z].banknotSayi != 0){
                  Serial.print(ust[z].banknotTip); Serial.print("TL'den ");
                  Serial.print(ust[z].banknotSayi); Serial.println(" adet verildi.");
             	}
          }
            for(int p=0; p<5; p++){
            	kasa[p].banknotSayi -= ust[p].banknotSayi;
            	toplam -= ust[p].banknotSayi * ust[p].banknotTip;
            }
          }else{
          	Serial.println("Para ustu yeterli banknot bulunmadigindan verilememektedir.");
          	Serial.println("Islemler iptal edildi.");
			for(int u=0; u<5; u++){
                if(banknot[u].banknotSayi != 0){
				  Serial.print(banknot[u].banknotSayi); Serial.print(" adet ");
                  Serial.print(banknot[u].banknotTip); Serial.println("TL iade edildi.");
             	}
          }            for(int b=0; b<4; b++){
            islem[b].hizmetHak += hizmet[b].hizmetHak;
      		}
            for(int a=0; a<5; a++){
            kasa[a].banknotSayi -= banknot[a].banknotSayi;
            toplam -= banknot[a].banknotSayi * banknot[a].banknotTip;
            }
          }
          Serial.print("\nKasada kalan para: ");   Serial.println(toplam);
          Serial.print("Kalan kopukleme hakki: "); Serial.println(islem[0].hizmetHak);
          Serial.print("Kalan yikama hakki: ");    Serial.println(islem[1].hizmetHak);
          Serial.print("Kalan kurulama hakki: ");  Serial.println(islem[2].hizmetHak);
          Serial.print("Kalan cilalama hakki: ");  Serial.println(islem[3].hizmetHak);
          Serial.println("\n\n");
          
        }
    }
  }
  		delay(2000);
      loopIsaret++;
      digitalWrite(kirmiziLed,LOW);
      digitalWrite(yesilLed,LOW);
  for(int y =0; y<5; y++){
        banknot[y].banknotSayi = 0;
    	ust[y].banknotSayi=0;
  }
  for(int r=0; r<4; r++){
        hizmet[r].hizmetHak = 0;
  }    
}

void hizmetIslemleri(){
	Serial.println("\nKopukleme icin 1. butona basin (15 TL)");
    Serial.println("Yikama icin 2. butona basin (10 TL)");
    Serial.println("Kurulama icin 3. butona basin (5 TL)");
    Serial.println("Cilalama icin 4. butona basin (50 TL)");
    Serial.println("Cikis icin 6. butona basin\n");
  
  while(cikis){
      if(digitalRead(buton1) == HIGH){
            if(girilenPara >= islem[0].hizmetFiyat && islem[0].hizmetHak > 0){
                islem[0].hizmetHak -= 1;
                hizmet[0].hizmetHak += 1;
                girilenPara -= islem[0].hizmetFiyat;
                Serial.println("Kopukleme sectiniz");
                delay(1000);
            }
           else if(girilenPara < islem[0].hizmetFiyat){
                Serial.println("Paraniz kopukleme icin yeterli degildir.");
           		delay(500); 
           }else{
              	Serial.println("Kopukleme hizmet hakki bulunmamaktadir.");
           		delay(500); 
           }
      }
      if(digitalRead(buton2) == HIGH){
            if(girilenPara >= islem[1].hizmetFiyat && islem[1].hizmetHak > 0){
                islem[1].hizmetHak -=1;
                hizmet[1].hizmetHak += 1;
                girilenPara -= islem[1].hizmetFiyat;
                Serial.println("Yikama sectiniz");
                delay(1000);
            }
             else if(girilenPara < islem[1].hizmetFiyat){
                Serial.println("Paraniz yikama icin yeterli degildir.");
            	delay(500);
             }else{
              	Serial.println("Yikama hizmet hakki bulunmamaktadir.");
            	delay(500);
             }
      }
      if(digitalRead(buton3) == HIGH){
            if(girilenPara >= islem[2].hizmetFiyat && islem[2].hizmetHak > 0){
                islem[2].hizmetHak -=1;
                hizmet[2].hizmetHak += 1;
                girilenPara -= islem[2].hizmetFiyat;
                Serial.println("Kurulama sectiniz");
                delay(1000);
            }
            else if(girilenPara < islem[2].hizmetFiyat){
                Serial.println("Paraniz kurulama icin yeterli degildir.");
                delay(500);
            }else{
              	Serial.println("Kurulama hizmet hakki bulunmamaktadir.");
            	delay(500);
            }
      }
      if(digitalRead(buton4) == HIGH){
            if(girilenPara >= islem[3].hizmetFiyat && islem[3].hizmetHak > 0){
                islem[3].hizmetHak -=1;
                hizmet[3].hizmetHak += 1;
                girilenPara -= islem[3].hizmetFiyat;
                Serial.println("Cilalama sectiniz");
                delay(1000);
            }
 			else if(girilenPara < islem[3].hizmetFiyat){
                Serial.println("Paraniz cilalama icin yeterli degildir.");
                delay(500);
            }else{
              	Serial.println("Cilalama hizmet hakki bulunmamaktadir.");
                delay(500);
            }
      }
      if(digitalRead(buton6) == HIGH){
            cikis = 0;
      } 
    }
      for(int l=0; l<4; l++){
        harcananPara += hizmet[l].hizmetHak * hizmet[l].hizmetFiyat;
    }
  Serial.print("Harcanan para: "); Serial.println(harcananPara);
}