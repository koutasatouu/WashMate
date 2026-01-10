#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ==========================================
// 1. STRUCT & HELPER
// ==========================================
struct DetailLayanan
{
    string namaLayanan;
    int hargaPerKg;
};

struct Pelanggan
{
    int id;
    string nama; // KEY UTAMA UNTUK BST SEKARANG
    string noTelp;
    string namaPaket;
    float beratKg;
    int totalBayar;
    int tahapan;
};

string getStatusTeks(int t)
{
    if (t == 0)
        return "Menunggu Antrian";
    if (t == 1)
        return "Sedang Dicuci";
    if (t == 2)
        return "Sedang Disetrika";
    if (t == 3)
        return "Packing / Siap Kirim";
    if (t == 4)
        return "SUDAH TERKIRIM (Selesai)";
    return "Unknown";
}

// ==========================================
// 2. CLASS MENU (ARRAY)
// ==========================================
class ManajemenMenu
{
private:
    DetailLayanan daftarMenu[10];
    int jumlahMenu;

public:
    ManajemenMenu() { jumlahMenu = 0; }

    void tambahMenu(string nama, int harga)
    {
        if (jumlahMenu < 10)
        {
            daftarMenu[jumlahMenu].namaLayanan = nama;
            daftarMenu[jumlahMenu].hargaPerKg = harga;
            jumlahMenu++;
        }
    }

    void tampilkanDaftar()
    {
        cout << "\n--- PILIH LAYANAN ---\n";
        for (int i = 0; i < jumlahMenu; i++)
        {
            cout << i + 1 << ". " << daftarMenu[i].namaLayanan
                 << " \t[Rp " << daftarMenu[i].hargaPerKg << " /kg]\n";
        }
    }

    DetailLayanan getLayanan(int index)
    {
        if (index >= 0 && index < jumlahMenu)
            return daftarMenu[index];
        DetailLayanan k;
        k.namaLayanan = "";
        return k;
    }

    int getJumlah() { return jumlahMenu; }
};

// ==========================================
// 3. LINKED LIST (ARSIP)
// ==========================================
struct NodeLL
{
    Pelanggan data;
    NodeLL *next;
};

class LinkedListArsip
{
private:
    NodeLL *head;

public:
    LinkedListArsip() { head = NULL; }

    void simpanPermanen(Pelanggan p)
    {
        NodeLL *newNode = new NodeLL();
        newNode->data = p;
        newNode->next = NULL;
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            NodeLL *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    void tampilkanLaporan()
    {
        cout << "\n=== LAPORAN TRANSAKSI SELESAI ===\n";
        NodeLL *temp = head;
        while (temp != NULL)
        {
            cout << "[LUNAS] " << temp->data.nama << " | ID:" << temp->data.id
                 << " | Rp" << temp->data.totalBayar << endl;
            temp = temp->next;
        }
    }

    // CEK DUPLIKAT DI ARSIP
    bool isNamaExist(string namaCari)
    {
        NodeLL *temp = head;
        while (temp != NULL)
        {
            if (temp->data.nama == namaCari)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void saveToFile()
    {
        ofstream file("laporan_final.txt");
        NodeLL *temp = head;
        while (temp != NULL)
        {
            file << temp->data.id << "|" << temp->data.nama << "|LUNAS" << endl;
            temp = temp->next;
        }
        file.close();
    }
};

// ==========================================
// 4. BST (PENCARIAN VIA NAMA) - UPDATED
// ==========================================
struct NodeBST
{
    Pelanggan data;
    NodeBST *left, *right;
};

class BSTPencarian
{
private:
    NodeBST *root;

    NodeBST *insertRec(NodeBST *node, Pelanggan p)
    {
        if (node == NULL)
        {
            NodeBST *n = new NodeBST();
            n->data = p;
            n->left = n->right = NULL;
            return n;
        }
        // LOGIKA SORTING BERDASARKAN STRING (Alphabetical)
        if (p.nama < node->data.nama)
            node->left = insertRec(node->left, p);
        else if (p.nama > node->data.nama)
            node->right = insertRec(node->right, p);

        return node;
    }

    void searchRec(NodeBST *node, string namaCari)
    {
        if (node == NULL)
        {
            cout << "Nama '" << namaCari << "' tidak ditemukan di arsip.\n";
            return;
        }

        if (node->data.nama == namaCari)
        {
            cout << "\n=== HASIL PENCARIAN (BST BY NAME) ===\n";
            cout << "Nama     : " << node->data.nama << endl;
            cout << "ID       : " << node->data.id << endl;
            cout << "No Telp  : " << node->data.noTelp << endl;
            cout << "Paket    : " << node->data.namaPaket << endl;
            cout << "Status   : " << getStatusTeks(node->data.tahapan) << endl;
        }
        // Logic pencarian string (Kiri lebih kecil abjadnya, Kanan lebih besar)
        else if (namaCari < node->data.nama)
        {
            searchRec(node->left, namaCari);
        }
        else
        {
            searchRec(node->right, namaCari);
        }
    }

public:
    BSTPencarian() { root = NULL; }

    void insert(Pelanggan p) { root = insertRec(root, p); }

    // Parameter pencarian sekarang STRING
    void cariNama(string nama) { searchRec(root, nama); }
};

// ==========================================
// 5. STACK (MEJA PROSES)
// ==========================================
struct NodeStack
{
    Pelanggan data;
    NodeStack *next;
};

class StackProses
{
private:
    NodeStack *top;

public:
    StackProses() { top = NULL; }
    bool isEmpty() { return top == NULL; }

    void pushMasukKerja(Pelanggan p)
    {
        NodeStack *newNode = new NodeStack();
        newNode->data = p;
        newNode->data.tahapan = 1;
        newNode->next = top;
        top = newNode;
    }

    void kontrolTahapan(int aksi)
    {
        if (isEmpty())
        {
            cout << "Meja kerja kosong!\n";
            return;
        }
        if (aksi == 1)
        {
            if (top->data.tahapan < 4)
            {
                top->data.tahapan++;
                cout << ">> Status naik ke: " << getStatusTeks(top->data.tahapan) << endl;
            }
            else
                cout << ">> Sudah Final.\n";
        }
        else if (aksi == 2)
        {
            if (top->data.tahapan > 1)
            {
                top->data.tahapan--;
                cout << ">> Status mundur ke: " << getStatusTeks(top->data.tahapan) << endl;
            }
            else
                cout << ">> Tidak bisa mundur lagi.\n";
        }
    }

    bool isTopFinished() { return (!isEmpty() && top->data.tahapan == 4); }

    Pelanggan popFinal()
    {
        if (isEmpty())
        {
            Pelanggan k;
            k.id = -1;
            return k;
        }
        NodeStack *temp = top;
        Pelanggan p = temp->data;
        top = top->next;
        delete temp;
        return p;
    }

    void infoTop()
    {
        if (!isEmpty())
            cout << "[Top Stack]: " << top->data.nama << " (" << getStatusTeks(top->data.tahapan) << ")\n";
    }

    void lihatMejaKerja()
    {
        cout << "\n=== MEJA KERJA (STACK) ===\n";
        NodeStack *curr = top;
        while (curr != NULL)
        {
            cout << "-> " << curr->data.nama << " [" << getStatusTeks(curr->data.tahapan) << "]\n";
            curr = curr->next;
        }
    }

    // CEK DUPLIKAT DI STACK
    bool isNamaExist(string namaCari)
    {
        NodeStack *curr = top;
        while (curr != NULL)
        {
            if (curr->data.nama == namaCari)
                return true;
            curr = curr->next;
        }
        return false;
    }
};

// ==========================================
// 6. QUEUE (ANTRIAN)
// ==========================================
struct NodeQueue
{
    Pelanggan data;
    NodeQueue *next;
};

class QueueAntrian
{
private:
    NodeQueue *front, *rear;

public:
    QueueAntrian() { front = rear = NULL; }
    bool isEmpty() { return front == NULL; }

    void enqueue(Pelanggan p)
    {
        NodeQueue *newNode = new NodeQueue();
        p.tahapan = 0;
        newNode->data = p;
        newNode->next = NULL;
        if (isEmpty())
            front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Pelanggan dequeue()
    {
        if (isEmpty())
        {
            Pelanggan p;
            p.id = -1;
            return p;
        }
        NodeQueue *temp = front;
        Pelanggan p = temp->data;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        delete temp;
        return p;
    }

    void lihatAntrian()
    {
        cout << "\n=== ANTRIAN (QUEUE) ===\n";
        NodeQueue *temp = front;
        while (temp != NULL)
        {
            cout << "-> " << temp->data.nama << endl;
            temp = temp->next;
        }
    }

    // CEK DUPLIKAT DI QUEUE
    bool isNamaExist(string namaCari)
    {
        NodeQueue *temp = front;
        while (temp != NULL)
        {
            if (temp->data.nama == namaCari)
                return true;
            temp = temp->next;
        }
        return false;
    }
};

// ==========================================
// MAIN PROGRAM
// ==========================================
int main()
{
    ManajemenMenu menu;
    menu.tambahMenu("Cuci Komplit", 6000);
    menu.tambahMenu("Cuci Kilat", 10000);
    menu.tambahMenu("Setrika Saja", 4000);

    QueueAntrian q;
    StackProses s;
    LinkedListArsip ll;
    BSTPencarian bst;

    int pilihan, idGen = 1001;

    while (true)
    {
        cout << "\n=============================================";
        cout << "\n   SISTEM LAUNDRY (Unique Name & BST Name)";
        cout << "\n=============================================";
        cout << "\n1. Pelanggan Baru";
        cout << "\n2. Proses Antrian (Q -> S)";
        cout << "\n3. Update Status (Stack)";
        cout << "\n4. Selesai & Arsip (S -> LL & BST)";
        cout << "\n5. Monitoring";
        cout << "\n6. Cari Nama (BST)";
        cout << "\n7. Keluar";
        cout << "\nPilihan: ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            Pelanggan p;
            p.id = idGen++;

            // --- VALIDASI NAMA UNIK ---
            bool namaValid = false;
            do
            {
                cout << "\nMasukkan Nama Pelanggan : ";
                cin.ignore();
                getline(cin, p.nama);

                // Cek di semua tempat (Queue, Stack, Linked List)
                if (q.isNamaExist(p.nama) || s.isNamaExist(p.nama) || ll.isNamaExist(p.nama))
                {
                    cout << "ERROR: Nama '" << p.nama << "' sudah ada di sistem! Harap gunakan nama lain.\n";
                }
                else
                {
                    namaValid = true;
                }
            } while (!namaValid);
            // ---------------------------

            cout << "Nomor Telepon  : ";
            getline(cin, p.noTelp);

            menu.tampilkanDaftar();
            cout << "Pilih Layanan (Nomor): ";
            int pick;
            cin >> pick;

            if (pick > 0 && pick <= menu.getJumlah())
            {
                DetailLayanan selected = menu.getLayanan(pick - 1);
                p.namaPaket = selected.namaLayanan;
                int hargaPerKg = selected.hargaPerKg;

                cout << "Berat Laundry (Kg) : ";
                cin >> p.beratKg;
                p.totalBayar = (int)(p.beratKg * hargaPerKg);
                cout << ">> Total Bayar: Rp " << p.totalBayar << endl;

                q.enqueue(p);
                cout << "Berhasil Masuk Antrian.\n";
            }
        }
        else if (pilihan == 2)
        {
            if (!q.isEmpty())
            {
                Pelanggan p = q.dequeue();
                s.pushMasukKerja(p);
            }
            else
                cout << "Antrian Kosong.\n";
        }
        else if (pilihan == 3)
        {
            if (!s.isEmpty())
            {
                s.infoTop();
                cout << "   [1] Next Step  [2] Undo Step: ";
                int sub;
                cin >> sub;
                s.kontrolTahapan(sub);
            }
            else
                cout << "Stack Kosong.\n";
        }
        else if (pilihan == 4)
        {
            if (s.isEmpty())
                cout << "Stack Kosong.\n";
            else if (s.isTopFinished())
            {
                Pelanggan p = s.popFinal();
                ll.simpanPermanen(p); // Simpan ke Laporan
                bst.insert(p);        // Indexing ke BST berdasarkan Nama
                cout << "Data berhasil diarsipkan.\n";
            }
            else
                cout << "Belum selesai (Status belum Terkirim).\n";
        }
        else if (pilihan == 5)
        {
            q.lihatAntrian();
            s.lihatMejaKerja();
            ll.tampilkanLaporan();
        }
        else if (pilihan == 6)
        {
            string cari;
            cout << "Masukkan Nama yang dicari: ";
            cin.ignore();
            getline(cin, cari);
            bst.cariNama(cari); // Cari String
        }
        else if (pilihan == 7)
        {
            ll.saveToFile();
            break;
        }
    }
    return 0;
}