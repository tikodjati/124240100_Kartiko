
#include <iostream>
#include <string>
using namespace std;

struct BookNode {
    string judul;
    string pengarang;
    int tahun;
    BookNode *left, *right;
};

struct StackNode {
    string judul;
    string pengarang;
    int tahun;
    string aksi;
    StackNode *next;
};

BookNode* root = NULL;
StackNode* undoStack = NULL;

BookNode* createBook(string judul, string pengarang, int tahun) {
    BookNode* newNode = new BookNode;
    newNode->judul = judul;
    newNode->pengarang = pengarang;
    newNode->tahun = tahun;
    newNode->left = newNode->right = NULL;
    return newNode;
}

StackNode* createStackNode(string judul, string pengarang, int tahun, string aksi) {
    StackNode* node = new StackNode;
    node->judul = judul;
    node->pengarang = pengarang;
    node->tahun = tahun;
    node->aksi = aksi;
    node->next = NULL;
    return node;
}

void pushUndo(string judul, string pengarang, int tahun, string aksi) {
    StackNode* newNode = createStackNode(judul, pengarang, tahun, aksi);
    newNode->next = undoStack;
    undoStack = newNode;
}

BookNode* insertBook(BookNode* node, string judul, string pengarang, int tahun, bool &success) {
    if (node == NULL) {
        success = true;
        return createBook(judul, pengarang, tahun);
    }
    if (judul == node->judul) {
        success = false;
        return node;
    }
    if (judul < node->judul)
        node->left = insertBook(node->left, judul, pengarang, tahun, success);
    else
        node->right = insertBook(node->right, judul, pengarang, tahun, success);
    return node;
}

void displayDescending(BookNode* node) {
    if (node == NULL) return;
    displayDescending(node->right);
    cout << node->judul << " - " << node->pengarang << " - " << node->tahun << endl;
    displayDescending(node->left);
}

BookNode* findMin(BookNode* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

BookNode* deleteBook(BookNode* node, string judul, bool &found, string &pengarang, int &tahun) {
    if (node == NULL) return NULL;
    if (judul < node->judul)
        node->left = deleteBook(node->left, judul, found, pengarang, tahun);
    else if (judul > node->judul)
        node->right = deleteBook(node->right, judul, found, pengarang, tahun);
    else {
        found = true;
        pengarang = node->pengarang;
        tahun = node->tahun;
        if (node->left == NULL && node->right == NULL) {
            delete node;
            return NULL;
        } else if (node->left == NULL) {
            BookNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            BookNode* temp = node->left;
            delete node;
            return temp;
        } else {
            BookNode* temp = findMin(node->right);
            node->judul = temp->judul;
            node->pengarang = temp->pengarang;
            node->tahun = temp->tahun;
            node->right = deleteBook(node->right, temp->judul, found, pengarang, tahun);
        }
    }
    return node;
}

BookNode* insertUndo(BookNode* node, string judul, string pengarang, int tahun) {
    bool dummy = false;
    return insertBook(node, judul, pengarang, tahun, dummy);
}

BookNode* undo(BookNode* node) {
    if (undoStack == NULL) {
        cout << "Tidak ada aksi untuk di-undo.\n";
        return node;
    }
    StackNode* top = undoStack;
    undoStack = undoStack->next;

    if (top->aksi == "ADD") {
        bool found = false;
        string dummyPengarang;
        int dummyTahun;
        node = deleteBook(node, top->judul, found, dummyPengarang, dummyTahun);
        cout << "Undo tambah buku berhasil.\n";
    } else if (top->aksi == "DELETE") {
        node = insertUndo(node, top->judul, top->pengarang, top->tahun);
        cout << "Undo hapus buku berhasil.\n";
    }
    delete top;
    return node;
}

int main() {
    int pilihan;
    string judul, pengarang;
    int tahun;

    do {
        cout << "\n=== Menu Perpustakaan ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Buku (Z - A)\n";
        cout << "3. Hapus Buku\n";
        cout << "4. Undo Aksi Terakhir\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Judul Buku: ";
                getline(cin, judul);
                cout << "Pengarang: ";
                getline(cin, pengarang);
                cout << "Tahun Terbit: ";
                cin >> tahun;
                cin.ignore();
                {
                    bool success = false;
                    root = insertBook(root, judul, pengarang, tahun, success);
                    if (success) {
                        pushUndo(judul, pengarang, tahun, "ADD");
                        cout << "Buku berhasil ditambahkan.\n";
                    } else {
                        cout << "Judul sudah ada.\n";
                    }
                }
                break;
            case 2:
                displayDescending(root);
                break;
            case 3:
                cout << "Judul Buku yang ingin dihapus: ";
                getline(cin, judul);
                {
                    bool found = false;
                    string penghapus;
                    int thn;
                    root = deleteBook(root, judul, found, penghapus, thn);
                    if (found) {
                        pushUndo(judul, penghapus, thn, "DELETE");
                        cout << "Buku berhasil dihapus.\n";
                    } else {
                        cout << "Buku tidak ditemukan.\n";
                    }
                }
                break;
            case 4:
                root = undo(root);
                break;
            case 5:
                cout << "Keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}
