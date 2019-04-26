# SoalShift_modul4_B06

## Oleh Kelompok B06 :
1. Yasinta Yusniawati   05111740000054
2. Bima Satria Ramadhan 05111740000081

## SOAL

## No 1
Semua nama file dan folder harus terenkripsi. Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:
```
qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0
```
Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
**“INI_FOLDER/halo”** saat belum di-mount maka akan bernama **“n,nsbZ]wio/QBE#”**, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi **“INI_FOLDER/halo”** .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

### Jawaban :
+ Untuk membuat enkripsi Caesar chipher buatlah terlebih dahulu fungsi enkripsi dan dekripsinya
+ Enkripsi jika dinotasikan dalam rumus matematika adalah sebagai berikut :
```
E_{n}(x)=(x+n)\mod {26}.
```
+ Dekripsi jika dinotasikan dalam rumus matematika adalah sebagai berikut :
```
D_{n}(x)=(x-n)\mod {26}.
```
+ Implementasikan Rumus yang didapat ke dalam kodingan
+ Jangan lupa tambahkan fungsi dekripsi di readdir untuk mendekripsi nama file sesuai perintah yang ada di soal.

## No 2
Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos” Urutan operasi dari kebutuhan ini adalah:
<ol type = "a">
<li> Tepat saat sebelum file system di-mount
+ Secara otomatis folder “Videos” terbuat di root directory file system
+ Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”
Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse
+ Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
+ Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
+ Jangan tampilkan file pecahan di direktori manapun
<li> Tepat saat file system akan di-unmount
+ Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
+ Hapus folder “Videos” 
</ol>

### Jawaban :

## No 3
Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:

+ Owner Name 	: ‘chipset’ atau ‘ic_controller’
+ Group Name	: ‘rusak’
+ Tidak dapat dibaca

Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

### Jawaban :

## No 4
Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah **“.iz1”**. File berekstensi **“.iz1”** tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

### Jawaban :
pada xmp_mkdir lakukan mengecek pada file youtuber kemudian membuat permission foldernya 750
```c
if(strstr(fpath, "/@ZA>AXio/") != NULL)
	{
		res = mkdir(fpath, 0750);	
	}
```
pada xmp_create lakukan mengecek pada file youtuber kemudian membuat permission file 750
```c
if(strstr(fpath, "/@ZA>AXio/") != NULL)
	{
		res = creat(fpath, 0640);
} 
```
menambah ekstensi .iz1
```c
if(strstr(fpath, "/@ZA>AXio/") != NULL)
	{
		strcpy(sementara, fpath);
		strcat(sementara, "`[S%");
		rename(fpath, sementara);
}
```
pada xmp_chmod memunculkan error bertuliskan "File ekstensi iz1 tidak boleh diubah permissionnya."
```c
char *argv[] = {"zenity", "--warning", "--text='File ekstensi iz1 tidak boleh diubah permissionnya.'", NULL};
execv("/usr/bin/zenity", argv);
```

## No 5
Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss

### Jawaban :

