#include <iostream>
#include <string>
using namespace std;

// ============ STRUCT DEFINITIONS ============

// Struct untuk Transaksi (Double Linked List)
struct Transaksi
{
    int id;
    string nama;
    string jenis;
    float berat;
    int totalHarga;
    Transaksi *prev;
    Transaksi *next;
};

// Struct untuk Queue (Single Linked List)
struct Pelanggan
{
    int id;
    string nama;
    string layanan;
    Pelanggan *next;
};

// Struct untuk BST
struct Node
{
    int idTransaksi;
    string nama;
    Node *left;
    Node *right;
};

// ============ ARRAY - MENU DAN HARGA ============
class MenuArray
{
private:
    string menu[10];
    int harga[10];
    int jumlahLayanan;

public:
    MenuArray()
    {
        jumlahLayanan = 0;
    }

    // Fungsi untuk menampilkan menu
    void tampilMenu()
    {
        cout << "\n========== DAFTAR MENU LAYANAN ==========" << endl;
        for (int i = 0; i < jumlahLayanan; i++)
        {
            cout << (i + 1) << ". " << menu[i] << " - Rp" << harga[i] << endl;
        }
        cout << "========================================" << endl;
    }

    // Fungsi untuk mendapatkan harga berdasarkan layanan
    int getHarga(string layanan)
    {
        for (int i = 0; i < jumlahLayanan; i++)
        {
            if (menu[i] == layanan)
            {
                return harga[i];
            }
        }
        return -1; // Layanan tidak ditemukan
    }

    // Fungsi untuk validasi layanan
    bool validasiLayanan(string layanan)
    {
        for (int i = 0; i < jumlahLayanan; i++)
        {
            if (menu[i] == layanan)
            {
                return true;
            }
        }
        return false;
    }

    // Fungsi untuk menambah menu
    void tambahLayanan(string nama, int hargaLayanan)
    {
        if (jumlahLayanan < 10)
        {
            menu[jumlahLayanan] = nama;
            harga[jumlahLayanan] = hargaLayanan;
            jumlahLayanan++;
        }
    }

    int getJumlahLayanan()
    {
        return jumlahLayanan;
    }

    // Fungsi untuk mendapatkan nama layanan berdasarkan nomor
    string getNamaLayananByNomor(int nomor)
    {
        if (nomor > 0 && nomor <= jumlahLayanan)
        {
            return menu[nomor - 1];
        }
        return ""; // Nomor tidak valid
    }

    // Fungsi untuk mendapatkan harga berdasarkan nomor
    int getHargaByNomor(int nomor)
    {
        if (nomor > 0 && nomor <= jumlahLayanan)
        {
            return harga[nomor - 1];
        }
        return -1; // Nomor tidak valid
    }
};

// ============ QUEUE - SINGLE LINKED LIST ============
class QueuePelanggan
{
private:
    Pelanggan *front;
    Pelanggan *rear;

public:
    QueuePelanggan()
    {
        front = NULL;
        rear = NULL;
    }

    // Fungsi untuk menambah pelanggan ke antrian
    void enqueue(int id, string nama, string layanan)
    {
        Pelanggan *nodeBaru = new Pelanggan();
        nodeBaru->id = id;
        nodeBaru->nama = nama;
        nodeBaru->layanan = layanan;
        nodeBaru->next = NULL;

        if (isEmptyQueue())
        {
            front = nodeBaru;
            rear = nodeBaru;
        }
        else
        {
            rear->next = nodeBaru;
            rear = nodeBaru;
        }
        cout << "Pelanggan " << nama << " masuk antrian (ID: " << id << ")" << endl;
    }

    // Fungsi untuk mengeluarkan pelanggan dari antrian
    Pelanggan *dequeue()
    {
        if (isEmptyQueue())
        {
            cout << "Antrian kosong!" << endl;
            return NULL;
        }

        Pelanggan *temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        cout << "Pelanggan " << temp->nama << " mulai diproses" << endl;
        return temp;
    }

    // Fungsi untuk cek antrian kosong
    bool isEmptyQueue()
    {
        return front == NULL;
    }

    // Fungsi untuk menampilkan antrian
    void tampilAntrian()
    {
        if (isEmptyQueue())
        {
            cout << "\nAntrian kosong!" << endl;
            return;
        }

        cout << "\n========== DAFTAR ANTRIAN PELANGGAN ==========" << endl;
        Pelanggan *current = front;
        int nomor = 1;
        while (current != NULL)
        {
            cout << nomor << ". ID: " << current->id << " | Nama: " << current->nama
                 << " | Layanan: " << current->layanan << endl;
            current = current->next;
            nomor++;
        }
        cout << "==============================================" << endl;
    }

    // Destructor
    ~QueuePelanggan()
    {
        Pelanggan *current = front;
        while (current != NULL)
        {
            Pelanggan *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// ============ DOUBLE LINKED LIST - TRANSAKSI ============
class HistoriTransaksi
{
private:
    Transaksi *head;
    Transaksi *tail;

public:
    HistoriTransaksi()
    {
        head = NULL;
        tail = NULL;
    }

    // Fungsi untuk menambah transaksi
    void tambahTransaksi(int id, string nama, string jenis, float berat, int totalHarga)
    {
        Transaksi *nodeBaru = new Transaksi();
        nodeBaru->id = id;
        nodeBaru->nama = nama;
        nodeBaru->jenis = jenis;
        nodeBaru->berat = berat;
        nodeBaru->totalHarga = totalHarga;
        nodeBaru->prev = NULL;
        nodeBaru->next = NULL;

        if (head == NULL)
        {
            head = nodeBaru;
            tail = nodeBaru;
        }
        else
        {
            tail->next = nodeBaru;
            nodeBaru->prev = tail;
            tail = nodeBaru;
        }
        cout << "Transaksi ID " << id << " berhasil ditambahkan" << endl;
    }

    // Fungsi untuk menghapus transaksi berdasarkan ID
    void hapusTransaksi(int id)
    {
        if (head == NULL)
        {
            cout << "Riwayat transaksi kosong!" << endl;
            return;
        }

        Transaksi *current = head;
        while (current != NULL && current->id != id)
        {
            current = current->next;
        }

        if (current == NULL)
        {
            cout << "Transaksi dengan ID " << id << " tidak ditemukan!" << endl;
            return;
        }

        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        else
        {
            head = current->next;
        }

        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
        else
        {
            tail = current->prev;
        }

        cout << "Transaksi ID " << id << " berhasil dihapus" << endl;
        delete current;
    }

    // Fungsi untuk menampilkan semua transaksi
    void tampilHistori()
    {
        if (head == NULL)
        {
            cout << "\nRiwayat transaksi kosong!" << endl;
            return;
        }

        cout << "\n========== RIWAYAT TRANSAKSI ==========" << endl;
        Transaksi *current = head;
        int nomor = 1;
        while (current != NULL)
        {
            cout << nomor << ". ID: " << current->id << " | Nama: " << current->nama
                 << " | Jenis: " << current->jenis << " | Berat: " << current->berat
                 << "kg | Total: Rp" << current->totalHarga << endl;
            current = current->next;
            nomor++;
        }
        cout << "========================================" << endl;
    }

    // Fungsi untuk mencari transaksi berdasarkan ID
    Transaksi *cariTransaksiByID(int id)
    {
        Transaksi *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                cout << "Transaksi ditemukan - Nama: " << current->nama
                     << " | Jenis: " << current->jenis << endl;
                return current;
            }
            current = current->next;
        }
        cout << "Transaksi dengan ID " << id << " tidak ditemukan!" << endl;
        return NULL;
    }

    // Destructor
    ~HistoriTransaksi()
    {
        Transaksi *current = head;
        while (current != NULL)
        {
            Transaksi *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// ============ STACK - PROSES BERDASARKAN ARRAY ============
class StackProses
{
private:
    string proses[10];
    int top;

public:
    StackProses()
    {
        top = -1;
    }

    // Fungsi untuk push - lanjut tahap
    void pushProses(string tahapProses)
    {
        if (top < 9)
        {
            top++;
            proses[top] = tahapProses;
            cout << "Proses '" << tahapProses << "' ditambahkan ke tahap pengerjaan" << endl;
        }
        else
        {
            cout << "Stack sudah penuh!" << endl;
        }
    }

    // Fungsi untuk pop - undo / rollback
    string popProses()
    {
        if (isEmptyStack())
        {
            cout << "Tidak ada proses untuk di-undo!" << endl;
            return "";
        }
        string prosesDihapus = proses[top];
        top--;
        cout << "Proses '" << prosesDihapus << "' di-rollback" << endl;
        return prosesDihapus;
    }

    // Fungsi untuk peek - status saat ini
    string peekProses()
    {
        if (isEmptyStack())
        {
            cout << "Tidak ada proses yang sedang berjalan!" << endl;
            return "";
        }
        cout << "Status saat ini: " << proses[top] << endl;
        return proses[top];
    }

    // Fungsi untuk cek stack kosong
    bool isEmptyStack()
    {
        return top == -1;
    }

    // Fungsi untuk menampilkan semua tahap proses
    void tampilProses()
    {
        if (isEmptyStack())
        {
            cout << "\nTidak ada proses yang sedang berjalan!" << endl;
            return;
        }

        cout << "\n========== TAHAP PROSES PENGERJAAN ==========" << endl;
        for (int i = 0; i <= top; i++)
        {
            cout << (i + 1) << ". " << proses[i] << endl;
        }
        cout << "==============================================" << endl;
    }
};

// ============ BINARY SEARCH TREE - TRANSAKSI ============
class BSTTransaksi
{
private:
    Node *root;

    Node *insertBSTHelper(Node *node, int id, string nama)
    {
        if (node == NULL)
        {
            Node *nodeBaru = new Node();
            nodeBaru->idTransaksi = id;
            nodeBaru->nama = nama;
            nodeBaru->left = NULL;
            nodeBaru->right = NULL;
            return nodeBaru;
        }

        if (id < node->idTransaksi)
        {
            node->left = insertBSTHelper(node->left, id, nama);
        }
        else if (id > node->idTransaksi)
        {
            node->right = insertBSTHelper(node->right, id, nama);
        }
        else
        {
            cout << "ID transaksi sudah ada!" << endl;
            return node;
        }
        return node;
    }

    Node *searchBSTHelper(Node *node, int id)
    {
        if (node == NULL)
        {
            return NULL;
        }

        if (id == node->idTransaksi)
        {
            return node;
        }
        else if (id < node->idTransaksi)
        {
            return searchBSTHelper(node->left, id);
        }
        else
        {
            return searchBSTHelper(node->right, id);
        }
    }

    void inorderTraversalHelper(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        inorderTraversalHelper(node->left);
        cout << "ID: " << node->idTransaksi << " | Nama: " << node->nama << endl;
        inorderTraversalHelper(node->right);
    }

    void deleteTreeHelper(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        deleteTreeHelper(node->left);
        deleteTreeHelper(node->right);
        delete node;
    }

public:
    BSTTransaksi()
    {
        root = NULL;
    }

    // Fungsi untuk insert ke BST
    void insertBST(int id, string nama)
    {
        root = insertBSTHelper(root, id, nama);
        cout << "Data transaksi ID " << id << " berhasil ditambahkan ke BST" << endl;
    }

    // Fungsi untuk search di BST
    bool searchBST(int id)
    {
        Node *hasil = searchBSTHelper(root, id);
        if (hasil != NULL)
        {
            cout << "Transaksi ditemukan - ID: " << hasil->idTransaksi
                 << " | Nama: " << hasil->nama << endl;
            return true;
        }
        else
        {
            cout << "Transaksi dengan ID " << id << " tidak ditemukan di BST!" << endl;
            return false;
        }
    }

    // Fungsi untuk inorder traversal (Left-Root-Right)
    void inorderTraversal()
    {
        if (root == NULL)
        {
            cout << "\nBST kosong!" << endl;
            return;
        }

        cout << "\n========== INORDER TRAVERSAL (SORTED) ==========" << endl;
        inorderTraversalHelper(root);
        cout << "================================================" << endl;
    }

    // Destructor
    ~BSTTransaksi()
    {
        deleteTreeHelper(root);
    }
};

void tampilMenuUtama()
{
    cout << "\n========================================" << endl;
    cout << "   SISTEM LAUNDRY ONLINE - WASHMATE" << endl;
    cout << "========================================" << endl;
    cout << "1. Input Transaksi" << endl;
    cout << "2. Proses Transaksi" << endl;
    cout << "3. Lihat Riwayat Transaksi" << endl;
    cout << "4. Lihat Riwayat Proses" << endl;
    cout << "5. Cari Transaksi" << endl;
    cout << "6. Keluar" << endl;
    cout << "========================================" << endl;
    cout << "Pilihan: ";
}

void inputTransaksi(QueuePelanggan &antrian, HistoriTransaksi &riwayat, MenuArray &menu, BSTTransaksi &bst)
{
    int id;
    string nama;
    int nomorLayanan;
    string layanan;
    float berat;
    int totalHarga;

    cout << "\n===== INPUT TRANSAKSI BARU =====" << endl;

    cout << "Masukkan ID transaksi: ";
    cin >> id;
    cin.ignore();

    cout << "Masukkan nama pelanggan: ";
    getline(cin, nama);

    cout << "Pilih nomor layanan (1-" << menu.getJumlahLayanan() << "): ";
    cin >> nomorLayanan;
    cin.ignore();

    layanan = menu.getNamaLayananByNomor(nomorLayanan);
    if (layanan == "")
    {
        cout << "Nomor layanan tidak valid!" << endl;
        return;
    }

    cout << "Masukkan berat pakaian (kg): ";
    cin >> berat;

    int hargaLayanan = menu.getHargaByNomor(nomorLayanan);
    totalHarga = (int)(berat * hargaLayanan);

    cout << "Total Harga: Rp" << totalHarga << endl;

    // Tambah ke queue antrian
    antrian.enqueue(id, nama, layanan);

    // Tambah ke riwayat transaksi
    riwayat.tambahTransaksi(id, nama, layanan, berat, totalHarga);

    // Tambah ke BST
    bst.insertBST(id, nama);

    cout << "Transaksi berhasil diinput!" << endl;
}

void prosesTransaksi(QueuePelanggan &antrian, StackProses &stackProses)
{
    cout << "\n===== PROSES TRANSAKSI =====" << endl;

    Pelanggan *pelanggan = antrian.dequeue();

    if (pelanggan != NULL)
    {
        cout << "\nMasukkan tahap proses untuk " << pelanggan->nama << ":" << endl;
        cout << "1. Pemeriksaan Pakaian" << endl;
        cout << "2. Pencucian" << endl;
        cout << "3. Pengeringan" << endl;
        cout << "4. Setrika" << endl;
        cout << "5. Pembungkusan" << endl;

        int pilih;
        cout << "Pilih tahap (1-5): ";
        cin >> pilih;
        cin.ignore();

        string tahap;
        switch (pilih)
        {
        case 1:
            tahap = "Pemeriksaan Pakaian";
            break;
        case 2:
            tahap = "Pencucian";
            break;
        case 3:
            tahap = "Pengeringan";
            break;
        case 4:
            tahap = "Setrika";
            break;
        case 5:
            tahap = "Pembungkusan";
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
        }

        stackProses.pushProses(tahap + " - " + pelanggan->nama);
        delete pelanggan;
    }
}

void lihatRiwayatTransaksi(HistoriTransaksi &riwayat)
{
    cout << "\n";
    riwayat.tampilHistori();
}

void lihatRiwayatProses(StackProses &stackProses)
{
    cout << "\n";
    stackProses.tampilProses();
}

void cariTransaksi(HistoriTransaksi &riwayat)
{
    int id;
    cout << "\n===== CARI TRANSAKSI =====" << endl;
    cout << "Masukkan ID transaksi yang dicari: ";
    cin >> id;
    cin.ignore();
    cout << endl;
    riwayat.cariTransaksiByID(id);
}

int main()
{
    MenuArray menu;
    QueuePelanggan antrian;
    HistoriTransaksi riwayat;
    StackProses stackProses;
    BSTTransaksi bst;

    // Setup menu layanan default
    menu.tambahLayanan("Cuci Kering", 7000);
    menu.tambahLayanan("Setrika", 5000);
    menu.tambahLayanan("Cuci Selimut", 15000);
    menu.tambahLayanan("Express", 12000);

    // Tampilkan menu layanan di awal
    menu.tampilMenu();

    int pilihan;

    while (true)
    {
        tampilMenuUtama();
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1)
        {
            inputTransaksi(antrian, riwayat, menu, bst);
        }
        else if (pilihan == 2)
        {
            prosesTransaksi(antrian, stackProses);
        }
        else if (pilihan == 3)
        {
            lihatRiwayatTransaksi(riwayat);
        }
        else if (pilihan == 4)
        {
            lihatRiwayatProses(stackProses);
        }
        else if (pilihan == 5)
        {
            cariTransaksi(riwayat);
        }
        else if (pilihan == 6)
        {
            cout << "\nTerima kasih telah menggunakan WASHMATE!" << endl;
            break;
        }
        else
        {
            cout << "\nPilihan tidak valid! Coba lagi." << endl;
        }
    }

    return 0;
}
