#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>  
using namespace std;
string toStr(int x)
{
    ostringstream ss;
    ss << x;
    return ss.str();
}

struct Log
{
    string message;
    Log* next;

    Log(string m)
    {
        message = m;
        next = NULL;
    }
};
Log* logHead = NULL;
Log* logTail = NULL;
void logEvent(string msg)
{
    Log* newLog = new Log(msg);
    if (!logHead)
    {
        logHead = logTail = newLog;
    }
    else
    {
        logTail->next = newLog;
        logTail = newLog;
    }
}
void generateReport()
{
    for (int i = 0; i < 115; i++)
    {
        cout << "=";
    }
    cout << endl;
    cout << "SESSION REPORT" << endl;
    cout << "Actions performed during this session:" << endl;
    Log* temp = logHead;
    while (temp)
    {
        cout << "- " << temp->message << endl;
        temp = temp->next;
    }
    for (int i = 0; i < 115; i++)
    {
        cout << "=";
    }
    cout << endl;
}

//Item Structure
struct Item
{
    int id;
    string name;
    string type;
    int quantity;
    Item* next;
    Item(int i, string n, string t, int q)
    {
        id = i;
        name = n;
        type = t;
        quantity = q;
        next = NULL;
    }
};

//Inventory class
class Inventory
{
private:
    Item* head;
public:
    Inventory()
    {
        head = NULL;
        addItem(101, "Glock17", "Handgun", 10);
        addItem(102, "M1911", "Handgun", 55);
        addItem(103, "DesertEagle", "Handgun", 34);
        addItem(104, "Beretta M9", "Handgun", 44);
        addItem(105, "SIG P226", "Handgun", 20);
        addItem(201, "AK47", "Rifle", 20);
        addItem(202, "M4A1", "Rifle", 15);
        addItem(203, "HK416", "Rifle", 12);
        addItem(204, "FN Scar-L", "Rifle", 15);
        addItem(205, "Steyr AUG", "Rifle", 30);
        addItem(301, "KevlarVest", "Armor", 8);
        addItem(302, "SteelPlate", "Armor", 6);
        addItem(303, "Kevlar Helmet", "Armor", 24);
        addItem(401, "9mm", "Ammo", 200);
        addItem(402, "5.56x45mm", "Ammo", 150);
        addItem(403, "7.62x39mm", "Ammo", 180);
        addItem(404, "12 Gauge", "Ammo", 300);
        addItem(405, ".50 BMG", "Ammo", 295);
    }
    Item* getHead()
    {
        return head;
    }
    void addItem(int id, string name, string type, int qty)
    {
        Item* newItem = new Item(id, name, type, qty);
        newItem->next = head;
        head = newItem;
        logEvent("Added item: " + name + " (" + type + ")");
    }
    Item* searchRec(Item* node, int id)
    {
        if (!node) return NULL;
        if (node->id == id) return node;
        return searchRec(node->next, id);
    }
    Item* searchItem(int id)
    {
        Item* r = searchRec(head, id);
        if (r) logEvent("Searched item ID " + toStr(id) + " (FOUND)");
        else   logEvent("Searched item ID " + toStr(id) + " (NOT FOUND)");
        return r;
    }
    int typeRank(string t)
    {
        if (t == "Handgun")
        {
            return 1;
        }
        if (t == "Rifle")
        {
            return 2;
        }
        if (t == "Armor")
        {
            return 3;
        }
        return 4;
    }
    void sortByName()
    {
        bool swapped;
        do {
            swapped = false;
            Item* curr = head;
            while (curr && curr->next)
            {
                if (curr->name > curr->next->name)
                {
                    swap(curr->id, curr->next->id);
                    swap(curr->name, curr->next->name);
                    swap(curr->type, curr->next->type);
                    swap(curr->quantity, curr->next->quantity);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);

        logEvent("Sorted inventory by NAME");
    }
    void sortByType()
    {
        bool swapped;
        do {
            swapped = false;
            Item* curr = head;
            while (curr && curr->next)
            {
                if (typeRank(curr->type) > typeRank(curr->next->type))
                {
                    swap(curr->id, curr->next->id);
                    swap(curr->name, curr->next->name);
                    swap(curr->type, curr->next->type);
                    swap(curr->quantity, curr->next->quantity);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);

        logEvent("Sorted inventory by TYPE");
    }
    void sortByID()
    {
        bool swapped;
        do {
            swapped = false;
            Item* curr = head;
            while (curr && curr->next)
            {
                if (curr->id > curr->next->id)
                {
                    swap(curr->id, curr->next->id);
                    swap(curr->name, curr->next->name);
                    swap(curr->type, curr->next->type);
                    swap(curr->quantity, curr->next->quantity);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);

        logEvent("Sorted inventory by ID");
    }
    bool removeQuantity(int id, int qty, bool autoRestock)
    {
        Item* item = searchItem(id);
        if (!item)
        {
            cout << "Item not found!\n";
            return false;
        }
        if (item->quantity >= qty)
        {
            item->quantity -= qty;
            logEvent("Removed " + toStr(qty) + " units of ID " + toStr(id));
        }
        else
        {
            int removed = item->quantity;
            item->quantity = 0;

            logEvent("Insufficient stock for ID " + toStr(id) +
                ". Removed remaining " + toStr(removed));

            cout << "Insufficient stock. Removed " << removed << endl;

            if (autoRestock)
            {
                item->quantity = 50;
                logEvent("Auto-restocked ID " + toStr(id) + " to quantity 50");
                cout << "Item auto-restocked to 50.\n";
            }
        }
        return true;
    }
    void displayCategory(string c)
    {
        Item* temp = head;
        while (temp)
        {
            if (temp->type == c)
                cout << temp->id << "\t| Name: " << temp->name << "\t| Qty: " << temp->quantity << endl;
            temp = temp->next;
        }
    }
    void displayAll()
    {
        for (int i = 0; i < 115; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << "HANDGUNS: " << endl;
        displayCategory("Handgun");
        for (int i = 0; i < 115; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << "RIFLES: " << endl;
        displayCategory("Rifle");
        for (int i = 0; i < 115; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << "ARMOR:" << endl;
        displayCategory("Armor");
        for (int i = 0; i < 115; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << "AMMO:" << endl;
        displayCategory("Ammo");
        for (int i = 0; i < 115; i++)
        {
            cout << "-";
        }
        cout << endl;
        logEvent("Displayed inventory");
    }
};

// Procurement
class Procurement
{
private:
    Inventory* inv;
public:
    Procurement(Inventory* i)
    {
        inv = i;
    }
    void addNewItem()
    {
        int id, qty;
        string name, type;
        cout << "Enter (ID Name Type Qty): ";
        cin >> id >> name >> type >> qty;
        inv->addItem(id, name, type, qty);
        logEvent("Procurement added: " + name);
    }
    void updateItem()
    {
        int id, qty;
        cout << "Enter ID: ";
        cin >> id;
        Item* item = inv->searchItem(id);
        if (!item)
        {
            cout << "Item not found!\n";
            return;
        }
        cout << "Enter quantity to add: ";
        cin >> qty;
        item->quantity += qty;
        logEvent("Updated item ID " + toStr(id) + " qty +" + toStr(qty));
    }
    void removeItem()
    {
        int id, qty;
        cout << "Enter ID to remove: ";
        cin >> id;
        cout << "Enter quantity to remove: ";
        cin >> qty;

        inv->removeQuantity(id, qty, true);
    }
};

// BST
struct Node
{
    int key;
    Node* left;
    Node* right;
    Node(int k)
    {
        key = k;
        left = right = NULL;
    }
};
class BST
{
public:
    Node* root;
    BST()
    {
        root = NULL;
    }
    Node* insertRec(Node* node, int key)
    {
        if (!node)
        {
            return new Node(key);
        }
        if (key < node->key)
        {
            node->left = insertRec(node->left, key);
        }
        else
        {
            node->right = insertRec(node->right, key);
        }
        return node;
    }
    void insert(int key)
    {
        root = insertRec(root, key);
    }
    void inorder(Node* node)
    {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
};
void handleBST(Inventory& inv)
{
    BST bst;
    Item* temp = inv.getHead();
    while (temp)
    {
        bst.insert(temp->id);
        temp = temp->next;
    }
    cout << "BST (Inorder Traversal): ";
    bst.inorder(bst.root);
    cout << endl;
    logEvent("Displayed BST");
}

//Menu
void menu()
{
    for (int i = 0; i < 115; i++)
    {
        cout << "=";
    }
    cout << endl;
    cout << "Menu: " << endl;
    cout << "1.  Display Inventory\n";
    cout << "2.  Add New Item\n";
    cout << "3.  Remove Item\n";
    cout << "4.  Update Item\n";
    cout << "5.  Sort by Name\n";
    cout << "6.  Sort by Type\n";
    cout << "7.  Sort by ID\n";
    cout << "8.  Search Item by ID\n";
    cout << "9.  Display BST\n";
    cout << "10. Exit\n";
    for (int i = 0; i < 115; i++)
    {
        cout << "=";
    }
    cout << endl;
}

int main()
{
    Inventory inv;
    Procurement procurement(&inv);
    int choice;

    do {
        menu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            inv.displayAll();
            break;
        }
        case 2:
        {
            procurement.addNewItem();
            break;
        }
        case 3:
        {
            procurement.removeItem();
            break;
        }
        case 4:
        {
            procurement.updateItem();
            break;
        }
        case 5:
        {
            inv.sortByName();
            inv.displayAll();
            break;
        }
        case 6:
        {
            inv.sortByType();
            inv.displayAll();
            break;
        }
        case 7:
        {
            inv.sortByID();
            inv.displayAll();
            break;
        }
        case 8:
        {
            int id;
            cout << "Enter ID: ";
            cin >> id;

            Item* f = inv.searchItem(id);
            if (f)
                cout << f->name << " | " << f->type << " | Qty: " << f->quantity << endl;
            else
                cout << "Item not found!\n";
            break;
        }
        case 9:
        {
            handleBST(inv);
            break;
        }
        case 10:
        {
            cout << "Exiting the Program." << endl;
            generateReport();
            break;
        }
        default:
        {
            cout << "Invalid option!!" << endl;
        }
        }
    } while (choice != 10);

    system("pause");
    return 0;
} 