# CMPE 1101 - Otobüs Biletleme Sistemi Projesi

Bu proje, C programlama dili kullanılarak geliştirilmiş, dosya tabanlı bir otobüs bilet satış ve sefer yönetim programıdır.

Derleyip çalıştırmak için:
````bash
gcc main.c -o program
./program
````


## Özellikler

<ol>
  <li>Menü yapısı</li>
    <ol>
      <li>Sefer Yönetim Menüsü</li>
      <li>Bilet Menüsü</li>
    </ol>
  <li>Sefer Yönetimi</li>
    <ol>
      <li>Sefer Ekleme</li>
      <li>Seferleri Listeleme</li>
      <li>Sefer Detayı Sorgulama</li>
      <li>Sefer Silme</li>
      <li>Sefer Detaylarını Silme</li>
    </ol>
  <li>Bilet Yönetimi</li>
    <ol>
      <li>Bilet Alma</li>
      <li>Bilet İptal etme</li>
      <li>Biletleri Listeleme</li>
      <li>Makbuz Oluşturma</li>
    </ol>
</ol>


##  Nasıl Çalışıyor?

1. Kodu Dev-C++ veya uyumlu bir C derleyicisi ile derleyin.
2. Oluşan `.exe` dosyasını çalıştırın.
3. Sefer verileri `trips.txt` dosyasında saklanacaktır.
4. Bilet verileri `tickets.txt` dosyasında saklanacaktır.
5. Bilet alındığında txt biçiminde formatlı bir makbuz dosyası oluşturulur.

## Dosya yapısı

main.c → programın ana dosyası

`trips.txt` → trip bilgileri

`tickets.txt` → ticket kayıtları

`receipt_*.txt` → bilet fişleri

**“Program çalıştıkça otomatik oluşur” **


#### Eklenebilecek Özellikler 

- Girdi kontrollerinin özelleştirilip geliştirilmiş hali
- Rastgele ID Üretimi
- Sefer detaylarını düzenlerken istenen veriyi tekli değiştirme 

