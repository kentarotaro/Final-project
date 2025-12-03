#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// ===================================
// DEKLARASI STRUCT (harus di awal)
// ===================================
struct data {
    int kode;
    string nama;
    string kategori;
    int harga;
    int stock;
};

const int MAX_DATA = 100;

// ===================================
// DATA AWAL
// ===================================
data makanan[MAX_DATA] = {
    {201, "Nasi Goreng", "makanan", 25000, 30},
    {202, "Es Teh Manis", "minuman", 5000, 50},
    {203, "Keripik Singkong", "cemilan", 15000, 40},
    {204, "Mie Ayam", "makanan", 20000, 25},
    {205, "Kopi Susu", "minuman", 12000, 35}
};

int jumlahData = 5; // Variabel untuk menyimpan jumlah data aktif


// ===================================
// Fungsi Utility untuk Clear Screen
// ===================================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ===================================
// Fungsi untuk menampilkan header tabel
// ===================================
void tampilkanHeaderTabel() {
    cout << "\n";
    cout << "======================================================================================\n";
    cout << "| No | Kode  | Nama Makanan        | Kategori     | Harga        | Stock |\n";
    cout << "======================================================================================\n";
}

// ===================================
// Fungsi untuk menampilkan satu baris data
// ===================================
void tampilkanBarisTabel(const data &item, int nomor) {
    cout << "| " << setw(2) << right << nomor << " | ";
    cout << setw(5) << left << item.kode << " | ";
    cout << setw(19) << left << item.nama << " | ";
    cout << setw(12) << left << item.kategori << " | ";
    cout << "Rp " << setw(9) << right << item.harga << " | ";
    cout << setw(5) << right << item.stock << " |\n";
}

// ===================================
// Fungsi untuk menampilkan footer tabel
// ===================================
void tampilkanFooterTabel() {
    cout << "======================================================================================\n";
}

// ===================================
// Fungsi CREATE (Tambah Data)
// ===================================
void createMakanan(data makanan[], int *jumlahData, int maxSize) {
    clearScreen();
    cout << "\n=============== TAMBAH DATA BARU ===============\n\n";
    
    if (*jumlahData >= maxSize) {
        cout << "[!] Database penuh! Maksimal " << maxSize << " data.\n\n";
        return;
    }
    
    int jumlahTambah;
    cout << "Jumlah data yang ingin ditambahkan: ";
    cin >> jumlahTambah;
    
    if (*jumlahData + jumlahTambah > maxSize) {
        cout << "\n[!] Tidak cukup ruang! Hanya bisa menambahkan " 
             << (maxSize - *jumlahData) << " data lagi.\n\n";
        return;
    }
    
    cin.ignore(); // Bersihkan buffer
    
    for (int i = 0; i < jumlahTambah; i++) {
        int index = *jumlahData + i;
        
        cout << "\n--- Data ke-" << (i + 1) << " ---\n";
        
        // Input dan validasi kode unik
        bool kodeValid = false;
        while (!kodeValid) {
            cout << "Masukkan Kode: ";
            cin >> makanan[index].kode;
            
            // Cek apakah kode sudah ada
            kodeValid = true;
            for (int j = 0; j < *jumlahData + i; j++) {
                if (makanan[j].kode == makanan[index].kode) {
                    cout << "[?] Kode sudah digunakan! Masukkan kode lain.\n";
                    kodeValid = false;
                    break;
                }
            }
        }
        
        cin.ignore(); // Bersihkan buffer setelah input integer
        
        cout << "Masukkan Nama: ";
        getline(cin, makanan[index].nama);
        
        cout << "Masukkan Kategori: ";
        getline(cin, makanan[index].kategori);
        
        cout << "Masukkan Harga: Rp ";
        cin >> makanan[index].harga;
        
        cout << "Masukkan Stock: ";
        cin >> makanan[index].stock;
        
        cin.ignore(); // Bersihkan buffer untuk iterasi berikutnya
        
        cout << "[?] Data ke-" << (i + 1) << " berhasil ditambahkan!\n";
    }
    
    *jumlahData += jumlahTambah;
    
    cout << "\n[?] Total " << jumlahTambah << " data berhasil ditambahkan!\n";
    cout << "Total data sekarang: " << *jumlahData << " item\n\n";
}

// ===================================
// Fungsi MERGE SORT - Combine (Helper)
// ===================================
void combineMakanan(data makanan[], int low, int mid, int high) {
    int batasBawah = mid - low + 1;
    int batasAtas = high - mid;
    
    // Alokasi array sementara
    data* kiri = new data[batasBawah];
    data* kanan = new data[batasAtas];
    
    // Copy data ke array kiri
    for (int i = 0; i < batasBawah; i++) {
        kiri[i] = makanan[low + i];
    }
    
    // Copy data ke array kanan
    for (int j = 0; j < batasAtas; j++) {
        kanan[j] = makanan[mid + 1 + j];
    }
    
    // Merge kembali ke array asli
    int i = 0, j = 0, k = low;
    
    while (i < batasBawah && j < batasAtas) {
        if (kiri[i].harga <= kanan[j].harga) {
            makanan[k] = kiri[i];
            i++;
        } else {
            makanan[k] = kanan[j];
            j++;
        }
        k++;
    }
    
    // Copy sisa elemen kiri (jika ada)
    while (i < batasBawah) {
        makanan[k] = kiri[i];
        i++;
        k++;
    }
    
    // Copy sisa elemen kanan (jika ada)
    while (j < batasAtas) {
        makanan[k] = kanan[j];
        j++;
        k++;
    }
    
    // Bebaskan memori
    delete[] kiri;
    delete[] kanan;
}

// ===================================
// Fungsi MERGE SORT - Recursive
// ===================================
void mergeSortMakanan(data makanan[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2; // Hindari overflow
        
        // Sort bagian kiri
        mergeSortMakanan(makanan, low, mid);
        
        // Sort bagian kanan
        mergeSortMakanan(makanan, mid + 1, high);
        
        // Gabungkan hasil
        combineMakanan(makanan, low, mid, high);
    }
}

// ===================================
// Fungsi SORT dengan Pilihan
// ===================================
void sortMakanan(data makanan[], int jumlahData) {
    clearScreen();
    cout << "\n=============== URUTKAN DATA ===============\n\n";
    
    if (jumlahData == 0) {
        cout << "[!] Tidak ada data untuk diurutkan!\n\n";
        return;
    }
    
    int pilihan;
    cout << "Urutkan berdasarkan:\n";
    cout << "1. Harga (Termurah - Termahal)\n";
    cout << "2. Harga (Termahal - Termurah)\n";
    cout << "3. Kode (Kecil - Besar)\n";
    cout << "4. Nama (A - Z)\n";
    cout << "0. Batal\n";
    cout << "-------------------------------------\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    
    if (pilihan == 0) {
        cout << "\n[!] Pengurutan dibatalkan.\n\n";
        return;
    }
    
    // Backup data untuk bisa dikembalikan jika perlu
    cout << "\n[...] Mengurutkan data...\n";
    
    // Lakukan sorting berdasarkan pilihan
    // Untuk pilihan 1: sort by harga ascending (sudah ada di merge sort)
    if (pilihan == 1) {
        mergeSortMakanan(makanan, 0, jumlahData - 1);
        cout << "[?] Data berhasil diurutkan berdasarkan harga (termurah - termahal)!\n\n";
    } 
    else if (pilihan == 2) {
        mergeSortMakanan(makanan, 0, jumlahData - 1);
        // Reverse array untuk descending
        for (int i = 0; i < jumlahData / 2; i++) {
            data temp = makanan[i];
            makanan[i] = makanan[jumlahData - 1 - i];
            makanan[jumlahData - 1 - i] = temp;
        }
        cout << "[?] Data berhasil diurutkan berdasarkan harga (termahal - termurah)!\n\n";
    }
    else if (pilihan == 3) {
        // Bubble sort sederhana untuk kode (karena integer, tidak perlu merge sort)
        for (int i = 0; i < jumlahData - 1; i++) {
            for (int j = 0; j < jumlahData - i - 1; j++) {
                if (makanan[j].kode > makanan[j + 1].kode) {
                    data temp = makanan[j];
                    makanan[j] = makanan[j + 1];
                    makanan[j + 1] = temp;
                }
            }
        }
        cout << "[?] Data berhasil diurutkan berdasarkan kode!\n\n";
    }
    else if (pilihan == 4) {
        // Bubble sort untuk nama (string)
        for (int i = 0; i < jumlahData - 1; i++) {
            for (int j = 0; j < jumlahData - i - 1; j++) {
                if (makanan[j].nama > makanan[j + 1].nama) {
                    data temp = makanan[j];
                    makanan[j] = makanan[j + 1];
                    makanan[j + 1] = temp;
                }
            }
        }
        cout << "[?] Data berhasil diurutkan berdasarkan nama (A - Z)!\n\n";
    }
    else {
        cout << "\n[?] Pilihan tidak valid!\n\n";
        return;
    }
    
    // Tampilkan hasil sorting
    tampilkanHeaderTabel();
    for (int i = 0; i < jumlahData; i++) {
        tampilkanBarisTabel(makanan[i], i + 1);
    }
    tampilkanFooterTabel();
}

// ===================================
// Fungsi READ
// ===================================
void read(const data makanan[], int jumlahBarang) {
    clearScreen();
    cout << "\n=============== DAFTAR MAKANAN & MINUMAN ===============\n";
    
    if (jumlahBarang == 0) {
        cout << "\n[!] Tidak ada data tersedia!\n\n";
        return;
    }
    
    tampilkanHeaderTabel();
    
    for (int i = 0; i < jumlahBarang; i++) {
        tampilkanBarisTabel(makanan[i], i + 1);
    }
    
    tampilkanFooterTabel();
    cout << "\nTotal data: " << jumlahBarang << " item\n";
}

// ===================================
// Fungsi SEARCH
// ===================================
void searchKode(const data makanan[], int jumlahBarang) {
    clearScreen();
    cout << "\n=============== PENCARIAN DATA ===============\n\n";
    
    int kodeCari;
    cout << "Masukkan kode yang dicari: ";
    cin >> kodeCari;
    
    bool ditemukan = false;
    
    for (int i = 0; i < jumlahBarang; i++) {
        if (makanan[i].kode == kodeCari) {
            cout << "\n[?] Data ditemukan!\n";
            tampilkanHeaderTabel();
            tampilkanBarisTabel(makanan[i], 1);
            tampilkanFooterTabel();
            
            cout << "\n--- Detail Lengkap ---\n";
            cout << "Kode     : " << makanan[i].kode << endl;
            cout << "Nama     : " << makanan[i].nama << endl;
            cout << "Kategori : " << makanan[i].kategori << endl;
            cout << "Harga    : Rp " << makanan[i].harga << endl;
            cout << "Stock    : " << makanan[i].stock << " unit\n";
            
            ditemukan = true;
            break;
        }
    }
    
    if (!ditemukan) {
        cout << "\n[?] Kode " << kodeCari << " tidak ditemukan!\n";
    }
    
    cout << "\n";
}

// ===================================
// Fungsi UPDATE
// ===================================
void updateMakanan(data makanan[], int jumlahData) {
    clearScreen();
    cout << "\n=============== UPDATE DATA ===============\n\n";
    
    if (jumlahData == 0) {
        cout << "[!] Tidak ada data untuk diupdate!\n\n";
        return;
    }
    
    int index = -1;
    int kodeInput;
    
    // Loop untuk input kode sampai valid atau user membatalkan
    do {
        // Tampilkan data yang ada
        cout << "Data yang tersedia:\n";
        tampilkanHeaderTabel();
        for (int i = 0; i < jumlahData; i++) {
            tampilkanBarisTabel(makanan[i], i + 1);
        }
        tampilkanFooterTabel();
        
        cout << "\nMasukkan kode makanan/minuman yang ingin diupdate (0 untuk batal): ";
        cin >> kodeInput;
        
        // Cek jika user ingin membatalkan
        if (kodeInput == 0) {
            cout << "\n[!] Update dibatalkan.\n\n";
            return;
        }
        
        // 1. Cari indeks data yang akan diupdate
        index = -1;
        for (int i = 0; i < jumlahData; i++) {
            if (makanan[i].kode == kodeInput) {
                index = i;
                break;
            }
        }
        
        if (index == -1) {
            cout << "\n[?] Kode " << kodeInput << " tidak ditemukan! Silakan coba lagi.\n\n";
            // Loop akan mengulang
        }
        
    } while (index == -1); // Ulangi selama kode belum ditemukan
    
    // 2. Tampilkan data saat ini
    cout << "\n--- Data Saat Ini ---\n";
    tampilkanHeaderTabel();
    tampilkanBarisTabel(makanan[index], 1);
    tampilkanFooterTabel();
    
    // 3. Menu pilihan field yang ingin diupdate
    int pilihanUpdate;
    cout << "\nPilih data yang ingin diupdate:\n";
    cout << "1. Nama\n";
    cout << "2. Kategori\n";
    cout << "3. Harga\n";
    cout << "4. Stock\n";
    cout << "5. Update Semua Data\n";
    cout << "0. Batal\n";
    cout << "-------------------------------------\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihanUpdate;
    
    cin.ignore(); // Membersihkan buffer input
    
    switch (pilihanUpdate) {
        case 1: {
            cout << "\nNama saat ini: " << makanan[index].nama << endl;
            cout << "Masukkan nama baru: ";
            getline(cin, makanan[index].nama);
            cout << "\n[?] Nama berhasil diupdate!\n";
            break;
        }
        
        case 2: {
            cout << "\nKategori saat ini: " << makanan[index].kategori << endl;
            cout << "Masukkan kategori baru: ";
            getline(cin, makanan[index].kategori);
            cout << "\n[?] Kategori berhasil diupdate!\n";
            break;
        }
        
        case 3: {
            cout << "\nHarga saat ini: Rp " << makanan[index].harga << endl;
            cout << "Masukkan harga baru: Rp ";
            cin >> makanan[index].harga;
            cout << "\n[?] Harga berhasil diupdate!\n";
            break;
        }
        
        case 4: {
            cout << "\nStock saat ini: " << makanan[index].stock << " unit" << endl;
            cout << "Masukkan stock baru: ";
            cin >> makanan[index].stock;
            cout << "\n[?] Stock berhasil diupdate!\n";
            break;
        }
        
        case 5: {
            cout << "\n--- Update Semua Data ---\n";
            cout << "Masukkan nama baru: ";
            getline(cin, makanan[index].nama);
            
            cout << "Masukkan kategori baru: ";
            getline(cin, makanan[index].kategori);
            
            cout << "Masukkan harga baru: Rp ";
            cin >> makanan[index].harga;
            
            cout << "Masukkan stock baru: ";
            cin >> makanan[index].stock;
            
            cout << "\n[?] Semua data berhasil diupdate!\n";
            break;
        }
        
        case 0: {
            cout << "\n[!] Update dibatalkan.\n\n";
            return;
        }
        
        default: {
            cout << "\n[?] Pilihan tidak valid!\n\n";
            return;
        }
    }
    
    // 4. Tampilkan data setelah diupdate
    cout << "\n--- Data Setelah Update ---\n";
    tampilkanHeaderTabel();
    tampilkanBarisTabel(makanan[index], 1);
    tampilkanFooterTabel();
    cout << "\n";
}

// ===================================
// Fungsi DELETE
// ===================================
void deleteMakanan(data makanan[], int *jumlahData) { 
    clearScreen();
    cout << "\n=============== HAPUS DATA ===============\n\n";
    
    if (*jumlahData == 0) {
        cout << "[!] Tidak ada data untuk dihapus!\n\n";
        return;
    }
    
    // Tampilkan data yang ada
    cout << "Data yang tersedia:\n";
    tampilkanHeaderTabel();
    for (int i = 0; i < *jumlahData; i++) {
        tampilkanBarisTabel(makanan[i], i + 1);
    }
    tampilkanFooterTabel();
    
    int kodeInput;
    cout << "\nMasukkan kode makanan/minuman yang ingin dihapus: ";
    cin >> kodeInput;
    
    int index = -1;
    
    // 1. Cari indeks data yang akan dihapus
    for (int i = 0; i < *jumlahData; i++) {
        if (makanan[i].kode == kodeInput) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "\n[?] Kode " << kodeInput << " tidak ditemukan!\n\n";
        return;
    }
    
    // Tampilkan data yang akan dihapus
    cout << "\nData yang akan dihapus:\n";
    tampilkanHeaderTabel();
    tampilkanBarisTabel(makanan[index], 1);
    tampilkanFooterTabel();
    
    // Konfirmasi penghapusan
    char konfirmasi;
    cout << "\nApakah Anda yakin ingin menghapus data ini? (y/n): ";
    cin >> konfirmasi;
    
    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "\n[!] Penghapusan dibatalkan.\n\n";
        return;
    }
    
    // 2. Geser elemen array ke kiri untuk menimpa data yang dihapus
    for (int i = index; i < *jumlahData - 1; i++) {
        makanan[i] = makanan[i + 1];
    }
    
    // 3. Kurangi jumlah data
    (*jumlahData)--;
    
    cout << "\n[?] Data dengan kode " << kodeInput << " berhasil dihapus!\n";
    cout << "Sisa data: " << *jumlahData << " item\n\n";
}

// ===================================
// Fungsi SAVE DATA ke File (Format Rapi)
// ===================================
void saveToFile(const data makanan[], int jumlahData) {
    clearScreen();
    cout << "\n=============== SIMPAN DATA KE FILE ===============\n\n";
    
    if (jumlahData == 0) {
        cout << "[!] Tidak ada data untuk disimpan!\n\n";
        return;
    }
    
    // Buka file untuk menulis (mode truncate - menimpa file lama)
    ofstream file("DataMenuMakanan.txt");
    
    // Cek apakah file berhasil dibuka
    if (!file.is_open()) {
        cout << "[?] Gagal membuka file DataMenuMakanan.txt!\n\n";
        return;
    }
    
    // Header file yang menarik
    file << "===============================================================================\n";
    file << "                       DATA MENU MAKANAN & MINUMAN                            \n";
    file << "===============================================================================\n";
    file << "Total Data: " << jumlahData << " item\n";
    file << "Tanggal Simpan: " << __DATE__ << " " << __TIME__ << "\n";
    file << "===============================================================================\n\n";
    
    // Tulis data dalam format yang rapi
    for (int i = 0; i < jumlahData; i++) {
        file << "--- Data #" << (i + 1) << " ---\n";
        file << "Kode     : " << makanan[i].kode << "\n";
        file << "Nama     : " << makanan[i].nama << "\n";
        file << "Kategori : " << makanan[i].kategori << "\n";
        file << "Harga    : Rp " << makanan[i].harga << "\n";
        file << "Stock    : " << makanan[i].stock << " unit\n";
        file << "-------------------------------------------------------------------------------\n";
    }
    
    // Footer file
    file << "\n===============================================================================\n";
    file << "                            END OF FILE                                       \n";
    file << "===============================================================================\n";
    
    file.close();
    
    cout << "[?] Data berhasil disimpan ke file DataMenuMakanan.txt!\n";
    cout << "Total data tersimpan: " << jumlahData << " item\n\n";
}

// ===================================
// Fungsi Helper untuk konversi string ke int (pengganti stoi)
// ===================================
int stringToInt(string str) {
    int result = 0;
    int i = 0;
    bool negative = false;
    
    // Handle tanda negatif
    if (str[0] == '-') {
        negative = true;
        i = 1;
    }
    
    // Konversi karakter ke integer
    for (; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    
    return negative ? -result : result;
}

// ===================================
// Fungsi Helper untuk ekstrak angka dari string
// ===================================
int extractNumber(string line, string keyword) {
    size_t pos = line.find(keyword);
    if (pos == string::npos) return 0;
    
    // Cari posisi setelah keyword
    pos = line.find(":", pos) + 1;
    
    // Skip spasi
    while (pos < line.length() && line[pos] == ' ') pos++;
    
    // Skip "Rp" jika ada
    if (line.substr(pos, 2) == "Rp") {
        pos += 2;
        while (pos < line.length() && line[pos] == ' ') pos++;
    }
    
    // Ekstrak angka
    string numStr = "";
    while (pos < line.length() && line[pos] >= '0' && line[pos] <= '9') {
        numStr += line[pos];
        pos++;
    }
    
    return stringToInt(numStr);
}

// ===================================
// Fungsi Helper untuk ekstrak teks setelah ":"
// ===================================
string extractText(string line) {
    size_t pos = line.find(":");
    if (pos == string::npos) return "";
    
    pos += 1;
    // Skip spasi
    while (pos < line.length() && line[pos] == ' ') pos++;
    
    return line.substr(pos);
}

// ===================================
// Fungsi LOAD DATA dari File (Format Rapi - C++ Lama)
// ===================================
void loadFromFile(data makanan[], int *jumlahData, int maxSize) {
    clearScreen();
    cout << "\n=============== MUAT DATA DARI FILE ===============\n\n";
    
    // Buka file untuk membaca
    ifstream file("DataMenuMakanan.txt");
    
    // Cek apakah file ada dan bisa dibuka
    if (!file.is_open()) {
        cout << "[!] File DataMenuMakanan.txt tidak ditemukan!\n";
        cout << "[!] Pastikan file ada di folder yang sama dengan program.\n\n";
        return;
    }
    
    string line;
    int berhasil = 0;
    
    // Skip header (5 baris pertama)
    for (int i = 0; i < 5; i++) {
        getline(file, line);
    }
    
    // Baca data
    while (berhasil < maxSize && getline(file, line)) {
        // Cek apakah ini adalah baris "--- Data #X ---"
        if (line.find("--- Data #") != string::npos) {
            
            // Baca Kode
            if (getline(file, line) && line.find("Kode") != string::npos) {
                makanan[berhasil].kode = extractNumber(line, "Kode");
            } else break;
            
            // Baca Nama
            if (getline(file, line) && line.find("Nama") != string::npos) {
                makanan[berhasil].nama = extractText(line);
            } else break;
            
            // Baca Kategori
            if (getline(file, line) && line.find("Kategori") != string::npos) {
                makanan[berhasil].kategori = extractText(line);
            } else break;
            
            // Baca Harga
            if (getline(file, line) && line.find("Harga") != string::npos) {
                makanan[berhasil].harga = extractNumber(line, "Harga");
            } else break;
            
            // Baca Stock
            if (getline(file, line) && line.find("Stock") != string::npos) {
                makanan[berhasil].stock = extractNumber(line, "Stock");
            } else break;
            
            berhasil++;
            
            // Skip garis pemisah
            getline(file, line);
        }
    }
    
    file.close();
    
    *jumlahData = berhasil;
    
    if (berhasil > 0) {
        cout << "[?] Data berhasil dimuat dari file DataMenuMakanan.txt!\n";
        cout << "Total data dimuat: " << berhasil << " item\n\n";
        
        // Tampilkan preview data yang dimuat
        cout << "Preview data:\n";
        tampilkanHeaderTabel();
        int preview = (berhasil < 5) ? berhasil : 5; // Tampilkan max 5 data
        for (int i = 0; i < preview; i++) {
            tampilkanBarisTabel(makanan[i], i + 1);
        }
        tampilkanFooterTabel();
        
        if (berhasil > 5) {
            cout << "... dan " << (berhasil - 5) << " data lainnya\n";
        }
    } else {
        cout << "[?] Gagal membaca data dari file!\n";
        cout << "[!] Periksa format file DataMenuMakanan.txt\n\n";
    }
}

// ===================================
// MAIN FUNCTION
// ===================================
int main() {
    int pilihan;

    do {
        cout << "\n=====================================\n";
        cout << "   SISTEM MANAJEMEN MENU MAKANAN     \n";
        cout << "=====================================\n";
        cout << "1. Tampilkan Semua Menu (READ)\n";
        cout << "2. Cari Menu Berdasarkan Kode (SEARCH)\n";
        cout << "3. Hapus Menu Berdasarkan Kode (DELETE)\n";
        cout << "4. Update Menu Berdasarkan Kode (UPDATE)\n";
        cout << "5. Tambah Data Baru (CREATE)\n";
        cout << "6. Urutkan Data (SORT)\n";
        cout << "7. Simpan Data ke File (SAVE)\n";        
        cout << "8. Muat Data dari File (LOAD)\n";        
        cout << "9. Keluar\n";                             
        cout << "-------------------------------------\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                read(makanan, jumlahData);
                break;
            
            case 2:
                searchKode(makanan, jumlahData);
                break;

            case 3:
                deleteMakanan(makanan, &jumlahData);
                break;

            case 4:
                updateMakanan(makanan, jumlahData);
                break;
            
            case 5:
                createMakanan(makanan, &jumlahData, MAX_DATA);
                break;
            
            case 6:
                sortMakanan(makanan, jumlahData);
                break;
            
            case 7:                                     
                saveToFile(makanan, jumlahData);
                break;
            
            case 8:                                     
                loadFromFile(makanan, &jumlahData, MAX_DATA);
                break;
                
            case 9:                                      
                clearScreen();
                cout << "\n=====================================\n";
                cout << "  Terima kasih telah menggunakan\n";
                cout << "  Sistem Manajemen Menu Makanan!\n";
                cout << "=====================================\n\n";
                break;

            default:
                cout << "\n[?] Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }

    } while (pilihan != 9);  

    return 0;
}
