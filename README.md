# Kitap Yönetim Sistemi

Bu proje, bir kitapevindeki kategorileri ve kitapları dinamik bellek mimarisi kullanarak yönetmek amacıyla C dili ile geliştirilmiştir.

## Proje Özellikleri
* **Dosya Entegrasyonu:** Başlangıçta `Kategoriler.txt` ve `Kitaplar.txt` dosyalarındaki verileri okur; program kapanırken güncel verileri tekrar dosyalara kaydeder.
* **Dinamik Bellek Yönetimi:** Kitap ve kategori dizileri `malloc` ve `realloc` ile dinamik olarak büyür. Program sonlanırken `free` ile bellek tamamen temizlenir.
* **Sözdizimi Kuralı:** Pointer yapılarında `(*pointer).variable` kullanımı tercih edilmiştir.
