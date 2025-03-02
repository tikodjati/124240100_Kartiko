#include <iostream>
using namespace std;

int pilih_menu, jumlah_barang, simpan, metode;

typedef struct{
    string nama_barang;
    int harga;
}barang;

barang dataBarang[1000];

void ENTER_1X()
{
    cout << endl;
    cout << "Tekan 'ENTER' 1x";
    cin.get();
    cin.get();
    system("clear");
}

void ENTER_2X()
{
    cout << endl;
    cout << "Tekan 'ENTER' 2x";
    cin.get();
    cin.get();
    system("clear");
}

//fungsi tampilan menu
void menu()
{
    cout << "Menu : " << endl;
    cout << "1. Input data barang" << endl;
    cout << "2. Tampilkan data barang" << endl;
    cout << "3. Cari data barang (nama/harga)" << endl;
    cout << "4. Keluar" << endl;
    cout << "Pilih menu : ";
    cin >> pilih_menu;
    ENTER_1X();
}

//fungsi input data (menu ke-1)
void input_data()
{
    cout << "Masukkan jumlah barang yang ingin diinput : ";
    cin >> jumlah_barang;
    cout << endl;
    cin.ignore();

    //looping input menu
    for (int i = 0; i < jumlah_barang; i++)
    {
        cout << simpan + i + 1 << ". Masukkan nama barang   : ";
        getline(cin, dataBarang[simpan + i].nama_barang);
        cout << "   Masukkan harga barang  : ";
        cin >> dataBarang[simpan + i].harga;
        cin.ignore();
        cout << endl;
        /*
        Variabel simpan disini sebagai alat menyimpan data.
        Karena deklarasi simpan masih NULL, maka simpan bernilai = 0
        */
    }
    simpan += jumlah_barang; //untuk update berdasarkan jumlah barang yang dimasukkan
    ENTER_2X();
}

//fungsi bubble sort
void bubble_sort()
{
    for (int i = 0; i < simpan-1; i++)
    {
        for (int j = 0; j < simpan-i-1; j++)
        {
            if (dataBarang[j].nama_barang > dataBarang[j+1].nama_barang)
            {
                swap(dataBarang[j], dataBarang[j+1]);
            }
        }
    }
}

//fungsi menampilkan data (menu ke-2)
void tampilkan_Data()
{
    bubble_sort();
    cout << "barang anda : " << endl;
    for (int i = 0; i < simpan; i++)
    {
        cout << i + 1 << ". Nama barang : " << dataBarang[i].nama_barang << endl;
        cout << "   Harga       : " << dataBarang[i].harga << endl;
        cout << endl;
    }
    ENTER_2X();
}

//fungsi metode pencarian dengan nama (binary search) - Diperbaiki
void mtdNama()
{
    bubble_sort();
    string cariNama;
    bool ditemukan = false;

    cin.ignore();
    cout << "Masukkan nama barang yang dicari : ";
    getline(cin, cariNama);
    system("clear");

    int awal = 0, akhir = simpan - 1, tengah, index = -1;
    
    while (awal <= akhir)
    {
        tengah = awal + (akhir - awal) / 2;
        if (dataBarang[tengah].nama_barang == cariNama)
        {
            index = tengah; // Menyimpan indeks awal barang yang ditemukan
            break;
        }
        else if (dataBarang[tengah].nama_barang < cariNama)
        {
            awal = tengah + 1;
        }
        else
        {
            akhir = tengah - 1;
        }
    }

    if (index == -1)
    {
        cout << "Barang dengan nama " << cariNama << " tidak tersedia dalam daftar." << endl;
    }
    else
    {
        cout << "Barang dengan nama " << cariNama << " ditemukan dengan detail :" << endl;
        cout << endl;

        // Mencetak semua barang dengan nama yang sama
        int i = index;
        while (i >= 0 && dataBarang[i].nama_barang == cariNama)
        {
            cout << "Nama barang : " << dataBarang[i].nama_barang << endl;
            cout << "Harga       : " << dataBarang[i].harga << endl;
            cout << endl;
            ditemukan = true;
            i--;
        }

        // Mencetak semua barang dengan nama yang sama
        i = index + 1;
        while (i < simpan && dataBarang[i].nama_barang == cariNama)
        {
            cout << "Nama barang : " << dataBarang[i].nama_barang << endl;
            cout << "Harga       : " << dataBarang[i].harga << endl;
            cout << endl;
            ditemukan = true;
            i++;
        }
    }
}

//fungsi metode pencarian berdasarkan harga (sequential search)
void mtdHarga()
{
    //metode pencarian sequential yang diurutkan terlebih dahulu tanpa sentinel
    int cariHarga;

    cout << "Masukkan harga barang yang dicari : ";
    cin >> cariHarga;
    system("clear");
    bool ditemukan = false;

    for (int i = 0; i < simpan; i++)
    {
        if (dataBarang[i].harga == cariHarga)
        {
            if (!ditemukan) {
                cout << "Barang dengan harga " << cariHarga << " ditemukan dengan detail :" << endl;
                cout << endl;
                ditemukan = true;
            }
            cout << "Nama barang  : " << dataBarang[i].nama_barang << endl;
            cout << "Harga barang : " << dataBarang[i].harga << endl;
            cout << endl;
        }
    }

    if(!ditemukan)
    {
        cout << "Barang dengan harga " << cariHarga << " tidak tersedia dalam daftar harga barang";
    }
}

//fungsi opsi searching
void opsi_search()
{
    if(pilih_menu == 3)
    {
        cout << "Metode pencarian : " << endl;
        cout << "1. Cari berdasarkan nama" << endl;
        cout << "2. Cari berdasarkan harga" << endl;
        cout << "Pilih metode : ";
        cin >> metode;
        system("clear");
            if (metode == 1)
        {
            mtdNama();
            ENTER_2X();
        }
        else if(metode == 2)
        {
            mtdHarga();
            ENTER_2X();
        }
        else
        {
            cout << "Maaf, hanya dapat melakukan pencarian berdasarkan nama barang dan harga barang." << endl;
            cout << "Tekan 'ENTER' untuk kembali";
            ENTER_2X();
        }
    }
}

//ERROR function
void ERROR()
{
    cout << "Maaf, hanya dapat memilih menu 1 hingga 4." << endl;
}

int main()
{
    while (true)
    {
        menu();
        switch (pilih_menu)
        {
        case 1:
            input_data();
            break;
        
        case 2:
            tampilkan_Data();
            break;

        case 3: 
            opsi_search();
            break;

        case 4:
            return 0;
            break;

        default:
            ERROR();
            ENTER_2X();
            break;
        }
    }
    
}

