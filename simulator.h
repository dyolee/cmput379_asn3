struct node {
	int pageNumber;
	unsigned int address;
	int value;
	struct node *next;
};


struct hash {
	struct node *head;
};

struct node * createNode (unsigned int address, int value, int pageNumber);

void init (int psize, int winsize);

void put (unsigned int address, int value);

int get (unsigned int address);

void done();

