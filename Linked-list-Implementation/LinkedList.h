template<class T>
struct Node
{
    T data;
    Node * next;
};
template<class T>
class LinkedList
{
private:
    Node <T> *first;
    Node<T> *last;
public:
    LinkedList()
    {
        first = nullptr;
        last  = nullptr;
    }

    void lInsert(T key)
    {
        Node<T> *p = first;
        Node<T> *q = last;
        Node<T> *t = new Node<T>;
        t->data = key;
        t->next = nullptr;
        if(p==nullptr)
        {
           p = q = t;
            
        }
        else
        {
           q->next = t;
           q = t;
        }
        first = p;
        last = q;
    }

    void insertInto(T key , int pos)
    {
        Node<T>* p =first;
        if(pos < 0 || pos > count())
            std::cout<<"Insertion out of bound\n";
        else
        {
            Node<T>* t = new Node<T>;
            t->data = key;
            if(pos == 0)
            {
                t->next = p;
                p = t;
                first = p;
            }
            else
            {
            for(int i = 0 ; i < pos-1 ; i++)
            {
                p = p->next;
            }
            t->next = p->next;
            p->next = t; 
            }
        }
    }

    int count()
    {
        int sum = 0 ;
        Node <T> *p = first;
        if(!p)
            return 0;
        else
        {
            while(p)
            {
                sum++;
                p = p->next;
            }
        }
        return sum;
    }

    bool search(T key)
    {
        Node <T> *p = first;
        if(!p)
            return 0;
        else
        {
            while(p)
            {
                if(p->data == key)
                    {
                        return 1;
                    }
                else
                    p = p->next;
            }
        }
        return 0;
    }

    void deleteKey(T key)
	{
		if (!search(key))
			return;
		else
		{
			Node <T>* w = nullptr;
			Node<T>* q = nullptr;
			if (first->data == key)
			{
				q = first;
				first = first->next;
				 w = first;
				delete q;
			}
			else
			{
				Node <T>* p = first;
				w = p;
				while (p)
				{
					q = p;
					p = p->next;
					if (p->data == key)
						break;
				}
				q->next = p->next;
				delete p;
				first = w;
			}
		}
	}

    void deleteFrom(int pos)
    {
        pos++;
        if(pos < 0 || pos >count())
            std::cout<<"deletion out of bound\n";
        else
        {
            Node<T> *p=first;
            Node<T> *q=nullptr;
            Node<T> *w=nullptr;
            if(pos == 1)
            {
                q = first;
                first = first->next;
                w = first;
                delete q;
            }
            else
            {
                w = p;
                for(int i = 0 ; i < pos-1 ;i++)
                {
                    q = p ;
                    p = p->next;
                }
                q->next = p->next;
                delete p;
                first = w;
            }
        }
    }

    Node<T>* gethead()
    {
        return first;
    }
};
template<class T>
static void concat(Node<T>* p1 ,Node<T>* p2)
    {
        if(p1 && p2)
        {
            if(p1->next == nullptr)
                p1->next = p2;
            else
                concat(p1->next,p2);
        }
        else
        {
            std::cout<<"Can't be concatenated because one of them are null\n";
        }
    }

template<class T>
static void printLL(Node<T> *p)
    {
        while(p)
        {
            std::cout<<p->data<<" ";
            p = p->next;
        }
        std::cout<<std::endl;
    }

