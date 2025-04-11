# Kompresi Gambar dengan Metode Quadtree
> Tugas Kecil 2 IF 2211 Strategi Algoritma

> Disusun oleh Muhammad Ghifary Komara Putra - 13523066

![tc7-emu-gif](https://github.com/user-attachments/assets/197c4ec1-608a-47ab-b1c9-201f640b14c8)

### Deskripsi Singkat
Selamat datang di program Kompresi Gambar dengan Quadtree!
Kompresi gambar dengan metode quadtree merupakan suatu metode kompresi gambar bersifat lossy yang memanfaatkan struktur data quadtree dan algoritma divide and conquer dalam proses kompresi. Dalam konteks ini, suatu node quadtree akan menyatakan blok gambar tertentu dan keempat child dari node tersebut akan menyatakan blok gambar yang merupakan segmen hasil pembagian blok gambar parent-nya menjadi empat bagian sama besar. Pembagian dilakukan hingga mencapai ambang batas tertentu, baik ambang batas secara matematis maupun berdasarkan ukuran blok minimum. Penulis mengembangkan alternatif solusi program kompresi gambar dengan metode quadtree berbasis CLI dengan bahasa C++. Pada program ini, pengguna dapat memasukkan gambar yang hendak dikompresi, memilih metode kompresi yang tersedia: variansi, Mean Absolute Deviation (MAD), Max Pixel Difference, entropi, dan Structural Similarity Index (SSIM), kemudian melakukan kompresi berdasarkan ambang batas tertentu. Selain itu, pengguna pun dapat melakukan kompresi berdasarkan target persentase kompresi yang diinginkan serta dapat melihat proses kompresi dalam bentuk file GIF. Kompresi berdasarkan target persentase diimplementasikan dengan algoritma binary search terhadap threshold sedangkan kompresi GIF dilakukan dengan menelusuri setiap node pada quadtree hasil kompresi.

### Requirement, Instalasi, dan Panduan Penggunaan
1. Program dikembangkan dengan GCC versi 6.3.0. Silakan lakukan instalasi versi tersebut atau versi C++ setelahnya yang kompatibel
2. Clone repositori pada lampiran ke dalam perangkat Anda
3. Pada CLI, pastikan anda berada pada root directory
4. Jalankan perintah berikut: ```./bin/main```
5. Program siap dijalankan

   
Jika hendak melakukan kompilasi kembali terhadap file .exe, silakan ikuti langkah berikut:
1. Buka CLI pada root directory
2. Jalankan perintah berikut untuk melakukan kompilasi
```g++ src/error_measurement/variance.cpp src/quadtree/quadtree.cpp src/main.cpp src/error_measurement/entropy.cpp src/error_measurement/mad.cpp src/error_measurement/mpd.cpp src/bonus/gif_generator.cpp src/bonus/ssim.cpp src/bonus/compression_target.cpp src/utils/input_data.cpp -o bin/main```

Program menerima masukan berikut:
1. Absolute path ke image input (png, jpg, jpeg)
2. Kode angka metode perhitungan error (1-5)
3. Threshold
4. Minimum block size
5. Target persentase (masukkan 0 jika tidak ingin memberikan target kompresi)
6. Absolute path ke image output
7. Absolute path ke GIF proses kompresi

### Credits
Program menggunakan library stb_image.h dan stb_image_write.h untuk pembacaan dan penulisan file image. Library dapat diakses melalui tautan berikut: ```https://github.com/nothings/stb```
Program juga menggunakan library gif.h karya Charlie Tangora untuk menggabungkan file gambar menjadi suatu file GIF. Library dapat diakses melalui tautan berikut: ```https://github.com/charlietangora/gif-h/blob/master/gif.h```
