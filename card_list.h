// card_list.h
// Author: Oscar Valeriano
// All class declarations related to defining a BST that represents a player's hand
class bst {
    private:
        struct Node {
            Card card;
            Node* left;
            Node* right;
            Node* parent;

            Node(const Card& c, Node* p = nullptr)
                : card(c), left(nullptr), right(nullptr), parent(p) {}
        };

        Node* root;
        void insertHelper(Node*& curr, const Card& card, Node* parent);
        Node* findNode(Node* curr, const Card& card) const;
        void removeNode(Node*& curr, const Card& card);
        void deleteTree(Node* node);
        void printInOrder(Node* node) const;
        Node* getMin(Node* node) const;
        Node* getMax(Node* node) const;
        Node* getSuccessor(Node* node) const;
        Node* getPredecessor(Node* node) const;

    public:
        bst();
        ~bst();
        void insert(const Card& card);
        void remove(const Card& card);
        bool contains(const Card& card) const;
        void printDeck() const;
        class Iterator {
        private:
            Node* curr;
            const bst* tree;
        public:
            Iterator(Node* node = nullptr) : curr(node), tree(nullptr) {}
            const Card& operator*() const { return curr->card; }
            const Card* operator->() const { return &(curr->card); }
            Iterator& operator++();
            Iterator& operator--();
            bool operator!=(const Iterator& other) const { return curr != other.curr; }
            bool operator==(const Iterator& other) const { return curr == other.curr; }
    
            friend class bst;
        };

        Iterator begin() const;
        Iterator end() const;
        Iterator rbegin() const;
        Iterator rend() const;
};
#endif
