#include <iostream>
#include <string>

using namespace std;

// struck
struct DetailLayanan
{
    string namaLayanan;
    int hargaPerKg;
};

struct Pelanggan
{
    int id;
    string nama;
    string noTelp;
    string namaPaket;
    float beratKg;
    int totalBayar;
    int tahapan;
};

// untuk status
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

// array - menu
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
        else
        {
            cout << "Daftar menu sudah penuh!\n";
        }
    }

    void tampilkanDaftar()
    {
        cout << "\n--- PILIH LAYANAN ---\n";
        for (int i = 0; i < jumlahMenu; i++)
        {
            cout << i + 1 << ". ";
            cout << daftarMenu[i].namaLayanan;
            cout << " \t[Rp " << daftarMenu[i].hargaPerKg << " / kg]\n";
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

    int getJumlah()
    {
        return jumlahMenu;
    }
};

// penyelesaian order - linkedlist
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
    LinkedListArsip()
    {
        head = NULL;
    }

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
            // Menampilkan ID juga agar terlihat bedanya walau nama sama
            cout << "[ID:" << temp->data.id << "] " << temp->data.nama
                 << " | Rp" << temp->data.totalBayar << endl;
            temp = temp->next;
        }
    }
};

// binary search tree - pencarian
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

        if (p.id < node->data.id)
            node->left = insertRec(node->left, p);
        else if (p.id > node->data.id)
            node->right = insertRec(node->right, p);

        return node;
    }

    void searchByNameRec(NodeBST *node, string namaCari, bool &found)
    {
        if (node == NULL)
            return;
        if (node->data.nama == namaCari)
        {
            found = true;
            cout << "--------------------------------\n";
            cout << "ID Order\t: " << node->data.id << endl;
            cout << "Nama\t\t: " << node->data.nama << endl;
            cout << "No Telp\t\t: " << node->data.noTelp << endl;
            cout << "Paket\t\t: " << node->data.namaPaket << endl;
            cout << "Status\t\t: " << getStatusTeks(node->data.tahapan) << endl;
        }

        searchByNameRec(node->left, namaCari, found);
        searchByNameRec(node->right, namaCari, found);
    }

public:
    BSTPencarian()
    {
        root = NULL;
    }
    void insert(Pelanggan p)
    {
        root = insertRec(root, p);
    }
    void cariNama(string nama)
    {
        bool found = false;
        cout << "\n=== HASIL PENCARIAN : " << nama << " ===\n";
        searchByNameRec(root, nama, found);
        if (!found)
        {
            cout << "Data tidak ditemukan.\n";
        }
    }
};

// stack - proses
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
        system("cls");
        cout << "\nAntrian ID " << top->data.id << " (" << top->data.nama << ") di proses!\n";
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
                cout << ">> Status Baru : " << getStatusTeks(top->data.tahapan) << endl;
            }
            else
                cout << ">> Sudah Selesai\n";
        }
        else if (aksi == 2)
        {
            if (top->data.tahapan > 1)
            {
                top->data.tahapan--;
                cout << ">> Status mundur ke : " << getStatusTeks(top->data.tahapan) << endl;
            }
            else
                cout << ">> Tidak bisa mundur lagi\n";
        }
    }

    bool isTopFinished()
    {
        return (!isEmpty() && top->data.tahapan == 4);
    }

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

    void mejaPalingAtas()
    {
        cout << "\n=== PROSES YANG SEDANG BERJALAN ===\n";
        NodeStack *curr = top;
        cout << "-> [ID:" << curr->data.id << "] " << curr->data.nama << " [" << getStatusTeks(curr->data.tahapan) << "] <-\n";
    }

    void lihatMejaKerja()
    {
        cout << "\n=== PROSES YANG SEDANG BERJALAN ===\n";
        NodeStack *curr = top;
        while (curr != NULL)
        {
            cout << "-> [ID:" << curr->data.id << "] " << curr->data.nama << " [" << getStatusTeks(curr->data.tahapan) << "]\n";
            curr = curr->next;
        }
    }
};

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
            cout << "-> [ID:" << temp->data.id << "] " << temp->data.nama << " | Rp " << temp->data.totalBayar << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    ManajemenMenu menu;
    menu.tambahMenu("Cuci Komplit", 5000);
    menu.tambahMenu("Cuci Selimut", 7000);
    menu.tambahMenu("Setrika Saja", 4000);
    menu.tambahMenu("Cuci Express", 10000);
    menu.tambahMenu("Cuci & Setrika", 8000);

    QueueAntrian q;
    StackProses s;
    LinkedListArsip ll;
    BSTPencarian bst;

    int pilihan, idGen = 1001;

    while (true)
    {
        cout << "\n======================================";
        cout << "\n\tSISTEM LAUNDRY WASHMATE";
        cout << "\n======================================";
        cout << "\n1. Pelanggan Baru";
        cout << "\n2. Proses Antrian";
        cout << "\n3. Update Status";
        cout << "\n4. Selesai & Arsip";
        cout << "\n5. Monitoring";
        cout << "\n6. Cari Riwayat Nama";
        cout << "\n7. Keluar";
        cout << "\nPilihan: ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            Pelanggan p;
            p.id = idGen++;

            cout << "\nMasukkan Nama Pelanggan : ";
            cin.ignore();
            getline(cin, p.nama);

            cout << "Nomor Telepon   : ";
            getline(cin, p.noTelp);

            system("cls");
            cout << "---   PELANGGAN   ---\n";
            cout << "ID Order : " << p.id << endl;
            cout << "Nama     : " << p.nama;
            menu.tampilkanDaftar();
            cout << "\nPilih Layanan : ";
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
                system("cls");
                cout << "======================================";
                cout << "\nStruk Pembayaran WashMate";
                cout << "\n======================================";
                cout << "\nID Order\t: " << p.id;
                cout << "\nNama Pelanggan\t: " << p.nama;
                cout << "\nLayanan\t\t: " << p.namaPaket;
                cout << "\nBerat Laundry\t: " << p.beratKg << " Kg";
                cout << "\nTotal Bayar\t: Rp " << p.totalBayar << endl;
                q.enqueue(p);
                cout << "Berhasil Masuk Antrian!";
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
                cout << "\nAntrian Kosong.\n";
        }
        else if (pilihan == 3)
        {
            if (!s.isEmpty())
            {
                system("cls");
                s.mejaPalingAtas();
                cout << "\n[1] Lanjutkan Tahapan\n";
                cout << "[2] Mundur Tahapan\n";
                cout << "Pilih Aksi: ";
                int sub;
                cin >> sub;
                s.kontrolTahapan(sub);
            }
            else
            {
                system("cls");
                cout << "\nTidak ada proses saat ini.\n";
            }
        }
        else if (pilihan == 4)
        {
            if (s.isEmpty())
            {
                system("cls");
                cout << "\nTidak ada proses yang berjalan\n";
            }
            else if (s.isTopFinished())
            {
                Pelanggan p = s.popFinal();
                ll.simpanPermanen(p);
                bst.insert(p);
                system("cls");
                cout << "=== Pesanan Selesai! ===\n";
                cout << "Order ID " << p.id << " (" << p.nama << ") Berhasil Disimpan";
            }
            else
            {
                system("cls");
                cout << "\nPesanan paling atas belum status 'Selesai/Terkirim'\n";
            }
        }
        else if (pilihan == 5)
        {
            system("cls");
            q.lihatAntrian();
            s.lihatMejaKerja();
            ll.tampilkanLaporan();
        }
        else if (pilihan == 6)
        {
            string cari;
            system("cls");
            cout << "\n=== PENCARIAN RIWAYAT NAMA ===\n";
            cout << "Masukkan Nama yang dicari: ";
            cin.ignore();
            getline(cin, cari);
            bst.cariNama(cari);
        }
        else if (pilihan == 7)
        {
            cout << "Keluar dari program. Data di-reset.\n";
            break;
        }
    }
    return 0;
}