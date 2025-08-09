#include <iostream>
#include <initializer_list>

template <typename T>
struct Node
{
    T data;
    Node<T>* next = nullptr;
};

template <typename T>
class Queue
{
    public:
        ~Queue()
        {
            clear();
        }

        Queue(int cap) : capacity(cap), num_elem(0), frontPtr(nullptr), rearPtr(nullptr) {} // constructor

        Queue(std::initializer_list<T> init_list) : capacity(init_list.size()), num_elem(0), frontPtr(nullptr), rearPtr(nullptr) // initializer_list constructor
        {
            for(const T& item : init_list)
            {
                enqueue(item);
            }
        }

        Queue(const Queue& rhs) : capacity(rhs.capacity), num_elem(0), frontPtr(nullptr), rearPtr(nullptr)
        {
            Node<T>* tempPtr = rhs.getFrontPtr();
            
            while(tempPtr != nullptr) // copy every element from the rhs queue into this new queue
            {
                enqueue(tempPtr->data);
                tempPtr = tempPtr->next;
            }
        }

        Queue& operator=(const Queue& rhs)
        {
            if(this == &rhs)
            {
                return *this;
            }

            while(!empty())
            {
                dequeue();
            }

            capacity = rhs.capacity;
            num_elem = 0;

            Node<T>* tempPtr = rhs.getFrontPtr();
            
            while(tempPtr != nullptr) // copy every element from the rhs queue into this new queue
            {
            enqueue(tempPtr->data);
            tempPtr = tempPtr->next;
            }

            return *this;
        }

        void enqueue(const T& item)
        {
            if(capacity == 0)
            {
                std::cerr << "Error: Queue has capacity of 0\n";
                return;
            }
            else if(num_elem == capacity)
            {
                std::cerr << "Error: Queue is full\n";
                return;
            }

            if(frontPtr == nullptr)
            {
                frontPtr = new Node<T>;
                frontPtr->data = item;
                rearPtr = frontPtr;
            }
            else
            {
                Node<T>* newNode = new Node<T>;
                newNode->data = item;
                rearPtr->next = newNode;
                rearPtr = newNode;
            }
            num_elem++;
        }

        void enqueue(T&& item)
        {
            if(capacity == 0)
            {
                std::cerr << "Error: Queue has capacity of 0\n";
                return;
            }
            else if(num_elem == capacity)
            {
                std::cerr << "Error: Queue is full\n";
                return;
            }

            if(frontPtr == nullptr)
            {
                frontPtr = new Node<T>;
                frontPtr->data = std::move(item);
                rearPtr = frontPtr;
            }
            else
            {
                Node<T>* newNode = new Node<T>;
                newNode->data = std::move(item);
                rearPtr->next = newNode;
                rearPtr = newNode;
            }
            num_elem++;
        }

        T dequeue()
        {
            if (empty())
            {
                throw std::out_of_range("Queue is empty\n");
            }

            Node<T>* tempPtr = frontPtr;
            T value = tempPtr->data;

            frontPtr = frontPtr->next;
            delete tempPtr;

            num_elem--;

            if(frontPtr == nullptr)
            {
                rearPtr = nullptr;
            }

            return value;
        }

        T& front()
        {
            if (empty())
            {
                throw std::out_of_range("Queue is empty\n");
            }
            
            return frontPtr->data;
        }

        bool empty() const { return num_elem == 0; }

        void clear()
        {
            while(!empty())
            {
                dequeue();
            }
        }

        size_t totalCapacity() const { return capacity; }

        size_t size() const { return num_elem; }

        void printQueue() const
        {
            Node<T>* temp = frontPtr;
            while(temp != nullptr)
            {
                std::cout << temp->data << std::endl;
                temp = temp->next;
            }
        }
    
    private:
        size_t capacity;// capacity that queue can hold
        size_t num_elem; // number of elements currently in queue (always <= capacity)
        Node<T>* frontPtr; // pointer to the front of the queue
        Node<T>* rearPtr; // pointer to the rear of the queue
        Node<T>* getFrontPtr() const { return frontPtr; } // get the front pointer (keeping this method private)
        Queue() = delete; // delete default constructor to enforce initialization of object with some capacity
};

int main()
{
    try
    {
        // 1. Create a queue with capacity 3
        Queue<int> q1(3);
        std::cout << "Created queue with capacity: " << q1.totalCapacity() << "\n";

        // 2. Enqueue some elements
        q1.enqueue(10);
        q1.enqueue(20);
        q1.enqueue(30);

        std::cout << "Queue after enqueueing 10, 20, 30:\n";
        q1.printQueue();

        // 3. Try enqueue when full
        std::cout << "Trying to enqueue 40 (should be full)...\n";
        q1.enqueue(40); // should print error

        // 4. Dequeue elements
        std::cout << "Dequeued: " << q1.dequeue() << "\n";
        std::cout << "Front after dequeue: " << q1.front() << "\n";

        // 5. Enqueue again to test rearPtr update
        q1.enqueue(40);
        std::cout << "Queue after enqueueing 40:\n";
        q1.printQueue();

        // 6. Dequeue everything to test rearPtr reset
        while(!q1.empty())
        {
            std::cout << "Dequeued: " << q1.dequeue() << "\n";
        }

        std::cout << "Queue empty? " << (q1.empty() ? "Yes" : "No") << "\n";

        // 7. Try dequeue on empty queue (should throw)
        std::cout << "Trying to dequeue from empty queue...\n";
        q1.dequeue(); // will throw

    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    // 8. Test initializer_list constructor
    Queue<std::string> q2{"Alice", "Bob", "Charlie"};
    std::cout << "Initializer list queue:\n";
    q2.printQueue();

    // 9. Test copy constructor
    Queue<std::string> q3 = q2;
    std::cout << "Copied queue (q3):\n";
    q3.printQueue();

    // 10. Test copy assignment
    Queue<std::string> q4(5);
    q4 = q2;
    std::cout << "Assigned queue (q4):\n";
    q4.printQueue();

    return 0;
}