//@BP3 PROJE
//@date: 13.12.2025-14.12.2025-19.12.2025-20.12.2025
//@ Nisa Aktaş nisa.aktas@stu.fsm.edu.tr 
/*@ Bu proje, bir kitapevindeki Kategorileri ve bu kategorilere ait Kitapları yönetmek için
tasarlanmıştır. */
//@ Proje 1 


#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>


int main(){

    //kategori dizisi tanımlama 
Kategori *kategoriDizisi=NULL;
int kategoriSayisi=0;

printf("***SİSTEM BASLATILIYOR***\n\n");

// 4 kategori varsayıp kategori dizisine bellekye yer ayırıyoruz 
kategoriSayisi=4;
kategoriDizisi=(Kategori*)malloc(kategoriSayisi*sizeof(Kategori));
if(kategoriDizisi==NULL){
    printf("HATA: Bellek Ayırma Basarısız\n");
    exit(EXIT_FAILURE);
}

  //BU KISIM DosyadanDiziyeAktar fonksiyonu cagırılmadan en basta dosyalara verı eklemek ıcın kullanılmıstır.   


  printf("\nBaslangıc Verileri Olusturuluyor.\n\n");
    
char uzun_kategori_adi[]="30_karakterı_asan_kategori_adlandırında_ilk_30_karakterden_sonrası_kategori_adına_eklenmez.";
char uzun_kitap_adi[]="Bu_Kitabın_Adı_50_Karakterden_Daha_Uzun_İse_Max_50_Karakter_Alınmalıdır_50_karakterden_sonrası_eklenmeyecektir_.";
char uzun_yazar_ad[]="Yazar Adı 40 Karakter Asarsa İlk 40 Karakter Kullan";

kategoriDizisi[0]=KategoriOlustur("Roman",1);
kategoriDizisi[1]=KategoriOlustur("Hikaye",2);
kategoriDizisi[2]=KategoriOlustur("ŞİİR",3);
kategoriDizisi[3]=KategoriOlustur(uzun_kategori_adi,4);


Kitap b1=KitapOlustur("Suç Ve Ceza","Dostoyevski",1,85.0f,1866);
KitapEkle(kategoriDizisi,&kategoriSayisi,b1);
Kitap b2=KitapOlustur("DUNE", "Frank Herbert",2,120.0f,1965);
KitapEkle(kategoriDizisi,&kategoriSayisi,b2);
Kitap b3=KitapOlustur("Yüzyıllık Yalnızlık","Gabriel Garcia Marquez",1,150.0f,1967);
KitapEkle(kategoriDizisi,&kategoriSayisi,b3);
Kitap b4=KitapOlustur("Sefiller","Victor Hugo",1,60.0f,1862);
KitapEkle(kategoriDizisi,&kategoriSayisi,b4);
Kitap b5=KitapOlustur("Ağaçkakan","Sait Faik Abasıyanık",2,120.0f,1965);
KitapEkle(kategoriDizisi,&kategoriSayisi,b5);
Kitap kk=KitapOlustur(uzun_kitap_adi,uzun_yazar_ad,4,150.00,2024);
KitapEkle(kategoriDizisi,&kategoriSayisi,kk);
    
printf("Baslangıc Verılerı Olusturuldu. \n\n");  



//olusturulan verılrı dosyaya gınderdım
DiziyDosyayaYaz(kategoriDizisi,kategoriSayisi);

//dizideki verileri sıfırladım. 
bellekTemizle(kategoriDizisi,kategoriSayisi);
kategoriDizisi=NULL;
kategoriSayisi=0;


//diziye dosyadan verıleri tekrar ekledım 
DosyadanDiziyeAktar(&kategoriDizisi,&kategoriSayisi);



printf("FONKSİYON TESTLERİ.\n");


    //TÜM KATEGORİLERİ GÖRÜNTÜLEME**;
    TumKategorileriYazdir(kategoriDizisi,kategoriSayisi);

    printf("**TEKLİ BİLGİ YAZDIRMA\n");

    //Kategori Bilgileri
    //kategori dizisini gezip ilgili elemaın adresını pointer attı 
    for (int i=0;i<kategoriSayisi;i++){
        Kategori *k=&kategoriDizisi[i];
        KategoriBilgileriniYazdir(k);

        //kategorinşn kitaplarını gezıp her kıtabın bılgısını yazdırdı
        if((*k).kitapSayisi>0){
           //Kitap Bilgileri- kitaplar dizisini döner j. elemanın adresını fonk atar 
            for(int j=0;j<(*k).kitapSayisi;j++){
                KitapBilgileriniYazdir(&(*k).kategoriKitaplar[j]);
            }
    }
    }

//ORTALAMA HESABI
    printf("**Kategori Ortalama Hesabı**\n");
    printf(".............................\n");
    //ksategori dizisini gezip k pointera atıyor 
    for(int i=0;i<kategoriSayisi;i++){
        Kategori *k= &kategoriDizisi[i];
        FiyatOrtalamasiHesapla(k);
        printf("\n");
    } 

    
//FİYAT GUNCELLEME 
printf("**FİYAT GÜNCELLEME** \n");
printf("\n");
EskiKitapFiyatGuncelle(kategoriDizisi,kategoriSayisi,1900,555.00f);

//ORTALAMA ÜSTÜ KİTAPLAR
printf("\n**ORTALAMA ÜSTÜ KİTAPLAR** \n");
//kategori dizisini gezip pointer ı fonk atıyor 
for (int i=0;i<kategoriSayisi;i++){
    Kategori *k=&kategoriDizisi[i];
    OrtalamaUstuKitaplariListele(k);

   }
    
//en pahalı kıtaplar 
    printf("\n**EN PAHALI KİTAPLAR\n");
    EnPahaliKitaplariYazdir(kategoriDizisi,kategoriSayisi);
    
printf("Sistem Sonlandırılıyor.\n");


//guncel hali dosyaya yazdırdım. 
DiziyDosyayaYaz(kategoriDizisi,kategoriSayisi);



//guncel liste 
printf("KATEGORİLER VE KİTAPLAR GUNCEL LİSTE\n");
//kategori dizisini gezıip pointer ı fonk atıyoruz
for (int i=0;i<kategoriSayisi;i++){
        Kategori *k=&kategoriDizisi[i];
        KategoriBilgileriniYazdir(k);
 
        if((*k).kitapSayisi>0){
           //Kitap Bilgileri- Kitapları dönüp 
            for(int j=0;j<(*k).kitapSayisi;j++){
                KitapBilgileriniYazdir(&(*k).kategoriKitaplar[j]); //dizideki j. elemanı hulur adreını fonk atar. 
            }
    }
    }

bellekTemizle(kategoriDizisi,kategoriSayisi);

printf("**PROGRAM SONLANDIRILDI**\n");

return 0; 

}