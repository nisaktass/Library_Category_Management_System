//@ BP3 proje
/*@ Nisa Aktaş nisa.aktas@stu.fsm.edu.tr */
/*@ Bu proje, bir kitapevindeki Kategorileri ve bu kategorilere ait Kitapları yönetmek için
tasarlanmıştır. */
//@ Proje 1 

#include "proje1.h"
#include<stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <float.h>

//@date:07.12.2025
// 1 kategori olusturma
Kategori KategoriOlustur(char *ad, unsigned short kod){
Kategori k; //kategorş nesnesi 
size_t length; //karakter uzunlupu tutmak için 

//basta çöp değerleri temizleyip tum değerleri sıfırlama. 
 k.kategoriAdi=NULL;
 k.kategoriKitaplar=NULL;
 k.kapasite=0;
 k.kategoriKodu=0;
 k.kitapSayisi=0; 

 //kontroller 
 //gönderılen  adın bos olup olmadııg kontrol
 if(ad==NULL||strlen(ad)==0){
    printf("HATA: KATEGORİ ADI GİRİNİZ");
    exit(EXIT_FAILURE); //program sonlandırıyor 
 }
 
 //max 30 karakter olması ıcın. 
length=strlen(ad);
if(length>30){
    printf(" KATEGORİ ADI COK UZUN İlk 30 karakter kullanılacak.\n");
    length=30;
 }


//kategori isimleri için bellek ayırıyoruz char*: strıng ıcın yer ayırıyoruz. 
k.kategoriAdi=(char*)malloc(sizeof(char)*(length+1)); //length +1 '\0' için 

//kontrol
if(k.kategoriAdi==NULL){
    printf("HATA: BELLEK AYRILAMADI.\n");
    exit(EXIT_FAILURE);
}

//Malloc ile ayrılan yere verileri yollama 
//İSMİ KOPYALAMA. length kadar. 
strncpy(k.kategoriAdi,ad,length); //30 karakter asmasın dıyte strncpy
k.kategoriAdi[length]='\0'; //sonlandırıcı eklıyoruz. strncpy eklemez. 

k.kategoriKodu=kod;
k.kapasite=2; //basta 2 kıtaplık yer ayırdım. 
k.kitapSayisi=0;


//kitap dizisini saklamak için 
//1 kitap değil 1den fazla kitap saklayacak o yuzden kitap* 
k.kategoriKitaplar=(Kitap*)malloc(sizeof(Kitap)*k.kapasite); //kitapların dizisini saklamak için  zamanla artacagı ıcın dınamık 
//MALLOC İÇİN KONTROL 
if(k.kategoriKitaplar==NULL){
    free(k.kategoriAdi);
    exit(EXIT_FAILURE);

}


return k;
}




// 2 Kitap Olusturma
Kitap KitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil){
    Kitap k;
    size_t length;

    k.kitapAdi=NULL;
    k.yazar=NULL;
    k.basimYili=0;
    k.fiyat=0.0f;
    k.kategoriKodu=0;


//kitap ismi bos mu dıye kontrol. 
    if(ad==NULL||strlen(ad)==0){
        printf("HATA: KİTAP ADI GİRİNİZ \n");
       exit(EXIT_FAILURE);
    }
//kitap adı sınırlama 
    length=strlen(ad);
    if(length>50){
        printf("KİTAP İSMİ COK UZUN İLK 50 KARAKTER KULLANILACAK\n");
        length=50;
    }
//kitap adı için yer acıyoruz. length+1 sondaki '\0' için. 
    k.kitapAdi=(char*)malloc(sizeof(char)*(length+1));
    
    //actıgım yere kitabın adını uzunluk kadar kopyalıyorum 
    strncpy(k.kitapAdi,ad,length);
    k.kitapAdi[length]='\0'; //nul termınator strncpy 30 karakter okuyunca sona '\0' bundan koymaz bu da olmayınca rastgele değerleri okumaya devam edr program. 
    

    //yazar adı grırıldı mı kontrol. 
    if(yazar==NULL || strlen(yazar)==0){
        printf("HATA: YAZAR ADI GİRİNİZ \n");
        free(k.kitapAdi); //önceden ayırdıgımız adı serbesst bırakma. 
        exit(EXIT_FAILURE);
    }
//yazar ısmı max 40 karakter olsun dıye 
    length=strlen(yazar);
    if(length>40){
        printf("YAZAR ISMI COK UZUN İLK 40 KARAKTER KULLANILACAK \n");
        length=40;
    }
   //yazar ısmı ıcın yer acma
    k.yazar=(char*)malloc(sizeof(char)*(length+1));
    //yazar ısmını bellege yolluyorum 
    strncpy(k.yazar,yazar,length);
    k.yazar[length]='\0';

    k.kategoriKodu=kod;
    k.fiyat=fiyat;
    k.basimYili=yil;
    return k;

}



/*@date:10.12.2025-11.12.2025 */
// 3 Kitapları ilgili kategoriye ekleme
void KitapEkle(Kategori *kategoriDizi, int *kategoriSayisi, Kitap yeniKitap){
int hedefIndex=-1; //kitap hangı kategoriye ait bulmak için 

//kategori dizisini dolaşıp yenı kıtabın kateogı kodunu kategori dizisinde bulmaya calısıyor 
for(int i=0;i< *kategoriSayisi;i++){
    if(kategoriDizi[i].kategoriKodu==yeniKitap.kategoriKodu){
        hedefIndex=i;
        break;
    }
}
//kod dızıden eşleşmedıyse 
if (hedefIndex==-1){
printf("HATA: Kategori Bulunamadı \n");
if(yeniKitap.kitapAdi!=NULL)free(yeniKitap.kitapAdi);
if(yeniKitap.yazar!=NULL)free(yeniKitap.yazar);

return;
}


//buldugumuz KATEGORİYE ERİŞİM için bunu kullanıyorum 
//buldugum kategorinin adresi hedefkategori pointer a gonderıyorum. 
Kategori * hedefKategori=&kategoriDizi[hedefIndex];


//KAPASİTE KONTROL BELLEK GENISLETME 
int yeniKapasite;
if((*hedefKategori).kitapSayisi>=(*hedefKategori).kapasite){


if((*hedefKategori).kitapSayisi==0){
     yeniKapasite= 2;

}else{
        yeniKapasite=(*hedefKategori).kapasite*2;
    

    printf("Kategori '%s' dolu kapasite artırılıyor.\n ",(*hedefKategori).kategoriAdi);

}
    //kitap türü, temp değişkeni (geçici işaretcı realloc basarısız olursa diye, kategorideki litaplar dızisine erişip boyut değiştiriyor sizeof(KİTAP)=BİR KİTABIN BELLKETEKI BAYT MIKTARI 
    Kitap*temp= (Kitap*)realloc((*hedefKategori).kategoriKitaplar,yeniKapasite*sizeof(Kitap));

    if(temp==NULL){
        printf("realloc basarısız oldu");
        if(yeniKitap.kitapAdi!=NULL)free(yeniKitap.kitapAdi);
        if(yeniKitap.yazar!=NULL)free(yeniKitap.yazar);
        return;
    }
    
    (*hedefKategori).kategoriKitaplar=temp; //pointer guncelledi daha buyuk bellek oldu baslangıc=temp. eski bellek adresi temp adresine tasındı 
    (*hedefKategori).kapasite=yeniKapasite; //kapasite guncelledik. 

}
 



//kitabı yerleştırme 
//kategori kıtapların hangı ındexıne yerleşşsın 
int yeniSayi=(*hedefKategori).kitapSayisi; //2 kitap varsa 2 olacak 0 1 dolu olacak 2. indekse yazacagız dırekt 

//belırlı ındexe yerlestırıyorum 
(*hedefKategori).kategoriKitaplar[yeniSayi]=yeniKitap;
//kitap sayısı artırma 
(*hedefKategori).kitapSayisi=(*hedefKategori).kitapSayisi+1; // kitap sayısını artıordıdk. 
//adresteki kategoriye gidip oradaki kitap sayısını alır. 

}




// 4 Kitap bilgisi yazdırma
void KitapBilgileriniYazdir(Kitap *kitap){


    if(kitap==NULL){
        printf("Kitap Bulunamadı");
        return;
    }
    



    //printf("..................");
    printf("**KİTAP BİLGİLERİ**\n");
   // printf("..................");
    
    printf("Kitap Adı:%s\n",(*kitap).kitapAdi); //pointerın işraet ettiği nesne.değişken
    printf("Yazar Adı:%s\n",(*kitap).yazar);
    printf("Basım Yılı:%d\n",(*kitap).basimYili);
    printf("Fiyat:%2.f TL\n",(*kitap).fiyat);
    printf("Kategori Kodu: %hu\n",(*kitap).kategoriKodu);

    printf("........................\n");


}

//5 Kategori bilgisi yazdırma 
void KategoriBilgileriniYazdir(Kategori *kategori){
    
    if(kategori==NULL){
        printf("kategori bulunamadı.\n");
        return;
    }

   
    printf("**Kategori Bilgileri** \n");
  

   
    printf("Kategori Adı: %s\n",(*kategori).kategoriAdi); //pointerın nesnesi.değişken
    printf("Kategori Kodu:%hu\n",(*kategori).kategoriKodu);
    printf("Toplam Kitap Sayısı:%d\n",(*kategori).kitapSayisi);
    printf("..........................\n");
}

// 6 tum kategorileri ve kitaplarını yazdırma
void TumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi){
   
    //liste bos mu kontrol 
   if(kategoriDizi==NULL||kategoriSayisi==0){
    printf("Veri Bulunamadı.\n");
    return;
   }
    
    printf("** TÜM KATEGORİLER VE KİTAPLAR ** \n");
   

    //Kategorileri dönüyor
    for(int i=0;i<kategoriSayisi;i++){
        Kategori k=kategoriDizi[i];
       //kontrol
        if(k.kitapSayisi==0){
            printf("%s KATEGORİSİ BOŞ\n",k.kategoriAdi);
            continue; //bir sonraki kategoriye geç döngu basa doner 
        }
        //kategorideki kitapları dönuyor 
        for(int j=0;j<k.kitapSayisi;j++){
            Kitap b=k.kategoriKitaplar[j];
         //i kategori index j kitap index 
            printf("%s [%d.%d] %s\n ",k.kategoriAdi,i+1,j+1,b.kitapAdi);

        }
    }
}
 // 7 kategor bazlı ortalama fiyat hesaplama
float FiyatOrtalamasiHesapla(Kategori *kategori){
    float ortalama;
    //kategori bos mu kontrol
    if(kategori==NULL){
        printf("Kategori Yok\n"); //öyle bir işaretcı olmadıgında 
        return 0.0f;
    }
    //kategoride kitap var mı kontrol 
    if((*kategori).kitapSayisi==0){
        printf("%s Kategorisinde Hiç Kitap Bulunmamaktadır.\n ",(*kategori).kategoriAdi);
        return 0.0f;
    }
    float toplam=0.0f;
    //her kategoriye gidip kitaplarının fıyatını topluyor 
    for(int i=0;i<(*kategori).kitapSayisi;i++){ //pointerın nesnesi.değişken 
        toplam+=(*kategori).kategoriKitaplar[i].fiyat; //1 kategorideki kitapların fıyatını topluyor 
   //kategorileri mainde döndüm 
        
 }

 ortalama= toplam/(*kategori).kitapSayisi; 
 
        printf("%s kategorisi için Fiyat Ortalaması:%.2f TL\n",(*kategori).kategoriAdi,ortalama);
        printf("\n");
        
  return ortalama;
}


// her kategorideki ortakama ustu kıtapları yazdırma
void OrtalamaUstuKitaplariListele(Kategori *kategori){
    //kontrol 
    if(kategori==NULL){
        printf("kategori yok\n"); //öyle bir işaretcı olmadıgında 
        return ;
    }

    if((*kategori).kitapSayisi==0){
        printf("Kategoride hiç kitap bulunmamaktadır. \n");
        return ;
    }

    //ortaka fıyatı alıyor. 
    float ortalama=FiyatOrtalamasiHesapla(kategori);

    if(ortalama==0.0f){
        printf("ortalama fıyat sıfırdır. ortalama üstü kitap bulunmamaktadır. \n");
        return;
    }
   
    
    int sayi=0;
    //kategorideki kıtapları dönüyor. her bırının fıyatını alıp ortalamayla kıyas 
    for(int i=0;i<(*kategori).kitapSayisi;i++){
        float kitapFiyatı=(*kategori).kategoriKitaplar[i].fiyat;

        if(kitapFiyatı>ortalama){
            printf("%d-%s(Fiyat: %2.f TL)\n",sayi+1,(*kategori).kategoriKitaplar[i].kitapAdi,kitapFiyatı);
            printf("\n");
           //ortalama ustu kitap bulunca sayacı artırıyoruz 
            sayi++;

        }
    }
    //bulunamazsa 
    if(sayi==0){
        printf("Bu Kategoide Ortalama Fiyat Üzerınde Kitap Bulunmamaktadır. \n");
    }
}

// 9 her kategorinin en pahalı kitabını yazdırma
void EnPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi){

printf("**KATEGORİ BAZLI EN PAHALI KİTAPLAR**\n");

//kontroller 
if(kategoriDizi==NULL||kategoriSayisi==0){
    printf("Kategori Bulunamadı");
    return;
}

//kategorileri dönüp ilgili kategoriyi k değişkenıne atıyor 
for(int i=0;i<kategoriSayisi;i++){
    Kategori k=kategoriDizi[i];
//kategorinin kitabı var mı kontrol 
    if(k.kitapSayisi==0){
        printf("%s Kategorisinde Hiç Kitap Bulunmamaktadır.\n",k.kategoriAdi);
        continue;
    }

    //max ı en küçük float değişkenine atıyor. 
    float max =FLT_MIN; //MİN FLOAT DEĞERİ İLE BASLADIK.
   
    Kitap *pahalı=NULL; 
//kategorideki tüm kitapları dönüyor 
    for(int j=0;j<k.kitapSayisi;j++){
        //kitap fiyatı max dan buyukse 
        if(k.kategoriKitaplar[j].fiyat>max){
            //yeni max bu kıtabın fıyatı oluyor 
            max=k.kategoriKitaplar[j].fiyat;
        }
        }
    

    
        printf(" Kategori: %hu %s || Fiyat:%.2f TL \n",k.kategoriKodu,k.kategoriAdi,max);
        
        //en yuksek fıyata sahıp bırden fazla kıtap varsa onu da yazsırmak için 2. döngü 
        for(int j=0;j<k.kitapSayisi;j++){
            if(k.kategoriKitaplar[j].fiyat==max){
                printf("-> %s\n",k.kategoriKitaplar[j].kitapAdi);

            }
        }
        printf(".....................\n");

}

}
// 10 belirlenen yıldan önce basılmıs kıtapların fıyatını guncelleme
void EskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat){
    //kontroller. 
    if(kategoriDizi==NULL||kategoriSayisi==0){
    printf("Kategori Bulunamadı");
    return;
    }
//kategorileri dönüp ilgili kategoriyi k ye atar 
    for (int i=0;i<kategoriSayisi;i++){
        Kategori k= kategoriDizi[i];

        if(k.kitapSayisi==0){
            continue;
        }
        
        int güncellenen=0;

        printf("Kategori: %s \n", k.kategoriAdi);
        printf("\n");
        //kategorinin kitaplarını döner 
        for(int j=0;j<k.kitapSayisi;j++){
            
            //kitabın adresi bir pointere atılır kalıcı değişim 
            Kitap * adres=&k.kategoriKitaplar[j];
             //adrestekı kıtabın basım yılını karsılastırma 
            if((*adres).basimYili<yil){
                float eskiFiyat=(*adres).fiyat;
                //guncelleme 
                (*adres).fiyat=yeniFiyat;
                printf(" -> %s Kitabı güncellendi. Güncel Fiyat %.2f, Eski Fiyat %.2f \n",(*adres).kitapAdi,yeniFiyat,eskiFiyat);
                printf("\n");
                //guncelleme olunca sayac artırma 
                güncellenen++;

             }
        }
        if(güncellenen==0){
            printf("%s Kategorisinde Guncellenecek Kitap Bulunmadı\n",k.kategoriAdi);
        }
    }
}



// 11 dizideki verileri txt dosyalarına yazma 
void DiziyDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi){

    // dosya işaretcısı olusturma 
    FILE *kategoriDosya=NULL;
    FILE *kitapDosya=NULL;
    //yazılak dizi var mı kontrol. 
    if(kategoriDizi==NULL||kategoriSayisi==0){
        printf("kategori Bulunamadı.");
        return;
    }

    //write modunda dosyayı acar 
    kategoriDosya=fopen("Kategoriler.txt","w"); //w ///////////////
    kitapDosya=fopen("Kitaplar.txt","w");
   
    //kontrol
    if(kategoriDosya==NULL||kitapDosya==NULL){
        printf("Dosya Acılamadı");
        //bırı acılıp bırı acılaamazsa acılanı kapatır 
        if(kategoriDosya!=NULL)fclose(kategoriDosya);
        if(kitapDosya!=NULL)fclose(kitapDosya);
        return;
    }
   
    
    printf("Kategori.txt ve Kitap.txt Dosyaları Olusturuldu.\n\n");

      //kategori dolaşmak için ilgili kategori k ye atıyır 
     for(int i=0;i<kategoriSayisi;i++){
        Kategori k=kategoriDizi[i];
       //o kategorinin adını kodunu dosyaya yazıyor. 
        fprintf(kategoriDosya, "%hu\t%s\n",kategoriDizi[i].kategoriKodu,kategoriDizi[i].kategoriAdi); //hu unsıgned short oldugu ıcın 
      //kitapları dolaşma  ilgili kitabı b ye atıyor 
        for(int j=0;j<kategoriDizi[i].kitapSayisi;j++){
            Kitap b=kategoriDizi[i].kategoriKitaplar[j];

            //o kitabın bılgılerını dosyaya yazıyor. 
            fprintf(kitapDosya,"Kitap Adı: %s\n",b.kitapAdi);
            fprintf(kitapDosya,"Yazar:%s\n",b.yazar);
            fprintf(kitapDosya,"Basım Yılı %d\n",b.basimYili);
            fprintf(kitapDosya,"Fiyat: %.2f\n",b.fiyat);
            fprintf(kitapDosya,"Kategori Kodu: %hu\n",b.kategoriKodu);
            fprintf(kitapDosya,"...................\n");
            
        }
     }
     //işlem bitince dosya kapatma
     fclose(kategoriDosya);
     fclose(kitapDosya);

}

//@date:17.12.2025-18.12.2025-19.12-2025
// 12 Dosyadan diziye veri cekme 
void DosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr){
    
    //dosyadan okuyaxagımız verıler ıcın buffer 
    FILE *fk,*fb; //kategori ve kıtap dosyaları ıcın ısaretcı 
    char kategoriAd[100];
    char kitapAd[100];
    char yazar[100];
    unsigned short kategoriKod;
    float fiyat;
    int yil;
   
//kontrol 
   if( *kategoriDiziPtr==NULL){
  *kategoriDiziPtr=NULL;  //diziyi bos baslatma Maİnden de değiştirir ptr 
 *kategoriSayisiPtr=0;
   }
   //KATEGORİLERI DOSYADAN OKUMA
   //kategori dosyasını read modunda actık. 
    fk=fopen("Kategoriler.txt","r");
    //kontrol
    if(fk==NULL){
        printf("Kategoriler.txt acılamadı\n" );
        return;
    }
 

    if(fk!=NULL){
        //verıyı okuma %99s : kelimenın max 99 karkterını oku. 
    while (fscanf(fk,"%hu %99s",&kategoriKod,kategoriAd)==2){ //Kategori ad dizi zate adres o yuzden & gerek yok 
        //yenı bır kategori yapısı olusturma okudugumuz kod ve ad ile 
        Kategori yeniKategori= KategoriOlustur(kategoriAd,kategoriKod);

        //her yenı kategori için ana diziyi buyutuyorum 
        *kategoriDiziPtr=realloc(*kategoriDiziPtr,(*kategoriSayisiPtr +1) *sizeof(Kategori));

        //olusturdugumuz kategoriyi dizinın son ındeksıne yollama 
        (*kategoriDiziPtr)[*kategoriSayisiPtr]=yeniKategori;
        (*kategoriSayisiPtr)++; //sayıyı artırma 
    }

    fclose(fk);//dosya kapata 
    }
    

    //KİTAPLARI DOSYADAN OKUMA 
    //kitaplar txt acar: 
    fb=fopen("Kitaplar.txt","r");
    if(fb==NULL){
        printf("Kitaplar.txt acılamadı");
        return;
    }
    char satir[256]; //her satır gecıcu olarak bu kutuya
    

    while(fgets(satir,sizeof(satir),fb)!=NULL){ //dosyadan 1. satırı komple okur 
        if(strncmp(satir,"Kitap Adı:",10)==0){ //satrın ilk 10 karakterı "KİTAP ADI:"ile aynı mı karsılastuırır
            char *veri=satir+10; //kitap adı kısmını atlar asıl verıyo alır 
            while(*veri==' '||*veri==':')veri++; //verının basındakı bısluk : karakterlerı atlar 

            strcpy(kitapAd,veri); //temizlenmia sadece isim kısmını değişkene kopyalar 
            
            /***strcspn: satır somu sonundakı gorunmez \n karakterının kacıncı indekste old bulıur indeks
            numarası döner bız de o ındeksı 0 koyyoruz */
            kitapAd[strcspn(kitapAd,"\r\n")]=0; 
        
       if( fgets(satir,sizeof(satir),fb)){ //dosyadan 2. satırı komple okur 
        veri=satir+6; //yazar: kısmını atlar 
        while(*veri==' '||*veri==':')veri++; //bosluk : karakterı atla verıyı 1 artırarak 
        if(strncmp(satir,"Yazar:",6)==0){ //satırın ilk 6 karaskterı yazar: ile aynı mı karsılastır aynıysa 0 döner strcmp 
            strcpy(yazar,veri);//oyleyse verıyı değişkene kpylayalr 
            yazar[strcspn(yazar,"\r\n")]=0; //strcspn sondakı bosluk karakterın ındeksını veırır bız onu 0 yaptık 
        }
    }

           if( fgets(satir,sizeof(satir),fb)){ //dosyanın 3. satırını okur 
            
            char *p=strpbrk(satir,"0123456789"); //strpbrk: ilk rakmı gorunce durur adresı p ye verır 
           if(p!=NULL){ //adres bos deilse 
                yil=atoi(p); //atoi:p adresınden baslar rakamları okur sayıya cevırır. int 
            }else{
            yil=0;
            }
            
        }
        if(fgets(satir,sizeof(satir),fb)){ //dosyanın 4. satırına gıder okur 
            
                fiyat=(float)atof(satir+7); //satırda ilk 7 yı atlar metnı float cevırır
            }
            if(fgets(satir,sizeof(satir),fb)){ //dosya 5. satırı okur 
            
                kategoriKod=(unsigned short)atoi(satir+15); //ilk 15 atlar buldugunu sayı yapar 
            }
           fgets(satir,sizeof(satir),fb); //dosya 6. satırı okur .... kısmını 
           //printf("DEBUG: Okunan Kitap: %s, Kod: %hu\n", kitapAd, kategoriKod);

           //okudugumu verılerle yenı kıtap olusturuyoruz 
            Kitap yk=KitapOlustur(kitapAd,yazar,kategoriKod,fiyat,yil);
            strcpy(yk.yazar,yazar);
            yk.kategoriKodu=kategoriKod;
            yk.basimYili=yil;
            yk.fiyat=fiyat;

            //döngü ile ait oldugu kategori bulma ve ekleme 
            //*kategoriSayisiPtr mainden düzgünce almak için 

            for (int i=0;i<*kategoriSayisiPtr;i++){
                //maindeki dizinin i. elemanının kodu == bizim okudugımuz kod 
                if((*kategoriDiziPtr)[i].kategoriKodu==kategoriKod){
                    //buldugumuz kategorinin adresi ,kategor sayı adresi,yenı kıtap 
                    KitapEkle(&(*kategoriDiziPtr)[i],kategoriSayisiPtr,yk);
                    break; //doğru kategori bulunca diğerleirne bakma 
                }
            }

        }
    }
    
fclose(fb); //dosyayı kapat 
    
}


       

        
    
    //@date: 11.12.2025
    // 13 bellek temizleme 
void bellekTemizle(Kategori *kategoriDizi,int kategoriSayisi){
    
    //kontrol 
    if(kategoriDizi==NULL || kategoriSayisi<=0){
        printf("Bellek iadesi gerektiren bir veri bulunamadı.");
        return;
    }
    //kategorileri dolasır işlem yapılacak kategorinin adresını alır 
    for(int i=0;i<kategoriSayisi;i++){
        Kategori *k=&kategoriDizi[i];

        //adrestekı dızı bos değilşse 
        if((*k).kategoriKitaplar!=NULL){
            //kitapları gezer ilgili kitabın adresını b ye atar 
            for (int j=0;j<(*k).kitapSayisi; j++){
                Kitap *b=&(*k).kategoriKitaplar[j];

                //ismi yazazrı bellekten sıler işaretcıyı sıfırlar 
                if ((*b).kitapAdi !=NULL){
                    free((*b).kitapAdi);
                    (*b).kitapAdi=NULL;
                }
                if((*b).yazar!=NULL){
                    free((*b).yazar);
                    (*b).yazar=NULL;
                
                }

            }
            //kitapları bellekten sıler 
            free((*k).kategoriKitaplar);
            (*k).kategoriKitaplar=NULL;

        }
        //kategoriyi siler 
        if((*k).kategoriAdi!=NULL){
            free((*k).kategoriAdi);
            (*k).kategoriAdi=NULL;
        }
    
    
    }
    //kategori dizisini serbest bırakır 
        free(kategoriDizi);
       // kategoriDizi=NULL;
    
    printf("iade işlemi gerçekleşti.\n ");
    printf("..............................\n\n");

};
    




