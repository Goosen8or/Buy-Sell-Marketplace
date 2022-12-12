

class Node
{
    
public:
    string title;

protected:
    Node *parent_;
    /**
     * Optionally, the base Node can declare an interface for setting and
     * accessing a parent of the component in a tree structure. It can also
     * provide some default implementation for these methods.
     */
public:
    Node(string s){
        title = s;
    }
    virtual ~Node() {}
    
    void SetParent(Node *parent)
    {
        this->parent_ = parent;
    }
    Node *GetParent() const
    {
        return this->parent_;
    }
    /**
     * In some cases, it would be beneficial to define the child-management
     * operations right in the base Node class. This way, you won't need to
     * expose any concrete component classes to the client code, even during the
     * object tree assembly. The downside is that these methods will be empty for
     * the leaf-level components.
     */
    virtual void Add(Node *component) {}
    virtual void Remove(Node *component) {}
    /**
     * You can provide a method that lets the client code figure out whether a
     * component can bear children.
     */
    virtual bool IsCategory() const
    {
        return false;
    }
    /**
     * The base Node may implement some default behavior or leave it to
     * concrete classes (by declaring the method containing the behavior as
     * "abstract").
     */
    virtual bool Operation(string findString) const = 0;
    
    string getTitle() {
        return title;
    }
    
    void setTitle(string s){
        title = s;
    }
    
    virtual list<Node *> getChildren() = 0;
    
    virtual string getDescription() = 0;
    virtual double getPrice() = 0;
    virtual int getQuantity() = 0;
    virtual double getMaxDiscount() = 0;
    virtual void setQuantity(int neqQuant) = 0;

};
/**
 * The Item class represents the end objects of a composition. A leaf can't have
 * any children.
 *
 * Usually, it's the Item objects that do the actual work, whereas Category
 * objects only delegate to their sub-components.
 */


class Item : public Node
{
private:
    string description;
    double price;
    int quantity;
    double maxDiscount;
public:
    Item(string title, string descrip, double pri, int quant, double maxDisc):Node(title){
        description = descrip;
        price = pri;
        quantity = quant;
        maxDiscount = 0.01 * maxDisc;
    }
    bool Operation(string findString) const override
    {
        if (title.find(findString) != string::npos){
            cout << endl << endl;
            cout << "The following item is for sale:" << endl;
            cout << "| Item key" << setw(20) << "| Item Title" << setw(20) << "| Stock Quantity" << setw(20) << "| List Price" << setw(20) << "| Description" << endl << endl;
            cout << "1" << setw(20) << title << setw(20) << quantity << setw(20) << price << setw(20) << description << setw(20);
            return true;
        }
        return false;
    }
    list<Node *> getChildren() override{
        list<Node *> temp;
        return temp;
    }
    
    string getDescription() override{
        return description;
    }
    
    double getPrice() override{
        return price;
    }
    int getQuantity() override{
        return quantity;
    }
    double getMaxDiscount() override {
        return maxDiscount;
    }
    
    void setQuantity(int quant) override {
        quantity = quant;
    }

    
};

/**
 * The Category class represents the complex components that may have children.
 * Usually, the Category objects delegate the actual work to their children and
 * then "sum-up" the result.
 */
class Category : public Node
{
    /**
     * @var \SplObjectStorage
     */
private:
    string title;
protected:
    std::list<Node *> children_;

public:
    /**
     * A composite object can add or remove other components (both simple or
     * complex) to or from its child list.
     */
    Category(string s) : Node(s){
        title = s;
    };
    
    void Add(Node *component) override
    {
        this->children_.push_back(component);
        component->SetParent(this);
    }
    /**
     * Have in mind that this method removes the pointer to the list but doesn't
     * frees the
     *     memory, you should do it manually or better use smart pointers.
     */
    void Remove(Node *component) override
    {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    bool IsCategory() const override
    {
        return true;
    }
    /**
     * The Category executes its primary logic in a particular way. It traverses
     * recursively through all its children, collecting and summing their results.
     * Since the composite's children pass these calls to their children and so
     * forth, the whole object tree is traversed as a result.
     */
    bool Operation(string find) const override
    {
        bool found = false;
        if (title.find(find) != string::npos){
            cout << endl;
            cout << "The following category was found:" << endl;
            cout << "| Category key" << setw(20) << "| Category Title" << endl;
            cout << "1" << setw(20) << title << setw(20);
        }
        for (const Node *c : children_)
        {
            found = c->Operation(find);
        }
        
        return  false;
    }
    
    list<Node *> getChildren() override {
        return this->children_;
    }
    string getDescription() override{
        return "";
    };
    double getPrice() override{
        return 0.0;
    };
    int getQuantity() override{
        return 0;
    };
    double getMaxDiscount() override{
        return 0.0;
    };
    void setQuantity(int quant) override {
    }
};
/**
 * The client code works with all of the components via the base interface.
 */
bool searchItem(Node *component, string textFind)
{
    // ...
    bool found =  component->Operation(textFind);
    
    return found;
    // ...
}

void deleteCategory(Node* current){
    delete current;
}

void editCategory(Node* current){
    string titleNew;
    cout << "Enter title: ";
    cin >> titleNew;
    current->setTitle(titleNew);
    return;
    
}
