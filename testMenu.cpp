#include <iostream>	// Import os
#include <string>	// Import string
#include <iomanip>	// Import iomanip untuk setw (weidth)
#include <fstream>	// Import fstream untuk push ke file txt
#include <ctime>  	// Import time
#include <cstdio>	
#include <limits>

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

struct Pendapatan {
    int totalHariIni;
    int totalBulanIni;
    string tanggalTerakhir;  // Format: DD-MM-YYYY
    string bulanTerakhir;    // Format: MM-YYYY
};

Pendapatan pendapatan = {0, 0, "", ""};

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
    bool inputValid = false;
    
    // Validasi input jumlah data
    while (!inputValid) {
        cout << "Jumlah data yang ingin ditambahkan (0 untuk batal): ";
        
        if (cin >> jumlahTambah) {
            if (jumlahTambah == 0) {
                cout << "\n[!] Penambahan data dibatalkan.\n\n";
                return;
            }
            
            if (jumlahTambah > 0) {
                if (*jumlahData + jumlahTambah > maxSize) {
                    cout << "\n[!] Tidak cukup ruang! Hanya bisa menambahkan " 
                         << (maxSize - *jumlahData) << " data lagi.\n\n";
                } else {
                    inputValid = true;
                }
            } else {
                cout << "[?] Jumlah harus lebih dari 0!\n\n";
            }
        } else {
            cout << "[?] Input tidak valid! Harap masukkan angka.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    cin.ignore(); // Bersihkan buffer
    
    for (int i = 0; i < jumlahTambah; i++) {
        int index = *jumlahData + i;
        
        cout << "\n--- Data ke-" << (i + 1) << " ---\n";
        
        // Input dan validasi kode unik
        bool kodeValid = false;
        while (!kodeValid) {
            cout << "Masukkan Kode: ";
            
            if (cin >> makanan[index].kode) {
                // Cek apakah kode sudah ada
                kodeValid = true;
                for (int j = 0; j < *jumlahData + i; j++) {
                    if (makanan[j].kode == makanan[index].kode) {
                        cout << "[?] Kode sudah digunakan! Masukkan kode lain.\n";
                        kodeValid = false;
                        break;
                    }
                }
            } else {
                cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        cin.ignore(); // Bersihkan buffer setelah input integer
        
        // Input Nama
        bool namaValid = false;
        while (!namaValid) {
            cout << "Masukkan Nama: ";
            getline(cin, makanan[index].nama);
            
            if (makanan[index].nama.length() > 0) {
                namaValid = true;
            } else {
                cout << "[?] Nama tidak boleh kosong!\n";
            }
        }
        
        // Input Kategori
        bool kategoriValid = false;
        while (!kategoriValid) {
            cout << "Masukkan Kategori: ";
            getline(cin, makanan[index].kategori);
            
            if (makanan[index].kategori.length() > 0) {
                kategoriValid = true;
            } else {
                cout << "[?] Kategori tidak boleh kosong!\n";
            }
        }
        
        // Input Harga
        bool hargaValid = false;
        while (!hargaValid) {
            cout << "Masukkan Harga: Rp ";
            
            if (cin >> makanan[index].harga) {
                if (makanan[index].harga >= 0) {
                    hargaValid = true;
                } else {
                    cout << "[?] Harga tidak boleh negatif!\n";
                }
            } else {
                cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        // Input Stock
        bool stockValid = false;
        while (!stockValid) {
            cout << "Masukkan Stock: ";
            
            if (cin >> makanan[index].stock) {
                if (makanan[index].stock >= 0) {
                    stockValid = true;
                } else {
                    cout << "[?] Stock tidak boleh negatif!\n";
                }
            } else {
                cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
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
    bool pilihanValid = false;
    
    // Validasi input pilihan
    while (!pilihanValid) {
        cout << "Urutkan berdasarkan:\n";
        cout << "1. Harga (Termurah - Termahal)\n";
        cout << "2. Harga (Termahal - Termurah)\n";
        cout << "3. Kode (Kecil - Besar)\n";
        cout << "4. Nama (A - Z)\n";
        cout << "0. Batal\n";
        cout << "-------------------------------------\n";
        cout << "Pilihan: ";
        
        if (cin >> pilihan) {
            if (pilihan >= 0 && pilihan <= 4) {
                pilihanValid = true;
            } else {
                cout << "\n[?] Pilihan tidak valid! Pilih 0-4.\n\n";
            }
        } else {
            cout << "\n[?] Input tidak valid! Harap masukkan angka.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    if (pilihan == 0) {
        cout << "\n[!] Pengurutan dibatalkan.\n\n";
        return;
    }
    
    // Tampilkan loading
    cout << "\n[...] Mengurutkan data...\n";
    
    // Lakukan sorting berdasarkan pilihan
    if (pilihan == 1) {
        // Sort by harga ascending (Merge Sort)
        mergeSortMakanan(makanan, 0, jumlahData - 1);
        cout << "[?] Data berhasil diurutkan berdasarkan harga (termurah - termahal)!\n\n";
    } 
    else if (pilihan == 2) {
        // Sort by harga descending
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
        // Bubble sort untuk kode (integer)
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
    
    if (jumlahBarang == 0) {
        cout << "[!] Tidak ada data untuk dicari!\n\n";
        return;
    }
    
    int pilihan;
    bool pilihanValid = false;
    
    // Menu pilihan metode pencarian
    while (!pilihanValid) {
        cout << "Pilih metode pencarian:\n";
        cout << "1. Cari berdasarkan Kode\n";
        cout << "2. Cari berdasarkan Nama\n";
        cout << "3. Cari berdasarkan Kategori\n";
        cout << "0. Batal\n";
        cout << "-------------------------------------\n";
        cout << "Masukkan pilihan: ";
        
        if (cin >> pilihan) {
            if (pilihan >= 0 && pilihan <= 3) {
                pilihanValid = true;
            } else {
                cout << "\n[?] Pilihan tidak valid! Pilih 0-3.\n\n";
            }
        } else {
            cout << "\n[?] Input tidak valid! Harap masukkan angka.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    if (pilihan == 0) {
        cout << "\n[!] Pencarian dibatalkan.\n\n";
        return;
    }
    
    cin.ignore(); // Bersihkan buffer
    
    bool ditemukan = false;
    int jumlahDitemukan = 0;
    
    if (pilihan == 1) {
        // Pencarian berdasarkan Kode
        int kodeCari;
        bool inputValid = false;
        
        while (!inputValid) {
            cout << "\nMasukkan kode yang dicari (0 untuk batal): ";
            
            if (cin >> kodeCari) {
                inputValid = true;
                
                if (kodeCari == 0) {
                    cout << "\n[!] Pencarian dibatalkan.\n\n";
                    return;
                }
            } else {
                cout << "\n[?] Input tidak valid! Harap masukkan angka.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        for (int i = 0; i < jumlahBarang; i++) {
            if (makanan[i].kode == kodeCari) {
                if (!ditemukan) {
                    cout << "\n[?] Data ditemukan!\n";
                    tampilkanHeaderTabel();
                }
                tampilkanBarisTabel(makanan[i], jumlahDitemukan + 1);
                jumlahDitemukan++;
                ditemukan = true;
            }
        }
        
        if (ditemukan) {
            tampilkanFooterTabel();
            
            // Tampilkan detail lengkap (untuk pencarian kode, pasti hanya 1 hasil)
            for (int i = 0; i < jumlahBarang; i++) {
                if (makanan[i].kode == kodeCari) {
                    cout << "\n--- Detail Lengkap ---\n";
                    cout << "Kode     : " << makanan[i].kode << endl;
                    cout << "Nama     : " << makanan[i].nama << endl;
                    cout << "Kategori : " << makanan[i].kategori << endl;
                    cout << "Harga    : Rp " << makanan[i].harga << endl;
                    cout << "Stock    : " << makanan[i].stock << " unit\n";
                    break;
                }
            }
        }
        
    } else if (pilihan == 2) {
        // Pencarian berdasarkan Nama
        string namaCari;
        cout << "\nMasukkan nama yang dicari: ";
        getline(cin, namaCari);
        
        // Konversi ke lowercase untuk pencarian case-insensitive
        for (int i = 0; i < jumlahBarang; i++) {
            string namaLower = makanan[i].nama;
            string cariLower = namaCari;
            
            // Konversi ke lowercase
            for (int j = 0; j < namaLower.length(); j++) {
                namaLower[j] = tolower(namaLower[j]);
            }
            for (int j = 0; j < cariLower.length(); j++) {
                cariLower[j] = tolower(cariLower[j]);
            }
            
            // Cek apakah nama mengandung kata kunci
            if (namaLower.find(cariLower) != string::npos) {
                if (!ditemukan) {
                    cout << "\n[?] Data ditemukan!\n";
                    tampilkanHeaderTabel();
                }
                tampilkanBarisTabel(makanan[i], jumlahDitemukan + 1);
                jumlahDitemukan++;
                ditemukan = true;
            }
        }
        
        if (ditemukan) {
            tampilkanFooterTabel();
            cout << "\nTotal ditemukan: " << jumlahDitemukan << " item\n";
        }
        
    } else if (pilihan == 3) {
        // Pencarian berdasarkan Kategori
        string kategoriCari;
        cout << "\nMasukkan kategori yang dicari: ";
        getline(cin, kategoriCari);
        
        // Konversi ke lowercase untuk pencarian case-insensitive
        for (int i = 0; i < jumlahBarang; i++) {
            string kategoriLower = makanan[i].kategori;
            string cariLower = kategoriCari;
            
            // Konversi ke lowercase
            for (int j = 0; j < kategoriLower.length(); j++) {
                kategoriLower[j] = tolower(kategoriLower[j]);
            }
            for (int j = 0; j < cariLower.length(); j++) {
                cariLower[j] = tolower(cariLower[j]);
            }
            
            // Cek apakah kategori mengandung kata kunci
            if (kategoriLower.find(cariLower) != string::npos) {
                if (!ditemukan) {
                    cout << "\n[?] Data ditemukan!\n";
                    tampilkanHeaderTabel();
                }
                tampilkanBarisTabel(makanan[i], jumlahDitemukan + 1);
                jumlahDitemukan++;
                ditemukan = true;
            }
        }
        
        if (ditemukan) {
            tampilkanFooterTabel();
            cout << "\nTotal ditemukan: " << jumlahDitemukan << " item\n";
        }
    }
    
    if (!ditemukan) {
        cout << "\n[?] Data tidak ditemukan!\n";
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
    bool inputValid = false;
    
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
        
        // Validasi input kode
        if (cin >> kodeInput) {
            inputValid = true;
            
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
                inputValid = false;
            }
        } else {
            // Jika input bukan angka
            cout << "\n[?] Input tidak valid! Harap masukkan angka.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
            inputValid = false;
        }
        
    } while (!inputValid); // Ulangi selama input tidak valid
    
    // 2. Tampilkan data saat ini
    cout << "\n--- Data Saat Ini ---\n";
    tampilkanHeaderTabel();
    tampilkanBarisTabel(makanan[index], 1);
    tampilkanFooterTabel();
    
    // 3. Menu pilihan field yang ingin diupdate
    int pilihanUpdate;
    bool pilihanValid = false;
    
    while (!pilihanValid) {
        cout << "\nPilih data yang ingin diupdate:\n";
        cout << "1. Nama\n";
        cout << "2. Kategori\n";
        cout << "3. Harga\n";
        cout << "4. Stock\n";
        cout << "5. Update Semua Data\n";
        cout << "0. Batal\n";
        cout << "-------------------------------------\n";
        cout << "Masukkan pilihan: ";
        
        if (cin >> pilihanUpdate) {
            if (pilihanUpdate >= 0 && pilihanUpdate <= 5) {
                pilihanValid = true;
            } else {
                cout << "\n[?] Pilihan tidak valid! Pilih 0-5.\n";
            }
        } else {
            cout << "\n[?] Input tidak valid! Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
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
            bool hargaValid = false;
            while (!hargaValid) {
                cout << "\nHarga saat ini: Rp " << makanan[index].harga << endl;
                cout << "Masukkan harga baru: Rp ";
                
                if (cin >> makanan[index].harga) {
                    if (makanan[index].harga >= 0) {
                        hargaValid = true;
                        cout << "\n[?] Harga berhasil diupdate!\n";
                    } else {
                        cout << "[?] Harga tidak boleh negatif!\n";
                    }
                } else {
                    cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            break;
        }
        
        case 4: {
            bool stockValid = false;
            while (!stockValid) {
                cout << "\nStock saat ini: " << makanan[index].stock << " unit" << endl;
                cout << "Masukkan stock baru: ";
                
                if (cin >> makanan[index].stock) {
                    if (makanan[index].stock >= 0) {
                        stockValid = true;
                        cout << "\n[?] Stock berhasil diupdate!\n";
                    } else {
                        cout << "[?] Stock tidak boleh negatif!\n";
                    }
                } else {
                    cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            break;
        }
        
        case 5: {
            cout << "\n--- Update Semua Data ---\n";
            cout << "Masukkan nama baru: ";
            getline(cin, makanan[index].nama);
            
            cout << "Masukkan kategori baru: ";
            getline(cin, makanan[index].kategori);
            
            bool hargaValid = false;
            while (!hargaValid) {
                cout << "Masukkan harga baru: Rp ";
                if (cin >> makanan[index].harga) {
                    if (makanan[index].harga >= 0) {
                        hargaValid = true;
                    } else {
                        cout << "[?] Harga tidak boleh negatif!\n";
                    }
                } else {
                    cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            
            bool stockValid = false;
            while (!stockValid) {
                cout << "Masukkan stock baru: ";
                if (cin >> makanan[index].stock) {
                    if (makanan[index].stock >= 0) {
                        stockValid = true;
                    } else {
                        cout << "[?] Stock tidak boleh negatif!\n";
                    }
                } else {
                    cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            
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
    bool inputValid = false;
    
    // Loop untuk validasi input
    while (!inputValid) {
        cout << "\nMasukkan kode makanan/minuman yang ingin dihapus (0 untuk batal): ";
        
        // Cek apakah input valid (angka)
        if (cin >> kodeInput) {
            inputValid = true;
            
            // Cek jika user ingin batal
            if (kodeInput == 0) {
                cout << "\n[!] Penghapusan dibatalkan.\n\n";
                return;
            }
        } else {
            // Jika input bukan angka
            cout << "\n[?] Input tidak valid! Harap masukkan angka.\n";
            
            // Bersihkan error state dan buffer input
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
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
    bool konfirmasiValid = false;
    
    while (!konfirmasiValid) {
        cout << "\nApakah Anda yakin ingin menghapus data ini? (y/n): ";
        cin >> konfirmasi;
        
        if (konfirmasi == 'y' || konfirmasi == 'Y' || 
            konfirmasi == 'n' || konfirmasi == 'N') {
            konfirmasiValid = true;
        } else {
            cout << "[?] Input tidak valid! Masukkan 'y' atau 'n'.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
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
// Fungsi Helper untuk mendapatkan tanggal hari ini
// ===================================
string getTanggalHariIni() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    char buffer[20];
    sprintf(buffer, "%02d-%02d-%04d", 
            ltm->tm_mday, 
            1 + ltm->tm_mon, 
            1900 + ltm->tm_year);
    
    return string(buffer);
}

// ===================================
// Fungsi Helper untuk mendapatkan bulan ini
// ===================================
string getBulanIni() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    char buffer[20];
    sprintf(buffer, "%02d-%04d", 
            1 + ltm->tm_mon, 
            1900 + ltm->tm_year);
    
    return string(buffer);
}

// ===================================
// Fungsi untuk cek dan reset pendapatan jika perlu
// ===================================
void cekDanResetPendapatan() {
    string tanggalSekarang = getTanggalHariIni();
    string bulanSekarang = getBulanIni();
    
    // Jika tanggal berbeda, reset pendapatan harian
    if (pendapatan.tanggalTerakhir != tanggalSekarang) {
        pendapatan.totalHariIni = 0;
        pendapatan.tanggalTerakhir = tanggalSekarang;
    }
    
    // Jika bulan berbeda, reset pendapatan bulanan
    if (pendapatan.bulanTerakhir != bulanSekarang) {
        pendapatan.totalBulanIni = 0;
        pendapatan.bulanTerakhir = bulanSekarang;
    }
}

// ===================================
// Fungsi PENJUALAN
// ===================================
void penjualanMakanan(data makanan[], int jumlahData) {
    clearScreen();
    cout << "\n=============== TRANSAKSI PENJUALAN ===============\n\n";
    
    if (jumlahData == 0) {
        cout << "[!] Tidak ada data untuk dijual!\n\n";
        return;
    }
    
    // Cek dan reset pendapatan jika perlu
    cekDanResetPendapatan();
    
    char lanjut;
    int totalTransaksi = 0;
    
    do {
        // Tampilkan data yang ada
        cout << "\nData yang tersedia:\n";
        tampilkanHeaderTabel();
        for (int i = 0; i < jumlahData; i++) {
            tampilkanBarisTabel(makanan[i], i + 1);
        }
        tampilkanFooterTabel();
        
        int kodeInput;
        bool kodeValid = false;
        
        // Validasi input kode
        while (!kodeValid) {
            cout << "\nMasukkan kode makanan/minuman yang dibeli (0 untuk selesai): ";
            
            if (cin >> kodeInput) {
                kodeValid = true;
                
                if (kodeInput == 0) {
                    break;
                }
            } else {
                cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        if (kodeInput == 0) {
            break;
        }
        
        // Cari data berdasarkan kode
        int index = -1;
        for (int i = 0; i < jumlahData; i++) {
            if (makanan[i].kode == kodeInput) {
                index = i;
                break;
            }
        }
        
        if (index == -1) {
            cout << "\n[?] Kode " << kodeInput << " tidak ditemukan!\n";
            continue;
        }
        
        // Cek apakah stock tersedia
        if (makanan[index].stock == 0) {
            cout << "\n[?] Stock habis untuk produk " << makanan[index].nama << "!\n";
            continue;
        }
        
        // Tampilkan info produk
        cout << "\n--- Produk Dipilih ---\n";
        cout << "Nama     : " << makanan[index].nama << "\n";
        cout << "Harga    : Rp " << makanan[index].harga << "\n";
        cout << "Stock    : " << makanan[index].stock << " unit\n";
        
        // Input jumlah pembelian dengan validasi
        int jumlahBeli;
        bool jumlahValid = false;
        
        while (!jumlahValid) {
            cout << "\nMasukkan jumlah yang dibeli (0 untuk batal): ";
            
            if (cin >> jumlahBeli) {
                if (jumlahBeli == 0) {
                    cout << "[!] Pembelian produk ini dibatalkan.\n";
                    jumlahValid = true;
                    jumlahBeli = -1; // Tandai sebagai batal
                } else if (jumlahBeli < 0) {
                    cout << "[?] Jumlah tidak boleh negatif!\n";
                } else if (jumlahBeli > makanan[index].stock) {
                    cout << "[?] Stock tidak cukup! Stock tersedia: " << makanan[index].stock << " unit\n";
                } else {
                    jumlahValid = true;
                }
            } else {
                cout << "[?] Input tidak valid! Harap masukkan angka.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        // Jika dibatalkan, lanjut ke iterasi berikutnya
        if (jumlahBeli == -1) {
            continue;
        }
        
        // Hitung total harga
        int totalHarga = makanan[index].harga * jumlahBeli;
        
        // Update stock
        makanan[index].stock -= jumlahBeli;
        
        // Update pendapatan
        pendapatan.totalHariIni += totalHarga;
        pendapatan.totalBulanIni += totalHarga;
        totalTransaksi += totalHarga;
        
        // Konfirmasi transaksi
        cout << "\n[?] Transaksi berhasil!\n";
        cout << "--- Detail Transaksi ---\n";
        cout << "Produk       : " << makanan[index].nama << "\n";
        cout << "Jumlah       : " << jumlahBeli << " unit\n";
        cout << "Harga Satuan : Rp " << makanan[index].harga << "\n";
        cout << "Total Bayar  : Rp " << totalHarga << "\n";
        cout << "Stock Tersisa: " << makanan[index].stock << " unit\n";
        cout << "------------------------\n";
        
        // Tanya apakah ingin melanjutkan dengan validasi
        bool lanjutValid = false;
        while (!lanjutValid) {
            cout << "\nAda pembelian lagi? (y/n): ";
            cin >> lanjut;
            
            if (lanjut == 'y' || lanjut == 'Y' || 
                lanjut == 'n' || lanjut == 'N') {
                lanjutValid = true;
            } else {
                cout << "[?] Input tidak valid! Masukkan 'y' atau 'n'.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        if (lanjut == 'y' || lanjut == 'Y') {
            clearScreen();
            cout << "\n=============== TRANSAKSI PENJUALAN ===============\n";
        }
        
    } while (lanjut == 'y' || lanjut == 'Y');
    
    // Tampilkan ringkasan transaksi
    if (totalTransaksi > 0) {
        clearScreen();
        cout << "\n=============== RINGKASAN TRANSAKSI ===============\n\n";
        cout << "Total Transaksi Sekarang : Rp " << totalTransaksi << "\n";
        cout << "---------------------------------------------------\n";
        cout << "Pendapatan Hari Ini      : Rp " << pendapatan.totalHariIni << "\n";
        cout << "Pendapatan Bulan Ini     : Rp " << pendapatan.totalBulanIni << "\n";
        cout << "Tanggal                  : " << pendapatan.tanggalTerakhir << "\n";
        cout << "===================================================\n\n";
    } else {
        cout << "\n[!] Tidak ada transaksi dilakukan.\n\n";
    }
}

// ===================================
// Fungsi LAPORAN PENDAPATAN
// ===================================
void laporanPendapatan() {
    clearScreen();
    cout << "\n=============== LAPORAN PENDAPATAN ===============\n\n";
    
    // Cek dan reset pendapatan jika perlu
    cekDanResetPendapatan();
    
    cout << "=================================================\n";
    cout << "  LAPORAN KEUANGAN TOKO MAKANAN & MINUMAN\n";
    cout << "=================================================\n\n";
    
    cout << "Tanggal Hari Ini    : " << pendapatan.tanggalTerakhir << "\n";
    cout << "Bulan/Tahun         : " << pendapatan.bulanTerakhir << "\n\n";
    
    cout << "-------------------------------------------------\n";
    cout << "PENDAPATAN HARIAN\n";
    cout << "-------------------------------------------------\n";
    cout << "Total Hari Ini      : Rp " << setw(12) << right << pendapatan.totalHariIni << "\n\n";
    
    cout << "-------------------------------------------------\n";
    cout << "PENDAPATAN BULANAN\n";
    cout << "-------------------------------------------------\n";
    cout << "Total Bulan Ini     : Rp " << setw(12) << right << pendapatan.totalBulanIni << "\n\n";
    
    cout << "=================================================\n";
    cout << "Catatan:\n";
    cout << "- Pendapatan harian direset setiap hari (00:00)\n";
    cout << "- Pendapatan bulanan direset setiap bulan\n";
    cout << "=================================================\n\n";
}

// ===================================
// Fungsi SAVE DATA ke File (Format Rapi - UPDATED)
// ===================================
void saveToFile(const data makanan[], int jumlahData) {
    clearScreen();
    cout << "\n=============== SIMPAN DATA KE FILE ===============\n\n";
    
    if (jumlahData == 0) {
        cout << "[!] Tidak ada data untuk disimpan!\n\n";
        return;
    }
    
    // Cek dan reset pendapatan jika perlu
    cekDanResetPendapatan();
    
    // Buka file untuk menulis
    ofstream file("DataMenuMakanan.txt");
    
    if (!file.is_open()) {
        cout << "[?] Gagal membuka file DataMenuMakanan.txt!\n\n";
        return;
    }
    
    // Header file
    file << "===============================================================================\n";
    file << "                       DATA MENU MAKANAN & MINUMAN                            \n";
    file << "===============================================================================\n";
    file << "Total Data: " << jumlahData << " item\n";
    file << "Tanggal Simpan: " << getTanggalHariIni() << "\n";
    file << "===============================================================================\n\n";
    
    // Bagian Pendapatan
    file << "===============================================================================\n";
    file << "                          LAPORAN KEUANGAN                                    \n";
    file << "===============================================================================\n";
    file << "Tanggal Terakhir    : " << pendapatan.tanggalTerakhir << "\n";
    file << "Bulan/Tahun         : " << pendapatan.bulanTerakhir << "\n";
    file << "Pendapatan Hari Ini : Rp " << pendapatan.totalHariIni << "\n";
    file << "Pendapatan Bulan Ini: Rp " << pendapatan.totalBulanIni << "\n";
    file << "===============================================================================\n\n";
    
    // Data Produk
    file << "===============================================================================\n";
    file << "                           DATA PRODUK                                        \n";
    file << "===============================================================================\n\n";
    
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
    cout << "Total data tersimpan: " << jumlahData << " item\n";
    cout << "Pendapatan tersimpan: Harian Rp " << pendapatan.totalHariIni 
         << ", Bulanan Rp " << pendapatan.totalBulanIni << "\n\n";
}

// ===================================
// Fungsi Helper untuk konversi string ke int
// ===================================
int stringToInt(string str) {
    int result = 0;
    int i = 0;
    bool negative = false;
    
    if (str[0] == '-') {
        negative = true;
        i = 1;
    }
    
    for (; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    
    return negative ? -result : result;
}

// ===================================
// Fungsi Helper untuk ekstrak angka
// ===================================
int extractNumber(string line, string keyword) {
    size_t pos = line.find(keyword);
    if (pos == string::npos) return 0;
    
    pos = line.find(":", pos) + 1;
    
    while (pos < line.length() && line[pos] == ' ') pos++;
    
    if (line.substr(pos, 2) == "Rp") {
        pos += 2;
        while (pos < line.length() && line[pos] == ' ') pos++;
    }
    
    string numStr = "";
    while (pos < line.length() && line[pos] >= '0' && line[pos] <= '9') {
        numStr += line[pos];
        pos++;
    }
    
    return stringToInt(numStr);
}

// ===================================
// Fungsi Helper untuk ekstrak teks
// ===================================
string extractText(string line) {
    size_t pos = line.find(":");
    if (pos == string::npos) return "";
    
    pos += 1;
    while (pos < line.length() && line[pos] == ' ') pos++;
    
    return line.substr(pos);
}

// ===================================
// Fungsi LOAD DATA dari File (UPDATED)
// ===================================
void loadFromFile(data makanan[], int *jumlahData, int maxSize) {
    clearScreen();
    cout << "\n=============== MUAT DATA DARI FILE ===============\n\n";
    
    ifstream file("DataMenuMakanan.txt");
    
    if (!file.is_open()) {
        cout << "[!] File DataMenuMakanan.txt tidak ditemukan!\n";
        cout << "[!] Pastikan file ada di folder yang sama dengan program.\n\n";
        return;
    }
    
    string line;
    int berhasil = 0;
    bool pendapatanLoaded = false;
    
    // Skip header awal (5 baris)
    for (int i = 0; i < 5; i++) {
        getline(file, line);
    }
    
    // Baca data
    while (getline(file, line)) {
        // Cek bagian Laporan Keuangan
        if (!pendapatanLoaded && line.find("LAPORAN KEUANGAN") != string::npos) {
            getline(file, line); // Skip garis
            
            // Baca Tanggal Terakhir
            if (getline(file, line) && line.find("Tanggal Terakhir") != string::npos) {
                pendapatan.tanggalTerakhir = extractText(line);
            }
            
            // Baca Bulan/Tahun
            if (getline(file, line) && line.find("Bulan/Tahun") != string::npos) {
                pendapatan.bulanTerakhir = extractText(line);
            }
            
            // Baca Pendapatan Hari Ini
            if (getline(file, line) && line.find("Pendapatan Hari Ini") != string::npos) {
                pendapatan.totalHariIni = extractNumber(line, "Pendapatan Hari Ini");
            }
            
            // Baca Pendapatan Bulan Ini
            if (getline(file, line) && line.find("Pendapatan Bulan Ini") != string::npos) {
                pendapatan.totalBulanIni = extractNumber(line, "Pendapatan Bulan Ini");
            }
            
            pendapatanLoaded = true;
            
            // Cek apakah perlu reset
            cekDanResetPendapatan();
            continue;
        }
        
        // Cek bagian Data Produk
        if (line.find("--- Data #") != string::npos && berhasil < maxSize) {
            
            if (getline(file, line) && line.find("Kode") != string::npos) {
                makanan[berhasil].kode = extractNumber(line, "Kode");
            } else break;
            
            if (getline(file, line) && line.find("Nama") != string::npos) {
                makanan[berhasil].nama = extractText(line);
            } else break;
            
            if (getline(file, line) && line.find("Kategori") != string::npos) {
                makanan[berhasil].kategori = extractText(line);
            } else break;
            
            if (getline(file, line) && line.find("Harga") != string::npos) {
                makanan[berhasil].harga = extractNumber(line, "Harga");
            } else break;
            
            if (getline(file, line) && line.find("Stock") != string::npos) {
                makanan[berhasil].stock = extractNumber(line, "Stock");
            } else break;
            
            berhasil++;
            getline(file, line); // Skip garis pemisah
        }
    }
    
    file.close();
    *jumlahData = berhasil;
    
    if (berhasil > 0) {
        cout << "[?] Data berhasil dimuat dari file!\n";
        cout << "Total data: " << berhasil << " item\n";
        cout << "Pendapatan Hari Ini: Rp " << pendapatan.totalHariIni << "\n";
        cout << "Pendapatan Bulan Ini: Rp " << pendapatan.totalBulanIni << "\n\n";
        
        cout << "Preview data:\n";
        tampilkanHeaderTabel();
        int preview = berhasil;
        for (int i = 0; i < preview; i++) {
            tampilkanBarisTabel(makanan[i], i + 1);
        }
        tampilkanFooterTabel();
        
    } else {
        cout << "[?] Gagal membaca data dari file!\n\n";
    }
}

// Main Function
// Main Function dengan Error Handling
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
        cout << "7. Transaksi Penjualan (SELL)\n";
        cout << "8. Laporan Pendapatan (REPORT)\n";
        cout << "9. Simpan Data ke File (SAVE)\n";
        cout << "10. Muat Data dari File (LOAD)\n";
        cout << "11. Keluar\n";
        cout << "-------------------------------------\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;
        
        // Error Handling: Cek jika input bukan angka (misalnya string)
        if (cin.fail()) {
            cout << "\n[?] ERROR: Input tidak valid! Harap masukkan angka (1-11).\n";
            
            // Clear error flag pada cin
            cin.clear();
            
            // Buang semua karakter invalid di buffer sampai newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // Set pilihan ke nilai invalid agar tidak masuk ke case manapun
            pilihan = -1;
            continue; // Lanjut ke iterasi berikutnya (tampilkan menu lagi)
        }
        
        // Buang karakter newline yang tersisa setelah input valid
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
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
                penjualanMakanan(makanan, jumlahData);
                break;
            case 8:
                laporanPendapatan();
                break;
            case 9:
                saveToFile(makanan, jumlahData);
                break;
            case 10:
                loadFromFile(makanan, &jumlahData, MAX_DATA);
                break;
            case 11:
                clearScreen();
                cout << "\n=====================================\n";
                cout << "  Terima kasih telah menggunakan\n";
                cout << "  Sistem Manajemen Menu Makanan!\n";
                cout << "=====================================\n\n";
                break;
            default:
                cout << "\n[?] Pilihan tidak valid! Harap pilih angka 1-11.\n";
                break;
        }
    } while (pilihan != 11);
    
    return 0;
}
