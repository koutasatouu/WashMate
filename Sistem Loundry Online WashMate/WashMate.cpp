#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <iomanip>   // setw
#include <limits>    // numeric_limits
#include <utility>
using namespace std;

// ================== DATA LAYANAN (ARRAY) ==================
string layanan[] = {"Cuci Kering", "Setrika", "Express", "Cuci Selimut"};
int harga[]      = {7000, 5000, 12000, 15000};
int jumlahLayanan = sizeof(harga) / sizeof(harga[0]);

// ================== LINKED LIST (CUCIAN) ==================
struct Cucian {
    int id;
    string nama;
    string jenis;
    float berat;
    string status;
    stack<string> riwayat; // stack per item -> menyimpan status lama
    Cucian* next;
    Cucian(int _id, string _nama, string _jenis, float _berat)
        : id(_id), nama(std::move(_nama)), jenis(std::move(_jenis)),
          berat(_berat), status("Diterima"), next(nullptr) {}
};
Cucian* head = nullptr;
int idCounter = 1;

// ================== QUEUE (ANTRIAN) ==================
queue<int> antrianIds;

// ================== BST (PELANGGAN) ==================
struct Node {
    string nama;
    Node* left;
    Node* right;
    Node(string n) : nama(std::move(n)), left(nullptr), right(nullptr) {}
};
Node* rootPelanggan = nullptr;

// =============== FUNGSI-BANTU (IO SAFETY) ===============
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ================== FUNGSI CUCIAN ==================
void tambahCucian(const string& nama, const string& jenis, float berat) {
    Cucian* baru = new Cucian(idCounter++, nama, jenis, berat);
    if (!head) head = baru;
    else {
        Cucian* tmp = head;
        while (tmp->next) tmp = tmp->next;
        tmp->next = baru;
    }
    // Masukkan ke antrian otomatis
    antrianIds.push(baru->id);

    // Tambah pelanggan ke BST juga
    // (satu nama disimpan meskipun ada duplikat � BST sederhana: jika sama -> kanan)
    // We'll handle duplicates by placing to right.
    // Insert pelanggan
    Node** cur = &rootPelanggan;
    while (*cur) {
        if (nama < (*cur)->nama) cur = &((*cur)->left);
        else cur = &((*cur)->right);
    }
    *cur = new Node(nama);

    cout << "? Cucian ditambahkan (ID=" << baru->id << ", Nama=" << nama << ")\n";
}

Cucian* cariCucianById(int id) {
    Cucian* tmp = head;
    while (tmp) {
        if (tmp->id == id) return tmp;
        tmp = tmp->next;
    }
    return nullptr;
}

void tampilCucian() {
    cout << "\n=== DATA CUCIAN ===\n";
    if (!head) { cout << "Belum ada data cucian.\n"; return; }
    cout << left << setw(6) << "ID |" << setw(18) << " Nama |" << setw(13) << " Jenis |" << setw(8) << " Berat(kg) |" << " Status\n";
    cout << "---------------------------------------------------------\n";
    Cucian* tmp = head;
    while (tmp) {
        cout << left << setw(6) << tmp->id
             << setw(18) << tmp->nama
             << setw(16) << tmp->jenis
             << setw(8) << tmp->berat 
             << tmp->status << '\n';
        tmp = tmp->next;
    }
}

// ================== STACK OPERATIONS (per item) ==================
void ubahStatus(int id, const string& statusBaru) {
    Cucian* c = cariCucianById(id);
    if (!c) {
        cout << "? ID tidak ditemukan.\n";
        return;
    }
    // Push status lama ke stack
    c->riwayat.push(c->status);
    c->status = statusBaru;
    if(statusBaru != "Diproses" && statusBaru != "Dicuci" && statusBaru != "Dikeringkan" && statusBaru != "Diterima" && statusBaru != "Selesai")
        cout << "Tidak bisa mengubah status menjadi: " << statusBaru << "hanya bisa Di proses, Di cuci, Di keringkan, Di terima, Selesai\n";
    else
    cout << "?? Status ID " << id << " (" << c->nama << ") diubah menjadi: " << statusBaru << '\n';
}

void undoStatus(int id) {
    Cucian* c = cariCucianById(id);
    if (!c) {
        cout << "? ID tidak ditemukan.\n";
        return;
    }
    if (c->riwayat.empty()) {
        cout << "?? Tidak ada riwayat status untuk ID " << id << '\n';
        return;
    }
    string prev = c->riwayat.top(); c->riwayat.pop();
    c->status = prev;
    cout << "?? Undo berhasil. Status ID " << id << " sekarang: " << c->status << '\n';
}

void tampilRiwayat(int id) {
    Cucian* c = cariCucianById(id);
    if (!c) { cout << "? ID tidak ditemukan.\n"; return; }
    cout << "\nRiwayat status untuk ID " << id << " (" << c->nama << "):\n";
    if (c->riwayat.empty()) {
        cout << "  - Kosong\n";
        return;
    }
    // Can't iterate stack directly without copy; copy to display
    stack<string> copy = c->riwayat;
    int idx = copy.size();
    while (!copy.empty()) {
        cout << "  " << idx-- << ". " << copy.top() << '\n';
        copy.pop();
    }
}

// ================== QUEUE OPERATIONS ==================
void tambahAntrianById(int id) {
    Cucian* c = cariCucianById(id);
    if (!c) { cout << "? ID tidak ditemukan.\n"; return; }
    antrianIds.push(id);
    cout << "?? ID " << id << " (" << c->nama << ") masuk antrian.\n";
}

void tampilAntrian() {
    cout << "\n=== ANTRIAN (ID) ===\n";
    if (antrianIds.empty()) { cout << "Antrian kosong.\n"; return; }
    queue<int> copy = antrianIds;
    while (!copy.empty()) {
        cout << copy.front() << " ";
        copy.pop();
    }
    cout << '\n';
}

void prosesAntrian() {
    if (antrianIds.empty()) { cout << "? Antrian kosong.\n"; return; }
    int id = antrianIds.front(); antrianIds.pop();
    Cucian* c = cariCucianById(id);
    if (!c) {
        cout << "?? ID " << id << " tidak ditemukan (mungkin dihapus).\n";
        return;
    }
    // contoh proses: ubah status jadi "Dicuci"
    c->riwayat.push(c->status);
    c->status = "Dicuci";
    cout << "?? Memproses ID " << id << " (" << c->nama << ") -> Status: Dicuci\n";
}

// ================== BST (PELENGGAN) ==================
void inorderPelanggan(Node* node) {
    if (!node) return;
    inorderPelanggan(node->left);
    cout << node->nama << "  ";
    inorderPelanggan(node->right);
}

void tampilPelanggan() {
    cout << "\n=== DATA PELANGGAN (inorder) ===\n";
    if (!rootPelanggan) { cout << "Belum ada pelanggan.\n"; return; }
    inorderPelanggan(rootPelanggan);
    cout << '\n';
}

// ================== MENU & MAIN ==================
void tampilMenu() {
    cout << "\n===== WASHMATE TEMAN BAIK CUCIANMU! =====\n"
         << "SELAMAT DATANG DI WASHMATE\n"
         << "Silahkan Pilih Menu Berikut:\n"
         << "1. Tampilkan daftar layanan\n"
         << "2. Tambah cucian\n"
         << "3. Tampilkan data cucian\n"
         << "4. Ubah status cucian (push ke stack)\n"
         << "5. Undo status cucian (pop dari stack)\n"
         << "6. Tampilkan riwayat status (stack) per ID\n"
         << "7. Tampilkan antrian\n"
         << "8. Tambah ke antrian (by ID)\n"
         << "9. Proses antrian (dequeue)\n"
         << "10. Tampilkan data pelanggan (BST inorder)\n"
         << "0. Keluar\n"
         << "Pilihan: ";
}

void tampilLayanan() {
    cout << "\n=== DAFTAR LAYANAN ===\n";
    for (int i = 0; i < jumlahLayanan; ++i) {
        cout << (i+1) << ". " << layanan[i] << " - Rp" << harga[i] << '\n';
    }
}

int main() {
    cout << "=== SISTEM LAUNDRY (Console C++) ===\n";
    int pilih;
    do {
        tampilMenu();
        if (!(cin >> pilih)) { 
            cout << "Input tidak valid.\n";
            clearInput();
            continue;
        }
        clearInput(); // clear newline

        switch (pilih) {
            case 1:
                tampilLayanan();
                break;
            case 2: {
                string nama; int opsi; float berat;
                cout << "Masukkan nama: "; getline(cin, nama);
                tampilLayanan();
                cout << "Pilih layanan (nomor): "; cin >> opsi; clearInput();
                if (opsi < 1 || opsi > jumlahLayanan) { cout << "Pilihan layanan tidak valid.\n"; break; }
                cout << "Masukkan berat (Kg): "; cin >> berat; clearInput();
                tambahCucian(nama, layanan[opsi-1], berat);
                break;
            }
            case 3:
                tampilCucian();
                break;
            case 4: {
                int id; string status;
                cout << "Masukkan ID cucian: "; cin >> id; clearInput();
                cout << "Masukkan status baru: "; getline(cin, status);
                ubahStatus(id, status);
                break;
            }
            case 5: {
                int id; cout << "Masukkan ID cucian untuk undo: "; cin >> id; clearInput();
                undoStatus(id);
                break;
            }
            case 6: {
                int id; cout << "Masukkan ID cucian untuk tampil riwayat: "; cin >> id; clearInput();
                tampilRiwayat(id);
                break;
            }
            case 7:
                tampilAntrian();
                break;
            case 8: {
                int id; cout << "Masukkan ID cucian untuk masuk antrian: "; cin >> id; clearInput();
                tambahAntrianById(id);
                break;
            }
            case 9:
                prosesAntrian();
                break;
            case 10:
                tampilPelanggan();
                break;
            case 0:
                cout << "Keluar. Terima kasih.\n";
                break;
            default:
                cout << "Pilihan tidak dikenal.\n";
                break;
        }

    } while (pilih != 0);

    return 0;
}