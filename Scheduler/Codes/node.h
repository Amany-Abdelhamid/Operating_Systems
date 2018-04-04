class node
{//private data
int data;
node * next;

public:
node() {data=0; next=0;} //constructor
node(int d) :data(d), next(0 ) {} // another form of constructor

//getter functions
int getData() {return data;}
node * getNext() {return next;}

//setter functions
void setData(int d) {data=d;}
void setNext( node * n) {next =n;}

friend class list;
};
