#include <iostream>
#include <string>
using namespace std;

/* =====================================================
   NODE RELASI (penghubung alat angkutan dan daerah)
   ===================================================== */
struct Relasi {
    Relasi *nextRelasi;
    struct Angkutan *angkutan;
    struct Daerah *daerah;
};

/* =====================================================
   NODE ALAT ANGKUTAN
   ===================================================== */
struct Angkutan {
    string nama;
    Angkutan *next;
};

/* =====================================================
   NODE DAERAH
   ===================================================== */
struct Daerah {
    string nama;
    Daerah *next;
};

/* =====================================================
   HEAD POINTER
   ===================================================== */
Angkutan *headAngkutan = NULL;
Daerah *headDaerah = NULL;
Relasi *headRelasi = NULL;

/* =====================================================
   a. PENAMBAHAN DATA ALAT ANGKUTAN
   ===================================================== */
void tambahAngkutan(string nama) {
    Angkutan *baru = new Angkutan{nama, NULL};
    if (!headAngkutan) headAngkutan = baru;
    else {
        Angkutan *temp = headAngkutan;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
}

/* =====================================================
   b. PENAMBAHAN DATA DAERAH
   ===================================================== */
void tambahDaerah(string nama) {
    Daerah *baru = new Daerah{nama, NULL};
    if (!headDaerah) headDaerah = baru;
    else {
        Daerah *temp = headDaerah;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
}

/* =====================================================
   FUNGSI CARI
   ===================================================== */
Angkutan* cariAngkutan(string nama) {
    Angkutan *temp = headAngkutan;
    while (temp && temp->nama != nama) temp = temp->next;
    return temp;
}

Daerah* cariDaerah(string nama) {
    Daerah *temp = headDaerah;
    while (temp && temp->nama != nama) temp = temp->next;
    return temp;
}

/* =====================================================
   c. PENENTUAN RELASI ALAT & DAERAH
   ===================================================== */
void tambahRelasi(string namaAngkutan, string namaDaerah) {
    Angkutan *a = cariAngkutan(namaAngkutan);
    Daerah *d = cariDaerah(namaDaerah);

    if (!a || !d) {
        cout << "Angkutan atau Daerah tidak ditemukan!\n";
        return;
    }

    Relasi *r = new Relasi{headRelasi, a, d};
    headRelasi = r;
}

/* =====================================================
   d. MENGHAPUS DATA ALAT ANGKUTAN
   ===================================================== */
void hapusAngkutan(string nama) {
    Angkutan *curr = headAngkutan, *prev = NULL;
    while (curr && curr->nama != nama) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return;

    if (!prev) headAngkutan = curr->next;
    else prev->next = curr->next;

    // hapus relasi terkait
    Relasi *r = headRelasi, *pr = NULL;
    while (r) {
        if (r->angkutan == curr) {
            if (!pr) headRelasi = r->nextRelasi;
            else pr->nextRelasi = r->nextRelasi;
            Relasi *hapus = r;
            r = r->nextRelasi;
            delete hapus;
        } else {
            pr = r;
            r = r->nextRelasi;
        }
    }
    delete curr;
}

/* =====================================================
   e. MENGHAPUS DATA DAERAH
   ===================================================== */
void hapusDaerah(string nama) {
    Daerah *curr = headDaerah, *prev = NULL;
    while (curr && curr->nama != nama) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return;

    if (!prev) headDaerah = curr->next;
    else prev->next = curr->next;

    // hapus relasi terkait
    Relasi *r = headRelasi, *pr = NULL;
    while (r) {
        if (r->daerah == curr) {
            if (!pr) headRelasi = r->nextRelasi;
            else pr->nextRelasi = r->nextRelasi;
            Relasi *hapus = r;
            r = r->nextRelasi;
            delete hapus;
        } else {
            pr = r;
            r = r->nextRelasi;
        }
    }
    delete curr;
}

/* =====================================================
   f. MENAMPILKAN SEMUA ALAT & DAERAH YANG DIKUNJUNGI
   ===================================================== */
void tampilSemua() {
    Angkutan *a = headAngkutan;
    while (a) {
        cout << a->nama << " -> ";
        Relasi *r = headRelasi;
        while (r) {
            if (r->angkutan == a)
                cout << r->daerah->nama << ", ";
            r = r->nextRelasi;
        }
        cout << endl;
        a = a->next;
    }
}

/* =====================================================
   g. DAERAH DARI ALAT ANGKUTAN TERTENTU
   ===================================================== */
void daerahDariAngkutan(string nama) {
    Angkutan *a = cariAngkutan(nama);
    if (!a) return;

    Relasi *r = headRelasi;
    cout << "Daerah yang dilalui " << nama << ": ";
    while (r) {
        if (r->angkutan == a)
            cout << r->daerah->nama << ", ";
        r = r->nextRelasi;
    }
    cout << endl;
}

/* =====================================================
   h. ALAT ANGKUTAN DARI DAERAH TERTENTU
   ===================================================== */
void angkutanDariDaerah(string nama) {
    Daerah *d = cariDaerah(nama);
    if (!d) return;

    Relasi *r = headRelasi;
    cout << "Alat ke " << nama << ": ";
    while (r) {
        if (r->daerah == d)
            cout << r->angkutan->nama << ", ";
        r = r->nextRelasi;
    }
    cout << endl;
}

/* =====================================================
   i. DAERAH PALING MUDAH & PALING SULIT
   ===================================================== */
void daerahEkstrem() {
    Daerah *d = headDaerah;
    int max = -1, min = 999;
    string mudah, sulit;

    while (d) {
        int count = 0;
        Relasi *r = headRelasi;
        while (r) {
            if (r->daerah == d) count++;
            r = r->nextRelasi;
        }
        if (count > max) { max = count; mudah = d->nama; }
        if (count < min) { min = count; sulit = d->nama; }
        d = d->next;
    }

    cout << "Paling mudah: " << mudah << endl;
    cout << "Paling sulit: " << sulit << endl;
}

/* =====================================================
   MAIN (CONTOH PEMAKAIAN)
   ===================================================== */
int main() {
    int pilih;
    string angkutan, daerah;

    do {
        cout << "\n=== MENU DATA ALAT TRANSPORT ===\n";
        cout << "1. Tambah Alat Angkutan (A)\n";
        cout << "2. Tambah Daerah (B)\n";
        cout << "3. Tambah Relasi Alat & Daerah (C)\n";
        cout << "4. Hapus Alat Angkutan (D)\n";
        cout << "5. Hapus Daerah (E)\n";
        cout << "6. Tampilkan Semua Alat & Daerah (F)\n";
        cout << "7. Tampilkan Daerah dari Alat Tertentu (G)\n";
        cout << "8. Tampilkan Alat dari Daerah Tertentu (H)\n";
        cout << "9. Daerah Paling Mudah & Sulit (I)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
        case 1:
            cout << "Nama Alat Angkutan: ";
            getline(cin, angkutan);
            tambahAngkutan(angkutan);
            break;

        case 2:
            cout << "Nama Daerah: ";
            getline(cin, daerah);
            tambahDaerah(daerah);
            break;

        case 3:
            cout << "Nama Alat Angkutan: ";
            getline(cin, angkutan);
            cout << "Nama Daerah: ";
            getline(cin, daerah);
            tambahRelasi(angkutan, daerah);
            break;

        case 4:
            cout << "Nama Alat Angkutan yang dihapus: ";
            getline(cin, angkutan);
            hapusAngkutan(angkutan);
            break;

        case 5:
            cout << "Nama Daerah yang dihapus: ";
            getline(cin, daerah);
            hapusDaerah(daerah);
            break;

        case 6:
            tampilSemua();
            break;

        case 7:
            cout << "Nama Alat Angkutan: ";
            getline(cin, angkutan);
            daerahDariAngkutan(angkutan);
            break;

        case 8:
            cout << "Nama Daerah: ";
            getline(cin, daerah);
            angkutanDariDaerah(daerah);
            break;

        case 9:
            daerahEkstrem();
            break;
        }
    } while (pilih != 0);

    return 0;
}
