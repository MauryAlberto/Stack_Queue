#include <iostream>
#include <initializer_list>

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template <typename T>
class Stack
{
    public:
        ~Stack() // destructor
        {
            clear();
        }

        Stack(int cap) : capacity(cap), num_elem(0), topPtr(nullptr) {} // constructor

        Stack(std::initializer_list<T> init_list) : capacity(init_list.size()), num_elem(0), topPtr(nullptr) // initializer_list constructor
        {
            for(const T& item : init_list)
            {
                push(item);
            }
        }

        Stack(const Stack& rhs) : capacity(rhs.capacity), num_elem(0), topPtr(nullptr)
        {
            capacity = rhs.capacity;
            num_elem = 0;

            Node<T>* tempPtr = rhs.getTopPtr();
            Stack tempStack(rhs.capacity);

            while(tempPtr != nullptr) // push onto temp stack in reversed order
            {
                tempStack.push(tempPtr->data);
                tempPtr = tempPtr->next;
            }

            while(!tempStack.empty()) // push onto 'this' stack which undoes the reversed order
            {
                push(tempStack.pop());
            }
        }

        Stack& operator=(const Stack& rhs)
        {
            if(this == &rhs)
            {
                return *this;
            }

            while(!empty())
            {
                pop();
            }

            capacity = rhs.capacity;
            num_elem = 0;

            Node<T>* tempPtr = rhs.getTopPtr();
            Stack tempStack(rhs.capacity);

            while(tempPtr != nullptr) // push onto temp stack in reversed order
            {
                tempStack.push(tempPtr->data);
                tempPtr = tempPtr->next;
            }

            while(!tempStack.empty()) // push onto 'this' stack which undoes the reversed order
            {
                push(tempStack.pop());
            }

            return *this;
        }

        void push(const T& item)
        {
            if(capacity == 0)
            {
                std::cerr << "Error: Stack has capacity of 0\n";
                return;
            }
            else if(num_elem == capacity)
            {
                std::cerr << "Error: Stack is full\n";
                return;
            }

            Node<T>* newNode = new Node<T>;
            newNode->data = item;
            newNode->next = topPtr;
            topPtr = newNode;
            num_elem++;
        }

        void push(T&& item)
        {
            if(capacity == 0)
            {
                std::cerr << "Error: Stack has capacity of 0\n";
                return;
            }
            else if(num_elem == capacity)
            {
                std::cerr << "Error: Stack is full\n";
                return;
            }

            Node<T>* newNode = new Node<T>;
            newNode->data = std::move(item);
            newNode->next = topPtr;
            topPtr = newNode;
            num_elem++;
        }

        T pop() // return the top value and remove it
        {
            if(empty())
            {
                throw std::out_of_range("Stack is empty\n");
            }

            Node<T>* tempPtr = topPtr;
            T value = tempPtr->data;

            topPtr = topPtr->next;
            delete tempPtr;

            num_elem--;
            return value;
        }

        T& top() const // return the top value and do not remove it
        { 
            if (empty())
            {
                throw std::out_of_range("Stack is empty\n");
            }

            return topPtr->data;
        } 

        bool empty() const { return num_elem == 0; }

        size_t totalCapacity() const { return capacity; }

        size_t size() const { return num_elem; }

        void clear()
        {
            while(!empty())
            {
                pop();
            }
        }

        void printStack() const
        {
            Node<T>* temp = topPtr;
            while(temp != nullptr)
            {
                std::cout << temp->data << std::endl;
                temp = temp->next;
            }
        }
    
    private:
        size_t capacity; // capacity that stack can hold
        size_t num_elem; // number of elements currently in stack (always <= capacity)
        Node<T>* topPtr; // pointer to the top of the stack
        Node<T>* getTopPtr() const { return topPtr; } // get the top pointer (keeping this method private)
        Stack() = delete; // delete default constructor to enforce initialization of object with some capacity
};

int main()
{
    try
    {
        // 1. Create a stack with capacity 3
        Stack<int> s1(3);
        std::cout << "Created stack with capacity: " << s1.totalCapacity() << "\n";

        // 2. Push some elements
        s1.push(10);
        s1.push(20);
        s1.push(30);

        std::cout << "Stack after pushing 10, 20, 30:\n";
        s1.printStack();

        // 3. Try push when full
        std::cout << "Trying to push 40 (should be full)...\n";
        s1.push(40); // should print error

        // 4. Check top element
        std::cout << "Top element: " << s1.top() << "\n";

        // 5. Pop an element
        std::cout << "Popped: " << s1.pop() << "\n";
        std::cout << "Stack after pop:\n";
        s1.printStack();

        // 6. Push again to test LIFO order
        s1.push(40);
        std::cout << "Stack after pushing 40:\n";
        s1.printStack();

        // 7. Pop all elements to empty stack
        while(!s1.empty())
        {
            std::cout << "Popped: " << s1.pop() << "\n";
        }

        std::cout << "Stack empty? " << (s1.empty() ? "Yes" : "No") << "\n";

        // 8. Try pop on empty stack (should throw)
        std::cout << "Trying to pop from empty stack...\n";
        s1.pop(); // will throw
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    // 9. Test initializer_list constructor
    Stack<std::string> s2{"Alice", "Bob", "Charlie"};
    std::cout << "Initializer list stack:\n";
    s2.printStack();

    // 10. Test copy constructor
    Stack<std::string> s3 = s2;
    std::cout << "Copied stack (s3):\n";
    s3.printStack();

    // 11. Test copy assignment
    Stack<std::string> s4(5);
    s4 = s2;
    std::cout << "Assigned stack (s4):\n";
    s4.printStack();

    return 0;
}