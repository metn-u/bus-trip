# CMPE 1101 - Otobüs Biletleme Sistemi Projesi

Bu proje, C programlama dili kullanılarak geliştirilmiş, dosya tabanlı bir otobüs bilet satış ve yönetim sistemidir.
````bash
gcc main.c -o program
./program
````
## 📌 Proje Durumu
* **Tamamlananlar:** Sefer oluşturma (Create), Sefer listeleme (Read).
* **Eksikler:** Bilet satışı, Güncelleme, Silme, Sorgulama ve Raporlama.

---

##  Yapılacaklar Listesi (To-Do List)

### 1. Temel Fonksiyonların Eklenmesi (Gereksinimler)
- [ ] **Sefer Sorgulama (Trip Inquiry):** - Kullanıcıdan ID isteyip, sadece o seferin detaylarını ekrana basan fonksiyonun yazılması.
- [ ] **Bilet Satışı (Ticket Sell):** - Sefer ID'si ile kontrol (Koltuk var mı?).
  - Yolcu bilgilerini alma.
  - `tickets.dat` dosyasına bilet kaydetme.
  - **Önemli:** `trips.dat` içindeki koltuk sayısını güncelleme (azaltma).
- [ ] **Makbuz Oluşturma (Receipt):** - Satış sonrası `BiletID_Makbuz.txt` formatında çıktı veren fonksiyonun yazılması.
- [ ] **Sefer Silme (Delete Trip):** - ID'si girilen seferin dosyadan silinmesi (Geçici dosya yöntemi ile).
- [ ] **Sefer Güncelleme (Update Trip):** - Var olan bir seferin bilgilerinin (Saat, Sürücü vb.) değiştirilmesi.
- [ ] **Bilet İptali (Ticket Cancel):** - Satılan biletin silinmesi ve ilgili seferin koltuk sayısının 1 artırılması.

### 2. Kod İyileştirmeleri ve Hata Düzeltmeleri (Refactoring)
- [ ] **Menü Yapısı:** - `menu()` fonksiyonunun kendi kendini çağırması (recursive) engellenecek. Yerine `while(1)` döngüsü kurulacak.
- [ ] **Benzersiz ID Kontrolü:** - `CreateTrip` fonksiyonunda, girilen ID'nin dosyada zaten var olup olmadığını kontrol eden `isIdUnique` fonksiyonu eklenecek.
- [ ] **Veri Okuma Güvenliği:** - `ListTrips` fonksiyonunda `sscanf` dönüş değeri kontrol edilecek (Hatalı satırlarda "123" gibi rastgele sayıların çıkması engellenecek).
- [ ] **Dosya Modu Güncellemesi:**
  - Yazma işlemleri için `ab` (append binary) yerine `a` (append text) modu kullanılarak format tutarlılığı sağlanacak.

### 3. Teslimat Hazırlığı
- [ ] Kodun okunabilirliği için fonksiyonlara yorum satırları eklenmesi.
- [ ] Proje Raporunun (PDF) hazırlanması.
- [ ] `CMPE1101_Project_OgrenciNo_Ad_Soyad.zip` formatında paketleme.

---

##  Nasıl Çalıştırılır?
1. Kodu Dev-C++ veya uyumlu bir C derleyicisi ile derleyin.
2. Oluşan `.exe` dosyasını çalıştırın.
3. Menüden işlem seçin. Veriler `trips.dat` dosyasında saklanacaktır.
