//@BP3 PROJE
// @ Nisa Aktaş nisa.aktas@stu.fsm.edu.tr 
/*@ Bu proje, bir kitapevindeki Kategorileri ve bu kategorilere ait Kitapları yönetmek için
tasarlanmıştır. */
//@date 06.12.2025
//@ Proje 1 

//aynı header dosyasının bırden fazla kez okunmasını önlemek 
#ifndef proje1_h
#define proje1_h


#include<stdio.h>


typedef struct {
char *kitapAdi; // Kitabın adı (Dinamik bellek, max 50 karakter)
char *yazar; // Yazarın adı (Dinamik bellek, max 40 karakter)
unsigned short int kategoriKodu; // Hangi kategoriye ait olduğunu belirten kod
float fiyat; // Kitabın fiyatı
int basimYili; // Kitabın basım yıl
} Kitap ;

typedef struct {
    char *kategoriAdi; // Kategorinin adı (Dinamik bellek, max 30 karakter)
unsigned short int kategoriKodu; // Kategorinin benzersiz kodu
Kitap *kategoriKitaplar; // Bu kategoriye ait kitapların dinamik dizisi
int kitapSayisi; // Dizideki mevcut kitap sayısı
int kapasite; // Dizinin o anki maksimum kapasitesi (Dinamik bellek yönetimi için)
} Kategori;





Kategori KategoriOlustur(char *ad, unsigned short kod); //struct döndürüyor 
Kitap KitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil); //stsruct dönduruyır
void KitapEkle(Kategori *kategoriDizi, int *kategoriSayisi, Kitap yeniKitap);
void KitapBilgileriniYazdir(Kitap *kitap);
void KategoriBilgileriniYazdir(Kategori *kategori);
void TumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi);
float FiyatOrtalamasiHesapla(Kategori *kategori);
void OrtalamaUstuKitaplariListele(Kategori *kategori);
void EnPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi);
void EskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat);
void DiziyDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi);
void DosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr);
void bellekTemizle(Kategori *kategoriDizi,int kategoriSayisi);


#endif



